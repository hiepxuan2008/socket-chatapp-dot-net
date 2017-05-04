#include "RequestSendFileStruct.h"

RequestSendFileStruct::RequestSendFileStruct()
{
	strUsername = nullptr;
	strFileName = nullptr;
	iFileSize = 0;
}

array<Byte>^ RequestSendFileStruct::pack()
{
	List<Byte>^ byteData = gcnew List<Byte>();
	byteData->AddRange(BitConverter::GetBytes(int(ChatStruct::MessageType::RequestSendFile)));

	//add Username info
	if (strUsername != nullptr)
	{
		byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(strUsername))); //Length of username
		byteData->AddRange(Encoding::UTF8->GetBytes(strUsername)); //Username string
	}
	else
		byteData->AddRange(BitConverter::GetBytes(0));


	//add FileName Info
	if (strFileName != nullptr)
	{
		byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(strFileName))); //Length of FileName
		byteData->AddRange(Encoding::UTF8->GetBytes(strFileName)); //FileName string
	}
	else
		byteData->AddRange(BitConverter::GetBytes(0));

	//add FileSize info
	byteData->AddRange(BitConverter::GetBytes(iFileSize));

	//Return
	return byteData->ToArray();
}

ChatStruct^ RequestSendFileStruct::unpack(array<Byte>^ buff)
{
	int offset = 4; //Skip messageType
	int usernameLength, filenameLength;

	usernameLength = BitConverter::ToInt32(buff, offset);
	offset += 4; //Update Offset
	if (usernameLength > 0)
		strUsername = Encoding::UTF8->GetString(buff, offset, usernameLength);

	offset += usernameLength; //Update offset

	filenameLength = BitConverter::ToInt32(buff, offset);
	offset += 4; //Update offset
	if (filenameLength > 0)
		strFileName = Encoding::UTF8->GetString(buff, offset, filenameLength);

	offset += filenameLength;
	iFileSize = BitConverter::ToInt32(buff, offset);

	return this;
}