#arm-none-linux-gnueabi-gcc -c main.c -o main.o 
rm -rf *.o
arm-none-linux-gnueabi-gcc -c send_data.c -o send_data.o 
arm-none-linux-gnueabi-gcc -c uart.c -o uart.o 
arm-none-linux-gnueabi-gcc -c setconfig.c -o setconfig.o 
arm-none-linux-gnueabi-gcc -c main.c -o main.o
arm-none-linux-gnueabi-gcc -c rec_data.c -o rec_data.o
arm-none-linux-gnueabi-gcc -o zigbee  main.o  setconfig.o  uart.o send_data.o  rec_data.o -static
