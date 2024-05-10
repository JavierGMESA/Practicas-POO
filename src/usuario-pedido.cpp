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
        pedidos_.insert(std::make_pair(&us, ped));
    }
    else
    {
        /*ped = pedidos_[&us]*/ it->second.insert(&p);
        //ped.insert(&p);
        //pedidos_[&us] = ped;
    }

    usuarios_.insert(std::pair<Pedido *, Usuario *>(&p, &us)); //sería mejor un make_pair
}

Usuario_Pedido::Pedidos Usuario_Pedido::pedidos(Usuario& us) const
{
    if(pedidos_.find(&us) == pedidos_.end())
    {
        return Usuario_Pedido::Pedidos();
    }
    else
    {
        return pedidos_.at(&us); //NO DEBO USAR [] PORQUE NO EXISTE SOBRECARGA CONST DE ESTOS
    }
}

Usuario* Usuario_Pedido::cliente(Pedido& p) const
{
    if(usuarios_.find(&p) == usuarios_.end())
    {
        return nullptr;
    }
    else
    {
        return usuarios_.at(&p);
    }
}


void Usuario_Pedido::asocia(Pedido& p, Usuario& us)
{
    asocia(us, p);
}