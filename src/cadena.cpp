#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>

#include "cadena.hpp"

char Cadena::vacia[1]{'\0'};

Cadena::Cadena(const size_t& tam, const char& c): tam_(tam)
{
    int i;
    if(tam == 0)
    {
        s_ = Cadena::vacia;
    }
    else
    {
        try
        {
            s_ = new char[tam_ + 1];
            for(i = 0; i < tam_; ++i)
            {
                s_[i] = c;
            }
            s_[tam_] = '\0';
        }
        catch(std::bad_alloc& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}

Cadena::Cadena(const char *cad)
{
    int i;
    try
    {
        for(tam_ = 0; cad[tam_]!= '\0'; ++tam_);
        s_ = new char[tam_ + 1];
        for(i = 0; i < tam_ + 1; ++i)
        {
            s_[i] = cad[i];
        }
    }
    catch(std::bad_alloc& e)
    {
        std::cout << e.what() << std::endl;
    }
}

Cadena::operator const char*() const
{
    int i;
    char *cad;
    try
    {
        cad = new char[tam_ + 1];
        for(i = 0; i < tam_ + 1; ++i)
        {
            cad[i] = s_[i];
        }
    }
    catch(std::bad_alloc& e)
    {
        std::cout << e.what() << std::endl;
    }
    return cad;
}

const char& Cadena::operator[](const size_t& index) const
{
    return s_[index];
}

char& Cadena::operator[](const size_t& index)
{
    return s_[index];
}

const char& Cadena::at(const size_t& index) const
{
    if(index > tam_ - 1 || index < 0)
    {
        throw std::out_of_range ("Indice no valido");
    }
    return s_[index];
}

char& Cadena::at(const size_t& index)
{
    if(index > tam_ - 1 || index < 0)
    {
        throw std::out_of_range ("Indice no valido");
    }
    return s_[index];
}

Cadena Cadena::substr(const size_t& index, const size_t& tama) const
{
    Cadena cad{tama, 'm'};
    int i;
    if(s_ == Cadena::vacia || index > tam_ - 1 || index < 0)
    {
        throw std::out_of_range (std::to_string(index) + " esta fuera de rango");
    }
    else
    {
        if(index + tama > tam_)
        {
            throw std::out_of_range ("Despues de " + std::to_string(index) + " no hay " + std::to_string(tama) + " caracteres");
        }
    }
    cad.tam_ = tama;
    for(i = 0; i < tama; ++i)
    {
        cad.s_[i] = s_[i + index];
    }
    cad.s_[i] = '\0';
    return cad;
}

Cadena operator+(const Cadena& cade1, const Cadena& cade2)
{
    Cadena res{cade1};
    res += cade2;
    return res;
}

bool operator<(const Cadena& cade1, const Cadena& cade2)
{
    return std::strcmp((const char*)(cade1), (const char*)(cade2)) < 0;
}

bool operator==(const Cadena& cade1, const Cadena& cade2)
{
    return std::strcmp((const char*)(cade1), (const char *)(cade2)) == 0;
}

bool operator<=(const Cadena& cade1, const Cadena& cade2)
{
    return !(cade2 < cade1);
}

bool operator>(const Cadena& cade1, const Cadena& cade2)
{
    return cade2 < cade1;
}

bool operator>=(const Cadena& cade1, const Cadena& cade2)
{
    return !(cade1 < cade2);
}

bool operator!=(const Cadena& cade1, const Cadena& cade2)
{
    return !(cade1 == cade2);
}

Cadena& Cadena::operator=(const char* cad)
{
    *this = Cadena(cad);
    return *this;
}

Cadena& Cadena::operator+=(const Cadena& cade)
{
    int i = 0;
    int j = 0;
    char *cad;
    try
    {
        cad = new char[tam_ + cade.tam_ + 1]; //Si hay un bad_alloc pasa directamente al manejador
        if(s_ != Cadena::vacia)
        {
            while(s_[i] != '\0')
            {
                cad[i] = s_[i];
                ++i;
            }
        }
        if(cade.s_ != Cadena::vacia)
        {
            while(cade.s_[j] != '\0')
            {
                cad[i] = cade.s_[j];
                ++i;
                ++j;
            }
        }
        cad[i] = '\0';
        if(s_ != Cadena::vacia)
        {
            delete[] s_;
        }
        s_ = cad;
        tam_ = tam_ + cade.tam_ + 1;
    }
    catch(std::bad_alloc& e)
    {
        std::cout << e.what() << std::endl;
    }
    return *this;
}

Cadena::Cadena(const Cadena& cade)
{
    int i;
    try
    {
        s_ = new char[cade.tam_ + 1];
        tam_ = cade.tam_;
        for(i = 0; i < tam_ + 1; ++i)
        {
            s_[i] = cade.s_[i];
        }
    }
    catch(std::bad_alloc& e)
    {
        std::cout << e.what() << std::endl;
    }
}

Cadena& Cadena::operator=(const Cadena& cade)
{
    char *cad;
    int i;
    if(this != &cade)
    {
        try
        {
            cad = new char[cade.tam_ + 1]; //No hace falta guardar una copia pues
            if(s_ == Cadena::vacia)
            {
                s_ = cad;
            }
            else
            {
                delete[] s_;
            }
            for(i = 0; i < cade.tam_ + 1; ++i)
            {
                cad[i] = cade.s_[i];
            }
        }
        catch(std::bad_alloc& e)
        {
            std::cout << e.what() << std::endl;
        }
        s_ = cad;
        tam_ = cade.tam_;
    }
    return *this;
}

Cadena::~Cadena()
{
    if(s_ != Cadena::vacia)
    {
        delete[] s_;
        s_ = Cadena::vacia;
        tam_ = 0;
    }
}

Cadena::Cadena(Cadena&& cade)
{
    s_ = cade.s_;
    tam_ = cade.tam_;
    cade.s_ = Cadena::vacia;
    cade.tam_ = 0;
}

Cadena& Cadena::operator=(Cadena&& cade)
{
    if(this != &cade)
    {
        if(s_ != Cadena::vacia)
        {
            delete s_;
        }
        s_ = cade.s_;
        tam_ = cade.tam_;
        cade.s_ = Cadena::vacia;
        cade.tam_ = 0;
    }
    return *this;
}

std::istream& operator >>(std::istream& is, Cadena& cade)
{
    char cad1[100], cad2[32];
    int i = -1, j = 0;
    is >> cad1;
    do
    {
        ++i;
    }while(cad1[i] == ' ');

    while(cad1[i] != '\0' && cad1[i] != ' ' && j + 1 != 31)
    {
        cad2[j] = cad1[i];
        ++i,
        ++j;
    }
    cad2[i] = '\0';
    cade = Cadena(cad2);
    return is;
}

std::ostream& operator <<(std::ostream& os, const Cadena& cade)
{
    os << (const char*)(cade);
    return os;
}
