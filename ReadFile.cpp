#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int Random(int max)
{
    return int(float(rand()) / (RAND_MAX + 1) * float(max));
}

struct SProfessor {
public:
    string name;
    int prestige;
};

class CStudent;

class CCard {
public:
    int type;
    string name1;
    string name2;
    int power;

    virtual ~CCard() {}

    virtual void readCardType(ifstream& inFile) {
        inFile >> type;
    }

    virtual void readCardData(ifstream& inFile) {
        inFile >> name1 >> name2 >> power;
    }

    virtual void Play(vector<unique_ptr<CStudent>>& playerTable) {

    }

    virtual void Activate() {

    }
};

class CStudent : public CCard {
public:
    int resilience;

    void Play(vector<unique_ptr<CStudent>>& playerTable) {
        cout << "Player plays " << this->name1 << this->name2 << "\n";
        if (this) {
            playerTable.push_back(make_unique<CStudent>(*this));
        }
        else {
            cout << "Cannot add non-student card to bench.\n";
        }
        cout << playerTable.size() << endl;
    }
};


    void BenchActivate(vector<unique_ptr<CStudent>>& playerTable, vector<unique_ptr<CStudent>>& player2Table, SProfessor& professor2) {
        int attackerIndex = Random(playerTable.size());
        int targetIndex = Random(player2Table.size());
        for (int i = 0; i < playerTable.size(); i++) {
            auto& attackerCard = playerTable[(playerTable.size() - i) - 1];
            if (player2Table.empty()) {
                int attackPower = attackerCard->power;
                professor2.prestige -= attackPower;

                // Output the attack result
                cout << attackerCard->name1 << " attacks " << professor2.name << ". ";
                cout << professor2.name << "'s prestige is now " << professor2.prestige << "\n";
            }
            else
            {
                auto& targetCard = player2Table[targetIndex];

                // Check if the target card is a student or the professor
                if (targetCard) {
                    // Reduce the target student's resilience by the power of the attacker student
                    int attackPower = attackerCard->power;
                    targetCard->resilience -= attackPower;

                    // Output the attack result
                    cout << attackerCard->name1 << attackerCard->name2 << " attacks " << targetCard->name1 << targetCard->name2 << ". ";
                    if (targetCard->resilience <= 0) {
                        cout << targetCard->name1 << " is defeated\n";
                        player2Table.erase(player2Table.begin() + targetIndex);
                    }
                    else {
                        cout << targetCard->name1 << targetCard->name2 << "'s resilience is now " << targetCard->resilience << "\n";
                    }
                }

            }



        }

        

    };

    class CPlagiarism : public CCard {
    public:
        virtual void Activate() override {

        }
    };



    class CAccreditation : public CCard {
    public:
        virtual void Activate() override {
        }
    };





    int main() {
        // Open the file containing player 1's deck
        ifstream inFile;
        inFile.open("plagiarist.txt");

        // Gives the player a 30 card deck 

        vector<unique_ptr<CCard>> player1Deck;
        while (inFile) {
            auto tempCard = make_unique<CCard>();
            tempCard->readCardType(inFile);
            if (inFile.eof()) {
                break;
            }

            switch (tempCard->type) {
            case 1: {
                auto studentCard = make_unique<CStudent>();
                studentCard->type = tempCard->type;
                studentCard->readCardData(inFile);
                inFile >> studentCard->resilience;
                player1Deck.push_back(move(studentCard));

                break;
            }

                  // Add cases for other card types as needed
            default:
                cout << "Unknown card type: " << tempCard->type << endl;
                break;
            }
        }

        inFile.close();

        cout << "player1Deck size: " << player1Deck.size() << endl;

        // Open the file containing player 2's deck
        inFile.open("piffle-paper.txt");
        // Gives player 2 a 30 card deck
        vector<unique_ptr<CCard>> player2Deck;
        while (inFile) {
            auto tempCard = make_unique<CCard>();
            tempCard->readCardType(inFile);
            if (inFile.eof()) {
                break;
            }

            switch (tempCard->type) {
            case 1: {
                auto studentCard = make_unique<CStudent>();
                studentCard->type = tempCard->type;
                studentCard->readCardData(inFile);
                inFile >> studentCard->resilience;
                player2Deck.push_back(move(studentCard));
                break;
            }
                  // Add cases for other card types as needed
            default:
                cout << "Unknown card type: " << tempCard->type << endl;
                break;
            }
        }

        inFile.close();

        cout << "player2Deck size: " << player2Deck.size() << endl;

        //This gives the professors a name and prestige value for the game
        SProfessor professor1 = { "Plagiarist", 30 };
        SProfessor professor2 = { "Piffle-Paper", 30 };
        //This gives the player a card before the game starts
        vector<unique_ptr<CCard>> player1Hand;
        player1Hand.push_back(move(player1Deck[0]));
        cout << "Player 1 draws " << player1Hand[0]->name1 << player1Hand[0]->name2 << "\n";
        player1Deck.erase(player1Deck.begin());


        vector<unique_ptr<CCard>> player2Hand;
        player2Hand.push_back(move(player2Deck[0]));
        cout << "Player 2 draws " << player2Hand[0]->name1 << player2Hand[0]->name2 << "\n";
        player2Deck.erase(player2Deck.begin());


        vector<unique_ptr<CStudent>> player1Table;
        vector<unique_ptr<CStudent>> player2Table;

        // The game begins in this section
        cout << "Welcome to U-Can’t. Let the winnowing begin...\n";

        // Displays the round counter for each round
        for (int round = 1; round <= 30; round++) {
            cout << "Round " << round << "\n";

            // This lets Player 1 draw a card
            player1Hand.push_back(move(player1Deck[0]));
            cout << "Player 1 draws " << player1Hand[1]->name1 << player1Hand[1]->name2 << "\n";
            cout << "player1Hand size: " << player1Hand.size() << endl;
            player1Deck.erase(player1Deck.begin());

            int randomCard;

            // This lets Player 1 choose a card randomly from their hand and play it
            randomCard = Random(player1Hand.size());
            unique_ptr<CCard> player1Card = move(player1Hand[randomCard]);
            player1Card->Play(player1Table);
            player1Hand.erase(player1Hand.begin() + randomCard);
            cout << "player1Hand size: " << player1Hand.size() << endl;
            BenchActivate(player1Table, player2Table, professor2);






            // This lets Player 2 draw a card
            player2Hand.push_back(move(player2Deck[1]));
            cout << "Player 2 draws " << player2Hand[1]->name1 << player2Hand[1]->name2 << "\n";
            cout << "player2Hand size: " << player2Hand.size() << endl;
            player2Deck.erase(player2Deck.begin());

            // This lets Player 2 choose a card randomly from their hand and play it
            randomCard = Random(player2Hand.size());
            unique_ptr<CCard> player2Card = move(player2Hand[randomCard]);
            cout << "Player 2 plays " << player2Card->name1 << player2Card->name2 << "\n";
            player2Card->Play(player2Table);
            player2Hand.erase(player2Hand.begin() + randomCard);
            cout << "player2Hand size: " << player2Hand.size() << endl;
            BenchActivate(player2Table, player1Table, professor1);
            // This checks if PLayer 1 has lost
            if (professor1.prestige <= 0) {
                cout << "Game over!\n";
                cout << professor1.name << "'s prestige is" << professor1.prestige << "\n";
                cout << professor2.name << "'s prestige is" << professor2.prestige << "\n";
                cout << "Player 1 wins!\n";
                return 0;
            }
            // This checks if PLayer 2 has lost
            else if (professor2.prestige <= 0) {
                cout << "Game over!\n";
                cout << professor1.name << "'s prestige is" << professor1.prestige << "\n";
                cout << professor2.name << "'s prestige is" << professor2.prestige << "\n";
                cout << "Player 2 wins!\n";
                return 0;
            }












        }



        cout << "Game over!\n";
        cout << professor1.name << "'s prestige is " << professor1.prestige << "\n";
        cout << professor2.name << "'s prestige is " << professor2.prestige << "\n";
        if (professor1.prestige > professor2.prestige) {
            cout << "Player 1 wins!\n";
            return 0;
        }
        else if (professor2.prestige > professor1.prestige) {
            cout << "Player 2 wins!\n";
            return 0;
        }
        else {
            cout << "It's a tie!\n";
            return 0;
        }


    }

