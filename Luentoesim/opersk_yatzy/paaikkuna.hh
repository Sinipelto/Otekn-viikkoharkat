#ifndef PAAIKKUNA_HH
#define PAAIKKUNA_HH

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QCheckBox>

#include <vector>

using namespace std;

namespace Ui {
class Paaikkuna;
}

class Paaikkuna : public QWidget
{
    Q_OBJECT

public:
    explicit Paaikkuna(QWidget *parent = 0);
    ~Paaikkuna();

    void salli_heitto();
    void esta_heitto();
    void salli_vuoron_luovutus();
    void esta_vuoron_luovutus();
    void salli_lukitukset();
    void esta_lukitukset();
    void poista_lukitukset();

    void tyhjenna_nopat();
    void raportoi_pelaajan_tilanne(int pelaaja);
    void paivita_ohje(int pelaaja, int heittoja_jaljella);
    void raportoi_voittaja();

public slots:
    void alusta_uusi_peli();
    void heita();
    void anna_vuoro();

private:
    Ui::Paaikkuna *ui;

    vector<QPixmap>    noppakuvat;
    vector<QLabel*>    noppaLabelit;
    vector<QCheckBox*> lukituksetCheckBoxit;

    vector<int> pelaajan_1_silmaluvut;
    vector<int> pelaajan_2_silmaluvut;

    int pelivuoro;
    int heittoja_jaljella;
};

#endif // PAAIKKUNA_HH
