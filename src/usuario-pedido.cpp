#include "usuario-pedido.hpp"
#include "pedido.hpp"
#include "usuario.hpp"
#include <set>
#include <map>



void Usuario_Pedido::asocia(Usuario& us, Pedido& p)
{
    Usuario_Pedido::Pedidos ped;
    std::map<Usuario*, Pedidos>::iterator it = pedidos_.find(&us);
    if(/*!pedidos_.count(&us)*/ it == pedidos_.end())
    {
        ped.insert(&p);
        pedidos_.insert(std::pair<Usuario*, Pedidos>(&us, ped));
    }
    else
    {
        /*ped = pedidos_[&us]*/ it->second.insert(&p);
        //ped.insert(&p);
        //pedidos_[&us] = ped;
    }

    usuarios_.insert(std::pair<Pedido *, Usuario *>(&p, &us));
}

void Usuario_Pedido::asocia(Pedido& p, Usuario& us)
{
    asocia(us, p);
}