#ifndef FUNCTIONS_HH
#define FUNCTIONS_HH
#include <string>
#include <vector>

using namespace std;

int roll_dice();
string construe_result(const vector<int>& pointValues);
string decide_winner(const vector<int>& player_1_pointValues,
                         const vector<int>& player_2_pointValues);

#endif // FUNCTIONS_HH
