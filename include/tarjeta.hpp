#ifndef TARJETA_HPP_
#define TARJETA_HPP_
#include "cadena.hpp"
#include "fecha.hpp"
//#include "usuario.hpp"
#include <set>
#include <iostream>
#include <string.h>
//#include <algorithm>
//#include <functional>

class Usuario;
class Numero
{
public:
    enum Razon{LONGITUD, DIGITOS, NO_VALIDO};
    class Incorrecto
    {
    public:
        
        Incorrecto(Razon r): razon_{r}{} 
        Razon razon() const {return razon_;}   
    private:
        Razon razon_;
    };

    class EsBlanco
    {
    public:
        using argument_type = char;
        bool operator()(char p)const {return std::isspace(p);}
    };

    class EsDigito
    {
    public:
        using argument_type = char;
        bool operator()(char p)const {return std::isdigit(p);}
    };

    Numero(const Cadena& num);
    operator const char*() const;
    friend bool operator<(const Numero& num1, const Numero& num2); //Hay que hacerlo amigo para
                                                                   //para poder acceder a las cadenas y así comparar 
private:
    Cadena numero_;
};

class Tarjeta
{
public:
    enum Tipo{Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};

    friend class Usuario;

    class Caducada
    {
    public:
        Caducada(const Fecha& fech): fech_{fech}{}
        const Fecha& cuando() const {return fech_;}
    private:
        Fecha fech_;
    };

    class Num_duplicado
    {
    public:
        Num_duplicado(const Numero& num): num_{num}{}
        const Numero& que() const {return num_;}
    private:
        Numero num_;
    };

    class Desactivada{};


    Tarjeta(const Numero& num, Usuario& us, const Fecha& fech);

    const Numero& numero() const {return numero_;}
    const Usuario* titular() const {return titular_;}
    const Fecha& caducidad() const {return caduca_;}
    bool activa() const {return activa_;}
    Tipo tipo() const;

    bool activa(bool estado) 
    {
        activa_ = estado;
        return activa_;
    }

    Tarjeta(const Tarjeta&) = delete;
    Tarjeta& operator=(const Tarjeta&) = delete;

    ~Tarjeta();
private:
    const Numero numero_;
    const Usuario* titular_;
    const Fecha caduca_;
    bool activa_;

    static std::set<Numero> tarjetas;
    typedef std::set<Numero>::iterator IT;

    void anula_titular();
};

std::ostream& operator<<(std::ostream& os, Tarjeta::Tipo t);

std::ostream& operator<<(std::ostream& os, const Tarjeta& tar);

bool operator<(const Tarjeta& tar1, const Tarjeta& tar2);

bool luhn(const Cadena& numero);

#endif