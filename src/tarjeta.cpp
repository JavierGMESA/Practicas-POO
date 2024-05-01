#include "cadena.hpp"
#include "usuario.hpp"
#include "fecha.hpp"
#include "tarjeta.hpp"
#include <ctype.h>
#include <set>
#include <iostream>
#include <algorithm>
#include <functional>

Numero::Numero(const Cadena& num): numero_{num}
{
    bool numerico = true;
    char* correct_n = new char[numero_.length()];
    int i = 0, j = 0;

    Cadena::const_iterator it = std::remove_if(numero_.begin(), numero_.end() + 1, EsBlanco()); //Hay que pasarle un objeto de la clase funcion. Le sumo 1 al end para que mueva el '\0'
    numero_ = numero_.substr(0, it - numero_.begin()); //Le asigno una nueva cadena pues tras el remove_if el tamaño de la cadena ha quedado inexacto

    std::unary_negate<EsDigito> NoDigito((EsDigito()));

    it = std::find_if(numero_.begin(), numero_.end(), NoDigito);
    if(it != numero_.end())
    {
        numero_ = Cadena("");
        throw Numero::Incorrecto(DIGITOS);
    }


    //while(i < numero_.length() && numerico)
    //{
    //
    //    if(!std::isdigit(numero_[i]) && !std::isspace(numero_[i]))
    //    {
    //        numerico = false;
    //    }
    //    else
    //    {
    //        if(!std::isspace(numero_[i]))
    //        {
    //            correct_n[j] = numero_[i];
    //            ++j;
    //        }
    //        ++i;
    //    }   
    //}
    //correct_n[j] = '\0';
    //numero_ = Cadena(correct_n);

    //numero_ = Cadena(numero_.operator const char *());

    //if(!numerico)
    //{
    //    numero_ = Cadena("");
    //    throw Numero::Incorrecto(DIGITOS);
    //}
    if(numero_.length() < 13 || numero_.length() > 19)
    {
        numero_ = Cadena("");
        throw Numero::Incorrecto(LONGITUD);
    }
    if(!luhn(numero_))
    {
        numero_ = Cadena("");
        throw Numero::Incorrecto(NO_VALIDO);
    }
}

Numero::operator const char*() const
{
    return (const char*)(numero_);
}

bool operator<(const Numero& num1, const Numero& num2)
{
    return num1.numero_ < num2.numero_;
}

std::set<Numero> Tarjeta::tarjetas{};

Tarjeta::Tarjeta(const Numero& num, Usuario& us, const Fecha& fech): numero_{num}, titular_{&us}, caduca_{fech}, activa_{true}
{
    if(caduca_ < Fecha("0/0/0"))
    {
        throw Tarjeta::Caducada(caduca_);
    }
    us.es_titular_de(*this);
    std::pair<IT, bool> res = Tarjeta::tarjetas.insert(numero_);
    if (!res.second)
        throw Num_duplicado(numero_);
}

Tarjeta::Tipo Tarjeta::tipo() const
{
    const char *num = numero_;
    if(num[0] == '4')
    {
        return VISA;
    }
    else
    {
        if(num[0] == '5')
        {
            return Mastercard;
        }
        else
        {
            if(num[0] == '6')
            {
                return Maestro;
            }
            else
            {
                if(num[0] == '3')
                {
                    if(num[1] == '4' || num[1] == '7')
                    {
                        return AmericanExpress;
                    }
                    else
                    {
                        return JCB;
                    }
                }
                else
                {
                    return Otro;
                }
            }
        }
    }
}

void Tarjeta::anula_titular()
{
    activa_ = false;
    titular_ = nullptr;
}

Tarjeta::~Tarjeta()
{
    if(titular_ != nullptr)
    {
        const_cast<Usuario *>(titular_)->no_es_titular_de(*this);
        titular_ = nullptr;
    }
    Tarjeta::tarjetas.erase(numero_);
}

std::ostream& operator <<(std::ostream& os, Tarjeta::Tipo t)
{
    if(t == Tarjeta::AmericanExpress)
    {
        os << "American Express";
    }
    else
    {
        if(t == Tarjeta::JCB)
        {
            os << "JCB";
        }
        else
        {
            if(t == Tarjeta::VISA)
            {
                os << "VISA";
            }
            else
            {
                if(t == Tarjeta::Mastercard)
                {
                    os << "Mastercard";
                }
                else
                {
                    if(t == Tarjeta::Maestro)
                    {
                        os << "Maestro";
                    }
                    else
                    {
                        //os << "Tipo indeterminado";
                        os << "Otro";
                    }
                }
            }
        }
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Tarjeta& tar)
{
    Cadena::const_iterator i;
    Cadena nombre = tar.titular()->nombre();
    Cadena caducidad;
    os << tar.tipo() << std::endl;
    os << tar.numero() << std::endl;

    for(i = nombre.begin(); i != nombre.end(); ++i)
    {
        os << char(std::toupper(*i));
    }
    os << ' ';
    nombre = tar.titular()->apellidos();
    for(i = nombre.begin(); i != nombre.end(); ++i)
    {
        os << char(std::toupper(*i));
    }
    os << std::endl << "Caduca: ";
    if(tar.caducidad().mes() < 10)
    {
        os << "0" << std::to_string(tar.caducidad().mes());
    }
    else
    {
        os << std::to_string(tar.caducidad().mes());
    }
    os << '/' << tar.caducidad().anno() % 100;
    return os;
}

bool operator<(const Tarjeta& tar1, const Tarjeta& tar2)
{
    return tar1.numero() < tar2.numero();
}