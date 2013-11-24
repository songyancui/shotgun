#include "log.h"
#include "sgconfig.h"
#include "main.h"
#include "controller.h"
#include "master.h";

Server_config g_server_config;


int main(int argc, char ** argv){
    sgLogInit(LOG_DEBUG,NULL);
    sgLogging(LOG_DEBUG, "%s", "debug");
    sgLogging(LOG_NOTICE, "%s", "notice");
    sgLogging(LOG_WARNING, "%s", "warning");
    sgConfigInit("./../conf/main.json");
    sgLogging(LOG_DEBUG,"%d",g_server_config.port);  
    sgLogging(LOG_DEBUG,"%d",g_server_config.worker_count);
	init_controller();
	run_controller();	  
    return;
}
