#include <iostream>
#include <ctime>
#include <string>
#include <cstring>
#include <cstdio>

#include "fecha.hpp"

const unsigned Fecha::AnnoMinimo(1902);
const unsigned Fecha::AnnoMaximo(2037);

Fecha::Invalida::Invalida(const char *e)
{
    std::strcpy(error, e);
}

Fecha::Fecha(int diaPas, int mesPas, int annoPas): Dia(diaPas), Mes(mesPas), Anno(annoPas), actual(false)
{
    unsigned diaM = 31;

    actualidad();
    diaM = diaMaximo();
    if(!comprobarFecha(diaM))
    {
        throw Fecha::Invalida("La fecha introducida es invalida");
    }
}

Fecha::Fecha(const char *cad): Dia(-1), Mes(-1), Anno(-1)
{
    unsigned diaM;
    char cad1[10], cad2[3], cad3[11], cad4[6];
    sscanf(cad, "%i/%i/%i", &Dia, &Mes, &Anno);
    if(Dia < 0 || Mes < 0 || Anno < 0)
    {
        throw Fecha::Invalida("La fecha introducida es invalida");
    }
    else
    {
        actualidad();
        diaM = diaMaximo();
        dia_semana(cad1);
        std::strcpy(crep, cad1);
        std::strcat(crep, " ");
        dia_a_cadena(cad2);
        std::strcat(crep, cad2);
        std::strcat(crep, " de ");
        mes_a_cadena(cad3);
        std::strcat(crep, cad3);
        std::strcat(crep, " de ");
        anno_a_cadena(cad4);
        std::strcat(crep, cad4);
        std::strcat(crep, "\0");
        actual = true;
        if(!comprobarFecha(diaM))
        {
            throw Fecha::Invalida("La fecha introducida es invalida");
        }
    }
}

bool Fecha::comprobarFecha(const unsigned& diaM) const
{
    bool valida = false;
    if(Anno < Fecha::AnnoMaximo && Anno > Fecha::AnnoMinimo)
    {
        if(Mes <= 12 && Mes > 0)
        {
            if(Dia <= diaM && Dia > 0)
            {
                valida = true;
            }
        }
    }
    return valida;
}

void Fecha::actualidad()
{
    std::time_t tiempo = std::time(nullptr);
    std::tm* tiempo_p = std::localtime(&tiempo); //Consigo el puntero con la hora del sistema
    if(Dia == 0)     //Compruebo si se ha puesto d�a actual
    {
        Dia = tiempo_p->tm_mday;
    }
    if(Mes == 0)     //Compruebo si se ha puesto mes actual
    {
        Mes = tiempo_p->tm_mon + 1;
    }
    if(Anno == 0)    //Compruebo si se ha puesto a�o actual
    {
        Anno = tiempo_p->tm_year + 1900;
    }
}

unsigned Fecha::diaMaximo() const
{
    unsigned diaM = 31;
    if(Mes == 4 || Mes == 6 || Mes == 9 || Mes == 11)
    //Compruebo si es un mes con solo 30 d�as
    {
        diaM = 30;
    }
    else
    {
        if(Mes == 2)
        //Compruebo si es Febrero
        {
            if(Anno % 4 == 0)
            //Si es bisiesto
            {
                diaM = 29;
            }
            else
            {
                diaM = 28;
            }
        }
    }
    return diaM;
}

Fecha& Fecha::operator+=(int e)
{
    int diasDeMas;
    Fecha f{*this};
    Dia = Dia + e;
    actual = false;
    if(e == 0)
    {
        actual = true;
    }
    else
    {
        try
        {
            if(Dia > diaMaximo())
            {
                diasDeMas = Dia - diaMaximo();
                while(diasDeMas > 0)
                {
                    ++Mes;
                    if(Mes > 12)
                    {
                        Mes = 1;
                        ++Anno;
                    }
                    Dia = diasDeMas;
                    diasDeMas = Dia - diaMaximo();
                }
            }
            else
            {
                if(Dia < 1)
                {
                    diasDeMas = - Dia;
                    while(diasDeMas >= 0)
                    {
                        --Mes;
                        if(Mes == 0)
                        {
                            Mes = 12;
                            --Anno;
                        }
                        Dia = diaMaximo() - diasDeMas;
                        diasDeMas = -Dia;
                    }
                }
            }
            if(!comprobarFecha(diaMaximo()))
            {
                throw Fecha::Invalida("Fecha fuera de rango");
            }
        }
        catch(Fecha::Invalida&)
        {
            std::cout << "La modificacion no es valida, la fecha devuelta sera la fecha operando sin modificar";
            *this = f;
        }
    }
    return *this;
}

Fecha& Fecha::operator++()
{
    *this += 1;
    return *this;
}

Fecha Fecha::operator++(int)
{
    Fecha copia(*this);
    *this += 1;
    return copia;
}

Fecha& Fecha::operator--()
{
    *this += -1;
    return *this;
}

Fecha Fecha::operator--(int)
{
    Fecha copia(*this);
    *this += -1;
    return copia;
}

Fecha Fecha::operator+(int e) const
{
    Fecha fech{*this};
    fech += e;
    return fech;
}


Fecha Fecha::operator-(int e) const
{
    Fecha fech{*this};
    fech += -e;
    return fech;
}

Fecha& Fecha::operator-=(int e)
{
    *this += -e;
    return *this;
}

