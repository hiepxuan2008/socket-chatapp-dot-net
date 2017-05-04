#include "UserStatusStruct.h"

UserStatusStruct::UserStatusStruct()
{
	lstOnlineUsers = nullptr;
}

array<Byte>^ UserStatusStruct::pack()
{
	List<Byte>^ byteData = gcnew List<Byte>();
	byteData->AddRange(BitConverter::GetBytes(int(ChatStruct::MessageType::UserStatus)));

	//Merge list to string
	String^ strListOnlineUsers = "";
	if (lstOnlineUsers != nullptr)
	{
		for (int i = 0; i < lstOnlineUsers->Length - 1; ++i)
			strListOnlineUsers += lstOnlineUsers[i] + "|";
		if (lstOnlineUsers->Length > 0)
			strListOnlineUsers += lstOnlineUsers[lstOnlineUsers->Length - 1];
		//End of merging!!

		//MessageBox::Show("debug pack" + strListOnlineUsers);
	}

	//add strListOnlineUsers info
	if (strListOnlineUsers != "")
	{
		byteData->AddRange(BitConverter::GetBytes(Encoding::UTF8->GetByteCount(strListOnlineUsers))); //Length of strListOnlineUsers
		byteData->AddRange(Encoding::UTF8->GetBytes(strListOnlineUsers)); //strListOnlineUsers string
	}
	else
		byteData->AddRange(BitConverter::GetBytes(0));

	//Return
	return byteData->ToArray();
}

ChatStruct^ UserStatusStruct::unpack(array<Byte>^ buff)
{
	int offset = 4; //Skip messageType
	int length;
	String^ strListOnlineUsers = "";

	length = BitConverter::ToInt32(buff, offset);
	offset += 4; //Update Offset
	if (length > 0)
	{
		strListOnlineUsers = Encoding::UTF8->GetString(buff, offset, length);

		//MessageBox::Show("debug unpack" + strListOnlineUsers);

		//Split string to list
		array<wchar_t>^ delimiterChars = gcnew array<wchar_t>(1);
		delimiterChars[0] = '|';
		lstOnlineUsers = strListOnlineUsers->Split(delimiterChars);
	}
		
	//return
	return this;
}