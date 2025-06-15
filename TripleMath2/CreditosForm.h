#pragma once

namespace TripleMath {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for CreditosForm
	/// </summary>
	public ref class CreditosForm : public System::Windows::Forms::Form
	{
	public:
		CreditosForm(void)
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
		~CreditosForm()
		{
			if (components)
			{
				delete components;
			}
		}

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
			this->SuspendLayout();
			// 
			// CreditosForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(565, 396);
			this->Name = L"CreditosForm";
			this->Text = L"CreditosForm";
			this->Load += gcnew System::EventHandler(this, &CreditosForm::CreditosForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void CreditosForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
