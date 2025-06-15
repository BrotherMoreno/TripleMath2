#pragma once
#include "Figuras.h"
#include "controladoraJuego.h"
#include "RankingForm.h" // Para acceso al ranking

namespace TripleMath {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class StartForm : public System::Windows::Forms::Form
	{
	public:
		// Propiedad pública para el nombre del usuario
		property String^ NombreUsuario;

		StartForm(void)
		{
			InitializeComponent();
			this->DoubleBuffered = true;
			controladora = gcnew ControladoraJuego();
			timer = gcnew System::Windows::Forms::Timer();
			timer->Interval = 500;
			timer->Tick += gcnew System::EventHandler(this, &StartForm::OnTimerTick);
			timer->Start();
			this->KeyPreview = true;
			this->KeyDown += gcnew KeyEventHandler(this, &StartForm::OnKeyDown);
			guardadoEnRanking = false; // Inicializa el flag
		}

	protected:
		~StartForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container^ components;
		ControladoraJuego^ controladora;
		System::Windows::Forms::Timer^ timer;
		bool guardadoEnRanking; // Flag para evitar guardar varias veces

		// Guardar usuario y puntaje en archivo
		void GuardarUsuarioPuntajeEnArchivo(String^ nombre, int puntaje)
		{
			if (String::IsNullOrWhiteSpace(nombre)) return;
			try {
				System::IO::StreamWriter^ sw = gcnew System::IO::StreamWriter("ranking.txt", true);
				sw->WriteLine(nombre->Trim() + "," + puntaje.ToString());
				sw->Close();
			}
			catch (System::Exception^ ex) {
				MessageBox::Show("Error al guardar el ranking: " + ex->Message);
			}
		}

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(500, 600);
			this->Name = L"StartForm";
			this->Text = L"TripleMatch";
			this->Load += gcnew System::EventHandler(this, &StartForm::StartForm_Load);
			this->ResumeLayout(false);
		}
#pragma endregion
	private: System::Void StartForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}

	private:
		void OnTimerTick(System::Object^ sender, System::EventArgs^ e) {
			if (!controladora->EsFinJuego()) {
				controladora->Paso();
				this->Invalidate();
			}
			else if (!guardadoEnRanking) {
				if (!String::IsNullOrEmpty(NombreUsuario)) {
					GuardarUsuarioPuntajeEnArchivo(NombreUsuario, controladora->puntaje);
				}
				guardadoEnRanking = true;
			}
		}

		void OnKeyDown(System::Object^ sender, KeyEventArgs^ e) {
			if (controladora->figuraActual == nullptr) return;
			if (e->KeyCode == Keys::A) controladora->MoverFigura(-1);
			if (e->KeyCode == Keys::D) controladora->MoverFigura(1);
			if (e->KeyCode == Keys::S) controladora->BajarFigura();
			if (e->KeyCode == Keys::Escape) timer->Stop();
			this->Invalidate();
		}

	protected:
		virtual void OnPaint(PaintEventArgs^ e) override {
			e->Graphics->Clear(Color::White);

			// Puntaje a la izquierda
			System::Drawing::Font^ fuente = gcnew System::Drawing::Font("Arial", 18, FontStyle::Bold);
			e->Graphics->DrawString("Puntaje: " + controladora->puntaje, fuente, Brushes::DarkRed, 10, 10);

			// Usuario a la derecha
			if (!String::IsNullOrEmpty(NombreUsuario)) {
				System::Drawing::Font^ fuenteUsuario = gcnew System::Drawing::Font("Arial", 18, FontStyle::Bold);
				String^ textoUsuario = "Usuario: " + NombreUsuario;
				SizeF size = e->Graphics->MeasureString(textoUsuario, fuenteUsuario);
				float x = this->ClientSize.Width - size.Width - 10;
				float y = 10;
				e->Graphics->DrawString(textoUsuario, fuenteUsuario, Brushes::DarkRed, x, y);
			}

			controladora->Dibujar(e->Graphics);

			if (controladora->EsFinJuego())
				e->Graphics->DrawString("¡Fin del Juego!", gcnew System::Drawing::Font("Arial", 24, FontStyle::Bold), Brushes::Red, 60, 120);

			Form::OnPaint(e);
		}
	};
}