#include "paaikkuna.hh"
#include "ui_paaikkuna.h"
#include "apufunktiot.hh"

#include <QPixmap>
#include <QLabel>
#include <QCheckBox>

#include <string>
#include <sstream>
#include <vector>
#include <iostream>

#include <unistd.h>  // usleep


using namespace std;


const vector<string> NOPPAKUVATIEDOSTOT{
  "tyhja.png", "1.png", "2.png", "3.png", "4.png", "5.png", "6.png",
};

const int EI_KUKAAN{0};
const int PELAAJA_1{1};
const int PELAAJA_2{2};

const int HEITTOJEN_ALKUMAARA{3};


Paaikkuna::Paaikkuna(QWidget *parent) :
    QWidget(parent), ui(new Ui::Paaikkuna) {

    ui->setupUi(this);

    noppaLabelit = {
        ui->noppa1Label, ui->noppa2Label, ui->noppa3Label,
        ui->noppa4Label, ui->noppa5Label,
    };

    lukituksetCheckBoxit = {
        ui->lukitus1CheckBox, ui->lukitus2CheckBox,
        ui->lukitus3CheckBox, ui->lukitus4CheckBox,
        ui->lukitus5CheckBox,
    };

//    for (int i=1; i<=5; ++i)
//    {
//        QVBoxLayout* noppalayout = new QVBoxLayout(this);
//        QLabel* label = new QLabel();
//        label->setScaledContents(true);
//        QCheckBox* cbox = new QCheckBox();
//        noppalayout->addWidget(label);
//        noppalayout->addWidget(cbox);
//        ui->noppaLayout->addLayout(noppalayout);
//        noppaLabelit.push_back(label);
//        lukituksetCheckBoxit.push_back(cbox);
//    }

    for ( auto tiedoston_nimi : NOPPAKUVATIEDOSTOT ) {
        QPixmap kuva{ (":/noppakuvat/"+tiedoston_nimi).c_str() };
        noppakuvat.push_back(kuva);
    }

    alusta_uusi_peli();

    connect(ui->uusipeliButton, SIGNAL(clicked()),
            this, SLOT(alusta_uusi_peli()));
    connect(ui->heitaButton, SIGNAL(clicked()),
            this, SLOT(heita()));
    connect(ui->luovutavuoroButton, SIGNAL(clicked()),
            this, SLOT(anna_vuoro()));
}


Paaikkuna::~Paaikkuna() {
    delete ui;
}


void Paaikkuna::alusta_uusi_peli() {
    ui->pelaaja1Label->setText("ei yhdistelmaa");
    ui->pelaaja2Label->setText("ei yhdistelmaa");

    salli_heitto();
    esta_vuoron_luovutus();
    tyhjenna_nopat();
    poista_lukitukset();
    esta_lukitukset();

    pelaajan_1_silmaluvut = { 0, 0, 0, 0, 0 };
    pelaajan_2_silmaluvut = { 0, 0, 0, 0, 0 };

    pelivuoro = PELAAJA_1;
    heittoja_jaljella = HEITTOJEN_ALKUMAARA;
    paivita_ohje(pelivuoro, heittoja_jaljella);
}


void Paaikkuna::tyhjenna_nopat() {
    for ( auto label : noppaLabelit ) {
        label->setPixmap(noppakuvat.at(0));
    }
}


void Paaikkuna::salli_heitto() {
    ui->heitaButton->setEnabled(true);
}


void Paaikkuna::esta_heitto() {
    ui->heitaButton->setEnabled(false);
}


void Paaikkuna::salli_vuoron_luovutus() {
    ui->luovutavuoroButton->setEnabled(true);
}


void Paaikkuna::esta_vuoron_luovutus() {
    ui->luovutavuoroButton->setEnabled(false);
}


void Paaikkuna::salli_lukitukset() {
    for ( auto checkbox : lukituksetCheckBoxit ) {
        checkbox->setEnabled(true);
    }
}


void Paaikkuna::esta_lukitukset() {
    for ( auto checkbox : lukituksetCheckBoxit ) {
        checkbox->setEnabled(false);
    }
}


void Paaikkuna::poista_lukitukset() {
    for ( auto checkbox : lukituksetCheckBoxit ) {
        checkbox->setCheckState(Qt::Unchecked);
    }
}


