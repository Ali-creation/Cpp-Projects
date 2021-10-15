#include <cstdlib>
#include <iostream>

using namespace std;

typedef struct {
    // TODO: complete struct
    char name[50];
    int combat;
    int initiative;
    int wits;
    int sum;
} Soldier;

int compare(const void* p1, const void* p2) {
    // TODO: complete compare function for qsort()
    int first = ((Soldier *)p1)->sum;
    int second = ((Soldier *)p2)->sum;
    return ( second - first );
}

int main() {
    // TODO: read input
    int n;
    cin >> n;
    Soldier arr[n];
    for (int i=0; i<n; i++){
        cin >> arr[i].name >> arr[i].combat >> arr[i].initiative >> arr[i].wits;
        arr[i].sum = arr[i].combat + arr[i].initiative + arr[i].wits;
    }
    // TODO: sort array with qsort()
    qsort(arr, n, sizeof(Soldier), compare);

    // TODO: print result
    for (int i=0; i<n; i++){
        cout << arr[i].name <<" "<< arr[i].combat <<" "<< arr[i].initiative <<" "<< arr[i].wits<<endl;
    }

    return 0;
}