#include <iostream>

#include "fecha.hpp"
#include "cadena.hpp"

#include "articulo.hpp"
#include "usuario.hpp"
#include "tarjeta.hpp"

#include "pedido.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"

#include <unistd.h>
#include <cstring>
#include <locale>
#include <algorithm>
#include <functional>
#include <ctype.h>

void pruebaFechaCadena();
void pruebaArticulo();
void pruebaClave();
void pruebaNumero();
void pruebaUsuarioTarjeta();
void pruebaP3();
void pruebaP4();

//typedef basic_ostringstream<char> ostringstream;

int main()
{

    //pruebaFechaCadena();
    //pruebaArticulo();
    //pruebaClave();
    //pruebaNumero();
    //pruebaUsuarioTarjeta();
    //pruebaP3();
    pruebaP4();

    //Cadena cad{"Hola a todos"};
    //std::remove_if(cad.begin(), cad.end(), Numero::EsBlanco());
    //std::cout << cad << std::endl;

    std::cout << std::endl << "System Pause" << std::endl;
    return 0;
}

void pruebaArticulo()
{
    std::cout << "Va a comenzar" << std::endl;
    try
    {
        //Articulo a1("JJ", "Alfajor", "15/8/2023", 99.109, 100);
        //std::cout << a1 << std::endl;
    }
    catch(...)
    {
        std::cerr << "Ha habido una excepcion" << '\n';
    }
}

void pruebaClave()
{
    try
    {
        std::cout << "Va a crear el objeto" << std::endl;
        Clave c("Juanito");
        std::cout << c.clave() << std::endl;
        if(c.verifica("Juanit"))
        {
            std::cout << "Es igual" << std::endl;
        }
        else
        {
            std::cout << "No es igual" << std::endl;
        }
    }
    catch(Clave::Incorrecta& c)
    {
        std::cerr << c.razon() << std::endl;
    }
}

void pruebaNumero()
{
    try
    {
        Numero n1{"298907654329017"};
        std::cout << n1 << std::endl;
        Numero n2{"298907654321097"};
        if(n1 < n2)
        {
            std::cout << "Menor" << std::endl;
        }
        else
        {
            std::cout << "Mayor o igual" << std::endl;
        }
        Numero n3{"4539 4512 0398 7356"};
        std::cout << n3 << std::endl;
    }
    catch(Numero::Incorrecto& n)
    {
        std::cerr << "Ha habido una excepción:" << n.razon() << std::endl;
    }
}

void pruebaUsuarioTarjeta()
{
    Usuario us1{"TheFox102", "Javier", "Mesa", "Calle Montevideo", "Juanito"};
    try
    {
        
        std::cout << us1.id() << ' ' << us1.nombre() << ' ' << us1.apellidos() << ' ' << us1.direccion() << std::endl;
        //Articulo a1("JJ", "Alfajor", "15/8/2023", 99.19, 100);
        //Articulo a2("Jg", "Camas de seda", "17/8/2023", 99.19, 90);
        //us1.compra(a1, 7);
        //us1.compra(a2, 10);
        //us1.vaciar_carro();
        Usuario::Articulos::const_iterator i;
        for(i = us1.compra().begin(); i != us1.compra().end(); ++i)
        {
            //std::cout << *(i->first) << std::endl;
        }
        std::cout << us1.n_articulos() << std::endl;
        std::cout << us1 << std::endl; 

        Tarjeta tar1{Numero{"298907654329017"}, us1, Fecha{"0/0/0"}};
        std::cout << "El usuario es:" << std::endl << us1 << std::endl;
        std::cout << tar1.numero() << ' ' << tar1.titular() << ' ' << tar1.caducidad() << ' ' << tar1.tipo() << ' ';
        if(tar1.activa())
        {
            std::cout << "Activa" << std::endl;
        }
        else
        {
            std::cout << "Desactivada" << std::endl;
        }
        std::cout << std::endl;
        //Usuario us2{"TheFox102", "Javi", "Garcia", "Calle Montevideo", "JuanitoBaker"}; //Genera una excepción (mismo id que otro que ya estaba)
        tar1.~Tarjeta();
        std::cout << us1;
    }
    catch(Usuario::Id_duplicado& i)
    {
        std::cerr << "El id ya estaba: " << i.idd() << std::endl;
    }
    try
    {
        Usuario us2{"TheFox1020", "Javier", "Mesa", "Calle Montevideo", "Juanito"};
        //Tarjeta tar2{Numero{"298907654329017"}, us2, Fecha{"0/0/0"}};
    }
    catch(Tarjeta::Num_duplicado& e)
    {
        std::cerr << "Tarjeta duplicada: " << e.que() << '\n';
    }
    
}


