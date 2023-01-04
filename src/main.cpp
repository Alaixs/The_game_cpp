//v0.6.0
#include <iostream>
#include "functions.h"

using namespace std;

int main() {
  // Initialisation du plateau de jeu
  List fundationUpA, fundationUpB, fundationDownA, fundationDownB, stock, hand;
  shuffle(&stock);

  // Distribution des cartes au joueur
  for (int i = 0; i < 10; ++i) {
    int card = top(&stock);
    pop(&stock);
    putACard(&hand, card);
  }

  // Début de la partie
  bool gameOver = false;
  while (!gameOver) {
    // Affichage du plateau de jeu
    displayBoard(&fundationUpA, &fundationUpB, &fundationDownA, &fundationDownB, &hand);

    // Demande de jouer une carte au joueur
    int card;
    char stack;
    play(card, stack);

    // Vérification de la validité de la carte jouée
    if (!isValid(&hand, card)) {
      cout << "Invalid card." << endl;
      continue;
    }

    // Déplacement de la carte dans la colonne de fondations choisie
    bool moveSuccessful = false;
    switch (stack) {
      case 'A':
        moveSuccessful = moveUp(&fundationUpA, card);
        break;
      case 'B':
        moveSuccessful = moveUp(&fundationUpB, card);
        break;
      case 'C':
        moveSuccessful = moveDown(&fundationDownA, card);
        break;
      case 'D':
        moveSuccessful = moveDown(&fundationDownB, card);
        break;
      default:
        cout << "Invalid stack." << endl;
        break;
    }

    // Si le mouvement a réussi, on retire la carte de la main du joueur
    if (moveSuccessful) {
      remove(&hand, card);
    } else {
      cout << "Invalid move." << endl;
    }

    // Si la main du joueur est vide, la partie est terminée
    if (hand.size == 0) {
      gameOver = true;
    }
  }

  // Calcul du score final
  int finalScore = score(&hand, &stock);
  cout << "Game over. Finalscore: " << finalScore << ::endl;

  return 0;
}

