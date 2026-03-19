#include "HashInventory.hpp"

/**
 * @brief Default constructor for the Inventory template class.
 *
 * Initializes an empty inventory with no items, no equipped item,
 * and zero total weight.
 *
 * @tparam Comparator The comparison class for querying items
 */
template <class Comparator>
Inventory<Comparator, std::unordered_set<Item>>::Inventory() : 
    items_(),
    equipped_(nullptr),
    weight_(0.0)
{}

/**
 * @brief Retrieves the value stored in `equipped_`
 * @return The Item pointer stored in `equipped_`
 */
template <class Comparator>
Item* Inventory<Comparator, std::unordered_set<Item>>::getEquipped() const
{
    return equipped_;
}

/**
 * @brief Equips a new item.
 * @param itemToEquip A pointer to the item to equip.
 * @post Updates `equipped` to the specified item
 * without deallocating the original.
 */
template <class Comparator>
void Inventory<Comparator, std::unordered_set<Item>>::equip(Item* itemToEquip)
{
    equipped_ = itemToEquip; //without deallocaiting the original ...
}

/**
 * @brief Discards the currently equipped item.
 * @post Deallocates the item pointed to by `equipped`
 * and sets `equipped` to nullptr, if `equipped` is not nullptr already.
 */
template <class Comparator>
void Inventory<Comparator, std::unordered_set<Item>>::discardEquipped()
{
    if(equipped_ != nullptr){
        delete equipped_;
        equipped_ = nullptr;
    }
}

/**
 * @brief Retrieves the value stored in `weight_`
 * @return The float value stored in `weight_`
 */
template <class Comparator>
float Inventory<Comparator, std::unordered_set<Item>>::getWeight() const
{
    return weight_;
}

/**
 * @brief Retrieves the size of items_
 */
template <class Comparator>
size_t
Inventory<Comparator, std::unordered_set<Item>>::size() const
{
    return items_.size();
}

/**
 * @brief Retrieves a copy of the container holding inventory items.
 *
 * @return Container of items in the inventory
 */
template <class Comparator>
std::unordered_set<Item>
Inventory<Comparator, std::unordered_set<Item>>::getItems() const
{
    std::unordered_set<Item> copy(items_); //initialized with items_ container 
    return copy;
    //can just do return items_ ? why? T*****T

    //essentially what the copy constructor is doing w/above initialization
    /* 
        for(auto x : items_){
            copy.insert(x); 
        }
    */
}

/**
 * @brief Attempts to add a new item to the inventory.
 *
 * @param target Item to be added to the inventory
 * @return true if the item was successfully added, false if an item
 *         with the same name already exists
 * @post Updates the weight_ member to reflect the new Item pickup
 */
template <class Comparator>
bool Inventory<Comparator, std::unordered_set<Item>>::pickup(const Item& target)
{
    //O(1) operation: 
    auto iter = items_.find(target);
    if(iter != items_.end()){
        return false; //iterator didn't reach the end because it found a match
    }

    if((items_.insert(target)).second){ //insert() returns a pair<iterator, bool>
        weight_ += target.weight_;
        return true;
    };

    /* 
    Results in O(n) cost:
    for(auto x : items_){
        if(target.name_ == x.name_){ //when is good use case for comparator class? T*****T
            return false;
        }
    }
    */
}

/**
 * @brief Attempts to remove an item from the inventory by name.
 *
 * @param name Name of the item to be removed
 * @return true if the item was successfully removed, false if the
 *         item was not found in the inventory
 * @post Updates the weight_ member to reflect removing the Item
 */
template <class Comparator>
bool Inventory<Comparator, std::unordered_set<Item>>::discard(
    const std::string& itemName)
{
    // Why I cant just use contains() member function?? T*******T
    auto iter = items_.find(Item{itemName, 0}); //only name matters here
    if(iter == items_.end()){ //item not found in items_
        return false;
    } 
    weight_ -= iter->weight_;
    items_.erase(iter);
    return true;
}

/**
 * @brief Checks if an item with the given name exists in the inventory.
 *
 * @param name Name of the item to search for
 * @return true if the item exists in the inventory, false otherwise
 */
template <class Comparator>
bool Inventory<Comparator, std::unordered_set<Item>>::contains(
    const std::string& itemName) const
{
    //creating a temp Item object
    auto iter = items_.find(Item{itemName,0});
    return iter != items_.end(); //return result of operation
    
    /*
    Does the same as above:
    if(iter != items.end()){ //item found in items_
        return true;
    }
    return false;
    */
}

/**
 * @brief Queries the inventory for items within a specified range.
 *
 * Returns a set of items that fall between the start and end items
 * according to the specified Comparator (inclusive on both ends)
 *
 * @param start An Item whose compared property is the lower bound of the query range
 * @param end An Item whose compared property is the upper bound of the query range
 * @return std::unordered_set of items within the specified range
 *
 * @note Returns an empty set if the end item is less than the start item
 * @example To select all Items with weights 0.4 to 10.9, we'd setup the class & parameters as such:
 *  - this Inventory object is of type Inventory<CompareItemWeight>
 *  - start = Item("some_name", 0.4, ItemType::None)
 *  - end = = Item("some_other_name", 10.9, ItemType::None)
 *
 */
template <class Comparator>
std::unordered_set<Item>
Inventory<Comparator, std::unordered_set<Item>>::query(const Item& start,
    const Item& end) const
{
    //STUB FUNCTION
}

/**
 * @brief Destructor for the Inventory class.
 * @post Deallocates any dynamically allocated resources.
 */
template <class Comparator>
Inventory<Comparator, std::unordered_set<Item>>::~Inventory()
{
    if(equipped_ != nullptr){
        delete equipped_;
        equipped_ = nullptr;
    }
}