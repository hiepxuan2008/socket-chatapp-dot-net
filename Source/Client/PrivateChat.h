#pragma once

namespace Client{
	ref class PrivateChat;
}

#include "AppController.h"

namespace Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Summary for PrivateChat
	/// </summary>
	public ref class PrivateChat : public System::Windows::Forms::Form
	{
	public:
		PrivateChat(void)
		{
			//MessageBox::Show("Private chat: Default constructor!");
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			pathFileToReceiver = System::Reflection::Assembly::GetEntryAssembly()->Location;
		}

		PrivateChat(String^ myUsername, String^ friendUsername) : strMyUsername(myUsername), strFriendUsername(friendUsername)
		{
			InitializeComponent();
			this->Text = "Private Chat With " + strFriendUsername;
			pathFileToReceiver = System::Reflection::Assembly::GetEntryAssembly()->Location;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PrivateChat()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  butSend;
	protected:
	private: System::Windows::Forms::Label^  labMessage;
	private: System::Windows::Forms::TextBox^  txtMessage;
	private: System::Windows::Forms::TextBox^  DisplayChatBox;
	private: System::Windows::Forms::Label^  labChatBox;






	private: System::Windows::Forms::TextBox^  textStat;
	private: System::Windows::Forms::Label^  labStat;
	private: System::Windows::Forms::Button^  butFile;
	private: System::Windows::Forms::TextBox^  txtPath;
	private: System::Windows::Forms::Label^  labPath;
	private: System::Windows::Forms::Label^  labfName;
	private: System::Windows::Forms::TextBox^  txtfName;











	protected:

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
			this->butSend = (gcnew System::Windows::Forms::Button());
			this->labMessage = (gcnew System::Windows::Forms::Label());
			this->txtMessage = (gcnew System::Windows::Forms::TextBox());
			this->DisplayChatBox = (gcnew System::Windows::Forms::TextBox());
			this->labChatBox = (gcnew System::Windows::Forms::Label());
			this->textStat = (gcnew System::Windows::Forms::TextBox());
			this->labStat = (gcnew System::Windows::Forms::Label());
			this->butFile = (gcnew System::Windows::Forms::Button());
			this->txtPath = (gcnew System::Windows::Forms::TextBox());
			this->labPath = (gcnew System::Windows::Forms::Label());
			this->labfName = (gcnew System::Windows::Forms::Label());
			this->txtfName = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			this->butSend->Location = System::Drawing::Point(278, 225);
			this->butSend->Name = L"butSend";
			this->butSend->Size = System::Drawing::Size(68, 39);
			this->butSend->TabIndex = 9;
			this->butSend->Text = L"Send";
			this->butSend->UseVisualStyleBackColor = true;
			this->butSend->Click += gcnew System::EventHandler(this, &PrivateChat::butSend_Click);
			this->labMessage->AutoSize = true;
			this->labMessage->Location = System::Drawing::Point(12, 209);
			this->labMessage->Name = L"labMessage";
			this->labMessage->Size = System::Drawing::Size(59, 13);
			this->labMessage->TabIndex = 8;
			this->labMessage->Text = L"MESSAGE";
			this->txtMessage->Location = System::Drawing::Point(12, 225);
			this->txtMessage->Multiline = true;
			this->txtMessage->Name = L"txtMessage";
			this->txtMessage->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->txtMessage->Size = System::Drawing::Size(257, 39);
			this->txtMessage->TabIndex = 7;
			this->DisplayChatBox->Location = System::Drawing::Point(15, 27);
			this->DisplayChatBox->Multiline = true;
			this->DisplayChatBox->Name = L"DisplayChatBox";
			this->DisplayChatBox->ReadOnly = true;
			this->DisplayChatBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->DisplayChatBox->Size = System::Drawing::Size(487, 163);
			this->DisplayChatBox->TabIndex = 6;
			this->labChatBox->AutoSize = true;
			this->labChatBox->Location = System::Drawing::Point(12, 9);
			this->labChatBox->Name = L"labChatBox";
			this->labChatBox->Size = System::Drawing::Size(61, 13);
			this->labChatBox->TabIndex = 5;
			this->labChatBox->Text = L"CHAT BOX";
			this->textStat->Location = System::Drawing::Point(395, 199);
			this->textStat->Name = L"textStat";
			this->textStat->ReadOnly = true;
			this->textStat->Size = System::Drawing::Size(107, 20);
			this->textStat->TabIndex = 19;
			this->labStat->AutoSize = true;
			this->labStat->Location = System::Drawing::Point(330, 202);
			this->labStat->Name = L"labStat";
			this->labStat->Size = System::Drawing::Size(59, 13);
			this->labStat->TabIndex = 18;
			this->labStat->Text = L"File Status:";
			this->butFile->Location = System::Drawing::Point(352, 225);
			this->butFile->Name = L"butFile";
			this->butFile->Size = System::Drawing::Size(150, 39);
			this->butFile->TabIndex = 20;
			this->butFile->Text = L"Choose File";
			this->butFile->UseVisualStyleBackColor = true;
			this->butFile->Click += gcnew System::EventHandler(this, &PrivateChat::butFile_Click);
			this->txtPath->Location = System::Drawing::Point(278, 270);
			this->txtPath->Name = L"txtPath";
			this->txtPath->ReadOnly = true;
			this->txtPath->Size = System::Drawing::Size(224, 20);
			this->txtPath->TabIndex = 21;
			this->labPath->AutoSize = true;
			this->labPath->Location = System::Drawing::Point(240, 273);
			this->labPath->Name = L"labPath";
			this->labPath->Size = System::Drawing::Size(32, 13);
			this->labPath->TabIndex = 22;
			this->labPath->Text = L"Path:";
			this->labPath->Click += gcnew System::EventHandler(this, &PrivateChat::label1_Click_2);
			this->labfName->AutoSize = true;
			this->labfName->Location = System::Drawing::Point(12, 273);
			this->labfName->Name = L"labfName";
			this->labfName->Size = System::Drawing::Size(55, 13);
			this->labfName->TabIndex = 23;
			this->labfName->Text = L"File name:";
			this->txtfName->Location = System::Drawing::Point(73, 270);
			this->txtfName->Name = L"txtfName";
			this->txtfName->ReadOnly = true;
			this->txtfName->Size = System::Drawing::Size(161, 20);
			this->txtfName->TabIndex = 24;
			this->AcceptButton = this->butSend;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(514, 296);
			this->Controls->Add(this->txtfName);
			this->Controls->Add(this->labfName);
			this->Controls->Add(this->labPath);
			this->Controls->Add(this->txtPath);
			this->Controls->Add(this->butFile);
			this->Controls->Add(this->textStat);
			this->Controls->Add(this->labStat);
			this->Controls->Add(this->butSend);
			this->Controls->Add(this->labMessage);
			this->Controls->Add(this->txtMessage);
			this->Controls->Add(this->DisplayChatBox);
			this->Controls->Add(this->labChatBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"PrivateChat";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Private Chat";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &PrivateChat::PrivateChat_FormClosing);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &PrivateChat::PrivateChat_FormClosed);
			this->Load += gcnew System::EventHandler(this, &PrivateChat::PrivateChat_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	public: String^ strFriendUsername = nullptr;
	public: String^ strMyUsername = nullptr;
	public: String^ filePathToSend = nullptr;
	public: String^ fileNameToSend = nullptr;
	public: int fileSizeToSend = 0;
	public: String^ pathFileToReceiver;// = System::Reflection::Assembly::GetEntryAssembly()->Location;
	public: FileStream^ writerStream = nullptr;

	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label1_Click_1(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label1_Click_2(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void butFile_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
	public: void SetCaption(String^ txtCaption);
	public: void AddTextToDisplayChatbox(String^ text);
	private: System::Void butSend_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void PrivateChat_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void PrivateChat_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
	private: System::Void PrivateChat_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e);
	//private: System::Void DisplayChatBox_TextChanged(System::Object^  sender, System::EventArgs^  e);
	public: System::Void ThreadChooseFile();
	};
}
