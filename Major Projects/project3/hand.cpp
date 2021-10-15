#include "hand.h"

Hand::Hand() {
    this->discardAll();
}
void Hand:: discardAll() {
    this->curValue.soft = false;
    this->curValue.count = 0;
}
void Hand::addCard(Card c) {
    if (c.spot == ACE){
        if(this->curValue.soft || this->curValue.count>=11)
            this->curValue.count += 1;
        else{
            this->curValue.count += 11;
            this-> curValue.soft = true;
        }
    }
    else if (c.spot >= TWO && c.spot <= TEN)
        this->curValue.count += (c.spot + 2);
    else
        this->curValue.count += 10;
    
    if (this->curValue.soft && this->curValue.count > 21){
        this->curValue.count -= 10;
        this->curValue.soft = false;
    }
}
HandValue Hand::handValue() const {
    return this->curValue;
}