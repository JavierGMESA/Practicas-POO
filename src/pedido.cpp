#include "fecha.hpp"
#include "pedido.hpp"
#include "tarjeta.hpp"
#include "usuario.hpp"
#include "articulo.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
#include <iostream>
#include <iomanip>

int Pedido::n_pedidos_{0};

Pedido::Pedido(Usuario_Pedido& rup, Pedido_Articulo& rpa, Usuario& us, const Tarjeta& tar, Fecha f): numero_{n_pedidos_ + 1}, importe_{0.0}, tarjeta_{&tar}, f_pedido_{f}
{
    bool vacio = true;
    if(tar.titular() != &us)
    {
        throw Impostor(us);
    }
    if(us.compra().empty())
    {
        throw Vacio(us);
    }
    if(tar.caducidad() < f_pedido_)
    {
        throw Tarjeta::Caducada(tar.caducidad());
    }
    if(!tar.activa())
    {
        throw Tarjeta::Desactivada();
    }
    //Usuario::Articulos::iterator it;
    for(auto it: us.compra())
    {
        ArticuloAlmacenable *p = dynamic_cast<ArticuloAlmacenable*>(it.first);
        if(p != nullptr)
        {
            if(p->stock() < it.second)
            {
                us.vaciar_carro();
                throw SinStock(*(it.first));
            }
        }
    }
    for(auto it: us.compra())
    {

        ArticuloAlmacenable *p = dynamic_cast<ArticuloAlmacenable*>(it.first);
        if(p == nullptr)
        {
            LibroDigital *l = dynamic_cast<LibroDigital*>(it.first);
            if(l->f_expir() >= Fecha())
            {
                importe_ += it.first->precio() * it.second;
                rpa.pedir(*this, (*(it.first)), it.first->precio(), it.second);
                vacio = false;
            }
        }
        else
        {
            p->stock() -= it.second;
            importe_ += it.first->precio() * it.second;
            rpa.pedir(*this, (*(it.first)), it.first->precio(), it.second);
            vacio = false;
        }
    }
    if(vacio) //Más fácil poner importe == 0
    {
        us.vaciar_carro();
        throw Vacio(us);
    }

    Pedido::n_pedidos_ += 1;
    rup.asocia(us, *this);
    us.vaciar_carro();
    
}

std::ostream& operator <<(std::ostream& os, const Pedido& p)
{
    os << std::endl;
    os << "Núm. pedido: " << p.numero() << std::endl;
    os << "Fecha:       " << p.fecha() << std::endl;
    if(p.tarjeta()->tipo() == Tarjeta::Tipo::Otro)
    {
        os << "Pagado con: Tipo indeterminado";
    }
    else
    {
        os << "Pagado con: " << p.tarjeta()->tipo();
    }
    os << " nº: " << p.tarjeta()->numero() << std::endl;
    os << "Importe: ";
    os << std::fixed << std::setprecision(2) << p.total() << " €" << std::endl;
    return os;
}
