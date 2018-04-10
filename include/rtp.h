#ifndef _RTP_H_
#define _RTP_H_

#include "rtp_jrtp.h"
#include "rtsp_struct.h"
#include "rtp_memery.h"
#include "rtp_record_file.h"

static const int payload = 100;
#define MAX_RTP_PKT_LENGTH     1360
class RTPForRtsp: public RTPMemery, public RTPRecordFile
{
public:
    MyRTPSession session;
    rtp_nalu_header_t     *nalu_hdr;
    rtp_fu_indicator_t    *fu_ind;
    rtp_fu_header         *fu_hdr;
    rtp_nalu_t            *n;
    FILE *fp_record;
    char sendbuf[1400];
    char* nalu_payload;
    unsigned long ts_current;
    unsigned long ts_compare;
    int timestamp_increse;
    int fast_go_iframe_stat;
    int slow_go_iframe_stat;
    int fast_back_iframe_stat;
    int fast_back_frame_count;
    int slow_back_iframe_stat;
    int slow_back_frame_count;
    int fast_frame_count;
    int slow_frame_count;
    int  RTPSessionInit(rtsp_event_t* event);
    int  RTPSessionSend(rtsp_event_t* event);
    void RTPSessionClose();
    void RTPSessionCheckError(int rtperr);
    int  FileOPen (char *filename);
};
#endif