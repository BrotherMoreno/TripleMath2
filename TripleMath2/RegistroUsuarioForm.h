#pragma once
#include "StartForm.h"
#include "RankingForm.h" // Agrega esta línea para acceder al ranking
#include "UsuarioPuntaje.h"

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
	private: System::Windows::Forms::PictureBox^ pictureBox1;
		   System::Windows::Forms::Button^ btnPlay;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(RegistroUsuarioForm::typeid));
			   this->lblUsuario = (gcnew System::Windows::Forms::Label());
			   this->txtUsuario = (gcnew System::Windows::Forms::TextBox());
			   this->btnPlay = (gcnew System::Windows::Forms::Button());
			   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			   this->SuspendLayout();
			   // 
			   // lblUsuario
			   // 
			   this->lblUsuario->AutoSize = true;
			   this->lblUsuario->Location = System::Drawing::Point(214, 130);
			   this->lblUsuario->Name = L"lblUsuario";
			   this->lblUsuario->Size = System::Drawing::Size(96, 13);
			   this->lblUsuario->TabIndex = 0;
			   this->lblUsuario->Text = L"Ingrese su usuario:";
			   // 
			   // txtUsuario
			   // 
			   this->txtUsuario->Location = System::Drawing::Point(167, 146);
			   this->txtUsuario->Name = L"txtUsuario";
			   this->txtUsuario->Size = System::Drawing::Size(200, 20);
			   this->txtUsuario->TabIndex = 1;
			   // 
			   // btnPlay
			   // 
			   this->btnPlay->Location = System::Drawing::Point(210, 172);
			   this->btnPlay->Name = L"btnPlay";
			   this->btnPlay->Size = System::Drawing::Size(100, 30);
			   this->btnPlay->TabIndex = 2;
			   this->btnPlay->Text = L"Registrar";
			   this->btnPlay->UseVisualStyleBackColor = true;
			   this->btnPlay->Click += gcnew System::EventHandler(this, &RegistroUsuarioForm::btnPlay_Click);
			   // 
			   // pictureBox1
			   // 
			   this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->pictureBox1->Image = System::Drawing::Image::FromFile("fondoV.jpg");

			   this->pictureBox1->Location = System::Drawing::Point(0, 0);
			   this->pictureBox1->Name = L"pictureBox1";
			   this->pictureBox1->Size = System::Drawing::Size(565, 396);
			   this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			   this->pictureBox1->TabIndex = 3;
			   this->pictureBox1->TabStop = false;
			   this->pictureBox1->Click += gcnew System::EventHandler(this, &RegistroUsuarioForm::pictureBox1_Click);
			   // 
			   // RegistroUsuarioForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(565, 396);
			   this->Controls->Add(this->lblUsuario);
			   this->Controls->Add(this->txtUsuario);
			   this->Controls->Add(this->btnPlay);
			   this->Controls->Add(this->pictureBox1);
			   this->Name = L"RegistroUsuarioForm";
			   this->Text = L"RegistroUsuarioForm";
			   this->Load += gcnew System::EventHandler(this, &RegistroUsuarioForm::RegistroUsuarioForm_Load);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
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

			// --- AGREGADO: Registrar usuario en el ranking con puntaje 0 ---
			bool encontrado = false;
			for each (UsuarioPuntaje ^ up in RankingForm::ranking) {
				if (up->nombre == this->NombreUsuario) {
					encontrado = true;
					break;
				}
			}
			if (!encontrado) {
				RankingForm::ranking->Add(gcnew UsuarioPuntaje(this->NombreUsuario, 0));
				RankingForm::ActualizarRankingVisual();
			}
			// -------------------------------------------------------------

			this->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->Close();
		}
		else {
			MessageBox::Show("Por favor, ingresa un nombre de usuario.");
		}
	}
	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}