const char* Fecha::cadena() const
{
    int i;
    char cad1[10], cad2[3], cad3[11], cad4[6];
    if(actual)
    {
        return crep;
    }
    else
    {
        dia_semana(cad1);
        std::strcpy(crep, cad1);
        std::strcat(crep, " ");
        dia_a_cadena(cad2);
        std::strcat(crep, cad2);
        std::strcat(crep, " de ");
        mes_a_cadena(cad3);
        std::strcat(crep, cad3);
        std::strcat(crep, " de ");
        anno_a_cadena(cad4);
        std::strcat(crep, cad4);
        std::strcat(crep, "\0");
        actual = true;
        return crep;
    }
}

bool operator<(const Fecha& f1, const Fecha& f2)
{
    bool res = true;
    if(f1.Anno > f2.Anno)
    {
        res = false;
    }
    else
    {
        if(f1.Anno == f2.Anno && f1.Mes > f2.Mes)
        {
            res = false;
        }
        else
        {
            if(f1.Anno == f2.Anno && f1.Mes == f2.Mes && f1.Dia >= f2.Dia)
            {
                res = false;
            }
        }
    }
    return res;
}

bool operator==(const Fecha& f1, const Fecha& f2)
{
    bool res = false;
    if(f1.Dia == f2.Dia && f1.Mes == f2.Mes && f1.Anno == f2.Anno)
    {
        res = true;
    }
    return res;
}

bool operator<=(const Fecha& f1, const Fecha& f2)
{
    return !(f2 < f1);
}

bool operator>(const Fecha& f1, const Fecha& f2)
{
    return f2 < f1;
}

bool operator>=(const Fecha& f1, const Fecha& f2)
{
    return !(f1 < f2);
}

bool operator!=(const Fecha& f1, const Fecha& f2)
{
    return !(f1 == f2);
}

void Fecha::dia_semana(char *cad) const
{
    unsigned Dia_semana;
    std::time_t tiempo = std::time(nullptr);
    std::tm* tiempo_p = std::localtime(&tiempo); //Consigo el puntero con la hora del sistema

    if(Dia == tiempo_p->tm_mday && Mes == tiempo_p->tm_mon + 1 && Anno == tiempo_p->tm_year + 1900)
    {
        Dia_semana = tiempo_p->tm_wday;
    }
    else
    {
        Dia_semana = CalcularDiaSemana();
    }
    if(Dia_semana == 0)
    {
        Dia_semana = 7;
    }
    switch(Dia_semana)
    {
    case 1:
        std::strcpy(cad, "lunes");
        cad[5] = '\0';
        break;
    case 2:
        std::strcpy(cad, "martes");
        cad[6] = '\0';
        break;
    case 3:
        std::strcpy(cad, "miercoles");
        cad[9] = '\0';
        break;
    case 4:
        std::strcpy(cad, "jueves");
        cad[6] = '\0';
        break;
    case 5:
        std::strcpy(cad, "viernes");
        cad[7] = '\0';
        break;
    case 6:
        std::strcpy(cad, "sabado");
        cad[6] = '\0';
        break;
    case 7:
        std::strcpy(cad, "domingo");
        cad[7] = '\0';
        break;
    }
}

void Fecha::dia_a_cadena(char *cad) const
{
    int i;
    std::string cad2 = std::to_string(Dia);
    for(i = 0; cad2[i] != '\0'; ++i)
    {
        cad[i] = cad2[i];
    }
    cad[i] = '\0';
}

void Fecha::mes_a_cadena(char *cad) const
{
    switch(Mes)
    {
    case 1:
        std::strcpy(cad, "enero");
        cad[5] = '\0';
        break;
    case 2:
        std::strcpy(cad, "febrero");
        cad[7] = '\0';
        break;
    case 3:
        std::strcpy(cad, "marzo");
        cad[5] = '\0';
        break;
    case 4:
        std::strcpy(cad, "abril");
        cad[5] = '\0';
        break;
    case 5:
        std::strcpy(cad, "mayo");
        cad[4] = '\0';
        break;
    case 6:
        std::strcpy(cad, "junio");
        cad[5] = '\0';
        break;
    case 7:
        std::strcpy(cad, "julio");
        cad[5] = '\0';
        break;
    case 8:
        std::strcpy(cad, "agosto");
        cad[6] = '\0';
        break;
    case 9:
        std::strcpy(cad, "septiembre");
        cad[10] = '\0';
        break;
    case 10:
        std::strcpy(cad, "octubre");
        cad[7] = '\0';
        break;
    case 11:
        std::strcpy(cad, "noviembre");
        cad[9] = '\0';
        break;
    case 12:
        std::strcpy(cad, "diciembre");
        cad[9] = '\0';
        break;
    }
}

void Fecha::anno_a_cadena(char *cad) const
{
    std::string cad2 = std::to_string(Anno);
    cad[0] = cad2[0];
    cad[1] = cad2[1];
    cad[2] = cad2[2];
    cad[3] = cad2[3];
    cad[4] = '\0';
}

int Fecha::CalcularDiaSemana() const
{
    int no_bisiesto[12] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
    int bisiesto[12] = {0, 3, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6};
    int DM, res1, res2, res3, res4, DiaSem;
    if(Anno % 4 == 0)
    {
        DM = bisiesto[Mes - 1];
    }
    else
    {
        DM = no_bisiesto[Mes - 1];
    }
    res1 = (Anno - 1) % 7;
    res2 = (Anno - 1) / 4;
    res3 = (3 * (((Anno - 1) / 100) + 1)) / 4;
    res4 = Dia % 7;
    DiaSem = (res1 + ((res2 - res3) % 7) + DM + res4) % 7;
    return DiaSem;
}

std::istream& operator >>(std::istream& is, Fecha& fech)
{
    char cad[100];
    is.getline(cad, 100, '\n');
    fech = Fecha(cad);
    return is;
}

std::ostream& operator <<(std::ostream& os, const Fecha& fech)
{
    os << fech.cadena();
    return os;
}
