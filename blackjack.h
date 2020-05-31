#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

enum Rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
enum Type { 
            CLUBS = 'C', 
            DIAMONDS = 'D', 
            HEARTS = 'H', 
            SPADES = 'S'
        };
        
class Card {
    protected:
        Rank rank;
        Type type;
    public:
        Card(Rank r, Type t);
        int getValue() const;
        void displayCard() const;
};

class Hand {
    protected:
        vector<Card> hand;
        int aces = 0;
    public:
        void add(Card c);
        void clear();
        int getTotal() const;
        void show() const;
};

class Deck {
    private:
        vector<Card> deck;
    public:
        void populate();
        void shuffle();
        void deal(Hand &h);
        void clear();
        void show() const;
};

class AbstractPlayer : public Hand {
    //inherits: hand, aces, getVHand(), add(), clear(), getTotal()
    public:
        virtual bool isDrawing() const = 0;
        bool isBusted();
};

class ComputerPlayer : public virtual AbstractPlayer {
    //inherits: hand, aces, getVHand(), add(), clear(), getTotal()
    //inherits: getHand(), isDrawing(), isBusted()
    public:
        bool isDrawing() const;
};

class HumanPlayer : public virtual AbstractPlayer {
    //inherits: hand, aces, getVHand(), add(), clear(), getTotal()
    //inherits: getHand(), isDrawing(), isBusted()
    public:
        bool isDrawing() const;
        void announce(Hand computer);
};

class BlackJackGame {
    private:
        Deck m_deck;
        ComputerPlayer m_casino;
    public:
        void play();
};