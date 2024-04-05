#ifndef FECHA_HPP_
#define FECHA_HPP_
#include <cstring>

class Fecha
{
public:

    const static unsigned AnnoMinimo;
    const static unsigned AnnoMaximo;
    class Invalida
    {
    public:
        Invalida(const char * e);
        const char* por_que() const
        {
            return error;
        }
    private:
        char error[40];
    };

    explicit Fecha(int diaPas = 0, int mesPas = 0, int annoPas = 0);
    Fecha(const char *cad);

    Fecha& operator++();
    Fecha operator++(int);
    Fecha& operator--();
    Fecha operator--(int);
    Fecha operator+(int e) const;
    Fecha operator-(int e) const;
    Fecha& operator+=(int e);
    Fecha& operator-=(int e);

    inline const int& dia() const;
    inline const int& mes() const;
    inline const int& anno() const;
    const char* cadena() const;

    friend bool operator<(const Fecha& f1, const Fecha& f2);
    friend bool operator==(const Fecha& f1, const Fecha& f2);

private:
    int Dia, Mes, Anno;
    mutable char crep[36];
    mutable bool actual;

    void actualidad(); //funci�n para transformar los valores 0 por el valor de la fecha actual
    unsigned diaMaximo() const; //funci�n que devuelve el d�a maximo del mes actual de la fecha
    bool comprobarFecha(const unsigned& diaM) const; //funci�n que comprueba que la fecha sea valida o no

    void dia_semana(char *cad) const;
    void dia_a_cadena(char *cad) const;
    void mes_a_cadena(char *cad) const;
    void anno_a_cadena(char *cad) const;
    int CalcularDiaSemana() const;
};

bool operator<=(const Fecha& f1, const Fecha& f2);
bool operator>(const Fecha& f1, const Fecha& f2);
bool operator>=(const Fecha& f1, const Fecha& f2);
bool operator!=(const Fecha& f1, const Fecha& f2);

const int& Fecha::dia() const
{
    return Dia;
}

const int& Fecha::mes() const
{
    return Mes;
}

const int& Fecha::anno() const
{
    return Anno;
}

std::istream& operator >>(std::istream& is, Fecha& fech);

std::ostream& operator <<(std::ostream& os, const Fecha& fech);

#endif // FECHA_HPP_
