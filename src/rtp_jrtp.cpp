#include "rtp_jrtp.h"

void MyRTPSession::OnValidatedRTPPacket(RTPSourceData *srcdat, RTPPacket *rtppack, bool isonprobation, bool *ispackethandled)
{
    DeletePacket(rtppack);
    *ispackethandled = true;
}
void MyRTPSession::OnRTCPCompoundPacket(RTCPCompoundPacket *p, const RTPTime &receivetime, const RTPAddress *senderaddress)
{   
    printf("%u.%06u RECEIVED\n",receivetime.GetSeconds(),receivetime.GetMicroSeconds());
    
    DumpCompoundPacket(stdout,p);
}
void MyRTPSession::DumpCompoundPacket(FILE *f, RTCPCompoundPacket *p)
{
    RTCPPacket *pack;

    p->GotoFirstPacket();
    flag_RR  = 0;
    while ((pack = p->GetNextPacket()) != 0)
    {
        if (pack->GetPacketType() == RTCPPacket::RR)
        {
            fprintf(f,"SOCKED_FD %d: GET RR success\n", sock_fd);
            flag_RR = 1;
            break;
        }
    }
    if(flag_RR == 1)
        map_count = 0;
}