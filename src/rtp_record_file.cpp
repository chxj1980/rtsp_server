#include "rtp_record_file.h"
#include <iostream>
#include <math.h>
using namespace std;
int RTPRecordFile::RTPGetFrameNegative(rtp_nalu_t *nalu, FILE *fp)
{
    int info3 = 0;
    int flag = 0;
    int iframe_count = 0;
    unsigned char *Buf;
    Buf = (unsigned char*)calloc (20 , sizeof(char));
    fseek (fp, -6, SEEK_CUR);
    if(ftell(fp) == 0)
    {
        if(Buf)
            free(Buf);
        return -1;
    }
    fread (Buf, 1, 4, fp);
    while(1)
    {
        info3 = FindStartCode3(Buf);
        if(info3 == 1)
        {
           flag = 1;
        }
        fread (Buf, 1, 1, fp);
        if(ftell(fp) == 0)
        {
            if(Buf)
                free(Buf);
            return -1;
        }
        if(flag == 1 && Buf[0] == 0x65)
        {
            iframe_count++;
        }
        flag = 0;
        if(iframe_count == 3)
        {
            fseek (fp, -5, SEEK_CUR);
            break;
        }
        fseek (fp, -6, SEEK_CUR); 
        fread (Buf, 1, 4, fp);
    }
    if(Buf)
        free(Buf);
    return 0;
}
int RTPRecordFile::RTPGetFrame(rtp_nalu_t *nalu, FILE *fp)
{
    int info3 = 0;
    int pos = 4;
    int begin_pos = 0;
    int end_pos = 0;
    unsigned char *Buf;
    Buf = (unsigned char*)calloc (20 , sizeof(char));
    unsigned char *Buf1;
    Buf1 = (unsigned char*)calloc (20 , sizeof(char));
    fread (Buf, 1, 4, fp);
    if(feof(fp))
    {
        if(Buf)
            free(Buf);
        if(Buf1)
            free(Buf1);
        return -1;
    }
    while(end_pos == 0)
    {
        info3 = FindStartCode3(Buf);
        if(info3 == 1 && begin_pos == 0)
        {
            begin_pos = pos;
        }
        else if(info3 == 1 && begin_pos != 0)
        {
            end_pos = pos;
            break;
        }
        Buf[0] = Buf[1];
        Buf[1] = Buf[2];
        Buf[2] = Buf[3];
        fread (Buf1, 1, 1, fp);
        if(feof(fp))
        {
            if(Buf)
                free(Buf);
            if(Buf1)
                free(Buf1);
            return -1;
        }
        Buf[3] = Buf1[0];
        pos ++;
    }
    nalu->len = end_pos - begin_pos - 4;
    fseek (fp, begin_pos - end_pos, SEEK_CUR);
    fread (nalu->buf, 1, nalu->len, fp);
    nalu->forbidden_bit = nalu->buf[0] & 0x80; 
    nalu->nal_reference_idc = nalu->buf[0] & 0x60; 
    nalu->nal_unit_type = (nalu->buf[0]) & 0x1f;
    nalu->fram_type = nalu->buf[0];
    if(Buf)
        free(Buf);
    if(Buf1)
        free(Buf1); 
    return 0;
}
int RTPRecordFile::GetFramNum(char* filepath)
{
    FILE *fp;
    int info3 = 0;
    int frame_count = 0;
    unsigned char *Buf;
    Buf = (unsigned char*)calloc (20 , sizeof(char));
    unsigned char *Buf1;
    Buf1 = (unsigned char*)calloc (20 , sizeof(char));
    memset(Buf, 0, 20);
    memset(Buf1, 0, 20);
    if (NULL == (fp=fopen(filepath, "rb")))
    {
        cout<<"open filename failed:"<<filepath<<endl;
        return -1;
    }
    int flag = 0;
    int i_fram = 0;
    fread (Buf, 1, 4, fp);
    while(!feof(fp))
    {
        info3 = FindStartCode3(Buf);
        if(info3 == 1)
        {
            flag = 1;
            frame_count++;  
        }
        Buf[0] = Buf[1];
        Buf[1] = Buf[2];
        Buf[2] = Buf[3];
        fread (Buf1, 1, 1, fp);
        Buf[3] = Buf1[0];
        if(flag == 1)
        {
            flag = 0;
            if((Buf[3])== 0x65)
              i_fram++;
        }
    }
    cout<<"frame_count is :"<<frame_count<<endl;
    cout<<"i_fram is :"<<i_fram<<endl;
    if(Buf)
        free(Buf);
    if(Buf1)
        free(Buf1);
    if(fp != NULL)
        fclose(fp);
    return frame_count;
}
int RTPRecordFile::FindStartCode2 (unsigned char *Buf)
{
    if(Buf[0]!=0 || Buf[1]!=0 || Buf[2] !=1) 
        return 0; 
    else 
        return 1;
}

int RTPRecordFile::FindStartCode3 (unsigned char *Buf)
{
    if(Buf[0]!=0 || Buf[1]!=0 || Buf[2] !=0 || Buf[3] !=1) 
        return 0;
    else 
        return 1;
}
