#include "date.hh"
#include <iostream>

int main()
{
    Date d(1, 2, 2014);

    std::cout << d.giveDay() << "." << d.giveMonth() << "." << d.giveYear() << std::endl;
    d.step(5);
    std::cout << d.giveDay() << "." << d.giveMonth() << "." << d.giveYear() << std::endl;
}
