/**
* 
* Copyright (c) 2006-2020, Songyan Cui <songyancui.gmail.com>
* All rights reserved.
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*   * Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in the
*     documentation and/or other materials provided with the distribution.
*   * Neither the name of Redis nor the names of its contributors may be used
*     to endorse or promote products derived from this software without
*     specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN	
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "log.h"
#include "third/json-c/json.h"
#include "config.h"
#include "sgconfig.h"
#include "controller.h"
#include "master.h"
#include "channel.h"
#include "errno.h"

int init_controller(){
	if(sizeof(g_server_config)==0) { 
		sgLogging(LOG_FATAL,"%s","There is no server_config");
	}
	return 1;
}

int run_controller(){
	int master_count = g_server_config.master_count ;
	int port = g_server_config.master_count;
	int listenfd;
	struct sockaddr_in server_addr;
	pid_t child_pid;
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = port;
	
	bind(listenfd, (struct sockaddr_in *) &server_addr, sizeof(server_addr));
	
	listen(listenfd, BACKLOGQ);
	sgLogging(LOG_DEBUG,"%s","controller is listening");
	
	Master *m;
	m = calloc(master_count,sizeof(Master));
	sgLogging(LOG_DEBUG,"%d",master_count);
	Channel * channel_ptr ;
	int i=0;
	for(i=0; i<master_count; i++){
		sgLogging(LOG_DEBUG,"%s %d","loop create the masters" ,i);
		channel_ptr = create_channel();	
		m[i].status = MASTER_STATUS_PREPARE ;
		m[i].master_id = i;
		m[i].channel = channel_ptr;
		if((m[i].pid = fork())==0){
			sgLogging(LOG_DEBUG,"%s %d  started ","child precess",getpid() );
			//master_init();  //child process
			close(m[i].channel->fd[0]);
			master_run(&m[i]); 
			break;  
		}else{
			close(m[i].channel->fd[1]);
			if(i==(master_count-1)){
				int status ;
				Inner_msg *msg = malloc(sizeof(Inner_msg));
				msg->command = 10;
				sleep(3);
				send_msg_channel(m[0].channel,msg);
				send_msg_channel(m[1].channel,msg);
				while((child_pid = waitpid(-1,&status,0 ))!= -1){
                			sgLogging(LOG_DEBUG,"chlid %d existed",child_pid);
        			}	
			}
			continue;		//parent process
		}
		
	}
		
	return (1);	
}


