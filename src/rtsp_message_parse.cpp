#include "rtsp_message_parse.h"

#include <iostream>
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h> 
#include <sqlite.h>
STATUSCODE RtspMessageParse::rtsp_request_message_parse_option(rtsp_request_message_t* request_message)
{
	return 200;
}
STATUSCODE RtspMessageParse::rtsp_request_message_parse_describe(rtsp_event_t* event)
{
  STATUSCODE res = rtsp_message_url_check(event);
  if(res != 200)
    return res;
	return 200;
}
STATUSCODE RtspMessageParse::rtsp_request_message_parse_setup(rtsp_event_t* event)
{
	STATUSCODE res;
	res = rtsp_message_header_get_client_port(event->request_message->transport, event->rtp_message);
	if(res != 200)
		return res;
	return 200;
}
STATUSCODE RtspMessageParse::rtsp_request_message_parse_play(rtsp_event_t* event)
{
	STATUSCODE res = rtsp_message_header_range_handle(event);
	if(res != 200)
		return res;
	return 200;
}
STATUSCODE RtspMessageParse::rtsp_request_message_parse_record(rtsp_event_t* event)
{
	return 200;
}
STATUSCODE RtspMessageParse::rtsp_request_message_parse_pause(rtsp_request_message_t* request_message, 
                                                            rtsp_response_message_t* response_message)
{
	return 200;
}
STATUSCODE RtspMessageParse::rtsp_request_message_parse_get_parameter(void)
{
	return 200;
}
STATUSCODE RtspMessageParse::rtsp_request_message_parse_teardown(void)
{
	return 200;
}
int RtspMessageParse::rtsp_build_response_message_option(char *send_buff, rtsp_response_message_t* response_message)
{
	sprintf(send_buff, "RTSP/1.0 200 OK\r\n"
			           "CSeq: %d\r\n"
                       "Server: GE730-RTSP-SERVER\r\n"
                       "Public: DESCRIBE, SETUP, TEARDOWN, PLAY, GET_PARAMETER, OPTIONS, PAUSE, RECORD, ANNOUNCE\r\n\r\n"
                       ,response_message->cseq);
	return 0;
}
int RtspMessageParse::rtsp_build_response_message_describe(char *send_buff, rtsp_response_message_t* response_message)
{
	sprintf(response_message->body, "v=0\r\n"
			         "o=- 1234 1234 IN 192.168.0.106\r\n"
			         "s=- \r\n"
			         "t= 0 0\r\n"
			         "m=video 0 RTP/AVP 100\r\n"
                     "c=IN IP4 0.0.0.0\r\n"
                     "a=rtpmap:100 H264/90000\r\n"
                     "a=fmtp:100 "
                     "profile-level-id=420029; packetization-mode=1; "
                     "sprop-parameter-sets=Z01AHppkBYCT/NQUFBUAAAMD6AAAw1AE,aO48gA==\r\n");
	int length = strlen(response_message->body);
	sprintf(send_buff, "RTSP/1.0 200 OK\r\n"
	                   "CSeq: %d\r\n"
                       "Server: GE730-RTSP-SERVER\r\n"
                       "Content-Base: \r\n"
                       "Content-Type: application/SDP\r\n"
                       "Content-Length: %d\r\n\r\n"
                       "%s"
                       ,response_message->cseq, length, response_message->body);
	return 0;
}
int RtspMessageParse::rtsp_build_response_message_setup(char *send_buff, rtsp_event_t* event)
{
	rtsp_response_message_t* response_message = event->response_message;
	rtp_message_t* rtp_message = event->rtp_message;
	rtsp_get_server_ip(event->rtp_message);
	sprintf(send_buff, "RTSP/1.0 200 OK\r\n"
			           "CSeq: %d\r\n"
                       "Cache-Control: no-cache\r\n"
                       "Transport: RTP/AVP;unicast;mode=play;destination=%s;client_port=%d-%d;source=%s;server_port=%d-%d\r\n"
                       "Session: AA00BB11%d \r\n\r\n"
                       ,response_message->cseq, rtp_message->client_ip, rtp_message->client_port, rtp_message->client_port+1
                       ,rtp_message->server_ip, rtp_message->server_port, rtp_message->server_port+1, event->sid);
	return 0;
}
int RtspMessageParse::rtsp_build_response_message_play(char *send_buff, rtsp_event_t* event)
{
	rtsp_response_message_t* response_message = event->response_message;
	if(event->scale_stat == 0)
        sprintf(send_buff, "RTSP/1.0 200 OK\r\n"
        		           "CSeq: %d\r\n"
                           "Session: AA00BB11%d\r\n"
                           "Range: %s\r\n"
                           "RTP-Info: url=%s/trackID=%d;seq=%lu;rtptime=%lu\r\n\r\n"
                           , response_message->cseq, event->sid, response_message->range->value, event->response_message->url
                           , event->trackID, event->rtp_message->cur_timestamp, event->rtp_message->cur_timestamp);
    else if(event->scale_stat == 1 || event->scale_stat == -1)
    	sprintf(send_buff, "RTSP/1.0 200 OK\r\n"
        		           "CSeq: %d\r\n"
                           "Session: AA00BB11%d\r\n"
                           "Range: %s\r\n"
                           "Scale: %f\r\n"
                           "RTP-Info: url=%s/trackID=%d;seq=%lu;rtptime=%lu\r\n\r\n"
                           , response_message->cseq, event->sid, response_message->range->value, response_message->scale, event->response_message->url
                           , event->trackID, event->rtp_message->cur_timestamp, event->rtp_message->cur_timestamp);
	return 0;
}
int RtspMessageParse::rtsp_build_response_message_record(char *send_buff, rtsp_event_t* event)
{
	sprintf(send_buff, "RTSP/1.0 200 OK\r\n"
			           "CSeq: %d\r\n"
                       "Session: AA00BB11%d\r\n\r\n"
                       ,event->response_message->cseq, event->sid);
	return 0;
}
int RtspMessageParse::rtsp_build_response_message_pause(char *send_buff, rtsp_event_t* event)
{
	sprintf(send_buff, "RTSP/1.0 200 OK\r\n"
			           "CSeq: %d\r\n"
                       "Session: AA00BB11%d\r\n\r\n"
                       ,event->response_message->cseq, event->sid);
	return 0;
}
int RtspMessageParse::rtsp_build_response_message_get_parameter(char *send_buff, rtsp_event_t* event)
{
	if(event->scale_stat == 0)
        sprintf(send_buff, "RTSP/1.0 200 OK\r\n"
        		           "CSeq: %d\r\n"
                           "Session: AA00BB11%d\r\n\r\n"
                           , event->response_message->cseq, event->sid);
    else if(event->scale_stat == 1 || event->scale_stat == -1)
    	sprintf(send_buff, "RTSP/1.0 200 OK\r\n"
        		           "CSeq: %d\r\n"
                           "Session: AA00BB11%d\r\n"
                           "Scale: %f\r\n\r\n"
                           , event->response_message->cseq, event->sid, event->response_message->scale);
	return 0;
}
int RtspMessageParse::rtsp_build_response_message_teardown(char *send_buff, rtsp_event_t* event)
{
	sprintf(send_buff, "RTSP/1.0 200 OK\r\n"
			           "CSeq: %d\r\n"
                       "Session: AA00BB11%d\r\n\r\n"
                       , event->response_message->cseq, event->sid);
	return 0;
}
int RtspMessageParse::rtsp_get_server_ip(rtp_message_t* rtp_message)
{
	int count = 0;
  sqlite *_db;
  char **data;
  int res;
  int row = 0;
  int col = 0;
  char *err = 0;
  do
  {
    count ++;
    if(count == 10)
    {
        return -1;
    }  
    _db = sqlite_open("/opt/app/dat/nrx.db", 2, &err);
  }while(!_db);
  res = sqlite_get_table(_db,"select mip from inf",&data,&row,&col,&err);
  if( res != SQLITE_OK )
  {
    sqlite_close(_db);
    return -1;
  }
  if(row != 0)
      strcpy( rtp_message->server_ip, data[1]);
  sqlite_free_table(data);
  sqlite_close(_db);   
	return 0;
}
int RtspMessageParse::rtsp_build_response_message_error(char *send_buff, int cseq, int response_status_code)
{
	switch(response_status_code)
	{
		case 400:
		sprintf(send_buff, "RTSP/1.0 400 WRONG_REQUEST_TYPE\r\n"
			               "CSeq: %d\r\n"
                           "Server: GE730-RTSP-SERVER\r\n"
                           ,cseq);
		break;
		case 404:
		sprintf(send_buff, "RTSP/1.0 404 FILE_NOT_EXIST\r\n"
			               "CSeq: %d\r\n"
                           "Server: GE730-RTSP-SERVER\r\n"
                           ,cseq);
		break;
		case 405:
		sprintf(send_buff, "RTSP/1.0 405 UNSUPPORTED_METHOD\r\n"
			               "CSeq: %d\r\n"
                           "Server: GE730-RTSP-SERVER\r\n"
                           ,cseq);
		break;
		case 461:
		sprintf(send_buff, "RTSP/1.0 461 UNSUPPORTED_RTP\r\n"
			               "CSeq: %d\r\n"
                           "Server: GE730-RTSP-SERVER\r\n"
                           ,cseq);
		break;
		default: ;break;
	}
	return 0;
}