#pragma once
#include <WinSock2.h>
#include <process.h>
#include <vector>

#define MAX_BUFFER_SIZE 1024

void NetworkStart();
void NetworkEnd();

void ReceiveThread(void* params);
void ErrorDisplay(wchar_t *szError);
void SendChatMsg(wchar_t* message);


