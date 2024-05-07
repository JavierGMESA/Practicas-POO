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
    Pedidos pedidos(Usuario& us) const; //RECORDAR QUE NO SE PUEDEN PASAR const PUES LA CLAVE DEL MAP NO ES CONSTANTE
    Usuario* cliente(Pedido& p) const; 
private:
    std::map<Usuario*, Pedidos> pedidos_;
    std::map<Pedido*, Usuario*> usuarios_;
};

#endif