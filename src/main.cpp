//v0.7.0
#include <iostream>
#include "typeDef.h"
#include "functions.h"


using namespace std;

  /*

test_push();
test_top();
test_pop();
test_insert();
test_displayList();
test_deleteList();
test_remove();
test_min();


test_putACard();
test_-e();
test_displayBoard();
test_moveUp();
test_moveDown();
test_play();
test_isValid();
test_score();
}
*/

int main() {
    // Initialisation des piles de fondations et de la main du joueur
    List * fundationUpA = new List();
    List * fundationUpB = new List();
    List * fundationDownA = new List();
    List * fundationDownB = new List();
    List * hand = new List();

    // Initialisation du stock
    List * stock = new List();
    shuffle(stock);

    // Distribution des cartes
    for (int i = 0; i < 5; i++) {
        push(hand, new Element{top(stock)});
        pop(stock);
    }

    // Boucle de jeu
    while (!isGameOver(hand, fundationUpA, fundationUpB, fundationDownA, fundationDownB)) {
        // Affichage du plateau de jeu
        displayBoard(fundationUpA, fundationUpB, fundationDownA, fundationDownB, hand);

        // Demande de jeu à l'utilisateur
        int card;
        char stack;
        play(card, stack);
        // Vérification de la validité de la carte
        if (!isValid(hand, card)) {
            cout << "Carte non valide, veuillez réessayer." << endl;
            continue;
        }

        // Déplacement de la carte vers la pile de fondation sélectionnée
        if (!moveSuccessful(fundationUpA, fundationUpB, fundationDownA, fundationDownB, hand,stack,card)) {
            cout << "Déplacement impossible, veuillez réessayer." << endl;
            continue;
        }

    // Suppression de la carte de la main du joueur
    remove(hand, card);

    // Ajout d'une carte de la main du joueur si la main est vide
    if (hand->size == 0) {
        for(int i = 0; i < 5; i++)
        {
        push(hand, new Element{top(stock)});
        pop(stock);
         }
    }
}

// Calcul du score final
cout << "Partie terminée ! Score final : " << score(hand, stock) << endl;

// Libération de la mémoire
deleteList(fundationUpA);
deleteList(fundationUpB);
deleteList(fundationDownA);
deleteList(fundationDownB);
deleteList(hand);
deleteList(stock);

return 0;
}
