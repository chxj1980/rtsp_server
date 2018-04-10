#ifndef _RTSP_MESSAGE_URL_H_
#define _RTSP_MESSAGE_URL_H_
#include "rtsp_struct.h"
#include "rtp_record_file.h"

extern char  g_filepath[100];

class RtspMessageUrl: public RTPRecordFile
{
public:
	STATUSCODE rtsp_message_url_check(rtsp_event_t* event);
	STATUSCODE rtsp_message_url_check_file(rtp_message_t* rtp_message);
	unsigned long get_file_size(char *path);
};


#endif