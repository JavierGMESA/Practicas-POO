#include "pedido-articulo.hpp"
#include "fecha.hpp"
#include "usuario.hpp"
//#include "pedido.hpp"
//#include "articulo.hpp"
//#include "tarjeta.hpp"
//#include "usuario-pedido.hpp"
#include <iostream>
#include <cmath>

std::ostream& operator<<(std::ostream& os, const LineaPedido& l)
{
    //std::ceil(l.precio_venta() * 100.0) / 100.0
    os << std::ceil(l.precio_venta() * 100.0) / 100.0 << " €\t" << l.cantidad();
}

void Pedido_Articulo::pedir(Pedido& p, Articulo& art, float precio, int cantidad)
{
    LineaPedido lp{precio, cantidad};
    p_a_[&p].insert(std::pair<Articulo*, LineaPedido>(&art, lp));
    a_p_[&art].insert(std::pair<Pedido*, LineaPedido>(&p, lp));
}

void Pedido_Articulo::pedir(Articulo& art, Pedido& p, float precio, int cantidad)
{
    pedir(p, art, precio, cantidad);
}

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::ItemsPedido& ip)
{
    int importe = 0;
    Pedido_Articulo::ItemsPedido::const_iterator i;
    os << "PVP   Cantidad        Artículo" << std::endl;
    os.fill('=');
    os.width(60);
    os << "" << std::endl;
    for(i = ip.begin(); i != ip.end(); ++i)
    {
        //std::ceil(i->second.precio_venta() * 100.0) / 100.0
        importe += i->second.precio_venta() * i->second.cantidad();
        os << /*std::ceil(i->second.precio_venta() * 100.0) / 100.0  << " € " << i->second.cantidad()*/ i->second;
        os << "               [" << (*(i->first)).referencia() << "] " << '"' << (*(i->first)).titulo() << '"' << std::endl;
    }
    os.fill('=');
    os.width(60);
    os << "" << std::endl;
    os << "Total\t" << /*std::ceil(importe * 100.0) / 100.0*/ importe << " €";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::Pedidos& ip)
{
    int importe = 0;
    Pedido_Articulo::Pedidos::const_iterator i;
    os << "[Pedidos: " << ip.size() << ']' << std::endl;
    os.fill('=');
    os.width(60);
    os << "" << std::endl;
    os << "PVP   Cantidad        Fecha de venta" << std::endl;
    os.fill('=');
    os.width(60);
    os << "" << std::endl;
    for(i = ip.begin(); i != ip.end(); ++i)
    {
        importe += i->second.precio_venta() * i->second.cantidad();
        os << /*std::ceil(i->second.precio_venta() * 100.0) / 100.0 << " € " << i->second.cantidad() */ i->second;
        os << "          " << (*(i->first)).fecha() << std::endl;
    }
    os.fill('=');
    os.width(60);
    os << "" << std::endl;
    os << "Total\t" << /*std::ceil(importe * 100.0) / 100.0*/ importe << " €\t";
    return os;
}

void mostrarDetallePedidos(std::ostream& os, const Pedido_Articulo& p)
{
    std::map<Pedido*, Pedido_Articulo::ItemsPedido, Pedido_Articulo::OrdenaPedidos>::const_iterator i;
    //Usuario_Pedido us;
    float importe = 0;
    for(i = p.p_a_.begin(); i != p.p_a_.end(); ++i)
    {
        os << "Pedido núm. " << (*(i->first)).numero() << std::endl;
        os << "Cliente: " << (*(i->first)).tarjeta()->titular()->nombre();
        os << "          Fecha: " << (*(i->first)).fecha() << std::endl;
        os << i->second << std::endl;
        importe += (*(i->first)).total();
    }
    os << "TOTAL VENTAS          " << importe << " €";
}

void mostrarVentasArticulos(std::ostream& os, const Pedido_Articulo& p)
{
    std::map<Articulo*, Pedido_Articulo::Pedidos, Pedido_Articulo::OrdenaArticulos>::const_iterator i;
    Pedido_Articulo::Pedidos::const_iterator j;
    float importe = 0;
    for(i = p.a_p_.begin(); i!= p.a_p_.end(); ++i)
    {
        os << "Ventas de [" << (*(i->first)).referencia() << "] " << '"' << (*(i->first)).titulo() << '"' << std::endl;
        os << i->second << std::endl;
        //for(j = i->second.begin(); j != i->second.end(); ++j)
        //{
        //    os << "\tPedido núm. " << (*(j->first)).numero() << std::endl;
        //    os << "\tCliente: " << (*(j->first)).tarjeta()->titular()->nombre() << std::endl;
        //    os << "\tFecha: " << (*(j->first)).fecha() << std::endl;
        //    importe += (*(j->first)).total();
        //}
        //os << "TOTAL VENTAS          " << importe << " €";
    }
}