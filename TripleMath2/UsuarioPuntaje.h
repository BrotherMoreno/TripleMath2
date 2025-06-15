#pragma once

using namespace System;

namespace TripleMath {

    public ref class UsuarioPuntaje
    {
    public:
        String^ nombre;
        int puntaje;

        UsuarioPuntaje(String^ n, int p)
        {
            nombre = n;
            puntaje = p;
        }
    };

}