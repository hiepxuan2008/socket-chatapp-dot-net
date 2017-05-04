#pragma once
#include "ChatStruct.h"

ref class SignupStruct : public ChatStruct
{
public:
	String^ strUsername;
	String^ strPassword;

	SignupStruct();
	virtual array<Byte>^ pack() override;
	virtual ChatStruct^ unpack(array<Byte>^ buff) override;
};

