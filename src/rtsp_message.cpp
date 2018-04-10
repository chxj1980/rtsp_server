#include "rtsp_message.h"
#include <malloc.h>  
#include <iostream>
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h> 


int RtspMessageHandle::rtsp_request_message_init(char* recv_buff, rtsp_request_message_t* request_message)
{
	char *ptr = strchr(recv_buff,' ');
	int length = ptr - recv_buff;
	memset(request_message->method,0,METHOD_SIZE);
	strncpy(request_message->method, recv_buff, length);
	char *ptr1 = strchr(ptr+1,' ');
	length = ptr1 - ptr;
	memset(request_message->url,0,URL_SIZE);
	strncpy(request_message->url, ptr+1, length-1);
	char *ptr2 = strchr(ptr1,'\r');
	length = ptr2 - ptr1;
	memset(request_message->version,0,VERSION_SIZE); 
	strncpy(request_message->version, ptr1+1, length-1);
	//cseq
	ptr = strstr(recv_buff,"CSeq");
	char tmp[20];
	memset(tmp,0,20);
    if(ptr != NULL)
    {
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(tmp, ptr1+1, length-1);
    	request_message->cseq = atoi(tmp);	
    }
    //Bandwidth
	ptr = strstr(recv_buff,"Bandwidth");
	memset(tmp,0,20);
    if(ptr != NULL)
    {
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(tmp, ptr1+1, length-1);
    	request_message->band_width = atoi(tmp);	
    }
    //Blocksize
	ptr = strstr(recv_buff,"Blocksize");
	memset(tmp,0,20);
    if(ptr != NULL)
    {
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(tmp, ptr1+1, length-1);
    	request_message->block_size = atoi(tmp);	
    }
    //conference
    ptr = strstr(recv_buff,"Conference");
    if(ptr != NULL)
    {
    	memset(request_message->conference->value,0,CONFERENCE_SIZE);
    	sprintf(request_message->conference->name, "Conference");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(request_message->conference->value, ptr1+1, length-1);	
    }
    //require
    ptr = strstr(recv_buff,"Require");
    if(ptr != NULL)
    {
    	memset(request_message->require->value,0,REQUIRE_SIZE);
    	sprintf(request_message->require->name, "Require");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(request_message->require->value, ptr1+1, length-1);	
    }
    //Scale 
	ptr = strstr(recv_buff,"Scale");
	memset(tmp,0,20);
    if(ptr != NULL)
    {
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(tmp, ptr1+1, length-1);
    	request_message->scale = atof(tmp);	
    }
    //Speed  
	ptr = strstr(recv_buff,"Speed");
	memset(tmp,0,20);
    if(ptr != NULL)
    {
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(tmp, ptr1+1, length-1);
    	request_message->speed = atof(tmp);	
    }
     //session
    ptr = strstr(recv_buff,"Session");
    if(ptr != NULL)
    {
    	memset(request_message->session->value,0,SESSION_SIZE);
    	sprintf(request_message->session->name, "Session");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(request_message->session->value, ptr1+1, length-1);	
    }
    //timestamp
    ptr = strstr(recv_buff,"Timestamp");
    if(ptr != NULL)
    {
    	memset(request_message->timestamp->value,0,TIMESTAMP_SIZE);
    	sprintf(request_message->timestamp->name, "Timestamp");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(request_message->timestamp->value, ptr1+1, length-1);	
    }
     //transport
    ptr = strstr(recv_buff,"Transport");
    if(ptr != NULL)
    {
    	memset(request_message->transport->value,0,TRANSPORT_SIZE);
    	sprintf(request_message->transport->name, "Transport");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(request_message->transport->value, ptr1+1, length-1);	
    }
     //cache_control
    ptr = strstr(recv_buff,"Cache-Control");
    if(ptr != NULL)
    {
    	memset(request_message->cache_control->value,0,CACHE_CONTROL_SIZE);
    	sprintf(request_message->cache_control->name, "Cache-Control");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(request_message->cache_control->value, ptr1+1, length-1);	
    }
    //connection
    ptr = strstr(recv_buff,"Connection");
    if(ptr != NULL)
    {
    	memset(request_message->connection->value,0,CONNECTION_SIZE);
    	sprintf(request_message->connection->name, "Connection");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(request_message->connection->value, ptr1+1, length-1);	
    }
    //date
    ptr = strstr(recv_buff,"Date");
    if(ptr != NULL)
    {
    	memset(request_message->date->value,0,DATE_SIZE);
    	sprintf(request_message->date->name, "Date");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(request_message->date->value, ptr1+1, length-1);	
    }
    //via
    ptr = strstr(recv_buff,"Via");
    if(ptr != NULL)
    {
    	memset(request_message->via->value,0,VIA_SIZE);
    	sprintf(request_message->via->name, "Via");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(request_message->via->value, ptr1+1, length-1);	
    }
    //user_agent
    ptr = strstr(recv_buff,"User-Agent");
    if(ptr != NULL)
    {
    	memset(request_message->user_agent->value,0,USER_AGENT_SIZE);
    	sprintf(request_message->user_agent->name, "User-Agent");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(request_message->user_agent->value, ptr1+1, length-1);	
    }
    //accept
    ptr = strstr(recv_buff,"Accept");
    if(ptr != NULL)
    {
    	memset(request_message->accept->value,0,ACCEPPT_SIZE);
    	sprintf(request_message->accept->name, "Accept");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(request_message->accept->value, ptr1+1, length-1);	
    }
    //accept_encoding
    ptr = strstr(recv_buff,"Accept-Encoding");
    if(ptr != NULL)
    {
    	memset(request_message->accept_encoding->value,0,ACCEPPT_ENCODING_SIZE);
    	sprintf(request_message->accept_encoding->name, "Accept-Encoding");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(request_message->accept_encoding->value, ptr1+1, length-1);	
    }
    //accept_language
    ptr = strstr(recv_buff,"Accept-Language");
    if(ptr != NULL)
    {
    	memset(request_message->accept_language->value,0,ACCEPPT_LANGUAGE_SIZE);
    	sprintf(request_message->accept_language->name, "Accept-Language");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(request_message->accept_language->value, ptr1+1, length-1);	
    }
     //from
    ptr = strstr(recv_buff,"From");
    if(ptr != NULL)
    {
    	memset(request_message->from->value,0,FROM_SIZE);
    	sprintf(request_message->from->name, "From");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(request_message->from->value, ptr1+1, length-1);	
    }
     //range
    ptr = strstr(recv_buff,"Range");
    if(ptr != NULL)
    {
    	memset(request_message->range->value,0,RANGE_SIZE);
    	sprintf(request_message->range->name, "Range");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(request_message->range->value, ptr1+1, length-1);	
    }
    //referer
    ptr = strstr(recv_buff,"Referer");
    if(ptr != NULL)
    {
    	memset(request_message->referer->value,0,REFERER_SIZE);
    	sprintf(request_message->referer->name, "Referer");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(request_message->referer->value, ptr1+1, length-1);	
    }
    //if_modified_since
    ptr = strstr(recv_buff,"If-Modified-Since");
    if(ptr != NULL)
    {
    	memset(request_message->if_modified_since->value,0,IF_MODIFIED_SINCE_SIZE);
    	sprintf(request_message->if_modified_since->name, "If-Modified-Since");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(request_message->if_modified_since->value, ptr1+1, length-1);	
    }
     //authorization
    ptr = strstr(recv_buff,"Authorization");
    if(ptr != NULL)
    {
    	memset(request_message->authorization->value,0,AUTHORIZATION_SIZE);
    	sprintf(request_message->authorization->name, "Authorization");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(request_message->authorization->value, ptr1+1, length-1);	
    }
     //allow
    ptr = strstr(recv_buff,"Allow");
    if(ptr != NULL)
    {
    	memset(request_message->allow->value,0,ALLOW_SIZE);
    	sprintf(request_message->allow->name, "Allow");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(request_message->allow->value, ptr1+1, length-1);	
    }
     //content_base
    ptr = strstr(recv_buff,"Content-Base");
    if(ptr != NULL)
    {
    	memset(request_message->content_base->value,0,CONTENT_BASE_SIZE);
    	sprintf(request_message->content_base->name, "Content-Base");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(request_message->content_base->value, ptr1+1, length-1);	
    }
     //content_encoding
    ptr = strstr(recv_buff,"Content-Encoding");
    if(ptr != NULL)
    {
    	memset(request_message->content_encoding->value,0,CONTENT_ENCODING_SIZE);
    	sprintf(request_message->content_encoding->name, "Content-Encoding");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(request_message->content_encoding->value, ptr1+1, length-1);	
    }
    //content_language
    ptr = strstr(recv_buff,"Content-Language");
    if(ptr != NULL)
    {
    	memset(request_message->content_language->value,0,CONTENT_LANGUAGE_SIZE);
    	sprintf(request_message->content_language->name, "Content-Language");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(request_message->content_language->value, ptr1+1, length-1);	
    }
     //content_length
	ptr = strstr(recv_buff,"Content-Length");
	memset(tmp,0,20);
    if(ptr != NULL)
    {
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(tmp, ptr1+1, length-1);
    	request_message->content_length = atoi(tmp);	
    }
    //content_location
    ptr = strstr(recv_buff,"Content-Location");
    if(ptr != NULL)
    {
    	memset(request_message->content_location->value,0,CONTENT_LOCATION_SIZE);
    	sprintf(request_message->content_location->name, "Content-Location");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(request_message->content_location->value, ptr1+1, length-1);	
    }
    //content_type
    ptr = strstr(recv_buff,"Content-Type");
    if(ptr != NULL)
    {
    	 memset(request_message->content_type->value,0,CONTENT_TYPE_SIZE);
    	sprintf(request_message->content_type->name, "Content-Type");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(request_message->content_type->value, ptr1+1, length-1);	
    }
     //expires
	ptr = strstr(recv_buff,"Expires");
	memset(tmp,0,20);
    if(ptr != NULL)
    {
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(tmp, ptr1+1, length-1);
    	request_message->expires = atoi(tmp);	
    }
     //last_modified
    ptr = strstr(recv_buff,"Last-Modified");
    if(ptr != NULL)
    {
    	memset(request_message->last_modified->value,0,LAST_MODIFIED_SIZE);
    	sprintf(request_message->last_modified->name, "Last-Modified");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(request_message->last_modified->value, ptr1+1, length-1);	
    }
    //body
    ptr = strstr(recv_buff,"\r\n\r\n");
    if(ptr != NULL)
    {
    	ptr1 = strchr(ptr+3,'\r');
    	if(ptr1 != NULL)
    	{
    		memset(request_message->body,0,BODY_SIZE);
    		length = ptr1 - ptr;
    	    strncpy(request_message->body, ptr+4, length-4);	
    	}
    }
	return 0;
}
int RtspMessageHandle::rtsp_response_message_init(char* recv_buff, rtsp_response_message_t* response_message)
{
	char *ptr = strchr(recv_buff,' ');
	int length = ptr - recv_buff;
	memset(response_message->version,0,VERSION_SIZE);
	strncpy(response_message->version, recv_buff, length);
	char tmp[20];
	memset(tmp,0,20);
	char *ptr1 = strchr(ptr+1,' ');
	length = ptr1 - ptr;
	strncpy(tmp, ptr+1, length-1);
	response_message->status_code = atoi(tmp);
	char *ptr2 = strchr(ptr1,'\r');
	length = ptr2 - ptr1;
	memset(response_message->reason,0,REASON_SIZE);
	strncpy(response_message->reason, ptr1+1, length-1);
	//cseq
	ptr = strstr(recv_buff,"CSeq");
	memset(tmp,0,20);
    if(ptr != NULL)
    {
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(tmp, ptr1+1, length-1);
    	response_message->cseq = atoi(tmp);	
    }
     //timestamp
    ptr = strstr(recv_buff,"Timestamp");
    if(ptr != NULL)
    {
    	memset(response_message->timestamp->value,0,TIMESTAMP_SIZE);
    	sprintf(response_message->timestamp->name, "Timestamp");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(response_message->timestamp->value, ptr1+1, length-1);	
    }
    //session
    ptr = strstr(recv_buff,"Session");
    if(ptr != NULL)
    {
    	memset(response_message->session->value,0,SESSION_SIZE);
    	sprintf(response_message->session->name, "Session");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(response_message->session->value, ptr1+1, length-1);	
    }
    //scale
	ptr = strstr(recv_buff,"Scale");
	memset(tmp,0,20);
    if(ptr != NULL)
    {
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(tmp, ptr1+1, length-1);
    	response_message->scale = atof(tmp);	
    }
    //rtp_info
    ptr = strstr(recv_buff,"RTP-MESSAGE");
    if(ptr != NULL)
    {
    	memset(response_message->rtp_info->value,0,RTP_INFO_SIZE);
    	sprintf(response_message->rtp_info->name, "RTP-MESSAGE");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(response_message->rtp_info->value, ptr1+1, length-1);	
    }
    //unsupported
    ptr = strstr(recv_buff,"Unsupported");
    if(ptr != NULL)
    {
    	memset(response_message->unsupported->value,0,UNSUPPORTED_SIZE);
    	sprintf(response_message->unsupported->name, "Unsupported");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(response_message->unsupported->value, ptr1+1, length-1);	
    }
    //speed
	ptr = strstr(recv_buff,"Speed");
	memset(tmp,0,20);
    if(ptr != NULL)
    {
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(tmp, ptr1+1, length-1);
    	response_message->speed = atof(tmp);	
    }
    //transport
    ptr = strstr(recv_buff,"Transport");
    if(ptr != NULL)
    {
    	memset(response_message->transport->value,0,TRANSPORT_SIZE);
    	sprintf(response_message->transport->name, "Transport");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(response_message->transport->value, ptr1+1, length-1);	
    }
    //cache_control
    ptr = strstr(recv_buff,"Cache-Control");
    if(ptr != NULL)
    {
    	sprintf(response_message->cache_control->name, "Cache-Control");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(response_message->cache_control->value, ptr1+1, length-1);	
    }
     //connection
    ptr = strstr(recv_buff,"Connection");
    if(ptr != NULL)
    {
    	memset(response_message->cache_control->value,0,CACHE_CONTROL_SIZE);
    	sprintf(response_message->connection->name, "Connection");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(response_message->connection->value, ptr1+1, length-1);	
    }
     //date
    ptr = strstr(recv_buff,"Date");
    if(ptr != NULL)
    {
    	memset(response_message->date->value,0,DATE_SIZE);
    	sprintf(response_message->date->name, "Date");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(response_message->date->value, ptr1+1, length-1);	
    }
     //via
    ptr = strstr(recv_buff,"Via");
    if(ptr != NULL)
    {
    	memset(response_message->via->value,0,VIA_SIZE);
    	sprintf(response_message->via->name, "Via");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(response_message->via->value, ptr1+1, length-1);	
    }
    //location
    ptr = strstr(recv_buff,"Location");
    if(ptr != NULL)
    {
    	memset(response_message->location->value,0,LOCATION_SIZE);
    	sprintf(response_message->location->name, "Location");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(response_message->location->value, ptr1+1, length-1);	
    }
     //proxy_authenticate
    ptr = strstr(recv_buff,"Proxy-Authenticate");
    if(ptr != NULL)
    {
    	memset(response_message->proxy_authenticate->value,0,PROXY_AUTHENTICATE_SIZE);
    	sprintf(response_message->proxy_authenticate->name, "Proxy-Authenticate");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(response_message->proxy_authenticate->value, ptr1+1, length-1);	
    }
     //_public
    ptr = strstr(recv_buff,"Public");
    if(ptr != NULL)
    {
    	memset(response_message->_public->value,0,_PUBLIC_SIZE);
    	sprintf(response_message->_public->name, "Public");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(response_message->_public->value, ptr1+1, length-1);	
    }
     //retry_after
    ptr = strstr(recv_buff,"Retry-After");
    if(ptr != NULL)
    {
    	memset(response_message->retry_after->value,0,RETRY_AFTER_SIZE);
    	sprintf(response_message->retry_after->name, "Retry-After");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(response_message->retry_after->value, ptr1+1, length-1);	
    }
    //server
    ptr = strstr(recv_buff,"Server");
    if(ptr != NULL)
    {
    	memset(response_message->server->value,0,SERVER_SIZE);
    	sprintf(response_message->server->name, "Server");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(response_message->server->value, ptr1+1, length-1);	
    }
    //vary
    ptr = strstr(recv_buff,"Vary");
    if(ptr != NULL)
    {
    	memset(response_message->vary->value,0,VARY_SIZE);
    	sprintf(response_message->vary->name, "Vary");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(response_message->vary->value, ptr1+1, length-1);	
    }
    //www_authenticate
    ptr = strstr(recv_buff,"WWW-Authenticate");
    if(ptr != NULL)
    {
    	memset(response_message->www_authenticate->value,0,WWW_AUTHENTICATE_SIZE);
    	sprintf(response_message->www_authenticate->name, "WWW-Authenticate");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(response_message->www_authenticate->value, ptr1+1, length-1);	
    }
     //allow
    ptr = strstr(recv_buff,"Allow");
    if(ptr != NULL)
    {
    	memset(response_message->allow->value,0,ALLOW_SIZE);
    	sprintf(response_message->allow->name, "Allow");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(response_message->allow->value, ptr1+1, length-1);	
    }
     //content_base
    ptr = strstr(recv_buff,"Content-Base");
    if(ptr != NULL)
    {
    	memset(response_message->content_base->value,0,CONTENT_BASE_SIZE);
    	sprintf(response_message->content_base->name, "Content-Base");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(response_message->content_base->value, ptr1+1, length-1);	
    }
     //content_encoding
    ptr = strstr(recv_buff,"Content-Encoding");
    if(ptr != NULL)
    {
    	memset(response_message->content_encoding->value,0,CONTENT_ENCODING_SIZE);
    	sprintf(response_message->content_encoding->name, "Content-Encoding");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(response_message->content_encoding->value, ptr1+1, length-1);	
    }
    //content_language
    ptr = strstr(recv_buff,"Content-Language");
    if(ptr != NULL)
    {
    	memset(response_message->content_language->value,0,CONTENT_LANGUAGE_SIZE);
    	sprintf(response_message->content_language->name, "Content-Language");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(response_message->content_language->value, ptr1+1, length-1);	
    }
     //content_length
	ptr = strstr(recv_buff,"Content-Length");
	memset(tmp,0,20);
    if(ptr != NULL)
    {
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(tmp, ptr1+1, length-1);
    	response_message->content_length = atoi(tmp);	
    }
    //content_location
    ptr = strstr(recv_buff,"Content-Location");
    if(ptr != NULL)
    {
    	memset(response_message->content_location->value,0,CONTENT_LOCATION_SIZE);
    	sprintf(response_message->content_location->name, "Content-Location");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(response_message->content_location->value, ptr1+1, length-1);	
    }
    //content_type
    ptr = strstr(recv_buff,"Content-Type");
    if(ptr != NULL)
    {
    	memset(response_message->content_type->value,0,CONTENT_TYPE_SIZE);
    	sprintf(response_message->content_type->name, "Content-Type");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(response_message->content_type->value, ptr1+1, length-1);	
    }
     //expires
	ptr = strstr(recv_buff,"Expires");
	memset(tmp,0,20);
    if(ptr != NULL)
    {
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(tmp, ptr1+1, length-1);
    	response_message->expires = atoi(tmp);	
    }
     //last_modified
    ptr = strstr(recv_buff,"Last-Modified");
    if(ptr != NULL)
    {
    	memset(response_message->last_modified->value,0,LAST_MODIFIED_SIZE);
    	sprintf(response_message->last_modified->name, "Last-Modified");
    	ptr1 = strchr(ptr,' ');
    	ptr2 = strchr(ptr1,'\r');
    	length = ptr2 - ptr1;
    	strncpy(response_message->last_modified->value, ptr1+1, length-1);	
    }
    //BODY
    ptr = strstr(recv_buff,"\r\n\r\n");
    if(ptr != NULL)
    {
    	ptr1 = strchr(ptr+3,'\r');
    	if(ptr1 != NULL)
    	{
    		memset(response_message->body,0,BODY_SIZE);
    		length = ptr1 - ptr;
    	    strncpy(response_message->body, ptr+4, length-4);
    	}		
    }
    return 0;
}
METHODTYPE RtspMessageHandle::rtsp_request_message_get_method(rtsp_request_message_t* request_message)
{
	if(strstr(request_message->method, "OPTIONS"))
	    return 1; 
	else if(strstr(request_message->method, "DESCRIBE"))
	    return 2;
	else if(strstr(request_message->method, "ANNOUNCE"))
	    return 3;
	else if(strstr(request_message->method, "SETUP"))
	    return 4;
	else if(strstr(request_message->method, "PLAY"))
	    return 5;
	else if(strstr(request_message->method, "PAUSE"))
	    return 6;
	else if(strstr(request_message->method, "TEARDOWN"))
	    return 7;
	else if(strstr(request_message->method, "GET_PARAMETER"))
	    return 8;
	else if(strstr(request_message->method, "SET_PARAMETER"))
	    return 9;
	else if(strstr(request_message->method, "REDIRECT"))
	    return 10;
	else if(strstr(request_message->method, "RECORD"))
	    return 11;
	else 
		return -1; 
}
STATUSCODE RtspMessageHandle::rtsp_request_message_handle(rtsp_event_t* event)
{
	switch(event->type)
	{
		case MESSAGE_IS_OPTION: return rtsp_request_message_parse_option(event->request_message); break;
		case MESSAGE_IS_DESCRIBE: return rtsp_request_message_parse_describe(event); break;
		case MESSAGE_IS_SETUP: return rtsp_request_message_parse_setup(event); break;
        case MESSAGE_IS_PLAY: return rtsp_request_message_parse_play(event); break;
        case MESSAGE_IS_PAUSE: return rtsp_request_message_parse_pause(event->request_message, event->response_message); break;
        case MESSAGE_IS_GET_PARAMETER: return rtsp_request_message_parse_get_parameter(); break;
        case MESSAGE_IS_TEARDOWN: return rtsp_request_message_parse_teardown(); break;
        case MESSAGE_IS_RECORD: return rtsp_request_message_parse_record(event); break;
		default: ; break;
	}
	return 405;
}
int RtspMessageHandle::rtsp_build_response_message(char *send_buff, rtsp_event_t* event, int response_status_code)
{
	if(response_status_code == 200)
	{
		switch(event->type)
        {
        	case MESSAGE_IS_OPTION:
        	return rtsp_build_response_message_option(send_buff, event->response_message);
        	break;
        	case MESSAGE_IS_DESCRIBE:
        	return rtsp_build_response_message_describe(send_buff, event->response_message);
        	break;
            case MESSAGE_IS_SETUP:
            return rtsp_build_response_message_setup(send_buff, event);
            break;
            case MESSAGE_IS_PLAY:
            {
                if(event->play == 0)
                    event->play = 1;
                else if(event->play == 1)
                    event->pause = 0;
                return rtsp_build_response_message_play(send_buff, event);
            }
            break;
            case MESSAGE_IS_PAUSE:
            {
                event->pause = 1;
                return rtsp_build_response_message_pause(send_buff, event);
            }
            break;
            case MESSAGE_IS_GET_PARAMETER:
            return rtsp_build_response_message_get_parameter(send_buff, event);
            break;
            case MESSAGE_IS_RECORD:
            return rtsp_build_response_message_record(send_buff, event);
            break;
            case MESSAGE_IS_TEARDOWN:
            {
                event->teardown = 1;
                return rtsp_build_response_message_teardown(send_buff, event);
            }
            break;
        	default:	;break;
        }
	}
	else
	{
		rtsp_build_response_message_error(send_buff, event->response_message->cseq, response_status_code);
	}
	
	return 0;
}
