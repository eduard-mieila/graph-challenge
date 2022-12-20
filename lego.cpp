#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <limits>

#define KMAX 10001

using namespace std;

class Task {
 public:
    void solve() {
        read_input();
        get_result();
        print_output();
    }

 private:
    int n, k, t;
    int max_consecutive = 0, index_max = -1;
    vector<vector<int>> domains;
    vector<int> piecesAvailable;
    bool sums[KMAX];
    void read_input() {
        ifstream fin("lego.in");

        fin >> k >> n >> t;

        // Generare piese ce pot fi folosite
        for (int i = 1; i <= k; i++) {
            piecesAvailable.push_back(i);
        }


        fin.close();
    }

    // Functia de combinari din laboratorul de backtracking
    void getDomains(int step, int stop, vector<int> domain,
                                            vector<int> result) {
        if (step == stop) {
            domains.push_back(result);
            return;
        }

        unsigned i = step > 0 ? result[step - 1] + 1 : 1;
        for (; i <= domain.size(); ++i) {
            result[step] = i;
            getDomains(step + 1, stop, domain, result);
        }
    }

    // Genereaza toate sumele posibile folosind maxim stop numere din domain
    // Pune valoarea true pe pozitia sum din vectorul sums
    void getAllPossibleSums(int step, int stop, int sum, vector<int> domain) {
        if (step == stop) {
            return;
        }

        for (size_t i = 0; i < domain.size(); i++) {
            sums[sum + domain[i]] = true;
            getAllPossibleSums(step + 1, stop, sum + domain[i], domain);
        }
    }

    // Functia returneaza numarul maxim de numere consecutive dintr-un vector
    int getMostConsecutiveSizes(int range) {
        int consecutive = 0, maxConsecutive = -1;
        for (int i = 1; i <= range * t + 1; i++) {
            if (sums[i]) {
                consecutive++;
            } else {
                if (consecutive > maxConsecutive) {
                    maxConsecutive = consecutive;
                }
                consecutive = 0;
            }
        }
        return maxConsecutive;
    }

    void get_result() {
        // Generam toate combinatiile de piese ce pot fi folosite
        // Plecam cu piesa 1 din start in toate domeniile
        vector<int> result(n);
        result[0] = 1;
        getDomains(1, n, piecesAvailable, result);

        for (size_t i = 0; i < domains.size(); i++) {
            // Reseteaza vectorul sums
            memset(sums, false, k * t + 1);

            // Genereaza toate sumele posibile
            getAllPossibleSums(0, t, 0, domains[i]);

            // Verifica daca numarul de sume consecutive din domeniul curent
            // este cel maxim. Actualizeaza daca este necesar.
            int curr_consecutive = getMostConsecutiveSizes(domains[i].back());
            if (curr_consecutive > max_consecutive) {
                index_max = i;
                max_consecutive = curr_consecutive;
            }
        }
    }


    void print_output() {
        ofstream fout("lego.out");

        fout << max_consecutive << endl;
        for (size_t i = 0; i < domains[index_max].size(); i++) {
            fout << domains[index_max][i] << " ";
        }

        fout << endl;

        fout.close();
    }
};

// [ATENTIE] NU modifica functia main!
int main() {
    // * se aloca un obiect Task pe heap
    // (se presupune ca e prea mare pentru a fi alocat pe stiva)
    // * se apeleaza metoda solve()
    // (citire, rezolvare, printare)
    // * se distruge obiectul si se elibereaza memoria

    auto* task = new (std::nothrow) Task{};  // hint: cppreference/nothrow
    if (!task) {
        std::cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
