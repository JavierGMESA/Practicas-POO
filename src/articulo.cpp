#include <iostream>
#include <ctime>
#include <iomanip>
#include <math.h>
#include <cmath>
#include "cadena.hpp"
#include "fecha.hpp"
#include "articulo.hpp"


Articulo::Articulo(Autores& a, const Cadena& Ref, const Cadena& tit, const Fecha& pub, float precio):autores_{a} ,referencia_{Ref}, titulo_{tit}, f_publi_{pub}, precio_{precio}
{
    if(autores_.empty())
    {
        throw Autores_vacios();
    }
}

std::ostream& operator<<(std::ostream& os, Articulo* art)
{
    //os < '[' << art.referencia() << "] \"" << art.titulo()  << "\", " << art.f_publi().anno() << ". ";
    //os << std::fixed << std::setprecision(2) << art.precio() << " €";
    art->impresion_especifica(os);
    return os;
}

void Libro::impresion_especifica(std::ostream& os) const
{
    os << "[" << referencia() << "] \"" << titulo() << "\", de ";
    Articulo::Autores::const_iterator i = autores_.begin();
    os << (*i)->nombre();
    for(++i; i != autores_.end(); ++i)
    {
        os << ", " << (*i)->nombre();
    }
    os << ". " << f_publi().anno() << ". " << std::fixed << std::setprecision(2) << precio() << " €" << std::endl;
    os << "\t" << n_pag() << " págs., " << stock() << " unidades.";
}

void Revista::impresion_especifica(std::ostream& os) const
{
    os << "[" << referencia() << "] \"" << titulo() << "\", de ";
    Articulo::Autores::const_iterator i = autores_.begin();
    os << (*i)->nombre();
    for(++i; i != autores_.end(); ++i)
    {
        os << ", " << (*i)->nombre();
    }
    os << ". " << f_publi().anno() << ". " << std::fixed << std::setprecision(2) << precio() << " €" << std::endl;
    os << "Número: " << numero() << ", Periodicidad: " << periodicidad() << " días." << std::endl << "\t";
    Fecha f = f_publi();
    while(f < Fecha())
    {
        f += perio_;
    }
    os << "Próximo número a partir de: " << f << ".";
}

void LibroDigital::impresion_especifica(std::ostream& os) const
{
    os << "[" << referencia() << "] \"" << titulo() << "\", de ";
    Articulo::Autores::const_iterator i = autores_.begin();
    os << (*i)->nombre();
    for(++i; i != autores_.end(); ++i)
    {
        os << ", " << (*i)->nombre();
    }
    os << ". " << f_publi().anno() << ". " << std::fixed << std::setprecision(2) << precio() << " €" << std::endl<< "\t";
    os << "A la venta hasta el " << f_expir_ << ".";
}
