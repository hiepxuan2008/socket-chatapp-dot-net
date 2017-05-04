#pragma once
#include "ChatStruct.h"

ref class ResponseLoginStruct : public ChatStruct
{
public:
	bool IsSucc;
	String^ errorMsg;
	ResponseLoginStruct(); //Default constructor
	virtual array<Byte>^ pack() override;
	virtual ChatStruct^ unpack(array<Byte>^ buff) override;
};