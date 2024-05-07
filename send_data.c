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

int send_data(int fd,int length,char *cmd[])
{
	unsigned char buffer[128];
	int i,time=0,num,flag=0;
	int check_length=0;
	
	memset(buffer, 0, sizeof(buffer));
	
	printf("set_config setdata is : ");
	for(i = 0; i < length-2; i++){	
		buffer[i] = strtol(cmd[i+2], NULL, 16);	
		check_length++;
		if(buffer[i] == 0xfe){
			check_length--;
		}
		printf("0x%02x ",buffer[i]);
	}
	printf("\n");
	
	DPRINTF("length is %d and %d\n",buffer[1],check_length);
	//pak_length = pkg_length - num_fe - 2 
	if(buffer[1] == check_length - 2){
		write(fd,buffer,i);
	}
	else{
		DPRINTF("cmd length is err\n");
		return -1;
	}
	
	return 0;
}