void pruebaFechaCadena()
{
    //Fecha f(0, 0, 0);
    Fecha f{"0000/9/00000"};
    Fecha g{"29/5/2020"};
    Fecha h{};
    std::cout << "f queda: " << f << " g queda: " << g << std::endl;
    g = g - 29;

    std::cout << g << std::endl;
    std::cout << h << std::endl;

    if(f > g)
    {
        std::cout << "Mayor" << std::endl;
    }

    std::cout << std::endl << "Comenzamos a probar cadena" << std::endl;

    Cadena cad1{"Hola a todos"};
    Cadena cad2{0, ' '};
    Cadena cad3{" Buenas Juan"};
    //Cadena cad4{2, 'l'};
    std::cout << "cad1 queda: " << cad1 << " (Longitud = " << cad1.length() << ')' << std::endl;
    std::cout << cad1[0] << ' ' << cad1[1] << std::endl;
    std::cout << cad1.at(0) << ' ' << cad1.at(11) << std::endl;
    std::cout << "cad1 cortada queda: " << cad1.substr(0, cad1.length()) << std::endl;

    std::cout << cad1.length() << ' ' << cad3.length() << std::endl;
    std::cout << cad1 + cad3 << std::endl;
    //cad1 += cad3;
    std::cout << cad1 << std::endl;
    cad2 = cad1;
    std::cout << cad2 << std::endl;

    std::cout << "cad2 cortada queda: " << cad2.substr(0, 5) << std::endl;

    std::cout << cad1 << ' ' << cad3 << std::endl;

    if(cad3 >= cad1)
    {
        std::cout << "mayor o igual" << std::endl;
    }
    else
    {
        std::cout << "menor que" << std::endl;
    }
    if(cad3 == " Buenas Juan")
    {
        std::cout << "iguales" << std::endl;
    }
    try
    {
        //std::cin >> cad1;
        //std::cout << cad1;
    }
    catch(Cadena::Invalida&)
    {
        std::cerr << "Mal" << std::endl;
    }
    Cadena::iterator i;
    for(i = cad3.begin(); i != cad3.end(); ++i)
    {
        std::cout << *i;
    }
    std::cout << std::endl;
    Cadena::reverse_iterator j;
    for(j = cad3.rbegin(); j != cad3.rend(); ++j)
    {
        std::cout << *j;
    }
    std::cout << "fin" << std::endl;

    //std::cin >> cad3;
    //std::cout << cad3 << std::endl;
    //try
    //{
    //    std::cin >> f;
    //}
    //catch(Fecha::Invalida& e)
    //{
    //    std::cout << e.por_que() << std::endl;
    //}
    //std::cin >> f;
    //std::cout << f << std::endl;
    try
    {
        f + 2000000;
    }
    catch(Fecha::Invalida& e)
    {
        std::cerr << e.por_que() << std::endl;
    }
    try
    {
        Fecha f8{"1/2/2001"};
        std::cout << std::endl << f8 << std::endl;
    }
    catch(Fecha::Invalida &e)
    {
        std::cerr << e.por_que() << '\n';
    }
    try
    {
        const Cadena cad{"Hola a todos"};
        std::cout << cad.at(10);
    }
    catch(std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        const Fecha f("11/09/2001");
    }
    catch(Fecha::Invalida& e)
    {
        std::cerr << e.por_que() << '\n';
    }
    
    std::cout << "Va a mostrar" << std::endl;

    Cadena a("Ingles,");
    std::cout << a << std::endl;
    const Cadena b(" pirata es");
    a += b;
    std::cout << a << ' ' << a.operator const char *() << std::endl;
    
}

void pruebaP3()
{
    Usuario us{"1234", "Javier", "Mesa", "Montevideo", "mamaita"};
    std::cout << "Crea el usuario Javier" << std::endl;
    Pedido_Articulo PA{};
    Usuario_Pedido UP{};
    std::cout << "Crea las clases de asociacion" << std::endl;
    //Articulo art{"alfajor", "alfajores argentinos", "10/8/1990", 11.90, 20};
    std::cout << "Crea el Alfajor" << std::endl;
    Tarjeta tar{Numero{"2989 0765 4329 017"}, us, "10/10/2025"};
    std::cout << "Crea la tarjeta" << std::endl;
    std::cout << tar.numero() << std::endl;
    //us.compra(art, 10);
    Pedido p{UP, PA, us, tar, "0/0/0"};
    std::cout << "Crea el pedido" << std::endl;
    std::cout << p.fecha() << std::endl;
    std::cout << p.numero() << std::endl;
    std::cout << *(p.tarjeta()) << std::endl;
    std::cout << p.total() << std::endl;
    std::cout << Pedido::n_total_pedidos() << std::endl;
    std::cout << std::endl << p << std::endl;

    PA.mostrarDetallePedidos(std::cout);
    std::cout << std::endl << std::endl;
    PA.mostrarVentasArticulos(std::cout);
    std::cout << *(UP.cliente(p)) << std::endl;
    Usuario_Pedido::Pedidos::const_iterator i;
    for(i = UP.pedidos(us).begin(); i != UP.pedidos(us).end(); ++i)
    {
        std::cout << *(*i) << std::endl;
    }
}

void pruebaP4()
{
    Autor a1("Javier", "García Mesa", "Montevideo");
    Autor a2("Larry", "Capinga", "Valdezorras");
    Articulo::Autores a;
    a.insert(&a1);
    a.insert(&a2);
    Articulo *ap = new Libro(a, "alfajor", "alfajores argentinos", "10/8/1990", 11.90, 11, 10);
    std::cout << *ap << std::endl;
    delete ap;
    ap = new Revista(a, "alfajor", "alfajores argentinos", "10/8/1990", 11.90, 11, 30, 8);
    std::cout << *ap << std::endl;
    delete ap;
    ap = new LibroDigital(a, "alfajor", "alfajores argentinos", "10/8/1990", 11.90, "20/12/2030");
    std::cout << *ap << std::endl;
    delete ap;

    Usuario us{"1234", "Javier", "Mesa", "Montevideo", "mamaita"};
    us.compra(*ap, 10);
    mostrar_carro(std::cout, us);
    std::cout << std::endl << "Termina de mostrar el carro" << std::endl;
    Pedido_Articulo PA{};
    Usuario_Pedido UP{};
    Tarjeta tar{Numero{"2989 0765 4329 017"}, us, "10/10/2025"};
    Pedido p(UP, PA, us, tar, Fecha());
    std::cout << p << std::endl;
}
