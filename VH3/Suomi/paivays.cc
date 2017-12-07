#include "paivays.hh"
#include <QtDebug>

void Paivays::asetaPaiva(unsigned int paiva)
{
    Q_ASSERT(1 <= paiva && paiva <= 31); // Esiehto
    invariantti();

    if (paiva > kuukaudenPituus())
    {
        throw HuonoPaivays();
    }

    paiva_ = paiva;

    Q_ASSERT(paiva_ == paiva); // Ei näin simppeliä oikeasti kirjoiteta. :)
    invariantti();
}

unsigned int Paivays::kuukaudenPituus() const
{
    return -1; // Palauta jotain järjetöntä, kun ei kerran ole toteutettu
}

void Paivays::invariantti() const
{
    Q_ASSERT(1 <= paiva_ && paiva_ <= kuukaudenPituus() && 1 <= kuukausi_ && kuukausi_ <= 12 && vuosi_ >= 1754);
}


// Tyhjä pääohjelma, jotta käännös menee läpi
int main()
{
}
