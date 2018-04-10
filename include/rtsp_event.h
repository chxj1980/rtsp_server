#ifndef _RTSP_EVENT_H_
#define _RTSP_EVENT_H_
#include "rtsp_message.h"


using namespace std;


class RtspEventHandle: public RtspMessageHandle
{
public:
	rtsp_event_t* rtsp_event_init(int fd);
	int rtsp_event_handle(char* recv_buff, char* send_buff, rtsp_event_t* event, const char *client_ip);
	int rtsp_event_free(rtsp_event_t* event);
};


#endif