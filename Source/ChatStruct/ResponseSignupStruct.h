#pragma once
#include "ChatStruct.h"

ref class ResponseSignupStruct : public ChatStruct
{
public:
	bool IsSucc;
	String^ errorMsg;
	ResponseSignupStruct(); //Default constructor
	virtual array<Byte>^ pack() override;
	virtual ChatStruct^ unpack(array<Byte>^ buff) override;
};