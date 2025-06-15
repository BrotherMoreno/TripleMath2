#pragma once
#include "StartForm.h"
namespace TripleMath {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class RegistroUsuarioForm : public System::Windows::Forms::Form
	{
	public:
		RegistroUsuarioForm(void)
		{
			InitializeComponent();
		}

	protected:
		~RegistroUsuarioForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container^ components;
		System::Windows::Forms::Label^ lblUsuario;
		System::Windows::Forms::TextBox^ txtUsuario;
		System::Windows::Forms::Button^ btnPlay;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->lblUsuario = (gcnew System::Windows::Forms::Label());
			this->txtUsuario = (gcnew System::Windows::Forms::TextBox());
			this->btnPlay = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// lblUsuario
			// 
			this->lblUsuario->AutoSize = true;
			this->lblUsuario->Location = System::Drawing::Point(40, 40);
			this->lblUsuario->Name = L"lblUsuario";
			this->lblUsuario->Size = System::Drawing::Size(96, 13);
			this->lblUsuario->TabIndex = 0;
			this->lblUsuario->Text = L"Ingrese su usuario:";
			// 
			// txtUsuario
			// 
			this->txtUsuario->Location = System::Drawing::Point(40, 60);
			this->txtUsuario->Name = L"txtUsuario";
			this->txtUsuario->Size = System::Drawing::Size(200, 20);
			this->txtUsuario->TabIndex = 1;
			// 
			// btnPlay
			// 
			this->btnPlay->Location = System::Drawing::Point(90, 110);
			this->btnPlay->Name = L"btnPlay";
			this->btnPlay->Size = System::Drawing::Size(100, 30);
			this->btnPlay->TabIndex = 2;
			this->btnPlay->Text = L"Play";
			this->btnPlay->UseVisualStyleBackColor = true;
			this->btnPlay->Click += gcnew System::EventHandler(this, &RegistroUsuarioForm::btnPlay_Click);
			// 
			// RegistroUsuarioForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(565, 396);
			this->Controls->Add(this->lblUsuario);
			this->Controls->Add(this->txtUsuario);
			this->Controls->Add(this->btnPlay);
			this->Name = L"RegistroUsuarioForm";
			this->Text = L"RegistroUsuarioForm";
			this->Load += gcnew System::EventHandler(this, &RegistroUsuarioForm::RegistroUsuarioForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void RegistroUsuarioForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	public: property System::String^ NombreUsuario;

	private: System::Void btnPlay_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!String::IsNullOrWhiteSpace(txtUsuario->Text)) {
			this->NombreUsuario = txtUsuario->Text->Trim();
			this->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->Close();
		}
		else {
			MessageBox::Show("Por favor, ingresa un nombre de usuario.");
		}
	}
	};
}