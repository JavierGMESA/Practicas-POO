#ifndef CADENA_HPP_
#define CADENA_HPP_
#include <iterator>
#include <string>


class Cadena
{
public:

    typedef char* iterator;
    typedef const char* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    class Invalida{};

    explicit Cadena(const size_t& tam = 0, const char& c = ' ');
    Cadena(const char *cad);

    explicit operator const char*() const;
    inline const size_t& length() const;

    const char& operator[](const size_t& index) const;
    char& operator[](const size_t& index);
    const char& at(const size_t& index) const;
    char& at(const size_t& index);
    Cadena substr(const size_t& index, const size_t& tama) const;

    Cadena& operator+=(const Cadena& cade);
    Cadena& operator=(const char* cad);

    iterator begin(){return s_;}
    iterator end(){return s_ + tam_;}
    const_iterator cbegin() const{return s_;}
    const_iterator cend() const{return s_ + tam_;}
    reverse_iterator rbegin(){return reverse_iterator(end());}
    reverse_iterator rend(){return reverse_iterator(begin());}
    const_reverse_iterator crbegin() const{return const_reverse_iterator(cend());}
    const_reverse_iterator crend() const{return const_reverse_iterator(cbegin());}

    Cadena(const Cadena& cade);
    Cadena& operator=(const Cadena& cade);
    Cadena(Cadena&& cade);
    Cadena& operator=(Cadena&& cade);
    ~Cadena();
private:
    static char vacia[1];
    size_t tam_;
    char* s_;
};

const size_t& Cadena::length() const
{
    return tam_;
}

Cadena operator+(const Cadena& cade1, const Cadena& cade2);
bool operator<(const Cadena& cade1, const Cadena& cade2);
bool operator<=(const Cadena& cade1, const Cadena& cade2);
bool operator>(const Cadena& cade1, const Cadena& cade2);
bool operator>=(const Cadena& cade1, const Cadena& cade2);
bool operator==(const Cadena& cade1, const Cadena& cade2);
bool operator!=(const Cadena& cade1, const Cadena& cade2);

std::istream& operator >>(std::istream& is, Cadena& cade);

std::ostream& operator <<(std::ostream& os, const Cadena& cade);

template <>
struct std::hash<Cadena>
{
    size_t operator()(const Cadena& cad) const
    {
        std::hash<string> hs;
        auto p{(const char*)(cad)};
        std::string s{p};
        size_t res{hs(s)};
        return res;
    }
};

#endif // CADENA_HPP_
