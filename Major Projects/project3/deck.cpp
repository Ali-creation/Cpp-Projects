#include "deck.h"

Deck::Deck(){
    this->reset();
}
void Deck::reset(){
    int counter = 0;
    for (int i =0; i<=DIAMONDS; i++){
        for (int j=0; j<= ACE; j++){
            Suit ii = (Suit)  i ;
            Spot jj = (Spot) j;
            deck[counter].spot = jj;
            deck[counter].suit = ii;
            counter++;
        }
    }
    this->next = 0;
}
void Deck::shuffle (int n) {
    int leftSize = n;
    Card leftDeck[leftSize];
    int rightSize = DeckSize-n;
    Card rightDeck[rightSize];
    for(int i=0; i<leftSize; ++i)
        leftDeck[i] = this->deck[i];
    for(int j=0; j<rightSize; ++j)
        rightDeck[j] = this->deck[n+j];
    
    if(leftSize<26){
        for (int i=0; i<leftSize; ++i){
            this->deck[2*i] = rightDeck[i];
            this->deck[2*i + 1] = leftDeck[i];
        }
        for(int i = 2*leftSize; i<DeckSize; ++i)
            this->deck[i] = rightDeck[i-leftSize];
    }else{
        for (int i=0; i<rightSize; ++i){
            this->deck[2*i] = rightDeck[i];
            this->deck[2*i + 1] = leftDeck[i];
        }
        for (int i=2*rightSize; i<DeckSize; ++i)
            this->deck[i] = leftDeck[i-rightSize];
    }
    this->next = 0;
}

Card Deck::deal() {
    if(this->next < DeckSize){
        this->next++;
        return this->deck[next-1];
    }
    throw DeckEmpty();
}

int Deck::cardsLeft(){
    return DeckSize - (this->next);
}
