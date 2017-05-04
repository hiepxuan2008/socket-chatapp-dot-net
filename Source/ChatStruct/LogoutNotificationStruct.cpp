#include "LogoutNotificationStruct.h"

LogoutNotificationStruct::LogoutNotificationStruct()
{
	strUsername = nullptr;
}

array<Byte>^ LogoutNotificationStruct::pack()
{
	List<Byte>^ byteData = gcnew List<Byte>();
	byteData->AddRange(BitConverter::GetBytes(int(ChatStruct::MessageType::LogoutNotification)));

	//add Username info
	if (strUsername != nullptr)
	{
		byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(strUsername))); //Length of username
		byteData->AddRange(Encoding::UTF8->GetBytes(strUsername)); //Username string
	}
	else
		byteData->AddRange(BitConverter::GetBytes(0));

	//Return
	return byteData->ToArray();
}

ChatStruct^ LogoutNotificationStruct::unpack(array<Byte>^ buff)
{
	int offset = 4; //Skip messageType
	int usernameLength;

	usernameLength = BitConverter::ToInt32(buff, offset);
	offset += 4; //Update Offset
	if (usernameLength > 0)
		strUsername = Encoding::UTF8->GetString(buff, offset, usernameLength);

	return this;
}