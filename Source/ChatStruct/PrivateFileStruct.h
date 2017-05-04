#pragma once
#include "ChatStruct.h"

ref class PrivateFileStruct : public ChatStruct
{
public:
	String^ strUsername;
	String^ strFilename;
	int iPackageNumber;
	int iTotalPackage;

	array<Byte>^ bData;

	PrivateFileStruct();
	virtual array<Byte>^ pack() override;
	virtual ChatStruct^ unpack(array<Byte>^ buff) override;
};

