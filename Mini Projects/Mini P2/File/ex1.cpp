#include <iostream>

using namespace std;

#define RANGE 100000

bool isPrime[RANGE + 1];

// MODIFIES: isPrime[]
// EFFECTS: fill in isPrime[], true for prime, false otherwise
void generateIsPrime() {
    // TODO: implement Eratosthenes Sieve Algorithm
    isPrime[0] = false;
    isPrime[1] = false;
    for (int i=2; i<=RANGE; i++){
        isPrime[i]=true;
    }
    for (int p=2; p<=RANGE; p++){
        if(isPrime[p] == true){
            for (int i=p+p; i<=RANGE; i+=p)
                isPrime[i] = false;
        }
    }
}

int main() {
    // TODO: generate lookup table
    generateIsPrime();

    // TODO: read input and check if each num is prime
    int n;
    cin>>n;
    int input[n];
    for(int i=0; i<n; i++){
        cin>>input[i];
        if(isPrime[input[i]] == true)
            cout<<input[i]<<" ";
    }
    
    return 0;
}