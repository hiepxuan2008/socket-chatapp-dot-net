#include "ServerController.h"
#include "../ChatStruct/IncludeAll.h"

ServerController::ServerController()
{
	serverIPAddr = "127.0.0.1";
	serverPort = 2015;

	createSocket();
}

ServerController^ ServerController::getObject()
{
	if (_instance == nullptr)
	{
		_instance = gcnew ServerController();
	}

	return _instance;
}

ServerController::~ServerController()
{
	delete serverSocket;
}

int ServerController::createSocket()
{
	serverSocket = gcnew Socket(AddressFamily::InterNetwork,
		SocketType::Stream, ProtocolType::Tcp);

	return 0;
}

//Helper


bool ServerController::checkLogin(String^ _Username, String^ _Password, String^& errorMsg)
{
	//Check for blank!
	if (String::IsNullOrEmpty(_Username) || String::IsNullOrEmpty(_Password))
	{
		errorMsg = "Username or Password can't be blank!";
		return false;
	}

	//Check for special characters
	//String^ lstSpecialCharacters = "|"
	if (_Username->Contains("|") || _Username->Contains("|"))
	{
		errorMsg = "Username or password can't contain special characters!";
		return false;
	}

	//Check account in database
	if (!checkAccount(_Username, _Password))
	{
		errorMsg = "Username or Password is not correct!";
		return false;
	}

	//Check account in current online
	for each (String^ user in getListClient())
	{
		if (_Username == user)
		{
			errorMsg = user + " is current login on another client!";
			return false;
		}
	}

	return true;
}

bool ServerController::checkAccount(String^ _Username, String^ _Password)
{
	array<String^>^ lines = System::IO::File::ReadAllLines(accountPath);
	for each (String^ line in lines)
	{
		//MessageBox::Show(line);
		if (line == _Username + "|" + _Password)
		{
			return true;
		}
	}

	return false;
}

bool ServerController::checkSignup(String^ _Username, String^ _Password, String^& errorMsg)
{
	//Check for blank!
	if (String::IsNullOrEmpty(_Username) || String::IsNullOrEmpty(_Password))
	{
		errorMsg = "Username or Password can't be blank!";
		return false;
	}

	//Check for special characters
	//String^ lstSpecialCharacters = "|"
	if (_Username->Contains("|") || _Password->Contains("|"))
	{
		errorMsg = "Username or password can't contain special characters!";
		return false;
	}

	//Check exists username in database
	if (checkAccountExists(_Username))
	{
		errorMsg = "This username has been registered!";
		return false;
	}

	if (!addAnAccountToDatabase(_Username, _Password))
	{
		errorMsg = "Can't register!";
		return false;
	}

	return true;
}

bool ServerController::checkAccountExists(String^ _Username)
{
	array<String^>^ lines = System::IO::File::ReadAllLines(accountPath);
	for each (String^ line in lines)
	{
		//MessageBox::Show(line);
		if (line->Contains(_Username + "|"))
		{
			return true;
		}
	}

	return false;
}

bool ServerController::addAnAccountToDatabase(String^ _Username, String^ _Password)
{
	try
	{
		System::IO::File::AppendAllText(accountPath, _Username + "|" + _Password + "\n");
	}
	catch (Exception^ e)
	{
		return false;
	}
	return true;
}

bool ServerController::login(String^ _UserName, String^ _Password, Socket^ _ClientSocket)
{
	String^ errorMsg = "";
	if (checkLogin(_UserName, _Password, errorMsg))
	{
		lstClientInfo->Add(gcnew ClientInfo(_ClientSocket, _UserName));
		mainScreen->UpdateConnectedClient(getListClient()); //Update list connected

		mainScreen->AddTextToContent(_UserName + " hast just online!");
		loginResponse(true, errorMsg, _ClientSocket);
		mainScreen->UpdateConnectedClient(getListClient());
		sendLoginNotification(_UserName, _ClientSocket);

		return true; //Login successs
	}

	loginResponse(false, errorMsg, _ClientSocket);

	return false; //Error login
}

