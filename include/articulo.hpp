#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include "fecha.hpp"
#include "cadena.hpp"
//class Cadena;
//class Fecha;
class Articulo
{
public:
    Articulo(const Cadena& Ref, const Cadena& tit, const Fecha& pub, float precio, unsigned stk);
    const Cadena& referencia() const {return referencia_;}
    const Cadena& titulo() const {return titulo_;}
    const Fecha& f_publi() const {return f_publi_;}
    float precio() const {return precio_;}
    float& precio() {return precio_;}
    unsigned stock() const {return stock_;}
    unsigned& stock() {return stock_;}
private:
    const Cadena referencia_, titulo_;
    const Fecha f_publi_;
    float precio_;
    unsigned stock_;
};

std::ostream& operator<<(std::ostream& os, const Articulo& art);

#endif