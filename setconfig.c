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

int set_config(int fd ,int length,char *cmd[])
{
	unsigned char buffer[128],rec_buffer[1];
	int i,nByte=0,time=0,num,flag=0;
	int check_length=0;
	
	memset(buffer, 0, sizeof(buffer));
	memset(buffer, 0, sizeof(rec_buffer));
	
	DPRINTF("set_config setdata is : ");
	for(i = 0; i < length-2; i++){	
		buffer[i] = strtol(cmd[i+2], NULL, 16);	
		check_length++;
		if(buffer[i] == 0xfe){
			check_length--;
		}
		printf("0x%02x ",buffer[i]);
	}
	printf("\n");
	
	DPRINTF("length uis %d and %d\n",buffer[1],check_length);
	//pak_length = pkg_length - num_fe - 2 
	if(buffer[1] == check_length - 2){
		write(fd,buffer,i);
	}
	else{
		printf("cmd length is err\n");
		return -1;
	}
	
	check_length = 0;
	memset(buffer, 0, sizeof(buffer));
	while(1){
		while((nByte = read(fd, rec_buffer, 1))>0){
			if(rec_buffer[0] == 0xfe && flag != 1){
				num = 0;	
				flag = 1;
				printf("set_config rev data is : ");
			}
			if(flag==1){
				buffer[num] = rec_buffer[0];
				printf("0x%02x ",rec_buffer[0]);
				
				check_length++;
				if(rec_buffer[0] == 0xfe)
					check_length--;
			}
			
			if(rec_buffer[0] == 0xff){
				goto rec_over;
			}
			
			memset(rec_buffer, 0, sizeof(rec_buffer));
			num++;
			nByte = 0;
			time = 0;
		}
	//if overtime 10ms , break.	
		usleep(1);
		time++;
		if(time>10000){
			DPRINTF("over time\n");
			close(fd);
			break;
		}
	}
	close(fd);
	return 0;
	
rec_over:
	printf("\n");
	if(buffer[1] == check_length - 2){
		DPRINTF("rec length check ok\n");
	}
	else{
		DPRINTF("rec length is err\n");
		return -1;
	}
	close(fd);
	return 0;
}

