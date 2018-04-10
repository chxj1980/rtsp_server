#ifndef _RTSP_MESSAGE_HEADER_H_
#define _RTSP_MESSAGE_HEADER_H_
#include "rtsp_struct.h"



class RtspMessageHeader
{
public:
	STATUSCODE rtsp_message_header_get_client_port(rtsp_header_t* transport_header, rtp_message_t* rtp_message);
	STATUSCODE rtsp_message_header_range_handle(rtsp_event_t* event);
	void rtsp_message_header_range_handle_clock(rtsp_event_t* event);
	void rtsp_message_header_range_handle_clock_pause(rtsp_event_t* event);
	void rtsp_message_header_range_handle_clock_goto(rtsp_event_t* event);
	unsigned long int rtsp_message_header_range_get_begintime(char *range_value);
};


#endif