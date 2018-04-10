#include "rtp.h"
#include <math.h>
#include <unistd.h>
#include "rtsp_message_url.h"
int RTPForRtsp::RTPSessionInit(rtsp_event_t* event)
{
    cout<<event->rtp_message->client_ip<<endl;
    cout<<event->rtp_message->filename<<endl;
    cout<<event->rtp_message->server_ip<<endl;
    cout<<event->rtp_message->client_port<<endl;
    cout<<event->rtp_message->server_port<<endl;
	fp_record = NULL;
	session.sock_fd = event->sid;
    uint32_t destip;

    RTPSessionParams sessionparams;
    sessionparams.SetOwnTimestampUnit(1.0/90000.0);

    RTPUDPv4TransmissionParams transparams;

    transparams.SetPortbase(event->rtp_message->server_port);

    int status = session.Create(sessionparams,&transparams);
    RTPSessionCheckError(status);
    
    destip = inet_addr(event->rtp_message->client_ip);
    destip = ntohl(destip);

    RTPIPv4Address addr(destip, event->rtp_message->client_port);

    status = session.AddDestination(addr);
    RTPSessionCheckError(status);

    session.SetDefaultPayloadType(payload);
    session.SetDefaultMark(false);
    session.SetDefaultTimestampIncrement(90000.0 /25.0);

    
    memset(sendbuf, 0, 1400);
    timestamp_increse = 1;
    ts_current = 0;
    ts_compare = 0;
    fast_go_iframe_stat = 0;
    slow_go_iframe_stat = 0;
    fast_back_iframe_stat = 0;
    fast_back_frame_count = 0;
    slow_back_iframe_stat = 0;
    slow_back_frame_count = 0;
    fast_frame_count = 0;
    slow_frame_count = 0;
    n = RTPNaluCalloc(5000000);
    if(FileOPen(event->rtp_message->filename) != 0)
        return -1;
    
    return 0;
}
int RTPForRtsp::RTPSessionSend(rtsp_event_t* event)
{
  //  cout<<"RTPSessionSend"<<endl;
    unsigned long npt_time;
	RTPTime delay(0.040);
	int status = 0;
	unsigned long fp_goto_size = 0;;
    float goto_percent = 0.0;
	if(!feof(fp_record) && event->teardown == 0)
    {
        while(!feof(fp_record))
        {
        	//实现视频拖拽
            npt_time = event->rtp_message->npt_time;
            if(ts_compare != npt_time)//拖
            {
                ts_compare = npt_time;
                goto_percent = npt_time/15000.0;
                fp_goto_size = (event->rtp_message->filesize ) * goto_percent;
                cout<<"fp_goto_size"<<fp_goto_size<<endl;
                int flag_pose = 0;
                while(fp_goto_size > 100000)
                {
                    if(flag_pose == 0)
                    {
                        fseek(fp_record, 100000, SEEK_SET);
                        flag_pose = 1;
                    }
                    else
                        fseek(fp_record, 100000, SEEK_CUR);
                    fp_goto_size = fp_goto_size - 100000;
                }  
                if(flag_pose == 0)
                    fseek(fp_record, fp_goto_size, SEEK_SET);
                else if(flag_pose == 1)
                    fseek(fp_record, fp_goto_size, SEEK_CUR);
                continue;
            }
            else if(ts_compare == npt_time)
            {
                //处理快进、快退、慢进、慢退
                float scale = event->response_message->scale;
                if(event->scale_stat == 1)
                {
                	if(scale >= 1.0)//快进
                	{
                		if(RTPGetFrame(n, fp_record) != 0) return 2;
                        ts_compare = ts_compare + timestamp_increse;
                        event->rtp_message->npt_time = ts_compare;
                		if(n->fram_type == 0x65)
                            fast_go_iframe_stat = 1;
                        if(fast_go_iframe_stat == 1)
                        {
                            fast_go_iframe_stat = 0;
                            fast_frame_count = 0;
                            break;
                        }
                        else if(fast_go_iframe_stat == 0)
                        {
                            fast_frame_count++;
                            if(fast_frame_count <= (25/scale))
                                break;
                            else
                                continue;
                        }	
                	}	
                	else if(scale < 1.0)//慢进
                	{
                        if(slow_frame_count > (25/scale))
                        {
                            slow_frame_count = 0;
                            slow_go_iframe_stat = 0;
                        }
                        if(slow_go_iframe_stat == 1)
                        {
                            slow_frame_count ++;
                            if(scale < 0.3)
                                usleep(40000);
                            else if(scale < 0.5)
                                usleep(20000);
                            break;
                        }
                        slow_frame_count ++;
                		if(RTPGetFrame(n, fp_record) != 0) return 2;
                        ts_compare = ts_compare + timestamp_increse;
                        event->rtp_message->npt_time = ts_compare;
                        if(n->fram_type == 0x65)
                            slow_go_iframe_stat = 1;
                		break;
                	}	
                }
                else if(event->scale_stat == -1)
                {
                	if(scale <= -1.0)//快退
                	{
                		if(RTPGetFrame(n, fp_record) != 0) return 2;
                        ts_compare = ts_compare - timestamp_increse;
                        event->rtp_message->npt_time = ts_compare;
                		if(n->fram_type == 0x65)
                            fast_back_iframe_stat ++;
                        if(fast_back_iframe_stat == 2)
                        {
                            fast_back_iframe_stat = 0;
                            if(RTPGetFrameNegative(n, fp_record) != 0) return 2;
                            fast_back_frame_count = 0;
                            continue;
                        }
                        else
                        {
                            if(fast_back_iframe_stat == 1)
                                fast_back_frame_count ++;
                            if(fast_back_frame_count <= fabs(25/scale))
                                break;
                            else
                                continue;
                        }
                	}	
                	else if(scale > -1.0)//慢退
                	{
                        slow_back_frame_count ++;
                        if(slow_back_frame_count < fabs(25/scale) && slow_back_frame_count > 25)
                            break;
                        else if(slow_back_frame_count <= 25)
                        {
                            if(RTPGetFrame(n, fp_record) != 0) return 2;
                            ts_compare = ts_compare - timestamp_increse;
                            event->rtp_message->npt_time = ts_compare;
                            if(n->fram_type == 0x65)
                                slow_back_iframe_stat ++;
                            if(slow_back_iframe_stat == 2)
                            {
                                slow_back_iframe_stat = 0;
                                if(RTPGetFrameNegative(n, fp_record) != 0) return 2;
                                continue;
                            }
                            else
                                 break;
                        } 
                        else if(slow_back_frame_count > fabs(25/scale))   
                            slow_back_frame_count = 0;
                	}	
                }
                else
                	if(RTPGetFrame(n, fp_record) != 0) return 2;
                break;
            }
        }
        ts_current = ts_current + timestamp_increse;
        event->rtp_message->cur_timestamp = ts_current;
        if(n->len<=MAX_RTP_PKT_LENGTH)
        {
            nalu_hdr =(rtp_nalu_header_t*)&sendbuf[0]; 
            nalu_hdr->F=n->forbidden_bit;
            nalu_hdr->NRI=n->nal_reference_idc>>5;
            nalu_hdr->TYPE=n->nal_unit_type;
            nalu_payload=&sendbuf[1];
            memcpy(nalu_payload,n->buf+1,n->len-1);
            

            if(n->nal_unit_type==1 || n->nal_unit_type==5)
            {
                status = session.SendPacket((void *)sendbuf,n->len,payload,true,3600);
            }
            else
            {
                    status = session.SendPacket((void *)sendbuf,n->len,payload,true,0);
                    return 0;
            }
            if (status < 0)
            {
                std::cerr << RTPGetErrorString(status) << std::endl;
                exit(1);
            }
        }
        else if(n->len>MAX_RTP_PKT_LENGTH)
        {
            int k=0,l=0;
            k=n->len/MAX_RTP_PKT_LENGTH;
            l=n->len%MAX_RTP_PKT_LENGTH;
            int t=0;
            while(t<=k)
            {
                if(!t)
                {
                    memset(sendbuf,0,1400);
                    fu_ind =(rtp_fu_indicator_t*)&sendbuf[0];
                    fu_ind->F=n->forbidden_bit;
                    fu_ind->NRI=n->nal_reference_idc>>5;
                    fu_ind->TYPE=28;
                    fu_hdr =(rtp_fu_header_t*)&sendbuf[1];
                    fu_hdr->E=0;
                    fu_hdr->R=0;
                    fu_hdr->S=1;
                    fu_hdr->TYPE=n->nal_unit_type;
                    nalu_payload=&sendbuf[2];
                    memcpy(nalu_payload,n->buf+1,MAX_RTP_PKT_LENGTH);
                    status = session.SendPacket((void *)sendbuf,MAX_RTP_PKT_LENGTH+2,payload,false,0);
                    if (status < 0)
                    {
                        std::cerr << RTPGetErrorString(status) << std::endl;
                        exit(1);
                    }
                    t++;
                }   
                else if(k==t)
                {
                    memset(sendbuf,0,1400);
                    fu_ind =(rtp_fu_indicator_t*)&sendbuf[0];
                    fu_ind->F=n->forbidden_bit;
                    fu_ind->NRI=n->nal_reference_idc>>5;
                    fu_ind->TYPE=28;

                    fu_hdr =(rtp_fu_header_t*)&sendbuf[1];
                    fu_hdr->R=0;
                    fu_hdr->S=0;
                    fu_hdr->TYPE=n->nal_unit_type;
                    fu_hdr->E=1;
                    nalu_payload=&sendbuf[2];
                    memcpy(nalu_payload,n->buf+t*MAX_RTP_PKT_LENGTH+1,l-1);

                    status = session.SendPacket((void *)sendbuf,l+1,payload,true,3600);
                    if (status < 0)
                    {
                        std::cerr << RTPGetErrorString(status) << std::endl;
                        exit(-1);
                    }
                    t++;
                }
                else if(t<k&&0!=t)
                {
                    memset(sendbuf,0,1400);
                    fu_ind =(rtp_fu_indicator_t*)&sendbuf[0]; 
                    fu_ind->F=n->forbidden_bit;
                    fu_ind->NRI=n->nal_reference_idc>>5;
                    fu_ind->TYPE=28;
                    fu_hdr =(rtp_fu_header_t*)&sendbuf[1];
                    fu_hdr->R=0;
                    fu_hdr->S=0;
                    fu_hdr->E=0;
                    fu_hdr->TYPE=n->nal_unit_type;

                    nalu_payload=&sendbuf[2];
                    memcpy(nalu_payload,n->buf+t*MAX_RTP_PKT_LENGTH+1,MAX_RTP_PKT_LENGTH);
                    status = session.SendPacket((void *)sendbuf,MAX_RTP_PKT_LENGTH+2,payload,false,0);
                    if (status < 0)
                    {
                        std::cerr << RTPGetErrorString(status) << std::endl;
                        exit(1);
                    }
                    t++;
                }
            }
        }
        RTPTime::Wait(delay); 
    }
    else
        return 2;
    return 0;
}
void RTPForRtsp::RTPSessionClose()
{
    cout<<"RTPSessionClose start"<<endl;
	if(fp_record != NULL)
	    fclose(fp_record);
    session.Destroy();
    RTPNaluFree(n);
    cout<<"RTPSessionClose"<<endl;
}
void RTPForRtsp::RTPSessionCheckError(int rtperr)
{
    if (rtperr < 0)
    {
        std::cout << "ERROR: " << RTPGetErrorString(rtperr) << std::endl;
        exit(1);
    }
}
int RTPForRtsp::FileOPen (char *filename)
{
    char *filepath = (char*)calloc (100, sizeof (char));
    snprintf(filepath, 100, "/%s/%s", g_filepath, filename);
    if (NULL == (fp_record=fopen(filepath, "rb")))
    {
        free(filepath);
        return -1;
    }
    free(filepath);
    return 0;
}