/**@file	/home/talos/Projets/Menli/sources/symbolic.hpp
 * @author	talos
 * @version	801
 * @date
 * 	Created:	13th Aug 2019
 * 	Last Update:	13th Aug 2019
 */

#ifndef SYMBOLIC_HPP
#define SYMBOLIC_HPP
#include <iostream>
#include <memory>
#include <functional>

class Symbol : public std::enable_shared_from_this<Symbol>
{
    public:
        using Ptr = std::shared_ptr<Symbol>;
        virtual float eval() =0;
        friend std::ostream& operator<<(std::ostream& stream, Symbol::Ptr p) {stream << (p->eval()); return stream;}
};

class Cst : public Symbol
{
    public:
        using Ptr = std::shared_ptr<Cst>;
        explicit Cst(float t) : _val(t) {}
        Cst& operator=(float value) {_val = value; return *this;}
        float eval() final override {return _val;}
        void set(float v) {_val = v;}
    private:
        float _val;
};

class Sum : public Symbol
{
    public:
        Sum() = delete;
        Sum(Symbol::Ptr lhs, Symbol::Ptr rhs) : _lhs(lhs), _rhs(rhs) {}
        float eval() override {return _lhs->eval() + _rhs->eval();}

    private:
        Symbol::Ptr _lhs;
        Symbol::Ptr _rhs;
};

Sum::Ptr operator+(Symbol::Ptr lhs, Symbol::Ptr rhs) {
    return std::make_shared<Sum>(lhs, rhs);
};

class CstHolder
{
public:
    template <typename ...Args>
    CstHolder(Args... args) : _ptr(std::make_shared<Cst>(args...)) {}
    CstHolder(Cst::Ptr ptr) : _ptr(ptr) {}
    CstHolder& operator=(float x) {*_ptr = x; return *this;}
    friend std::ostream& operator<<(std::ostream& stream, CstHolder& holder) {stream << static_cast<Symbol::Ptr>(holder._ptr); return stream;}
private:
    Cst::Ptr _ptr;
};

int main()
{
    Cst::Ptr c = std::make_shared<Cst>(5);
    auto x = std::make_shared<Cst>(3) + c;
    auto y = x+x;

    CstHolder cc(10);
    std::cout << cc << std::endl;
    cc = 15;
    std::cout << cc << std::endl;

    std::cout << y << std::endl;
    c->set(10);
    *c = 10;
    std::cout << y << std::endl;
    return 0;
}


#endif // SYMBOLIC_HPP
