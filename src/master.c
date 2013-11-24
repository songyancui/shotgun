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
#include "log.h"
#include "master.h"
#include "channel.h"
char *_master_status[5]={"MASTER_STATUS_PREPARE","MASTER_STATUS_RUNNING","MASTER_STATUS_STOPING","MASTER_STATUS_STOPED","MASTER_STATUS_CHANGE_CONFIG"};
#define MTSTATUS(n) _master_status[n]

char * _master_command[3]={"MASTER_COMMANDED_STOP","MASTER_COMMANDED_START","MASTER_COMMANDED_CHANGE_CONFIG"};
#define MC2STR(n) _master_command[n]

Master * create_master(){
	Master master_item ;
}

int 	master_run(Master * m){
	sgLogging(LOG_DEBUG,"%s","master_running");
	sgLogging(LOG_DEBUG,"%s %d","master_runing",m->channel->fd[1]);
	Inner_msg inner_msg;
	receive_msg_channel(m->channel,&inner_msg);	
	sgLogging(LOG_DEBUG,"%s recieved %d","master_runed",inner_msg.command);
	
}
