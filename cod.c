#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

///definesc structurile ce urmeaza sa fie folosite pentru noduri si liste
typedef struct NODE {
    double data;
    int timestemp;
    struct NODE *next;
    struct NODE *prev;
} node;

typedef struct LIST {
    node *head;
    node *tail;
    int len;
} list;

///functia de mai jos initializeaza un nod, alocand memorie pentru acesta, dandu-i valoarea value campului data  si valoate t campului timestamp
node * init_node(double value, int t) 
{
    node *new_node = calloc(1,sizeof(node));
    new_node->data = value;
    new_node->timestemp=t;

    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;
}

///initializarea unei liste, alocand memorie pentru aceasta si initializand head-ul si tail-ul cu NULL 
list *init_list() 
{
    list *new_list = calloc(1,sizeof(list));
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->len = 0;

    return new_list;
}

///functia de mai jos elibereaza memoria ocupata de o lista parcurgand-o de la final catre inceput si eliberand nodul de pe pozitia lista->tail
void free_list(list *lista)
{
    node *aux;
    while(lista->len > 0){
        aux=lista->tail;
        lista->tail=lista->tail->prev;
        free(aux);
        lista->len=lista->len-1;
    }
    free(lista);
}

///printeaza listea conform formatului cerut preznetat in cerinte
void print_list(list *lista) 
{
    node *aux = lista->head;

    while (aux != lista->tail) {
        printf("%d %.2f\n", aux->timestemp, aux->data);
        aux = aux->next;
    }
    printf("%d %.2f\n", aux->timestemp, aux->data);
}

///functia de mai jos insereaza un nou nod in lista cu valoare value pe pozitia p luand in considerare 4 cazuri:
/// 1). lista este vida, deci noul nod inserat este singurul din lista(el este si head si tail)
/// 2). noul nod trebuie inserat pe pozitia 0 (el devine head)
/// 3). noul nod trebuie inserat in prima jumatate a listei, caz in care aceasta va fi parcursa de la inceput pana la gasire pozitie pe care trebuie sa se insereze
/// 4). noul nod trebuie inserat in cea de-a 2 parte a liste, caz in care lista va fi parcursa de la final pana la gasirea pozitiei corespunzatoare
///se insereaza nodul, creandu-se noile legaturi intre pointerii next si prev si se creste lungiea listei
void insert_node(list *lista, double value, int p, int t) 
{
    node *nod=init_node(value,t);
    int mij=lista->len/2;
 
    if(lista->head==NULL && lista->tail==NULL){
        lista->head=nod;
        lista->tail=nod;
        lista->len++;
    }
    else
        if(p==0){
            nod->next=lista->head;
            lista->head->prev=nod;
            lista->head=nod;
            lista->len++;
        }
        else
            if(p == lista->len){
                nod->prev=lista->tail;
                lista->tail->next=nod;
                lista->tail=nod;
                lista->len++;
            }
            else
                    if(p < mij){
                        int i=0;
                        node *curr=lista->head;
                        while(i < p){
                            curr=curr->next;
                            i++;
                        }
                        nod->prev=curr->prev;
                        curr->prev->next=nod;
                        nod->next=curr;
                        curr->prev=nod;
                        lista->len++;
                    }
                    else
                        if(p >= mij){
                            int i=lista->len-1;
                            node *curr=lista->tail;
                            while(i > p){
                                curr=curr->prev;
                                i--;
                            }
                            nod->prev=curr->prev;
                            nod->next=curr;
                            curr->prev->next=nod;
                            curr->prev=nod;
                            lista->len++;
                        }
}

