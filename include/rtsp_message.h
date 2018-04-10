#ifndef _RTSP_MESSAGE_H_
#define _RTSP_MESSAGE_H_
#include "rtsp_message_parse.h"


using namespace std;


class RtspMessageHandle: public RtspMemeryHandle, public RtspMessageParse
{
public:
	int rtsp_request_message_init(char* recv_buff, rtsp_request_message_t* request_message);
	int rtsp_response_message_init(char* recv_buff, rtsp_response_message_t* response_message);

	METHODTYPE rtsp_request_message_get_method(rtsp_request_message_t* request_message);
	STATUSCODE rtsp_request_message_handle(rtsp_event_t* event);

	int rtsp_build_request_message(char *send_buff, rtsp_request_message_t* request_message, int cseq);
	int rtsp_build_response_message(char *send_buff, rtsp_event_t* event, int response_status_code);
};


#endif