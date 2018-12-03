/*
 * drvTCP.c
 *
 *  Created on: 3 ���. 2016 �.
 *      Author: Sergey Rybalko
 */

#include "drvTCP.h"
#include<stdio.h>
#include<string.h>    //strlen
#include <stdlib.h>
#include<sys/socket.h>
#include <string.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include "drvSTM32F303.h"

int socket_desc;
int new_socket;
struct sockaddr_in server, client;
static uint8_t start_command_state = 0;

void drvTCP_CreateSocket(void)
{

	 //Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );

   //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
    	puts("bind failed");
       exit(EXIT_FAILURE);
    }
    puts("bind done");
}

void drvTCP_ListeningSocket(void)
{
	 listen(socket_desc, 3);
	 puts("Waiting for incoming connections...");
	 int c = sizeof(struct sockaddr_in);
	 while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
	 {
	    puts("Connection accepted");
	    //Reply to the client
	    //drvTCP_SendInfo();
	 }

}

void drvTCP_SendInfo(void)
{
	char message[256];
	sprintf(message, "Active Channels: 0x%02x\n", drvSTM_getSettings()->ActiveChannel);
	//write(new_socket, message, strlen(message));
	drvTCP_SendData(message, strlen(message));
	printf("%s", message);
}

void drvTCP_SendData(const void* data, uint16_t data_length_b)
{
	unsigned char bytes[4];
	bytes[0] = (data_length_b >> 24) & 0xFF;
	bytes[1] = (data_length_b >> 16) & 0xFF;
	bytes[2] = (data_length_b >> 8) & 0xFF;
	bytes[3] = data_length_b & 0xFF;
	write(new_socket, bytes, 4);
	write(new_socket, data, data_length_b);
}

void drvTCP_ReadData(char *data)
{
	recv(new_socket, data, 1, 0);
}

void drvTCP_Loop(void)
{
	char data[100];
	char command[] = "Start\n";
	int data_size = recv(new_socket, data, 100, 0);
	if(data_size>0)
	{
		if(strcmp(data,command))
		{
			start_command_state = 1;
		}
	}
}

uint8_t drvTCP_StartCommand(void)
{
	return start_command_state;
}
