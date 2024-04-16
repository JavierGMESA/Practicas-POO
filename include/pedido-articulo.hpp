#ifndef PEDIDO_ARTICULO_HPP_
#define PEDIDO_ARTICULO_HPP_

#include <map>
#include "articulo.hpp"

class Pedido;
//class Articulo;
class LineaPedido;
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