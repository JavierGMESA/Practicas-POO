#include <iostream>
#include <ctime>
#include <iomanip>
#include <math.h>
#include <cmath>
#include "cadena.hpp"
#include "fecha.hpp"
#include "articulo.hpp"


Articulo::Articulo(const Cadena& Ref, const Cadena& tit, const Fecha& pub, float precio, unsigned stk): referencia_{Ref}, titulo_{tit}, f_publi_{pub}, precio_{precio}, stock_{stk} {}

std::ostream& operator<<(std::ostream& os, const Articulo& art)
{
    os << '[' << art.referencia() << "] \"" << art.titulo()  << "\", " << art.f_publi().anno() << ". ";
    os << std::fixed << std::setprecision(2) << art.precio() << " €";
    return os;
}