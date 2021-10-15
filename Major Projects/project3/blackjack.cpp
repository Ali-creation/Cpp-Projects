#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "rand.h"
#include "card.h"

using namespace std;

void shuffling(Deck& deck, Player* player);
bool checkDeckEmpty(Deck& deck, Player* player, int& thishand);
Card dealforPlayer(Deck& deck, Hand& hand, Player* player);
Card dealforPlayerWithoutAnnounce(Deck& deck, Hand& hand, Player* player);
Card dealforDealer(Deck& deck, Hand& hand, string dealerName, Player* player, bool faceUp);
string dealerName(string& dealerTeam, int& dealerId);
void Kujo_player_process(Deck& deck, Hand& hand, Player* kujo, int& NumOfCards, Card dealerFaceUpCard, Card& theLastCard);
void kujo_dealer_process(Deck& deck, Hand& hand, int& NumOfCards, Player* player, Card& theLastCard, string dealer_name);
const int minimumBet = 5;

int main(int argc, char* argv[]){
    int bankroll = stoi(argv[1]);
    int handsNum = stoi(argv[2]);
    string type = argv[3];
    string dealerTeam = argv[4];
    const int normal_bankroll = bankroll;

    int playerId = 0;
    int dealerId = 0;
    bool playerLose = true;
    bool dealerLose = true;
    Player *curPlayer = nullptr;
    string dealer_name;
    Deck deck;
    while( (dealerId < 6 && playerId < 6) && ((playerLose && playerId !=5) || (dealerLose && dealerId != 5)) ){
        
        if(playerLose){
            playerId++;
            curPlayer = get_Player(dealerTeam, type, playerId);
            bankroll = normal_bankroll;
            if(dealerTeam.compare("sc") == 0)
                curPlayer->setPlayer(SOSBrigade, playerId);
            else
                curPlayer->setPlayer(StardustCrusaders, playerId);
            
            if(curPlayer->getName().compare("Joseph Joestar") == 0)
                bankroll = 2*normal_bankroll;
        }
        if(dealerLose){
            dealerId++;
            dealer_name = dealerName(dealerTeam, dealerId);
        }
        
        shuffling(deck, curPlayer);

        int thishand = 0;
        Hand playerHand;
        Hand dealerHand;

        bool JosephEscape = false;

        while(bankroll >= minimumBet && handsNum > thishand){
            thishand++;
            cout << "Hand " << thishand << " bankroll " << bankroll << endl;

            if(deck.cardsLeft() < 20)
                shuffling(deck, curPlayer);
            int wager = curPlayer->bet(bankroll, minimumBet);
            cout << "Player: " << curPlayer->getName() << " bets " << wager << endl;

            dealerHand.discardAll();
            playerHand.discardAll();

            dealforPlayer(deck, playerHand, curPlayer);
            Card dealerFaceUpCard = dealforDealer(deck, dealerHand, dealer_name, curPlayer, true);
            dealforPlayer(deck, playerHand, curPlayer);
            Card dealerFaceDownCard = dealforDealer(deck, dealerHand, dealer_name, curPlayer, false);

            if(playerHand.handValue().count == 21){
                int winPay = (int) ((wager*3)/2);
                bankroll += winPay;
                cout << "Player: " << curPlayer->getName() << " dealt natural 21" << endl;
                cout << "Player: " << curPlayer->getName() << " has " << bankroll << " after " << thishand << " hands" << endl;
                continue;
            }

            int playerNumOfCards = 2;
            Card theLastCard;
            if(curPlayer->getName().compare("Kujo Jotaro") == 0){
                while(curPlayer->draw(dealerFaceUpCard, playerHand)){
                    if(deck.cardsLeft() == 0) break;
                    theLastCard = dealforPlayerWithoutAnnounce(deck, playerHand, curPlayer);
                    playerNumOfCards++;
                    if(playerHand.handValue().count <= 21){
                        
                        cout << "Player: " << curPlayer->getName() << " dealt " <<  SpotNames[theLastCard.spot] << " of " << SuitNames[theLastCard.suit] << endl;
                    }
                    else{
                        Kujo_player_process(deck, playerHand, curPlayer, playerNumOfCards, dealerFaceUpCard, theLastCard);
                    }
                }
                if(checkDeckEmpty(deck, curPlayer, thishand)) continue;
            }
            else{
                while(curPlayer->draw(dealerFaceUpCard, playerHand)){
                    if(deck.cardsLeft() == 0) break;
                    dealforPlayer(deck, playerHand, curPlayer);
                    //playerNumOfCards++;
                }
                if(checkDeckEmpty(deck, curPlayer, thishand)) continue;
            }
            
            int player_count = playerHand.handValue().count;
            cout << "Player: " << curPlayer->getName() << "'s total is " << player_count << endl;

            if(player_count > 21){
                cout << "Player: " << curPlayer->getName() << " busts" << endl;
                bankroll -= wager;
            }
            else{
                cout << "Dealer: " << dealer_name << "'s hole card is " << SpotNames[dealerFaceDownCard.spot] 
                << " of " << SuitNames[dealerFaceDownCard.suit] << endl;
                curPlayer->expose(dealerFaceDownCard);

                bool natural21 = false;
                if(dealerHand.handValue().count == 21){
                    cout << "Dealer: " << dealer_name << " dealt natural 21" << endl;
                    natural21 = true;
                }

                int dealerNumOfCards = 2;
                Card lastDealerCard;
                if(dealer_name.compare("Kujo Jotaro") == 0){
                    while(dealerHand.handValue().count  < 17){
                        if(deck.cardsLeft() == 0) break;
                        lastDealerCard = dealforDealer(deck, dealerHand, dealer_name, curPlayer, false);
                        dealerNumOfCards++;
                        if(dealerHand.handValue().count <= 21){
                            cout << "Dealer: " << dealer_name << " dealt " <<  SpotNames[lastDealerCard.spot] << " of " << SuitNames[lastDealerCard.suit] << endl;
                            curPlayer->expose(lastDealerCard);
                        }
                        else{
                            kujo_dealer_process(deck, dealerHand, dealerNumOfCards, curPlayer, lastDealerCard, dealer_name);
                        }
                    }
                    if(checkDeckEmpty(deck, curPlayer, thishand)) continue;
                }
                else{
                    while(dealerHand.handValue().count  < 17){
                        if(deck.cardsLeft() == 0) break;
                        dealforDealer(deck, dealerHand, dealer_name, curPlayer, true);
                        //dealerNumOfCards++;
                    }
                    if(checkDeckEmpty(deck, curPlayer, thishand)) continue;
                }

                int dealer_count = dealerHand.handValue().count;
                if(!natural21)
                    cout << "Dealer: " << dealer_name << "'s total is " << dealer_count << endl;

                if(dealer_count > 21){
                    cout << "Dealer: " << dealer_name << " busts" << endl;
                    bankroll += wager;
                }
                else if(dealer_count > player_count){
                    cout << "Dealer: " << dealer_name << " wins this hand" << endl;
                    bankroll -= wager;
                }
                else if (player_count> dealer_count){
                    cout << "Player: " << curPlayer->getName() << " wins this hand" << endl;
                    bankroll += wager;
                }
                else
                    cout << "Push" << endl;
            }
            cout << "Player: " << curPlayer->getName() << " has " << bankroll << " after " << thishand << " hands" << endl;
            if(curPlayer->getName().compare("Joseph Joestar") == 0 && bankroll < normal_bankroll/2){
                cout << "Player: Joseph Joestar: \"Ni Ge Run Da Yo\"" << endl;
                JosephEscape = true;
                break;
            }
        }

        if(thishand == 0)
            cout << "Player: " << curPlayer->getName() << " has " << bankroll << " after " << thishand << " hands" << endl;

        if(bankroll >= minimumBet && !JosephEscape){
            cout << "Dealer: " << dealer_name << " has been kicked out. The winner of this round is "<< curPlayer->getName() <<"." << endl;
            if(curPlayer->getName().compare("Kakyoin Noriaki") == 0)
                cout << "Player: Kakyoin Noriaki: \"rerorerorero rerorerorero\"" << endl;
            if(curPlayer->getName().compare("Joseph Joestar") == 0)
                cout << "Player: Joseph Joestar: \"Nice!\"" << endl;
            dealerLose = true;
            playerLose = false;
        }
        else if(bankroll < minimumBet || JosephEscape){
            cout << "Player: " << curPlayer->getName() << " has been kicked out. The winner of this round is "<< dealer_name <<"." << endl;
            if(dealer_name.compare("Kakyoin Noriaki") == 0)
                cout << "Dealer: Kakyoin Noriaki: \"rerorerorero rerorerorero\"" << endl;
            if(dealer_name.compare("Joseph Joestar") == 0)
                cout << "Dealer: Joseph Joestar: \"Nice!\"" << endl;
            dealerLose = false;
            playerLose = true;
        }
    }
    if(dealerId > 4){
        if(dealerTeam.compare("sc") == 0)
            cout << "Game over. The winner is SOS Brigade. SOS Brigade got four computers and Stardust Crusaders become an affiliate group of SOS Brigade" << endl;
        else
            cout << "Game over. The winner is Stardust Crusaders. SOS Brigade will return the computer to Joseph Joestar and Suzumiya Haruhi will become a member of Stardust Crusaders" << endl;
    }
    if(playerId > 4){
        if(dealerTeam.compare("sc") == 0)
            cout << "Game over. The winner is Stardust Crusaders. SOS Brigade will return the computer to Joseph Joestar and Suzumiya Haruhi will become a member of Stardust Crusaders" << endl;
        else
            cout << "Game over. The winner is SOS Brigade. SOS Brigade got four computers and Stardust Crusaders become an affiliate group of SOS Brigade" << endl;
    }
}

