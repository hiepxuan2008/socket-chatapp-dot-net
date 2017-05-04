#include "MainScreen.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	ServerController::getObject()->mainScreen = gcnew Server::MainScreen;
	Application::Run(ServerController::getObject()->mainScreen);

	//Server::MainScreen MainForm;
	//Application::Run(%MainForm);
}