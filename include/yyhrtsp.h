#ifndef _YYHRTSP_H_
#define _YYHRTSP_H_
#include "rtsp_event.h"
#include "rtp.h"
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <errno.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <unistd.h>
#include <pthread.h>
#include <assert.h>          
#include <string> 
#include <map>
#include <iostream>
extern map<int, string> map_client_ipaddr;
using namespace std;
int     create_server(void);
void*  rtsp_thread(void * sock_fd);

		

#endif