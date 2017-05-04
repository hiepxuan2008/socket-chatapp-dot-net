#pragma once
#include "ChatStruct.h"

ref class PublicMessageStruct : public ChatStruct
{
public:
	String^ strMessage;

	PublicMessageStruct();
	virtual array<Byte>^ pack() override;
	virtual ChatStruct^ unpack(array<Byte>^ buff) override;
};

