#include "yyhrtsp.h"
#include "pthread.h"
map<int, string> map_client_ipaddr;
int create_server(void)
{
    int    server_port = 554;
    int    max_conn_limit = 1024;
    int    sockfd_server, connect_fd;
    struct sockaddr_in addr_server, addr_client;
    int client_length;
	if( (sockfd_server = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
    {  
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(1);  
    }  
    int reuse  = 1;   
    setsockopt(sockfd_server, SOL_SOCKET, SO_REUSEADDR, (const void *)&reuse, sizeof(reuse));
    memset(&addr_server, 0, sizeof(addr_server));
    addr_server.sin_family = AF_INET;  
    addr_server.sin_addr.s_addr = htonl(INADDR_ANY);  
    addr_server.sin_port = htons(server_port);
    if( bind(sockfd_server, (struct sockaddr*)&addr_server, sizeof(addr_server)) == -1)
    {  
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(1);  
    }  
    if( listen(sockfd_server, max_conn_limit) == -1)
    {  
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(1);  
    }  
    client_length = sizeof(addr_client);
    while(1)
    { 
        pthread_t thread_id; 
        pthread_attr_t attr;
        pthread_attr_init (&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        
        cout<<"wait user connect"<<endl;
        if( (connect_fd = accept(sockfd_server, (struct sockaddr *)&addr_client, (socklen_t *)(&client_length))) == -1)
        {  
            printf("accept socket error: %s(errno: %d)",strerror(errno),errno);  
            continue;
        }
        map_client_ipaddr[connect_fd] =  inet_ntoa(addr_client.sin_addr); 
        if(pthread_create(&thread_id, &attr, rtsp_thread, (void *)(&connect_fd)) == -1)
        {
            fprintf(stderr,"pthread_create error!\n");
            break;                                 
        }
        pthread_attr_destroy (&attr);
    } 
    int ret = shutdown(sockfd_server,SHUT_WR); 
    assert(ret != -1);
    printf("Server shuts down\n");
    return 0;    
}
void*  rtsp_thread(void * sock_fd)
{
    int fd = *((int *)sock_fd);
    printf("SOCKED_FD %d: start\n", fd);
    RtspEventHandle MyRtspEventHandle;
    rtsp_event_t* event;
    event = MyRtspEventHandle.rtsp_event_init(fd);
    if(event == NULL)
        exit(1);
    RTPForRtsp MyRTPForRtsp;
    int rtp_stat = 0;
    int res, i_recvBytes, res_handle_rtsp;
    int recv_buff_length = 4096;
    char recv_buff[recv_buff_length];
    char send_buff[4096];
    fd_set rfds, wfds;
    struct timeval tv;
    while(1)
    {
        i_recvBytes = 0;
        res_handle_rtsp = 0;
        memset(recv_buff,0,recv_buff_length);
        memset(send_buff,0,4096);
        tv.tv_sec  = 1;                    
        tv.tv_usec = 0;
        FD_ZERO(&rfds); 
        FD_ZERO(&wfds); 
        FD_SET(fd, &rfds);
        FD_SET(fd, &wfds);
        res = select(fd+1, &rfds, &wfds, NULL, &tv);
        if(res == -1)
            break;
        else if(res == 0)
            ;
        else if(res > 0)
        {
            if(FD_ISSET(fd,&rfds))
            {
                i_recvBytes = read(fd, recv_buff, recv_buff_length);
                if(i_recvBytes == 0)
                    break;
            }
            if(FD_ISSET(fd,&wfds))
            {
                if(i_recvBytes > 0)
                {
                    res_handle_rtsp = MyRtspEventHandle.rtsp_event_handle(recv_buff, send_buff, event, map_client_ipaddr[fd].c_str());
                    cout<<"*************************************************"<<endl;
                    cout<<"request_message is:"<<endl;
                    cout<<recv_buff<<endl;
                    cout<<"*************************************************"<<endl;
                    if(res_handle_rtsp == 0)
                    {
                        cout<<"*************************************************"<<endl;
                        cout<<"response_message is:"<<endl;
                        cout<<send_buff<<endl;
                        cout<<"*************************************************"<<endl;
                        write(fd, send_buff, strlen(send_buff));
                    }
                }
                if(res_handle_rtsp < 0)
                {
                    ;
                }
            }
        }
        if(rtp_stat == 0)
        {
            usleep(5000);
            if(event->play == 1)
            {
                rtp_stat = 1;
                if(MyRTPForRtsp.RTPSessionInit(event) != 0)
                {
                    fprintf(stderr,"RTPSessionInit error!\n");
                    break;                                 
                }
            }   
        }
        else if(rtp_stat == 1 && event->pause == 0)
        {
            if(MyRTPForRtsp.RTPSessionSend(event) == 2)
                rtp_stat = 2;
        }
        else if(rtp_stat == 2)
        {
            rtp_stat = 0;
            event->play = 0;
            MyRTPForRtsp.RTPSessionClose();
            usleep(5000);
            break;
        }
        else
            usleep(5000);
    }
    cout<<"rtp_stat is :"<<rtp_stat<<endl;
    if(rtp_stat == 1 || rtp_stat == 2)
        MyRTPForRtsp.RTPSessionClose();
    res = MyRtspEventHandle.rtsp_event_free(event);
    printf("SOCKED_FD %d: terminating current client_connection...\n", fd);
    close(fd); 
    map_client_ipaddr.erase(fd);          
    pthread_exit(NULL);   
    return NULL; 
}
    
 

