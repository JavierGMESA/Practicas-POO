#ifndef USUARIO_PEDIDO_HPP_
#define USUARIO_PEDIDO_HPP_

#include <map>
#include <set>

class Pedido;
class Usuario;



class Usuario_Pedido
{
public:
    typedef std::set<Pedido*> Pedidos;

    Usuario_Pedido(): pedidos_{}, usuarios_{}{}
    void asocia(Usuario& us, Pedido& p);
    void asocia(Pedido& p, Usuario& us);
    const Pedidos& pedidos(Usuario& us){return pedidos_[&us];}
    Usuario* cliente(Pedido& p){return usuarios_[&p];}
private:
    std::map<Usuario*, Pedidos> pedidos_;
    std::map<Pedido*, Usuario*> usuarios_;
};

#endif