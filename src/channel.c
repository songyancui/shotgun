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
#include <sys/types.h>
#include <sys/socket.h>
#include "channel.h"
#include <errno.h>



Channel *create_channel(){
	Channel * channel_ptr;
	channel_ptr  = malloc(sizeof(Channel));
	memset(channel_ptr,0,sizeof(Channel));
	if(socketpair(AF_UNIX, SOCK_STREAM,0 ,channel_ptr->fd)<0){
		sgLogging(LOG_FATAL,"%s","create channel failed");
	}
	sgLogging(LOG_DEBUG,"%s","create channel successful");
	return channel_ptr;		
}

int 	send_msg_channel(Channel * channel_ptr,Inner_msg * msg){
		if(channel_ptr ==NULL) {
			sgLogging(LOG_WARNING,"%s","There is no channel to send");
		}
		int write_len;
		sgLogging(LOG_DEBUG,"%s %d","writing the msg",msg->command);
		
		write_len = write(channel_ptr->fd[0],msg,sizeof(Inner_msg));
		if(write_len != sizeof(Inner_msg)){  //TODO  care interupting
			sgLogging(LOG_WARNING,"%s write_len is  %d"," writing message failed  ",write_len);
		}
			sgLogging(LOG_DEBUG,"%s size: %d","send complete",write_len);
	}

int	receive_msg_channel(Channel * channel_ptr,Inner_msg *msg){
		sgLogging(LOG_DEBUG,"%s","receive reading");
		Inner_msg *inner_msg_ptr ;
		inner_msg_ptr = msg;	
		int receive_msg_len;
		if(channel_ptr ==NULL){
			sgLogging(LOG_WARNING,"%s","Channel is NULL, can not receive message");
			return ;	
		}
		receive_msg_len = read(channel_ptr->fd[1],inner_msg_ptr, sizeof(Inner_msg));
			
		if(receive_msg_len == -1){
				sgLogging(LOG_DEBUG,"%s errno:%d ","receive err",errno);
				return -1;
		}
		sgLogging(LOG_DEBUG,"%s %d %d","receive the mess",inner_msg_ptr->command,sizeof(Inner_msg));
		
		return 1;
	}
	
void channel_read_callback(int fd, void * ptr){
	ssize n;
	struct iovec iov[1];
	struct msghdr msg;
	
	iov[0].iov_base = ptr;
	iov[0].iov_len = sizeof(*ptr);
	
	msg.msg_control = NULL;
	msg.msg_controllen = 0;
	msg.msg_name = NULL;
	msg.msg_namelen = 0; 
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;
	msg.msg_flags = 0;

	n = recvmsg(fd, &msg, 0);
	
	if(n === -1){
		sgLogging(LOG_WARNING,"%s","recvmsg failed ");
	}
		
	if(n < sizeof(ptr)){
			sgLogging(LOG_WARNING,"%s","recvmsg returned not enough message");
			
	}
	return ptr;
}


int channel_push(int fd ,void * ptr){
	ssize_t n;
	struct iovec iov[1];
	struct msghdr msg;
	
	iov[0].iov_base = ptr;
	iov[0].iov_len = sizeof(*ptr);
	
	msg.msg_control = NULL;
	msg.msg_controllen = 0;
	msg.msg_name =NULL;
	msg.msg_namelen = 0;
	msg.msg_iov = iov;
	msg.msg_iovlen  =1;
	msg.msg_flags = 0;

	n = sendmsg(fd, ptr,0);
	
	if(n ==-1){
		sgLogging(LOG_WARNING,"%s","channel push failed");
	}else{
		sgLogging(LOG_DEBUG,"%s","sendmsg failed");
	}
	return 0;
}


int	close_channel(Channel * channel_ptr){
		if(channel_ptr !=NULL){
			sgLogging(LOG_WARNING,"%s","The channel has been closed");
			return ;}
		close(channel_ptr->fd[0]);
		close(channel_ptr->fd[1]);
	}



