#include "PublicMessageStruct.h"

PublicMessageStruct::PublicMessageStruct()
{
	strMessage = nullptr;
}

array<Byte>^ PublicMessageStruct::pack()
{
	List<Byte>^ byteData = gcnew List<Byte>();
	byteData->AddRange(BitConverter::GetBytes(int(ChatStruct::MessageType::PublicMessage)));

	//add Message info
	if (strMessage != nullptr)
	{
		int lengthMessage = Encoding::UTF8->GetByteCount(strMessage);
		byteData->AddRange(BitConverter::GetBytes(lengthMessage)); //Length of Message
		byteData->AddRange(Encoding::UTF8->GetBytes(strMessage)); //Message string
	}
	else
		byteData->AddRange(BitConverter::GetBytes(0));

	//Return
	return byteData->ToArray();
}

ChatStruct^ PublicMessageStruct::unpack(array<Byte>^ buff)
{
	int offset = 4; //Skip messageType
	int messageLength;

	messageLength = BitConverter::ToInt32(buff, offset);
	offset += 4; //Update Offset
	if (messageLength > 0)
		strMessage = Encoding::UTF8->GetString(buff, offset, messageLength);

	return this;
}