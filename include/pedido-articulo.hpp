#ifndef PEDIDO_ARTICULO_HPP_
#define PEDIDO_ARTICULO_HPP_

#include <map>
#include "articulo.hpp"
#include <iostream>

class Pedido;
//class Articulo;
class LineaPedido
{
public:
    explicit LineaPedido(float precio = 0.0, int cant = 1): precio_v_{precio}, cant_{cant}{}
    float precio_venta() const {return precio_v_;}
    int cantidad() const {return cant_;}
private:
    float precio_v_;
    int cant_;
};

std::ostream& operator<<(std::ostream& os, const LineaPedido& l);



class Pedido_Articulo
{
public:
    class OrdenaArticulos
    {
    public:
        bool operator()(const Articulo* a1, const Articulo* a2){return a1->referencia() > a2->referencia();}
    };
    class OrdenaPedidos
    {
    public:
        bool operator()(const Articulo* p1, const Articulo* p2){return ;}
    }

    typedef std::map<Articulo *, LineaPedido, OrdenaArticulos> ItemsPedido;
private:

};

#endif