#pragma once
#include "UsuarioPuntaje.h"
using namespace System::Collections::Generic;

namespace TripleMath {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class RankingForm : public System::Windows::Forms::Form
	{
	public:
		static List<UsuarioPuntaje^>^ ranking = gcnew List<UsuarioPuntaje^>();
		static RankingForm^ instanciaAbierta = nullptr;

		RankingForm(void)
		{
			InitializeComponent();
			this->DoubleBuffered = true;
			this->ClientSize = System::Drawing::Size(500, 600);
			this->BackgroundImage = Image::FromFile("FondoHorizontalJuego.jpg");
			this->BackgroundImageLayout = ImageLayout::Stretch;

			// Título
			labelTitulo = gcnew Label();
			labelTitulo->Text = L"Ranking de Jugadores";
			labelTitulo->Font = gcnew System::Drawing::Font("Arial", 26, FontStyle::Bold);
			labelTitulo->ForeColor = Color::DarkBlue;
			labelTitulo->BackColor = Color::Transparent;
			labelTitulo->AutoSize = true;
			labelTitulo->Location = System::Drawing::Point((this->ClientSize.Width - 400) / 2, 20);
			this->Controls->Add(labelTitulo);

			// Crear labels para el Top 15 debajo del título
			labels = gcnew array<Label^>(15);
			for (int i = 0; i < labels->Length; i++) {
				labels[i] = gcnew Label();
				labels[i]->AutoSize = true;
				labels[i]->Font = gcnew System::Drawing::Font("Arial", 18, FontStyle::Bold);
				labels[i]->ForeColor = Color::Black;
				labels[i]->BackColor = Color::Transparent;
				labels[i]->Location = System::Drawing::Point(80, 100 + i * 32);
				this->Controls->Add(labels[i]);
			}
		}

		static int CompararUsuarios(UsuarioPuntaje^ a, UsuarioPuntaje^ b) {
			return b->puntaje.CompareTo(a->puntaje);
		}

		static void ActualizarRankingVisual() {
			if (instanciaAbierta != nullptr) {
				instanciaAbierta->MostrarTop();
			}
		}

	protected:
		~RankingForm()
		{
			if (components)
			{
				delete components;
			}
			if (instanciaAbierta == this)
				instanciaAbierta = nullptr;
		}

	private:
		System::ComponentModel::Container^ components;
		array<Label^>^ labels;
		Label^ labelTitulo;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(500, 600);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->Name = L"RankingForm";
			this->Text = L"Ranking";
			this->Load += gcnew System::EventHandler(this, &RankingForm::RankingForm_Load);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &RankingForm::RankingForm_FormClosed);
			this->ResumeLayout(false);
		}
#pragma endregion

	private:
		System::Void RankingForm_Load(System::Object^ sender, System::EventArgs^ e) {
			instanciaAbierta = this;
			MostrarTop();
		}

		System::Void RankingForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
			if (instanciaAbierta == this)
				instanciaAbierta = nullptr;
		}

		void MostrarTop() {
			List<UsuarioPuntaje^>^ ordenado = gcnew List<UsuarioPuntaje^>(ranking);
			ordenado->Sort(gcnew Comparison<UsuarioPuntaje^>(CompararUsuarios));
			for (int i = 0; i < labels->Length; i++) {
				if (i < ordenado->Count) {
					labels[i]->Text = (i + 1).ToString() + ". " + ordenado[i]->nombre + " [ " + ordenado[i]->puntaje.ToString() + " ]";
				}
				else {
					labels[i]->Text = "";
				}
			}
		}

	protected:
		virtual void OnPaint(PaintEventArgs^ e) override {
			Form::OnPaint(e);
		}
	};
}