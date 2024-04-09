#ifndef USUARIO_HPP_
#define USUARIO_HPP_
//#include "tarjeta.hpp"
#include "cadena.hpp"
//#include "articulo.hpp"
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <map>

class Numero;
class Tarjeta;
class Articulo;
class Clave
{
public:
    enum Razon{CORTA, ERROR_CRYPT};
    class Incorrecta
    {
    public:
        
        Incorrecta(Razon r): reason{r} {}
        Razon razon() const {return reason;}
    private:
        Razon reason;
    };
    Clave(const char* passwd);
    const Cadena& clave() const {return clave_;};
    bool verifica(const char* passwd) const;
private:
    Cadena clave_;
    char encriptacion_[3];
    static Cadena caracteres;
};


class Usuario
{
public:
    typedef std::map<Numero, Tarjeta*> Tarjetas;
    typedef std::unordered_map<Articulo*, unsigned int> Articulos;

    class Id_duplicado
    {
    public:
        Id_duplicado(const Cadena& id): id_incorrecto{id} {}
        const Cadena& idd() const {return id_incorrecto;}
    private:
        Cadena id_incorrecto;
    };

    Usuario(const Cadena& id, const Cadena& nom, const Cadena& apell,  const Cadena& direccion, const char* passwd);

    const Cadena& id() const {return id_;}
    const Cadena& nombre() const {return nombre_;}
    const Cadena& apellidos() const {return apellidos_;}
    const Cadena& direccion() const {return direccion_;}
    const Tarjetas& tarjetas() const {return Tarjetas_;}
    const Articulos& compra() const {return Articulos_;}

    void es_titular_de(Tarjeta* tar);
    void no_es_titular_de(Tarjeta* tar);
    void compra(Articulo& art, unsigned ctd);
    void vaciar_carro() {Articulos_.clear();}
    unsigned n_articulos() const {return Articulos_.size();}

    friend std::ostream& operator <<(std::ostream& os, const Usuario& us);

    Usuario(const Usuario&) = delete;
    Usuario& operator=(const Usuario&) = delete;

    ~Usuario();

private:
    typedef std::unordered_set<Cadena>::iterator tipolt;
    Cadena id_, nombre_, apellidos_, direccion_;
    Clave passwd_;
    Tarjetas Tarjetas_;
    Articulos Articulos_;
    static std::unordered_set<Cadena> ids;
};

void mostrar_carro(std::ostream& os, const Usuario& us); //QUEDA POR IMPLEMENTAR


#endif