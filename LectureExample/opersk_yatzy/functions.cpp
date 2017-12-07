#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>    // ostringstream type
#include <random>     // random numbers of roll_dices function
#include <ctime>      // initialization of the random number generator
using namespace std;


const string YATZY              {"yatzy"};
const string FOUR_OF_A_KIND     {"four of a kind"};
const string FULL_HOUSE          {"full house"};
const string STRAIGHT           {"straight"};
const string THREE_OF_A_KIND    {"three of a kind"};
const string TWO_PAIRS          {"two pairs"};
const string PAIR               {"pair"};
const string NOTHING            {"nothing"};


//-----------------------------------------------------------------------------
// Private functions of the module

namespace {


//-----------------------------------------------------------------------------
// Functions recognizing results

bool is_yatzy(const map<int, int>& statistics) {
    if ( statistics.size() == 1 ) {
        return true;
    } else {
        return false;
    }
}

bool is_four_of_a_kind(const map<int, int>& statistics) {
    if ( statistics.size() == 2 ) {
        int either_count{ statistics.begin()->second };
        if ( either_count == 1 or either_count == 4 ) {
            return true;
        }
    }

    return false;
}

bool is_full_house(const map<int, int>& statistics) {
    if ( statistics.size() == 2 and not is_four_of_a_kind(statistics) ) {
        return true;
    } else {
        return false;
    }
}

bool is_straight(const map<int, int>& statistics) {
    if ( statistics.size() == 5
           and (statistics.find(1) == statistics.end()
                  or statistics.find(6) == statistics.end()) ) {
            return true;
    } else {
        return false;
    }
}

bool is_three_of_a_kind(const map<int, int>& statistics) {
    if ( statistics.size() == 3 ) {
        for ( auto infopair : statistics ) {
            if ( infopair.second == 3 ) {
                return true;
            }
        }
    }

    return false;
}

bool is_two_pairs(const map<int, int>& statistics) {
    if ( statistics.size() == 3 and not is_three_of_a_kind(statistics) ) {
        return true;
    } else {
        return false;
    }
}

bool is_pair(const map<int, int>& statistics) {
    if ( statistics.size() == 4 ) {
        return true;
    } else {
        return false;
    }
}

bool is_six(const map<int, int>& statistics) {
    if ( statistics.size() == 5 and not is_straight(statistics) ) {
        return true;
    } else {
        return false;
    }
}


//-----------------------------------------------------------------------------
// Functions giving a textual representation for the result

string format_result_yatzy(const map<int, int>& statistics) {
    ostringstream outputstream{""};

    outputstream << YATZY << " (" << statistics.begin()->second << ")";

    return outputstream.str();
}

string format_result_four_of_a_kind(const map<int, int>& statistics) {
    ostringstream outputstream{""};

    int what_four{0};
    int what_one{0};

    for ( auto pair : statistics ) {
        if ( pair.second == 4 ) {
            what_four = pair.first;
        } else {
            what_one = pair.first;
        }
    }

    outputstream << FOUR_OF_A_KIND << " (" << what_four << "), in addition " << what_one;

    return outputstream.str();
}

string format_result_full_house(const map<int, int>& statistics) {
    ostringstream outputstream{""};

    int what_three{0};
    int what_two{0};

    for ( auto pair : statistics ) {
        if ( pair.second == 3 ) {
            what_three = pair.first;
        } else {
            what_two = pair.first;
        }
    }

    outputstream << FULL_HOUSE << " (" << what_three << ", " << what_two << ")";

    return outputstream.str();
}

string format_result_straight(const map<int, int>& statistics) {
    ostringstream outputstream{""};

    outputstream << "straight (";

    if ( statistics.find(1) == statistics.end() ) {
        outputstream << 6;
    } else {
        outputstream << 1;
    }

    outputstream << ")";

    return outputstream.str();
}

string format_result_three_of_a_kind(const map<int, int>& statistics) {
    ostringstream outputstream{""};

    int what_three{0};
    vector<int> what_one{};

    for ( auto pair : statistics ) {
        if ( pair.second == 3 ) {
            what_three = pair.first;
        } else {
            what_one.push_back(pair.first);
        }
    }

    sort(what_one.begin(), what_one.end());

    outputstream << THREE_OF_A_KIND << " (" << what_three << "), in addition "
               << what_one.at(1) << " ja " << what_one.at(0);

    return outputstream.str();
}

string format_result_two_pairs(const map<int, int>& statistics) {
    ostringstream outputstream{""};

    vector<int> what_two{};
    int what_one{0};

    for ( auto pair : statistics ) {
        if ( pair.second == 1 ) {
            what_one = pair.first;
        } else {
            what_two.push_back(pair.first);
        }
    }

    sort(what_two.begin(), what_two.end());

    outputstream << TWO_PAIRS << " ("
               << what_two.at(1) << ", " << what_two.at(0)
               << "), in addition " << what_one;

    return outputstream.str();
}

string format_result_pair(const map<int, int>& statistics) {
    ostringstream outputstream{""};

    int what_two{0};
    vector<int> what_one{};

    for ( auto pair : statistics ) {
        if ( pair.second == 2 ) {
            what_two = pair.first;
        } else {
            what_one.push_back(pair.first);
        }
    }

    sort(what_one.begin(), what_one.end());

    outputstream << PAIR << " (" << what_two << "), in addition "
               << what_one.at(2) << ", "
               << what_one.at(1) << ", "
               << what_one.at(0);

    return outputstream.str();
}

string format_result_six(const map<int, int>& statistics) {
    ostringstream outputstream{""};

    vector<int> pointValues;

    for ( auto pair : statistics ) {
        pointValues.push_back(pair.first);
    }

    // call of function sort not needed, why?
    // sort(pointValues.begin(), pointValues.end());

    outputstream << NOTHING << " (" << pointValues.at(4) << "), in addition ";
    pointValues.pop_back();
    reverse(pointValues.begin(), pointValues.end());

    for ( int silmaluku : pointValues ) {
        outputstream << silmaluku << ", ";
    }

    return outputstream.str();
}

} // end of namespace


