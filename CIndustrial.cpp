#include "CIndustrial.h"
void CIndustrial::Activate(vector<unique_ptr<CStudent>>& playerTable, vector<unique_ptr<CStudent>>& player2Table, CProfessor& Attacker, CProfessor& professor2) {
    CStudent::Activate(playerTable, player2Table, Attacker, professor2);


    // This increase the resilience of the target card by the boost of the attacker card
    this->resilience += boost;

    // Output the effect of the attack
    cout << this->name1 << this->name2 << " boosts " << "it's resilience by " << boost << ". ";
    cout << this->name1 << this->name2 << "'s resilience is now " << this->resilience << "\n";
}