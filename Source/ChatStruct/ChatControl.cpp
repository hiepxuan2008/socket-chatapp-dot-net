#include "ChatControl.h"
#include "LoginStruct.h"
#include "PublicMessageStruct.h"
#include "ResponseLoginStruct.h"
#include "PrivateMessageStruct.h"
#include "SignupStruct.h"
#include "ResponseSignupStruct.h"
#include "UserStatusStruct.h"
#include "LoginNotificationStruct.h"
#include "LogoutNotificationStruct.h"
#include "PrivateFileStruct.h"
#include "RequestSendFileStruct.h"
#include "ResponseSendFileStruct.h"

ChatStruct^ ChatControl::unpack(array<Byte>^ buff)
{
	if (buff->Length == 0)
		return nullptr;

	ChatStruct^ result = nullptr; //The result
	ChatStruct::MessageType messageType = (ChatStruct::MessageType)BitConverter::ToInt32(buff, 0); //Read first 4 byte for messageType

	//
	switch (messageType)
	{
	case ChatStruct::MessageType::PublicMessage:
		result = gcnew PublicMessageStruct();
		result->messageType = ChatStruct::MessageType::PublicMessage;
		result->unpack(buff);
		//MessageBox::Show("Client received public message!");
		break;
	case ChatStruct::MessageType::PrivateMessage:
		result = gcnew PrivateMessageStruct();
		result->messageType = ChatStruct::MessageType::PrivateMessage;
		result->unpack(buff);
		break;
	case ChatStruct::MessageType::PrivateFile:
		result = gcnew PrivateFileStruct();
		result->messageType = ChatStruct::MessageType::PrivateFile;
		result->unpack(buff);
		break;
	case ChatStruct::MessageType::UserStatus:
		result = gcnew UserStatusStruct();
		result->messageType = ChatStruct::MessageType::UserStatus;
		result->unpack(buff);
		break;
	case ChatStruct::MessageType::RequestSendFile:
		result = gcnew RequestSendFileStruct();
		result->messageType = ChatStruct::MessageType::RequestSendFile;
		result->unpack(buff);
		break;
	case ChatStruct::MessageType::ResponseSendFile:
		result = gcnew ResponseSendFileStruct;
		result->messageType = ChatStruct::MessageType::ResponseSendFile;
		result->unpack(buff);
		break;
	case ChatStruct::MessageType::Login:
		result = gcnew LoginStruct(); //Login Unpack
		result->messageType = ChatStruct::MessageType::Login;
		result->unpack(buff); //Call Override function
		break;
	case ChatStruct::MessageType::ResponseLogin:
		result = gcnew ResponseLoginStruct();
		result->messageType = ChatStruct::MessageType::ResponseLogin;
		result->unpack(buff);
		break;
	case ChatStruct::MessageType::Signup:
		result = gcnew SignupStruct();
		result->messageType = ChatStruct::MessageType::Signup;
		result->unpack(buff);

		break;
	case ChatStruct::MessageType::ResponseSignup:
		result = gcnew ResponseSignupStruct();
		result->messageType = ChatStruct::MessageType::ResponseSignup;
		result->unpack(buff);

		break;
	case ChatStruct::MessageType::LoginNotification:
		result = gcnew LoginNotificationStruct();
		result->messageType = ChatStruct::MessageType::LoginNotification;
		result->unpack(buff);
		
		break;
	case ChatStruct::MessageType::LogoutNotification:
		result = gcnew LogoutNotificationStruct();
		result->messageType = ChatStruct::MessageType::LogoutNotification;
		result->unpack(buff);
		break;

	default:
		break;
	}

	return result;
}