#include "typeDef.h"
#include "functions.h"
#include <iostream>

using namespace std;



void push(List* aList, Element* anElement) {
  // Mise à jour de la taille de la liste
  aList->size++;

  // Mise à jour de l'élément suivant de l'élément à insérer
  anElement->next = aList->first;

  // Mise à jour de l'élément en tête de la liste
  aList->first = anElement;
}

int top(const List * aList) {
  // Si la liste est vide, on renvoie 0
  if (aList->size == 0) {
    return 0;
  }

  // Sinon, on renvoie la valeur de l'élément en tête de la liste
  return aList->first->value;
}

void pop(List * aList) {
  // Si la liste est vide, il n'y a rien à faire
  if (aList->size == 0) {
    return;
  }

  // Sinon, on récupère l'élément en tête de la liste
  Element * topElement = aList->first;

  // On met à jour l'élément en tête de la liste
  aList->first = topElement->next;

  // On libère la mémoire de l'élément en tête de la liste
  delete topElement;

  // On met à jour la taille de la liste
  aList->size--;
}

void insert(List * aList, Element * anElement) {
  // Si la liste est vide, on insère l'élément en tête de la liste
  if (aList->size == 0) {
    aList->first = anElement;
    aList->size++;
    return;
  }

  // Si la valeur de l'élément à insérer est inférieure ou égale à la valeur de l'élément en tête de la liste, on insère l'élément en tête de la liste
  if (anElement->value <= aList->first->value) {
    anElement->next = aList->first;
    aList->first = anElement;
    aList->size++;
    return;
  }

  // Sinon, on parcourt la liste à la recherche de l'élément avant lequel insérer l'élément à insérer
  Element * currentElement = aList->first;
  while (currentElement->next != nullptr && currentElement->next->value < anElement->value) {
    currentElement = currentElement->next;
  }

  // On insère l'élément à insérer
  anElement->next = currentElement->next;
  currentElement->next = anElement;

  // On met à jour la taille de la liste
  aList->size++;
}

void displayList(const List * aList) {
  // On affiche la taille de la liste
  cout << "List size: " << aList->size << endl;

  // On parcourt la liste et on affiche chaque élément
  Element * currentElement = aList->first;
  while (currentElement != nullptr) {
    cout << currentElement->value << " ";
    currentElement = currentElement->next;
  }
  cout << endl;
}

void deleteList(List * aList) {
  // On parcourt la liste et on libère la mémoire de chaque élément
  Element * currentElement = aList->first;
  while (currentElement != nullptr) {
    Element * nextElement = currentElement->next;
    delete currentElement;
    currentElement = nextElement;
  }

  // On met à jour la taille de la liste
  aList->size = 0;
  aList->first = nullptr;
}

void remove(List * aList, const int aValue) {
  // Si la liste est vide, il n'y a rien à faire
  if (aList->size == 0) {
    return;
  }

  // Si l'élément en tête de la liste est à supprimer, on met à jour l'élément en tête de la liste et on libère la mémoire de l'élément en tête de la liste
  if (aList->first->value == aValue) {
    Element * topElement = aList->first;
    aList->first = topElement->next;
    delete topElement;
    aList->size--;
    return;
  }

  // Sinon, on parcourt la liste à la recherche de l'élément à supprimer
  Element * currentElement = aList->first;
  while (currentElement->next != nullptr && currentElement->next->value != aValue) {
    currentElement = currentElement->next;
  }

  // Si l'élément à supprimer a été trouvé, on le supprime
  if (currentElement->next != nullptr) {
    Element * elementToDelete = currentElement->next;
    currentElement->next = elementToDelete->next;
    delete elementToDelete;
    aList->size--;
  }
}

//Cette fonction renvoie le minimum de aNb1 et aNb2, ou aNb1 si les deux sont égaux.
// Elle utilise l'opérateur ?: pour renvoyer l'un ou l'autre des deux nombres 
//en fonction de la valeur de la condition.
int min(const int aNb1, const int aNb2) {
  return aNb1 <= aNb2 ? aNb1 : aNb2;
}

void putACard(List * aList, const int aCard) {
  // Création d'un nouvel élément à partir de la carte à insérer
  Element * newElement = new Element;
  newElement->value = aCard;

  // Insertion de l'élément dans la liste (pile)
  push(aList, newElement);
}


