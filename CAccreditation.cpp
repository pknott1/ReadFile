#include "CAccreditation.h"
#include "CCard.h"

void CAccreditation::Activate(vector<unique_ptr<CStudent>>& playerTable, vector<unique_ptr<CStudent>>& player2Table, CProfessor& Attacker, CProfessor& professor2) {
    //This goes through the table and reduces everything by 1
    for (int i = 0; i < player2Table.size(); i++) {
        auto& targetCard = player2Table[i];
        targetCard->resilience -= 1;
        cout << this->name1 << this->name2 << " attacks " << targetCard->name1 << targetCard->name2 << " \n";
        //Destroys cards under 0 resilience
        if (targetCard->resilience <= 0) {
            cout << targetCard->name1 << " is defeated\n";
            player2Table.erase(player2Table.begin() + i);
        }
        else {
            cout << targetCard->name1 << targetCard->name2 << "'s resilience is now " << targetCard->resilience << "\n";
        }
    }
    professor2.prestige -= 1;
    cout << "Professor's prestige is now " << professor2.prestige << endl;
}