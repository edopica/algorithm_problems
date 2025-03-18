#include <iostream>
#include <unordered_map>

using namespace std;

unordered_map<char, char> opposite = { {'1','0'}, {'0','1'} };

string odd_case(int feature_count[], int n_features, int threshold) {
    string player = "";
    for(int i=0; i<n_features; i++) {
        if (feature_count[i] > threshold) {
            player += "0";
        }
        else {
            player += "1";
        }
    }

    return player;
}

string even_case(int feature_count[], int n_features, int threshold) {
    string player = "";
    bool turn = 1;

    for(int i=0; i<n_features; i++) {
        if (feature_count[i] > threshold) {
            player += "0";
        }
        else if(feature_count[i] == threshold) {
            if (turn)
                player += "1";
            else
                player += "0";
            turn = ! turn;
        }
        else {
            player += "1";
        }
    }

    return player;
}

/**
 * @brief counts how many players are equal to a particular one
 *
 *
 */
int get_score(string player, int* players, int n_players, int n_features) {
    int score = 0;
    int features[n_features], i, h, f;
    bool check;

    for(i=0; i<n_features; i++) {
        features[i] = (player[i] - '0');
    }

    for(i=0; i<n_players; i++) {
        check = true;
        for(h=0; h<n_features; h++) {
            f = *((players + i * n_features) + h);
            if(features[h] != f) {
                check = false;
                break;
            }
        }
        if(check)
            score += 1;
    }

    return score;
}

int main()
{
    int i, h, n_players, n_features;
    string player, o1, o2;

    cin >> n_players;
    cin >> n_features;

    int players[n_players][n_features];

    int feature_count[n_features] = {0};
    int threshold = n_players / 2;
    // Count how many times each feature was chosen
    for(i=0; i<n_players; i++) {
        cin >> player;
        for(h=0; h<n_features; h++) {
            if(player[h] == '1') {
                feature_count[h] += 1;
                players[i][h] = 1;
            }
            else {
                players[i][h] = 0;
            }        }
    }

    //cout << "***********" << endl;

    // For each feature, choose to use it or not based on what
    // more than half of the players did.
    /*
    if((n_players % 2) == 0) {
        player = even_case(feature_count, n_features, threshold);
        cout << player << " - score: " << get_score(player, &players[0][0], n_players, n_features) << endl;
    }
    else
        cout << odd_case(feature_count, n_features, threshold);
    player = odd_case(feature_count, n_features, threshold);
    cout << player << " - score: " << get_score(player, &players[0][0], n_players, n_features) << endl;
    //cout << player;
    */
    o1 = odd_case(feature_count, n_features, threshold);
    //cout << "O1: " << o1 << endl;
    o2 = even_case(feature_count, n_features, threshold);
    //cout << "O2: " << o2 << endl;

    if( get_score(o1, &players[0][0], n_players, n_features) > get_score(o2, &players[0][0], n_players, n_features))
        cout << o2;
    else
        cout << o1;


    return 0;
}
