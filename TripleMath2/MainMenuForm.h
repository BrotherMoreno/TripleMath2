#pragma once

#include "StartForm.h"
#include "InstruccionesForm.h"
#include "RankingForm.h"
#include "CreditosForm.h"
#include "RegistroUsuarioForm.h"

namespace TripleMath {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MainMenuForm : public System::Windows::Forms::Form
	{
	public:
		MainMenuForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MainMenuForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container^ components;
		Button^ btnStart;
		Button^ btnInstrucciones;
		Button^ btnRanking;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
		   Button^ btnCreditos;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->btnStart = (gcnew System::Windows::Forms::Button());
			   this->btnInstrucciones = (gcnew System::Windows::Forms::Button());
			   this->btnRanking = (gcnew System::Windows::Forms::Button());
			   this->btnCreditos = (gcnew System::Windows::Forms::Button());
			   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			   this->SuspendLayout();
			   // 
			   // btnStart
			   // 
			   this->btnStart->Location = System::Drawing::Point(158, 308);
			   this->btnStart->Name = L"btnStart";
			   this->btnStart->Size = System::Drawing::Size(90, 35);
			   this->btnStart->TabIndex = 0;
			   this->btnStart->Text = L"Start";
			   this->btnStart->UseVisualStyleBackColor = true;
			   this->btnStart->Click += gcnew System::EventHandler(this, &MainMenuForm::btnStart_Click);
			   // 
			   // btnInstrucciones
			   // 
			   this->btnInstrucciones->Location = System::Drawing::Point(309, 308);
			   this->btnInstrucciones->Name = L"btnInstrucciones";
			   this->btnInstrucciones->Size = System::Drawing::Size(90, 35);
			   this->btnInstrucciones->TabIndex = 1;
			   this->btnInstrucciones->Text = L"Instrucciones";
			   this->btnInstrucciones->UseVisualStyleBackColor = true;
			   this->btnInstrucciones->Click += gcnew System::EventHandler(this, &MainMenuForm::btnInstrucciones_Click);
			   // 
			   // btnRanking
			   // 
			   this->btnRanking->Location = System::Drawing::Point(158, 349);
			   this->btnRanking->Name = L"btnRanking";
			   this->btnRanking->Size = System::Drawing::Size(90, 35);
			   this->btnRanking->TabIndex = 2;
			   this->btnRanking->Text = L"Ranking";
			   this->btnRanking->UseVisualStyleBackColor = true;
			   this->btnRanking->Click += gcnew System::EventHandler(this, &MainMenuForm::btnRanking_Click);
			   // 
			   // btnCreditos
			   // 
			   this->btnCreditos->Location = System::Drawing::Point(309, 349);
			   this->btnCreditos->Name = L"btnCreditos";
			   this->btnCreditos->Size = System::Drawing::Size(90, 35);
			   this->btnCreditos->TabIndex = 3;
			   this->btnCreditos->Text = L"Créditos";
			   this->btnCreditos->UseVisualStyleBackColor = true;
			   this->btnCreditos->Click += gcnew System::EventHandler(this, &MainMenuForm::btnCreditos_Click);
			   // 
			   // pictureBox1
			   // 
			   this->pictureBox1->Image = System::Drawing::Image::FromFile("TripleMath.png");
			   this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			   // NO ASIGNAR IMAGEN AQUÍ
			   this->pictureBox1->Location = System::Drawing::Point(0, 0);
			   this->pictureBox1->Name = L"pictureBox1";
			   this->pictureBox1->Size = System::Drawing::Size(565, 396);
			   this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			   this->pictureBox1->TabIndex = 4;
			   this->pictureBox1->TabStop = false;
			   // 
			   // MainMenuForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(565, 396);
			   this->Controls->Add(this->btnStart);
			   this->Controls->Add(this->btnInstrucciones);
			   this->Controls->Add(this->btnRanking);
			   this->Controls->Add(this->btnCreditos);
			   this->Controls->Add(this->pictureBox1);
			   this->Name = L"MainMenuForm";
			   this->Text = L"TripleMath";
			   this->Load += gcnew System::EventHandler(this, &MainMenuForm::MainMenuForm_Load);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			   this->ResumeLayout(false);

		   }
#pragma endregion
	private: System::Void MainMenuForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void btnStart_Click(System::Object^ sender, System::EventArgs^ e) {
		RegistroUsuarioForm^ registroForm = gcnew RegistroUsuarioForm();
		registroForm->StartPosition = FormStartPosition::Manual;
		registroForm->Location = this->Location;
		this->Hide();
		if (registroForm->ShowDialog() == System::Windows::Forms::DialogResult::OK &&
			!String::IsNullOrEmpty(registroForm->NombreUsuario)) {
			String^ nombreUsuario = registroForm->NombreUsuario;
			StartForm^ startForm = gcnew StartForm();
			startForm->NombreUsuario = nombreUsuario;
			startForm->StartPosition = FormStartPosition::Manual;
			startForm->Location = this->Location;
			startForm->ShowDialog();
		}
		this->Show();
	}
	private: System::Void btnInstrucciones_Click(System::Object^ sender, System::EventArgs^ e) {
		InstruccionesForm^ instruccionesForm = gcnew InstruccionesForm();
		instruccionesForm->StartPosition = FormStartPosition::Manual;
		instruccionesForm->Location = this->Location;
		this->Hide();
		instruccionesForm->ShowDialog();
		this->Show();
	}
	private: System::Void btnRanking_Click(System::Object^ sender, System::EventArgs^ e) {
		RankingForm^ rankingForm = gcnew RankingForm();
		rankingForm->StartPosition = FormStartPosition::Manual;
		rankingForm->Location = this->Location;
		this->Hide();
		rankingForm->ShowDialog();
		this->Show();
	}
	private: System::Void btnCreditos_Click(System::Object^ sender, System::EventArgs^ e) {
		CreditosForm^ creditosForm = gcnew CreditosForm();
		creditosForm->StartPosition = FormStartPosition::Manual;
		creditosForm->Location = this->Location;
		this->Hide();
		creditosForm->ShowDialog();
		this->Show();
	}
	private: System::Void pictureBoxLogo_Click_1(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}