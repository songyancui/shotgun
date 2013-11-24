#include "log.h"
#include "main.h"
#include "channel.h"



int main(int argc, char ** argv){
    sgLogInit(LOG_DEBUG,NULL);
    sgLogging(LOG_DEBUG, "%s", "debug");
    sgLogging(LOG_NOTICE, "%s", "notice");
    sgLogging(LOG_WARNING, "%s", "warning");
	Channel * channel_ptr;
	channel_ptr = create_channel();
//	pid_t child_id;

//	int fd[2] = {1,2};
//	printf("%d", fd[1]);
	int child_id;
	char * a;
	a  = malloc(3);
	memcpy(a,"ad\0",3);
	if((child_id=fork())==0){
		printf("%s",a);
		memcpy(a,"ab\0",3);
		printf("%p",a);
		printf("%s",a);
		close(channel_ptr->fd[1]);		//child	
		Inner_msg *msg = malloc(sizeof(Inner_msg));
			   msg->command =12;
		sleep(2);	
		send_msg_channel(channel_ptr,msg);
	}else{
		close(channel_ptr->fd[0]);
		Inner_msg inner_msg;
		receive_msg_channel(channel_ptr,&inner_msg);
		
	}
	return;
}
