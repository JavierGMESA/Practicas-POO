#include "usuario.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include "fecha.hpp"
#include "cadena.hpp"
#include <unistd.h>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <random>
#include <crypt.h>
#include <iostream>

#include <iostream>

Cadena Clave::caracteres{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./"};

Clave::Clave(const char* passwd): clave_{passwd}
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<char> distrib(0, Clave::caracteres.length() - 1);
    char * c;
    if(clave_.length() < 5)
    {
        throw Clave::Incorrecta(Clave::CORTA);
    }
    else
    {
        //crypt devuelve un puntero a cadena
        //crypt recibe la cadena a encriptar y como segunda una cadena de dos caracteres que deben estar entre [a-zA-Z0-9./]
        encriptacion_[2] = '\0';
        encriptacion_[0] = Clave::caracteres[distrib(gen)];
        encriptacion_[1] = Clave::caracteres[distrib(gen)];
        c = crypt(passwd, encriptacion_);
        if(c == nullptr) //cuando crypt falla devuelve un puntero nulo
        {
            throw Clave::Incorrecta(Clave::ERROR_CRYPT);
        }
        clave_ = Cadena(c);
    }
}

bool Clave::verifica(const char* passwd) const
{
    return strcmp(crypt(passwd, encriptacion_), (const char*)(clave_)) == 0;
}

std::unordered_set<Cadena> Usuario::ids{};

Usuario::Usuario(const Cadena& id, const Cadena& nom, const Cadena& apell,  const Cadena& direccion, const Clave& passwd): id_{id}, nombre_{nom}, apellidos_{apell}, direccion_{direccion}, passwd_{passwd}
{
    std::pair <tipolt, bool> res = Usuario::ids.insert(id); //comprobar si el id está en el conjunto
    if(!(res.second))
    {
        throw Usuario::Id_duplicado(id_);
    }
}

void Usuario::es_titular_de(Tarjeta& tar)
{
    if(!Tarjetas_.count(tar.numero_))
    {
        Tarjetas_[tar.numero_] = &tar;
    }
    tar.titular_ = this;
}

void Usuario::no_es_titular_de(Tarjeta& tar)
{
    if(Tarjetas_.count(tar.numero_))
    {
        Tarjetas_.erase(tar.numero_);
    }
}

void Usuario::compra(Articulo& art, unsigned ctd)
{
    Articulos_.erase(&art);
    if(ctd != 0)
    {
        Articulos_[&art] = ctd;
    }
}

std::ostream& operator <<(std::ostream& os, const Usuario& us)
{
    os << us.id_ << " [" << us.passwd_.clave() << "] " << us.nombre_ << ' ' << us.apellidos_ << std::endl;
    os << us.direccion_ << std::endl << "Tarjetas:" << std::endl;;
    Usuario::Tarjetas::const_iterator is; 
    for(is = us.Tarjetas_.begin(); is != us.Tarjetas_.end(); ++ is)
    {
        os << std::endl << std::endl << *(is->second);
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
    Usuario::Articulos::const_iterator is;
    for(is = us.compra().begin(); is != us.compra().end(); ++is) // Por que?
    {
        os << std::endl << "   " << is->second << "   " << *(is->first);
    }
}

Usuario::~Usuario()
{
    Tarjetas::iterator it;
    for(it = Tarjetas_.begin(); it != Tarjetas_.end(); ++it)
    {
        it->second->anula_titular();
    }
}

