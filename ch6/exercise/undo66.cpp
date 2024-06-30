#include<iostream>
#include"../case/6-2.h"

template<class DECK, class SUIT, class FACE>
class card
{
    public:
        card(DECK theDeck, SUIT theSuit, FACE theFace, card<DECK, SUIT, FACE>* theLink)
        {
            deck = theDeck; suit = theSuit; face = theFace; link = theLink;
        }
        operator DECK()const {return deck;}
        operator SUIT()const {return suit;}
        operator FACE()const {return face;}
    protected:
        DECK deck;
        SUIT suit;
        FACE face;
        card<DECK, SUIT, FACE>* link;
};



int main()
{
    chain<card<int, char, double>> a;

}
