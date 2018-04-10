#ifndef _RTP_STRUCT_H_
#define _RTP_STRUCT_H_

typedef struct rtp_nalu_header rtp_nalu_header_t;
struct rtp_nalu_header
{
	unsigned char TYPE:5;
    unsigned char NRI:2;
	unsigned char F:1;
};

typedef struct rtp_fu_indicator rtp_fu_indicator_t;
struct rtp_fu_indicator
{
	unsigned char TYPE:5;
    unsigned char NRI:2;
	unsigned char F:1;
};

typedef struct rtp_fu_header rtp_fu_header_t;
struct rtp_fu_header
{
	unsigned char TYPE:5;
	unsigned char R:1;
	unsigned char E:1;
	unsigned char S:1;
};

typedef struct rtp_nalu rtp_nalu_t;
struct rtp_nalu
{
	int startcodeprefix_len;      
    unsigned len;                 
    unsigned max_size;            
    int forbidden_bit;           
    int nal_reference_idc;       
    int nal_unit_type;            
    unsigned char *buf;     
    unsigned char fram_type;             
    unsigned short lost_packets;  
};
#endif