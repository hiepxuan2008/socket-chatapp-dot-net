#pragma once

#include "PrivateChat.h"

ref class PrivateChatInfo
{
public:
	Client::PrivateChat^ privateChatForm;
	System::String^ strUsername;

	PrivateChatInfo(Client::PrivateChat^ _privateChatForm, System::String^ _strUsername) :
		privateChatForm(_privateChatForm), strUsername(_strUsername){};
};