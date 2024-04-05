#include "usuario.hpp"
#include "tarjeta.hpp"
#include <unistd.h>
#include <unordered_map>
#include <unordered_set>

#include <iostream>

Clave::Clave(const char* passwd): clave_{passwd}
{
    if(clave_.length() < 5)
    {
        throw Clave::Incorrecta(Clave::CORTA);
    }
    else
    {

    }
    //std::cout << std::crypt(passwd, passwd);
}

const Cadena& Clave::clave() const
{

    return ;
}

bool Clave::verifica(const char* passwd) const
{

}


Usuario::Usuario(const Cadena& id, const Cadena& nom, const Cadena& apell,  const Cadena& direccion, const char* passwd): id_{id}, nombre_{nom}, apellidos_{apell}, direccion_{direccion}, passwd_{passwd}
{
    std::pair <tipolt, bool> res = ids.insert(id); //comprobar si el id está en el conjunto
    if(!(res.second))
    {
        throw Usuario::Id_duplicado(id_);
    }
}

void Usuario::es_titular_de(Tarjeta* tar)
{
    if(!Tarjetas_.count(tar->numero_))
    {
        Tarjetas_[tar->numero_] = tar;
    }
}

void Usuario::no_es_titular_de(Tarjeta* tar)
{
    if(Tarjetas_.count(tar->numero_))
    {
        Tarjetas_.erase(tar->numero_);
    }
}

void Usuario::compra(const Articulo& art, unsigned ctd)
{
    Articulos_.erase(&art);
    if(ctd != 0)
    {
        Articulos_[&art] = ctd;
    }
}

std::ostream& operator <<(std::ostream& os, const Usuario& us)
{
    os << us.id_ << "[ " << us.passwd_.clave() << "] " << us.nombre_ << ' ' << us.apellidos_ << std::endl;
    os << us.direccion_ << std::endl << "Tarjetas:" << std::endl;;
    Usuario::Tarjetas::iterator is; 
    for(is = us.Tarjetas_.begin(); is != us.Tarjetas_.end(); ++ is) // Por que?
    {
        os << is->second << std::endl << std::endl << std::endl;
    }
    return os;
}

void mostrar_carro(std::ostream& os, const Usuario& us)
{
    os << "Carrito de compra de " << us.id() << " [Articulos: " << us.n_articulos() << ']' << std::endl;
    os << " Cant. Articulo" << std::endl;
    int i;
    for(i = 0; i < 25; ++i)
    {
        os << '=';
    }
    Usuario::Articulos::iterator is;
    for(is = us.compra().begin(); is != us.compra().end(); ++ is) // Por que?
    {
        os << "   " << is->first << "   " << is->second << std::endl;
    }
}

Usuario::~Usuario()
{
    Tarjetas::iterator it;
    for(it = Tarjetas_.begin(); it != Tarjetas_.end(); ++i)
    {
        it->second->anula_titular();
    }
}

