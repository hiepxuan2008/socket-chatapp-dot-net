#pragma once
#include "ChatStruct.h"

ref class RequestSendFileStruct : public ChatStruct
{
public:
	String^ strUsername;
	String^ strFileName;
	int iFileSize;

	RequestSendFileStruct();
	virtual array<Byte>^ pack() override;
	virtual ChatStruct^ unpack(array<Byte>^ buff) override;
};

