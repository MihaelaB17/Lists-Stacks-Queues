Tema 1:

La inceput am definit structurile pe care urmeaza sa le folosesc in implementarea nodurilor si a listelor(node, liste). Ulterior am definit cateva functii uzuale ce urmeza sa ma ajute in intializrea listelor, nodurilor, printarea listelor, eliberarea memoriei ocupate de acestea, dar si functii pentru inserare nodurilor(luam in condiserare 4 cazuri puntru o mai usoara parcurgere si inseram pe pozitia p:1). lista este vida, deci noul nod inserat este singurul din lista(el este si head si tail)
  2). noul nod trebuie inserat pe pozitia 0 (el devine head)
  3). noul nod trebuie inserat in prima jumatate a listei, caz in care aceasta va fi parcursa de la inceput pana la gasire pozitie pe care trebuie sa se insereze
  4). noul nod trebuie inserat in cea de-a 2 parte a liste, caz in care lista va fi parcursa de la final pana la gasirea pozitiei corespunzatoare
se insereaza nodul, creandu-se noile legaturi intre pointerii next si prev si se creste lungiea listei), de eliminare a nodurilor(tot 4 cazuri), pentru a sorta lista, pentru a copia o lista in alta lista, pentru a calcula media, deviatia si o funtia ce ajuta la filtratea folosind media aritmetica ce returneaza elemntul din mijloc pentru o lista de 5 elemente sortata.

In functia principala definesc listele de care voi avea nevoie ulterior pentru stocare datelor, dar si nodurilo folosite la parcurgerea acestora. ulterior parcurg argumentele transmise in linia de comanda si retinintru sir de caracte s valoreare respectiva oe care ulterior o compar cu e1, e2, e3, u, c, pentru a si ce cazuri trebuie efectuate.

Pentru e1: se creeaza o copie listei deoarece daca eliminan vreunul dintre primele 2 noduri ce il preced pe altul avem nevoite de valaore respectivului nod eliminat pentru a calcula media si derivatia celui ce il urmeaza. Ulterior se parcurg elementele din lista lista, dar si din copia acesteia intre pozitiile 2 si list->len-3 si se elimina nodurile cu nu respecta conditia, iar in momentul in care se elimina un nod se retine in ant precedentul, caruia si de dam dupa eliminare valoarea ant->next, pentru a sti mereu unde ne aflam. Daca nu se elimina se trece pur si simplu mai departe. In ambele cazuri se inaiteaza si in copia listei.

Pentru e2: se creeaza o noua lista in care vor fi retinute valorie din mijloc pentru fiecare bloc de 5 noduri consecutive. Aceast lista se sorteaza ulterior si se copiaza in variabila lista, eliberandu-se memoria necesara

Pentru e3: se creeaza o noua lista (sort_list) ce retine valorea mediei ficarui bloc de 5 noduri, iar aceasta este copiata ulterior in variriabila lista

Pentru u: se inlocuiesc valaorile  din campurile data respectiv timestamp pentru ficare nod ce respecta conditia ca valaore timestamp-ului sa fie intre [100,1000]

Pentru c: se parcurge lista si se creeaza pentru fiecare nod listele left si right si se initializeaza variabilele v1 si v2 su cele mai apropiate valori de nodul la care s-a ajuns. In calculul formuleleor vom folosi si variabile precum c, w, s1, s2 ce au corespondente in formulele prezentate. Valoarea finala a nodului inserat se retine in variabila cont.

Pentru st: se extrage mai intai valoarea lungimii intervalelor. sortam lista si retinem maximul si minimul din aceasta. Parcurgen elementele din lista, unde indicii left si right reprezinta capatul din stanga respectiv din dreapa a intervalelor in care cautam valori de ficare data cand terminam cu un interval si am gasit noduri a caror valoare se afla in interiorul acestuaia, afisam intervalul si nuamrul de noduri.

In final afisam lista doar daca variabila ok (initializata cu 1) este in continuare 1(singurul moment in care aceasta se schimba este cand intram pe ramura st si atunci nu mai trebuie aifsta lista. 
Eliberam memoria acupata de lista. 
