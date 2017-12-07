#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>    // ostringstream-tyyppi
#include <random>     // heita_arpakuutiota-funktion satunnaisluvut
#include <ctime>      // Satunnaislukugeneraattorin alustus

using namespace std;


const string YATZY          {"yatzy"};
const string NELILUKU       {"neliluku"};
const string TAYSKASI       {"tayskasi"};
const string SUORA          {"suora"};
const string KOLMILUKU      {"kolmiluku"};
const string KAKSI_PARIA    {"kaksi paria"};
const string PARI           {"pari"};
const string EI_YHDISTELMAA {"ei yhdistelmaa"};


//-----------------------------------------------------------------------------
// Moduulin yksityisen rajapinnan funktiot

namespace {


//-----------------------------------------------------------------------------
// Funktiot, jotka tunnistavat, onko kyseessä jokin tietty yhdistelmä

bool onko_yatzy(const map<int, int>& tilasto) {
    if ( tilasto.size() == 1 ) {
        return true;
    } else {
        return false;
    }
}

bool onko_neliluku(const map<int, int>& tilasto) {
    if ( tilasto.size() == 2 ) {
        int jompi_kumpi_lukumaara{ tilasto.begin()->second };
        if ( jompi_kumpi_lukumaara == 1 or jompi_kumpi_lukumaara == 4 ) {
            return true;
        }
    }

    return false;
}

bool onko_tayskasi(const map<int, int>& tilasto) {
    if ( tilasto.size() == 2 and not onko_neliluku(tilasto) ) {
        return true;
    } else {
        return false;
    }
}

bool onko_suora(const map<int, int>& tilasto) {
    if ( tilasto.size() == 5
           and (tilasto.find(1) == tilasto.end()
                  or tilasto.find(6) == tilasto.end()) ) {
            return true;
    } else {
        return false;
    }
}

bool onko_kolmiluku(const map<int, int>& tilasto) {
    if ( tilasto.size() == 3 ) {
        for ( auto infopari : tilasto ) {
            if ( infopari.second == 3 ) {
                return true;
            }
        }
    }

    return false;
}

bool onko_kaksiparia(const map<int, int>& tilasto) {
    if ( tilasto.size() == 3 and not onko_kolmiluku(tilasto) ) {
        return true;
    } else {
        return false;
    }
}

bool onko_pari(const map<int, int>& tilasto) {
    if ( tilasto.size() == 4 ) {
        return true;
    } else {
        return false;
    }
}

bool onko_kutonen(const map<int, int>& tilasto) {
    if ( tilasto.size() == 5 and not onko_suora(tilasto) ) {
        return true;
    } else {
        return false;
    }
}


//-----------------------------------------------------------------------------
// Funktiot, jotka muodostavat tekstuaalisen esityksen tulokselle.

string muotoile_tulos_yatzy(const map<int, int>& tilasto) {
    ostringstream tulosvirta{""};

    tulosvirta << YATZY << " (" << tilasto.begin()->second << ")";

    return tulosvirta.str();
}

string muotoile_tulos_neliluku(const map<int, int>& tilasto) {
    ostringstream tulosvirta{""};

    int mita_nelja{0};
    int mita_yksi{0};

    for ( auto pari : tilasto ) {
        if ( pari.second == 4 ) {
            mita_nelja = pari.first;
        } else {
            mita_yksi = pari.first;
        }
    }

    tulosvirta << NELILUKU << " (" << mita_nelja << "), lisaksi " << mita_yksi;

    return tulosvirta.str();
}

string muotoile_tulos_tayskasi(const map<int, int>& tilasto) {
    ostringstream tulosvirta{""};

    int mita_kolme{0};
    int mita_kaksi{0};

    for ( auto pari : tilasto ) {
        if ( pari.second == 3 ) {
            mita_kolme = pari.first;
        } else {
            mita_kaksi = pari.first;
        }
    }

    tulosvirta << TAYSKASI << " (" << mita_kolme << ", " << mita_kaksi << ")";

    return tulosvirta.str();
}

string muotoile_tulos_suora(const map<int, int>& tilasto) {
    ostringstream tulosvirta{""};

    tulosvirta << "suora (";

    if ( tilasto.find(1) == tilasto.end() ) {
        tulosvirta << 6;
    } else {
        tulosvirta << 1;
    }

    tulosvirta << ")";

    return tulosvirta.str();
}

string muotoile_tulos_kolmiluku(const map<int, int>& tilasto) {
    ostringstream tulosvirta{""};

    int mita_kolme{0};
    vector<int> mita_yksi{};

    for ( auto pari : tilasto ) {
        if ( pari.second == 3 ) {
            mita_kolme = pari.first;
        } else {
            mita_yksi.push_back(pari.first);
        }
    }

    sort(mita_yksi.begin(), mita_yksi.end());

    tulosvirta << KOLMILUKU << " (" << mita_kolme << "), lisaksi "
               << mita_yksi.at(1) << " ja " << mita_yksi.at(0);

    return tulosvirta.str();
}

string muotoile_tulos_kaksiparia(const map<int, int>& tilasto) {
    ostringstream tulosvirta{""};

    vector<int> mita_kaksi{};
    int mita_yksi{0};

    for ( auto pari : tilasto ) {
        if ( pari.second == 1 ) {
            mita_yksi = pari.first;
        } else {
            mita_kaksi.push_back(pari.first);
        }
    }

    sort(mita_kaksi.begin(), mita_kaksi.end());

    tulosvirta << KAKSI_PARIA << " ("
               << mita_kaksi.at(1) << ", " << mita_kaksi.at(0)
               << "), lisaksi " << mita_yksi;

    return tulosvirta.str();
}

string muotoile_tulos_pari(const map<int, int>& tilasto) {
    ostringstream tulosvirta{""};

    int mita_kaksi{0};
    vector<int> mita_yksi{};

    for ( auto pari : tilasto ) {
        if ( pari.second == 2 ) {
            mita_kaksi = pari.first;
        } else {
            mita_yksi.push_back(pari.first);
        }
    }

    sort(mita_yksi.begin(), mita_yksi.end());

    tulosvirta << PARI << " (" << mita_kaksi << "), lisaksi "
               << mita_yksi.at(2) << ", "
               << mita_yksi.at(1) << ", "
               << mita_yksi.at(0);

    return tulosvirta.str();
}

string muotoile_tulos_kutonen(const map<int, int>& tilasto) {
    ostringstream tulosvirta{""};

    vector<int> silmaluvut;

    for ( auto pari : tilasto ) {
        silmaluvut.push_back(pari.first);
    }

    // sort-funktion kutsu on turha, miksi?
    // sort(silmaluvut.begin(), silmaluvut.end());

    tulosvirta << EI_YHDISTELMAA << " (" << silmaluvut.at(4) << "), lisaksi ";
    silmaluvut.pop_back();
    reverse(silmaluvut.begin(), silmaluvut.end());

    for ( int silmaluku : silmaluvut ) {
        tulosvirta << silmaluku << ", ";
    }

    return tulosvirta.str();
}

} // namespace:n loppusulku


