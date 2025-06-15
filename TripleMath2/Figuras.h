#pragma once
#include <vector>
using namespace System::Drawing;
using namespace System::Collections::Generic;

public enum class TipoFigura { Circulo, Cuadrado, Triangulo };
public enum class NivelFigura { Nivel1 = 1, Nivel2, Nivel3 };

public ref class Figura abstract
{
public:
    int columna, fila;
    int valor;
    TipoFigura tipo;
    NivelFigura nivel;
    Color color;

    Figura(int col, int fil, int val, TipoFigura t, NivelFigura n, Color clr)
        : columna(col), fila(fil), valor(val), tipo(t), nivel(n), color(clr) {
    }

    virtual void Dibujar(Graphics^ g, int origenX, int origenY, int anchoCelda, int altoCelda)
    {
        int x = origenX + columna * anchoCelda;
        int y = origenY + fila * altoCelda;
        int tam = (nivel == NivelFigura::Nivel1) ? 40 : (nivel == NivelFigura::Nivel2 ? 54 : 60);
        int cx = x + anchoCelda / 2;
        int cy = y + altoCelda / 2;

        Pen^ lapiz = gcnew Pen(Color::FromArgb(60, 60, 60), 2);
        SolidBrush^ pincel = gcnew SolidBrush(color);

        // El dibujo específico se hace en las clases hijas
    }

    virtual bool EsMismoTipo(Figura^ otra)
    {
        return tipo == otra->tipo && color.ToArgb() == otra->color.ToArgb() && nivel == otra->nivel;
    }
};

public ref class Circulo : public Figura
{
public:
    Circulo(int col, int fil, int val, NivelFigura n, Color clr)
        : Figura(col, fil, val, TipoFigura::Circulo, n, clr) {
    }

    virtual void Dibujar(Graphics^ g, int origenX, int origenY, int anchoCelda, int altoCelda) override
    {
        int x = origenX + columna * anchoCelda;
        int y = origenY + fila * altoCelda;
        int tam = (nivel == NivelFigura::Nivel1) ? 40 : (nivel == NivelFigura::Nivel2 ? 54 : 60);
        int cx = x + anchoCelda / 2;
        int cy = y + altoCelda / 2;

        Pen^ lapiz = gcnew Pen(Color::FromArgb(60, 60, 60), 2);
        SolidBrush^ pincel = gcnew SolidBrush(color);

        g->FillEllipse(pincel, cx - tam / 2, cy - tam / 2, tam, tam);
        g->DrawEllipse(lapiz, cx - tam / 2, cy - tam / 2, tam, tam);

        // Valor
        System::Drawing::Font^ fuente = gcnew System::Drawing::Font("Arial", 16, FontStyle::Bold);
        SolidBrush^ pincelTexto = gcnew SolidBrush(Color::Black);
        g->DrawString(valor.ToString(), fuente, pincelTexto, cx - 10, cy - 15);
    }
};

public ref class Cuadrado : public Figura
{
public:
    Cuadrado(int col, int fil, int val, NivelFigura n, Color clr)
        : Figura(col, fil, val, TipoFigura::Cuadrado, n, clr) {
    }

    virtual void Dibujar(Graphics^ g, int origenX, int origenY, int anchoCelda, int altoCelda) override
    {
        int x = origenX + columna * anchoCelda;
        int y = origenY + fila * altoCelda;
        int tam = (nivel == NivelFigura::Nivel1) ? 40 : (nivel == NivelFigura::Nivel2 ? 54 : 60);
        int cx = x + anchoCelda / 2;
        int cy = y + altoCelda / 2;

        Pen^ lapiz = gcnew Pen(Color::FromArgb(60, 60, 60), 2);
        SolidBrush^ pincel = gcnew SolidBrush(color);

        g->FillRectangle(pincel, cx - tam / 2, cy - tam / 2, tam, tam);
        g->DrawRectangle(lapiz, cx - tam / 2, cy - tam / 2, tam, tam);

        System::Drawing::Font^ fuente = gcnew System::Drawing::Font("Arial", 16, FontStyle::Bold);
        SolidBrush^ pincelTexto = gcnew SolidBrush(Color::Black);
        g->DrawString(valor.ToString(), fuente, pincelTexto, cx - 10, cy - 15);
    }
};

public ref class Triangulo : public Figura
{
public:
    Triangulo(int col, int fil, int val, NivelFigura n, Color clr)
        : Figura(col, fil, val, TipoFigura::Triangulo, n, clr) {
    }

    virtual void Dibujar(Graphics^ g, int origenX, int origenY, int anchoCelda, int altoCelda) override
    {
        int x = origenX + columna * anchoCelda;
        int y = origenY + fila * altoCelda;
        int tam = (nivel == NivelFigura::Nivel1) ? 40 : (nivel == NivelFigura::Nivel2 ? 54 : 60);
        int cx = x + anchoCelda / 2;
        int cy = y + altoCelda / 2;

        Pen^ lapiz = gcnew Pen(Color::FromArgb(60, 60, 60), 2);
        SolidBrush^ pincel = gcnew SolidBrush(color);

        array<Point>^ puntos = gcnew array<Point>{
            Point(cx, cy - tam / 2),
                Point(cx - tam / 2, cy + tam / 2),
                Point(cx + tam / 2, cy + tam / 2)
        };
        g->FillPolygon(pincel, puntos);
        g->DrawPolygon(lapiz, puntos);

        System::Drawing::Font^ fuente = gcnew System::Drawing::Font("Arial", 16, FontStyle::Bold);
        SolidBrush^ pincelTexto = gcnew SolidBrush(Color::Black);
        g->DrawString(valor.ToString(), fuente, pincelTexto, cx - 10, cy - 15);
    }
};