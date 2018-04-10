#ifndef _RTP_RECORD_FILE_H_
#define _RTP_RECORD_FILE_H_
#include "rtp_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>


class RTPRecordFile
{
public:
	int RTPGetFrame(rtp_nalu_t *nalu, FILE *fp);
    int RTPGetFrameNegative(rtp_nalu_t *nalu, FILE *fp);
	int GetFramNum(char* filepath);
	int FindStartCode2 (unsigned char *Buf);
	int FindStartCode3 (unsigned char *Buf);
};

#endif