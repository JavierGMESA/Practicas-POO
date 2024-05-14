#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include "cadena.hpp"
#include "fecha.hpp"
//#include "articulo.hpp"
//#include "usuario.hpp"
#include "tarjeta.hpp"
#include <iostream>

class Usuario;
class Tarjeta;
//class Fecha;
class Articulo;
class Usuario_Pedido;
class Pedido_Articulo;
//class Usuario;
class Pedido
{

public:

    Pedido(Usuario_Pedido& rup, Pedido_Articulo& rpa, Usuario& us, const Tarjeta& tar, Fecha f = Fecha());

    class Vacio;
    class Impostor;
    class SinStock;

    int numero() const {return numero_;}
    const Tarjeta* tarjeta() const {return tarjeta_;}
    const Fecha& fecha() const {return f_pedido_;}
    double total() const {return importe_;}
    static int n_total_pedidos() {return Pedido::n_pedidos_;}

private:
    double importe_;
    int numero_;
    const Tarjeta* tarjeta_;
    Fecha f_pedido_;
    static int n_pedidos_;
};

std::ostream& operator <<(std::ostream& os, const Pedido& p);

class Pedido::Vacio
    {
    public:
        Vacio(const Usuario& us): us_{us}{}
        const Usuario& usuario() const{return us_;}
    private:
        const Usuario& us_; //¿ por que se debe declarar como referencia constante?
    };

    class Pedido::Impostor
    {
    public:
        Impostor(const Usuario& us): us_{us}{}
        const Usuario& usuario() const{return us_;}
    private:
        const Usuario& us_;
    };

    class Pedido::SinStock
    {
    public:
        SinStock(const Articulo& art): art_{art}{}
        const Articulo& articulo() const{return art_;}
    private:
        const Articulo& art_;
    };


#endif