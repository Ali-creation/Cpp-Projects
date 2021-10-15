#include "player.h"
#include <string>
using namespace std;

string Player::getName(){
    return this->name;
}
int Player::getID(){
    return this->ID;
}
Team Player::getTeam(){
    return this->team;
}
void Player::setPlayer(Team tm, int id){
    this->team = tm;
    this->ID = id;
    if (tm == SOSBrigade)
        this->name = SOS_Name[id-1];
    else
        this->name = SC_Name[id-1];
}

class SimplePlayer : public Player{
    public:
        int bet(unsigned int bankroll, unsigned int minimum) override{
            if (bankroll < minimum)
                return 0;
            return (int) minimum;
        }
        
        bool draw(Card dealer, const Hand& player) override{
            if(!player.handValue().soft){
                if( player.handValue().count <= 11)
                    return true;
                else return !((player.handValue().count == 12 && dealer.spot >= FOUR && dealer.spot <= SIX) ||
                                (player.handValue().count >= 13 && player.handValue().count <= 16 && dealer.spot >= TWO &&
                                dealer.spot <= SIX) || (player.handValue().count >= 17));
            }
            else {
                if( player.handValue().count <= 17)
                    return true;
                else return !((player.handValue().count == 18 && 
                                (dealer.spot == TWO || dealer.spot == SEVEN || dealer.spot == EIGHT) ) || 
                                (player.handValue().count >=19));
            }
        }

        void expose(Card c) override{}
        void shuffled() override{}
};

class CountingPlayer : public SimplePlayer{
    protected:
        int count = 0;
    public:
        int bet(unsigned int bankroll, unsigned int minimum) override{
            if(this->count >= 2 && bankroll >= 2*minimum)
                return (int) 2*minimum;
            return (int) minimum;
        }

        /*bool draw(Card dealer, const Hand& player){
            if(!player.handValue().soft){
                if( player.handValue().count <= 11)
                    return true;
                else return !((player.handValue().count == 12 && dealer.spot >= FOUR && dealer.spot <= SIX) ||
                                (player.handValue().count >= 13 && player.handValue().count <= 16 && dealer.spot >= TWO &&
                                dealer.spot <= SIX) || (player.handValue().count >= 17));
            }
            else {
                if( player.handValue().count <= 17)
                    return true;
                else return !((player.handValue().count == 18 && 
                                (dealer.spot == TWO || dealer.spot == SEVEN || dealer.spot == EIGHT) ) || 
                                (player.handValue().count >=19));
            }
        }*/

        void expose(Card c) override{
            if( c.spot >= TEN ) this->count --;
            else if( c.spot >= TWO && c.spot <= SIX) this->count ++;
        }
        void shuffled() override{
            this->count = 0;
        }
};

class SuzumiyaHaruhi : public SimplePlayer{
    public:
        int bet(unsigned int bankroll, unsigned int minimum) override{
            return (int) 2*minimum;
        }
};

class AsahinaMikuru : public CountingPlayer{
    public:
        int bet(unsigned int bankroll, unsigned int minimum) override{
            if(this->count < -2 && bankroll >= 2*minimum)
                return (int) 2*minimum;
            return (int) minimum;
        }
};

class KakyoinNoriaki : public CountingPlayer {
    public:
        int bet(unsigned int bankroll, unsigned int minimum) override{
            if(this->count >= 4 && bankroll >= 2*minimum)
                return (int) 2*minimum;
            return (int) minimum;
        }
};

Player* get_Player(string& dealerSide, string& playerType, int& ID){
    Team playerSide;
    if (dealerSide.compare("sc") == 0)
        playerSide = SOSBrigade;
    else
        playerSide = StardustCrusaders;
    
    Player* get = nullptr;
    if(playerSide == SOSBrigade){
        switch (ID)
        {
        case 1:
            get = new SuzumiyaHaruhi();
            break;
        case 2:
            get = new CountingPlayer();
            break;
        case 3:
            get = new AsahinaMikuru();
            break;
        case 4:
            get = new SimplePlayer();
            break;
        case 5:
            if(playerType.compare("simple") == 0)
                get = new SimplePlayer();
            else
                get = new CountingPlayer();
            break;
        }
    }
    else{
        switch (ID)
        {
        case 1:
            get = new CountingPlayer();
            break;
        case 2:
            get = new CountingPlayer();
            break;
        case 3:
            get = new SimplePlayer();
            break;
        case 4:
            get = new KakyoinNoriaki();
            break;
        case 5:
            if(playerType.compare("simple") == 0)
                get = new SimplePlayer();
            else
                get = new CountingPlayer();
            break;
        }
    }
    return get;
}