#include <iostream>
#include "CCard.h"
#include "CStudent.h"
#include "CEasy.h"
#include "CFeedback.h"
#include "CGraduate.h"
#include "CIndustrial.h"
#include "CMitigating.h"
#include "CPass.h"
#include "CPlagiarism.h"
#include "CResearch.h"
#include "CSerial.h"
#include "CAccreditation.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//This is the random function given in the assignment brief
int Random(int max) {
    return int(float(rand()) / (RAND_MAX + 1) * float(max));
}

//This reads in the seed from the text file given and returns the value in the file
int readSeed() {
    ifstream inFile;
    int seed;
    inFile.open("seed.txt");
    //This loop reads each line until it reaches the end of the file
    while (inFile) {
        if (inFile.eof()) {
            break;
        }
        inFile >> seed;
    }

    return seed;
}
//This opens the files containing the decks and stores them in a vector of unique pointers.
void readDeck(vector < unique_ptr < CCard >>& playerDeck, string fileName) {

    // Open the file containing player 1's deck
    ifstream inFile;
    inFile.open(fileName);
    vector < unique_ptr < CCard >> player1Deck;
    while (inFile) {
        auto tempCard = make_unique < CCard >();
        tempCard->readCardType(inFile);
        if (inFile.eof()) {
            break;
        }
        //This reads in all of the card types and accounts for the different properties they might have.
        switch (tempCard->type) {
        //This reads in the student cards that all have a type of 1.
        case 1: {
            // A new unique pointer is created for the student card
            auto studentCard = make_unique < CStudent >();
            studentCard->type = tempCard->type;
            //Student cards have all the properties of CCard so it calls the read function form the CCard class
            studentCard->readCardData(inFile);
            //It has an additonal property so this is also read
            inFile >> studentCard->resilience;
            //Then it's added to the deck
            player1Deck.push_back(move(studentCard));
            break;
        }
        case 2: {
            auto plagiaristCard = make_unique < CPlagiarism >();
            plagiaristCard->type = tempCard->type;
            plagiaristCard->readCardData(inFile);
            player1Deck.push_back(move(plagiaristCard));
            break;
        }
        case 3: {
            auto accredationCard = make_unique < CAccreditation >();
            accredationCard->type = tempCard->type;
            accredationCard->readCardData(inFile);
            player1Deck.push_back(move(accredationCard));
            break;
        }
        case 4: {
            auto feedbackCard = make_unique < CFeedback >();
            feedbackCard->type = tempCard->type;
            feedbackCard->readCardData(inFile);
            inFile >> feedbackCard->boost;
            player1Deck.push_back(move(feedbackCard));
            break;
        }
        case 5: {
            auto industrialCard = make_unique < CIndustrial >();
            industrialCard->type = tempCard->type;
            industrialCard->readCardData(inFile);
            inFile >> industrialCard->resilience;
            inFile >> industrialCard->boost;
            player1Deck.push_back(move(industrialCard));
            break;
        }
        case 6: {
            auto passCard = make_unique < CPass >();
            passCard->type = tempCard->type;
            passCard->readCardData(inFile);
            inFile >> passCard->resilience;
            inFile >> passCard->powerIncrement;
            player1Deck.push_back(move(passCard));
            break;
        }
        case 7: {
            auto researchCard = make_unique < CResearch >();
            researchCard->type = tempCard->type;
            researchCard->readCardData(inFile);
            player1Deck.push_back(move(researchCard));
            break;
        }
        case 8: {
            auto mitigatingCard = make_unique < CMitigating >();
            mitigatingCard->type = tempCard->type;
            mitigatingCard->readCardData(inFile);
            player1Deck.push_back(move(mitigatingCard));
            break;
        }
        case 9: {
            auto easyCard = make_unique < CEasy >();
            easyCard->type = tempCard->type;
            easyCard->readCardData(inFile);
            inFile >> easyCard->resilience;
            inFile >> easyCard->powerIncrement;
            player1Deck.push_back(move(easyCard));
            break;
        }
        case 10: {
            auto SerialCard = make_unique < CSerial >();
            SerialCard->type = tempCard->type;
            SerialCard->readCardData(inFile);
            inFile >> SerialCard->resilience;
            player1Deck.push_back(move(SerialCard));
            break;
        }
        case 11: {
            auto GraduateCard = make_unique < CGraduate >();
            GraduateCard->type = tempCard->type;
            GraduateCard->readCardData(inFile);
            inFile >> GraduateCard->resilience;
            inFile >> GraduateCard->boost;
            player1Deck.push_back(move(GraduateCard));
            break;
        }

        default:
            cout << "Unknown card type: " << tempCard->type << endl;
            break;
        }
    }

    inFile.close();

}
//This calls all the functions to read the files to set the game up and call the actual game function
void initialiseGame() {
    int seed = readSeed();
    srand(seed);
    vector < unique_ptr < CCard >> player1Deck;
    vector < unique_ptr < CCard >> player2Deck;
    readDeck(player1Deck, "plagiarist.txt");
    readDeck(player2Deck, "piffle-paper.txt");
    playGame(player1Deck, player2Deck);
}
//This  allows the player to play a random card from their hand
void playCard(vector < unique_ptr < CCard >>& hand, vector < unique_ptr < CStudent >>& table, vector < unique_ptr < CStudent >>& table2, CProfessor& current, CProfessor& opponent) {
    int randomCard = Random(hand.size());
    //This moves a random card from the hand to be activated/moved to the bench
    unique_ptr < CCard > card = move(hand[randomCard]);
    cout << current.name << " plays " << card->name1 << card->name2 << "\n";
    //All student cards will be played onto the table
    card->Play(table);
    hand.erase(hand.begin() + randomCard);
    //An effect of a card will activate and in the case of the student card it will attack the opposing player
    card->Activate(table, table2, current, opponent);
}
//This allows the player to draw a card from the deck in the order it was read from the file
void drawCard(vector < unique_ptr < CCard >>& deck, vector < unique_ptr < CCard >>& hand,
    const string& playerName) {
    //This moves a card from the deck to the hand
    hand.push_back(move(deck[0]));
    cout << playerName << " draws " << hand.back()->name1 << hand.back()->name2 << "\n";
    deck.erase(deck.begin());
}
//This checks to see if the game has ended or if a player has zero health
void checkGameOver(CProfessor& professor1, CProfessor& professor2) {
    //This outputs the winner of the game based on whoever has 0 health
    if (professor1.prestige <= 0 || professor2.prestige <= 0) {
        cout << "Game over!\n";
        cout << professor1.name << "'s prestige is " << professor1.prestige << "\n";
        cout << professor2.name << "'s prestige is " << professor2.prestige << "\n";
        if (professor1.prestige > professor2.prestige) {
            cout << "Player 1 wins!\n";
        }
        else if (professor2.prestige > professor1.prestige) {
            cout << "Player 2 wins!\n";
        }
        else {
            cout << "It's a tie!\n";
        }
        exit(0);
    }
}
//This starts the game. All the variables for the game are declared here and these variables are used to call all the other functions.
int playGame(vector < unique_ptr < CCard >>& player1Deck, vector < unique_ptr < CCard >>& player2Deck) {
    CProfessor professor1 = {
      "Plagiarist",
      30
    };
    CProfessor professor2 = {
      "Piffle-Paper",
      30
    };
    vector < unique_ptr < CCard >> player1Hand;
    vector < unique_ptr < CCard >> player2Hand;
    vector < unique_ptr < CStudent >> player1Table;
    vector < unique_ptr < CStudent >> player2Table;

    cout << "Welcome to U-Can’t. Let the winnowing begin...\n";

    drawCard(player1Deck, player1Hand, "Player 1");
    drawCard(player2Deck, player2Hand, "Player 2");

    //Each round will consist of both players taking a turn, which they will draw a card and play it. The card will either attack/activate it's effect.

    for (int round = 1; round <= 30; round++) {
        cout << "Round " << round << "\n";

        // Player 1's turn
        drawCard(player1Deck, player1Hand, "Player 1");
        playCard(player1Hand, player1Table, player2Table, professor1, professor2);
        checkGameOver(professor1, professor2);

        // Player 2's turn
        drawCard(player2Deck, player2Hand, "Player 2");
        playCard(player2Hand, player2Table, player1Table, professor2, professor1);
        checkGameOver(professor1, professor2);
    }

    return 0;
}

int main() {

    initialiseGame();

};