void shuffle(List * aList) {
  // Tableau de booléens pour marquer les cartes déjà tirées
  bool drawnCards[99] = { false };

  // Tirage aléatoire des cartes et insertion dans la liste (pile)
  for (int drawIndex = 0; drawIndex < 98; drawIndex++) {
    int card = -1;
    do {
      // Tirage aléatoire d'une carte
      card = rand() % 99 + 2;
    } while (drawnCards[card - 2]); // Tant que la carte a déjà été tirée, on recommence

    // Marque de la carte comme tirée
    drawnCards[card - 2] = true;

    // Insertion de la carte dans la liste (pile)
    putACard(aList, card);
  }
}

void displayBoard(const List * aFundationUpA, const List * aFundationUpB, const  List * aFundationDownA, const List * aFundationDownB, const List * aHand) {
  // Affichage de la colonne de fondations du haut (A)
  std::cout << "Fundations (up, A): ";
  displayList(aFundationUpA);

  // Affichage de la colonne de fondations du haut (B)
  std::cout << "Fundations (up, B): ";
  displayList(aFundationUpB);

  // Affichage de la colonne de fondations du bas (A)
  std::cout << "Fundations (down, A): ";
  displayList(aFundationDownA);

  // Affichage de la colonne de fondations du bas (B)
  std::cout << "Fundations (down, B): ";
  displayList(aFundationDownB);

  // Affichage de la main du joueur
  std::cout << "Hand: ";
  displayList(aHand);
}

bool moveUp(List * aList, const int aCard) {
  // Si la liste est vide ou si la valeur de la carte à insérer est inférieure à 10 de celle en tête de la liste, le mouvement n'est pas possible
  if (aList->size == 0 || aCard + 10 < top(aList)) {
    return false;
  }

  // Si la valeur de la carte à insérer est supérieure à celle en tête de la liste, le mouvement est possible
  if (aCard > top(aList)) {
    // Création d'un nouvel élément à partir de la carte à insérer
    Element * newElement = new Element;
    newElement->value = aCard;

    // Insertion de l'élément dans la liste (pile)
    push(aList, newElement);
    return true;
  }

  // Dans les autres cas, le mouvement n'est pas possible
  return false;
}

bool moveDown(List * aList, const int aCard) {
  // Si la liste est vide ou si la valeur de la carte à insérer est supérieure de 10 à celle en tête de la liste, le mouvement n'est pas possible
  if (aList->size == 0 || aCard - 10 > top(aList)) {
    return false;
  }

  // Si la valeur de la carte à insérer est inférieure à celle en tête de la liste, le mouvement est possible
  if (aCard < top(aList)) {
    // Création d'un nouvel élément à partir de la carte à insérer
    Element * newElement = new Element;
    newElement->value = aCard;

    // Insertion de l'élément dans la liste (pile)
    push(aList, newElement);
    return true;
  }

  // Dans les autres cas, le mouvement n'est pas possible
  return false;
}

//Cette fonction demande à un joueur de jouer une carte en lui demandant d'abord de choisir la valeur de la carte
// à jouer et ensuite le nom de la colonne de fondations dans laquelle jouer la carte. Elle utilise les entrées 
//standard pour récupérer la valeur et le nom choisis par le joueur.
void play(int & aCard, char & aStack) {
  cout << "Choose the value of the card to play: ";
  cin >> aCard;
  cout << "Choose the name of the stack (A, B, C, D): ";
  cin >> aStack;
}

bool isValid(const List * aHand, const int aValue) {
  // Parcours de la main pour vérifier si la carte est présente
  Element * currentElement = aHand->first;
  while (currentElement != nullptr) {
    if (currentElement->value == aValue) {
      return true;
    }
    currentElement = currentElement->next;
  }

  // Si la carte n'a pas été trouvée, elle n'est pas valide
  return false;
}

int score(const List* aHand, const List* aStock) {
  // Somme des valeurs des cartes de la main et du stock
  int sum = 0;

  // Parcours de la main et ajout des valeurs des cartes à la somme
  Element * currentElement = aHand->first;
  while (currentElement != nullptr) {
    sum += currentElement->value;
    currentElement = currentElement->next;
  }

  // Parcours du stock et ajout des valeurs des cartes à la somme
  currentElement = aStock->first;
  while (currentElement != nullptr) {
    sum += currentElement->value;
    currentElement = currentElement->next;
  }

  // Renvoi de la somme
  return sum;
}

