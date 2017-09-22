#include "typedAny.h"

#include <cassert>
#include <iostream>

class Base {
};

class Derived : public Base {
};

class Derived2 : public Derived {
};

class Derived3 : public Derived2 {
};

int main() {
    TypedAny<Derived3, Derived2, Derived, Base> a;

    a.get();

    Any& b = a;

    auto c = b.as<Derived>();
    auto d = b.as<Base>();

    Any& b2 = *d;

    auto e = b2.as<Derived>();
    auto f = b2.as<Base>();

    auto g = b2.as<Derived>();
    auto h = b2.as<Base>();


    assert(a.get() == c->get());
    assert(a.get() == d->get());
    assert(a.get() == e->get());
    assert(a.get() == f->get());
    assert(a.get() == g->get());
    assert(a.get() == h->get());

    std::cout << std::boolalpha;
    std::cout << (a.get() == c->get()) << "\n";
    std::cout << (a.get() == d->get()) << "\n";
    std::cout << (a.get() == e->get()) << "\n";
    std::cout << (a.get() == f->get()) << "\n";
    std::cout << (a.get() == g->get()) << "\n";
    std::cout << (a.get() == h->get()) << "\n";

    return 0;
}
