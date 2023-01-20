//v1.8.0
#include "typeDef.h"
#include "functions.h"
#include <iostream>
#include <random>
#include <windows.h>

using namespace std;



void push(List* aList, Element* anElement) {
    // Update of the list size
    aList->size++;

    // Update the next element of the element to be inserted
    anElement->next = aList->first;

    // Update the item at the top of the list
    aList->first = anElement;
}

int top(const List * aList)
{
  // If the list is empty, there is nothing to do
    if (aList->first != nullptr)
    {
      // Otherwise, we return the value of the element at the top of the list
        return aList->first->value;
    } else
    {
        return 0;
    }
};

void pop(List * aList) {
    // If the list is empty, there is nothing to do
    if (aList->size == 0) {
        return;
    }

    // We update the element at the top of the list
    Element * topElement = aList->first;

    // We update the item at the top of the list
    aList->first = topElement->next;

    // We free the memory occupied by the element at the top of the list
    delete topElement;

    // We update the size of the list
    aList->size--;
}



void insert(List * aList, Element * anElement)
{ 
    // Check if the list is empty or if the first value is already the greater value
    if ((aList->size == 0) || aList->first->value >= anElement->value)
    {
        push(aList, anElement);
        return;
    }

    // Loop to compare every values
    Element *current_node = aList->first;
    while (current_node->next != nullptr)
    {
        if (current_node->next->value >= anElement->value)
        {
            anElement->next = current_node->next;
            current_node->next = anElement;
            aList->size++;
            return;
        }
        current_node = current_node->next;
    }

    // anElement->value is the greatest value
    anElement->next = current_node->next;
    current_node->next = anElement;
    aList->size++;
}





void displayList(const List * aList) {
    // We display the size of the list
    Element * currentElement = aList->first;
    while (currentElement != nullptr) {
      // We display the value of the element
        cout << currentElement->value << " ";
        currentElement = currentElement->next;
    }
    cout << endl;
}

void deleteList(List * aList) {
    // We free the memory occupied by each element
    Element * currentElement = aList->first;
    while (currentElement != nullptr) {
        Element * nextElement = currentElement->next;
        // We free the memory occupied by the current element
        delete currentElement;
        currentElement = nextElement;
    }

    // We update the size of the list
    aList->size = 0;
    aList->first = nullptr;
  // We free the memory occupied by the list
    delete aList;

}

void remove(List * aList, const int aValue) {
    // If the list is empty, there is nothing to do
    if (aList->size == 0) {
        return;
    }

    // If the element to remove is at the top of the list, we remove it
    if (aList->first->value == aValue) {
        Element * topElement = aList->first;
        aList->first = topElement->next;
        delete topElement;
        aList->size--;
        return;
    }

    // We search the element to remove
    Element * currentElement = aList->first;
    while (currentElement->next != nullptr && currentElement->next->value != aValue) {
        currentElement = currentElement->next;
    }

    // If the element to remove has been found, we remove it
    if (currentElement->next != nullptr) {
        Element * elementToDelete = currentElement->next;
        currentElement->next = elementToDelete->next;
        delete elementToDelete;
        aList->size--;
    }
}

// Returns the minimum of two integers (aNb1 and aNb2)
int min(const int aNb1, const int aNb2) {
    return aNb1 <= aNb2 ? aNb1 : aNb2;
}

void putACard(List * aList, const int aCard) {
    // Creation of the element to insert
    Element * newElement = new Element;
    newElement->value = aCard;

    // Insertion of the element in the list
    push(aList, newElement);
}


void shuffle(List * aList) {
    // Initialisation of the array of drawn cards
    bool drawnCards[99] = { false };

    //Initialisation of the random number generator
    const int MIN=2, MAX=99;
    random_device rd;
    default_random_engine eng(rd());
    uniform_int_distribution<int> distr(MIN, MAX);

    // Draw of 98 cards aleatory 
    for (int drawIndex = 0; drawIndex < 98; drawIndex++) {
        int card = -1;
        do {
            // Draw of a card
            card = distr(eng);
        } while (drawnCards[card - 2]); // If the card has already been drawn, we draw another card

        // The card has been drawn
        drawnCards[card - 2] = true;

        // Insertion of the card in the list
        putACard(aList, card);
    }
}

void styleCardTop() {
    SetConsoleOutputCP( 65001 );
    cout << " ╭───╮  ╭───╮       ╭───╮   ╭───╮" << endl;
}

void styleCardBot() {
    SetConsoleOutputCP( 65001 );
    cout << " ╰───╯  ╰───╯       ╰───╯   ╰───╯" << endl;
}

// Returns a string with the number of the card and a fixed length
string formatNumber(int number) {
    // Convert the number to a string
    string result = to_string(number);
    if (number < 10) {
        result = "  " + result;
    } else if (number < 100) {
        result = " " + result;
    }
    return result;
}


