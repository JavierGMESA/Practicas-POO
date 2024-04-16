#include "usuario-pedido.hpp"
#include "pedido.hpp"
#include "usuario.hpp"



void Usuario_Pedido::asocia(Usuario& us, Pedido& p)
{
    Usuario_Pedido::Pedidos ped;
    if(!pedidos_.count(&us))
    {
        ped.insert(&p);
        pedidos_.insert(std::pair<Usuario*, Pedidos>(&us, ped));
    }
    else
    {
        ped = pedidos_[&us];
        ped.insert(&p);
        pedidos_[&us] = ped;
    }

    if(!usuarios_.count(&p))
    {
        usuarios_.insert(std::pair<Pedido *, Usuario *>(&p, &us));
    }
}