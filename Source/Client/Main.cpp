#include "LoginScreen.h"
using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	AppController::getObject()->loginScreen = gcnew Client::LoginScreen;
	//AppController::getObject()->mainScreen = gcnew Client::MainScreen;
	//AppController::getObject()->privateChat = gcnew Client::PrivateChat;

	//Client::LoginScreen LoginForm;
	//Application::Run(%LoginForm);
	Application::Run(AppController::getObject()->loginScreen);
}