void shuffling(Deck& deck, Player* player){
    cout<< "Shuffling the deck"<<endl;
    for(int i=0; i <7; i++){
        int cut = get_cut();
        deck.shuffle(cut);
        cout << "cut at " << cut << endl;
    }
    player->shuffled();
}

bool checkDeckEmpty(Deck& deck, Player* player, int& thishand){
    if(deck.cardsLeft() == 0){
        cout << "Hand " << thishand << " card used up, this hand will start again" << endl;
        shuffling(deck, player);
        thishand--;
        return true;
    }
    return false;
}

Card dealforPlayer(Deck& deck, Hand& hand, Player* player){
    Card dealt = deck.deal();
    hand.addCard(dealt);
    player->expose(dealt);
    cout << "Player: " << player->getName() << " dealt " <<  SpotNames[dealt.spot] << " of " << SuitNames[dealt.suit] << endl;
    return dealt; 
}
Card dealforPlayerWithoutAnnounce(Deck& deck, Hand& hand, Player* player){
    Card dealt = deck.deal();
    hand.addCard(dealt);
    player->expose(dealt);
    return dealt;
}

Card dealforDealer(Deck& deck, Hand& hand, string dealerName, Player* player, bool faceUp){
    Card dealt = deck.deal();
    hand.addCard(dealt);
    if(faceUp){
        cout << "Dealer: " << dealerName << " dealt " <<  SpotNames[dealt.spot] << " of " << SuitNames[dealt.suit] << endl;
        player->expose(dealt);
    }
    return dealt;
}

