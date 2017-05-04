#pragma once
#include "ChatStruct.h"

ref class PrivateMessageStruct : public ChatStruct
{
public:
	String^ strToUsername;
	String^ strMessage;

	PrivateMessageStruct();
	virtual array<Byte>^ pack() override;
	virtual ChatStruct^ unpack(array<Byte>^ buff) override;
};

