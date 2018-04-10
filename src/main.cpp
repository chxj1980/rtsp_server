#include "yyhrtsp.h"  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include "Log.h"
int main(int argc, char** argv)
{
	LOG("rtsp_server start");
    create_server();
    return 0;     
}
