/**
 * Basically, to make it parellel, my idea is as follows.
 * First, find some break points, the sum between each two break points is no more the maximum candy.
 * Then, we have the final answer can't contains two break points.
 * So, we can run the algorithm in main parellelly on joint intervals.
 */
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

ifstream fin("/Users/liuyi103/ClionProjects/nvtest/input.txt");  // Need to modify to adapt working environment.

int main() {
    int n;  // the number of homes
    int maxCandy; // the maximum number for candies.
    vector<int> candies;  // the candies in each home.
    vector<int> breakpoints{0};
    int blockSum = 0;
    fin >> n >> maxCandy;
    if (n == 0) {
        cout << "Don't go here" << endl;
        return 0;
    }
    for(int i = 0; i < maxCandy; i ++) {
        int candy;
        fin >> candy;
        blockSum += candy;
        if (blockSum >= maxCandy) {
            breakpoints.push_back(i+1);
            blockSum = 0;
        }
        candies.push_back(candy);
    }
    breakpoints.push_back(n);

    // the total sum is smaller than the max candies.
    if (breakpoints.size() == 2) {
        cout << 1 << " " << n << endl;
        return 0;
    }

    int finalAns = -1, finalSt, finalEn;

    #pragma omp parallel for
    for (int k = 0; k < breakpoints.size() - 2; k ++) {
        int best = -1;  // the best result until now, -1 means infeasible
        int st = 0, en = 0;  // the start and end points.
        int sum = 0;  // the sum between st (inclusive) and en (exclusive).
        int bestSt, bestEn; // the solution corresponding to best

        while (en <= n) {
            while (sum > maxCandy) {
                sum -= candies[st];
                st++;
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
            en++;
        }
        if (best > finalAns) {
            finalAns = best;
            finalSt = bestSt;
            finalEn = bestEn;
        }
    }

    if (finalAns == -1) {
        cout << "Don't go here" << endl;
    } else {
        cout << finalSt + 1 << " " << finalEn << endl;
    }
    return 0;
}
