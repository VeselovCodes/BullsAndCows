#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iostream>

struct Case {
    int cows;
    int bulls;
    int n;
    int n1;
    int n2;
    int n3;
    int n4;
};

class Checker {
public:
    void addCheck(Case c) {
        checks_.push_back(c);
    }

    bool check(int n) const {
        int n1 = n / 1000;
        int n2 = (n / 100) % 10;
        int n3 = (n / 10) % 10;
        int n4 = n % 10;

        for (const auto& c : checks_) {
            int bulls = (c.n1 == n1) +
                        (c.n2 == n2) +
                        (c.n3 == n3) +
                        (c.n4 == n4);
            int cows = ((c.n1 == n2) || (c.n1 == n3) || (c.n1 == n4)) +
                       ((c.n2 == n1) || (c.n2 == n3) || (c.n2 == n4)) +
                       ((c.n3 == n1) || (c.n3 == n2) || (c.n3 == n4)) +
                       ((c.n4 == n1) || (c.n4 == n2) || (c.n4 == n3));
            if (bulls != c.bulls || cows != c.cows)
                return false;
        }
        return true;
    }
    std::vector<Case> checks_;
};

int makeDecision(const std::vector<int>& cases, const Checker& checker) {
    auto it = checker.checks_.begin();
    int newC;
    while (it != checker.checks_.end())
    {
        newC = cases[rand() % cases.size()];
        it = std::find_if(checker.checks_.begin(), checker.checks_.end(), [newC](Case cc) {
            return cc.n == newC;
        });
    }
    if (checker.checks_.size() == 0) {
        newC = 1234; 
    }
    std::cout<<newC<<std::endl;
    return newC;
}

void getAnswer(Case& c) {
    std::cin>>c.bulls>>c.cows;
}

int main() {
    std::vector<int> remainCases;
    for (int i = 1; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (j == i)
                continue;
            for (int k = 0; k < 10; ++k) {
                if (k == i || k == j)
                    continue;
                for (int l = 0; l < 10; ++l) {
                    if (l == i || l == j || l ==k)
                        continue;
                    
                    remainCases.push_back(i * 1000 + j * 100 + k * 10 + l);
                }
            }
        }
    }

    Checker checker;
    bool solved = false;
    while(!solved) {
        Case c;
        c.n = makeDecision(remainCases, checker);
        c.n1 = c.n / 1000;
        c.n2 = (c.n / 100) % 10;
        c.n3 = (c.n / 10) % 10;
        c.n4 = c.n % 10;
        getAnswer(c);
        if (c.bulls == 4) {
            std::cout<<"Answer: "<<remainCases.back()<<std::endl;
            std::cin>>c.n;
            break;
        }

        checker.addCheck(c);

        for (auto it = remainCases.begin(); it != remainCases.end(); ) {
            if (!checker.check(*it)) {
                it = remainCases.erase(it);
            } else {
                ++it;
            }
        }
    }
    return 0;
}