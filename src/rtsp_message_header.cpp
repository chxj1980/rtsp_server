#include "rtsp_message_header.h"
#include "rtsp_memery.h"
#include <iostream>
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h> 
using namespace std;
STATUSCODE RtspMessageHeader::rtsp_message_header_get_client_port(rtsp_header_t* transport_header, rtp_message_t* rtp_message)
{
	char *ptr = strstr(transport_header->value, "client_port");
	if(ptr == NULL)
		return 400;
	char *ptr1 = strchr(ptr, '-');
	if(ptr1 == NULL)
		return 400;
	int length = ptr1 - ptr;
	char temp[10];
	memset(temp, 0, 10);
	strncpy(temp, ptr+12, length-12);
	rtp_message->client_port = atoi(temp);
	return 200;
}

STATUSCODE RtspMessageHeader::rtsp_message_header_range_handle(rtsp_event_t* event)
{
	float replay_time = 0.0;
	unsigned long  timestamp_range = 0;
	if(event->play == 0)
	{
		if(strstr(event->request_message->range->value, "npt"))
		{
		    sprintf(event->response_message->range->value,"npt=0.000-%.3f", event->rtp_message->record_time);
		    event->rtp_message->npt_or_clock = 0;
		}
		else if(strstr(event->request_message->range->value, "clock"))
		{
			rtsp_message_header_range_handle_clock(event);
			event->rtp_message->npt_or_clock = 1;
		}
	}
	if(event->play == 1 && event->pause == 1)
	{
		char *range_value = event->request_message->range->value;
		if(event->rtp_message->npt_or_clock == 0)
		{
			if(strstr(range_value, "npt"))
	        {
	            sprintf(event->response_message->range->value,"%s%.3f", event->request_message->range->value, event->rtp_message->record_time);
	            cout<<"event->response_message->range->value is :"<<event->response_message->range->value<<endl;
	            event->rtp_message->npt_time = rtsp_message_header_range_get_begintime(event->request_message->range->value);
	        }
	        else
	        {
	        	timestamp_range = event->rtp_message->npt_time;
	        	replay_time = timestamp_range/25.0;
	            sprintf(event->response_message->range->value,"npt=%.3f-%.3f", replay_time, event->rtp_message->record_time);
	        }
		}
		else if(event->rtp_message->npt_or_clock == 1)
		{
			if(strstr(range_value, "clock"))
	        {
	            rtsp_message_header_range_handle_clock_goto(event);
	        }
	        else
	        {
	        	rtsp_message_header_range_handle_clock_pause(event);
	        }
		}
	}
	else if(event->play == 1 && event->pause == 0)
	{
		if(event->rtp_message->npt_or_clock == 0)
		{
			if(event->request_message->scale > 0.0)
	        {
	        	event->scale_stat = 1;
	        	float scale = event->request_message->scale;
	            cout<<"scale is :"<<scale<<endl;
	            event->response_message->scale = scale;
	            timestamp_range = event->rtp_message->npt_time;
	            replay_time = timestamp_range/25.0;
	            sprintf(event->response_message->range->value,"npt=%.3f-%.3f", replay_time, event->rtp_message->record_time);
	        }
	        else if(event->request_message->scale < 0.0)	
	        {
	        	event->scale_stat = -1;
	        	float scale = event->request_message->scale;
	            cout<<"scale is :"<<scale<<endl;
	            event->response_message->scale = scale;
	            timestamp_range = event->rtp_message->npt_time;
	            replay_time = timestamp_range/25.0;
	            sprintf(event->response_message->range->value,"npt=%.3f-%.3f", replay_time, event->rtp_message->record_time);
	        }
		}
		else if(event->rtp_message->npt_or_clock == 1)
		{
			if(event->request_message->scale > 0.0)
	        {
	        	event->scale_stat = 1;
	        	float scale = event->request_message->scale;
	            cout<<"scale is :"<<scale<<endl;
	            event->response_message->scale = scale;
	            rtsp_message_header_range_handle_clock_pause(event);
	        }
	        else if(event->request_message->scale < 0.0)	
	        {
	        	event->scale_stat = -1;
	        	float scale = event->request_message->scale;
	            cout<<"scale is :"<<scale<<endl;
	            event->response_message->scale = scale;
	            rtsp_message_header_range_handle_clock_pause(event);
	        }
		}
	}
	memset(event->request_message->range->value, 0, RANGE_SIZE);
	return 200;
}

