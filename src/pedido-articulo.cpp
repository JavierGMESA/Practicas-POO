#include "pedido-articulo.hpp"

std::ostream& operator<<(std::ostream& os, const LineaPedido& l)
{
    os << l.precio_venta() << " €   " << l.cantidad();
}