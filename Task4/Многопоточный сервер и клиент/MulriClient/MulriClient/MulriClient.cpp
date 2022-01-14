#include <iostream>
#include <winsock2.h>
#pragma warning(disable: 4996)
#pragma comment (lib,"Ws2_32.lib")
using namespace std;

int main()
{
	WSADATA wsa;
	cout << "Start initialization of library...";
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cout << "Failed";
		return -1;
	}
	cout << "Successfully"<<endl;

	cout << "Creating socket...";
	SOCKET ConnectingSock = socket(AF_INET, SOCK_STREAM, 0);
	if (ConnectingSock == INVALID_SOCKET)
	{
		cout << "Failed";
		return -1;
	}
	cout << "Successfully" << endl;
	sockaddr_in serverinf;
	serverinf.sin_family = AF_INET;
	serverinf.sin_port= htons(1234);
	serverinf.sin_addr.s_addr = inet_addr("127.0.0.1");

	cout << "Trying to connect...";
	if (connect(ConnectingSock, (sockaddr*)&serverinf, sizeof(serverinf))!=0)
	{
		cout<<"Failed:"<<WSAGetLastError;
			return -1;
	}
	cout << "Successfully"<<endl;
	
	int choice = 1;
	char buff[256];
	int in;
	in = recv(ConnectingSock, (char*)&buff[0], 256, 0);
	cout << buff << endl;;
	while (choice == 1)
	{
		cout << "Ask a question" << endl;
		cin >> choice;
		in = send(ConnectingSock, (char*)&choice, sizeof(choice), 0);
		cout << "Calculating..."<<endl;
		in = recv(ConnectingSock, (char*)&buff[0], 256, 0);
		cout << buff<<endl;
	}
	system("pause");
	return 0;
}