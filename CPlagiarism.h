#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "CCard.h"



class CPlagiarism : public CCard {
public:
    void Activate(vector<unique_ptr<CStudent>>& playerTable, vector<unique_ptr<CStudent>>& player2Table, CProfessor& Attacker, CProfessor& professor2) override {
        int targetIndex = Random(player2Table.size());
        if (targetIndex > player2Table.size() - 1) {
            professor2.prestige -= 3;

        }
        else
        {
            auto& targetCard = player2Table[targetIndex];
            targetCard->resilience -= 3;
            if (targetCard->resilience <= 0) {
                cout << targetCard->name1 << " is defeated\n";
                player2Table.erase(player2Table.begin() + targetIndex);
            }
            else {
                cout << targetCard->name1 << targetCard->name2 << "'s resilience is now " << targetCard->resilience << "\n";
            }
        }

    }
};