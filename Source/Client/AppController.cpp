#include "AppController.h"
#define NULL 0
using namespace System::IO;

AppController::AppController() //Don't allow to create object
{
	appSocket = gcnew AppSocket();
}

AppController::~AppController()
{
	delete appSocket;
}

AppController^ AppController::getObject()
{
	if (_instance == nullptr)
	{
		_instance = gcnew AppController();
	}
	return _instance;
}

System::Void AppController::ListenMessage()
{
	while (true)
	{
		//Console::WriteLine("Sax");
		array<Byte>^ buff = gcnew array<Byte>(1024);
		Socket^ clientSocket = AppController::getObject()->appSocket->clientSocket;
		int revc;
		try
		{
			revc = clientSocket->Receive(buff);
		}
		catch (Exception^ e)
		{
			MessageBox::Show("Server has just disconnected!");
			AppController::getObject()->appSocket->clientSocket = nullptr;
			Application::Exit();
		}
		
		ChatStruct^ msgReceived = ChatControl::unpack(buff);
		//MessageBox::Show("Client Received " + revc + " bytes");
		switch (msgReceived->messageType)
		{
		case ChatStruct::MessageType::Login:
			MessageBox::Show("Login Message?");
			break;
		case ChatStruct::MessageType::ResponseLogin:
		{
													   ResponseLoginStruct^ resLoginStruct = (ResponseLoginStruct^)msgReceived;
													   if (resLoginStruct->IsSucc)
													   {
														   AppController::getObject()->loginScreen->Hide();
														   //Create new form
														   AppController::getObject()->mainScreen = gcnew Client::MainScreen;
														   //AppController::getObject()->mainScreen->Show();
														   Application::Run(AppController::getObject()->mainScreen);
													   }
													   else
													   {
														   MessageBox::Show(resLoginStruct->errorMsg);
													   }

													   break;
		}
		case ChatStruct::MessageType::PublicMessage:
		{
													   PublicMessageStruct^ publicMessageStruct = (PublicMessageStruct^)msgReceived;
													   AppController::getObject()->mainScreen->AddTextToContent(publicMessageStruct->strMessage);

													   break;
		}
		case ChatStruct::MessageType::PrivateMessage:
		{
														PrivateMessageStruct^ privateMsgStruct = (PrivateMessageStruct^)msgReceived;
														AppController::getObject()->setPrivateMessage(privateMsgStruct->strToUsername, privateMsgStruct->strMessage);
														break;
		}
		case ChatStruct::MessageType::ResponseSignup:
		{
														ResponseSignupStruct^ resSignUpStruct = (ResponseSignupStruct^)msgReceived;
														if (resSignUpStruct->IsSucc)
														{
															MessageBox::Show("Congratulation! You registered successfully!");
														}
														else
														{
															MessageBox::Show(resSignUpStruct->errorMsg);
														}
														break;
		}
		case ChatStruct::MessageType::Signup:
		{
												MessageBox::Show("Sign up received?");
												break;
		}
		case ChatStruct::MessageType::UserStatus:
		{
													//MessageBox::Show("Client Received: online users list");
													UserStatusStruct^ userStaStruct = (UserStatusStruct^)msgReceived;
													AppController::getObject()->mainScreen->SetOnlineUsers(userStaStruct->lstOnlineUsers);
													break;
		}
		case ChatStruct::MessageType::LoginNotification:
		{
														   LoginNotificationStruct^ logNoti = (LoginNotificationStruct^)msgReceived;
														   AppController::getObject()->mainScreen->AddTextToContent(logNoti->strUsername + " has just online!");
														   AppController::getObject()->mainScreen->AddAnOnlineUser(logNoti->strUsername);
														   break;
		}
		case ChatStruct::MessageType::LogoutNotification:
		{
															LogoutNotificationStruct^ logOut = (LogoutNotificationStruct^)msgReceived;
															//MessageBox::Show("sax");
															//MessageBox::Show("Username: " + logOut->strUsername);
															AppController::getObject()->mainScreen->AddTextToContent(logOut->strUsername + " has just offline!");
															AppController::getObject()->mainScreen->DeleteAnOnlineUser(logOut->strUsername);
															break;
		}
		case ChatStruct::MessageType::RequestSendFile:
		{
														 RequestSendFileStruct^ rqSendFileStruct = (RequestSendFileStruct^)msgReceived;
														 if (MessageBox::Show(rqSendFileStruct->strUsername + " want to send you a file " + 
																			  rqSendFileStruct->strFileName + " (" + Convert::ToString(rqSendFileStruct->iFileSize) +
																			  " bytes).\nDo you want to receive?", "Receive a file", MessageBoxButtons::YesNo) == DialogResult::Yes)
														 {
															 AppController::getObject()->responseSendFile(rqSendFileStruct->strUsername, true);
														 }
														 else
														 {
															 AppController::getObject()->responseSendFile(rqSendFileStruct->strUsername, false);
														 }
														 break;

		}
		case ChatStruct::MessageType::ResponseSendFile:
		{
														  ResponseSendFileStruct^ rpSendFileStruct = (ResponseSendFileStruct^)msgReceived;
														  Client::PrivateChat^ prvChat = getPrivateChatFormByFriendUsername(rpSendFileStruct->strUsername);
														  if (rpSendFileStruct->IsAccept)
														  {
															  //tempPrvChat = AppController::getPrivateChatFormByFriendUsername(rpSendFileStruct->strUsername);
															  setPrivateMessage(rpSendFileStruct->strUsername, rpSendFileStruct->strUsername + " accept a file "
																  + prvChat->fileNameToSend + " (" + Convert::ToString(prvChat->fileSizeToSend) + " bytes) from you!");

															  sendPrivateFile(prvChat->strFriendUsername, prvChat->fileNameToSend, prvChat->filePathToSend);
														  }
														  else
														  {

															  setPrivateMessage(rpSendFileStruct->strUsername, rpSendFileStruct->strUsername + " don't accept to receive file "
																  + prvChat->fileNameToSend + " (" + Convert::ToString(prvChat->fileSizeToSend) + " bytes) from you!");
														  }

														  //Change listen Message to non-static method.
														  //Send file thread


														  break;
		}
		case ChatStruct::MessageType::PrivateFile:
		{
													 //MessageBox::Show("Received");
													 PrivateFileStruct^ prvFileStruct = (PrivateFileStruct^)msgReceived;
													 Client::PrivateChat^ prvChat = getPrivateChatFormByFriendUsername(prvFileStruct->strUsername);
													 if (prvFileStruct->iPackageNumber == 1)
														 prvChat->writerStream = gcnew FileStream(prvChat->pathFileToReceiver + "/" + prvFileStruct->strFilename, FileMode::Create, FileAccess::Write);

													 prvChat->writerStream->Write(prvFileStruct->bData, 0, prvFileStruct->bData->Length);
													 setPrivateMessage(prvFileStruct->strUsername, "Received: " + prvFileStruct->iPackageNumber + "/" + prvFileStruct->iTotalPackage); 

													 break;
		}

		default:
			break;
		}
	}
}

