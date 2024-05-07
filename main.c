#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

#include "main.h"

#define SETMODE  0
#define SENDMODE 1
#define RECMODE 2

extern int uart_init(void);
extern int set_config(int fd ,int length,char *cmd[]);
extern int send_data(int fd,int length,char *cmd[]);
extern int rec_data(int fd);

int para(int argc,char *argv[])
{
	if(argc < 2){
		printf("argv is less\n");
		printf("Usage:	test_zigbee [type] [cmd]\n");
		printf("	type: 0--set, 1--send, 2--recv\n");
		return -1;
	}
	
	return 0;
}

int main(int argc, char *argv[])
{
	int fd=0;
	
	if(para(argc,argv)<0){
		return -1;
	}
	
	fd = uart_init();
	if(fd < 0){
		return -1;
	}
	DPRINTF("atoi(argv[1]) is %d\n",atoi(argv[1]));
	switch(atoi(argv[1])){
		case SETMODE:
			DPRINTF("set_config\n");
			set_config(fd,argc,argv);
			break;
		case SENDMODE:
			DPRINTF("send_data\n");
			send_data(fd,argc,argv);
			break;
		case RECMODE:
			DPRINTF("rec_data one time\n");
			rec_data(fd);
			break;
		default:
			break;
	}
	
	return 0;
}