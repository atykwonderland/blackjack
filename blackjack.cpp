#include "blackjack.h"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/*-----------------CARD-----------------*/
Card::Card(Rank r, Type t) {
    this->rank = r;
    this->type = t;
}
int Card::getValue() const {
    if (this->rank <= 10) {
        return this->rank;
    } else {
        return 10;
    }
}
void Card::displayCard() const {
    if (this->rank < 11) {
        cout << this->rank << char(this->type) << " ";
    } else {
        switch (this->rank) {
            case 11:
                cout << "J" << char(this->type) << " ";
                break;
            case 12:
                cout << "Q" << char(this->type) << " ";
                break;
            case 13:
                cout << "K" << char(this->type) << " ";
                break;
        }
    }
}
/*-----------------HAND-----------------*/
void Hand::add(Card c) {
    if (c.getValue() == 1){
        this->aces++;
    }
    (this->hand).push_back(c);
}
void Hand::clear() {
    (this->aces) = 0;
    (this->hand).clear();
}
int Hand::getTotal() const {
    int sum = 0;
    for(auto&& x: this->hand) {
        if (x.getValue() != 1) {
            sum += x.getValue();
        }
    }
	int count = this->aces;
    while (count > 0) {
        if (sum <= 10) {
            sum += 11;
            count--;
        }
        else {
            sum++;
            count--;
        }
    }
    return sum;
}
void Hand::show() const {
    for(auto&& x: this->hand) {
        x.displayCard();
    }
}
/*-----------------DECK-----------------*/
void Deck::populate() {
    for(int type = 1; type < 5; type++) {
        Type t;
        switch (type) {
            case 1:
                t = CLUBS;
                break;
            case 2:
                t = DIAMONDS;
                break;
            case 3:
                t = HEARTS;
                break;
            case 4:
                t = SPADES;
                break;
        }
        for(int rank = 1; rank < 14; rank++) {
            (this->deck).push_back(Card(static_cast<Rank>(rank), t));
        }
    }
}
void Deck::shuffle() {
     random_shuffle((this->deck).begin(),(this->deck).end());
}
void Deck::deal(Hand &h) {
    Card card = (this->deck).back();
    (this->deck).pop_back();
    h.add(card);
}
void Deck::show() const {
    for(auto&& x: this->deck) {
        x.displayCard();
    }
}
void Deck::clear() {
    (this->deck).clear();
}
/*-----------------ABSTRACTPLAYER-----------------*/
bool AbstractPlayer::isBusted() {
    return (getTotal() > 21);
}
/*-----------------COMPUTERPLAYER-----------------*/
bool ComputerPlayer::isDrawing() const {
    return (getTotal()<=16);
}
/*-----------------HUMANPLAYER-----------------*/
bool HumanPlayer::isDrawing() const {
    cout << "Do you want to draw ? (y/n): ";
    char input;
    bool isValid = false;
    cin >> input;
    while (!isValid) {
        if (input == 'y') {
            return true;
        }   
        else if (input == 'n') {
            return false;
        }
        else {
            cin.clear();
            cin.ignore(INT8_MAX, '\n');
            cout << "Input invalid. Enter 'y' or 'n': ";
            cin >> input;
        }
    }
}
void HumanPlayer::announce(Hand computer) {
    if (getTotal() > 21) {
        cout << "Casino Wins\n";
    } else if (computer.getTotal() > 21) {
        cout << "Player Wins\n";
    } else if ((computer.getTotal()-getTotal()) < 0) {
        cout << "Player Wins\n";
    } else if ((computer.getTotal()-getTotal()) > 0) {
        cout << "Casino Wins\n";
    } else {
        cout << "Push: It is a tie\n";
    }
}
/*-----------------BLACKJACKGAME-----------------*/
void BlackJackGame::play() {
    //setup deck
    m_deck.populate();
    m_deck.shuffle();
    
    // create player
    HumanPlayer player;
    
    
    // deal two cards to player and show
    m_deck.deal(player);
    m_deck.deal(player);
    cout << "Player: ";
    (player).show();
    cout << "[" << (player).getTotal() << "]\n";
    
    // deal one card to house and show
    m_deck.deal(m_casino);
    cout << "Casino: ";
    m_casino.show();
    cout << "[" << m_casino.getTotal() << "]\n";

    // player decides to draw or not
    while ((player).isDrawing()) {
        // deal a card to player and show
        m_deck.deal(player);
        cout << "Player: ";
        (player).show();
        cout << "[" << (player).getTotal() << "]\n";
        // check if busted.
        if ((player).isBusted())
        {
            cout << "Player is busted." << endl;
            (player).announce(m_casino);
            m_casino.clear();
            m_deck.clear();
            return;
        }
    }
    // deal another card to house and show
    m_deck.deal(m_casino);
    cout << "Casino: ";
    m_casino.show();
    cout << "[" << m_casino.getTotal() << "]\n";    
    
    // deal until casino <= 16
    while (m_casino.isDrawing()) { m_deck.deal(m_casino);}
    cout << "Casino: ";
    m_casino.show();
    cout << "[" << m_casino.getTotal() << "]\n";
    
    // show winner
    (player).announce(m_casino);
    
    m_casino.clear();
    m_deck.clear();
}