//-----------------------------------------------------------------------------
// Public functions

int roll_dice() {
    static unsigned int seed{static_cast<unsigned int>(time(0))};
    static default_random_engine engine{seed};
    static uniform_int_distribution<int> generator{1, 6};

    return generator(engine);
}

string construe_result(const vector<int>& pointValues) {
    // The purpose of this function is to form and return textual construction for
    // the values in <<pointValues>> vector.
    // Format could be e.g.:
    //   5 5 5 5 5  -> "yatzy (5)"
    //   3 2 3 3 3  -> "four of a kind (3), in addition 2"
    //   5 1 1 5 5  -> "full house (5, 1)"
    //   4 2 6 5 3  -> "straight (6)"
    //   4 6 4 4 2  -> "three of a kind (4), in addition 6 ja 2",
    //   5 1 1 2 5  -> "two pairs (5, 1), in addition 2"
    //   3 1 6 4 3  -> "pair (3), in addition 6, 4, 1"
    //   2 6 1 4 5  -> "nothing (6), in addition 5, 4, 2, 1"
    // or something similar.

    // map<pointValue, how_many>
    map<int, int> pointValueStatistics;

    for ( int pointValue : pointValues ) {
        if ( pointValueStatistics.find(pointValue) == pointValueStatistics.end() ) {
            pointValueStatistics.insert( { pointValue, 1 } );
        } else {
            ++pointValueStatistics.at(pointValue);
        }
    }

    if ( is_yatzy(pointValueStatistics) ) {
        return format_result_yatzy(pointValueStatistics);

    } else if ( is_four_of_a_kind(pointValueStatistics) ) {
        return format_result_four_of_a_kind(pointValueStatistics);

    } else if ( is_full_house(pointValueStatistics) ) {
        return format_result_full_house(pointValueStatistics);

    } else if ( is_straight(pointValueStatistics) ) {
        return format_result_straight(pointValueStatistics);

    } else if ( is_three_of_a_kind(pointValueStatistics) ) {
        return format_result_three_of_a_kind(pointValueStatistics);

    } else if ( is_two_pairs(pointValueStatistics) ) {
        return format_result_two_pairs(pointValueStatistics);

    } else if ( is_pair(pointValueStatistics) ) {
        return format_result_pair(pointValueStatistics);

    } else if ( is_six(pointValueStatistics) ) {
        return format_result_six(pointValueStatistics);

    } else {

        return "This is not happening...";
    }
}


string decide_winner(const vector<int>& player_1_pointValues,
                         const vector<int>& player_2_pointValues) {
    // This function forms and returns some of the strings:
    //   "player 1 is the winner!"
    //   "player 2 is the winner!"
    //   "result is tie!"

    const map<string, string> values{
        { YATZY,            "8" },
        { FOUR_OF_A_KIND,   "7" },
        { FULL_HOUSE,       "6" },
        { STRAIGHT,         "5" },
        { THREE_OF_A_KIND,  "4" },
        { TWO_PAIRS,        "3" },
        { PAIR,             "2" },
        { NOTHING,          "1" },
    };

    vector<string> interpretations {
        construe_result(player_1_pointValues),
        construe_result(player_2_pointValues),
    };


    for ( string& interpreation : interpretations ) {
       for ( auto valuePair : values ) {
          if ( interpreation.substr(0, valuePair.first.length()) == valuePair.first ) {
              // Results are strings of the form:
              //   5 5 5 5 5  -> "8yatzy (5)"
              //   3 2 3 3 3  -> "7four of a kind (3), in addition 2"
              //   5 1 1 5 5  -> "6full house (5, 1)"
              //   4 2 6 5 3  -> "5straight (6)"
              //   4 6 4 4 2  -> "4three of a kind (4), in addition 6 ja 2",
              //   5 1 1 2 5  -> "3two pairs (5, 1), in addition 2"
              //   3 1 6 4 3  -> "2pair (3), in addition 6, 4, 1"
              //   2 6 1 4 5  -> "1nothing (6), in addition 5, 4, 2, 1"
              // These are useful, since they can be compared directly,
              // and the later the string is in alphabethical order,
              // the better its value is.
              interpreation.insert(0, valuePair.second);
          }
       }
    }

    ostringstream outputstream{""};

    if ( interpretations.at(0) > interpretations.at(1) ) {
        outputstream << "player 1 is the winner!";
    } else if ( interpretations.at(1) > interpretations.at(0) ) {
        outputstream << "player 2 is the winner!";
    } else {
        outputstream << "result is tie";
    }

    return outputstream.str();
}
