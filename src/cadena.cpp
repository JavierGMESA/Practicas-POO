#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>

#include "cadena.hpp"

char Cadena::vacia[1]{""};

Cadena::Cadena(const size_t& tam, const char& c): tam_(tam)
{
    std::size_t i;
    if(tam == 0)
    {
        s_ = Cadena::vacia;
    }
    else
    {
        s_ = new char[tam_ + 1];
        for(i = 0; i < tam_; ++i)
        {
            s_[i] = c;
        }
        s_[tam_] = '\0';
    }
}

Cadena::Cadena(const char *cad): tam_{std::strlen(cad)}
{
    if(tam_ == 0)
    {
        s_ = Cadena::vacia;
    }
    else
    {
        s_ = new char[tam_ + 1];
        std::strcpy(s_, cad);
    }
}

Cadena::operator const char*() const
{
    return s_;
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
    if(index < 0 || index >= tam_)
    {
        throw std::out_of_range("Indice no valido");
    }
    return s_[index];
}

char& Cadena::at(const size_t& index)
{
    if(index < 0 || index >= tam_)
    {
        throw std::out_of_range("Indice no valido");
    }
    return s_[index];
}

Cadena Cadena::substr(int index, int tama) const
{
    //Cadena cad{tama, ' '};
    //size_t i;
    //if(index < 0 || index >= tam_)
    //{
    //    throw std::out_of_range ("Índice esta fuera de rango");
    //}
    //if(tama < 0 || index + tama - 1 >= tam_)
    //{
    //    throw std::out_of_range ("Tamaño fuera de rango");
    //}
    //for(i = 0; i < tama; ++i, ++index)
    //{
    //    cad.s_[i] = s_[index];
    //}
    //cad.s_[i] = '\0'; No hace falta pues ya lo pone cad en el constructor
    if (index < 0 || index >= tam_)
        throw std::out_of_range("El índice no es válido");
    if (tama < 0 || tama + index - 1 >= tam_)
        throw std::out_of_range("El tamaño está fuera de rango");
    Cadena cad(tama, ' ');
    for (size_t i = 0; i < tama; ++index, ++i)
        cad.s_[i] = s_[index];
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

Cadena& Cadena::operator+=(const Cadena& cade)
{
    char *cad = s_;

    if(tam_ + cade.tam_ == 0)
    {
        s_ = Cadena::vacia;
    }
    else
    {
        s_ = new char[tam_ + cade.tam_ + 1];
        std::strcpy(s_, cad);
        std::strcat(s_, cade.s_);
    }
    if(cad != Cadena::vacia)
    {
        delete[] cad;
    }
    tam_ = tam_ + cade.tam_;

    return *this;
}

Cadena& Cadena::operator=(const char* cade)
{
    if(strcmp(s_, cade) != 0)
    {
        if(tam_ != 0)
        {
            delete[] s_;
        }
        if(std::strlen(cade) == 0)
        {
            s_ = Cadena::vacia;
        }
        else
        {
            s_ = new char[std::strlen(cade) + 1];
            std::strcpy(s_, cade);
        }
        tam_ = std::strlen(cade);
    }
    return *this;
}

Cadena::Cadena(const Cadena& cade): tam_{cade.tam_}
{
    if(tam_ == 0)
    {
        s_ = Cadena::vacia;
    }
    else
    {
        s_ = new char[tam_ + 1];
        std::strcpy(s_, cade.s_);
    }
}

Cadena& Cadena::operator=(const Cadena& cade)
{
    if(this != &cade)
    {
        
        if(s_ != Cadena::vacia)
        {
            delete[] s_;
        }
        if(cade.tam_ == 0)
        {
            s_ = Cadena::vacia;
        }
        else
        {
            s_ = new char[cade.tam_ + 1];
            strcpy(s_, cade.s_);
        }
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

Cadena::Cadena(Cadena&& cade): tam_{cade.tam_}, s_{cade.s_}
{
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
    char cad1[33], cad2[32], c;
    int i = 0, j = 0;
    //is >> cad1;
    //do
    //{
    //    ++i;
    //}while(cad1[i] == ' ');
    cad1[0] = '\0';
    while(is.get(c) && std::isspace(c));
    if (is)
    {
        cad1[0] = c;
        is.get(cad1 + 1, 32, ' ');
    }

    for(i= 0; i <= 32 && cad1[i] != '\0' && !(j != 0 && std::isspace(cad1[i])); ++i)
    {
        if (!std::isspace(cad1[i]))
        {
            cad2[j] = cad1[i];
            ++j;
        }
    }
    cad2[j] = '\0';
    if(j == 0)
    {
        cade = Cadena{};
    }
    else
    {
        cade = Cadena(cad2);
    }
    return is;
}

std::ostream& operator <<(std::ostream& os, const Cadena& cade)
{
    os << (const char*)(cade);
    return os;
}
