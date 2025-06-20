#pragma once

namespace TripleMath {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for InstruccionesForm
	/// </summary>
	public ref class InstruccionesForm : public System::Windows::Forms::Form
	{
	public:
		InstruccionesForm(void)
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
		~InstruccionesForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::PictureBox^ pictureBoxInstrucciones;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(InstruccionesForm::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pictureBoxInstrucciones = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxInstrucciones))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 438);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(124, 41);
			this->button1->TabIndex = 0;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &InstruccionesForm::button1_Click);
			// 
			// pictureBoxInstrucciones
			// 
			this->pictureBoxInstrucciones->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBoxInstrucciones->Image = System::Drawing::Image::FromFile("Instrucciones.jpg");
			this->pictureBoxInstrucciones->Location = System::Drawing::Point(0, 0);
			this->pictureBoxInstrucciones->Name = L"pictureBoxInstrucciones";
			this->pictureBoxInstrucciones->Size = System::Drawing::Size(599, 425);
			this->pictureBoxInstrucciones->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBoxInstrucciones->TabIndex = 1;
			this->pictureBoxInstrucciones->TabStop = false;
			this->pictureBoxInstrucciones->Click += gcnew System::EventHandler(this, &InstruccionesForm::pictureBox1_Click);
			// 
			// InstruccionesForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(565, 396);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBoxInstrucciones);
			this->Name = L"InstruccionesForm";
			this->Text = L"InstruccionesForm";
			this->Load += gcnew System::EventHandler(this, &InstruccionesForm::InstruccionesForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxInstrucciones))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void InstruccionesForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
