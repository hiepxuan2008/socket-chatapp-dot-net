#pragma once
using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Windows::Forms;
using namespace System::Runtime::Serialization;
using namespace System::Collections::Generic; //List
using namespace System::Text; //Encoding

ref class AppSocket
{
private:
	String^ serverIPAddr;
	int serverPort;

public:
	Socket^ clientSocket;

	AppSocket();
	AppSocket(String^ _ServerIPAddr, int _ServerPort);
	int createSocket();
	int connectToServer();
	int connectToServer(String^ _ServerIPAddr, int _ServerPort);
	int sendMessage(array<Byte>^ buff);
	int sendMessage(array<Byte>^ buff, int size);
	void OnReceive(IAsyncResult^ ar);
	void OnSend(IAsyncResult^ ar);
};

