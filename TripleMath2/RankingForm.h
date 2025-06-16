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

	public:


		static String^ usuarioActual = nullptr;

		RankingForm(void)
		{
			InitializeComponent();
			this->DoubleBuffered = true;
			this->ClientSize = System::Drawing::Size(500, 600);

			try {
				this->fondo = Image::FromFile("FondoHorizontalJuego.jpg");
			}
			catch (...) {
				this->fondo = nullptr;
			}
		}


		static void RegistrarUsuario(String^ nombre) {
			usuarioActual = nombre;
		}
		static void AgregarUsuarioPuntajeActual(int puntaje) {
			if (!String::IsNullOrEmpty(usuarioActual)) {
				ranking->Add(gcnew UsuarioPuntaje(usuarioActual, puntaje));
			}
		}

		void AgregarUsuarioPuntaje(String^ nombre, int puntaje) {
			ranking->Add(gcnew UsuarioPuntaje(nombre, puntaje));
		}

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
			if (fondo != nullptr)
				delete fondo;
		}

	private:
		System::ComponentModel::Container^ components;
		Image^ fondo; // Imagen de fondo
		System::Windows::Forms::Button^ btnLimpiar; // Botón Limpiar

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(RankingForm::typeid));
			this->btnLimpiar = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btnLimpiar
			// 
			this->btnLimpiar->Location = System::Drawing::Point(10, 550); 
			this->btnLimpiar->Name = L"btnLimpiar";
			this->btnLimpiar->Size = System::Drawing::Size(90, 30);
			this->btnLimpiar->TabIndex = 1;
			this->btnLimpiar->Text = L"Limpiar";
			this->btnLimpiar->UseVisualStyleBackColor = true;
			this->btnLimpiar->Click += gcnew System::EventHandler(this, &RankingForm::btnLimpiar_Click);
			// 
			// RankingForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(500, 600);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->Controls->Add(this->btnLimpiar);
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
	private: System::Void btnLimpiar_Click(System::Object^ sender, System::EventArgs^ e) {
		// Limpiar ranking en memoria
		ranking->Clear();
		// Limpiar archivo
		try {
			System::IO::File::WriteAllText("ranking.txt", "");
		}
		catch (System::Exception^ ex) {
			MessageBox::Show("Error al limpiar el archivo: " + ex->Message);
		}
		this->Invalidate(); // Refrescar la pantalla
	}
	protected:
		virtual void OnPaint(PaintEventArgs^ e) override {
		
			if (fondo != nullptr) {
				e->Graphics->DrawImage(fondo, 0, 0, this->ClientSize.Width, this->ClientSize.Height);
			}
			else {
				e->Graphics->Clear(Color::White);
			}

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