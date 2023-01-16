//v1.6.0
#include <iostream>
#include "typeDef.h"
#include "functions.h"
#include "tests.h"


using namespace std;

/*
 int main() {

test_push();
test_top();
test_pop();
test_insert();
test_deleteList();
test_remove();
test_min();
test_putACard();
test_shuffle();
test_moveUp();
test_moveDown();
test_play();
test_isValid();
test_score();
}
*/
// /*

int main() {
    // Initialization of the foundation piles and the player's hand
    List * fundationUpA = new List();
    List * fundationUpB = new List();
    List * fundationDownA = new List();
    List * fundationDownB = new List();

    // Initialization of foundation piles
    push(fundationUpA, new Element{1});
    push(fundationUpB, new Element{1});
    push(fundationDownA, new Element{100});
    push(fundationDownB, new Element{100});


    // Initialization of the stock
    List * stock = new List();
    shuffle(stock);

    // Request for the number of players
    int numberOfPlayers = 0;
    while(numberOfPlayers < 1 || numberOfPlayers > 5)
    {
        cout << "Enter the number of players (1-5): ";
        cin >> numberOfPlayers;
    }

    // Initialization of the players' hands
    List ** hands = new List*[numberOfPlayers];
    for (int iHand = 0; iHand < numberOfPlayers; iHand++) {
        hands[iHand] = new List();
    }

    // Distribution of cards
    int cardsPerPlayer = 0;
    if(numberOfPlayers == 1) cardsPerPlayer = 8;
    else if(numberOfPlayers == 2) cardsPerPlayer = 7;
    else cardsPerPlayer = 6;
    for (int nbCard = 0; nbCard < cardsPerPlayer; nbCard++) {
        for (int nbPlayer = 0; nbPlayer < numberOfPlayers; nbPlayer++) {
            push(hands[nbPlayer], new Element{top(stock)});
            pop(stock);
        }
    }

    // Initialization of the currentPlayer variable
    int currentPlayer = 0;

    // Game loop
    while (!isGameOver(hands[currentPlayer], fundationUpA, fundationUpB, fundationDownA, fundationDownB) || (stock->size == 0 && hands[currentPlayer]->size == 0)) {

        // Case of a multiplayer game
        if (numberOfPlayers > 1)
        {
            cout << "Player " << currentPlayer + 1 << ", it's your turn !" << endl;
            // Two turns per player
            for(int turn = 0; turn < 2; ++turn)
            {
                playTurn(fundationUpA, fundationUpB, fundationDownA, fundationDownB, hands, currentPlayer);
            }
            char choice = '\0';
            cout << "Do you want to play again (y/n)? ";
            cin >> choice;
            while(choice == 'y')
            {
                playTurn(fundationUpA, fundationUpB, fundationDownA, fundationDownB, hands, currentPlayer);
            }

        }else
        // Case of a single player game
        {
            playTurn(fundationUpA, fundationUpB, fundationDownA, fundationDownB, hands, currentPlayer);
        }

        // Adding a card from the player's hand if the hand is empty in function of the number of players
        if (hands[currentPlayer]->size == 0) {
            for(int iCard = 0; iCard < 5; iCard++)
            {
                push(hands[currentPlayer], new Element{top(stock)});
                pop(stock);
            }
        }

        // Pass to the next player
        currentPlayer = (currentPlayer + 1) % numberOfPlayers;
    }

    // Calculation of the final score
    cout << "Game Over! Final score : " << score(hands[currentPlayer], stock) << endl;

    // Freeing the memory
    for (int nbDel = 0; nbDel < numberOfPlayers; nbDel++) {
        deleteList(hands[nbDel]);
    }
    delete[] hands;
    deleteList(fundationUpA);
    deleteList(fundationUpB);
    deleteList(fundationDownA);
    deleteList(fundationDownB);
    deleteList(stock);

    return 0;
}
// */
