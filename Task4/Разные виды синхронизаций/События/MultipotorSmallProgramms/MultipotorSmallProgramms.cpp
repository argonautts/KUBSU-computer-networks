#include<windows.h>
#include<iostream>
using namespace std;

HANDLE hEvent1, hEvent2, newP;//дискриптор

DWORD WINAPI TR(LPVOID pr) {
	int i, num = 0;
	for (int j = 0; j < 5; j++)
	{
		WaitForSingleObject(hEvent2, INFINITE);
		for (i = 0; i < 5; i++) cout << "THREAD2" << endl;
		num++;
		SetEvent(hEvent1);
	}
	return 0;
}

int main() {
	DWORD thID;
	hEvent1 = CreateEvent(NULL, FALSE, TRUE, NULL);
	hEvent2 = CreateEvent(NULL, FALSE, FALSE, NULL);
	newP = CreateThread(NULL, 0, TR, NULL, 0, &thID);
	for (int i=0;i<5;i++)
	{
		WaitForSingleObject(hEvent1, INFINITE);
		for (int j = 0; j < 5; j++)cout << "THREAD1";
		SetEvent(hEvent2);
	}
	return 0;
}