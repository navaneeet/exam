#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coeff, expo;
    struct Node *next;
} Node;

Node* create(int c,int e){ Node* n=malloc(sizeof(Node)); n->coeff=c; n->expo=e; n->next=NULL; return n; }

void insertSorted(Node** head, int c, int e) {
    if (c==0) return;
    Node *p = create(c,e);
    if (*head==NULL || (*head)->expo < e) { p->next = *head; *head = p; return; }
    Node *cur = *head;
    while (cur->next && cur->next->expo > e) cur=cur->next;
    if (cur->expo == e) {
        cur->coeff += c; free(p);
        return;
    } else { p->next = cur->next; cur->next = p; }
}

Node* add(Node* p1, Node* p2) {
    Node *r = NULL;
    while (p1 && p2) {
        if (p1->expo == p2->expo) { insertSorted(&r, p1->coeff + p2->coeff, p1->expo); p1=p1->next; p2=p2->next; }
        else if (p1->expo > p2->expo) { insertSorted(&r, p1->coeff, p1->expo); p1=p1->next; }
        else { insertSorted(&r, p2->coeff, p2->expo); p2=p2->next; }
    }
    while (p1) { insertSorted(&r, p1->coeff, p1->expo); p1=p1->next; }
    while (p2) { insertSorted(&r, p2->coeff, p2->expo); p2=p2->next; }
    return r;
}

Node* multiply(Node* p1, Node* p2) {
    Node *r = NULL;
    for (Node *a=p1; a; a=a->next) {
        for (Node *b=p2; b; b=b->next) {
            insertSorted(&r, a->coeff * b->coeff, a->expo + b->expo);
        }
    }
    return r;
}

void printPoly(Node* p) {
    if (!p) { printf("0\n"); return; }
    while (p) { printf("%d*x^%d", p->coeff, p->expo); if (p->next) printf(" + "); p=p->next; } printf("\n");
}

int main(){
    Node *p1=NULL,*p2=NULL;
    int n,c,e;
    printf("First polynomial terms: "); scanf("%d",&n);
    printf("Enter coeff expo in descending expo order:\n");
    for (int i=0;i<n;i++){ scanf("%d %d",&c,&e); insertSorted(&p1,c,e); }
    printf("Second polynomial terms: "); scanf("%d",&n);
    printf("Enter coeff expo in descending expo order:\n");
    for (int i=0;i<n;i++){ scanf("%d %d",&c,&e); insertSorted(&p2,c,e); }
    printf("P1: "); printPoly(p1);
    printf("P2: "); printPoly(p2);
    Node *sum = add(p1,p2);
    printf("Sum: "); printPoly(sum);
    Node *prod = multiply(p1,p2);
    printf("Product: "); printPoly(prod);
    return 0;
}