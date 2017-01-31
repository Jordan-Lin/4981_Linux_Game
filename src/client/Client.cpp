#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <stdlib.h>

#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Client.h"


Client::Client()
:tcp_sockfd(0),
username(NULL),
chat_buffer(NULL)
{
	initClient();
}

Client::~Client()
{
	cleanup();
	if(username   != NULL) free(username);
	if(chat_buffer!= NULL) free(chat_buffer);
}

void Client::initClient()
{
	//allocate any memory as needed
	//try to connect
	//if successful, go to thread
}
void Client::readFromOutputQueue()
{

}

const char * Client::packetize(const int specifier, const char * msg)
{
	char * cbuff;
	int buffsize;

	//determine buff size
	switch(static_cast<P_SPECIFIER>(specifier))
	{
		case P_SPECIFIER::EXIT:
				cleanup();
				exit(0);
				break;
		case P_SPECIFIER::UNAME:
			buffsize = UNAME_BUFFSIZE;
			break;
		case P_SPECIFIER::CHAT:
			buffsize = CHAT_BUFFSIZE;
		break;
		default: // error encountered.
			std::cerr << "Error occured. Undecalred Specifier." << std::endl;
			return NULL;
	}

  //creating the packet
	cbuff = (char * )malloc(buffsize+1);
	//is message too long? Cut it short.
	if (static_cast<int>(strlen(msg)) >= buffsize)
	{
		memcpy(cbuff, msg, buffsize);
		cbuff[buffsize-1]= '\0';
	}
	else
	{
		memcpy(cbuff, msg, strlen(msg));
		memset(cbuff + strlen(msg),'\0', UNAME_BUFFSIZE-strlen(msg));
	}

	//writeTCPSocket(/*buff*/);
    //REMINDER : REMEMBER TO FREE CBUFF AFTER YOU ARE DONE WITH IT!!!
	//free(cbuff);
	return cbuff;

}

void Client::parseData(char * msg)
{

}

void Client::writeTCPSocket()
{

}

void Client::readTCPSocket()
{

}

void Client::handleError()
{

}

int Client::TCPConnect(const char * ip_addr)
{
	if (ip_addr == NULL || inet_addr(ip_addr) == 0 )
	{
		std::cerr << "Missing or Incorrect IP addr."  
			<< "\n IP Address must be in the form x.x.x.x" 
			<< std::endl ;
		return -1;
	}
	
	struct sockaddr_in serv_addr;
	int nread;

	memset(&serv_addr, '0', sizeof(struct sockaddr_in));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(TCP_PORT);
	serv_addr.sin_addr.s_addr = inet_addr(ip_addr);
	
	if ( (tcp_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
			perror("Error opening socket");
			exit(1);
	if((connect(tcp_sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in))) < 0)
			perror("Error Connecting");
			exit(1);
}


void Client::cleanup()
{
	//close fd
	// free memory 
	//join threads
}
