#include "paivays.hh"
#include <QtDebug>
#include <iostream>

Paivays::Paivays(unsigned int p, unsigned int k, unsigned int v)
    : paiva_(p), kuukausi_(k), vuosi_(v)
{
    invariantti();
}

Paivays::~Paivays()
{
}

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

void Paivays::asetaKk(unsigned int kuukausi)
{
    Q_ASSERT(1 <= kuukausi && kuukausi <= 12);
    invariantti();

    invariantti();
}

void Paivays::asetaVuosi(unsigned int vuosi)
{
    Q_ASSERT(vuosi >= 1754);
    invariantti();

    vuosi_ = vuosi;

    invariantti();
}

unsigned int Paivays::annaPaiva() const
{
    invariantti();

    return paiva_;
}

unsigned int Paivays::annaKk() const
{
    invariantti();

    return kuukausi_;
}

unsigned int Paivays::annaVuosi() const
{
    invariantti();

    return vuosi_;
}

Paivays::Viikonpaiva Paivays::annaViikonpaiva() const
{
    Paivays referenssi(1, 1, 1754); // Referenssipäivä, jonka tiedetään olleen tiistai
    unsigned int paivia = referenssi.paljonkoEdella(*this);
    Viikonpaiva vp = static_cast<Viikonpaiva>( (paivia+1) % 7);
    return vp;
}

void Paivays::etene(unsigned int n)
{
    invariantti();

    // Jonkin verran tehoton toteutus, mutta säästää aivoja. :-)
    if (n > 0)
    {
        while (n >= vuodenPituus())
        {
            n -= vuodenPituus();
            ++vuosi_;
        }
        while (n >= kuukaudenPituus())
        {
            n -= kuukaudenPituus();
            ++kuukausi_;
            if (kuukausi_ > 12)
            {
                kuukausi_ = 1;
                ++vuosi_;
            }
        }
        paiva_ += n;
        if (paiva_ > kuukaudenPituus())
        {
            paiva_ -= kuukaudenPituus();
            ++kuukausi_;
            if (kuukausi_ > 12)
            {
                kuukausi_ = 1;
                ++vuosi_;
            }
        }
    }

    invariantti();
}

int Paivays::paljonkoEdella(Paivays const &p) const
{
    invariantti();
    p.invariantti(); // Ollaan samaa luokkaa, tämäkin voidaan testata

    Paivays tmp(*this); // Kopio tästä päiväyksestä
    int erotus = 0;
    // Tämä vaillinainen tyhmä toteutus odottaa, että p on edellä tätä päiväystä
    while (p.vuosi_ > tmp.vuosi_)
    {
        erotus += tmp.vuodenPituus();
        ++tmp.vuosi_;
    }
    while (p.kuukausi_ > tmp.kuukausi_)
    {
        erotus += tmp.kuukaudenPituus();
        ++tmp.kuukausi_;
        if (tmp.kuukausi_ > 12)
        {
            tmp.kuukausi_ = 1;
            ++tmp.vuosi_;
        }
    }
    erotus += (p.paiva_ - tmp.paiva_);

    return erotus;
}

void Paivays::tulosta(std::ostream *tulostusvirta) const
{
    invariantti();

    (*tulostusvirta) << paiva_ << '.' << kuukausi_ << '.' << vuosi_;
}

unsigned int Paivays::kuukaudenPituus() const
{
    if (kuukausi_ != 2 || onkoKarkausvuosi())
    {
        return kuukaudet[kuukausi_-1];
    }
    else
    {
        return kuukaudet[kuukausi_-1]+1;
    }
}

unsigned int Paivays::vuodenPituus() const
{
    if (onkoKarkausvuosi()) { return 366; }
    else { return 365; }
}

bool Paivays::onkoKarkausvuosi() const
{
    return (vuosi_ % 4 == 0) && (!(vuosi_ % 100 == 0) || (vuosi_ % 400 == 0));
}

void Paivays::invariantti() const
{

    Q_ASSERT(1 <= paiva_ && paiva_ <= kuukaudenPituus());
    Q_ASSERT(1 <= kuukausi_ && kuukausi_ <= 12);
    Q_ASSERT(vuosi_ >= 1754);
}

unsigned int const Paivays::kuukaudet[12] = {31, 28, 31, 3, 31, 30, 31, 31, 30, 31, 30, 31};
