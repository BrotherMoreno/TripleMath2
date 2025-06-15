#pragma once
#include "UsuarioPuntaje.h" // Incluye la clase de usuario y puntaje
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
		// Lista estática para mantener el ranking entre partidas
		static List<UsuarioPuntaje^>^ ranking = gcnew List<UsuarioPuntaje^>();

		// Variable estática para guardar el usuario actual
		static String^ usuarioActual = nullptr;

		RankingForm(void)
		{
			InitializeComponent();
			this->DoubleBuffered = true;
			this->ClientSize = System::Drawing::Size(500, 600);
		}

		// Método para registrar el usuario actual (llámalo al presionar "Play")
		static void RegistrarUsuario(String^ nombre) {
			usuarioActual = nombre;
		}

		// Método para agregar un usuario y puntaje al ranking (llámalo al terminar la partida)
		static void AgregarUsuarioPuntajeActual(int puntaje) {
			if (!String::IsNullOrEmpty(usuarioActual)) {
				ranking->Add(gcnew UsuarioPuntaje(usuarioActual, puntaje));
			}
		}

		// Método para agregar cualquier usuario y puntaje al ranking (opcional)
		void AgregarUsuarioPuntaje(String^ nombre, int puntaje) {
			ranking->Add(gcnew UsuarioPuntaje(nombre, puntaje));
		}

		// --- FUNCIÓN AUXILIAR PARA ORDENAR ---
		static int CompararUsuarios(UsuarioPuntaje^ a, UsuarioPuntaje^ b) {
			return b->puntaje.CompareTo(a->puntaje);
		}

	protected:
		~RankingForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(500, 600);
			this->Name = L"RankingForm";
			this->Text = L"Ranking";
			this->Load += gcnew System::EventHandler(this, &RankingForm::RankingForm_Load);
			this->ResumeLayout(false);
		}
#pragma endregion

	private:
		System::Void RankingForm_Load(System::Object^ sender, System::EventArgs^ e) {
			this->Invalidate(); // Forzar repintado para mostrar el ranking
		}
	private: List<UsuarioPuntaje^>^ LeerRankingDeArchivo() {
		List<UsuarioPuntaje^>^ lista = gcnew List<UsuarioPuntaje^>();
		if (System::IO::File::Exists("ranking.txt")) {
			array<String^>^ lineas = System::IO::File::ReadAllLines("ranking.txt");
			for each (String ^ linea in lineas) {
				array<String^>^ partes = linea->Split(',');
				if (partes->Length == 2) {
					String^ nombre = partes[0];
					int puntaje = 0;
					if (Int32::TryParse(partes[1], puntaje)) {
						lista->Add(gcnew UsuarioPuntaje(nombre, puntaje));
					}
				}
			}
		}
		return lista;
	}
	protected:
		virtual void OnPaint(PaintEventArgs^ e) override {
			e->Graphics->Clear(Color::White);

			String^ titulo = "Ranking de Jugadores";
			System::Drawing::Font^ fuenteTitulo = gcnew System::Drawing::Font("Arial", 22, FontStyle::Bold);
			SizeF sizeTitulo = e->Graphics->MeasureString(titulo, fuenteTitulo);
			float xTitulo = (this->ClientSize.Width - sizeTitulo.Width) / 2;
			e->Graphics->DrawString(titulo, fuenteTitulo, Brushes::DarkBlue, xTitulo, 30);

			// Leer ranking desde archivo
			List<UsuarioPuntaje^>^ ordenado = LeerRankingDeArchivo();
			ordenado->Sort(gcnew Comparison<UsuarioPuntaje^>(CompararUsuarios));

			System::Drawing::Font^ fuente = gcnew System::Drawing::Font("Arial", 16, FontStyle::Bold);
			int y = 100;
			int espacio = 35;
			if (ordenado->Count == 0) {
				String^ mensaje = "No hay jugadores registrados";
				SizeF sizeMensaje = e->Graphics->MeasureString(mensaje, fuente);
				float x = (this->ClientSize.Width - sizeMensaje.Width) / 2;
				e->Graphics->DrawString(mensaje, fuente, Brushes::Gray, x, y);
			}
			else {
				for (int i = 0; i < ordenado->Count; i++) {
					String^ linea = (i + 1).ToString() + ". " + ordenado[i]->nombre + " [ " + ordenado[i]->puntaje.ToString() + " ] ";
					SizeF sizeLinea = e->Graphics->MeasureString(linea, fuente);
					float x = (this->ClientSize.Width - sizeLinea.Width) / 2;
					e->Graphics->DrawString(linea, fuente, Brushes::Black, x, y);
					y += espacio;
				}
			}

			Form::OnPaint(e);
		}
	};
}