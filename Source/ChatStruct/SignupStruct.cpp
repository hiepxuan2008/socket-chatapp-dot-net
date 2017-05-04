#include "SignupStruct.h"

SignupStruct::SignupStruct()
{
	strUsername = nullptr;
	strPassword = nullptr;
}

array<Byte>^ SignupStruct::pack()
{
	List<Byte>^ byteData = gcnew List<Byte>();
	byteData->AddRange(BitConverter::GetBytes(int(ChatStruct::MessageType::Signup)));

	//add Username info
	if (strUsername != nullptr)
	{
		byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(strUsername))); //Length of username
		byteData->AddRange(Encoding::UTF8->GetBytes(strUsername)); //Username string
	}
	else
		byteData->AddRange(BitConverter::GetBytes(0));


	//add Password Info
	if (strPassword != nullptr)
	{
		byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(strPassword))); //Length of password
		byteData->AddRange(Encoding::UTF8->GetBytes(strPassword)); //Password string
	}
	else
		byteData->AddRange(BitConverter::GetBytes(0));

	//Return
	return byteData->ToArray();
}

ChatStruct^ SignupStruct::unpack(array<Byte>^ buff)
{
	int offset = 4; //Skip messageType
	int usernameLength, passwordLength;

	usernameLength = BitConverter::ToInt32(buff, offset);
	offset += 4; //Update Offset
	if (usernameLength > 0)
		strUsername = Encoding::UTF8->GetString(buff, offset, usernameLength);

	offset += usernameLength; //Update offset

	passwordLength = BitConverter::ToInt32(buff, offset);
	offset += 4; //Update offset
	if (passwordLength > 0)
		strPassword = Encoding::UTF8->GetString(buff, offset, passwordLength);

	return this;
}