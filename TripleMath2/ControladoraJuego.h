#pragma once
#include "Figuras.h"

using namespace System;
using namespace System::Drawing;

public ref class ControladoraJuego
{
public:
    literal int COLUMNAS = 7;
    literal int FILAS = 8;
    literal int ANCHO_CELDA = 60;
    literal int ALTO_CELDA = 60;
    literal int ORIGEN_X = 20;
    literal int ORIGEN_Y = 60;

    array<Figura^, 2>^ tablero;
    Figura^ figuraActual;
    int puntaje;
    Random^ aleatorio;

    ControladoraJuego() {
        tablero = gcnew array<Figura^, 2>(FILAS, COLUMNAS);
        figuraActual = nullptr;
        puntaje = 0;
        aleatorio = gcnew Random();
        NuevaFigura();
    }

    void NuevaFigura() {
        int tipo = aleatorio->Next(3);
        int colorIdx = aleatorio->Next(3);
        Color color = colorIdx == 0 ? Color::Red : (colorIdx == 1 ? Color::Blue : Color::Yellow);
        int valor = aleatorio->Next(10);
        int col = COLUMNAS / 2;
        if (tipo == 0)
            figuraActual = gcnew Circulo(col, 0, valor, NivelFigura::Nivel1, color);
        else if (tipo == 1)
            figuraActual = gcnew Cuadrado(col, 0, valor, NivelFigura::Nivel1, color);
        else
            figuraActual = gcnew Triangulo(col, 0, valor, NivelFigura::Nivel1, color);
    }

    bool PuedeMover(int dcol) {
        if (!figuraActual) return false;
        int nc = figuraActual->columna + dcol;
        if (nc < 0 || nc >= COLUMNAS) return false;
        if (tablero[figuraActual->fila, nc] != nullptr) return false;
        return true;
    }

    bool PuedeBajar() {
        if (!figuraActual) return false;
        int nf = figuraActual->fila + 1;
        if (nf >= FILAS) return false;
        if (tablero[nf, figuraActual->columna] != nullptr) return false;
        return true;
    }

    void ColocarFigura() {
        tablero[figuraActual->fila, figuraActual->columna] = figuraActual;
        RevisarColisiones(figuraActual->fila, figuraActual->columna);
        figuraActual = nullptr;
        if (!EsFinJuego()) NuevaFigura();
    }

    void RevisarColisiones(int f, int c) {
        Figura^ fig = tablero[f, c];
        if (f + 1 < FILAS && tablero[f + 1, c] != nullptr) {
            Figura^ abajo = tablero[f + 1, c];
            if (fig->EsMismoTipo(abajo)) {
                if (fig->nivel == NivelFigura::Nivel1) {
                    int nuevoValor = fig->valor + abajo->valor;
                    puntaje += nuevoValor;
                    tablero[f + 1, c] = nullptr;
                    if (fig->tipo == TipoFigura::Circulo)
                        tablero[f, c] = gcnew Circulo(c, f, nuevoValor, NivelFigura::Nivel2, fig->color);
                    else if (fig->tipo == TipoFigura::Cuadrado)
                        tablero[f, c] = gcnew Cuadrado(c, f, nuevoValor, NivelFigura::Nivel2, fig->color);
                    else
                        tablero[f, c] = gcnew Triangulo(c, f, nuevoValor, NivelFigura::Nivel2, fig->color);
                }
                else if (fig->nivel == NivelFigura::Nivel2) {
                    int nuevoValor = (fig->valor + abajo->valor) * 2;
                    puntaje += nuevoValor;
                    tablero[f + 1, c] = nullptr;
                    tablero[f, c] = nullptr;
                }
            }
            else {
                int minv = System::Math::Min(fig->valor, abajo->valor);
                puntaje -= minv;
            }
        }
    }

    bool EsFinJuego() {
        int ocupadas = 0;
        for (int f = 0; f < FILAS; ++f) {
            bool alguna = false;
            for (int c = 0; c < COLUMNAS; ++c)
                if (tablero[f, c] != nullptr) alguna = true;
            if (alguna) ocupadas++;
        }
        return ocupadas >= 5;
    }

    void MoverFigura(int dcol) {
        if (PuedeMover(dcol)) figuraActual->columna += dcol;
    }

    void BajarFigura() {
        while (PuedeBajar()) figuraActual->fila++;
        ColocarFigura();
    }

    void Paso() {
        if (!figuraActual) return;
        if (PuedeBajar()) {
            figuraActual->fila++;
        }
        else {
            ColocarFigura();
        }
    }

    void Dibujar(Graphics^ g) {
        // Cuadrícula
        Pen^ lapizGrid = gcnew Pen(Color::LightGray);
        for (int i = 0; i <= COLUMNAS; ++i)
            g->DrawLine(lapizGrid, ORIGEN_X + i * ANCHO_CELDA, ORIGEN_Y, ORIGEN_X + i * ANCHO_CELDA, ORIGEN_Y + FILAS * ALTO_CELDA);
        for (int i = 0; i <= FILAS; ++i)
            g->DrawLine(lapizGrid, ORIGEN_X, ORIGEN_Y + i * ALTO_CELDA, ORIGEN_X + COLUMNAS * ANCHO_CELDA, ORIGEN_Y + i * ALTO_CELDA);

        // Figuras en tablero
        for (int f = 0; f < FILAS; ++f)
            for (int c = 0; c < COLUMNAS; ++c)
                if (tablero[f, c] != nullptr)
                    tablero[f, c]->Dibujar(g, ORIGEN_X, ORIGEN_Y, ANCHO_CELDA, ALTO_CELDA);

        // Figura cayendo
        if (figuraActual != nullptr)
            figuraActual->Dibujar(g, ORIGEN_X, ORIGEN_Y, ANCHO_CELDA, ALTO_CELDA);
    }
};