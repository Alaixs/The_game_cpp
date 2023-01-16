//v1.4.0
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
    // Initialisation des piles de fondations et de la main du joueur
   List * fundationUpA = new List();
    List * fundationUpB = new List();
    List * fundationDownA = new List();
    List * fundationDownB = new List();

    // Initialisation des piles de fondations
    push(fundationUpA, new Element{1});
    push(fundationUpB, new Element{1});
    push(fundationDownA, new Element{100});
    push(fundationDownB, new Element{100});


    // Initialisation du stock
    List * stock = new List();
    shuffle(stock);

    // Demande du nombre de joueurs
    int numberOfPlayers = 0;
    while(numberOfPlayers < 1 || numberOfPlayers > 5)
    {
        cout << "Enter the number of players (1-5): ";
        cin >> numberOfPlayers;
    }

    // Initialisation des mains des joueurs
    List ** hands = new List*[numberOfPlayers];
    for (int i = 0; i < numberOfPlayers; i++) {
        hands[i] = new List();
    }

    // Distribution des cartes
    int cardsPerPlayer = 0;
    if(numberOfPlayers == 1) cardsPerPlayer = 8;
    else if(numberOfPlayers == 2) cardsPerPlayer = 7;
    else cardsPerPlayer = 6;
    for (int i = 0; i < cardsPerPlayer; i++) {
        for (int j = 0; j < numberOfPlayers; j++) {
            push(hands[j], new Element{top(stock)});
            pop(stock);
        }
    }

    // Initialisation de la variable currentPlayer
    int currentPlayer = 0;

    // Boucle de jeu
while (!isGameOver(hands[currentPlayer], fundationUpA, fundationUpB, fundationDownA, fundationDownB) || (stock->size == 0 && hands[currentPlayer]->size == 0)) {

    // Demande de jeu à l'utilisateur
    if (numberOfPlayers > 1)
    {
    cout << "Player " << currentPlayer + 1 << ", it's your turn !" << endl;
    }
    int card;
    char stack;
    int cardsPlayed = 0;
    for (int i = 0; i < 2; i++) {
        displayBoard(fundationUpA, fundationUpB, fundationDownA, fundationDownB, hands[currentPlayer]);
        play(card, stack);
        // Vérification de la validité de la carte
        if (!isValid(hands[currentPlayer], card)) {
            cout << "Invalid card, please try again." << endl;
            continue;
        }

        // Déplacement de la carte vers la pile de fondation sélectionnée
        if (!moveSuccessful(fundationUpA, fundationUpB, fundationDownA, fundationDownB,stack,card)) {
            cout << "Unable to move, please try again." << endl;
            continue;
        }
        // Suppression de la carte de la main du joueur
        remove(hands[currentPlayer], card);
        }
        // Demande au joueur s'il veut rejouer
        if(numberOfPlayers > 1)
        {
            cout << "Do you want to play again (y/n)? ";
            char choice;
            cin >> choice;
            if (choice == 'n') {

            }
        }
// Ajout d'une carte de la main du joueur si la main est vide
if (hands[currentPlayer]->size == 0) {
    for(int i = 0; i < 5; i++)
    {
        push(hands[currentPlayer], new Element{top(stock)});
        pop(stock);
    }
}

// Passage au joueur suivant
currentPlayer = (currentPlayer + 1) % numberOfPlayers;
}

// Calcul du score final
cout << "Game Over! Final score : " << score(hands[currentPlayer], stock) << endl;

// Libération de la mémoire
for (int i = 0; i < numberOfPlayers; i++) {
    deleteList(hands[i]);
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