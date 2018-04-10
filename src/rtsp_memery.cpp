#include "rtsp_memery.h"
#include <malloc.h>  
#include <iostream>
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h> 

rtsp_event_t* RtspMemeryHandle::rtsp_event_mem_calloc()
{
    rtsp_event_t* event;
    if ((event = (rtsp_event_t*)calloc (1, sizeof (rtsp_event_t))) == NULL)
        return NULL;
    if ((event->request_message = (rtsp_request_message_t*)calloc (1, sizeof (rtsp_request_message_t))) == NULL)
        return NULL;
    if ((event->response_message = (rtsp_response_message_t*)calloc (1, sizeof (rtsp_response_message_t))) == NULL)
        return NULL;
    if ((event->rtp_message = (rtp_message_t*)calloc (1, sizeof (rtp_message_t))) == NULL)
        return NULL;
  //  printf("rtsp_event_mem_calloc rtp_message:%d\n", event->rtp_message);
    return event;
}

int RtspMemeryHandle::rtsp_event_mem_free(rtsp_event_t* event)
{
    if(event)
        free(event);
    return 0;
}
int RtspMemeryHandle::rtp_message_mem_calloc(rtp_message_t* rtp_message)
{
  //  printf("rtsp_event_mem_calloc rtp_message:%d\n", rtp_message);
    if ((rtp_message->client_ip = (char*)calloc (CLIENT_IP_SIZE, sizeof (char))) == NULL)
        return -1;
    if ((rtp_message->server_ip = (char*)calloc (CLIENT_IP_SIZE, sizeof (char))) == NULL)
        return -1;
    if ((rtp_message->filename = (char*)calloc (FILENAME_SIZE, sizeof (char))) == NULL)
        return -1;
   // printf("rtp_message_mem_calloc rtp_message->server_ip:%d\n", rtp_message->server_ip);
    return 0;
}
int RtspMemeryHandle::rtp_message_mem_free(rtp_message_t* rtp_message)
{
  //  printf("rtp_message_mem_free rtp_message->server_ip:%d\n", rtp_message->server_ip);
    if(rtp_message)
    {
        if(rtp_message->server_ip)
        {
            free(rtp_message->server_ip);
            rtp_message->server_ip = NULL;
        }
        if(rtp_message->client_ip)
        {
            free(rtp_message->client_ip);
            rtp_message->client_ip = NULL;
        }  
        if(rtp_message->filename)
        {
            free(rtp_message->filename);
            rtp_message->filename = NULL;
        }  
        free(rtp_message);
    }
    return 0;
}
int RtspMemeryHandle::rtsp_request_message_mem_calloc(rtsp_request_message_t* request_message)
{
	//request-line
    if ((request_message->method = (char*)calloc (METHOD_SIZE, sizeof (char))) == NULL)
    	return -1;
    if ((request_message->url = (char*)calloc (URL_SIZE, sizeof (char))) == NULL)
    	return -1;
    if ((request_message->version = (char*)calloc (VERSION_SIZE, sizeof (char))) == NULL)
    	return -1;

    //other

    if ((request_message->conference = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((request_message->conference), CONFERENCE_SIZE)) != 0)
        return -1;

    if ((request_message->require = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((request_message->require), REQUIRE_SIZE)) != 0)
        return -1;

    if ((request_message->session = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((request_message->session), SESSION_SIZE)) != 0)
        return -1;

    if ((request_message->timestamp = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((request_message->timestamp), TIMESTAMP_SIZE)) != 0)
        return -1;

    if ((request_message->transport = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((request_message->transport), TRANSPORT_SIZE)) != 0)
        return -1;


    //general-header
    if ((request_message->cache_control = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
    	return -1;
    if((rtsp_header_mem_calloc((request_message->cache_control), CACHE_CONTROL_SIZE)) != 0)
    	return -1;

    if ((request_message->connection = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
    	return -1;
    if((rtsp_header_mem_calloc((request_message->connection), CONNECTION_SIZE)) != 0)
    	return -1;

    if ((request_message->date = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
    	return -1;
    if((rtsp_header_mem_calloc((request_message->date), DATE_SIZE)) != 0)
    	return -1;

    if ((request_message->via = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
    	return -1;
    if((rtsp_header_mem_calloc((request_message->via), VIA_SIZE)) != 0)
    	return -1;

    //request-header
    if ((request_message->user_agent = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
    	return -1;
    if((rtsp_header_mem_calloc((request_message->user_agent), USER_AGENT_SIZE)) != 0)
    	return -1;

    if ((request_message->accept = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
    	return -1;
    if((rtsp_header_mem_calloc((request_message->accept), ACCEPPT_SIZE)) != 0)
    	return -1;

    if ((request_message->accept_encoding = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
    	return -1;
    if((rtsp_header_mem_calloc((request_message->accept_encoding), ACCEPPT_ENCODING_SIZE)) != 0)
    	return -1;

    if ((request_message->accept_language = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
    	return -1;
    if((rtsp_header_mem_calloc((request_message->accept_language), ACCEPPT_LANGUAGE_SIZE)) != 0)
    	return -1;

    if ((request_message->from = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
    	return -1;
    if((rtsp_header_mem_calloc((request_message->from), FROM_SIZE)) != 0)
    	return -1;

    if ((request_message->range = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
    	return -1;
    if((rtsp_header_mem_calloc((request_message->range), RANGE_SIZE)) != 0)
    	return -1;

    if ((request_message->referer = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
    	return -1;
    if((rtsp_header_mem_calloc((request_message->referer), REFERER_SIZE)) != 0)
    	return -1;

    if ((request_message->if_modified_since = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
    	return -1;
    if((rtsp_header_mem_calloc((request_message->if_modified_since), IF_MODIFIED_SINCE_SIZE)) != 0)
    	return -1;

    if ((request_message->authorization = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
    	return -1;
    if((rtsp_header_mem_calloc((request_message->authorization), AUTHORIZATION_SIZE)) != 0)
    	return -1;

    // entity-header
    if ((request_message->allow = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
    	return -1;
    if((rtsp_header_mem_calloc((request_message->allow), ALLOW_SIZE)) != 0)
    	return -1;

    if ((request_message->content_base = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
    	return -1;
    if((rtsp_header_mem_calloc((request_message->content_base), CONTENT_BASE_SIZE)) != 0)
    	return -1;

    if ((request_message->content_encoding = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
    	return -1;
    if((rtsp_header_mem_calloc((request_message->content_encoding), CONTENT_ENCODING_SIZE)) != 0)
    	return -1;

    if ((request_message->content_language = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
    	return -1;
    if((rtsp_header_mem_calloc((request_message->content_language), CONTENT_LANGUAGE_SIZE)) != 0)
    	return -1;

    if ((request_message->content_location = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
    	return -1;
    if((rtsp_header_mem_calloc((request_message->content_location), CONTENT_LOCATION_SIZE)) != 0)
    	return -1;

    if ((request_message->content_type = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
    	return -1;
    if((rtsp_header_mem_calloc((request_message->content_type), CONTENT_TYPE_SIZE)) != 0)
    	return -1;

    if ((request_message->last_modified = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
    	return -1;
    if((rtsp_header_mem_calloc((request_message->last_modified), LAST_MODIFIED_SIZE)) != 0)
    	return -1;

    //body
    if ((request_message->body = (char*)calloc (BODY_SIZE, sizeof (char))) == NULL)
    	return -1;

    return 0;
}


int RtspMemeryHandle::rtsp_request_message_mem_free(rtsp_request_message_t* request_message)
{
    if(request_message)
    {
        //body   
        if(request_message->body)
        {
            free(request_message->body);
            request_message->body = NULL;
        }
            
    
        //general-header
        rtsp_header_mem_free((request_message->cache_control));
        if(request_message->cache_control)
        {
            free(request_message->cache_control);
            request_message->cache_control = NULL;
        }
            
    
        rtsp_header_mem_free((request_message->connection));
        if(request_message->connection)
        {
            free(request_message->connection);
            request_message->connection = NULL;
        }
            
    
        rtsp_header_mem_free((request_message->date));
        if(request_message->date)
        {
            free(request_message->date);
            request_message->date = NULL;
        }
            
    
        rtsp_header_mem_free((request_message->via));
        if(request_message->via)
        {
            free(request_message->via);
            request_message->via = NULL;
        }
            
    
        //request-header
        rtsp_header_mem_free((request_message->user_agent));
        if(request_message->user_agent)
        {
            free(request_message->user_agent);
            request_message->user_agent = NULL;
        }
            
    
        rtsp_header_mem_free((request_message->accept));
        if(request_message->accept)
        {
            free(request_message->accept);
            request_message->accept = NULL;
        }
            
    
        rtsp_header_mem_free((request_message->accept_encoding));
        if(request_message->accept_encoding)
        {
            free(request_message->accept_encoding);
            request_message->accept_encoding = NULL;
        }
            
    
        rtsp_header_mem_free((request_message->accept_language));
        if(request_message->accept_language)
        {
            free(request_message->accept_language);
            request_message->accept_language = NULL;
        }
            
        rtsp_header_mem_free((request_message->from));
        if(request_message->from)
        {
            free(request_message->from);
            request_message->from = NULL;
        }
            
    
        rtsp_header_mem_free((request_message->range));
        if(request_message->range)
        {
            free(request_message->range);
            request_message->range = NULL;
        }
            
    
        rtsp_header_mem_free((request_message->referer));
        if(request_message->referer)
        {
            free(request_message->referer);
            request_message->referer = NULL;
        }
    
        rtsp_header_mem_free((request_message->if_modified_since));
        if(request_message->if_modified_since)
        {
            free(request_message->if_modified_since);
            request_message->if_modified_since = NULL;
    
        }
            
    
        rtsp_header_mem_free((request_message->authorization));
        if(request_message->authorization)
        {
            free(request_message->authorization);
            request_message->authorization = NULL;
        }
            
    
        // entity-header
        rtsp_header_mem_free((request_message->allow));
        if(request_message->allow)
        {
            free(request_message->allow);
            request_message->allow = NULL;
        }
            
    
        rtsp_header_mem_free((request_message->content_base));
        if(request_message->content_base)
        {
            free(request_message->content_base);
            request_message->content_base = NULL;
        }
            
    
        rtsp_header_mem_free((request_message->content_encoding));
        if(request_message->content_encoding)
        {
            free(request_message->content_encoding);
            request_message->content_encoding = NULL;
        }
            
    
        rtsp_header_mem_free((request_message->content_language));
        if(request_message->content_language)
        {
            free(request_message->content_language);
            request_message->content_language = NULL;
        }
            
    
        rtsp_header_mem_free((request_message->content_location));
        if(request_message->content_location)
        {
            free(request_message->content_location);
            request_message->content_location = NULL;
        }
            
    
        rtsp_header_mem_free((request_message->content_type));
        if(request_message->content_type)
        {
            free(request_message->content_type);
            request_message->content_type = NULL;
        }
            
    
        rtsp_header_mem_free((request_message->last_modified));
        if(request_message->last_modified)
        {
            free(request_message->last_modified);
            request_message->last_modified = NULL;
        }
            
    
        //other
    
        rtsp_header_mem_free((request_message->conference));
        if(request_message->conference)
        {
            free(request_message->conference);
            request_message->conference = NULL;
        }
            
    
        rtsp_header_mem_free((request_message->require));
        if(request_message->require)
        {
            free(request_message->require);
            request_message->require = NULL;
        }
            
    
        rtsp_header_mem_free((request_message->session));
        if(request_message->session)
        {
            free(request_message->session);
            request_message->session = NULL;
        }
            
    
        rtsp_header_mem_free((request_message->timestamp));
        if(request_message->timestamp)
        {
            free(request_message->timestamp);
            request_message->timestamp = NULL;
        }
            
    
        rtsp_header_mem_free((request_message->transport));
        if(request_message->transport)
        {
            free(request_message->transport);
            request_message->transport = NULL;
        }
            
    
        //request-line
        if(request_message->version)
        {
            free(request_message->version);
            request_message->version = NULL;
        }
            
        if(request_message->url)
        {
            free(request_message->url);
            request_message->url = NULL;
        }
            
        if(request_message->method)
        {
            free(request_message->method);
            request_message->method = NULL;
        }
        free(request_message);
    }	    
	return 0;
}
 int RtspMemeryHandle::rtsp_response_message_mem_calloc(rtsp_response_message_t* response_message)
{
    //request-line
    if ((response_message->reason = (char*)calloc (REASON_SIZE, sizeof (char))) == NULL)
        return -1;
    if ((response_message->version = (char*)calloc (VERSION_SIZE, sizeof (char))) == NULL)
        return -1;
     if ((response_message->url = (char*)calloc (URL_SIZE, sizeof (char))) == NULL)
        return -1;
    //other

    if ((response_message->timestamp = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((response_message->timestamp), TIMESTAMP_SIZE)) != 0)
        return -1;

    if ((response_message->session = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((response_message->session), SESSION_SIZE)) != 0)
        return -1;

    if ((response_message->rtp_info = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((response_message->rtp_info), RTP_INFO_SIZE)) != 0)
        return -1;

    if ((response_message->unsupported = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((response_message->unsupported), UNSUPPORTED_SIZE)) != 0)
        return -1;

    if ((response_message->transport = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((response_message->transport), TRANSPORT_SIZE)) != 0)
        return -1;

    //general-header
    if ((response_message->cache_control = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((response_message->cache_control), CACHE_CONTROL_SIZE)) != 0)
        return -1;

    if ((response_message->connection = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((response_message->connection), CONNECTION_SIZE)) != 0)
        return -1;

    if ((response_message->date = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((response_message->date), DATE_SIZE)) != 0)
        return -1;

    if ((response_message->via = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((response_message->via), VIA_SIZE)) != 0)
        return -1;

    //response-header
    if ((response_message->range = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((response_message->range), RANGE_SIZE)) != 0)
        return -1;

    if ((response_message->location = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((response_message->location), LOCATION_SIZE)) != 0)
        return -1;

    if ((response_message->proxy_authenticate = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((response_message->proxy_authenticate), PROXY_AUTHENTICATE_SIZE)) != 0)
        return -1;

    if ((response_message->_public = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((response_message->_public), _PUBLIC_SIZE)) != 0)
        return -1;

    if ((response_message->retry_after = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((response_message->retry_after), RETRY_AFTER_SIZE)) != 0)
        return -1;

    if ((response_message->server = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((response_message->server), SERVER_SIZE)) != 0)
        return -1;

    if ((response_message->vary = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((response_message->vary), VARY_SIZE)) != 0)
        return -1;

    if ((response_message->www_authenticate = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((response_message->www_authenticate), WWW_AUTHENTICATE_SIZE)) != 0)
        return -1;

    // entity-header
    if ((response_message->allow = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((response_message->allow), ALLOW_SIZE)) != 0)
        return -1;

    if ((response_message->content_base = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((response_message->content_base), CONTENT_BASE_SIZE)) != 0)
        return -1;

    if ((response_message->content_encoding = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((response_message->content_encoding), CONTENT_ENCODING_SIZE)) != 0)
        return -1;

    if ((response_message->content_language = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((response_message->content_language), CONTENT_LANGUAGE_SIZE)) != 0)
        return -1;

    if ((response_message->content_location = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((response_message->content_location), CONTENT_LOCATION_SIZE)) != 0)
        return -1;

    if ((response_message->content_type = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((response_message->content_type), CONTENT_TYPE_SIZE)) != 0)
        return -1;

    if ((response_message->last_modified = (rtsp_header_t*)calloc (1, sizeof (rtsp_header_t))) == NULL)
        return -1;
    if((rtsp_header_mem_calloc((response_message->last_modified), LAST_MODIFIED_SIZE)) != 0)
        return -1;

    //body
    if ((response_message->body = (char*)calloc (BODY_SIZE, sizeof (char))) == NULL)
        return -1;

    return 0;
}

int RtspMemeryHandle::rtsp_response_message_mem_free(rtsp_response_message_t* response_message)
{
  //  printf("rtsp_response_message_free begin\n");
    if(response_message)
    {
        //body
        if(response_message->body)
        {
            free(response_message->body);
            response_message->body = NULL;
        }
            
        //general-header
        rtsp_header_mem_free((response_message->cache_control));
        if(response_message->cache_control)
        {
            free(response_message->cache_control);
            response_message->cache_control = NULL;
        }
            
        rtsp_header_mem_free((response_message->connection));
        if(response_message->connection)
        {
            free(response_message->connection);
            response_message->connection = NULL;
        }
    
        rtsp_header_mem_free((response_message->date));
        if(response_message->date)
        {
            free(response_message->date);
            response_message->date = NULL;
        }
    
        rtsp_header_mem_free((response_message->via));
        if(response_message->via)
        {
            free(response_message->via);
            response_message->via = NULL;
        }
    
        //response-header
        rtsp_header_mem_free((response_message->range));
        if(response_message->range)
        {
            free(response_message->range);
            response_message->range = NULL;
        }
    
        rtsp_header_mem_free((response_message->location));
        if(response_message->location)
        {
            free(response_message->location);
            response_message->location = NULL;
        }
            
    
        rtsp_header_mem_free((response_message->proxy_authenticate));
        if(response_message->proxy_authenticate)
        {
            free(response_message->proxy_authenticate);
            response_message->proxy_authenticate = NULL;
        }
            
    
        rtsp_header_mem_free((response_message->_public));
        if(response_message->_public)
        {
            free(response_message->_public);
            response_message->_public = NULL;
        }
            
    
        rtsp_header_mem_free((response_message->retry_after));
        if(response_message->retry_after)
        {
            free(response_message->retry_after);
            response_message->retry_after = NULL;
        }
            
    
        rtsp_header_mem_free((response_message->server));
        if(response_message->server)
        {
            free(response_message->server);
            response_message->server = NULL;
        }
    
    
        rtsp_header_mem_free((response_message->vary));
        if(response_message->vary)
        {
            free(response_message->vary);
            response_message->vary = NULL;
        }
            
    
        rtsp_header_mem_free((response_message->www_authenticate));
        if(response_message->www_authenticate)
        {
            free(response_message->www_authenticate);
            response_message->www_authenticate =NULL;
        }
            
    
        // entity-header
        rtsp_header_mem_free((response_message->allow));
        if(response_message->allow)
        {
            free(response_message->allow);
            response_message->allow = NULL;
        }
            
    
        rtsp_header_mem_free((response_message->content_base));
        if(response_message->content_base)
        {
            free(response_message->content_base);
            response_message->content_base = NULL;
        }
            
    
        rtsp_header_mem_free((response_message->content_encoding));
        if(response_message->content_encoding)
        {
            free(response_message->content_encoding);
            response_message->content_encoding = NULL;
        }
            
    
        rtsp_header_mem_free((response_message->content_language));
        if(response_message->content_language)
        {
            free(response_message->content_language);
            response_message->content_language = NULL;
        }
            
    
        rtsp_header_mem_free((response_message->content_location));
        if(response_message->content_location)
        {
            free(response_message->content_location);
            response_message->content_location = NULL;
        }
            
    
        rtsp_header_mem_free((response_message->content_type));
        if(response_message->content_type)
        {
            free(response_message->content_type);
            response_message->content_type = NULL;
        }
    
        rtsp_header_mem_free((response_message->last_modified));
        if(response_message->last_modified)
        {
            free(response_message->last_modified);
            response_message->last_modified = NULL;
        }
            
    
        //other
    
        rtsp_header_mem_free((response_message->timestamp));
        if(response_message->timestamp)
        {
            free(response_message->timestamp);
            response_message->timestamp = NULL;
        }
            
    
        rtsp_header_mem_free((response_message->session));
        if(response_message->session)
        {
            free(response_message->session);
            response_message->session = NULL;
        }
           
    
        rtsp_header_mem_free((response_message->rtp_info));
        if(response_message->rtp_info)
        {
            free(response_message->rtp_info);
            response_message->rtp_info = NULL;
        }
            
    
        rtsp_header_mem_free((response_message->unsupported));
        if(response_message->unsupported)
        {
            free(response_message->unsupported);
            response_message->unsupported = NULL;
        }
            
    
        rtsp_header_mem_free((response_message->transport));
        if(response_message->transport)
        {
            free(response_message->transport);
            response_message->transport = NULL;
        }
            
    
    
        //request-line
        
        if(response_message->url)
        {
            free(response_message->url);
            response_message->url = NULL;
        }
            
        if(response_message->version)
        {
            free(response_message->version);
            response_message->version = NULL;
        }
            
        if(response_message->reason)
        {
            free(response_message->reason);
            response_message->reason = NULL;
        }
            
        
        free(response_message);

    }
        
  //  printf("rtsp_response_message_free end\n");
    return 0;
}

int RtspMemeryHandle::rtsp_header_mem_calloc(rtsp_header_t* header, int value_size)
{
    if ((header->name = (char*)calloc (30, sizeof (char))) == NULL)
    {
    	return -1;
    }
    if ((header->value = (char*)calloc (value_size, sizeof (char))) == NULL)
    {
    	return -1;
    }
    return 0;
}
int RtspMemeryHandle::rtsp_header_mem_free(rtsp_header_t* header)
{
    if(header->name)
    {
        free(header->name);
        header->name = NULL;
    }
    if(header->value)
    {
        free(header->value);
        header->value = NULL;
    }	
    return 0;
}
