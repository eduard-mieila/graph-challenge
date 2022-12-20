#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

// Functie de sortare pentru perechi de forma <idClient, numeClient>
bool pairCmp(pair<int, string> p1, pair<int, string> p2) {
    return (p1.second.compare(p2.second) < 0);
}

// Clasa ce contine date despre un utilizator
class User {
 public:
    // ID-ul utilizatorului(ordinea in care acesta a fost primit la intrare)
    int id;
    // Numele utilizatorului
    string name;
    // Emailurile urilizatorului(vom folosi set, pentru a avea mailurile
    // permanent sortate)
    set<string> emails;

    User() {}

    User(int newId, string newName, set<string> newEmails) {
        id = newId;
        name = newName;
        emails = newEmails;
    }
};

// Functie ce sorteaza utilizatorii dupa nume
bool userCmp(User u1, User u2) {
    return (u1.name.compare(u2.name) < 0);
}

// Functie ce sorteaza utilizatorii dupa numarul de mailuri
bool userEmailsCmp(User u1, User u2) {
    return u1.emails.size() < u2.emails.size();
}

// Clasa ce contine date despre un email
class Email {
 public:
    // Emailul
    string email;
    // ID-ul utilizatorului care detine acest email
    int userId;

    Email() {}

    Email(string newEmail, int newId) {
        email = newEmail;
        userId = newId;
    }
};

class Task {
 public:
    void solve() {
        read_input();
        print_output();
    }

 private:
    // Numarul de utilizatori
    int n;

    // Utilizatorii vor fi stocati intr-un map cu
    // -    cheia = ID-ul utilizatorului
    // - valoarea = o structura de tip User
    // pentru a accesa, adauga si sterge elemente in O(log n)
    map<int, User> users;

    // Vom mentine toate mailurile intr-un unordered_map cu
    // -    cheia = email
    // - valoarea = o structura de tip Email
    // pentru a accesa si adauga elemente in O(1).
    // Vom folosi aceasta variabila pentru a verifica daca un anumit mail,
    // ce vine la un anumit moment, exista deja in baza de date
    unordered_map<string, Email> emails;