bool ServerController::signup(String^ _UserName, String^ _Password, Socket^ _ClientSocket)
{
	String^ errorMsg = "";
	if (checkSignup(_UserName, _Password, errorMsg))
	{
		signupResponse(true, errorMsg, _ClientSocket);
		mainScreen->UpdateClientList(getRegisteredClientList());

		return true; //Signup successs
	}
	signupResponse(false, errorMsg, _ClientSocket);

	return false; //Error sign up
}

void ServerController::signupResponse(bool _IsSucc, String^ errorMsg, Socket^ _ClientSocket)
{
	ResponseSignupStruct^ resSignup = gcnew ResponseSignupStruct;
	resSignup->IsSucc = _IsSucc;
	resSignup->errorMsg = errorMsg;
	array<Byte>^ buff = resSignup->pack();

	_ClientSocket->Send(buff); //Send the result to client.
}

void ServerController::userStatusResponse(Socket^ _ClientSocket)
{
	UserStatusStruct^ userStatusStruct = gcnew UserStatusStruct;
	userStatusStruct->lstOnlineUsers = getListClient()->ToArray();

	/*String^ debug = "";
	for each (String^ user in userStatusStruct->lstOnlineUsers)
	{
		debug += user;
	}
	MessageBox::Show(debug);*/

	array<Byte>^ buff = userStatusStruct->pack();
	_ClientSocket->Send(buff);
}

void ServerController::sendLoginNotification(String^ _Username, Socket^ _ClientSocket)
{
	LoginNotificationStruct^ loginNoti = gcnew LoginNotificationStruct;
	loginNoti->strUsername = _Username;
	array<Byte>^ buff = loginNoti->pack();

	for each (ClientInfo^ clientInfo in lstClientInfo)
	{
		if (clientInfo->clientSocket != _ClientSocket) //Send the others login notication
		{
			clientInfo->clientSocket->Send(buff);
		}
	}
}

void ServerController::sendLogoutNotification(Socket^ _ClientSocket)
{
	String^ clientUsername = getUsernameBySocket(_ClientSocket);
	LogoutNotificationStruct^ logoutNoti = gcnew LogoutNotificationStruct;
	logoutNoti->strUsername = clientUsername;
	array<Byte>^ buff = logoutNoti->pack();

	mainScreen->AddTextToContent(clientUsername + " hast just offline!");
	removeClientInfoByUsername(clientUsername);
	mainScreen->UpdateConnectedClient(getListClient()); //Update list connected

	for each (ClientInfo^ clientInfo in lstClientInfo)
	{
		if (clientInfo->clientSocket != _ClientSocket) //Send the others logout notication
		{
			clientInfo->clientSocket->Send(buff);
		}
	}
}

void ServerController::requestSendFile(String^ _ToUsername, String^ _FileName, int _iFileSize, Socket^ _ClientSocket)
{
	String^ sender = getUsernameBySocket(_ClientSocket);
	RequestSendFileStruct^ rqSendFileStruct = gcnew RequestSendFileStruct;
	rqSendFileStruct->strUsername = sender;
	rqSendFileStruct->strFileName = _FileName;
	rqSendFileStruct->iFileSize = _iFileSize;

	Socket^ receiver = getSocketByUsername(_ToUsername);
	array<Byte>^ byteData = rqSendFileStruct->pack();
	receiver->Send(byteData);
}

void ServerController::responseSendFile(String^ _ToUsername, bool _IsAccept, Socket^ _ClientSocket)
{
	String^ sender = getUsernameBySocket(_ClientSocket);
	ResponseSendFileStruct^ rpSendFileStruct = gcnew ResponseSendFileStruct;
	rpSendFileStruct->strUsername = sender;
	rpSendFileStruct->IsAccept = _IsAccept;

	Socket^ receiver = getSocketByUsername(_ToUsername);
	array<Byte>^ byteData = rpSendFileStruct->pack();
	receiver->Send(byteData);
}

void ServerController::sendPrivateFilePackage(String^ _ToUsername, String^ _Filename, int _iPackageNumber, int _TotalPackage, array<Byte>^ _bData, Socket^ _ClientSocket)
{
	String^ sender = getUsernameBySocket(_ClientSocket);
	PrivateFileStruct^ prvFileStruct = gcnew PrivateFileStruct;
	prvFileStruct->strUsername = sender;
	prvFileStruct->strFilename = _Filename;
	prvFileStruct->bData = _bData;
	prvFileStruct->iPackageNumber = _iPackageNumber;
	prvFileStruct->iTotalPackage = _TotalPackage;

	array<Byte>^ byteData = prvFileStruct->pack();
	Socket^ receiver = getSocketByUsername(_ToUsername);
	receiver->Send(byteData);
}