unsigned long  RtspMessageHeader::rtsp_message_header_range_get_begintime(char *range_value)
{
	char *ptr = strchr(range_value, '=');
	if(ptr == NULL)
		return -1;
	char *ptr1 = strchr(ptr, '-');
	if(ptr1 == NULL)
		return -1;
	char temp[20];
	memset(temp, 0, 20);
	int length = ptr1 - ptr;
	strncpy(temp, ptr+1, length-1);
	float begintime_f = atof(temp);
	unsigned long  begintime_lu = begintime_f * 25;
	return begintime_lu;
}
void RtspMessageHeader::rtsp_message_header_range_handle_clock_pause(rtsp_event_t* event)
{
	int replay_time = 0;
	unsigned long  timestamp_range = 0;
	timestamp_range = event->rtp_message->npt_time;
	replay_time = timestamp_range/25;
	char clock_T_y[6];
	memset(clock_T_y, 0, 6);
	strncpy(clock_T_y, event->rtp_message->filename, 4);
	char clock_T_m[4];
	memset(clock_T_m, 0, 4);
	strncpy(clock_T_m, event->rtp_message->filename + 4, 2);
	char clock_T_d[4];
	memset(clock_T_d, 0, 4);
	strncpy(clock_T_d, event->rtp_message->filename + 6, 2);
	char clock_Z_h[4];
	memset(clock_Z_h, 0, 4);
	strncpy(clock_Z_h, event->rtp_message->filename + 8, 2);
	char clock_Z_m[4];
	memset(clock_Z_m, 0, 4);
	strncpy(clock_Z_m, event->rtp_message->filename + 10, 2);
	char clock_Z_s[4];
	memset(clock_Z_s, 0, 4);
	strncpy(clock_Z_s, event->rtp_message->filename + 12, 2);

	time_t timep, cur_time_t, end_time_t;    
    struct tm begin_time; 
    begin_time.tm_year = atoi(clock_T_y)-1900;
    begin_time.tm_mon  = atoi(clock_T_m)-1;
    begin_time.tm_mday = atoi(clock_T_d);
    begin_time.tm_hour = atoi(clock_Z_h);
    begin_time.tm_min  = atoi(clock_Z_m);
    begin_time.tm_sec  = atoi(clock_Z_s);
    timep = mktime(&begin_time);
    cur_time_t = timep + replay_time;
    struct tm *cur_time;
    cur_time = localtime(&cur_time_t);

    char temp[100];
    memset(temp, 0, 100);
    sprintf(temp,"clock=%02d%02d%02dT%02d%02d%02dZ-", 
		    cur_time->tm_year + 1900, cur_time->tm_mon + 1, cur_time->tm_mday, cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
    end_time_t = timep + event->rtp_message->record_time;
    struct tm *end_time;
    end_time = localtime(&end_time_t);

	sprintf(event->response_message->range->value,"%s%02d%02d%02dT%02d%02d%02dZ", 
		    temp, end_time->tm_year + 1900, end_time->tm_mon + 1, end_time->tm_mday, end_time->tm_hour, end_time->tm_min, end_time->tm_sec);
}
void RtspMessageHeader::rtsp_message_header_range_handle_clock_goto(rtsp_event_t* event)
{
	char clock_T_y[6];
	memset(clock_T_y, 0, 6);
	strncpy(clock_T_y, event->request_message->range->value + 6, 4);
	char clock_T_m[4];
	memset(clock_T_m, 0, 4);
	strncpy(clock_T_m, event->request_message->range->value + 10, 2);
	char clock_T_d[4];
	memset(clock_T_d, 0, 4);
	strncpy(clock_T_d, event->request_message->range->value + 12, 2);
	char clock_Z_h[4];
	memset(clock_Z_h, 0, 4);
	strncpy(clock_Z_h, event->request_message->range->value + 15, 2);
	char clock_Z_m[4];
	memset(clock_Z_m, 0, 4);
	strncpy(clock_Z_m, event->request_message->range->value + 17, 2);
	char clock_Z_s[4];
	memset(clock_Z_s, 0, 4);
	strncpy(clock_Z_s, event->request_message->range->value + 19, 2);

	time_t timep;    
    struct tm cur_time; 
    cur_time.tm_year = atoi(clock_T_y)-1900;
    cur_time.tm_mon  = atoi(clock_T_m)-1;
    cur_time.tm_mday = atoi(clock_T_d);
    cur_time.tm_hour = atoi(clock_Z_h);
    cur_time.tm_min  = atoi(clock_Z_m);
    cur_time.tm_sec  = atoi(clock_Z_s);
    timep = mktime(&cur_time);
    event->rtp_message->npt_time = (timep - event->rtp_message->clock_begintime)*25;
	sprintf(event->response_message->range->value,"%s", event->request_message->range->value);
}
void RtspMessageHeader::rtsp_message_header_range_handle_clock(rtsp_event_t* event)
{
	char clock_T[10];
	memset(clock_T, 0, 10);
	strncpy(clock_T, event->rtp_message->filename, 8);
	char clock_T_y[6];
	memset(clock_T_y, 0, 6);
	strncpy(clock_T_y, event->rtp_message->filename, 4);
	char clock_T_m[4];
	memset(clock_T_m, 0, 4);
	strncpy(clock_T_m, event->rtp_message->filename + 4, 2);
	char clock_T_d[4];
	memset(clock_T_d, 0, 4);
	strncpy(clock_T_d, event->rtp_message->filename + 6, 2);
	char clock_Z[10];
	memset(clock_Z, 0, 10);
	strncpy(clock_Z, event->rtp_message->filename + 8, 6);
	char clock_Z_h[4];
	memset(clock_Z_h, 0, 4);
	strncpy(clock_Z_h, event->rtp_message->filename + 8, 2);
	char clock_Z_m[4];
	memset(clock_Z_m, 0, 4);
	strncpy(clock_Z_m, event->rtp_message->filename + 10, 2);
	char clock_Z_s[4];
	memset(clock_Z_s, 0, 4);
	strncpy(clock_Z_s, event->rtp_message->filename + 12, 2);

	time_t timep;    
    struct tm begin_time; 
    begin_time.tm_year = atoi(clock_T_y)-1900;
    begin_time.tm_mon  = atoi(clock_T_m)-1;
    begin_time.tm_mday = atoi(clock_T_d);
    begin_time.tm_hour = atoi(clock_Z_h);
    begin_time.tm_min  = atoi(clock_Z_m);
    begin_time.tm_sec  = atoi(clock_Z_s);
    timep = mktime(&begin_time);
    event->rtp_message->clock_begintime = timep;
    timep = timep + event->rtp_message->record_time;
    struct tm *end_time;
    end_time = localtime(&timep);
    

	sprintf(event->response_message->range->value,"clock=%sT%sZ-%02d%02d%02dT%02d%02d%02dZ", clock_T, clock_Z, 
		    end_time->tm_year + 1900, end_time->tm_mon + 1, end_time->tm_mday, end_time->tm_hour, end_time->tm_min, end_time->tm_sec);
}