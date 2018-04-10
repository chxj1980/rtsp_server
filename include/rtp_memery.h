#ifndef _RTP_MEMERY_H_
#define _RTP_MEMERY_H_
#include "rtp_struct.h"
class RTPMemery
{
public:
	rtp_nalu_t* RTPNaluCalloc(int size);
	void RTPNaluFree(rtp_nalu_t* n);
};


#endif