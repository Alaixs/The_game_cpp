#include "typeDef.h"
#include "functions.h"
#include <iostream>
#include <random>

using namespace std;



void push(List* aList, Element* anElement) {
  // Mise à jour de la taille de la liste
  aList->size++;

  // Mise à jour de l'élément suivant de l'élément à insérer
  anElement->next = aList->first;

  // Mise à jour de l'élément en tête de la liste
  aList->first = anElement;
}

int top(const List * aList)
{
    if (aList->first != nullptr)
    {
        return aList->first->value;
    } else
    {
        return 0;
    }
};

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

  delete aList;

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

    //Initialisation de la génération de nombres aléatoires
    const int MIN=2, MAX=99;
    random_device rd;
    default_random_engine eng(rd());
    uniform_int_distribution<int> distr(MIN, MAX);

  // Tirage aléatoire des cartes et insertion dans la liste (pile)
  for (int drawIndex = 0; drawIndex < 98; drawIndex++) {
    int card = -1;
    do {
      // Tirage aléatoire d'une carte
      card = distr(eng);
    } while (drawnCards[card - 2]); // Tant que la carte a déjà été tirée, on recommence

    // Marque de la carte comme tirée
    drawnCards[card - 2] = true;

    // Insertion de la carte dans la liste (pile)
    putACard(aList, card);
  }
}


void displayBoard(const List * aFundationUpA, const List * aFundationUpB, const  List * aFundationDownA, const List * aFundationDownB, const List * aHand) {
cout << "A  B  x  C   D" << endl;
cout << "1  1  x 100 100" << endl;
cout << top(aFundationUpA) << "  " << top(aFundationUpB) << "  x " << top(aFundationDownA) << "  " << top(aFundationDownB) << endl << endl;
cout << "Hand: ";
displayList(aHand);
}

bool moveUp(List * aList, const int aCard) {


  // Si la valeur de la carte à insérer est supérieure à celle en tête de la liste, le mouvement est possible
if (aCard > top(aList) || aCard + 10 == top(aList)) {
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

  // Si la valeur de la carte à insérer est inférieure à celle en tête de la liste, le mouvement est possible
  if (aCard < top(aList) || aCard - 10 == top(aList) || top(aList) == 0) {
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
  while (true) {
    cout << "Enter the value of the card to play: ";
    cin >> aCard;
    if (aCard >= 2 && aCard <= 99) {
      break;
    }
    cout << "Invalid value for card. Please enter a value between 2 and 99." << endl;
  }
  while (true) {
    cout << "Enter the name of the stack (A, B, C, D): ";
    cin >> aStack;
    toupper(aStack);
    if (aStack >= 'A' && aStack <= 'D') {
      break;
    }
    cout << "Invalid stack char. Please enter a character between A and D." << endl;
  }

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

bool moveSuccessful(List * aFundationUpA,List * aFundationUpB,List * aFundationDownA,List * aFundationDownB,List * aHand, char aStack, int aCard) 
{
        bool moveSuccessful;
        switch (aStack) {
            case 'A':
                moveSuccessful = moveUp(aFundationUpA, aCard);
                break;
            case 'B':
                moveSuccessful = moveUp
                (aFundationUpB, aCard);
                break;
            case 'C':
                moveSuccessful = moveDown(aFundationDownA, aCard);
                break;
            case 'D':
                moveSuccessful = moveDown(aFundationDownB, aCard);
                break;
            default:
                return false;
                break;
    }
}

bool isGameOver(List * hand, List * fundationUpA, List * fundationUpB, List * fundationDownA, List * fundationDownB)
{
        Element * current = hand->first;
        while (current != NULL) {
            if (current->value > top(fundationUpA) || current->value + 10 == top(fundationUpA) || current->value < top(fundationDownA) || current->value - 10 == top(fundationDownA) ||(current->value > top(fundationUpB) || current->value + 10 == top(fundationUpB) || current->value < top(fundationDownB) || current->value - 10 == top(fundationDownB) )) {
                return false;
            }
            current = current->next;
        }
        return true;
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



int calculateScore(List* hand, List* stock) {
    int score = 0;
    // Parcours la main du joueur et le stock et additionne les valeurs des cartes
    Element* currentElement = hand->first;
    while (currentElement != nullptr) {
        score += currentElement->value;
        currentElement = currentElement->next;
    }
    currentElement = stock->first;
    while (currentElement != nullptr) {
        score += currentElement->value;
        currentElement = currentElement->next;
    }
    return score;
}