// Displays the board with the cards in the foundations and in the hand
void displayBoard(const List * aFundationUpA, const List * aFundationUpB, const  List * aFundationDownA, const List * aFundationDownB, const List * aHand) {
    cout << "   A      B     x     C       D" << endl;
    styleCardTop();
    cout << " │" << formatNumber(top(aFundationUpA)) << "│  │" << formatNumber(top(aFundationUpB)) << "│   x   │" << formatNumber(top(aFundationDownA)) << "│   │" << formatNumber(top(aFundationDownB)) << "│" << endl ;
    styleCardBot();
    cout << "Hand: ";
    displayList(aHand);
}


bool moveUp(List * aList, const int aCard) {

    // If the value of the card to insert is greater than or equal to that at the top of the list, the movement is possible
    if (aCard > top(aList) || aCard + 10 == top(aList)) {
        // Creation of a new element from the card to insert
        Element * newElement = new Element;
        newElement->value = aCard;

        // Insertion of the element in the list (stack)
        push(aList, newElement);
        return true;
    }

    // In other cases, the movement is not possible
    return false;
}

bool moveDown(List * aList, const int aCard) {

    // If the value of the card to insert is less than or equal to that at the top of the list, the movement is possible
    if (aCard < top(aList) || aCard - 10 == top(aList) || top(aList) == 0) {
        // Creation of a new element from the card to insert
        Element * newElement = new Element;
        newElement->value = aCard;

        // Insertion of the element in the list (stack)
        push(aList, newElement);
        return true;
    }

    // In other cases, the movement is not possible
    return false;
}

// Asks the user to enter the value of a card and the name of a stack
void play(int & aCard, char & aStack) {
    while (true) {
        cout << "Enter the value of the card to play: ";
        while (!(cin >> aCard))
                {
                    cin.clear();
                    cin.ignore();
                    cout << "Entry error, please retry !" << endl;
                    cout << "Enter the value of the card to play: " << endl;
                }
        if (aCard >= 2 && aCard <= 99) {
            break;
        }
        cout << "Invalid value for card. Please enter a value between 2 and 99." << endl;
    }
    while (true) {
        cout << "Enter the name of the stack (A, B, C, D): ";
        cin >> aStack;
        cout << endl;
        aStack = toupper(aStack);
        if (aStack >= 'A' && aStack <= 'D') {
            break;
        }
        cout << "Invalid stack char. Please enter a character between A and D." << endl;
    }

}

bool isValid(const List * aHand, const int aValue) {
    // We search the card in the hand
    Element * currentElement = aHand->first;
    while (currentElement != nullptr) {
      // If the card has been found, it is valid
        if (currentElement->value == aValue) {
            return true;
        }
        currentElement = currentElement->next;
    }

    // If the card has not been found, it is not valid
    return false;
}

// In function of the char of the stack, the card is moved to the corresponding stack
bool moveSuccessful(List * aFundationUpA,List * aFundationUpB,List * aFundationDownA,List * aFundationDownB, char aStack, int aCard)
{
    switch (aStack) {
    case 'A':
        moveUp(aFundationUpA, aCard);
        break;
    case 'B':
        moveUp(aFundationUpB, aCard);
        break;
    case 'C':
        moveDown(aFundationDownA, aCard);
        break;
    case 'D':
        moveDown(aFundationDownB, aCard);
        break;
    default:
        return false;
        break;
    }
}

void playTurn(List * fundationUpA, List * fundationUpB, List * fundationDownA, List * fundationDownB, List * hands[], int currentPlayer) {
    displayBoard(fundationUpA, fundationUpB, fundationDownA, fundationDownB, hands[currentPlayer]);
    int card;
    char stack;
    play(card, stack);
    if (!isValid(hands[currentPlayer], card)) {
        cout << "Invalid card, please try again." << endl;

    }
    if (!moveSuccessful(fundationUpA, fundationUpB, fundationDownA, fundationDownB,stack,card)) {
        cout << "Unable to move, please try again." << endl;

    }
    remove(hands[currentPlayer], card);

}





bool isGameOver(List * hand, List * fundationUpA, List * fundationUpB, List * fundationDownA, List * fundationDownB)
{
    Element * current = hand->first;
    while (current != NULL) {
      // If the card is valid, the game is not over
        if (current->value > top(fundationUpA) || current->value + 10 == top(fundationUpA) || current->value < top(fundationDownA)
           || current->value - 10 == top(fundationDownA) ||(current->value > top(fundationUpB) 
           || current->value + 10 == top(fundationUpB) || current->value < top(fundationDownB) 
           || current->value - 10 == top(fundationDownB))) {
            return false;
        }
        current = current->next;
    }
    // else, the game is over
    return true;
}

int score(List* players[], List* stock, int numberOfPlayers) {
    int score = stock->size;
    for (int i = 0; i < numberOfPlayers; i++) {
        score += players[i]->size;
    }
    return score;
}



void displayEndScreen(List* players[], List* aStock, int numberOfPlayers) {
    for (int i = 0; i < numberOfPlayers; i++) {
    if (aStock->size == 0 && players[i]->size == 0) {
        cout << "Congratulations, you won!" << endl;
    }}
    if (aStock->size != 0) {
        cout << "You lost, better luck next time! Your score is: " << score(players, aStock, numberOfPlayers) << endl;
    }

}
