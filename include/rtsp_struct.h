#ifndef _RTSP_STRUCT_H_
#define _RTSP_STRUCT_H_

typedef int STATUSCODE; 
typedef int METHODTYPE;


typedef struct rtp_message_s rtp_message_t;
struct rtp_message_s
{
	char* client_ip;
	char* server_ip;
	int   client_port;
	int   server_port;
	char* filename;
	float record_time;
	int   npt_or_clock;
	unsigned long  cur_timestamp;
	unsigned long  npt_time;
	unsigned long  clock_begintime;
	unsigned long  filesize;
};

typedef struct rtsp_header rtsp_header_t;
struct rtsp_header
{
	char* name;
	char* value;
};

typedef struct rtsp_request_message rtsp_request_message_t;
struct rtsp_request_message
{
	//request-line
	char* method;
	char* url;
	char* version;

	int cseq;
	//other
	int band_width;
	int block_size;
	rtsp_header_t* conference;
	rtsp_header_t* require;
	
	float scale;
	float speed;
	rtsp_header_t* session;
	rtsp_header_t* timestamp;
	rtsp_header_t* transport;
	
    //general-header
	rtsp_header_t* cache_control;
	rtsp_header_t* connection;
	rtsp_header_t* date;
	rtsp_header_t* via;
    //request-header
	rtsp_header_t* user_agent;
	rtsp_header_t* accept;
	rtsp_header_t* accept_encoding;
	rtsp_header_t* accept_language;
	rtsp_header_t* from;
	rtsp_header_t* range;
	rtsp_header_t* referer;
	rtsp_header_t* if_modified_since;
	rtsp_header_t* authorization;
	// entity-header
    rtsp_header_t* allow;
	rtsp_header_t* content_base;
	rtsp_header_t* content_encoding;
	rtsp_header_t* content_language;
	int content_length;
	rtsp_header_t* content_location;
	rtsp_header_t* content_type;
	int expires;
	rtsp_header_t* last_modified;
	//message-body
	char* body;	
};
typedef struct rtsp_response_message rtsp_response_message_t;
struct rtsp_response_message
{
	//status-line
	char* version;
	int   status_code;
	char* reason;
    int   cseq;
    char* url;
    //other
    rtsp_header_t* timestamp;
    rtsp_header_t* session;
    float scale;
    rtsp_header_t* rtp_info;
    rtsp_header_t* unsupported;
    float speed;
    rtsp_header_t* transport;
	//general-header
    rtsp_header_t* cache_control;
	rtsp_header_t* connection;
	rtsp_header_t* date;
	rtsp_header_t* via;
	//response-header
	rtsp_header_t* location;
	rtsp_header_t* proxy_authenticate;
	rtsp_header_t* _public;
	rtsp_header_t* retry_after;
	rtsp_header_t* range;
	rtsp_header_t* server;
	rtsp_header_t* vary;
	rtsp_header_t* www_authenticate;
	// entity-header
    rtsp_header_t* allow;
	rtsp_header_t* content_base;
	rtsp_header_t* content_encoding;
	rtsp_header_t* content_language;
	int content_length;
	rtsp_header_t* content_location;
	rtsp_header_t* content_type;
	int expires;
	rtsp_header_t* last_modified;
	//message-body	
	char* body;	
};
typedef struct rtsp_event rtsp_event_t;
struct rtsp_event
{
	int   type;
	int   sid;//session id,socket fd
	int   cseq;
	int   play;
	int   pause;
	int   teardown;
	int   trackID;
	int   scale_stat;
	rtsp_request_message_t*  request_message;
	rtsp_response_message_t* response_message;
	rtp_message_t* rtp_message;
};
#endif