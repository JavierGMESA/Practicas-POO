#include "pedido.hpp"
#include "tarjeta.hpp"
#include "usuario.hpp"
#include "articulo.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
#include <iostream>

int Pedido::n_pedidos_{0};

Pedido::Pedido(Usuario_Pedido& rup, Pedido_Articulo& rpa, Usuario& us, Tarjeta& tar, const Fecha& f): numero_{0}, importe_{0}, tar_de_pago_{&tar}, f_pedido_{f}
{
    Usuario::Articulos art_us = us.compra();
    if(art_us.size() == 0)
    {
        throw Pedido::Vacio(us);
    }
    if(tar.titular() != &us)
    {
        throw Pedido::Impostor(us);
    }
    if(tar.caducidad() < f_pedido_)
    {
        throw Tarjeta::Caducada(tar.caducidad());
    }
    if(!tar.activa())
    {
        throw Tarjeta::Desactivada();
    }
    Usuario::Articulos::iterator it;
    for(it = art_us.begin(); it != art_us.end(); ++it)
    {
        if((*(it->first)).stock() < it->second)
        {
            throw Pedido::SinStock(*(it->first));
        }
    }
    for(it = art_us.begin(); it != art_us.end(); ++it)
    {
        (*(it->first)).stock() -= it->second;
        importe_ += (*(it->first)).precio() * it->second;
    }
    
    //Al final
    rup.asocia(us, *this);
    for(it = art_us.begin(); it != art_us.end(); ++it)
    {
        //rpa.nombredelafuncion(*this, *(it->first))
    }
    Pedido::n_pedidos_ += 1;
    numero_ = Pedido::n_pedidos_;
    us.vaciar_carro();
}

std::ostream& operator <<(std::ostream& os, const Pedido& p)
{
    os << "Núm. pedido: " << p.numero() << std::endl;
    os << "Fecha:       " << p.fecha() << std::endl;
    os << "Pagado con:  " << (*(p.tarjeta())).tipo() << " n.º: " << (*(p.tarjeta())).numero();
    os << "Importe:     " << p.total() << " €";
    return os;
}