int AppController::createThreadListenMessageFromServer()
{
	//Thread^ thread = gcnew Thread(gcnew ParameterizedThreadStart(AppController::ListenMessage));
	//thread->IsBackground = true;
	//thread->Start(0); //Listen messages from server
	Thread^ newThread = gcnew Thread(gcnew ThreadStart(this, &AppController::ListenMessage));
	newThread->SetApartmentState(ApartmentState::STA);
	newThread->Start();

	return 0;
}

int AppController::login(String^ _Username, String^ _Password)
{
	LoginStruct^ loginStruct = gcnew LoginStruct();
	loginStruct->strUsername = _Username;
	loginStruct->strPassword = _Password;

	array<Byte>^ byteData = loginStruct->pack();
	appSocket->sendMessage(byteData);

	return 0;
}

int AppController::logout()
{
	LogoutNotificationStruct^ logOut = gcnew LogoutNotificationStruct;
	
	array<Byte>^ byteData = logOut->pack();
	appSocket->sendMessage(byteData);

	return 0;
}

int AppController::signup(String^ _Username, String^ _Password)
{
	SignupStruct^ signupStruct = gcnew SignupStruct();
	signupStruct->strUsername = _Username;
	signupStruct->strPassword = _Password;

	array<Byte>^ byteData = signupStruct->pack();
	appSocket->sendMessage(byteData);

	return 0;
}

int AppController::sendPublicMessage(String^ _Message)
{
	PublicMessageStruct^ publicMessageStruct = gcnew PublicMessageStruct;
	publicMessageStruct->strMessage = _Message;

	array<Byte>^ byteData = publicMessageStruct->pack();

	appSocket->sendMessage(byteData);

	return 0;
}

int AppController::sendPrivateMessage(String^ _ToUsername, String^ _Message)
{
	PrivateMessageStruct^ privateMessageStruct = gcnew PrivateMessageStruct;
	privateMessageStruct->strToUsername = _ToUsername;
	privateMessageStruct->strMessage = _Message;

	array<Byte>^ byteData = privateMessageStruct->pack();
	appSocket->sendMessage(byteData);

	return 0;
}

int AppController::requestListOnlineUsers()
{
	UserStatusStruct^ userStatusStruct = gcnew UserStatusStruct;
	array<Byte>^ byteData = userStatusStruct->pack();
	appSocket->sendMessage(byteData);

	return 0;
}

