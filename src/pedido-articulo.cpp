#include "pedido-articulo.hpp"
#include "fecha.hpp"
//#include "pedido.hpp"
//#include "articulo.hpp"
//#include "tarjeta.hpp"
//#include "usuario-pedido.hpp"
#include <iostream>
#include <cmath>

std::ostream& operator<<(std::ostream& os, const LineaPedido& l)
{
    os << l.precio_venta() << " €   " << l.cantidad();
}

void Pedido_Articulo::pedir(Pedido& p, Articulo& art, float precio, int cantidad)
{
    LineaPedido lp{precio, cantidad};
    p_a_[&p].insert(std::pair<Articulo*, LineaPedido>(&art, lp));
    a_p_[&art].insert(std::pair<Pedido*, LineaPedido>(&p, lp));
    //std::map<Pedido*, ItemsPedido, OrdenaPedidos>::iterator it1 = p_a_.find(&p);
    //if(/*p_a_.count(&p)*/it1 != p_a_.end())
    //{
    //    //ItemsPedido& ip = p_a_[&p];
    //    //ip.insert(std::make_pair(&art, lp));
    //    it1->second.insert(std::make_pair(&art, lp));
    //}
    //else
    //{
    //    p_a_.insert(std::pair<Pedido*, ItemsPedido>(&p, ip));
    //}

    //std::map<Articulo*, Pedidos, OrdenaArticulos>::iterator it2 = a_p_.find(&art);
    

    //if(it2 != a_p_.end())
    //{
    //    Pedidos& ip = a_p_[&art];
    //    ip.insert(std::make_pair(&p, lp));
    //}
    //else
    //{
    //    Pedidos ip;
    //    ip[&p] = lp;
    //    a_p_[&art] = ip;
    //}
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
        os << std::ceil(i->second.precio_venta() * 100.0) / 100.0 << " € " << i->second.cantidad();
        os << "               [" << (*(i->first)).referencia() << "] " << '"' << (*(i->first)).titulo() << '"' << std::endl;
    }
    os.fill('=');
    os.width(60);
    os << "" << std::endl;
    os << "Total   " << std::ceil(importe * 100.0) / 100.0 << " €";
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
    os << "PVP   Cantidad        Artículo" << std::endl;
    os.fill('=');
    os.width(60);
    os << "" << std::endl;
    for(i = ip.begin(); i != ip.end(); ++i)
    {
        //std::ceil(i->second.precio_venta() * 100.0) / 100.0
        importe += i->second.precio_venta() * i->second.cantidad();
        os << std::ceil(i->second.precio_venta() * 100.0) / 100.0 << " € " << i->second.cantidad();
        os << "          " << (*(i->first)).fecha() << std::endl;
    }
    os.fill('=');
    os.width(60);
    os << "" << std::endl;
    os << "Total   " << std::ceil(importe * 100.0) / 100.0 << " €";
    return os;
}

void mostrarDetallePedidos(std::ostream& os, const Pedido_Articulo& p)
{
    std::map<Pedido*, Pedido_Articulo::ItemsPedido, Pedido_Articulo::OrdenaPedidos>::const_iterator i;
    //Usuario_Pedido us;
    int importe = 0;
    for(i = p.p_a_.begin(); i != p.p_a_.end(); ++i)
    {
        os << "Pedido núm. " << (*(i->first)).numero() << std::endl;
        os << "Cliente: " << (*(i->first)).tarjeta()->titular() << std::endl;
        os << "          Fecha: " << (*(i->first)).fecha() << std::endl;
        os << i->second << std::endl;
        importe += (*(i->first)).total();
    }
    os << "TOTAL VENTAS          " << std::ceil(importe * 100.0) / 100.0 << " €";
}

void mostrarVentasArticulos(std::ostream& os, const Pedido_Articulo& p)
{
    std::map<Articulo*, Pedido_Articulo::Pedidos, Pedido_Articulo::OrdenaArticulos>::const_iterator i;
    for(i = p.a_p_.begin(); i!= p.a_p_.end(); ++i)
    {
        os << "Ventas de [" << (*(i->first)).referencia() << "] " << '"' << (*(i->first)).titulo() << '"' << std::endl;
        os << i->second << std::endl;
    }
}