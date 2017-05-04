#include "PrivateFileStruct.h"

PrivateFileStruct::PrivateFileStruct()
{
	strUsername = nullptr;
	strFilename = nullptr;
	iPackageNumber = 0;
	iTotalPackage = 0;
	bData = nullptr;
	//iDataSize -
}

array<Byte>^ PrivateFileStruct::pack()
{
	List<Byte>^ byteData = gcnew List<Byte>();
	byteData->AddRange(BitConverter::GetBytes(int(ChatStruct::MessageType::PrivateFile)));

	//add Username info
	if (strUsername != nullptr)
	{
		byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(strUsername))); //Length of username
		byteData->AddRange(Encoding::UTF8->GetBytes(strUsername)); //Username string
	}
	else
		byteData->AddRange(BitConverter::GetBytes(0));


	//add Filename Info
	if (strFilename != nullptr)
	{
		byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(strFilename))); //Length of strFilename
		byteData->AddRange(Encoding::UTF8->GetBytes(strFilename)); //strFilename string
	}
	else
		byteData->AddRange(BitConverter::GetBytes(0));

	//file package number and total package info
	byteData->AddRange(BitConverter::GetBytes(iPackageNumber));
	byteData->AddRange(BitConverter::GetBytes(iTotalPackage));

	//Add data info
	byteData->AddRange(BitConverter::GetBytes(bData->Length));
	byteData->AddRange(bData);
	//Return
	return byteData->ToArray();
}

ChatStruct^ PrivateFileStruct::unpack(array<Byte>^ buff)
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
		strFilename = Encoding::UTF8->GetString(buff, offset, filenameLength);

	offset += filenameLength;
	iPackageNumber = BitConverter::ToInt32(buff, offset);
	offset += 4;
	iTotalPackage = BitConverter::ToInt32(buff, offset);
	offset += 4;
	
	int dataSize = BitConverter::ToInt32(buff, offset);
	offset += 4;
	if (dataSize > 0)
		System::Array::Copy(buff, offset, bData, 0, dataSize);

	return this;
}