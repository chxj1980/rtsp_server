#include "rtsp_message_url.h"
#include "rtsp_memery.h"
#include <iostream>
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h> 
#include <unistd.h>
#include <sys/stat.h> 
using namespace std;
char  g_filepath[100] = {0};
STATUSCODE RtspMessageUrl::rtsp_message_url_check(rtsp_event_t* event)
{
	char *ptr[10];
    ptr[0] = strstr(event->request_message->url, "//");
    if(ptr[0] == NULL)
    	return 400;
    ptr[1] = strchr(ptr[0], ':');
    if(ptr[1] == NULL)
    	return 400;
    int i = 1;
    while(ptr[i])
    {
    	i++;
    	ptr[i] = strchr(ptr[i-1]+1, '/');
    }
    int j = i;
  //  int j = i - 1;// SETUP URL rtsp://192.168.0.106:554/media/mmcblk0p1/20180109154330/
    int length = ptr[j-1] - ptr[2];
    strncpy(g_filepath, ptr[2]+1, length -1);
    cout<<"g_filepath"<<g_filepath<<endl;
    ptr[j] = strchr(ptr[j-1], '\0');
    if(ptr[j] == NULL)
    	return 400;
    length =  ptr[j] - ptr[j-1];
    strncpy(event->rtp_message->filename, ptr[j-1] + 1, length - 1);
  //  strncpy(rtp_message->filename, ptr[j-1] + 1, length - 2);
    STATUSCODE res = rtsp_message_url_check_file(event->rtp_message);
    if(res != 200)
        return res; 
    strncpy(event->response_message->url, event->request_message->url, URL_SIZE);
    return 200;
}
STATUSCODE RtspMessageUrl::rtsp_message_url_check_file(rtp_message_t* rtp_message)
{
    char filepath[100];
    memset(filepath, 0, 100);
    sprintf(filepath, "/%s/%s", g_filepath, rtp_message->filename);
    if(access(filepath, F_OK) != 0)
        return 404;
    int fram_num = 15000;
   // int fram_num = GetFramNum(filepath);
    rtp_message->record_time = fram_num/25.0;
    rtp_message->filesize = get_file_size(filepath);
	return 200;
}

unsigned long RtspMessageUrl::get_file_size(char *path)  
{  
    unsigned long filesize = -1;      
    struct stat statbuff;  
    if(stat(path, &statbuff) < 0){  
        return filesize;  
    }else{  
        filesize = statbuff.st_size;  
    }  
    return filesize;  
}
