#include <QString>
#include <QtTest>
#include <sstream>

#include "paivays.hh"

// Tarvitaan, jotta Qt:n testien makrot toimivat oman Viikonpäivä-enumin kanssa
// (ei kovin yleinen eikä oleellinen asia)
Q_DECLARE_METATYPE(Paivays::Viikonpaiva);

class Yksikkotesti : public QObject
{
    Q_OBJECT

public:
    Yksikkotesti();

private Q_SLOTS:
    void paivayksenLuominen();

    void helmikuunLaillisetPaivat();
    void helmikuunLaittomatPaivat();

    void kuukaudenAsetus();

    void kuukaudenVikat();
    void kuukaudenVikat_data();

    void viikonpaiva();
    void viikonpaiva_data();

    void tulostus();
};

Yksikkotesti::Yksikkotesti()
{
}

void Yksikkotesti::paivayksenLuominen()
{
    // Yksinkertainen testi, jossa testataan yhden päiväyksen luomista
    Paivays p(1, 2, 2014);
    QCOMPARE(p.annaPaiva(), 1u); // 1u tarvitaan, koska annaPaiva:n paluuarvo on unsigned int
    QCOMPARE(p.annaKk(), 2u);
    QCOMPARE(p.annaVuosi(), 2014u);
}

void Yksikkotesti::tulostus()
{
    // Luodaan ja tulostetaan päiväys merkkijonoon, tarkastetaan että oikein
    Paivays p(4, 5, 2000);
    std::ostringstream virta;
    p.tulosta(&virta);
    QCOMPARE(virta.str(), std::string("4.5.2000"));

    // Testataan tulostus tyhjällä osoittimella
    p.tulosta(nullptr);
}

void Yksikkotesti::helmikuunLaillisetPaivat()
{
    // Testataan silmukassa kaikki helmikuun päivät, varmistetaan että ok

    for (unsigned int paiva = 1; paiva <= 28; ++paiva)
    {
        Paivays p(1, 2, 2014);

        p.asetaPaiva(paiva);
        QCOMPARE(p.annaPaiva(), paiva);
//            try
//            {
//                p.asetaPaiva(paiva);
//                QCOMPARE(p.annaPaiva(), paiva);
//            }
//            catch (...)
//            {
//                QFAIL("Poikkeus laillisesta operaatiosta");
//            }
    }
}

void Yksikkotesti::helmikuunLaittomatPaivat()
{
    // Testataan silmukassa "helmikuun päivät" 29-31, varmistetaan että ei ok

    for (unsigned int paiva = 29; paiva <= 31; ++paiva)
    {
        Paivays p(1, 2, 2014);

        QVERIFY_EXCEPTION_THROWN(p.asetaPaiva(paiva), HuonoPaivays);
    }
}

void Yksikkotesti::kuukaudenAsetus()
{
    // Testataan silmukassa kaikkien kuukausien ensimmäiset päivät

    Paivays p(1, 1, 2014);
    for (unsigned int kuukausi = 1; kuukausi <= 12; ++kuukausi)
    {
        p.asetaKk(kuukausi);
        QCOMPARE(p.annaPaiva(), 1u);
        QCOMPARE(p.annaKk(), kuukausi);
        QCOMPARE(p.annaVuosi(), 2014u);
    }
}

void Yksikkotesti::kuukaudenVikat()
{
    // Luodaan päiväykset joka kuukauden viimeiselle päivälle
    QFETCH(unsigned int, kuukausi);
    QFETCH(unsigned int, pituus);

    // Luodaan päiväys, siirrytään seuraavaan päivään, varmistutaan että kuukausi vaihtuu
    Paivays p(pituus, kuukausi, 2014);
    p.etene(1);
    QCOMPARE(p.annaKk(), kuukausi+1);
}

void Yksikkotesti::kuukaudenVikat_data()
{
    // Tämä metodi määrittelee kuukausitestin testimatriisin ja tuottaa sinne halutut testitapaukset

    // Määritellään testimatriisin sarakkeet (tyypit ja nimet)
    QTest::addColumn<unsigned int>("kuukausi");
    QTest::addColumn<unsigned int>("pituus");

    // Tuotetaan testimatriisiin testitapaukset, 31u jne. tarvitaan taas, koska tyyppi on unsigned
    QTest::newRow("tammi") << 1u << 31u;
    QTest::newRow("helmi") << 2u << 28u;
    QTest::newRow("maalis") << 3u << 31u;
    QTest::newRow("huhti") << 4u << 30u;
    QTest::newRow("touko") << 5u << 31u;
    QTest::newRow("kesä") << 6u << 30u;
    QTest::newRow("heinä") << 7u << 31u;
    QTest::newRow("elo") << 8u << 31u;
    QTest::newRow("syys") << 9u << 30u;
    QTest::newRow("loka") << 10u << 311u;
    QTest::newRow("marras") << 11u << 30u;
    QTest::newRow("joulu") << 12u << 31u;
}

void Yksikkotesti::viikonpaiva()
{
    // Tämä metodi testaa yhden viikonpaiva_data-metodin tuottaman testimatriisin rivin.
    // Sitä kutsutaan automaattisesti jokaiselle matriisin riville

    // Haetaan data matriisista, luodaan automaattisesti muuttujat
    QFETCH(unsigned int, paiva);
    QFETCH(unsigned int, kuukausi);
    QFETCH(unsigned int, vuosi);
    QFETCH(Paivays::Viikonpaiva, viikonpaiva);

    // Suoritetaan testi
    Paivays p(paiva, kuukausi, vuosi);
    QVERIFY2(p.annaViikonpaiva() == viikonpaiva, "Väärä viikonpäivä");
}

void Yksikkotesti::viikonpaiva_data()
{
    // Tämä metodi määrittelee viikonpäivätestin testimatriisin ja tuottaa sinne halutut testitapaukset

    // Määritellään testimatriisin sarakkeet (tyypit ja nimet)
    QTest::addColumn<unsigned int>("paiva");
    QTest::addColumn<unsigned int>("kuukausi");
    QTest::addColumn<unsigned int>("vuosi");
    QTest::addColumn<Paivays::Viikonpaiva>("viikonpaiva");

    // Tuotetaan testimatriisiin testitapaukset, 3u jne. tarvitaan taas, koska tyyppi on unsigned
    QTest::newRow("tänään") << 3u << 2u << 2014u << Paivays::MAANANTAI;
    QTest::newRow("viime joulu") << 24u << 12u << 2013u << Paivays::TIISTAI;
    QTest::newRow("ensi vappu") << 1u << 5u << 2014u << Paivays::TORSTAI;
    QTest::newRow("viime vuoden loppu") << 31u << 12u << 2013u << Paivays::TIISTAI;
    QTest::newRow("uusi vuosi") << 1u << 1u << 2014u << Paivays::KESKIVIIKKO;
}

QTEST_APPLESS_MAIN(Yksikkotesti)

#include "tst_yksikkotesti.moc"
