//v1.10.0
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

    system("color 9F");

    title();

    // Request for the level of difficulty
    int difficulty = 0;
    while(difficulty < 1 || difficulty > 3)
    {
        cout << "Enter the level of difficulty (Normal: 1, Hard: 2, Really Hard: 3): ";
        cin >> difficulty;
    }

    // Request for the number of players
    int numberOfPlayers = 0;
    while(numberOfPlayers < 1 || numberOfPlayers > 5)
    {
        cout << "Enter the number of players (1-5): ";
        cin >> numberOfPlayers;
    }

    clearScreen();

    // Initialization of the players' hands
    List ** hands = new List*[numberOfPlayers];
    for (int iHand = 0; iHand < numberOfPlayers; iHand++) {
        hands[iHand] = new List();
    }
int cardsPerPlayer = 0;
    if(numberOfPlayers == 1) cardsPerPlayer = 8;
    else if(numberOfPlayers == 2) cardsPerPlayer = 7;
    else cardsPerPlayer = 6;
    if(difficulty == 3) 
    {cardsPerPlayer -= 1; }
    for (int nbCard = 0; nbCard < cardsPerPlayer; nbCard++) {
        for (int nbPlayer = 0; nbPlayer < numberOfPlayers; nbPlayer++) {
            insert(hands[nbPlayer], new Element{top(stock)});
            pop(stock);
        }
    }

    // Initialization of the currentPlayer variable
    int currentPlayer = 0;
    int numberOfTurns = 2;

    if(difficulty > 1)
    {
    numberOfTurns += 1;
    }
    // Game loop
    while (true)
    {
            cout << "Player " << currentPlayer + 1 << ", it's your turn !" << endl;
            // Two turns per player
            for(int turn = 0; turn < numberOfTurns; ++turn)
            {
                playTurn(fundationUpA, fundationUpB, fundationDownA, fundationDownB, hands, currentPlayer);
                clearScreen();
                if (isGameOver(hands[currentPlayer], fundationUpA, fundationUpB, fundationDownA, fundationDownB) || (stock->size == 0 && hands[currentPlayer]->size == 0))
                    {
                        displayEndScreen(hands, stock, numberOfPlayers);
                        return 0;
                    }
            }

            //ask to the player if he wants to play again with a loop
            char answer = ' ';
            while(answer != 'n') {
    cout << "Do you want to play again ? (y/n) ";
    cin >> answer;
    if (answer != 'n') {
    playTurn(fundationUpA, fundationUpB, fundationDownA, fundationDownB, hands, currentPlayer);
    clearScreen();
    }
    if (isGameOver(hands[currentPlayer], fundationUpA, fundationUpB, fundationDownA, fundationDownB) || (stock->size == 0 && hands[currentPlayer]->size == 0)) {
    displayEndScreen(hands, stock, numberOfPlayers);
        return 0;
    }
}

        // Adding a card from the player's hand after his turn
    // Adding a card from the player's hand after his turn
    while(cardsPerPlayer != hands[currentPlayer]->size)
    {
        if(stock->size == 0)
        {
            break;
        }
        insert(hands[currentPlayer], new Element{top(stock)});
        pop(stock);
    }

        // Pass to the next player
        currentPlayer = (currentPlayer + 1) % numberOfPlayers;
}

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

