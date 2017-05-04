#include "MainScreen.h"
#include "../ChatStruct/IncludeAll.h"
using namespace Server;

System::Void MainScreen::MainScreen_Load(System::Object^  sender, System::EventArgs^  e)
{
	ServerController^ serverController = ServerController::getObject();

	//Set default serverIPAddr, serverPort
	txtIPServer->Text = serverController->serverIPAddr;
	txtPortServer->Text = Convert::ToString(serverController->serverPort);

	UpdateClientList(serverController->getRegisteredClientList());
}

void MainScreen::ListenClientMessage(Object^ obj)
{
	Socket^ socket = (Socket^)obj;

	while (true)
	{
		try
		{
			array<Byte>^ buff = gcnew array<Byte>(1024);
			int recv = socket->Receive(buff);
			//MessageBox::Show("Received: " + Convert::ToString(recv) + " bytes from Client!");
			ChatStruct^ msgReceived = ChatControl::unpack(buff);

			switch (msgReceived->messageType)
			{
			case ChatStruct::MessageType::Login:
			{
												   LoginStruct^ loginStruct = (LoginStruct^)msgReceived;
												   ServerController::getObject()->login(loginStruct->strUsername, loginStruct->strPassword, socket);
												   break;
			}
			case ChatStruct::MessageType::PublicMessage:
			{
														   PublicMessageStruct^ pubMsgStr = (PublicMessageStruct^)msgReceived;
														   //MessageBox::Show("Sever recevied: " + pubMsg->strMessage);

														   ServerController::getObject()->sendPublicMsgToClients(pubMsgStr->strMessage, socket);
														   break;
			}
			case ChatStruct::MessageType::PrivateMessage:
			{
															PrivateMessageStruct^ privateMsgStr = (PrivateMessageStruct^)msgReceived;
															ServerController::getObject()->sendPrivateMessage(privateMsgStr->strToUsername, privateMsgStr->strMessage, socket);

															break;
			}
			case ChatStruct::MessageType::Signup:
			{
													SignupStruct^ signupStruct = (SignupStruct^)msgReceived;
													ServerController::getObject()->signup(signupStruct->strUsername, signupStruct->strPassword, socket);
													break;
			}
			case ChatStruct::MessageType::UserStatus:
			{
														ServerController::getObject()->userStatusResponse(socket);
														break;
			}
			case ChatStruct::MessageType::LogoutNotification:
			{
																//String^ username = ServerController::getObject()->getUsernameBySocket(socket);
																//ServerController::getObject()->mainScreen->AddTextToContent(username + " has just logouted!");
																ServerController::getObject()->sendLogoutNotification(socket);
																break;
			}
			case ChatStruct::MessageType::RequestSendFile:
			{
															 RequestSendFileStruct^ rqSendFileStruct = (RequestSendFileStruct^)msgReceived;
															 //MessageBox::Show("Server received\nUsername: " + rqSendFileStruct->strUsername + "\nFile name: " + rqSendFileStruct->strFileName + "\nFile size: " + Convert::ToString(rqSendFileStruct->iFileSize));
															 ServerController::getObject()->requestSendFile(rqSendFileStruct->strUsername, rqSendFileStruct->strFileName, rqSendFileStruct->iFileSize, socket);
															 break;
			}
			case ChatStruct::MessageType::ResponseSendFile:
			{
															  ResponseSendFileStruct^ rpSendFileStruct = (ResponseSendFileStruct^)msgReceived;
															  ServerController::getObject()->responseSendFile(rpSendFileStruct->strUsername, rpSendFileStruct->IsAccept, socket);
															  break;
			}
			case ChatStruct::MessageType::PrivateFile:
			{
														// MessageBox::Show("Server received: ");
														 PrivateFileStruct^ prvFileStruct = (PrivateFileStruct^)msgReceived;
														 ServerController::getObject()->sendPrivateFilePackage(prvFileStruct->strUsername, prvFileStruct->strFilename, prvFileStruct->iPackageNumber, prvFileStruct->iTotalPackage, prvFileStruct->bData, socket);
														 break;
			}

			default:
				break;
			}

		}
		catch (Exception^ e)
		{
			//Vào đây là mất kết nối với Client
			//lstConnectionSocket->Remove(socket);
			return; //Finish this thread
		}
	}

}

System::Void MainScreen::backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	Socket^ serverSocket = ServerController::getObject()->serverSocket;

	while (true)
	{
		Socket^ connectionSocket = serverSocket->Accept(); //Accept Connection From Client
		//lstConnectionSocket->Add(connectionSocket); //Add connection Socket to list

		threadListenClient = gcnew Thread(gcnew ParameterizedThreadStart(MainScreen::ListenClientMessage));
		threadListenClient->IsBackground = true;
		threadListenClient->Start(connectionSocket); //Listen messages from client

		//String^ announce = L"Kết nối " + connectionSocket->RemoteEndPoint->ToString();
		//AddTextToMainChat(announce);
	}

}

void MainScreen::AddTextToContent(String^ text)
{
	txtClientChatBox->AppendText(text);
	txtClientChatBox->AppendText("\n");
}

void MainScreen::UpdateConnectedClient(List<String^>^ lstClient) //
{
	txtConnected->Text = nullptr;
	for each (String^ user in lstClient)
	{
		txtConnected->AppendText(user);
		txtConnected->AppendText("\n");
	}
}

void MainScreen::UpdateClientList(List<String^>^ lstClient)
{
	txtConnected->Text = nullptr;
	for each (String^ user in lstClient)
	{
		txtClientList->AppendText(user);
		txtClientList->AppendText("\n");
	}
}

System::Void MainScreen::btListen_Click(System::Object^  sender, System::EventArgs^  e)
{
	ServerController^ serverController = ServerController::getObject();

	//Listen 
	IPAddress^ serverIPAddress = IPAddress::Parse(serverController->serverIPAddr);
	int serverPort = serverController->serverPort;
	IPEndPoint^ serverIPEndPoint = gcnew IPEndPoint(serverIPAddress, serverPort);

	serverController->serverSocket->Bind(serverIPEndPoint);
	serverController->serverSocket->Listen(10);

	backgroundWorker1->WorkerSupportsCancellation = true;
	backgroundWorker1->RunWorkerAsync();

	//Disable this button
	btListen->Enabled = false;
	txtIPServer->ReadOnly = true;
	txtPortServer->ReadOnly = true;
}