// Given array A; choose at most k events to maximize sum of points.
// Strategy: pick k largest values (if A may contain negatives, pick only positive ones up to k).
#include <stdio.h>
#include <stdlib.h>

int cmpdesc(const void*a,const void*b){ return (*(int*)b - *(int*)a); }

long maxPoints(int A[], int n, int k) {
    qsort(A,n,sizeof(int), cmpdesc);
    long sum=0;
    for (int i=0;i<n && i<k;i++) if (A[i]>0) sum+=A[i]; else break;
    return sum;
}

int main(){
    int n,k;
    printf("Enter number of events: "); scanf("%d",&n);
    int *A = malloc(n*sizeof(int));
    printf("Enter activity points for each event:\n");
    for (int i=0;i<n;i++) scanf("%d",&A[i]);
    printf("Enter max number of events allowed (k): "); scanf("%d",&k);
    long res = maxPoints(A,n,k);
    printf("Maximum activity points achievable (select at most %d): %ld\n",k,res);
    free(A);
    return 0;
}