#pragma once
using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Collections::Generic; //List
using namespace System::Threading; //Thread

ref class ClientInfo
{
public:
	Socket^ clientSocket = nullptr;
	String^ strUsermame = nullptr;

	ClientInfo();
	ClientInfo(Socket^ _clientSocket, String^ _strUsermame) : clientSocket(_clientSocket), strUsermame(_strUsermame){};
};

