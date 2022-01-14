#include "winsock2.h"
#include <sstream>
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma warning(disable: 4996)  
#pragma comment (lib, "Ws2_32.lib")
using namespace std;

int main() {
	WSADATA wsa;
	cout << "Initialising Winsock...";
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cout << ("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}
	cout << "Complete." << endl;

	cout << "Creating struct for adress and binding it to an adress...";
	addrinfo* Prinim = NULL;
	addrinfo Tecush;
	ZeroMemory(&Tecush, sizeof(Tecush));
	Tecush.ai_family = AF_INET;
	Tecush.ai_socktype = SOCK_STREAM;
	Tecush.ai_flags = AI_PASSIVE;
	Tecush.ai_protocol = IPPROTO_TCP;


	if (getaddrinfo("127.0.0.1", "9999", &Tecush, &Prinim) != 0)//localhost:9999
	{
		cout << "Failed";
		return -1;
	}
	cout << "Successful" << endl;


	cout << "Creating socket...";
	SOCKET AcceptingSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (AcceptingSocket == INVALID_SOCKET)
	{
		cout << "Failed";
		return -1;
	}
	cout << "Successful" << endl;


	cout << "Bindind the socket to IP adress...";
	if (bind(AcceptingSocket, Prinim->ai_addr, Prinim->ai_addrlen) == INVALID_SOCKET)
	{
		cout << "Failed";
		return -1;
	}
	cout << "Successful" << endl;


	cout << "Set listening to socket...";
	if (listen(AcceptingSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		cerr << "Failded";
		return -1;
	}

	cout << "Successful";
	char buf[4096];
	while (true)
	{
		cout << "Awaiting for accept...";
		int CurrentSocket = accept(AcceptingSocket, NULL, NULL);
		if (CurrentSocket == INVALID_SOCKET)
		{
			cout << "Failed somehow";
			return -1;
		}
		cout << "New connection!";

		int in;
		in = recv(CurrentSocket, buf, 4096, 0);
		if (in == -1)
		{
			cout << "Didn't get it";
			closesocket(CurrentSocket);
		}

		if (in == 0)
		{
			cout << "It's empty!";
			closesocket(CurrentSocket);
		}

		if (in > 0)
		{
			buf[in] = '\0';
			cout << "Recived the data! :3" << endl;
			std::stringstream response;
			std::stringstream response_body;

			response_body << "<title>Kozin Alexandr</title>\n"
				<< "<h1>Test HTTP C++ Server</h1>\n"
				<< "<p>Hello World!</p>\n"
				<< "<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer ac posuere tortor, id lobortis nisl. Fusce lacus erat, pretium vehicula scelerisque eu, lacinia sed leo. Phasellus eleifend feugiat tortor et malesuada. Sed sit amet egestas tellus. Curabitur arcu nisl, feugiat ultrices efficitur ac, ultrices non ante. Nulla eu ante malesuada, facilisis risus in, efficitur mi. Nulla feugiat pulvinar sem. Aenean ornare, leo ut egestas finibus, risus ligula consequat quam, nec cursus dolor quam id mauris. Curabitur ac est odio. Etiam eget leo at arcu tincidunt interdum. Aenean euismod eros et rhoncus accumsan. Donec vulputate nisl leo, eget ultricies lectus suscipit eu.</p>\n"
				<< "<p>Fusce sollicitudin pulvinar augue, non consectetur lorem. Fusce sollicitudin purus convallis cursus pharetra. Quisque tincidunt in lectus id bibendum. Donec faucibus metus ac feugiat volutpat. Vivamus mattis consequat nisl ut placerat. Integer nec ornare turpis. Phasellus rutrum scelerisque diam, in tincidunt odio tincidunt sed. Proin sapien enim, blandit eget urna sit amet, pulvinar varius leo. Praesent tincidunt a est non tempor. Integer a finibus libero, eget interdum mauris. Mauris hendrerit molestie gravida.</p>\n"
				<< "<p>Aliquam eleifend, mi at elementum volutpat, enim urna luctus libero, eget sodales nunc odio ac tortor. Duis iaculis ligula eget massa elementum ultricies. Phasellus at libero vulputate, consectetur diam quis, blandit mauris. Aliquam vitae magna eget est egestas lacinia vitae nec purus. Integer elit lacus, sodales vel velit et, vulputate fermentum leo. Quisque fringilla, tortor id cursus commodo, sem justo vestibulum ligula, ac ullamcorper neque lectus vel lacus. Aliquam vitae dui neque. Sed vel tincidunt quam. Proin metus velit, laoreet eu velit sed, dictum malesuada erat. Nam convallis ante sed rutrum rhoncus. Nullam hendrerit, massa sollicitudin sagittis bibendum, ex nulla iaculis leo, a ultrices dolor ex sit amet metus. Aenean eget dolor tempus, vestibulum erat et, dignissim leo. Quisque dapibus nunc erat, porta vehicula lorem luctus at.</p>\n";
			
			response << "HTTP/1.1 200 OK\r\n"
				<< "Version: HTTP/1.1\r\n"
				<< "Content-Type: text/html; charset=utf-8\r\n"
				<< "Content-Length: " << response_body.str().length()
				<< "\r\n\r\n"
				<< response_body.str();

			in = send(CurrentSocket, response.str().c_str(), response.str().length(), 0);
			if (in == -1)
			{
				cout << "Can't send the data :(";
			}
			closesocket(CurrentSocket);
		}
	}
	return 0;
}