//-----------------------------------------------------------------------------
// Julkisen rajapinnan funktiot

int heita_arpakuutiota() {
    static unsigned int seed{static_cast<unsigned int>(time(0))};
    static default_random_engine engine{seed};
    static uniform_int_distribution<int> generator{1, 6};

    return generator(engine);
}

string tulkitse_tulos(const vector<int>& silmaluvut) {
    // Tämän funktion on tarkoitus muodostaa ja palauttaa sanallinen tulkinta
    // <<silmaluvut>>-vektoriin talletetuille arpakuutioiden arvoille.
    // Esitysmuoto voisi olla vaikkapa jotain tyyliin:
    //   5 5 5 5 5  -> "yatzy (5)"
    //   3 2 3 3 3  -> "neliluku (3), lisaksi 2"
    //   5 1 1 5 5  -> "tayskasi (5, 1)"
    //   4 2 6 5 3  -> "suora (6)"
    //   4 6 4 4 2  -> "kolmiluku (4), lisaksi 6 ja 2",
    //   5 1 1 2 5  -> "kaksi paria (5, 1), lisaksi 2"
    //   3 1 6 4 3  -> "pari (3), lisaksi 6, 4, 1"
    //   2 6 1 4 5  -> "ei yhdistelmaa (6), lisaksi 5, 4, 2, 1"
    // tai jotain muuta mielestäsi selkeää.

    // map<silmäluku, montako_kappaletta>
    map<int, int> silmalukutilasto;

    for ( int silmaluku : silmaluvut ) {
        if ( silmalukutilasto.find(silmaluku) == silmalukutilasto.end() ) {
            silmalukutilasto.insert( { silmaluku, 1 } );
        } else {
            ++silmalukutilasto.at(silmaluku);
        }
    }

    if ( onko_yatzy(silmalukutilasto) ) {
        return muotoile_tulos_yatzy(silmalukutilasto);

    } else if ( onko_neliluku(silmalukutilasto) ) {
        return muotoile_tulos_neliluku(silmalukutilasto);

    } else if ( onko_tayskasi(silmalukutilasto) ) {
        return muotoile_tulos_tayskasi(silmalukutilasto);

    } else if ( onko_suora(silmalukutilasto) ) {
        return muotoile_tulos_suora(silmalukutilasto);

    } else if ( onko_kolmiluku(silmalukutilasto) ) {
        return muotoile_tulos_kolmiluku(silmalukutilasto);

    } else if ( onko_kaksiparia(silmalukutilasto) ) {
        return muotoile_tulos_kaksiparia(silmalukutilasto);

    } else if ( onko_pari(silmalukutilasto) ) {
        return muotoile_tulos_pari(silmalukutilasto);

    } else if ( onko_kutonen(silmalukutilasto) ) {
        return muotoile_tulos_kutonen(silmalukutilasto);

    } else {

        return "This is not happening...";
    }
}


