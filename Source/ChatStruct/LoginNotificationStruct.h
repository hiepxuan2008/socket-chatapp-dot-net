#pragma once
#include "ChatStruct.h"

ref class LoginNotificationStruct : public ChatStruct
{
public:
	String^ strUsername;

	LoginNotificationStruct();
	virtual array<Byte>^ pack() override;
	virtual ChatStruct^ unpack(array<Byte>^ buff) override;
};

