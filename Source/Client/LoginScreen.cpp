#include "LoginScreen.h"
using namespace Client;

System::Void LoginScreen::butSignup_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ username = txtUsername->Text;
	String^ password = txtPassword->Text;

	AppController::getObject()->strUsername = username;
	AppController::getObject()->signup(username, password);
}
System::Void LoginScreen::LoginScreen_Load(System::Object^  sender, System::EventArgs^  e) {
	if (AppController::getObject()->appSocket->connectToServer() != 0) //Connect to server
	{
		Application::Exit(); //Exit app
	}

	AppController::getObject()->createThreadListenMessageFromServer();
}

System::Void LoginScreen::butLogin_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ username = txtUsername->Text;
	String^ password = txtPassword->Text;

	AppController::getObject()->strUsername = username;
	AppController::getObject()->login(username, password);
}