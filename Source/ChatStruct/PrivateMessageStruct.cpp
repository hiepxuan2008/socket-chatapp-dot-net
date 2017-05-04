#include "PrivateMessageStruct.h"

PrivateMessageStruct::PrivateMessageStruct()
{
	strToUsername = nullptr;
	strMessage = nullptr;
}

array<Byte>^ PrivateMessageStruct::pack()
{
	List<Byte>^ byteData = gcnew List<Byte>();
	byteData->AddRange(BitConverter::GetBytes(int(ChatStruct::MessageType::PrivateMessage)));

	//add Username info
	if (strToUsername != nullptr)
	{
		byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(strToUsername))); //Length of username
		byteData->AddRange(Encoding::UTF8->GetBytes(strToUsername)); //Username string
	}
	else
		byteData->AddRange(BitConverter::GetBytes(0));


	//add Message Info
	if (strMessage != nullptr)
	{
		byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(strMessage))); //Length of message
		byteData->AddRange(Encoding::UTF8->GetBytes(strMessage)); //message string
	}
	else
		byteData->AddRange(BitConverter::GetBytes(0));

	//Return
	return byteData->ToArray();
}

ChatStruct^ PrivateMessageStruct::unpack(array<Byte>^ buff)
{
	int offset = 4; //Skip messageType
	int usernameLength, messageLength;

	usernameLength = BitConverter::ToInt32(buff, offset);
	offset += 4; //Update Offset
	if (usernameLength > 0)
		strToUsername = Encoding::UTF8->GetString(buff, offset, usernameLength);

	offset += usernameLength; //Update offset

	messageLength = BitConverter::ToInt32(buff, offset);
	offset += 4; //Update offset
	if (messageLength > 0)
		strMessage = Encoding::UTF8->GetString(buff, offset, messageLength);

	return this;
}