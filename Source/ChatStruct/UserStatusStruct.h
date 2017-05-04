#pragma once
#include "ChatStruct.h"

//#define DIM ""

ref class UserStatusStruct : public ChatStruct
{
public:
	array<String^>^ lstOnlineUsers;

	UserStatusStruct();
	virtual array<Byte>^ pack() override;
	virtual ChatStruct^ unpack(array<Byte>^ buff) override;
};

