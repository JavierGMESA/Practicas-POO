#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include "fecha.hpp"
#include "cadena.hpp"
//class Cadena;
//class Fecha;
#include <set>

class Autor
{
public:
    Autor(const Cadena& nom, const Cadena& apell, const Cadena& dir): nombre_{nom}, apellidos_{apell}, direccion_{dir}{}

    const Cadena& nombre() const{return nombre_;}
    const Cadena& apellidos() const{return apellidos_;}
    const Cadena& direccion() const{return direccion_;}
private:
    Cadena nombre_, apellidos_, direccion_;
};

class Articulo
{
public:
    typedef std::set<Autor*> Autores;

    class Autores_vacios{};

    //Articulo(const Cadena& Ref, const Cadena& tit, const Fecha& pub, float precio, unsigned stk = 0);
    
    Articulo(Autores& a, const Cadena& Ref, const Cadena& tit, const Fecha& pub, float precio);
    const Cadena& referencia() const {return referencia_;}
    const Cadena& titulo() const {return titulo_;}
    const Fecha& f_publi() const {return f_publi_;}
    float precio() const {return precio_;}
    float& precio() {return precio_;}

    //unsigned stock() const {return stock_;}
    //unsigned& stock() {return stock_;}

    virtual void impresion_especifica(std::ostream& os) const = 0;

    virtual ~Articulo(){}

protected:
    const Autores autores_; 

private:
    const Cadena referencia_, titulo_;
    const Fecha f_publi_;
    float precio_;
    //unsigned stock_;
};

class ArticuloAlmacenable: public Articulo
{
public:
    ArticuloAlmacenable(Articulo::Autores& a, const Cadena& Ref, const Cadena& tit, const Fecha& pub, float precio, unsigned stk = 0): Articulo(a, Ref, tit, pub, precio), stock_{stk}{}
    unsigned stock() const {return stock_;}
    unsigned& stock() {return stock_;}
    //IMPORTANTE: SI NO IMPLEMENTA EL MÉTODO impresion_especifica() HEREDADO, SE VUELVE ABSTRACTA
    virtual ~ArticuloAlmacenable(){}
private:
    unsigned stock_;
};

class Libro: public ArticuloAlmacenable
{
public:
    Libro(Articulo::Autores& a, const Cadena& Ref, const Cadena& tit, const Fecha& pub, float precio, unsigned n_pag, unsigned stk = 0): ArticuloAlmacenable(a, Ref, tit, pub, precio, stk), n_pag_{n_pag}{}
    unsigned n_pag() const {return n_pag_;}
    void impresion_especifica(std::ostream& os) const override;
private:
   const unsigned n_pag_;
};

class Revista: public ArticuloAlmacenable
{
public:
    Revista(Articulo::Autores& a, const Cadena& Ref, const Cadena& tit, const Fecha& pub, float precio, unsigned num, unsigned perio, unsigned stk = 0): ArticuloAlmacenable(a, Ref, tit, pub, precio, stk), num_{num}, perio_{perio}{}
    unsigned numero() const {return num_;}
    unsigned periodicidad() const {return perio_;}
    void impresion_especifica(std::ostream& os) const override;
private:
    const unsigned num_, perio_;
};

class LibroDigital: public Articulo
{
public:
    LibroDigital(Autores& a, const Cadena& Ref, const Cadena& tit, const Fecha& pub, float precio, const Fecha& f_expiracion): Articulo(a, Ref, tit, pub, precio), f_expir_{f_expiracion}{}
    const Fecha& f_expir() const {return f_expir_;}
    void impresion_especifica(std::ostream& os) const override;
private:
    const Fecha f_expir_;
};



std::ostream& operator<<(std::ostream& os, Articulo* art);

#endif