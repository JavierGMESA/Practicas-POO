#include "usuario.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include "fecha.hpp"
#include "cadena.hpp"
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <random>
#include <crypt.h>
#include <random>
#include <ctime>
#include <iostream>
#include <unistd.h>

//Cadena Clave::caracteres{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./"};
//const char Clave::caracteres[65]{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./"};

Clave::Clave(const char* passwd): clave_{passwd}
{
    static Cadena caracteres{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./"}; //IMPORTANTE
    //std::srand(std::time(nullptr));

    std::random_device rd; //IMPORTANTE
    std::mt19937 gen(rd());
    std::uniform_int_distribution<char> distrib(0, 63);
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
        encriptacion_[0] = caracteres[distrib(gen)];
        encriptacion_[1] = caracteres[distrib(gen)];

        //encriptacion_[0] = Clave::caracteres[rand() % Clave::caracteres.length()];
        //encriptacion_[1] = Clave::caracteres[rand() % Clave::caracteres.length()];

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
    //IMPORTANTE: El titular de la tarjeta es el usuario
    //if(!Tarjetas_.count(tar.numero_) && tar.activa_ && tar.titular_ == nullptr)
    if(tar.titular() == this)
    {
        Tarjetas_.insert(std::make_pair(tar.numero_, &tar)); //IMPORTANTE (no hace falta especificar los tipos)
    }
    //tar.titular_ = this;
}

void Usuario::no_es_titular_de(Tarjeta& tar)
{
    Tarjetas_.erase(tar.numero_);
    tar.anula_titular();
}

void Usuario::compra(Articulo& art, unsigned ctd)
{
    Articulos_[&art] = ctd;
    if(ctd == 0)
    {
        Articulos_.erase(&art);
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
    os << std::endl;
    os << "Carrito de compra de " << us.id() << " [Artículos: " << us.n_articulos() << ']' << std::endl;
    os << " Cant.  Artículo" << std::endl;
    //int i;
    os.fill('=');
    os.width(60);
    os << "" << std::endl;
    //Usuario::Articulos::const_iterator is;
    for(/*is = us.compra().begin(); is != us.compra().end(); ++is*/ auto is: us.compra())
    {
        os << std::endl << "  " << is.second << "   " << *(is.first);
        //(is.first)->impresion_especifica(os);
    }
    os << std::endl;
}

Usuario::~Usuario()
{
    Tarjetas::iterator it;
    for(it = Tarjetas_.begin(); it != Tarjetas_.end(); ++it)
    {
        it->second->anula_titular();
        //it.second->anula_titular();
    }
    Usuario::ids.erase(id_);
}

