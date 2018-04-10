#ifndef _RTSP_MESSAGE_PARSE_H_
#define _RTSP_MESSAGE_PARSE_H_
#include "rtsp_memery.h"
#include "rtsp_message_header.h"
#include "rtsp_message_url.h"



#define MESSAGE_IS_OPTION          1
#define MESSAGE_IS_DESCRIBE        2
#define MESSAGE_IS_ANNOUNCE        3
#define MESSAGE_IS_SETUP           4
#define MESSAGE_IS_PLAY            5
#define MESSAGE_IS_PAUSE           6
#define MESSAGE_IS_TEARDOWN        7
#define MESSAGE_IS_GET_PARAMETER   8
#define MESSAGE_IS_SET_PARAMETER   9
#define MESSAGE_IS_REDIRECT        10
#define MESSAGE_IS_RECORD          11

class RtspMessageParse : public RtspMessageUrl, public RtspMessageHeader
{

public:
	STATUSCODE rtsp_request_message_parse_option(rtsp_request_message_t* request_message);
	STATUSCODE rtsp_request_message_parse_describe(rtsp_event_t* event);
	STATUSCODE rtsp_request_message_parse_setup(rtsp_event_t* event);
	STATUSCODE rtsp_request_message_parse_play(rtsp_event_t* event);
	STATUSCODE rtsp_request_message_parse_record(rtsp_event_t* event);
	STATUSCODE rtsp_request_message_parse_pause(rtsp_request_message_t* request_message, rtsp_response_message_t* response_message);
	STATUSCODE rtsp_request_message_parse_get_parameter(void);
	STATUSCODE rtsp_request_message_parse_teardown(void);


	int rtsp_build_response_message_option(char *send_buff, rtsp_response_message_t* response_message);
	int rtsp_build_response_message_describe(char *send_buff, rtsp_response_message_t* response_message);
	int rtsp_build_response_message_setup(char *send_buff, rtsp_event_t* event);
    int rtsp_build_response_message_play(char *send_buff, rtsp_event_t* event);
    int rtsp_build_response_message_pause(char *send_buff, rtsp_event_t* event);
    int rtsp_build_response_message_record(char *send_buff, rtsp_event_t* event);
    int rtsp_build_response_message_get_parameter(char *send_buff, rtsp_event_t* event);
    int rtsp_build_response_message_teardown(char *send_buff, rtsp_event_t* event);



	int rtsp_build_response_message_error(char *send_buff, int cseq, int response_status_code);

	int rtsp_get_server_ip(rtp_message_t* rtp_message);
};


#endif