void ServerController::loginResponse(bool _IsSucc, String^ _errorMsg, Socket^ _ClientSocket)
{
	ResponseLoginStruct^ resLogin = gcnew ResponseLoginStruct;
	resLogin->IsSucc = _IsSucc;
	resLogin->errorMsg = _errorMsg;
	array<Byte>^ buff = resLogin->pack();

	_ClientSocket->Send(buff); //Send the result to client.
}

int ServerController::sendPublicMsgToClients(String^ _strMessage, Socket^ _ClientSocket)
{
	String^ username = getUsernameBySocket(_ClientSocket);
	String^ publicMsg = username + ": " + _strMessage;

	mainScreen->AddTextToContent(publicMsg);

	//MessageBox::Show(publicMsg);
	PublicMessageStruct^ pubMsgStruct = gcnew PublicMessageStruct;
	pubMsgStruct->strMessage = publicMsg;
	array<Byte>^ buff = pubMsgStruct->pack();

	for each (ClientInfo^ clientInfo in lstClientInfo)
	{
		//MessageBox::Show(clientInfo->clientSocket->RemoteEndPoint->ToString());
		try
		{
			//Why can't I send message to client?
			//Sent but don't process in Client???
			clientInfo->clientSocket->Send(buff);
		}
		catch (Exception^ e)
		{
			//Can't send message to this client
			MessageBox::Show(e->Message);
		}
	}

	return 0;
}

int ServerController::sendPrivateMessage(String^ _ToUsername, String^ _Message, Socket^ _SenderSocket)
{
	String^ sender = getUsernameBySocket(_SenderSocket);
	Socket^ receiverSocket = getSocketByUsername(_ToUsername);
	//If receiver is offline (nullptr)
	
	PrivateMessageStruct^ privateMessageStruct = gcnew PrivateMessageStruct;
	if (receiverSocket == nullptr)
	{
		//Send error message back to sender
		privateMessageStruct->strMessage = "Error: " + _ToUsername + " is offline!";
		privateMessageStruct->strToUsername = _ToUsername;
		array<Byte>^ byteData = privateMessageStruct->pack();
		_SenderSocket->Send(byteData);
	}
	else
	{
		privateMessageStruct->strMessage = sender + ": " + _Message;
		privateMessageStruct->strToUsername = sender;
		array<Byte>^ byteData = privateMessageStruct->pack();
		receiverSocket->Send(byteData);
	}

	return 0;
}

String^ ServerController::getUsernameBySocket(Socket^ _socket)
{
	for each (ClientInfo^ clientInfo in lstClientInfo)
	if (clientInfo->clientSocket == _socket)
		return clientInfo->strUsermame;

	return nullptr;
}

Socket^ ServerController::getSocketByUsername(String^ _username)
{
	for each (ClientInfo^ clientInfo in lstClientInfo)
	if (clientInfo->strUsermame == _username)
		return clientInfo->clientSocket;

	return nullptr;
}

void ServerController::removeClientInfoByUsername(String^ _username)
{
	for each (ClientInfo^ clientInfo in lstClientInfo)
	if (clientInfo->strUsermame == _username)
	{
		lstClientInfo->Remove(clientInfo);
		break;
	}
}

List<String^>^ ServerController::getListClient()
{
	List<String^>^ listClient = gcnew List<String^>;
	for each (ClientInfo^ clientInfo in lstClientInfo)
	{
		listClient->Add(clientInfo->strUsermame);
	}

	return listClient;
}

List<String^>^ ServerController::getRegisteredClientList()
{
	array<String^>^ lines = System::IO::File::ReadAllLines(accountPath);
	List<String^>^ listLines = gcnew List<String^>();
	for each (String^ line in lines)
	{
		
		listLines->Add(line->Substring(0, line->IndexOf("|")));
	}

	return listLines;
}