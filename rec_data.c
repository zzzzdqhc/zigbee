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

int rec_data(int fd)
{
	unsigned char buffer[128],rec_buffer[1];
	int nByte,num,flag=0;
	int check_length=0;
	char buf[128];

	memset(rec_buffer, 0, sizeof(rec_buffer));
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
				printf("num is %d\n",num);
				if((num == 6) && (buffer[6] == 0x01))
				{
					//system("echo 1 > /sys/class/gpio/gpio126/value");
					system("./relay 1");
				}
				else if((num == 6) && (buffer[6] == 0x02))
				{
					//system("echo 0 > /sys/class/gpio/gpio126/value");
					system("./relay 0");
				}
				if((num == 6) && (buffer[6] == 0x03))
				{
					system("./step_motor_app R 4076 3000");
				}
				else if((num == 6) && (buffer[6] == 0x04))
				{
					system("./step_motor_app L 4076 3000");
				}
				check_length++;
				printf(" check_length is %d\n",check_length);
				if(rec_buffer[0] == 0xfe)
					check_length--;
			}
			
			if(rec_buffer[0] == 0xff){
				//goto rec_over;
				num=0;
				flag=0;
				check_length=0;
				memset(buffer, 0, sizeof(buffer));
			}
			
			memset(rec_buffer, 0, sizeof(rec_buffer));
			num++;
		}
		usleep(100);
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