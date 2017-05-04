#pragma  once
#include "ChatStruct.h"

ref class ChatControl
{
public:
	static ChatStruct^ unpack(array<Byte>^ buff);
};