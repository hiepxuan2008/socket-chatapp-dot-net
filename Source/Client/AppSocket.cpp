#include "AppSocket.h"


AppSocket::AppSocket()
{
	serverIPAddr = "127.0.0.1"; //Localhost IP
	serverPort = 2015; //Default server Port

	createSocket(); //Create a socket
}

AppSocket::AppSocket(String^ _ServerIPAddr, int _ServerPort)
{
	serverIPAddr = _ServerIPAddr;
	serverPort = _ServerPort;
}

int AppSocket::createSocket()
{
	clientSocket = gcnew Socket(AddressFamily::InterNetwork,
		SocketType::Stream, ProtocolType::Tcp);

	return 0;
}

int AppSocket::connectToServer(String^ _ServerIPAddr, int _ServerPort)
{
	serverIPAddr = _ServerIPAddr;
	serverPort = _ServerPort;
	return connectToServer();
}

int AppSocket::connectToServer()
{
	IPAddress^ ipAddress = IPAddress::Parse(serverIPAddr);
	IPEndPoint^ ServerIPEndPoint = gcnew IPEndPoint(ipAddress, serverPort);

	try
	{
		clientSocket->Connect(ServerIPEndPoint);
	}
	catch (Exception^ e)
	{
		MessageBox::Show(e->Message, "Error Connection",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		return 1; //Error
	}	

	return 0; 
}

int AppSocket::sendMessage(array<Byte>^ buff)
{
	if (clientSocket != nullptr)
		return clientSocket->Send(buff, buff->Length, SocketFlags::None); //Sent bytes

	return 0;
}

int AppSocket::sendMessage(array<Byte>^ buff, int size)
{
	return clientSocket->Send(buff, size, SocketFlags::None); //Sent bytes
}

void AppSocket::OnReceive(IAsyncResult^ ar)
{

}

void AppSocket::OnSend(IAsyncResult^ ar)
{

}