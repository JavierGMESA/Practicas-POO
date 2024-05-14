#include <iostream>
#include <ctime>
#include <iomanip>
#include <math.h>
#include <cmath>
#include "cadena.hpp"
#include "fecha.hpp"
#include "articulo.hpp"


Articulo::Articulo(Autores& a, const Cadena& Ref, const Cadena& tit, const Fecha& pub, double precio):autores_{a} ,referencia_{Ref}, titulo_{tit}, f_publi_{pub}, precio_{precio}
{
    if(autores_.empty())
    {
        throw Autores_vacios();
    }
}

std::ostream& operator<<(std::ostream& os, const Articulo& art)
{
    //os < '[' << art.referencia() << "] \"" << art.titulo()  << "\", " << art.f_publi().anno() << ". ";
    //os << std::fixed << std::setprecision(2) << art.precio() << " €";

    os << "[" << art.referencia() << "] \"" << art.titulo() << "\", de ";
    Articulo::Autores::const_iterator i = art.autores().begin();
    os << (*i)->apellidos();
    for(++i; i != art.autores().end(); ++i)
    {
        os << ", " << (*i)->apellidos();
    }
    os << ". " << art.f_publi().anno() << ". " << std::fixed << std::setprecision(2) << art.precio() << " €" << std::endl << "\t";
    art.impresion_especifica(os);
    return os;
}

void Libro::impresion_especifica(std::ostream& os) const
{
    os << n_pag() << " págs., " << stock() << " unidades.";
}

void Revista::impresion_especifica(std::ostream& os) const
{
    os << "Número: " << numero() << ", Periodicidad: " << periodicidad() << " días." << std::endl << "\t";
    Fecha f = f_publi();

    //while(f < Fecha())
    //{
        f += perio_; //NO TIENE MUCHO SENTIDO SUMAR LA PERIODICIDAD UNA VEZ PUES YA PUEDE HABERSE ACABADO, PERO BUENO...
    //}

    os << "Próximo número a partir de: " << f << ".";
}

void LibroDigital::impresion_especifica(std::ostream& os) const
{
    os << "A la venta hasta el " << f_expir_ << ".";
}
