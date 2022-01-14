#include <iostream>
#include <winsock2.h>
#include <ctime>
#pragma warning(disable: 4996)
#pragma comment (lib,"Ws2_32.lib")
using namespace std;

DWORD WINAPI MyThreadFunction(LPVOID TemporarySock);

int main()
{
	WSADATA wsa;
	cout << "Initialising Winsock...";
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cout << ("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}
	cout << "Complete." << endl;

	cout << "Creating socket...";
	SOCKET AcceptingSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (AcceptingSocket == INVALID_SOCKET)
	{
		cout << "Failed";
		return -1;
	}
	cout << "Successful" << endl;

	sockaddr_in serv;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_family = AF_INET;
	serv.sin_port = htons(1234);
	bind(AcceptingSocket, (sockaddr*)&serv, sizeof(serv));
	listen(AcceptingSocket, SOMAXCONN);
	cout << "Awaiting for clients!";

	sockaddr_in from_serv;
	SOCKET TemporarySock;
	string ot;
	double otv;
	int len = sizeof(from_serv);
	while (1)
	{
		TemporarySock = accept(AcceptingSocket, (sockaddr*)&from_serv, &len);
		if (TemporarySock == 0)
		{
			cout << "ConnectionError";
			return -1;
		}
		cout << "New connection." << endl;
		DWORD clientId; // A 32-bit unsigned integer.
		CreateThread(NULL, 0, MyThreadFunction, &TemporarySock, 0, &clientId);
	}
	return 0;
}

DWORD WINAPI MyThreadFunction(LPVOID TemporarySock)
{
	srand(time(0));
	int ot;
	char in[] = "Majic sphere is greets you, do you need a prediction?(1-yes, 2-no)";
	SOCKET temp = ((SOCKET*)TemporarySock)[0];
	ot = send(temp, (char*)&in[0], sizeof(in), 0);
	int choice=1;
	while (choice == 1)
	{
		ot = recv(temp, (char*)&choice, sizeof(choice), 0);
		if (choice == 1)
		{
			int result = rand() % 4;
			if (result == 0)
			{
				char in[] = "Future is dark, ask later";
				ot = send(temp, (char*)&in[0], sizeof(in), 0);
			}
			if (result == 1)
			{
				char in[] = "Undoubtedly, yes";
				ot = send(temp, (char*)&in[0], sizeof(in), 0);
			}
			if (result == 2)
			{
				char in[] = "I do not believe in that";
				ot = send(temp, (char*)&in[0], sizeof(in), 0);
			}
			if (result == 3)
			{
				char in[] = "The signs discourage you";
				ot = send(temp, (char*)&in[0], sizeof(in), 0);
			}
		}
		else
		{
			cout << "Connection is lost";
			closesocket(temp);
		}
	}
	return 0;
};