int AppController::requestSendFile(String^ _ToUsername, String^ _FileName, int _iFileSize)
{
	RequestSendFileStruct^ rqSendFileStruct = gcnew RequestSendFileStruct;
	rqSendFileStruct->strFileName = _FileName;
	rqSendFileStruct->strUsername = _ToUsername;
	rqSendFileStruct->iFileSize = _iFileSize;
	array<Byte>^ byteData = rqSendFileStruct->pack();
	appSocket->sendMessage(byteData);

	return 0;
}

int AppController::responseSendFile(String^ _ToUsername, bool _IsAccept)
{
	ResponseSendFileStruct^ rpSendFileStruct = gcnew ResponseSendFileStruct;
	rpSendFileStruct->strUsername = _ToUsername;
	rpSendFileStruct->IsAccept = _IsAccept;
	array<Byte>^ byteData = rpSendFileStruct->pack();
	appSocket->sendMessage(byteData);

	return 0;
}

int AppController::sendPrivateFile(String^ _ToUsername, String^ _FileName, String^ _FilePath)
{
	PrivateFileStruct^ prvFileStruct = gcnew PrivateFileStruct;
	prvFileStruct->strFilename = _FileName;
	prvFileStruct->strUsername = _ToUsername;
	//Spit to smaller packages to send to server
	
	array<Byte>^ buffer;

	FileStream^ fileStream = nullptr;
	//FileStream^ writeSteam = nullptr;
	try
	{
		fileStream = gcnew FileStream(_FilePath, FileMode::Open, FileAccess::Read);
		//writeSteam = gcnew FileStream("Debug/" + _FilePath, FileMode::Create, FileAccess::Write);

		int length = (int)fileStream->Length;  // get file length
		buffer = gcnew array<Byte>(length);            // create buffer

		int count;                            // actual number of bytes read
		int sum = 0;                          // total number of bytes read

		// read until Read method returns 0 (end of the stream has been reached)
		while ((count = fileStream->Read(buffer, sum, length - sum)) > 0)
		{
			sum += count;  // sum is a buffer offset for next reading
		}

		int BUFF_SIZE = 512;
		int counter = 0;
		int curPackageNumber = 1;
		int iTotalPackage = sum / (BUFF_SIZE + 1) + 1;
		
		//Console::WriteLine("Start send file: ");
		for (; curPackageNumber <= iTotalPackage; ++curPackageNumber)
		{
			//System::Array::Copy(buffer, counter, bData, BUFF_SIZE);
			int copyLength = counter + BUFF_SIZE < sum ? BUFF_SIZE : (sum % BUFF_SIZE);
			array<Byte>^ bData = gcnew array<Byte>(copyLength);
			Console::WriteLine(copyLength);
			System::Array::Copy(buffer, counter, bData, 0, copyLength);
			counter += BUFF_SIZE;

			prvFileStruct->iPackageNumber = iTotalPackage;
			prvFileStruct->iTotalPackage = iTotalPackage;
			prvFileStruct->bData = bData;
			array<Byte>^ byteData = prvFileStruct->pack();
			appSocket->sendMessage(byteData);
			//MessageBox::Show("Debug");
			setPrivateMessage(_ToUsername, "Sent: " + curPackageNumber + "/" + iTotalPackage);

			//writeSteam->Write(bData, 0, copyLength);
		}
		//Console::WriteLine("End of sending file");

	}
	catch (Exception^ e)
	{
		Console::WriteLine(e->Message);
	}
	finally
	{
		if (fileStream != nullptr)
			fileStream->Close();
	}


	return 0;
}

int AppController::setPrivateMessage(String^ _ToUsername, String^ _Message)
{
	Client::PrivateChat^ prvChatForm = getPrivateChatFormByFriendUsername(_ToUsername);
	if (prvChatForm != nullptr)
	{
		prvChatForm->AddTextToDisplayChatbox(_Message);
	}
	else
	{
		Client::PrivateChat^ pChat = gcnew Client::PrivateChat(strUsername, _ToUsername);
		lstPrivateChatForm->Add(pChat);
		setPrivateMessage(_ToUsername, _Message); //Re set private message

		Application::Run(pChat);
		//threadListenClient = gcnew Thread(gcnew ParameterizedThreadStart(AppController::threadPrivateChatForm));
		//threadListenClient->IsBackground = true;
		//threadListenClient->Start(pChat);
	}

	return 0;
}

Client::PrivateChat^ AppController::getPrivateChatFormByFriendUsername(String^ _Username)
{
	for each (Client::PrivateChat^ prvChat in lstPrivateChatForm)
	{
		if (prvChat->strFriendUsername == _Username)
			return prvChat;
	}

	return nullptr; //not found
}

void AppController::threadPrivateChatForm(Object^ obj)
{
	MessageBox::Show("Debug thread");
	//How can I know my friend chat username. -> Solved!
	Client::PrivateChat^ pChat = (Client::PrivateChat^)obj;
	//Application::Run(pChat);
	//createThreadListenMessageFromServer();
	//MessageBox::Show("Debug");
	pChat->Show();
	MessageBox::Show("End Debug thread");
}