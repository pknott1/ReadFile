#include "CStudent.h"

void CStudent::Play(vector<unique_ptr<CStudent>>& playerTable) {
    AddToTable(playerTable);
    OutputTable(playerTable);
}

void CStudent::Activate(vector<unique_ptr<CStudent>>& playerTable, vector<unique_ptr<CStudent>>& player2Table, CProfessor& professor1, CProfessor& professor2) {
    //This generates the random number for the card to attack
    int attackerIndex = Random(playerTable.size());
    int targetIndex = Random(player2Table.size());
    //This goes through the table and attacks the target card
    for (int i = 0; i < playerTable.size(); i++) {
        auto& attackerCard = playerTable[(playerTable.size() - i) - 1];
        //Or attacks the professor
        if (player2Table.empty()) {
            AttackProfessor(attackerCard, professor2);
        }
        else {
            AttackStudent(attackerCard, player2Table[targetIndex]);
            RemoveDefeatedCards(player2Table, targetIndex);
        }
    }
}

void CStudent::AddToTable(vector<unique_ptr<CStudent>>& playerTable) {
    if (this) {
        playerTable.push_back(make_unique<CStudent>(*this));
    }
    else {
        cout << "Cannot add non-student card to bench.\n";
    }
}

void CStudent::OutputTable(vector<unique_ptr<CStudent>>& playerTable) {
    if (playerTable.size() != 0) {
        cout << "Cards on the table: ";
        for (int i = 0; i < playerTable.size(); i++) {
            auto& targetCard = playerTable[(playerTable.size() - i) - 1];
            cout << targetCard->name1 << " " << targetCard->name2 << " (" << targetCard->resilience << ") , ";
        }
        cout << endl;
    }
}

void CStudent::AttackProfessor(unique_ptr<CStudent>& attackerCard, CProfessor& professor) {
    // Subtracts the power from the prestige
    int attackPower = attackerCard->power;
    professor.prestige -= attackPower;

    // Output the attack result
    cout << attackerCard->name1 << " attacks " << professor.name << ". ";
    cout << professor.name << "'s prestige is now " << professor.prestige << "\n";
}

void CStudent::AttackStudent(unique_ptr<CStudent>& attackerCard, unique_ptr<CStudent>& targetCard) {
    // Check if the target card is a student or the professor
    if (targetCard) {
        // This reduces the target student's resilience by the power of the attacker student
        int attackPower = attackerCard->power;
        targetCard->resilience -= attackPower;

        // Output the attack result
        cout << attackerCard->name1 << attackerCard->name2 << " attacks " << targetCard->name1 << targetCard->name2 << ". ";
        if (targetCard->resilience <= 0) {
            cout << targetCard->name1 << " is defeated\n";
        }
        else {
            cout << targetCard->name1 << targetCard->name2 << "'s resilience is now " << targetCard->resilience << "\n";
        }
    }
}

void CStudent::RemoveDefeatedCards(vector<unique_ptr<CStudent>>& player2Table, int targetIndex) {
    //This removes the cards below 0 resilience
    if (player2Table[targetIndex]->resilience <= 0) {
        cout << player2Table[targetIndex]->name1 << " is defeated\n";
        player2Table.erase(player2Table.begin() + targetIndex);
    }
}