///functia de mai jos sterge nodul de pe pozitia p din lista
///se iau in calcul aceleasi cazuri ca si la functia de inserare, urmand ca dupa identificare pozitiei cautate sa se stearga nodul respectiv, sa se elibereze memorie
///unde este cazul si sa scada lungimea listei la fiecare eliminare
void remove_node(list *lista, int p) 
{    
    node *nod;
    int mij=lista->len-1/2;
  
    if(p == 0){
        nod=lista->head->next;
        lista->head=nod;
        lista->head->prev=NULL;
        lista->len--;
    }
    else
        if(p == lista->len-1){
            nod=lista->tail->prev;
            lista->tail=nod;
            lista->tail->next=NULL;
            lista->len--;
        }
        else 
            if(p < mij){
                node *curr, *aux;
                curr=lista->head;
                int i=0;
                while(i < p){
                    aux=curr;
                    curr=curr->next;
                    i++;
                }
                aux->next=curr->next;
                curr->next->prev=aux;
                free(curr);
                lista->len--;
            }
            else
                if(p >= mij){
                    node *curr, *aux;
                    curr=lista->tail;
                    int i=lista->len-1;
                    while(i > p){
                        aux=curr;
                        curr=curr->prev;
                        i--;
                    }
                    curr->next->prev=aux;
                    aux->next=curr->next;
                    free(curr);
                    lista->len--;
                }
}

///functia de mai jos sorteaza o lista in ordinea crescatoare a valorilor din campul data, parcurgand elementele listei cu ajutorul a 2 varialile de tip node: i si j
void sortare (list *lista)
{
    double aux;
    node *i, *j;
    for(i=lista->head; i->next != NULL; i=i->next)
        for(j=i->next; j != NULL; j=j->next){
            if(i->data > j->data){
                aux=i->data;
                i->data=j->data;
                j->data=aux;
            }
        }    
}

///functia de mai jos calculeaza media ceurta de prima cerinta, adunand valorile celor 5 noduri luate in considerare(nodul nod, primele 2 de dinaitea lu si urmaroarele
///doua noduri). Aceasta suma se imparte ulterior la 5 pentru a se obtine media aritmetica
double media(node *nod)
{
    double s;
    s = nod->prev->prev->data + nod->prev->data + nod->data + nod->next->data + nod->next->next->data;
    return s/5;
}

///mai jos este calculata deviatia, conform formulei date in cerinta 1 si cu ajutorul functiei media> In variabila s se retine suma respectiva care se actualizeaza
///pentru fiecare dinte cele 5 noduri luate in considerare. Ulterior se returneaza radical din suma respectiva
double deviatia(node *nod)
{
    double s=0;
    node *start, *stop;
    start=nod->prev->prev;
    stop=nod->next->next;
    while(start != stop->next){
        s = s + (start->data - media(nod)) * (start->data - media(nod)); 
        start=start->next;
    }
    return sqrt(s/5);
}

///functia de mai jos retine intr-o noua lista 5 noduri(de pe aceleasi pozitii precizte mai sus) pe care ulterior o sorteaza si returneaza elementul din mijloc
double f_mediana(node *nod)
{
    double min;
    int p=0;
    node *start, *stop, *aux;
    list *new_list;

    new_list=init_list(new_list);
    start=nod->prev->prev;
    stop=nod->next->next;

    while(start != stop->next){
        insert_node(new_list,start->data,p,start->timestemp);
        p++;
        start=start->next;
    }

    sortare(new_list);
    min=new_list->head->next->next->data;
    free_list(new_list);
    return min;
}

///urmatoare functia copiaza o lista in alta lista fara a o sterge pe cea din care se copiaza
void copiere_lista(list *new_list, list *lista)
{
    node *nod=lista->head;
    int p=0;
    while(nod != NULL){
        insert_node(new_list,nod->data,p,nod->timestemp);
        p++;
        nod=nod->next;
    }
}

