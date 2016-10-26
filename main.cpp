#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

ifstream fin("/Users/liuyi103/ClionProjects/nvtest/input.txt");  // Need to modify to adapt working environment.

int main() {
    int n;  // the number of homes
    int maxCandy; // the maximum number for candies.
    vector<int> candies;  // the candies in each home.
    fin >> n >> maxCandy;
    for(int i = 0; i < maxCandy; i ++) {
        int candy;
        fin >> candy;
        candies.push_back(candy);
    }
    int best = -1;  // the best result until now, -1 means infeasible
    int st = 0, en = 0;  // the start and end points.
    int sum = 0;  // the sum between st (inclusive) and en (exclusive).
    int bestSt, bestEn; // the solution corresponding to best

    while (en <= n) {
        while (sum > maxCandy) {
            sum -= candies[st];
            st ++;
        }
        if (st < en && sum > best) {
            best = sum;
            bestSt = st;
            bestEn = en;
        }
        if (en == n) {
            break;
        }
        sum += candies[en];
        en ++;
    }

    if (best == -1) {
        cout << "Don't go here" << endl;
    } else {
        cout << bestSt + 1 << " " << bestEn << endl;
    }
    return 0;
}