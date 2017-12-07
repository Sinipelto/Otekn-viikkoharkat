#include "paivays.hh"
#include <iostream>

int main()
{
    Paivays p(1, 2, 2014);

    std::cout << p.annaPaiva() << "." << p.annaKk() << "." << p.annaVuosi() << std::endl;
}
