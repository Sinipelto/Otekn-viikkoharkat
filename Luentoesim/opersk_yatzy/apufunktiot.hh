#ifndef APUFUNKTIOT_HH
#define APUFUNKTIOT_HH

#include <string>
#include <vector>

using namespace std;

int heita_arpakuutiota();
string tulkitse_tulos(const vector<int>& silmaluvut);
string paattele_voittaja(const vector<int>& pelaajan_1_silmaluvut,
                         const vector<int>& pelaajan_2_silmaluvut);

#endif // APUFUNKTIOT_HH