string dealerName(string& dealerTeam, int& dealerId){
    if(dealerTeam.compare("sc") == 0)
        return SC_Name[dealerId-1];
    else
        return SOS_Name[dealerId-1];
}

void Kujo_player_process(Deck& deck, Hand& hand, Player* kujo, int& NumOfCards, Card dealerFaceUpCard, Card& theLastCard){
    if(deck.cardsLeft() == 0) return;
    if(hand.handValue().count > 21){
        cout << "Player: " << kujo->getName() << ":" << " \"Star Platinum, Za Warudo\"" << endl;
        hand.discardAll();
        for(int i=0; i<NumOfCards; i++){
            theLastCard = dealforPlayerWithoutAnnounce(deck, hand, kujo);
            if(deck.cardsLeft() == 0) break;
        }
        Kujo_player_process(deck, hand, kujo, NumOfCards, dealerFaceUpCard, theLastCard);
    }
    else{
        cout << "Player: " << kujo->getName() << " dealt " <<  SpotNames[theLastCard.spot] << " of " << SuitNames[theLastCard.suit] << endl;
    }
}

void kujo_dealer_process(Deck& deck, Hand& hand, int& NumOfCards, Player* player, Card& theLastCard, string dealer_name){
    if(deck.cardsLeft() == 0) return;
    if(hand.handValue().count > 21){
        cout << "Dealer: Kujo Jotaro: \"Star Platinum, Za Warudo\"" << endl;
        hand.discardAll();
        for(int i=0; i<NumOfCards; i++){
            theLastCard = dealforDealer(deck, hand, "Kujo Jotaro", player, false);
            if(deck.cardsLeft() == 0) break;
        }
        kujo_dealer_process(deck, hand, NumOfCards, player, theLastCard, dealer_name);
    }
    else{
        player->expose(theLastCard);
        cout << "Dealer: " << dealer_name << " dealt " <<  SpotNames[theLastCard.spot] << " of " << SuitNames[theLastCard.suit] << endl;
    }
}
