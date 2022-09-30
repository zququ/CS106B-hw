#include "console.h"
#include "map.h"
#include "set.h"
#include "simpio.h"
#include "vector.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    Vector<string> wordlist;
    Map<string, int> wordfrequency;

    while (true) {
        string word = getLine("Enter your word: ");
        if (word == "")
            break;
        wordlist.add(word);
        wordfrequency[word]++;
    }

    cout << wordlist << endl;
    cout << wordfrequency << endl;

    return 0;
}
