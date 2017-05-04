#pragma once
#include "ChatStruct.h"

ref class ResponseSendFileStruct : public ChatStruct
{
public:
	String^ strUsername;
	bool IsAccept;

	ResponseSendFileStruct();
	virtual array<Byte>^ pack() override;
	virtual ChatStruct^ unpack(array<Byte>^ buff) override;
};

