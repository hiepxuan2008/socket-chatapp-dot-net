#include "ResponseLoginStruct.h"

ResponseLoginStruct::ResponseLoginStruct()
{
	IsSucc = false; //Not success
	errorMsg = nullptr;
}

array<Byte>^ ResponseLoginStruct::pack()
{
	List<Byte>^ byteData = gcnew List<Byte>();
	byteData->AddRange(BitConverter::GetBytes(int(ChatStruct::MessageType::ResponseLogin)));
	byteData->AddRange(BitConverter::GetBytes(IsSucc));

	if (errorMsg != nullptr)
	{
		byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(errorMsg))); //errorMsg length
		byteData->AddRange(Encoding::UTF8->GetBytes(errorMsg)); //errorMsg string
	}
	else
		byteData->AddRange(BitConverter::GetBytes(0));

	return byteData->ToArray();
}

ChatStruct^ ResponseLoginStruct::unpack(array<Byte>^ buff)
{
	int offset = 4;
	IsSucc = BitConverter::ToBoolean(buff, offset);
	offset += 1;
	int errorMsgLength = BitConverter::ToInt32(buff, offset);
	offset += 4;
	if (errorMsgLength > 0)
		errorMsg = Encoding::UTF8->GetString(buff, offset, errorMsgLength);

	return this;
}