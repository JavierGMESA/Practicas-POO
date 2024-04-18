#include <iostream>
#include <ctime>
#include <iomanip>
#include <math.h>
#include <cmath>
#include "articulo.hpp"
#include "cadena.hpp"
#include "fecha.hpp"


Articulo::Articulo(const Cadena& Ref, const Cadena& tit, const Fecha& pub, float precio, unsigned stk): referencia_{Ref}, titulo_{tit}, f_publi_{pub}, precio_{precio}, stock_{stk} {}

std::ostream& operator<<(std::ostream& os, const Articulo& art)
{
    float PEntera, Pdecimal;
    int Pd;
    //Pdecimal = modf(art.precio(), &PEntera);
    //Pd = Pdecimal * 100;
    //std::locale localidad("");
    //os.imbue(localidad);
    os << '[' << art.referencia() << "]" << ' ' << '"' << art.titulo() << '"' << ", " << art.f_publi().anno() << ". ";
    os <</* PEntera << ","  art.precio()*/ /* << " €" */ std::ceil(art.precio() * 100.0) / 100.0 << " €";
    //if(Pd == 0)
    //{
    //    os << "00";
    //}
    //else
    //{
    //    if(Pd < 10)
    //    {
    //        os << '0' << Pd;
    //    }
    //    else
    //    {
    //        os  << Pd;
    //    }
    //}
    //os << " €";
    return os;
}