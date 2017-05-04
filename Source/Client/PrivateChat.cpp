#include "PrivateChat.h"
using namespace Client;

System::Void PrivateChat::ThreadChooseFile()
{
	OpenFileDialog^ ofd = gcnew OpenFileDialog;
	if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		String^ _info = ofd->SafeFileName;
		String^ info = ofd->FileName;
		this->txtfName->Text = _info;
		this->txtPath->Text = info;
		int size = IO::FileInfo(ofd->FileName).Length;

		fileNameToSend = _info;
		filePathToSend = info;
		fileSizeToSend = size;
		AppController::getObject()->requestSendFile(strFriendUsername, _info, size);
	}
}

System::Void PrivateChat::butFile_Click(System::Object^  sender, System::EventArgs^  e) {
	Thread^ newThread = gcnew Thread(gcnew ThreadStart(this, &PrivateChat::ThreadChooseFile));
	newThread->SetApartmentState(ApartmentState::STA);
	newThread->Start();
}
System::Void PrivateChat::button1_Click(System::Object^  sender, System::EventArgs^  e) {
}

void PrivateChat::SetCaption(String^ txtCaption)
{
	this->Text = txtCaption;
}

void PrivateChat::AddTextToDisplayChatbox(String^ text)
{
	DisplayChatBox->AppendText(text);
	DisplayChatBox->AppendText("\n");
}
System::Void PrivateChat::butSend_Click(System::Object^  sender, System::EventArgs^  e) {

	AppController::getObject()->sendPrivateMessage(strFriendUsername, txtMessage->Text);
	AddTextToDisplayChatbox(strMyUsername + ": " + txtMessage->Text);
	txtMessage->Text = nullptr;
}

System::Void PrivateChat::PrivateChat_Load(System::Object^  sender, System::EventArgs^  e)
{
	AppController::getObject()->createThreadListenMessageFromServer();
}

System::Void PrivateChat::PrivateChat_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
{
	AppController::getObject()->lstPrivateChatForm->Remove(this);
	/*
		int counter = AppController::getObject()->lstPrivateChatForm->Count;
		MessageBox::Show(Convert::ToString(counter));*/
}

System::Void PrivateChat::PrivateChat_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e)
{
}