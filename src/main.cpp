#include <iostream>

#include "fecha.hpp"
#include "cadena.hpp"
#include "articulo.hpp"
#include "usuario.hpp"
#include "tarjeta.hpp"

void pruebaFechaCadena();
void pruebaArticulo();

int main()
{
    //pruebaFechaCadena();
    pruebaArticulo();
    std::cout << std::endl << "System Pause" << std::endl;
    return 0;
}

void pruebaArticulo()
{
    std::cout << "Va a comenzar" << std::endl;
    try
    {
        Articulo a1("JJ", "Alfajor", "15/8/2023", 99.109, 100);
        std::cout << a1 << std::endl;
    }
    catch(...)
    {
        std::cerr << "Ha habido una excepcion" << '\n';
    }
    try
    {
        Clave c("Juanito");
        std::cout << c.clave() << std::endl;

    }
    catch(Clave::Incorrecta& c)
    {
        std::cerr << c.razon() << std::endl;
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
    std::cout << "cad1 cortada queda: " << cad1.substr(0, 4) << std::endl;

    std::cout << cad1.length() << ' ' << cad3.length() << std::endl;
    std::cout << cad1 + cad3 << std::endl;
    cad1 += cad3;
    std::cout << cad1 << std::endl;
    cad2 = cad1;
    std::cout << cad2 << std::endl;

    //std::cout << "cad2 cortada queda: " << cad2.substr(0, 5) << std::endl;

    if(cad1 >= cad3)
    {
        std::cout << "cad1 es mayor o igual que cad3" << std::endl;
    }
    else
    {
        std::cout << "cad1 es menor que cad3" << std::endl;
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
        std::cout << e.por_que() << std::endl;
    }
}
