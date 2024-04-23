#ifndef PEDIDO_ARTICULO_HPP_
#define PEDIDO_ARTICULO_HPP_

#include <map>
#include "articulo.hpp"
#include "pedido.hpp"
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
        bool operator()(Articulo* a1, Articulo* a2){return a1->referencia() < a2->referencia();}
        //bool operator()(Articulo& a1, Articulo& a2){return a1.referencia() < a2.referencia();}
    };
    class OrdenaPedidos
    {
    public:
        bool operator()(Pedido* p1, Pedido* p2){return p1->numero() < p2->numero();}
        //bool operator()(Pedido& p1, Pedido& p2){return p1.numero() < p2.numero();}
    };

    typedef std::map<Articulo*, LineaPedido, OrdenaArticulos()> ItemsPedido;
    typedef std::map<Pedido*, LineaPedido, OrdenaPedidos()> Pedidos;

    void pedir(Pedido& p, Articulo& art, float precio, int cantidad = 1);
    void pedir(Articulo& art, Pedido& p, float precio, int cantidad = 1);

    const ItemsPedido& detalle(Pedido& p) const {return p_a_.find(&p)->second;}
    const Pedidos& ventas(Articulo& art) const {return a_p_.find(&art)->second;}

    friend void mostrarDetallePedidos(std::ostream& os, const Pedido_Articulo& p); //QUEDA POR IMPLEMENTAR
    friend void mostrarVentasArticulos(std::ostream& os, const Pedido_Articulo& p);
    
private:
     std::map<Pedido*, ItemsPedido, OrdenaPedidos> p_a_;
     std::map<Articulo*, Pedidos, OrdenaArticulos> a_p_;
};

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::ItemsPedido& ip);
std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::Pedidos& ip);


#endif