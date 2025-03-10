/**
 * TODO: write doc and comments
 *
 *
 */

#include <iostream>
#include <stack>
#include <unordered_map>

using namespace std;

// Define an unordered_map that associates each bracket with its closure
std::unordered_map<char, char> bracketPairs = {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'},
};

char l_brackets[3] = {'(', '[', '{'};
char r_brackets[3] = {')',']','}'};

bool is_r_bracket(char bracket) {
    for(int i=0; i<3; i++) {
        if(bracket == r_brackets[i])
            return true;
    }

    return false;
}

string solve_case(string s) {
    stack<char> brackets;

    for(int i=0; i<s.size(); i++) {
        if(brackets.empty()) {
            brackets.push(s[i]);
            continue;
        }

        if(s[i] == bracketPairs[brackets.top()]) {
            brackets.pop();
        }
        else {
            brackets.push(s[i]);
        }
    }

    if (brackets.empty())
        return "YES";

    string completing_sequence = "";
    char top;

    while (! brackets.empty()) {
        top = brackets.top();
        //cout << "evaluating " << top << endl;
        if (is_r_bracket(top))
            return "NO";
        completing_sequence += bracketPairs[top];
        //cout << "***ADDED " <<  bracketPairs[top] << " TO COMP****" << endl;
        //cout << "removing " << top << endl;
        brackets.pop();
    }
    //cout << "what remained was: " << remains << endl;
    return completing_sequence;


}


int main()
{
    string line;
    int i,loops;
    cin >> loops;

    string cases[loops];

    for(i=0; i<loops; i++) {
        cin >> line;
        cases[i] = line;
    }

    for(i=0; i<loops; i++) {
        cout << solve_case(cases[i]) << endl;
    }

    return 0;
}
