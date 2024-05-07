#include "fecha.hpp"
#include "pedido.hpp"
#include "tarjeta.hpp"
#include "usuario.hpp"
#include "articulo.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
#include <iostream>

int Pedido::n_pedidos_{0};

Pedido::Pedido(Usuario_Pedido& rup, Pedido_Articulo& rpa, Usuario& us, Tarjeta& tar, const Fecha& f): numero_{0}, importe_{0.0}, tar_de_pago_{&tar}, f_pedido_{f}
{
    //std::cout << tar.titular()->nombre() << ' ' << us.nombre() << std::endl;
    Usuario::Articulos art_us = us.compra();
    if(art_us.empty())
    {
        throw Pedido::Vacio(us);
    }
    else if(tar.titular() != &us)
    {
        throw Pedido::Impostor(us);
    }
    else if(tar.caducidad() < f_pedido_)
    {
        throw Tarjeta::Caducada(tar.caducidad());
    }
    else if(!tar.activa())
    {
        throw Tarjeta::Desactivada();
    }
    else
    {
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
            importe_ += (*(it->first)).precio() * (it->second);

            rpa.pedir(*this, (*(it->first)), (*(it->first)).precio(), it->second);
        }

        //Al final
        rup.asocia(us, *this);
        //for(it = art_us.begin(); it != art_us.end(); ++it)
        //{
        //    //rpa.nombredelafuncion(*this, *(it->first))
        //}
        Pedido::n_pedidos_ += 1;
        numero_ = Pedido::n_pedidos_;
        us.vaciar_carro();
    }
    
}

std::ostream& operator <<(std::ostream& os, const Pedido& p)
{
    os << "Núm. pedido: " << p.numero() << std::endl;
    os << "Fecha:       " << p.fecha() << std::endl;
    os << "Pagado con:  " << (*(p.tarjeta())).tipo() << " n.º: " << (*(p.tarjeta())).numero() << std::endl;
    os << "Importe:     " << p.total() << " €";
    return os;
}
