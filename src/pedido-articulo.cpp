#include "pedido-articulo.hpp"
#include "fecha.hpp"
#include "usuario.hpp"
//#include "pedido.hpp"
//#include "articulo.hpp"
//#include "tarjeta.hpp"
//#include "usuario-pedido.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>

std::ostream& operator<<(std::ostream& os, const LineaPedido& l)
{
    os << std::fixed << std::setprecision(2) << l.precio_venta() << " €\t" << l.cantidad();
    return os; //NO OLVIDARSE
}

void Pedido_Articulo::pedir(Pedido& p, Articulo& art, double precio, unsigned cantidad)
{
    p_a_[&p].insert(std::make_pair(&art, LineaPedido(precio, cantidad)));
    a_p_[&art].insert(std::make_pair(&p, LineaPedido(precio, cantidad)));
}

void Pedido_Articulo::pedir(Articulo& art, Pedido& p, double precio, unsigned cantidad)
{
    pedir(p, art, precio, cantidad);
}

const Pedido_Articulo::ItemsPedido Pedido_Articulo::detalle(Pedido& p) const
{
    auto i = p_a_.find(&p);
    if (i == p_a_.end()) return ItemsPedido();
    else return i->second;
    //return i->second;
}

const Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& art) const
{
    auto i = a_p_.find(&art);
    if (i == a_p_.end()) return Pedidos();
    else return i->second;
    //return i->second;
}

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::ItemsPedido& ip)
{
    double importe = 0;
    //Pedido_Articulo::ItemsPedido::const_iterator i;
    os << "  PVP     Cantidad           Articulo" << std::endl;
    os << "===========================================================" << std::endl;
    //for(i = ip.begin(); i != ip.end(); ++i)
    //{
    //    importe += i->second.precio_venta() * i->second.cantidad();
    //    os <<  i->second << "              ";
    //    os << "[" << i->first->referencia() << "] \"" << i->first->titulo() << '\"' << std::endl;
    //}
    for (auto i : ip)
    {
        importe += i.second.cantidad() * i.second.precio_venta();
        os << i.second << "              ";
        os << "[" << i.first->referencia() << "] \"" << i.first->titulo() << "\"" << std::endl;
    }

    os << "===========================================================" << std::endl;
    os << "Total\t" << std::fixed << std::setprecision(2) << importe << " €";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::Pedidos& ip)
{
    double importe = 0;
    int cant = 0;
    //Pedido_Articulo::Pedidos::const_iterator i;
    os << "[Pedidos: " << ip.size() << ']' << std::endl;
    os << "===========================================================" << std::endl;
    os << "  PVP     Cantidad           Fecha de venta" << std::endl;
    os << "===========================================================" << std::endl;
    //for(i = ip.begin(); i != ip.end(); ++i)
    //{
    //    cant += i->second.cantidad();
    //    importe += i->second.precio_venta() * i->second.cantidad();
    //    os <<  i->second << "          ";
    //    os << i->first->fecha() << std::endl;
    //}
    for (auto i : ip)
    {
        cant += i.second.cantidad();
        importe += i.second.cantidad() * i.second.precio_venta();
        os << i.second << "              ";
        os << i.first->fecha() << std::endl;
    }

    os << "===========================================================" << std::endl;
    os << "Total\t" << std::fixed << std::setprecision(2) << importe << " €\t" << cant;
    return os;
}

void Pedido_Articulo::mostrarDetallePedidos(std::ostream& os) const
{
    std::map<Pedido*, Pedido_Articulo::ItemsPedido, Pedido_Articulo::OrdenaPedidos>::const_iterator i;
    //Usuario_Pedido us;
    double importe = 0;
    for(i = p_a_.begin(); i != p_a_.end(); ++i)
    {
        Pedido& p = *(i->first);
        os << "Pedido num. " << p.numero() << std::endl;
        os << "Cliente: " << *(p.tarjeta()->titular()) << std::endl;
        os << "Fecha: " << p.fecha() << std::endl;
        os << detalle(p) << std::endl << std::endl;
        importe += i->first->total();
    }
    os << "TOTAL VENTAS          " << std::fixed << std::setprecision(2) << importe << " €" << std::endl;
}

void Pedido_Articulo::mostrarVentasArticulos(std::ostream& os) const
{
    double importe;
    //std::map<Articulo*, Pedido_Articulo::Pedidos, Pedido_Articulo::OrdenaArticulos>::const_iterator i;
    //Pedido_Articulo::Pedidos::const_iterator j;
    for(/*i = a_p_.begin(); i!= a_p_.end(); ++i*/ auto i: a_p_)
    {
        Articulo& a = /**(i->first);*/ *(i.first);
        importe = 0;
        os << "Ventas de [" << a.referencia() << "] \"" << a.titulo() << '\"' << std::endl;
        for(/*j = ventas(a).begin(); j != ventas(a).end(); ++j*/ auto j: ventas(a)) //IMPORTANTE: LO QUE ESTÁ COMENTADO NO SIVRE PUES CADA VEZ QUE SE LLAMA A ventas(a) EL PUNTERO A end CAMBIA
        {
            Pedido& p = /**(j->first);*/ *(j.first);
            os << "\tPedido num. " << p.numero() << std::endl;
            os << "\tCliente: " << p.tarjeta()->titular()->nombre() << std::endl;
            os << "\tFecha: " << p.fecha() << std::endl << std::endl;
            os << /*i->second;*/ i.second;
            importe += p.total();
        }
        os << "\tTOTAL VENTAS          " << std::fixed << std::setprecision(2) << importe << std::endl << std::endl;
    }
}