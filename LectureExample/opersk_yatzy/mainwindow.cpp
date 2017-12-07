#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "functions.hh"

#include <QPixmap>
#include <QLabel>
#include <QCheckBox>

#include <string>
#include <sstream>
#include <vector>
#include <iostream>

#include <unistd.h>  // usleep


using namespace std;


const vector<string> DICEPICTUREFILES{
  "tyhja.png", "1.png", "2.png", "3.png", "4.png", "5.png", "6.png",
};

const int NOBODY{0};
const int PLAYER_1{1};
const int PLAYER_2{2};

const int ROLL_INITIAL_NUMBER{3};


Mainwindow::Mainwindow(QWidget *parent) :
    QWidget(parent), ui(new Ui::Mainwindow) {

    ui->setupUi(this);

    diceLabels = {
        ui->dice1Label, ui->dice2Label, ui->dice3Label,
        ui->dice4Label, ui->dice5Label,
    };

    lockingCheckBoxes = {
        ui->locking1CheckBox, ui->locking2CheckBox,
        ui->locking3CheckBox, ui->locking4CheckBox,
        ui->locking5CheckBox,
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

    for ( auto file_name : DICEPICTUREFILES ) {
        QPixmap picture{ (":/noppakuvat/"+file_name).c_str() };
        dicepictures.push_back(picture);
    }

    initialize_new_game();

    connect(ui->newgameButton, SIGNAL(clicked()),
            this, SLOT(initialize_new_game()));
    connect(ui->rollButton, SIGNAL(clicked()),
            this, SLOT(roll()));
    connect(ui->transferturnButton, SIGNAL(clicked()),
            this, SLOT(give_turn()));
}


Mainwindow::~Mainwindow() {
    delete ui;
}


void Mainwindow::initialize_new_game() {
    ui->player1Label->setText("nothing");
    ui->player2Label->setText("nothing");

    enable_roll();
    disable_turn_transfer();
    empty_dices();
    remove_lockings();
    disable_lockings();

    player_1_pointValues = { 0, 0, 0, 0, 0 };
    player_2_pointValues = { 0, 0, 0, 0, 0 };

    gameturn = PLAYER_1;
    rolls_left = ROLL_INITIAL_NUMBER;
    update_guide(gameturn, rolls_left);
}


void Mainwindow::empty_dices() {
    for ( auto label : diceLabels ) {
        label->setPixmap(dicepictures.at(0));
    }
}


void Mainwindow::enable_roll() {
    ui->rollButton->setEnabled(true);
}


void Mainwindow::disable_roll() {
    ui->rollButton->setEnabled(false);
}


void Mainwindow::enable_turn_transfer() {
    ui->transferturnButton->setEnabled(true);
}


void Mainwindow::disable_turn_transfer() {
    ui->transferturnButton->setEnabled(false);
}


void Mainwindow::enable_lockings() {
    for ( auto checkbox : lockingCheckBoxes ) {
        checkbox->setEnabled(true);
    }
}


void Mainwindow::disable_lockings() {
    for ( auto checkbox : lockingCheckBoxes ) {
        checkbox->setEnabled(false);
    }
}


void Mainwindow::remove_lockings() {
    for ( auto checkbox : lockingCheckBoxes ) {
        checkbox->setCheckState(Qt::Unchecked);
    }
}


void Mainwindow::roll() {
    if ( gameturn == NOBODY ) {
        return;
    }

    disable_roll();

    for ( int animatetime{0}; animatetime < 10; ++animatetime ) {
        vector<QLabel*>::size_type dice{ 0 };

        while ( dice < diceLabels.size() ) {

           if ( lockingCheckBoxes.at(dice)->checkState() != Qt::Checked ) {

               int pointValue{ roll_dice() };

               diceLabels.at(dice)->setPixmap(dicepictures.at(pointValue));

               // Next two lines update the change in the previous line (label picture)
               // in UI.
               // Normally update would happen only when returning from the slot method
               // to the event loop (then the animation would not work).
               diceLabels.at(dice)->update();
               qApp->processEvents();

               if ( gameturn == 1 ) {
                   player_1_pointValues.at(dice) = pointValue;
               } else {
                   player_2_pointValues.at(dice) = pointValue;
               }

               usleep(10000);  // Stop for 10000 microseconds (1/100s)
           }

           ++dice;
        }
    }

    enable_roll();

    --rolls_left;

    enable_turn_transfer();
    enable_lockings();

    if ( gameturn == PLAYER_1 ) {
        report_player_status(PLAYER_1);

        if ( rolls_left == 0 ) {

            disable_roll();
            remove_lockings();
            disable_lockings();

            ui->infoLabel->setText("Turn of player 1 has ended!");

        } else {

            update_guide(gameturn, rolls_left);
        }

    } else {

        report_player_status(PLAYER_2);

        if ( rolls_left == 0 ) {

            disable_roll();
            disable_turn_transfer();

            report_player_status(PLAYER_1);
            report_winner();

        } else {

            update_guide(gameturn, rolls_left);
        }
    }
}


void Mainwindow::give_turn() {
    if ( gameturn == NOBODY ) {
        return;

    } else if ( gameturn == PLAYER_1 ) {
        gameturn = PLAYER_2;
        rolls_left = ROLL_INITIAL_NUMBER;

        empty_dices();
        ui->player1Label->setText("[HIDDEN]");

        enable_roll();
        disable_turn_transfer();
        remove_lockings();
        disable_lockings();

        update_guide(gameturn, rolls_left);

    } else {
        gameturn = NOBODY;

        disable_roll();
        disable_turn_transfer();
        remove_lockings();
        disable_lockings();

        report_player_status(PLAYER_1);
        report_winner();
    }
}


void Mainwindow::report_player_status(int player) {
    string textual_description{""};

    if ( player == 1 ) {
        textual_description = construe_result(player_1_pointValues);
        ui->player1Label->setText(textual_description.c_str());

    } else {

        textual_description = construe_result(player_2_pointValues);
        ui->player2Label->setText(textual_description.c_str());
    }
}


void Mainwindow::update_guide(int player, int rolls_left) {
    ostringstream guidestream{""};
    guidestream << "Player's' " << player << " turn, "
              << rolls_left << " trials left!";

    ui->infoLabel->setText(guidestream.str().c_str());
}


void Mainwindow::report_winner() {
    string winner{ decide_winner(player_1_pointValues,
                                       player_2_pointValues) };

    ui->infoLabel->setText(winner.c_str());
}
