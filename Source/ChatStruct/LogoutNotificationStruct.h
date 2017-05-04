#pragma once
#include "ChatStruct.h"

ref class LogoutNotificationStruct : public ChatStruct
{
public:
	String^ strUsername;

	LogoutNotificationStruct();
	virtual array<Byte>^ pack() override;
	virtual ChatStruct^ unpack(array<Byte>^ buff) override;
};

