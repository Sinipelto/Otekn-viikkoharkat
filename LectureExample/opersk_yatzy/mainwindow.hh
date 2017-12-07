#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QCheckBox>

#include <vector>

using namespace std;

namespace Ui {
class Mainwindow;
}

class Mainwindow : public QWidget
{
    Q_OBJECT

public:
    explicit Mainwindow(QWidget *parent = 0);
    ~Mainwindow();

    void enable_roll();
    void disable_roll();
    void enable_turn_transfer();
    void disable_turn_transfer();
    void enable_lockings();
    void disable_lockings();
    void remove_lockings();

    void empty_dices();
    void report_player_status(int player);
    void update_guide(int player, int rolls_left);
    void report_winner();

public slots:
    void initialize_new_game();
    void roll();
    void give_turn();

private:
    Ui::Mainwindow *ui;

    vector<QPixmap>    dicepictures;
    vector<QLabel*>    diceLabels;
    vector<QCheckBox*> lockingCheckBoxes;

    vector<int> player_1_pointValues;
    vector<int> player_2_pointValues;

    int gameturn;
    int rolls_left;
};

#endif // MAINWINDOW_HH