string paattele_voittaja(const vector<int>& pelaajan_1_silmaluvut,
                         const vector<int>& pelaajan_2_silmaluvut) {
    // Tämän funktion pitäisi muodostaa ja palauttaa jokin merkkijonoista:
    //   "pelaaja 1 on voittoisa!"
    //   "pelaaja 2 on voittoisa!"
    //   "tulos on tasapeli!"

    const map<string, string> yhdistelmien_arvot{
        { YATZY,          "8" },
        { NELILUKU,       "7" },
        { TAYSKASI,       "6" },
        { SUORA,          "5" },
        { KOLMILUKU,      "4" },
        { KAKSI_PARIA,    "3" },
        { PARI,           "2" },
        { EI_YHDISTELMAA, "1" },
    };

    vector<string> tulkinnat {
        tulkitse_tulos(pelaajan_1_silmaluvut),
        tulkitse_tulos(pelaajan_2_silmaluvut),
    };


    for ( string& tulkinta : tulkinnat ) {
       for ( auto arvopari : yhdistelmien_arvot ) {
          if ( tulkinta.substr(0, arvopari.first.length()) == arvopari.first ) {
              // Tuloksena saadaan merkkijonoja, jotka ovat muotoa:
              //   5 5 5 5 5  -> "8yatzy (5)"
              //   3 2 3 3 3  -> "7neliluku (3), lisaksi 2"
              //   5 1 1 5 5  -> "6tayskasi (5, 1)"
              //   4 2 6 5 3  -> "5suora (6)"
              //   4 6 4 4 2  -> "4kolmiluku (4), lisaksi 6 ja 2",
              //   5 1 1 2 5  -> "3kaksi paria (5, 1), lisaksi 2"
              //   3 1 6 4 3  -> "2pari (3), lisaksi 6, 4, 1"
              //   2 6 1 4 5  -> "1ei yhdistelmaa (6), lisaksi 5, 4, 2, 1"
              // Nämä ovat hyödyllisiä siksi, että niitä voidaan vertailla
              // suoraan, ja mitä myöhemmin merkkijono on aakkosissa,
              // sitä parempi yhdistelmä se on.
              tulkinta.insert(0, arvopari.second);
          }
       }
    }

    ostringstream tulosvirta{""};

    if ( tulkinnat.at(0) > tulkinnat.at(1) ) {
        tulosvirta << "pelaaja 1 on voittoisa!";
    } else if ( tulkinnat.at(1) > tulkinnat.at(0) ) {
        tulosvirta << "pelaaja 2 on voittoisa!";
    } else {
        tulosvirta << "tulos on tasapeli";
    }

    return tulosvirta.str();
}
