#include "Compare.hpp"
#include "HashInventory.hpp"
#include "Inventory.hpp"
#include "Item.hpp"
#include "ItemAVL.hpp"
#include "TreeInventory.hpp"

int main(){
    Item katana("Katana", 5.5, ItemType::WEAPON);
    Item sword("Sword", 5.2, ItemType::WEAPON);

    if(CompareItemName::lessThan(katana, sword)){
        std::cout << "True, katana < sword" << std::endl;
    };
    if(!CompareItemWeight::lessThan(katana, sword)){
        std::cout << "False, 5.5 not less than 5.2" << std::endl;
    };
    if(CompareItemType::equal(katana, sword)){
        std::cout << "True, WEAPON == WEAPON" << std::endl;
    };
    return 0;
}

/*
    To update changes on git:
    git add .                           //stage the changes 
    git commit -m "insert message" 
    git push                            //push changes remotely to git

    To merge changes on submission branch:
    git checkout submission             //switch to submission branch
    git merge main -m "insert message"  //merging main branch changes to submission tracked files
    git push                            //push changes remotely to git
    git checkout main                   //switch back to main branch to make edits
*/