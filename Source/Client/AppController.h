#pragma once
#include "AppSocket.h"
#include "../ChatStruct/IncludeAll.h"


ref class AppController;



#include "LoginScreen.h"
#include "MainScreen.h"
#include "PrivateChatInfo.h"
//Singleton pattern

using namespace System::Threading;

ref class AppController
{
private:
	static AppController^ _instance = nullptr;
	AppController(); //Don't allow to create object
public:
	static AppController^ getObject();
	static Client::PrivateChat^ tempPrvChat;
	~AppController();
	AppSocket^ appSocket;
	Client::LoginScreen^ loginScreen = nullptr;
	Client::MainScreen^ mainScreen = nullptr;
	List<Client::PrivateChat^>^ lstPrivateChatForm = gcnew List<Client::PrivateChat^>();
	String^ strUsername;

	//static void ListenMessage(Object^ obj);
	System::Void ListenMessage();
	//void ListenMessage(Object^ obj);
	int createThreadListenMessageFromServer();

	int login(String^ _Username, String^ _Password);
	int logout();
	int signup(String^ _Username, String^ _Password);
	int sendPublicMessage(String^ _Message);
	int sendPrivateMessage(String^ _ToUsername, String^ _Message);
	int requestListOnlineUsers();
	int requestSendFile(String^ _ToUsername, String^ _FileName, int _iFileSize);
	int responseSendFile(String^ _ToUsername, bool _IsAccept);
	int sendPrivateFile(String^ _ToUsername, String^ _FileName, String^ _FilePath);


	// Set private message to suit form
	int setPrivateMessage(String^ _ToUsername, String^ _Message);

	//Others
	Client::PrivateChat^ getPrivateChatFormByFriendUsername(String^ _Username);
	//void getFileToSendInfoByFriendUsername(String^& _FileName, String^& _FilePath, int& _iFileSize, String^ _Username);
	static void threadPrivateChatForm(Object^ obj);
	Thread^ threadListenClient;
};