int main(int argc, char *argv[])
{
    int n, p=0, i=0, t, ok=1,j;
    char s[4];
    double val1, val2, x;
    ///urmaroatele liste declarate vor fi folosite ulterios in rezolvare cerintelor e2, e2, e3, u, c
    list *lista, *cp_list, *sort_list;
    node *aux, *ult, *ant, *copie;

    ///initializam lista si ii dam valorile dorite
    lista=init_list(lista);
    scanf("%d",&n);
    while(i<n){
        scanf("%d %lf",&t, &x);
        insert_node(lista,x,p,t);
        p++;
        i++;
    }

    ///se parcurg argumentele transmise in linia de comanda pentru a se rezolva cerinta/cerintele respective
    for(i=1; i<argc; i++){
        strcpy(s,argv[i]+2);

        if(strcmp(s,"e1") == 0){
            p=2;
    ///pentur e1 se creeaza o copie listei deoarece daca eliminan vreunul dintre primele 2 noduri ce il preced pe altul avem nevoite de valaore respectivului nod eliminat
    ///pentru a calcula media si derivatia celui ce il urmeaza
    ///ulterior se parcurg elementele din lista lista, dar si din copia acesteia intre pozitiile 2 si list->len-3 si se elimina nodurile cu nu respecta conditia, iar 
    ///in momentul in care se elimina un nod se retine in ant precedentul, caruia si de dam dupa eliminare valoarea ant->next, pentru a sti mereu unde ne aflam. 
    ///Daca nu se elimina se trece pur si simplu mai departe. In ambele cazuri se inaiteaza si in copia listei
            cp_list=init_list(cp_list);
            copiere_lista(cp_list,lista);
            aux=lista->head->next->next;
            ult=cp_list->tail->prev->prev;
            copie=cp_list->head->next->next;
            while(copie != ult->next){
                val1=media(copie);
                val2=deviatia(copie);
                if(aux->data < val1-val2 || aux->data > val1+val2) {
                    ant=aux->prev;
                    remove_node(lista,p);
                    aux=ant->next;
                }
                else{

                    aux=aux->next;
                    p++;
                }
               
                copie=copie->next;
            }
            free_list(cp_list);
        }
    
        if(strcmp(s,"e2") == 0){
            p=0;
            sort_list=init_list(sort_list);
    ///pentru e2 se creeaza o noua lista in care vor fi retinute valorie din mijloc pentru fiecare bloc de 5 noduri consecutive. Aceast lista se sorteaza ulterior 
    ///si se copiaza in variabila lista, eliberandu-se memoria necesara
            aux=lista->head->next->next;
            ult=lista->tail->prev->prev;
            while(aux != ult->next){
                x=f_mediana(aux);
                insert_node(sort_list,x,p,aux->timestemp);
                aux=aux->next;
                p++;
            }

            free_list(lista);
            lista=init_list(lista);
            copiere_lista(lista, sort_list);
            free_list(sort_list);
        }
            
        if(strcmp(s,"e3") == 0){
    ///pentru e3 se creeaza o noua lista ce retine valorea mediei ficarui bloc de 5 noduri, iar aceasta lista este copiata ulterior in variriabila lista 
            sort_list=init_list(sort_list);
            aux=lista->head->next->next;
            ult=lista->tail->prev->prev;
            p=0;
            while(aux != ult->next){
                insert_node(sort_list,media(aux),p,aux->timestemp);
                aux=aux->next;
                p++;
            }

            free_list(lista);
            lista=init_list(lista);
            copiere_lista(lista, sort_list);
            free_list(sort_list);
        }

        if(strcmp(s,"u")==0){
    ///pentru u se inlocuiesc valaorile din campurile data si timestamp pentru ficare nod ce respecta conditia ca valaore timestamp-ului sa fie intre [100,1000]
            aux=lista->head->next;
            while(aux != NULL){
                if(aux->timestemp - aux->prev->timestemp >= 100 && aux->timestemp - aux->prev->timestemp <= 1000){
                    aux->timestemp=(aux->prev->timestemp + aux->timestemp)/2;
                    aux->data=(aux->prev->data + aux->data)/2;
                }
                aux=aux->next;
            }
        }
    
        if(strcmp(s,"c")==0){
            int p=1;
            node *aux;
            list *left, *right;
            aux=lista->head->next;
    ///pentru c se parcurge lista si se creeaza pentru fiecare nod listele left si right si se initializeaza variabilele v1 si v2 su cele mai apropiate valori de nodul
    ///la care s-a ajuns
            while(aux != NULL){
                if(aux->timestemp - aux->prev->timestemp > 1000){
                    left=init_list(left);
                    right=init_list(right);
                    int i;
                    double C, v1, v2;
                    node *st=aux->prev->prev->prev, *dr=aux->next->next;
                    for(i=0; i<3; i++){
                        insert_node(left,st->data,i,st->timestemp);
                        insert_node(right,dr->data,i,dr->timestemp);
                        st=st->next;
                        dr=dr->prev;
                        if(i==2){
                            v2=st->timestemp;
                            v1=dr->timestemp;
                        }
                    }
    ///dupa crearea celor 2 lsite se insereza noduri unde diferenta intre doua valori timestamp consecutive este mai mare de 200 pana cand aceasta diferenta scade sub 200
    ///valorile ce trebuie stocate in campurile data si timestamp ale noilor noduri inserate vor fi calculate conform formulelor. Valaore finala a nodului inserat se
    ///retine in variabila cont
                    while(aux->timestemp - aux->prev->timestemp > 200){
                        double ss, w, s1=0, s2=0, cont;
                        C=((double)aux->prev->timestemp + 200 - v1) / (v2 - v1);
                        node *c1, *c2;
                        c1=left->head;
                        c2=right->head;
                        for(i=0; i<3; i++){
                            ss=0;
                            for(j=0; j<3; j++)
                                ss=ss + ((double)j/2) * ((double)j/2) *0.9 + 0.1;
                            w=(((double)i/2) * ((double)i/2) *0.9 + 0.1) / ss;

                            s1=s1+c1->data * w;
                            s2=s2+c2->data * w;
                            c1=c1->next;
                            c2=c2->next;
                        }
                        cont=(1 - C) * s1 + C * s2;
                        insert_node(lista, cont, p, aux->prev->timestemp + 200);
                        p++;
                    }
                    free_list(left);
                    free_list(right);
                }
                p++;
                aux=aux->next;
            }
        }

        if(s[0] == 's'){
            ok=0;
            int valoare=0, p=1, i, maxim, left, right, nr, minim;
            node *nod;
    ///pentru st se extrage mai intai valoarea lungimii intervalelor
            i=strlen(s)-1;
            while(i >= 2){
                if(s[i] >= '0' && s[i] <= '9'){
                    valoare=valoare+(s[i]-'0')*p;
                    p=p*10;
                    i--;
                }
            }
    ///sortam lista si retinem maximul si minimul din aceasta
            sortare(lista);
            maxim=lista->tail->data;
            minim=lista->head->data;

            if(abs(minim) > maxim)
                maxim=abs(minim);

            left=maxim*(-1)-1;
            right=left+valoare;
    ///parcurgen elementele din lista, unde indicii left si right reprezinta capatul din stanga respectiv din dreapa a intervalelor in care csutam valori
    ///de ficare data cand terminam cu un interval si am gasit noduri a caror valoare se afla in interiorul acestuaia, afisam intervalul si nuamrul de noduri
            while(right <= maxim+1){
                nr=0;
                for(nod=lista->head; nod != NULL; nod=nod->next)
                    if(nod->data>=left && nod->data <= right)
                        nr++;
                if(nr != 0)
                    printf("[%d, %d] %d\n", left, right, nr);
                left=right;
                right=right+valoare;
            }
        }
    }
    ///singurul caz in care nu trebuie sa afisam lista este st, asa ca variabila ok(initializata cu 1) isi schimba valoarea in 0 doar daca intra pe cazul st. Altfel, dupa
    ///realizarea tuturor operatiilor se afiseaza lista obtinuta si se elibereaza memoria
    if(ok==1){
        printf("%d\n", lista->len);
        print_list(lista);
    }

    free_list(lista);
}