#ifndef _RTSP_MEMERY_H_
#define _RTSP_MEMERY_H_

#include "rtsp_struct.h"
using namespace std;

#define NAME_SIZE               30
#define METHOD_SIZE             15
#define VERSION_SIZE            10
#define URL_SIZE                200
#define REASON_SIZE             80

#define CONFERENCE_SIZE         80
#define REQUIRE_SIZE            80
#define RTP_INFO_SIZE           300
#define SESSION_SIZE            30
#define TIMESTAMP_SIZE          80
#define TRANSPORT_SIZE          300
#define UNSUPPORTED_SIZE        80

#define CACHE_CONTROL_SIZE      30
#define CONNECTION_SIZE         50
#define DATE_SIZE               80
#define VIA_SIZE                80

#define USER_AGENT_SIZE         80
#define ACCEPPT_SIZE            80
#define ACCEPPT_ENCODING_SIZE   80
#define ACCEPPT_LANGUAGE_SIZE   80
#define FROM_SIZE               80
#define RANGE_SIZE              80
#define REFERER_SIZE            80
#define IF_MODIFIED_SINCE_SIZE  80
#define AUTHORIZATION_SIZE      80

#define LOCATION_SIZE           80
#define PROXY_AUTHENTICATE_SIZE 80
#define _PUBLIC_SIZE            80
#define RETRY_AFTER_SIZE        80
#define SERVER_SIZE             80
#define VARY_SIZE               80
#define WWW_AUTHENTICATE_SIZE   80

#define ALLOW_SIZE              80
#define CONTENT_BASE_SIZE       80
#define CONTENT_ENCODING_SIZE   80
#define CONTENT_LANGUAGE_SIZE   80
#define CONTENT_LOCATION_SIZE   80
#define CONTENT_TYPE_SIZE       80
#define LAST_MODIFIED_SIZE      80

#define BODY_SIZE               4096

#define CLIENT_IP_SIZE          20
#define FILENAME_SIZE           20


class RtspMemeryHandle
{
public:
	rtsp_event_t* rtsp_event_mem_calloc();
	int rtsp_event_mem_free(rtsp_event_t* _event);
    
    int rtp_message_mem_calloc(rtp_message_t* _rtp_message);
    int rtp_message_mem_free(rtp_message_t* _rtp_message);
	
	int rtsp_request_message_mem_calloc(rtsp_request_message_t* _request_message);
	int rtsp_request_message_mem_free(rtsp_request_message_t* _request_message);
	
	
	int rtsp_response_message_mem_calloc(rtsp_response_message_t* _response_message);
	int rtsp_response_message_mem_free(rtsp_response_message_t* _response_message);

	int rtsp_header_mem_calloc(rtsp_header_t* _header, int value_size);
	int rtsp_header_mem_free(rtsp_header_t* _header);

};

#endif