void Paaikkuna::heita() {
    if ( pelivuoro == EI_KUKAAN ) {
        return;
    }

    esta_heitto();

    for ( int animointikerta{0}; animointikerta < 10; ++animointikerta ) {
        vector<QLabel*>::size_type noppa{ 0 };

        while ( noppa < noppaLabelit.size() ) {

           if ( lukituksetCheckBoxit.at(noppa)->checkState() != Qt::Checked ) {

               int silmaluku{ heita_arpakuutiota() };

               noppaLabelit.at(noppa)->setPixmap(noppakuvat.at(silmaluku));

               // Seuraavat kaksi riviä päivittävät edellisellä rivillä
               // tehdyn muutoksen (labelin kuvan) käyttöliittymässä.
               // Normaalisti päivitys tapahtuisi vasta, kun slot-metodista
               // palataan tapahtumasilmukkaan (silloin animaatio ei toimisi).
               noppaLabelit.at(noppa)->update();
               qApp->processEvents();

               if ( pelivuoro == 1 ) {
                   pelaajan_1_silmaluvut.at(noppa) = silmaluku;
               } else {
                   pelaajan_2_silmaluvut.at(noppa) = silmaluku;
               }

               usleep(10000);  // Pysähdytaan 10000 mikrosekunniksi (1/100s)
           }

           ++noppa;
        }
    }

    salli_heitto();

    --heittoja_jaljella;

    salli_vuoron_luovutus();
    salli_lukitukset();

    if ( pelivuoro == PELAAJA_1 ) {
        raportoi_pelaajan_tilanne(PELAAJA_1);

        if ( heittoja_jaljella == 0 ) {

            esta_heitto();
            poista_lukitukset();
            esta_lukitukset();

            ui->infoLabel->setText("Pelaajan 1 vuoro paattynyt!");

        } else {

            paivita_ohje(pelivuoro, heittoja_jaljella);
        }

    } else {

        raportoi_pelaajan_tilanne(PELAAJA_2);

        if ( heittoja_jaljella == 0 ) {

            esta_heitto();
            esta_vuoron_luovutus();

            raportoi_pelaajan_tilanne(PELAAJA_1);
            raportoi_voittaja();

        } else {

            paivita_ohje(pelivuoro, heittoja_jaljella);
        }
    }
}


void Paaikkuna::anna_vuoro() {
    if ( pelivuoro == EI_KUKAAN ) {
        return;

    } else if ( pelivuoro == PELAAJA_1 ) {
        pelivuoro = PELAAJA_2;
        heittoja_jaljella = HEITTOJEN_ALKUMAARA;

        tyhjenna_nopat();
        ui->pelaaja1Label->setText("[PIILOTETTU]");

        salli_heitto();
        esta_vuoron_luovutus();
        poista_lukitukset();
        esta_lukitukset();

        paivita_ohje(pelivuoro, heittoja_jaljella);

    } else {
        pelivuoro = EI_KUKAAN;

        esta_heitto();
        esta_vuoron_luovutus();
        poista_lukitukset();
        esta_lukitukset();

        raportoi_pelaajan_tilanne(PELAAJA_1);
        raportoi_voittaja();
    }
}


void Paaikkuna::raportoi_pelaajan_tilanne(int pelaaja) {
    string sanallinen_kuvaus{""};

    if ( pelaaja == 1 ) {
        sanallinen_kuvaus = tulkitse_tulos(pelaajan_1_silmaluvut);
        ui->pelaaja1Label->setText(sanallinen_kuvaus.c_str());

    } else {

        sanallinen_kuvaus = tulkitse_tulos(pelaajan_2_silmaluvut);
        ui->pelaaja2Label->setText(sanallinen_kuvaus.c_str());
    }
}


void Paaikkuna::paivita_ohje(int pelaaja, int heittoja_jaljella) {
    ostringstream ohjevirta{""};
    ohjevirta << "Pelaajan " << pelaaja << " pelivuoro, "
              << heittoja_jaljella << " yritysta jaljella!";

    ui->infoLabel->setText(ohjevirta.str().c_str());
}


void Paaikkuna::raportoi_voittaja() {
    string voittaja{ paattele_voittaja(pelaajan_1_silmaluvut,
                                       pelaajan_2_silmaluvut) };

    ui->infoLabel->setText(voittaja.c_str());
}
