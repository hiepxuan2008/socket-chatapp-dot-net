#pragma once

namespace Server {
	ref class MainScreen;
}

#include "ServerController.h"

namespace Server {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Net;
	using namespace System::Net::Sockets;

	/// <summary>
	/// Summary for MainScreen
	/// </summary>
	public ref class MainScreen : public System::Windows::Forms::Form
	{
	public:
		MainScreen(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainScreen()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  labInfo;
	protected:
	private: System::Windows::Forms::Label^  labIPServer;
	private: System::Windows::Forms::TextBox^  txtIPServer;
	private: System::Windows::Forms::Label^  labPortServer;
	private: System::Windows::Forms::TextBox^  txtPortServer;
	private: System::Windows::Forms::TextBox^  txtClientChatBox;
	private: System::Windows::Forms::Label^  labConference;
	private: System::Windows::Forms::Label^  labClientList;
	private: System::Windows::Forms::TextBox^  txtClientList;
	private: System::Windows::Forms::Label^  labConnect;
	private: System::Windows::Forms::TextBox^  txtConnected;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::Button^  btListen;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->labInfo = (gcnew System::Windows::Forms::Label());
			this->labIPServer = (gcnew System::Windows::Forms::Label());
			this->txtIPServer = (gcnew System::Windows::Forms::TextBox());
			this->labPortServer = (gcnew System::Windows::Forms::Label());
			this->txtPortServer = (gcnew System::Windows::Forms::TextBox());
			this->txtClientChatBox = (gcnew System::Windows::Forms::TextBox());
			this->labConference = (gcnew System::Windows::Forms::Label());
			this->labClientList = (gcnew System::Windows::Forms::Label());
			this->txtClientList = (gcnew System::Windows::Forms::TextBox());
			this->labConnect = (gcnew System::Windows::Forms::Label());
			this->txtConnected = (gcnew System::Windows::Forms::TextBox());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->btListen = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			this->labInfo->AutoSize = true;
			this->labInfo->Location = System::Drawing::Point(12, 9);
			this->labInfo->Name = L"labInfo";
			this->labInfo->Size = System::Drawing::Size(79, 13);
			this->labInfo->TabIndex = 0;
			this->labInfo->Text = L"SERVER INFO";
			this->labIPServer->AutoSize = true;
			this->labIPServer->Location = System::Drawing::Point(106, 9);
			this->labIPServer->Name = L"labIPServer";
			this->labIPServer->Size = System::Drawing::Size(20, 13);
			this->labIPServer->TabIndex = 1;
			this->labIPServer->Text = L"IP:";
			this->txtIPServer->Location = System::Drawing::Point(132, 6);
			this->txtIPServer->Name = L"txtIPServer";
			this->txtIPServer->Size = System::Drawing::Size(109, 20);
			this->txtIPServer->TabIndex = 2;
			this->labPortServer->AutoSize = true;
			this->labPortServer->Location = System::Drawing::Point(247, 9);
			this->labPortServer->Name = L"labPortServer";
			this->labPortServer->Size = System::Drawing::Size(29, 13);
			this->labPortServer->TabIndex = 3;
			this->labPortServer->Text = L"Port:";
			this->txtPortServer->Location = System::Drawing::Point(282, 6);
			this->txtPortServer->Name = L"txtPortServer";
			this->txtPortServer->Size = System::Drawing::Size(67, 20);
			this->txtPortServer->TabIndex = 4;
			this->txtClientChatBox->Location = System::Drawing::Point(163, 53);
			this->txtClientChatBox->Multiline = true;
			this->txtClientChatBox->Name = L"txtClientChatBox";
			this->txtClientChatBox->ReadOnly = true;
			this->txtClientChatBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->txtClientChatBox->Size = System::Drawing::Size(267, 206);
			this->txtClientChatBox->TabIndex = 5;
			this->labConference->AutoSize = true;
			this->labConference->Location = System::Drawing::Point(160, 37);
			this->labConference->Name = L"labConference";
			this->labConference->Size = System::Drawing::Size(112, 13);
			this->labConference->TabIndex = 6;
			this->labConference->Text = L"CHAT CONFERENCE";
			this->labClientList->AutoSize = true;
			this->labClientList->Location = System::Drawing::Point(12, 37);
			this->labClientList->Name = L"labClientList";
			this->labClientList->Size = System::Drawing::Size(128, 13);
			this->labClientList->TabIndex = 7;
			this->labClientList->Text = L"MANAGED CLIENT LIST";
			this->txtClientList->Location = System::Drawing::Point(15, 53);
			this->txtClientList->Multiline = true;
			this->txtClientList->Name = L"txtClientList";
			this->txtClientList->ReadOnly = true;
			this->txtClientList->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->txtClientList->Size = System::Drawing::Size(130, 88);
			this->txtClientList->TabIndex = 8;
			this->labConnect->AutoSize = true;
			this->labConnect->Location = System::Drawing::Point(12, 155);
			this->labConnect->Name = L"labConnect";
			this->labConnect->Size = System::Drawing::Size(126, 13);
			this->labConnect->TabIndex = 9;
			this->labConnect->Text = L"CONNECTING CLIENTS";
			this->txtConnected->Location = System::Drawing::Point(12, 171);
			this->txtConnected->Multiline = true;
			this->txtConnected->Name = L"txtConnected";
			this->txtConnected->ReadOnly = true;
			this->txtConnected->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->txtConnected->Size = System::Drawing::Size(130, 88);
			this->txtConnected->TabIndex = 10;
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainScreen::backgroundWorker1_DoWork);
			this->btListen->Location = System::Drawing::Point(355, 4);
			this->btListen->Name = L"btListen";
			this->btListen->Size = System::Drawing::Size(75, 23);
			this->btListen->TabIndex = 11;
			this->btListen->Text = L"Listen";
			this->btListen->UseVisualStyleBackColor = true;
			this->btListen->Click += gcnew System::EventHandler(this, &MainScreen::btListen_Click);
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(441, 272);
			this->Controls->Add(this->btListen);
			this->Controls->Add(this->txtConnected);
			this->Controls->Add(this->labConnect);
			this->Controls->Add(this->txtClientList);
			this->Controls->Add(this->labClientList);
			this->Controls->Add(this->labConference);
			this->Controls->Add(this->txtClientChatBox);
			this->Controls->Add(this->txtPortServer);
			this->Controls->Add(this->labPortServer);
			this->Controls->Add(this->txtIPServer);
			this->Controls->Add(this->labIPServer);
			this->Controls->Add(this->labInfo);
			this->Name = L"MainScreen";
			this->Text = L"Server";
			this->Load += gcnew System::EventHandler(this, &MainScreen::MainScreen_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	public: Thread^ threadListenClient;
	public: static void ListenClientMessage(Object^ obj);
	private: System::Void MainScreen_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
	public: void AddTextToContent(String^ text);
	public: void UpdateConnectedClient(List<String^>^ lstClient);
	public: void UpdateClientList(List<String^>^ lstClient);
	private: System::Void btListen_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
