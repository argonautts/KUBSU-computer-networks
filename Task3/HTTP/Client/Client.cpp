#include <iostream>
#include "winsock2.h"
#pragma comment (lib, "Ws2_32.lib")
#pragma warning(disable: 4996)
#define getHttp "GET / HTTP/1.0 \r\nHost:example.com\r\n\r\n"
//HTTP запрос
using namespace std;
int main()
{
	WSADATA wsa;
	cout << ("Initialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cout << ("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}
	cout << "Complete." << endl;

	cout << "Creating socket...";
	SOCKET KlientSock = socket(AF_INET, SOCK_STREAM, 0);
	if (KlientSock == INVALID_SOCKET)
	{
		cout << "Failed.";
		return -1;
	}
	cout << "Complete." << endl;

	cout << "Getting address...";
	hostent* ht;
	ht = gethostbyname("example.com");
	if (ht == NULL)
	{
		return -1;
	}
	cout << "Successfully." << endl;

	sockaddr_in nosoc;
	nosoc.sin_family = AF_INET;
	nosoc.sin_port = htons(80);
	nosoc.sin_addr.s_addr = *((unsigned long*)ht->h_addr);

	cout << "Start connection to server...";
	if (connect(KlientSock, (sockaddr*)&nosoc, sizeof(nosoc)) != 0)
	{
		cout << "Failed.";
		return -1;
	}
	cout << "Complete!" << endl;

	cout << "Send request..." << endl;
	if (send(KlientSock, (char*)&getHttp, sizeof(getHttp), 0) == SOCKET_ERROR)
	{
		return -1;
	}

	cout << "Awaiting request..." << endl;
	char buff[10000]; int len;
	do {
		if (SOCKET_ERROR == (len = recv(KlientSock, (char*)&buff, 4096, 0)))//чтение входящих данных
		{
			int res = WSAGetLastError(); return -1;
		}
		for (int i = 0; i < len; i++)
			cout << buff[i];
	} while (len != 0);

	closesocket(KlientSock);
	cin.get();
	return 0;
}