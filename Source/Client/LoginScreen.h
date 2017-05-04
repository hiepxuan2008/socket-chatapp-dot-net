#pragma once

//#include "MainScreen.h"

namespace Client {
	ref class LoginScreen;
}

#include "AppController.h"

namespace Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for LoginScreen
	/// </summary>
	public ref class LoginScreen : public System::Windows::Forms::Form
	{
	public:
		LoginScreen(void)
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
		~LoginScreen()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  butLogin;
	protected: 

	private: System::Windows::Forms::TextBox^  txtPassword;
	private: System::Windows::Forms::Label^  labPassword;
	private: System::Windows::Forms::TextBox^  txtUsername;
	private: System::Windows::Forms::Label^  labUsername;
	private: System::Windows::Forms::Button^  butSignup;


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
			this->butLogin = (gcnew System::Windows::Forms::Button());
			this->txtPassword = (gcnew System::Windows::Forms::TextBox());
			this->labPassword = (gcnew System::Windows::Forms::Label());
			this->txtUsername = (gcnew System::Windows::Forms::TextBox());
			this->labUsername = (gcnew System::Windows::Forms::Label());
			this->butSignup = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			this->butLogin->Location = System::Drawing::Point(108, 89);
			this->butLogin->Name = L"butLogin";
			this->butLogin->Size = System::Drawing::Size(82, 23);
			this->butLogin->TabIndex = 16;
			this->butLogin->Text = L"Log in";
			this->butLogin->UseVisualStyleBackColor = true;
			this->butLogin->Click += gcnew System::EventHandler(this, &LoginScreen::butLogin_Click);
			this->txtPassword->Location = System::Drawing::Point(15, 64);
			this->txtPassword->Name = L"txtPassword";
			this->txtPassword->Size = System::Drawing::Size(175, 20);
			this->txtPassword->TabIndex = 14;
			this->labPassword->AutoSize = true;
			this->labPassword->Location = System::Drawing::Point(12, 48);
			this->labPassword->Name = L"labPassword";
			this->labPassword->Size = System::Drawing::Size(53, 13);
			this->labPassword->TabIndex = 13;
			this->labPassword->Text = L"Password";
			this->txtUsername->Location = System::Drawing::Point(15, 25);
			this->txtUsername->Name = L"txtUsername";
			this->txtUsername->Size = System::Drawing::Size(175, 20);
			this->txtUsername->TabIndex = 12;
			this->labUsername->AutoSize = true;
			this->labUsername->Location = System::Drawing::Point(12, 9);
			this->labUsername->Name = L"labUsername";
			this->labUsername->Size = System::Drawing::Size(55, 13);
			this->labUsername->TabIndex = 11;
			this->labUsername->Text = L"Username";
			this->butSignup->Location = System::Drawing::Point(15, 89);
			this->butSignup->Name = L"butSignup";
			this->butSignup->Size = System::Drawing::Size(82, 23);
			this->butSignup->TabIndex = 17;
			this->butSignup->Text = L"Sign up";
			this->butSignup->UseVisualStyleBackColor = true;
			this->butSignup->Click += gcnew System::EventHandler(this, &LoginScreen::butSignup_Click);
			this->AcceptButton = this->butLogin;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(203, 124);
			this->Controls->Add(this->butSignup);
			this->Controls->Add(this->butLogin);
			this->Controls->Add(this->txtPassword);
			this->Controls->Add(this->labPassword);
			this->Controls->Add(this->txtUsername);
			this->Controls->Add(this->labUsername);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"LoginScreen";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"CLIENT";
			this->Load += gcnew System::EventHandler(this, &LoginScreen::LoginScreen_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		//public: MainScreen^ Mf = gcnew MainScreen;
	private: System::Void butSignup_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void LoginScreen_Load(System::Object^  sender, System::EventArgs^  e);
private: System::Void butLogin_Click(System::Object^  sender, System::EventArgs^  e);
};
}
