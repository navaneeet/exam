#include <stdio.h>

// Representation of a term in sparse polynomial: coeff and expo
struct Term { int coeff; int expo; };

// Add two sparse polynomials stored as arrays of Terms (descending exponents)
void addPoly(struct Term p1[], int n1, struct Term p2[], int n2, struct Term res[], int *n3) {
    int i = 0, j = 0, k = 0;
    while (i < n1 && j < n2) {
        if (p1[i].expo == p2[j].expo) {
            int s = p1[i].coeff + p2[j].coeff;
            if (s != 0) { res[k].coeff = s; res[k].expo = p1[i].expo; k++; }
            i++; j++;
        } else if (p1[i].expo > p2[j].expo) {
            res[k++] = p1[i++];
        } else {
            res[k++] = p2[j++];
        }
    }
    while (i < n1) res[k++] = p1[i++];
    while (j < n2) res[k++] = p2[j++];
    *n3 = k;
}

void display(struct Term p[], int n) {
    if (n == 0) { printf("0\n"); return; }
    for (int i = 0; i < n; i++) {
        printf("%d*x^%d", p[i].coeff, p[i].expo);
        if (i != n-1) printf(" + ");
    }
    printf("\n");
}

int main() {
    struct Term p1[20], p2[20], res[40];
    int n1, n2, n3;

    printf("Enter number of terms in first sparse polynomial: ");
    scanf("%d", &n1);
    printf("Enter coeff and exponent pairs in descending exponent order:\n");
    for (int i = 0; i < n1; i++) scanf("%d %d", &p1[i].coeff, &p1[i].expo);

    printf("Enter number of terms in second sparse polynomial: ");
    scanf("%d", &n2);
    printf("Enter coeff and exponent pairs in descending exponent order:\n");
    for (int i = 0; i < n2; i++) scanf("%d %d", &p2[i].coeff, &p2[i].expo);

    printf("\nFirst polynomial: "); display(p1, n1);
    printf("Second polynomial: "); display(p2, n2);

    addPoly(p1, n1, p2, n2, res, &n3);
    printf("Sum: "); display(res, n3);
    return 0;
}