    void read_input() {
        ifstream fin("adrese.in");

        fin >> n;

        for (int i = 0; i < n; i++) {
            int k;
            string currUsername;

            fin >> currUsername >> k;

            // Vom tine in tmpEmails, mailuri pentru utilizatorul ce este in
            // in curs de citire
            set<string> tmpEmails;
            // In vectorul duplUsers vom tine perechi de forma
            // <IDUtilizator, NumeUtilizator>, cu datele utilizatorilor care au
            // un mail in comun cu utilizatorul curent
            vector<pair<int, string>> duplUsers;

            for (int j = 0; j < k; j++) {
                // Citim emailul curent
                string currEmail;
                fin >> currEmail;

                unordered_map<string, Email>::iterator emailsIt;
                emailsIt = emails.find(currEmail);

                // Verifica daca emailul este deja existent
                if (emailsIt == emails.end()) {
                    // Daca emailul nu este duplicat, adauga-l in vectorul de
                    // emailuri ce urmeaza sa fie adaugate
                    tmpEmails.insert(currEmail);
                } else {
                    // Daca emailul este duplicat, adauga id-ul clientului in
                    // vectorul de clienti duplicati
                    duplUsers.push_back(pair<int, string>
                                        (emailsIt->second.userId,
                                        users[emailsIt->second.userId].name));
                }
            }

            // Eliminam duplicatele din duplUsers
            sort(duplUsers.begin(), duplUsers.end(), pairCmp);
            duplUsers.erase(unique(duplUsers.begin(), duplUsers.end()),
                                duplUsers.end());

            if (duplUsers.empty()) {
                // Nu avem mailuri duplicat, deci adaugam utlizatorul nou
                // alaturi de emailurile sale
                User currUser(i, currUsername, tmpEmails);
                for (auto currEmail : tmpEmails) {
                    emails.insert(pair<string, Email>(currEmail,
                                                        Email(currEmail, i)));
                }
                users.insert(pair<int, User>(i, currUser));
            } else if (duplUsers.size() == 1) {
                // Avem mailuri duplicat cu o singura persoana, asadar
                // determinam care din acestea ramane
                map<int, User>::iterator usersIt =
                                                users.find(duplUsers[0].first);

                if (currUsername.compare(usersIt->second.name) < 0) {
                    // Noul utilizator trebuie sa ramana
                    // Creaza un utlizator nou cu emailurile care nu sunt
                    // duplicat
                    User currUser = User(i, currUsername, tmpEmails);
                    for (auto currEmail : tmpEmails) {
                        emails.insert(pair<string, Email>(currEmail,
                                                    Email(currEmail, i)));
                    }

                    // Modifica mailurile deja existente cu noul id
                    for (auto currEmail : usersIt->second.emails) {
                        // Gaseste mailul
                        unordered_map<string, Email>::iterator emailsIt;
                        emailsIt = emails.find(currEmail);
                        // Modifica id-ul
                        emailsIt->second.userId = i;
                        // Adauga acest email la userul curent
                        currUser.emails.insert(emailsIt->second.email);
                    }

                    // Sterge utilizatorul vechi
                    users.erase(usersIt);

                    // adauga noul utilizator
                    users.insert(pair<int, User>(i, currUser));
                } else {
                    // Vechiul utilizator ramane
                    // Adaugam mailurile curente la acesta si in baza de date
                    for (auto currEmail : tmpEmails) {
                        usersIt->second.emails.insert(currEmail);
                        emails.insert(pair<string, Email>(currEmail,
                                        Email(currEmail, duplUsers[0].first)));
                    }
                }
            } else {
                // Avem mai multe duplicate
                // Determinam stringul cel mai mic dpdv lexicografic
                map<int, User>::iterator usersIt =
                                            users.find(duplUsers[0].first);

                // Daca utilizatorul care ramane este cel nou
                // Cream un utilizator nou, mutam ceilalti utilizatori in cel
                // nou, actualizam detaliile fiecarui mail
                if (currUsername.compare(duplUsers[0].second) < 0) {
                    User newUser(i, currUsername, tmpEmails);
                    for (size_t j = 1; j < duplUsers.size(); j++) {
                        for (auto currEmail :
                                    users[duplUsers[j].first].emails) {
                            // Gaseste mailul
                            unordered_map<string, Email>::iterator emailsIt;
                            emailsIt = emails.find(currEmail);
                            // Actualizeaza detinatorul mailului
                            emailsIt->second.userId = i;
                            // Adauga mailul la userul curent
                            newUser.emails.insert(currEmail);
                        }
                        // Elimina utlizatorul vechi
                        users.erase(duplUsers[j].first);
                    }

                    // Adaugam mailurile
                    for (auto currEmail : tmpEmails) {
                        emails.insert(pair<string, Email>(currEmail,
                                                    Email(currEmail, i)));
                    }

                    users.insert(pair<int, User>(i, newUser));
                } else {
                    // Vom folosi un utilizator deja existent
                    usersIt = users.find(duplUsers[0].first);
                    for (size_t j = 1; j < duplUsers.size(); j++) {
                        // Copiaza utilizatorii vechi
                        for (auto currEmail :
                                    users[duplUsers[j].first].emails) {
                            // Adauga mailul la userul curent
                            usersIt->second.emails.insert(currEmail);
                            // Actualizzeaza detinatorul mailului
                            unordered_map<string, Email>::iterator emailsIt;
                            emailsIt = emails.find(currEmail);
                            emailsIt->second.userId = duplUsers[0].first;
                        }
                        // Elimina utlizatorul vechi
                        users.erase(duplUsers[j].first);

                        // Copiaza mailurile utilizatorului nou
                        for (auto currEmail : tmpEmails) {
                            // Adauga mailurile la utilizator
                            usersIt->second.emails.insert(currEmail);
                            // Adauga mailurile in vectorul emails
                            emails.insert(pair<string, Email>(currEmail,
                                        Email(currEmail, duplUsers[0].first)));
                        }
                    }
                }
            }
        }

        fin.close();
    }

    void print_output() {
        ofstream fout("adrese.out");

        vector<User> sortedUsers;
        for (auto user : users) {
            sortedUsers.push_back(user.second);
        }

        // Sortam utilizatorii conform cerintei
        sort(sortedUsers.begin(), sortedUsers.end(), userCmp);
        sort(sortedUsers.begin(), sortedUsers.end(), userEmailsCmp);

        fout << sortedUsers.size() << endl;
        for (User currUser : sortedUsers) {
            fout << currUser.name << " " << currUser.emails.size() << endl;
            for (string currEmail : currUser.emails) {
                fout << currEmail << endl;
            }
        }

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
