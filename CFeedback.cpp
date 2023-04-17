#include "CFeedback.h"
void CFeedback::Activate(vector<unique_ptr<CStudent>>& playerTable, vector<unique_ptr<CStudent>>& player2Table, CProfessor& Attacker, CProfessor& professor2) {

    //This gains the total sum of all possible targets and attacks whichever card/player is targeted
    int targetIndex = Random(playerTable.size() + player2Table.size() + 2);
    if (targetIndex == playerTable.size() + player2Table.size()) {
        professor2.prestige -= power;
        cout << professor2.name << "'s prestige is now " << professor2.prestige << "\n";
    }
    //This heals an ally student card
    else if (targetIndex == playerTable.size() + player2Table.size() + 1) {
        Attacker.prestige += boost;
        cout << Attacker.name << "'s prestige is now " << Attacker.prestige << "\n";
    }
    //This damages an enemy student card
    else if (targetIndex >= playerTable.size()) {
        auto& targetCard = player2Table[targetIndex - playerTable.size()];
        targetCard->resilience -= power;
        if (targetCard->resilience <= 0) {
            cout << targetCard->name1 << " is defeated\n";
            player2Table.erase(player2Table.begin() + (targetIndex - playerTable.size()));
        }
        else {
            cout << targetCard->name1 << targetCard->name2 << "'s resilience is now " << targetCard->resilience << "\n";
        }
    }
    // This increase the resilience of the target card by the boost of the attacker card
    else {
        auto& targetCard = playerTable[targetIndex];
        targetCard->resilience += boost;
        cout << targetCard->name1 << targetCard->name2 << "'s resilience is now " << targetCard->resilience << "\n";
    }
}