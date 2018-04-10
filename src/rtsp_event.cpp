#include "rtsp_event.h"
#include <malloc.h>  
#include <iostream>
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h> 

rtsp_event_t* RtspEventHandle::rtsp_event_init(int fd)
{
	rtsp_event_t* event;
	event = rtsp_event_mem_calloc();
	if(event == NULL)
		return NULL;
	event->sid = fd;
	if(rtp_message_mem_calloc(event->rtp_message))
		return NULL;
	if(rtsp_request_message_mem_calloc(event->request_message))
		return NULL;
	if(rtsp_response_message_mem_calloc(event->response_message))
		return NULL;
	event->teardown = 0;
	event->play = 0;
	event->pause = 0;
	event->scale_stat = 0;
	event->rtp_message->cur_timestamp = 0;
	event->rtp_message->npt_time = 0;
	event->rtp_message->filesize = 0;
	return event;
}
int RtspEventHandle::rtsp_event_handle(char* recv_buff, char* send_buff, rtsp_event_t* event,const char *client_ip)
{
	strcpy(event->rtp_message->client_ip, client_ip);
	if((event->sid) % 2 == 0)
		event->rtp_message->server_port = event->sid + 10002;
	else
		event->rtp_message->server_port = 60001 - event->sid ;
	char *ptr = strchr(recv_buff,' ');
	int length = ptr - recv_buff;
	char tmp[20];
	memset(tmp,0,20);
	strncpy(tmp, recv_buff, length);
	if(strstr(tmp, "RTSP"))
	{
		if(rtsp_response_message_init(recv_buff, event->response_message))
		    return -1;
	}
	else
	{
		if(rtsp_request_message_init(recv_buff, event->request_message))
		    return -1;
		event->cseq = event->request_message->cseq;
		event->response_message->cseq = event->request_message->cseq;
		event->type = rtsp_request_message_get_method(event->request_message);
		if(event->type == -1)
		{
			rtsp_build_response_message(send_buff, event, 405);
			return -1;
		}
		int response_status_code = rtsp_request_message_handle(event);
		if( response_status_code == -1)
			return -1;
		if(rtsp_build_response_message(send_buff, event, response_status_code))
		    return -1;
	}
	return 0;
}
int RtspEventHandle::rtsp_event_free(rtsp_event_t* event)
{
	if(rtp_message_mem_free((event->rtp_message)))
		return -1;
	if(rtsp_response_message_mem_free((event->response_message)))
		return -1;
	if(rtsp_request_message_mem_free((event->request_message)))
		return -1;
	if(rtsp_event_mem_free(event))
		return -1;

	return 0;
}