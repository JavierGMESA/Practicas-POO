#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include "cadena.hpp"
#include "fecha.hpp"
#include "articulo.hpp"
#include "usuario.hpp"
#include <iostream>

class Tarjeta;
//class Articulo;
class Usuario_Pedido;
class Pedido_Articulo;
//class Usuario;
class Pedido
{

public:

    class Vacio
    {
    public:
        Vacio(Usuario& us): us_{&us}{}
        Usuario* usuario() const{return us_;}
    private:
        Usuario* us_;
    };

    class Impostor
    {
    public:
        Impostor(Usuario& us): us_{&us}{}
        Usuario* usuario() const{return us_;}
    private:
        Usuario* us_;
    };

    class SinStock
    {
    public:
        SinStock(Articulo& art): art_{&art}{}
        Articulo* articulo() const{return art_;}
    private:
        Articulo* art_;
    };


    Pedido(Usuario_Pedido& rup, Pedido_Articulo& rpa, Usuario& us, Tarjeta& tar, const Fecha& f = Fecha()); //POR TERMINAR

    int numero() const {return numero_;}
    const Tarjeta* tarjeta() const {return tar_de_pago_;}
    const Fecha& fecha() const {return f_pedido_;}
    float total() const {return importe_;}
    int total_pedidos() const {return Pedido::n_pedidos_;}

private:
    float importe_;
    int numero_,;
    const Tarjeta* tar_de_pago_;
    Fecha f_pedido_;
    static int n_pedidos_;
};

std::ostream& operator <<(std::ostream& os, const Pedido& p);



#endif