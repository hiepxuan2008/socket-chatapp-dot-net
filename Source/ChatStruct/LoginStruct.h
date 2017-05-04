#pragma once
#include "ChatStruct.h"

ref class LoginStruct : public ChatStruct
{
public:
	String^ strUsername;
	String^ strPassword;

	LoginStruct();
	virtual array<Byte>^ pack() override;
	virtual ChatStruct^ unpack(array<Byte>^ buff) override;
};

