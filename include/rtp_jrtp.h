#ifndef _RTP_JRTP_H_
#define _RTP_JRTP_H_
#include "rtpsession.h"
#include "rtpsessionparams.h"
#include "rtpudpv4transmitter.h"
#include "rtpipv4address.h"
#include "rtptimeutilities.h"
#include "rtppacket.h"
#include "rtcppacket.h"
#include "rtcpsrpacket.h"
#include "rtcpcompoundpacket.h"
#include "rtcpsrpacket.h"
#include "rtcprrpacket.h"
#include "rtcpbyepacket.h"
#include "rtprawpacket.h"
#include <iostream>
using namespace std;
using namespace jrtplib;
class MyRTPSession : public RTPSession
{
public:
    MyRTPSession()
    {
        SetChangeIncomingData(true);
        flag_RR  = 0;  
        map_count = 0;
    }

    ~MyRTPSession()
    {
    }
    int sock_fd;
    int flag_RR;
    int map_count;
protected:
    void OnValidatedRTPPacket(RTPSourceData *srcdat, RTPPacket *rtppack, bool isonprobation, bool *ispackethandled);
    void OnRTCPCompoundPacket(RTCPCompoundPacket *p, const RTPTime &receivetime, const RTPAddress *senderaddress);
    void DumpCompoundPacket(FILE *f, RTCPCompoundPacket *p);    
};

#endif