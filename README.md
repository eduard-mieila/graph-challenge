# Graph Challenge


## Descriere generală
Pe acest repo se află trei challenge-uri cu grafuri:

---

### 1. Bridges Challenge
Gigel se află pe un pod deasupra unei întinderi de apă în forma unui grid cu N linii si M coloane. Deasupra acestei suprafețe au fost construite trei tipuri de poduri: verticale(V), orizontale (O) sau duble (D). Denumirile acestor tipuri de poduri indică direcțiile încare se poate deplasa Gigel pe un astfel de pod:

1. pod vertical (V) – permite doar deplasarea cu o celulă la Nord sau cu o celulă la
Sud;
2. pod orizontal (O) – permite doar deplasarea cu o celulă la Vest sau cu o celulă la
Est;
3. pod dublu (D) – permite deplasarea cu o singură celulă în oricare dintre cele 4 direcții.

Scopul este acela de a determina numărul minim de poduri pe care trebuie să treacă Gigel pentru a ajunge la mal(a ieși de pe harta cu poduri).

---

### 2. Addresses Challenge

Gigel dorește să determine câte persoane distincte folosesc sistemul de poștă electronică. El are acces la o listă cu posibile persoane și pentru fiecare persoană o listă de e-mail-uri. Din păcate, multe dintre aceste persoane sunt fictive.
Îl vom ajuta pe Gigel să determine câte persoane distincte există și pentru fiecare persoană în parte vom afișa lista de e-mailuri, persoanele fiind sortate după numărul de e-mailuri, apoi lexicografic, iar e-mailurile afișate în ordine lexicografică.

---

### 3. LEGO Challenge

Având la dispoziție un număr mare de piede LEGO de dimensiune maxim K, dorim să selectăm N piese astfel încât să formăm cât mai multe dimensiuni diferite, combinând piesele între ele. Se impune restriția că vom folosi cel mult T piese.
Exemplu: cu parametrii K = 3, N = 2 și T = 3, folosind piesele de dimensiune 1 și 3 vom putea obșine din acestea dimensiunile următoare: 1, 2, 3, 4, 5, 6, 7, 9. Observăm că această secvență este formată din numerele de la 1 la 9, mai puțin 8. Scopul acestei probleme este identificarea pieselor cu care se pot forma cele mai multe bucăți de dimensiuni consecutive. 



## How to use
### Build
Pentru a compila toate problemele:

    make build

Pentru a compila fiecare challenge în parte:

    make b-poduri
    make b-adrese
    make b-lego

### Run

    # poduri:
    make run-p1 
    
    # adrese
    make run-p2

    # lego
    make run-p3


### Test
Pentru testarea corectitudinii se pot folosi materialele din graph_checker.zip.

## Informații suplimentare despre implementare
### 1. Bridges Challenge - poduri.cpp

In rezolvarea acestei probleme am urmarit ideea de la linkul [1]. Pe scurt, vom cauta cea mai scurta cale intr-un labirint, plecand de la punctul dat in fisierul de intrare si dorind sa ajungem in afara labirintului(nu la un anumit punct). De asemenea, deplasarea dintr-o casuta in alta a labirintului se face in functie de anumite restrictii, in functie de caracterul ce se afla in casuta curenta.
Ne vom folosi de o matrice de caractere, exact cea data in fisierul de intrare, si o matrice de booleeni ce ne arata daca o casuta a fost vizitata deja sau nu.
Se va initia o cautare BFS din nodul sursa, destinatia fiind oricare dintre linia sau coloana 0, respectiv linia n+1 sau coloana m+1(ne vom folosi de faptul ca indexarea se face incepand cu valoarea 1, asadar liniile si coloanele 0 nu sunt folosite).
Se va pune in coada de procesare casutele vecine de pe orizontala daca ne aflam pe un pod de tip O sau D, respectiv casutele vecine de pe vericala daca ne aflam pe un pod de tip V sau D.
Daca vom ajunge sa avem o coada de procesare goala, inseamna ca nu exista drum de la sursa in exteriorul labirintului, asdar distanta este -1.
Complexitatea acestui algoritm este O(N x M) pentru un labirint de dimensiuni N linii x M coloane, avand in vedere ca, in cel mai rau caz vom trece prin toate casutele labirintului.

---

### 2 - Addresses Challenge - adrese.cpp
Pentru acest challenge vom folosi structuri de tip User ce vor contine un ID(numarul de ordine al citirii), numele utilizatorului si emailurile pe care acesta le detine. Practic, fiecare utilizator va fi un nod ce va avea ca noduri adiacente toate mailurile pe care acesta le detine. Conditia acestei probleme este ca un mail sa fie detinut de un singur utilizator(pracitc, sa nu se ajunga de la un utilizator la altul, printr-un email). Pentru acest lucru ne vom folosi de un unordered_map ce va contine toate emailurile detinute de toti utilizatorii.
Se vor citi pe rand utilizatorii si mailurile lor, in cazul in care nu s-au gasit mailuri deja existente in unordered_map-ul cu emailuri, utilizatorul este adaugat direct in map-ul de utilizatori. Daca se gasesc mailuri duplicat, se determina utilizatorul care are numele cle mai mic din punct de vedere lexicografic, iar toate emailurile celorlalti clienti ii sunt atribuite acesstuia, actualizand datele in map-ul de utilizatori, respectiv unordered_map-ul de emailuri.
Considerand ca toate emailurile sunt unice, complexitatea algoritmului va fi O(n), unde n este numarul utilizatorilor. In cazul in care exista mailuri duplicat, vom adauga toate mailurile celorlalti utilizatori si vom actualiza datele acestora in O(k), unde k este numarul mailurilor ce vor fi adaugate si modificate. Toate celelalte adaugari/modificari/stergeri se realizeaza in cel mai rau caz in O(log n).

---

### 3 - Lego Challenge - lego.cpp
Pentru challenge-ul lego am pornit prin a genera toate piesele ce pot fi folosite(de la 1 la k). Apoi am generat toate domeniile pe care le vom verifica, formand toate combinarile de n elemente ce pot fi obtinute din toate piesele disponibile(restrictie: toate domeniile trebuie sa contina 1). Combinarile sunt generate folosind functia  disponibila la linkul [2]. Vom genera apoi toate sumele posibile folosind cel mult T elemente din fiecare domeniu. Pe masura ce sumele sunt generate, vom seta, intr-un vector de tip bool, pe pozitia i daca se poate obtine valoarea i folosind valorile din domeniul curent. La final vom verifica, pentru fiecare domeniu, cate sume sunt consecutive, folosind vectorul de booleeni.
Generarea domeniilor se va face in O(Combinari(n,k)), generarea tuturor sumelor in O(n^t), iar determinarea numarului de sume consecutive in O(k * t).

Referinte:
[1]: https://www.geeksforgeeks.org/shortest-path-in-a-binary-maze/
[2]: https://ocw.cs.pub.ro/courses/pa/laboratoare/laborator-05#backtracking_taierea_ramurilor_nefolositoare1