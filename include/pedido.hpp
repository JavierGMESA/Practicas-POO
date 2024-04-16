#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include "cadena.hpp"
#include "fecha.hpp"

class Tarjeta;
class Usuario_Pedido;
class Pedido
{

public:
    Pedido();
private:
    int numero_, importe_;
    const Tarjeta *tar_de_pago_;
    Fecha f_pedido_;
    static int n_pedidos_;
};



#endif