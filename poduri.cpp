#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <limits>

#define MAXDIM 2052

using namespace std;

struct qNode {
    int x;
    int y;
    int distance;
};

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, m, x, y;
    vector<vector<char>> grid;
    void read_input() {
        ifstream fin("poduri.in");
        fin >> n >> m;
        fin >> x >> y;

        // Gridul nostru va avea dimensiunea ((n + 2) X (m + 2)) pentru a
        // avea borduri ce vor reprezenta destinatia finala.
        grid = vector<vector<char>>(n+2, vector<char>(m + 2, '.'));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                fin >> grid[i][j];
            }
        }

        fin.close();
    }

    int get_result() {
        // Matrice ce va retine starea nodurilor: vizitat/nevizitat
        bool visited[MAXDIM][MAXDIM];
        memset(visited, false, sizeof(visited));

        // Setam nodul de plecare ca fiind vizitat
        visited[x][y] = true;

        // Cream o coada pentru nodurile ce urmeaza sa fie procesate
        queue<qNode> BFSq;

        // Adaugam nodul de plecare in coada de procesare
        qNode src = {x, y, 0};
        BFSq.push(src);

        while (!BFSq.empty()) {
            // Cat timp mai avem noduri de procesat, setam nodul curent pe
            // primul nod din coada
            qNode currNode = BFSq.front();

            // Daca nodul curent a ajuns pe marginea grid-ului,
            // s-a ajuns la destinatie
            if (currNode.x == 0 || currNode.y == 0 ||
                currNode.x == n + 1 || currNode.y == m + 1) {
                    return currNode.distance;
            }

            // Scoatem nodul curent din coada
            BFSq.pop();

            // Daca nodul curent este o punte verticala sau dubla,
            // incercam sa mergem in sus si jos pe grid. Vom merge
            // intr-unul din cele doua noduri daca acestea nu au fost
            // anterior vizitate
            if (grid[currNode.x][currNode.y] == 'V' ||
                grid[currNode.x][currNode.y] == 'D') {
                if (!visited[currNode.x - 1][currNode.y]) {
                    qNode n1 = {currNode.x - 1, currNode.y,
                                    currNode.distance + 1};     // sus
                    BFSq.push(n1);
                    visited[currNode.x - 1][currNode.y] = true;
                }

                if (!visited[currNode.x + 1][currNode.y]) {
                    qNode n2 = {currNode.x + 1, currNode.y,
                                    currNode.distance + 1};     // jos
                    BFSq.push(n2);
                    visited[currNode.x + 1][currNode.y] = true;
                }
            }

            // Daca nodul curent este o punte orizontala sau dubla,
            // incercam sa mergem in stanga si dreapta pe grid. Vom merge
            // intr-unul din cele doua noduri daca acestea nu au fost
            // anterior vizitate
            if (grid[currNode.x][currNode.y] == 'O' ||
                grid[currNode.x][currNode.y] == 'D') {
                if (!visited[currNode.x][currNode.y - 1]) {
                    qNode n1 = {currNode.x, currNode.y - 1,
                                    currNode.distance + 1};     // stanga
                    BFSq.push(n1);
                    visited[currNode.x][currNode.y - 1] = true;
                }

                if (!visited[currNode.x][currNode.y + 1]) {
                    qNode n2 = {currNode.x, currNode.y + 1,
                                    currNode.distance + 1};     // dreapta
                    BFSq.push(n2);
                    visited[currNode.x][currNode.y + 1] = true;
                }
            }
        }

        // Daca nu mai exista noduri de procesat, nu s-a ajuns la destinatie
        // asadar returnam -1.
        return -1;
    }



    void print_output(int result) {
        ofstream fout("poduri.out");
        fout << result;
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
