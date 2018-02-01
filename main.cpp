//#include "stdafx.h"
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <map>
#include <memory>
#include <utility>
#include <stdexcept>

using namespace std;

/* Item system 0.5 by baelothe      *
* Changelog:                       *
* 0.5: Initial version             *
* Planned versions:                *
* 0.6: Better autocasting,         *
* inventory categories             *
* 0.7: Inventory filters and       *
* sorting                          *
* 0.8: General rewrite             *
* 0.9: Improve the main parts of   *
* the system                       *
* 1.0: Item scripting              */
namespace ItemSystem
{
	/* The Items namespace holds the different Item subtypes  *
	* and the item categories. Define any new subtypes in    *
	* this namespace.                                        */
	namespace Items
	{
		/* Item categories are used to downcast to derived      *
		* pointers and sorting the inventory (WIP).            */
		enum class Category : unsigned int {
			CONSUMABLE, WEAPON, KEY, MISC
		};
		// Returns a integer value of a category (starts at 0, goes up).
		const unsigned int categoryToValue(const Category& c) {
			return static_cast<unsigned int>(c);
		}
		/* The Item class is the base type of all item objects. *
		* Derive this to create subtypes. Making objects of    *
		* this class won't work -- using a derived class is    *
		* required.                                            */
		class Item {
		private:
			// The display name of the item.
			const std::string name;
			// The description of the item.
			const std::string desc;
			// The ID of the item.
			const unsigned short id;
			// The buy price of the item.
			const unsigned short buy;
			// The sell price of the item.
			const unsigned short sell;
			// The category of the item (used for sorting and casting).
			const Category category;
		protected:
			// ctor(s)
			Item(const std::string& _name, const std::string& _desc,
				const unsigned short& _id, const unsigned short& _buy,
				const unsigned short& _sell, const Category& _category)
				: name(_name), desc(_desc), id(_id), buy(_buy),
				sell(_sell), category(_category) { /* empty ctor */
			}
		public:
			// copy ctor(s)
			Item(const Item& other) : name(other.name), desc(other.desc), id(other.id),
				buy(other.buy), sell(other.sell), category(other.category) { /* empty ctor */
			}
			// dtor(s)
			virtual ~Item() {
				// Override if needed
			}
			// Use function (WIP)
			virtual void use() = 0;
			// Getter functions
			const std::string& getName() const {
				return name;
			}
			const std::string& getDesc() const {
				return desc;
			}
			const unsigned short& getID() const {
				return id;
			}
			const unsigned short& getBuyPrice() const {
				return buy;
			}
			const unsigned short& getSellPrice() const {
				return sell;
			}
			const Category& getCategory() const {
				return category;
			}
		};
		/* The Weapon class derives from Item. Weapons are      *
		* unstackable (WIP), have damage values, and can be    *
		* equipped on the character.                           */
		class Weapon : public Item {
		private:
			// The damage value of the weapon.
			const unsigned short damage;
			// The critical chance of the weapon.
			const unsigned short crit;
			// The Spell damage of the weapon.
			const unsigned short spelldam;
			// The accuracy value of the weapon.
			const unsigned short accuracy;
		public:
			// ctor(s)
			Weapon(const std::string& _name, const std::string& _desc,
				const unsigned short& _id, const unsigned short& _damage, const unsigned short& _crit, const unsigned short& _spelldam, const unsigned short& _accuracy,
				const unsigned short& _buy, const unsigned short& _sell)
				: Item(_name, _desc, _id, _buy, _sell, Category::WEAPON), damage(_damage), crit(_crit), spelldam(_spelldam), accuracy(_accuracy) { }
			// dtor(s)
			virtual ~Weapon() {
				// Override if needed
			}
			// Use function (WIP)
			virtual void use() override {
				// Unused
			}
			// Getter functions
			virtual const unsigned short& getDamage() const {
				return damage;
			}
			virtual const unsigned short& getAccuracy() const {
				return accuracy;
			}
			virtual const unsigned short& getSpellDamage() const {
				return spelldam;
			}
			virtual const unsigned short& getCrit() const {
				return crit;
			}
		};
		/* The Consumable class derives from Item. Consumables  *
		* are stackable, and affect the stats of the           *
		* character or enemies.                                */
		class Consumable : public Item {
		private:
			// The health regain of the consumable.
			const unsigned short health;
			// The mana regain of the consumable.
			const unsigned short mana;
		public:
			// ctor(s)
			Consumable(const std::string& _name, const std::string& _desc,
				const unsigned short& _id, const unsigned short& _health,
				const unsigned short& _mana, const unsigned short& _buy,
				const unsigned short& _sell) : Item(_name, _desc, _id,
					_buy, _sell, Category::CONSUMABLE), health(_health), mana(_mana) { }
			// dtor(s)
			virtual ~Consumable() {
				// Override if needed
			}
			// Use function (WIP)
			virtual void use() override {
				// WIP
			}
			// Getter functions
			virtual const unsigned short& getHealth() const {
				return health;
			}
			virtual const unsigned short& getMana() const {
				return mana;
			}
		};
	}
	/* The Tables namespace has several item lookup tables,   *
	* making the generation and storage of item subtypes     *
	* easier.                                                */
	namespace Tables
	{
		// Better readability
		using namespace ItemSystem::Items;
		// Makes it easy to autogenerate item IDs
		unsigned short next_id = 0;
		class WeaponTable {
		private:
			// The table of weapons
			const std::map<const std::string, const Weapon> table{
				/*{
				"Weapon name goes here",
				Weapon(name, desc, next_id++, damage, crit, spell damage, buy, sell, accuracy,)
				}*/
				//{
				//"Test Weapon",
				//Weapon("Test Weapon", "For testing, idiot.", next_id++, 20, 10, 5)
				//}
				{
					"Stick",
					Weapon("Stick", "Useless, cannot gain any proficiency bonuses.", next_id++, 1, 0, 1, 100,  0, 0)
				},
				{
					"Modal Soul",
					Weapon("Modal Soul", "Wait!", next_id++, 9999, 100, 9999, 100, 9999, 9999)
				},
				{
					"Wooden Bow",
					Weapon("Wooden Bow", "A starter weapon for most hunters in training.", next_id++, 3, 5, 0, 50, 10, 7)
				},
				{
					"Reinforced Bow",
					Weapon("Reinforced Bow", "A more unique and composed wooden bow.", next_id++, 7, 10, 0, 60, 30, 20)
				},
				{
					"Iron Bow",
					Weapon("Iron Bow", "Forged in some unholy Audi'je's home, this bow is made from \nregurgitated iron.", next_id++, 15, 15, 0, 70, 60, 50)
				},
				{
					"Tactical Compound Bow",
					Weapon("Tactical Compound Bow", "A bow with a 16x optical scope, strap, and a better string.", next_id++, 35, 20, 0, 100, 100, 80)
				},
				{
					"Meteor Bow",
					Weapon("Meteor Bow", "Forged from a passing meteor, nicknamed MB-132. Incredibly Rare", next_id++, 50, 25, 0, 75, 250, 200)
				},
				{
					"Star Bow",
					Weapon("Star Bow", "This bow has an unkown origin, it's only main feature is the\ndistinct glow the arrows make when fired. The bow seems to possess a special \npower... The power of light.", next_id++, 100, 50, 0, 75, 1000, 750)
				},
				{
					"Copper Shortsword",
					Weapon("Copper Shortsword", "A flimsy blade, made from the cheapest material on the planet.", next_id++, 5, 1, 0, 90, 15, 10)
				},
				{
					"Iron Blade",
					Weapon("Iron Blade", "A less flimsy blade, made from less-cheap materials.", next_id++, 9, 2, 0, 90, 30, 20)
				},
				{
					"Steel Blade",
					Weapon("Steel Blade", "A blade made out of a semi-usable material. Not the best, or \nworst.", next_id++ , 20, 3, 0, 95, 75, 50)
				},
				{
					"Obsidian Longsword",
					Weapon("Obsidian Longsword", "A dangerous weapon, a major step-up from the previous blades.", next_id++, 50, 4, 0, 80, 150, 100)
				},
				{
					"Core Lightblade",
					Weapon("Core Lightblade", "The sword forged inside the planet's core. Has a obsidian blade \nwith magma flowing around it.", next_id++, 100, 4, 0, 95, 500, 400)
				},
				{
					"The Singularity Blade",
					Weapon("The Singularity Blade", "Cuts with astronomical force, created from a god of the past.\nThe blade is complicated and overdone in features, filling a part of the\nblade with a moral of rebirth.", next_id++, 200, 3, 0, 95, 1500, 1250)
				},
				{
					"Wooden Staff",
					Weapon("Wooden Staff", "A wooden stick with some message in an unknown language cut in on \nthe side.", next_id++, 1, 0, 15, 100, 5, 3)
				},
				{
					"Infused Staff",
					Weapon("Infused Staff", "Covered in markings and scratches, it seems to emanate power.", next_id++, 2, 1, 25, 100, 10, 5)
				},
				{
					"Cut Wand",
					Weapon("Cut Wand", "A small wand, it can be aimed to cast certain, more powerful \nspells.", next_id++, 2, 1, 55, 100, 50, 25)
				},
				{
					"Nuja Wand",
					Weapon("Nuja Wand", "A wand passed down through the ages. Holds a rhythmic power.", next_id++, 4, 1, 120, 100, 100, 75)
				},
				{
					"F.I.L.O.",
					Weapon("F.I.L.O.", "F.I.L.O is a staff made as a tribute to a human who died in an \naccident. Just you holding it brings back depressed memories.", next_id++, 5, 1, 200, 100, 150, 100)
				},
				{
					"Staff of Mythos",
					Weapon("Staff of Mythos", "This staff holds the power from the great eldritch monsters. \nIt was found by a human when he destroyed the eldritch beings on his planet. \nHolds the souls of all the eldritch monsters.", next_id++, 10, 1, 350, 100, 1000, 750)
				},
				{
					"Leather Gloves",
					Weapon("Leather Gloves", "Torn up, burnt, and dipped in acid. These leather gloves are \nwell-worn.", next_id++, 7, 0, 0, 99, 5, 3)
				},
				{
					"Red Rubber Gloves",
					Weapon("Red Rubber Gloves", "Somebody used these one time.", next_id++, 15, 0, 0, 99, 30, 20)
				},
				{
					"Brass Knuckles",
					Weapon("Brass Knuckles", "Packs a punch, and a pierce. The brass knuckles are light and \npowerful.", next_id++, 40, 0, 0, 99, 60, 50)
				},
				{
					"Power Glove",
					Weapon("Power Glove", "Confused with the techinical masterpiece often. The powerglove \nexplodes on impact.", next_id++, 75, 0, 0, 99, 150, 125)
				},
				{
					"Torched Wristband",
					Weapon("Torched Wristband", "Although not connected to the fists, the Torched Wristband \ninfuses the hand with strong power, also producing an explosion \nin the process.", next_id++, 150, 0, 0, 99, 750, 500)
				},
				{
					"Hell-Forged Wristband",
					Weapon("Hell-Forged Wristband", "Infuses the user with a large amount of strength so powerful, it \ncould destroy a building in one hit. The Hell-Forged wristband was \nused by a head executioner to keep control of his troops.", next_id++, 300, 0, 0, 99, 1750, 1400)
				}
			};
		public:
			// Generates a reference to an item in the table.
			const Weapon& generate(const std::string& nameID) const {
				// Check if the entry exists
				if (table.count(nameID) == 0)
					throw std::invalid_argument("Attempted to generate a Weapon that does not exist");
				// Return the reference
				return table.at(nameID);
			}
		} const WeaponTable;
		class ConsumableTable {
		private:
			// The table of consumables
			const std::map<const std::string, const Consumable> table{
				/*{
				"Consumable name goes here",
				Consumable(name, desc, next_id++, health, mana, buy, sell)
				}*/
				{
					"Test Consumable",
					Consumable("Test Consumable", "For testing, idiot.", next_id++, 20, 8, 10, 5)
				},
				{
					"Normal Health Potion",
					Consumable("Normal Health Potion", "Heals 25 HP ", next_id++, 25, 0, 15, 3)
				},
				{
					"Greater Health Potion",
					Consumable("Greater Health Potion", "Heals 100 HP", next_id++, 100, 0, 45, 20)
				},
				{
					"Super Health Potion",
					Consumable("Super Health Potion", "Heals 500 HP", next_id++, 500, 0, 100, 50)
				},
				{
                    "Full Health Potion",
                    Consumable("Full Health Potion", "Heals 9999 HP", next_id++, 9999, 0, 300, 150)
				},
				{
                    "Normal Mana Potion",
                    Consumable("Normal Mana Potion", "Restores 15 MP", next_id++, 0, 15, 10, 5)
				},
				{
                    "Greater Mana Potion",
                    Consumable("Greater Mana Potion", "Restores 45 MP", next_id++, 0, 45, 45, 20)
				},
				{
                    "Super Mana Potion",
                    Consumable("Super Mana Potion", "Restores 100 MP", next_id++, 0, 100, 100, 50)
				},
				{
                    "Full Mana Potion",
                    Consumable("Full Mana Potion", "Restores 9999 MP", next_id++, 0, 9999, 300, 150)
				},
				{
                    "Full Restore",
                    Consumable("Full Restore", "Restores 9999 MP and 9999 HP", next_id++, 9999, 9999, 500, 250)

				}
			};
		public:
			// Generates a reference to an item in the table.
			const Consumable& generate(const std::string& nameID) const {
				// Check if the entry exists
				if (table.count(nameID) == 0)
					throw std::invalid_argument("Attempted to generate a Weapon that does not exist");
				// Return the reference
				return table.at(nameID);
			}
		} const ConsumableTable;
	}
	/* The Container namespace has the item slot class and    *
	* the inventory system.                                  */
	namespace Container
	{
		// Better readability
		using namespace ItemSystem::Items;
		/* The ItemSlot class encapsulates a item subtype and   *
		* allows it to be stored in the inventory, along with  *
		* keeping track of how many items are stacked.         */
		class ItemSlot {
		private:
			// Pointer to (dynamically allocated) item-based instance
			std::shared_ptr<const Item> item;
			// Stack amount
			unsigned short stack;
		public:
			// ctor(s)
			ItemSlot(const Item* _item = nullptr, const unsigned short& _stack = 1)
				: item(_item), stack(_stack) { }
			// Updates the item in the slot (destroying the old instance).
			void update(const Item* newitem) {
				item.reset(newitem);
			}
			// Getter and setter functions
			const std::shared_ptr<const Item>& getItem() const {
				return item;
			}
			const unsigned short& getStackAmount() const {
				return stack;
			}
			// Increments (adds 1 to) the stack amount.
			void incrementStackAmount() {
				stack++;
			}
			// Decrements (removes 1 from) the stack amount.
			void decrementStackAmount() {
				stack--;
			}
			// Operator overloading
			bool operator==(const ItemSlot& other) {
				if (item->getID() == other.getItem()->getID())
					return true;
				else return false;
			}
		};
		/* The Inventory holds a vector of item slots, and      *
		* handles the creation and deletion of those slots.    *
		* The inventory can be added to, deleted from, taken   *
		* from, read entry by entry, and (WIP) sorted and      *
		* filtered.                                            */
		class Inventory {
		private:
			// The data storage of the inventory.
			std::vector<ItemSlot> storage;
		public:
			// ctor(s)
			Inventory() {
				// Reserve space
				storage.reserve(20);
			}
			// Adds an item to the inventory.
			template<class ItemType>
			void addItem(const ItemType& item) {
				// Initialize an item slot
				ItemSlot slot(new ItemType(item));
				// Check through inventory to see if an entry already exists
				for (ItemSlot& entry : storage) {
					// If there's an entry match
					if (entry == slot) {
						// Add to the existing slot's stack
						entry.incrementStackAmount();
						// Temporary item slot is destroyed here; no memory leaks (hopefully)
						return;
					}
				}
				// No matches, add new entry
				storage.push_back(std::move(slot));
			}
			// Adds multiple items to the inventory.
			template<class ItemType>
			void addItems(const std::initializer_list<const ItemType>& items) {
				// Call addItem() for each item
				for (auto it = items.begin(); it != items.end(); ++it)
					addItem(*it);
			}
			// Inspects an item in the inventory.
			const Item* inspectItem(const unsigned int& index) {
				// Check OOB
				if (index >= storage.size()) return nullptr;
				// Return the item pointer
				return storage.at(index).getItem().get();
			}
			// Inspects a item slot from the inventory.
			const ItemSlot* inspectSlot(const unsigned int& index) {
				// Check OOB
				if (index >= storage.size()) return nullptr;
				// Return the slot reference
				return &(storage.at(index));
			}
			// Removes a single item from the inventory.
			void deleteItem(const unsigned int& index) {
				// Check OOB
				if (index >= storage.size()) return;
				// Remove from stack
				storage.at(index).decrementStackAmount();
				// Check if the slot is empty (and should be deleted)
				if (storage.at(index).getStackAmount() == 0)
					// Delete the slot
					storage.erase(storage.begin() + index);
			}
			// Removes an item slot from the inventory.
			void deleteSlot(const unsigned int& index) {
				// Check OOB
				if (index >= storage.size()) return;
				// Remove the item slot at the specified index
				storage.erase(storage.begin() + index);
			}
			// Takes an item from the inventory (deleting the item slot if stack is out).
			const std::shared_ptr<const Item> takeItem(const unsigned int& index) {
				// Check OOB
				if (index >= storage.size()) return nullptr;
				// Get item
				const std::shared_ptr<const Item> item = storage.at(index).getItem();
				// Remove from stack or delete the item slot
				if (storage.at(index).getStackAmount() > 1) {
					// Subtract from stack
					storage.at(index).decrementStackAmount();
				}
				// No stack remaining, remove the entry
				else {
					// Delete the entry
					deleteItem(index);
				}
				// Return the item
				return item;
			}
			// Gets the entire inventory vector (read-only).
			const std::vector<ItemSlot>& getAll() {
				return storage;
			}
		};
	}
}

using namespace ItemSystem::Items;
using namespace ItemSystem::Tables;
using namespace ItemSystem::Container;

////////////////WEAPONSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS STructs.
/*
struct Weapon {
string wep_name;
string wep_desc;
int getDamage();
int getCrit();
int wep_type;
int wep_spelldam;
int getBuyPrice();
int getAccuracy();
};

struct Consumable {
string con_name;
int con_healgain;
int con_managain;
int con_type;
int con_cost;
};
*/

struct Accuracy {

	int head;
	int chest;
	int rightarm;
	int leftarm;
	int rightleg;
	int leftleg;
	///Bodypart Damage Multiplier
	double headdamagex = 2.00;
	double chestdamagex = 1.00;
	double rightarmdamagex = 1.00;
	double leftarmdamagex = 1.00;
	double rightlegdamagex = 1.00;
	double leftlegdamagex = 1.00;
} Acc;

void chargen();

/*
const vector<Consumable> consumableTable{
What does this mean... though?
Name
Health Gain
Mana Gain
Type (1 = Health Potion, 2 = Mana Potion)
Cost
///Health Potions
{ "Normal Health Potion", 25, 0, 1, 5 },
{ "Greater Health Potion", 100, 0, 1, 15, },
{ "Super Health Potion", 500, 0, 1, 50 },
{ "Full Health Potion", 9999, 0, 1, 150 },
///Mana Potions
{ "Normal Mana Potion", 0, 5, 2, 5 },
{ "Greater Mana Potion", 0, 25, 2, 10 },
{ "Super Mana Potion", 0, 100, 2, 35 },
{ "Full Mana Potion", 0, 9999, 2, 100 }

};

*/



int input;
void inventory();

struct Enemy
{
	string ename;
	int maxeHP;
	int maxeMP;
	int emp;
	int ehp;
	int estr;
	int edef;
	int eitl;
	int espd;
	int ecrt;
	int elvl;
	double eheadhp = 1.00;
	double echesthp = 1.00;
	double erightarmhp = 1.00;
	double eleftarmhp = 1.00;
	double erightleghp = 1.00;
	double eleftleghp = 1.00;
} Enemy;

struct Character
{
	///Everything not related to the things below
	string name = "None";
	string race = "None";
	string clas = "None";
	string difficultyN = "Normal";
	string profession = "None";
	string dad;
	double difficultyD = 1;
	double expmultiplier = 1;
	int dust = 15;
	///Stats
	int lvl = 1;
	int exp = 0;
	int maxHP;
	int maxMP;
	int hp;
	int mp;
	int str = 1;
	int def = 1;
	int crt = 1;
	int spd = 1;
	int itl = 1;
	///Bodypart Health
	double headhp = 1.00;
	double chesthp = 1.00;
	double rightarmhp = 1.00;
	double leftarmhp = 1.00;
	double rightleghp = 1.00;
	double leftleghp = 1.00;
	///Skill Professions start here
	double strprof = 1.00;
	double defprof = 1.00;
	double spdprof = 1.00;
	double itlprof = 1.00;
	///Weapon Professions start here
	double bowprof = 1.00;
	double swordprof = 1.00;
	double staffprof = 1.00;
	double unarmedprof = 1.00;
	///Literally useless.
	int seed;
	bool blackmarketfirst = false;
	bool workshopfirst = false;
	///Body Mods/workshop
	string modsot[4] = { "Dust Grip - (Sword Prof +.25) - 50 Dust", "Dust String - (Bow Prof +.25) - 50 Dust", "Casting Serum - (Staff Prof +.25) - 50 Dust", "Knuckle Dust - (Unarmed Prof +.25) - 50 Dust" };
	int modsmt[4] = { 15, 15, 15, 15 };
	// Inventory
	Inventory inventory;
	Weapon* equipped;
} Charac;

void home();
void enemyturn();

void ClearScreen()
{
	system("CLS");
}

void wait_enter(void) //Method of wait_enter, call it to create a Press Enter to continue screen.
{
	cin.ignore();
	cout << "Press ENTER to continue...";
	cin.ignore();
}

void weaponinv() {
	ClearScreen();
	cout << "-*- Inventory -*-\nCurrent Weapon: " << Charac.equipped->getName() << "\nDescription: " << Charac.equipped->getDesc() << endl;
	cout << "\n-*- Weapon Stats -*-\nDamage: " << Charac.equipped->getDamage() << "\nCrit Bonus: " << Charac.equipped->getCrit() << "\nSpell Damage: " << Charac.equipped->getSpellDamage() << "\nAccuracy: " << Charac.equipped->getAccuracy() << "\nWeapon Cost: " << Charac.equipped->getBuyPrice() << "\n" << endl;
	int index = 1;
	cout << "0) Exit" << endl;
	std::vector<Weapon*> weapons;
	for (const auto& item : Charac.inventory.getAll()) {
		if (item.getItem()->getCategory() == Category::WEAPON) {
			auto toCast = item.getItem().get();
			auto weapon = const_cast<Weapon*>(dynamic_cast<const Weapon*>(toCast));
			weapons.push_back(weapon);
		}
	}
	for (const auto& wep : weapons)
	{
		cout << index << ") " << wep->getName() << std::endl;
		index++;
	}
	cin >> input;
	if (input == 0) {

	}
	else if (input != 0) {
		Charac.equipped = const_cast<Weapon*>(dynamic_cast<const Weapon*>(Charac.inventory.inspectItem(input - 1)));
		weaponinv();
	}
}

void statcheck() {
    if(Charac.maxHP > Charac.hp) {
    Charac.hp = Charac.maxHP;
    }
    if(Charac.maxMP > Charac.mp) {
    Charac.mp = Charac.maxMP;
    }
}

void consuminv() {
	unsigned int index = 0;
	cout << "0) Exit" << endl;
	// Filter inventory into vector.
	std::vector<std::pair<Consumable*, unsigned int>> filtered;
	for (const auto& item : Charac.inventory.getAll()) {
		if (item.getItem()->getCategory() == Category::CONSUMABLE) {
			auto consumable = const_cast<Consumable*>(dynamic_cast<const Consumable*>(item.getItem().get()));
			filtered.push_back(std::make_pair(consumable, index));
			std::cout << filtered.size() << ") " << consumable->getName() << " x" << item.getStackAmount() << std::endl;
		}
		index++;
	}
	// Get input;
	unsigned int userInput;
	std::cin >> userInput;
	if (userInput == 0) return;
	userInput--;
	// Take item and use it.
	unsigned int takenInput = filtered.at(userInput).second;
	auto takenItem = filtered.at(userInput).first;
	Charac.hp += takenItem->getHealth();
	Charac.mp += takenItem->getMana();
	// Print info.
	std::cout << "You restore " << takenItem->getHealth() << " HP and " << takenItem->getMana() << " MP!" << endl;
	Charac.inventory.deleteItem(takenInput);
	statcheck();
	wait_enter();
}

void inventory() {
	ClearScreen();
	cout << "-*- Stats -*-\n\nName: " << Charac.name << "\nRace: " << Charac.race << "\nClass: " << Charac.clas << "\nProfession: " << Charac.profession << "\n\nMax Health: " << Charac.maxHP << "\nMax Mana: " << Charac.maxMP << "\n\nCurrent HP: " << Charac.hp << "\nCurrent MP: " << Charac.mp << "\n\nStrength: " << Charac.str << "\nDefense: " << Charac.def << "\nIntelligence: " << Charac.itl << "\nSpeed: " << Charac.spd << "\nCritical Chance: " << Charac.crt << "\n\nDifficulty: " << Charac.difficultyN << "\nDifficulty Multiplier: " << Charac.difficultyD << "x" << endl;
	cout << "\nEXP To Next Level: " << ((Charac.lvl * 50 * Charac.difficultyD) * Charac.expmultiplier) - Charac.exp << endl;
	cout << "\n0) Exit\n1) Weapons\n2) Consumables" << endl;
	cin >> input;
	switch (input) {
	case 0:
		break;
	case 1:
		weaponinv();
		break;
	case 2:
		consuminv();
		break;

	}
}



void Enemygen() {
	Enemy.elvl = rand() % Charac.lvl * Charac.difficultyD;
	Enemy.estr = rand() % Charac.str + Charac.lvl * Charac.difficultyD;
	Enemy.eitl = rand() % Charac.itl + Charac.lvl * Charac.difficultyD;
	Enemy.edef = rand() % Charac.def + Charac.lvl * Charac.difficultyD;
	Enemy.espd = rand() % Charac.spd + Charac.lvl * Charac.difficultyD;
	Enemy.ecrt = rand() % Charac.crt + Charac.lvl;
	if (Enemy.estr < 1) {
		Enemy.estr = 1;
	}
	if (Enemy.eitl < 1) {
		Enemy.eitl = 1;
	}
	if (Enemy.edef < 1) {
		Enemy.edef = 1;
	}
	if (Enemy.espd < 1) {
		Enemy.espd = 1;
	}
	Enemy.maxeHP = (Enemy.estr * 2) + (Enemy.edef * 3) + Enemy.elvl * 2 * Charac.difficultyD;
	Enemy.maxeMP = (Enemy.estr) - (Enemy.edef) + (Enemy.eitl + 2) + Enemy.elvl;
	if (Enemy.maxeMP < 1) {
		Enemy.maxeMP = 1;
	}
	if (Enemy.ecrt > 100) {
		Enemy.ecrt = 100;
	}
	if (Enemy.maxeHP < 9) {
		Enemy.maxeHP = 10;
	}
	if (Enemy.elvl < 1) {
		Enemy.elvl = 1;
	}
	Enemy.emp = Enemy.maxeMP;
	Enemy.ehp = Enemy.maxeHP;
	Enemy.eheadhp = 1.00;
	Enemy.echesthp = 1.00;
	Enemy.erightarmhp = 1.00;
	Enemy.eleftarmhp = 1.00;
	Enemy.erightleghp = 1.00;
	Enemy.eleftleghp = 1.00;
}

void victory() {
	int randint;
	randint = rand() % 15 + Enemy.elvl;
	cout << "You find " << randint << " dust." << endl;
	Charac.dust += randint;
	randint = ((Enemy.maxeHP + Enemy.estr + Enemy.edef + Enemy.eitl + Enemy.espd) * Enemy.elvl) / Charac.difficultyD;
	cout << "You earned " << randint << " experience!" << endl;
	Charac.exp += randint;
	while (Charac.exp > (int)((Charac.lvl * 50 * Charac.difficultyD)) * Charac.expmultiplier) {
		Charac.lvl++;
		Charac.expmultiplier += .25;
		cout << "You leveled! Current Level: " << Charac.lvl << endl;
		cout << "What would to like increase?" << endl;
		cout << "1) Strength: " << Charac.str << "\n2) Intelligence: " << Charac.itl << "\n3) Speed: " << Charac.spd << "\n4) Defense: " << Charac.def << endl;
		cin >> input;
		if (input < 1 || input > 4) {
			cout << "Not a valid option, putting point into strength." << endl;
			randint = rand() % 2 + 1;
			Charac.str += randint;
		}
		else if (input >= 1 || input <= 4) {
			switch (input) {
			case 1:
				randint = rand() % 2 + 1;
				Charac.str += randint;
				break;
			case 2:
				randint = rand() % 2 + 1;
				Charac.itl += randint;
				break;
			case 3:
				randint = rand() % 2 + 1;
				Charac.spd += randint;
				break;
			case 4:
				randint = rand() % 2 + 1;
				Charac.def += randint;
				break;
			}
		}
	}
	wait_enter();
	home();
}

void deathcheck() {
	if (Charac.hp <= 0) {
		cout << "You fall over, defeated." << endl;
		exit(0);

	}
	if (Enemy.ehp <= 0) {
		cout << "The enemy dies, you win!" << endl;
		victory();
	}
}


void playerTurn() {
	int acchit;
	int randamage;
	int randint;
	double bodydamage = .1;
	bool battlemenu = true;
	Acc.head = rand() % 100;
	while (battlemenu == true) {
		deathcheck();
		cout << "HP: " << Charac.hp << "      Enemy HP: " << Enemy.ehp << "\nMP: " << Charac.mp << "      Enemy MP: " << Enemy.emp << endl;
		cout << "\n1) Attack\n2) Cast\n3) Inventory\n4) Run" << endl;
		cin >> input;
}
}

void enemyTurn() {
	int acchit;
	int randamage;
	int randint;
	randint = rand() % 50;

}

void decideTurn() {
    unsigned int turnSpeed = Charac.spd + (rand() % 5 + 1);
    // Get enemy turn speed.
    unsigned int enemyTurnSpeed = Enemy.espd + (rand() % 5 + 1);
     if(turnSpeed > enemyTurnSpeed) {
        playerTurn();
    } else {
        enemyTurn();
    }
}


void explore() {
	Enemygen();
	string exploredesc[10] = { "While walking around the graveyard, you see ", "As you walk around the graveyard, you see ", "While you were walking around the graveyard, you see ", "When you were walking around the graveyard, you saw ", "As you explored the surrounding forest, you saw ", "While exploring the surrounding forest, you saw ", "During your patrol of the surrounding area, you saw ", "You see something guarding the gate, it is ", "Taking a look around the graveyard, you see ", "While wandering, you see " };
	string exploremonn[10] = { "a Skeleton", "a Man Wearing a Dinosaur Costume", "a Demon", "a Tiefling", "an Orc", "a Goblin", "a Troll", "a Cyborg-Guardian", "a Cultist", "a Bandit" };
	cout << exploredesc[rand() % 10] << exploremonn[rand() % 10] << "\nSizing up the creature, you can see it has approximately..." << endl;
	cout << Enemy.ehp << " Max Health...\n" << Enemy.emp << " Max Mana...\n" << endl;
	cout << "1) Attack\n2) Return Back Home" << endl;
	cin >> input;
	switch (input) {
	case 1:
		decideTurn();
		break;
	case 2:
		break;
	}
}

void workshop() {
	ClearScreen();
	if (Charac.workshopfirst == false) {
		cout << "You start to dig into a grave. It gives off a soft glow as you dig into the \ndirt.The dirt is thrown to the side and a door is revealed.\nYou open it to see tables, blueprints, and workstations littered around the \ndimly lit room. You pick up a blueprint and read it, it seems to focus on Dust.\nThe blueprint is for a body modification, allowing the user to withstand more \ndamage. You take it and look around for more blueprints." << endl;
		wait_enter();
		Charac.workshopfirst = true;
		workshop();
	}
	else if (Charac.workshopfirst == true) {
		ClearScreen();
		cout << "You look at your current blueprints." << endl;
		cout << "\n-*- One Time Creations -*-\n1) " << Charac.modsot[0] << "\n2) " << Charac.modsot[1] << "\n3) " << Charac.modsot[2] << "\n4) " << Charac.modsot[3] << "\n\n-*- Multiple Creations -*-\n5) Rotating Motor - (Str +5) - " << Charac.modsmt[0] << " Dust\n6) Traction Ropes - (Spd +5) - " << Charac.modsmt[1] << " Dust\n7) Dust Brain Augment - (Itl +5) - " << Charac.modsmt[2] << " Dust\n8) Dust Armor - (Def +5) - " << Charac.modsmt[3] << " Dust" << endl;
		cin >> input;
		switch (input) {
		case 1:
			if (Charac.modsot[0] == "Dust Grip - CREATED") {
				cout << "You already created that." << endl;
				wait_enter();
				break;
			}
			if (Charac.dust < 50) {
				cout << "You do not have enough dust." << endl;
				wait_enter();
			}
			else if (Charac.dust >= 50) {
				cout << "You create the dust grip. Gaining +.25 Sword Profficiency" << endl;
				Charac.modsot[0] = "Dust Grip - CREATED";
				Charac.swordprof = Charac.swordprof + .25;
				Charac.dust = Charac.dust - 50;
				wait_enter();
			}
			break;
		case 2:
			if (Charac.modsot[1] == "Dust String - CREATED") {
				cout << "You already created that." << endl;
				wait_enter();
				break;
			}
			if (Charac.dust < 50) {
				cout << "You do not have enough dust." << endl;
				wait_enter();
			}
			else if (Charac.dust >= 50) {
				cout << "You create the dust string. Gaining +.25 Bow Profficiency" << endl;
				Charac.modsot[1] = "Dust String - CREATED";
				Charac.bowprof = Charac.bowprof + .25;
				Charac.dust = Charac.dust - 50;
				wait_enter();
			}
			break;
		case 3:
			if (Charac.modsot[2] == "Casting Serum - CREATED") {
				cout << "You already created that." << endl;
				Charac.dust = Charac.dust - 50;
				wait_enter();
				break;
			}
			if (Charac.dust < 50) {
				cout << "You do not have enough dust." << endl;
				wait_enter();
			}
			else if (Charac.dust >= 50) {
				cout << "You create the casting serum. Gaining +.25 Staff Profficiency" << endl;
				Charac.modsot[2] = "Casting Serum - CREATED";
				Charac.staffprof = Charac.staffprof + .25;
				Charac.dust = Charac.dust - 50;
				wait_enter();
			}
			break;
		case 4:
			if (Charac.modsot[3] == "Knuckle Dust - CREATED") {
				cout << "You already created that." << endl;
				wait_enter();
				break;
			}
			if (Charac.dust < 50) {
				cout << "You do not have enough dust." << endl;
				wait_enter();
			}
			else if (Charac.dust >= 50) {
				cout << "You create the knuckle dust. Gaining +.25 Unarmed Profficiency" << endl;
				Charac.modsot[3] = "Knuckle Dust - CREATED";
				Charac.unarmedprof = Charac.unarmedprof + .25;
				Charac.dust = Charac.dust - 50;
				wait_enter();
			}
			break;
		case 5:
			if (Charac.dust < Charac.modsmt[0]) {
				cout << "You do not have enough dust." << endl;
				wait_enter();
			}
			else if (Charac.dust >= Charac.modsmt[0]) {
				cout << "You create the Rotating Motor, gaining 5 Strength." << endl;
				Charac.dust = Charac.dust - Charac.modsmt[0];
				Charac.str = Charac.str + 5;
				Charac.modsmt[0] = Charac.modsmt[0] + Charac.modsmt[0];
				wait_enter();
			}
			break;
		case 6:
			if (Charac.dust < Charac.modsmt[1]) {
				cout << "You do not have enough dust." << endl;
				wait_enter();
			}
			else if (Charac.dust >= Charac.modsmt[1]) {
				cout << "You create the Traction Ropes, gaining 5 Speed." << endl;
				Charac.dust = Charac.dust - Charac.modsmt[1];
				Charac.spd = Charac.spd + 5;
				Charac.modsmt[1] = Charac.modsmt[1] + Charac.modsmt[1];
				wait_enter();
			}
			break;
		case 7:
			if (Charac.dust < Charac.modsmt[2]) {
				cout << "You do not have enough dust." << endl;
				wait_enter();
			}
			else if (Charac.dust >= Charac.modsmt[1]) {
				cout << "You create the Dust Brain Augment, gaining 5 Intelligence." << endl;
				Charac.dust = Charac.dust - Charac.modsmt[2];
				Charac.itl = Charac.itl + 5;
				Charac.modsmt[2] = Charac.modsmt[2] + Charac.modsmt[2];
				wait_enter();
			}
			break;
		case 8:
			if (Charac.dust < Charac.modsmt[3]) {
				cout << "You do not have enough dust." << endl;
				wait_enter();
			}
			else if (Charac.dust >= Charac.modsmt[3]) {
				cout << "You create the Dust Armor, gaining 5 Defense." << endl;
				Charac.dust = Charac.dust - Charac.modsmt[3];
				Charac.def = Charac.def + 5;
				Charac.modsmt[3] = Charac.modsmt[3] + Charac.modsmt[3];
				wait_enter();
			}
			break;
		}
	}

}

void blackmarket() {
	int input2;
	ClearScreen();
	if (Charac.blackmarketfirst == false) {
		cout << "You lift up the lid to the underground... You can only see a single door\nA swarm of security drones flock to you and take your picture.\nThe door opens and reveals an underground society, the lights are blinding.\nYou look around and see a few shops, offering items for dust." << endl;
		wait_enter();
		Charac.blackmarketfirst = true;
		blackmarket();
	}
	else if (Charac.blackmarketfirst == true) {
		ClearScreen();
		cout << "You look at the shops available." << endl;
		cout << "\n1) Warrior's Supply \n2) Hunter's Edge\n3) The Magic's Gathering\n4) Rocket Wrestling\n5) Mike's Friendly Store" << endl;
		cout << "\nDust Available: " << Charac.dust << endl;
		cin >> input;
		switch (input) {
		case 1:
			ClearScreen();
			cout << "-*- Warrior's Supply -*-" << endl;
			cout << "\nYou walk in and are greeted by two Bren'kibs. \nThey are polishing their spears and weapons for selling.\nThey show you around the store." << endl;
			cout << "\n1) Copper Shortsword - " << WeaponTable.generate("Copper Shortsword").getBuyPrice() << " Dust\n2) Iron Blade - " << WeaponTable.generate("Iron Blade").getBuyPrice() << " Dust" << endl;
			cout << "3) Steel Blade - " << WeaponTable.generate("Steel Blade").getBuyPrice() << " Dust\n4) Obsidian Longsword - " << WeaponTable.generate("Obsidian Longsword").getBuyPrice() << " Dust" << endl;
			cout << "5) Core Lightblade - " << WeaponTable.generate("Core Lightblade").getBuyPrice() << " Dust\n6) The Singularity Blade - " << WeaponTable.generate("The Singularity Blade").getBuyPrice() << " Dust" << endl;
			cout << "\n0) Exit" << endl;
			cin >> input2;
			switch (input2) {
			case 1:
				if (Charac.dust < WeaponTable.generate("Copper Shortsword").getBuyPrice()) {
					cout << "You do not have enough dust." << endl;
					wait_enter();
					break;
				}
				else if (Charac.dust >= WeaponTable.generate("Copper Shortsword").getBuyPrice()) {
					cout << "You buy the Copper Shortsword for " << WeaponTable.generate("Copper Shortsword").getBuyPrice() << " dust." << endl;
					Charac.dust = Charac.dust - WeaponTable.generate("Copper Shortsword").getBuyPrice();
					Charac.inventory.addItem(WeaponTable.generate("Copper Shortsword"));
					wait_enter();
					break;
				}
				break;
			case 2:
				if (Charac.dust < WeaponTable.generate("Iron Blade").getBuyPrice()) {
					cout << "You do not have enough dust." << endl;
					wait_enter();
					break;
				}
				else if (Charac.dust >= WeaponTable.generate("Iron Blade").getBuyPrice()) {
					cout << "You buy the Iron Blade for " << WeaponTable.generate("Iron Blade").getBuyPrice() << " dust." << endl;
					Charac.dust = Charac.dust - WeaponTable.generate("Iron Blade").getBuyPrice();
					Charac.inventory.addItem(WeaponTable.generate("Iron Blade"));
					wait_enter();
					break;
				}
				break;
			case 3:
				if (Charac.dust < WeaponTable.generate("Steel Blade").getBuyPrice()) {
					cout << "You do not have enough dust." << endl;
					wait_enter();
					break;
				}
				else if (Charac.dust >= WeaponTable.generate("Steel Blade").getBuyPrice()) {
					cout << "You buy the Steel Blade for " << WeaponTable.generate("Steel Blade").getBuyPrice() << " dust." << endl;
					Charac.dust = Charac.dust - WeaponTable.generate("Steel Blade").getBuyPrice();
					Charac.inventory.addItem(WeaponTable.generate("Steel Blade"));
					wait_enter();
					break;
				}
				break;
			case 4:
				if (Charac.dust < WeaponTable.generate("Obsidian Longsword").getBuyPrice()) {
					cout << "You do not have enough dust." << endl;
					wait_enter();
					break;
				}
				else if (Charac.dust >= WeaponTable.generate("Obsidian Longsword").getBuyPrice()) {
					cout << "You buy the Obsidian Longsword for " << WeaponTable.generate("Obsidian Longsword").getBuyPrice() << " dust." << endl;
					Charac.dust = Charac.dust - WeaponTable.generate("Obsidian Longsword").getBuyPrice();
					Charac.inventory.addItem(WeaponTable.generate("Obsidian Longsword"));
					wait_enter();
					break;
				}
				break;
			case 5:
				if (Charac.dust < WeaponTable.generate("Core Lightblade").getBuyPrice()) {
					cout << "You do not have enough dust." << endl;
					wait_enter();
					break;
				}
				else if (Charac.dust >= WeaponTable.generate("Core Lightblade").getBuyPrice()) {
					cout << "You buy the Core Lightblade for " << WeaponTable.generate("Core Lightblade").getBuyPrice() << " dust." << endl;
					Charac.dust = Charac.dust - WeaponTable.generate("Core Lightblade").getBuyPrice();
					Charac.inventory.addItem(WeaponTable.generate("Core Lightblade"));
					wait_enter();
					break;
				}
				break;
			case 6:
				if (Charac.dust < WeaponTable.generate("The Singularity Blade").getBuyPrice()) {
					cout << "You do not have enough dust." << endl;
					wait_enter();
					break;
				}
				else if (Charac.dust >= WeaponTable.generate("The Singularity Blade").getBuyPrice()) {
					cout << "You buy the The Singularity Blade for " << WeaponTable.generate("The Singularity Blade").getBuyPrice() << " dust." << endl;
					Charac.dust = Charac.dust - WeaponTable.generate("The Singularity Blade").getBuyPrice();
					Charac.inventory.addItem(WeaponTable.generate("The Singularity Blade"));
					wait_enter();
					break;
				}

				break;
			}
			break;
		case 2:
			ClearScreen();
			cout << "-*- Hunter's Edge -*-" << endl;
			cout << "\nAs you enter the shop you see a Kenku sitting behind the counter.\nHe throws a dagger at you, barely missing you.\nHe laughs and lets you look at his wares.\n\n1) Wooden Bow - " << WeaponTable.generate("Wooden Bow").getBuyPrice() << " Dust\n2) Reinforced Bow - " << WeaponTable.generate("Reinforced Bow").getBuyPrice() << " Dust\n3) Iron Bow - " << WeaponTable.generate("Iron Bow").getBuyPrice() << " Dust\n4) Tactical Compound Bow - " << WeaponTable.generate("Tactical Compound Bow").getBuyPrice() << " Dust" << endl;
			cout << "5) Meteor Bow - " << WeaponTable.generate("Meteor Bow").getBuyPrice() << " Dust\n6) Star Bow - " << WeaponTable.generate("Star Bow").getBuyPrice() << " Dust" << endl;
			cout << "\n0) Exit" << endl;
			cin >> input2;
			switch (input2) {
			case 1:
				if (Charac.dust < WeaponTable.generate("Wooden Bow").getBuyPrice()) {
					cout << "You do not have enough dust." << endl;
					wait_enter();
					break;
				}
				else if (Charac.dust >= WeaponTable.generate("Wooden Bow").getBuyPrice()) {
					cout << "You buy the wooden bow for " << WeaponTable.generate("Wooden Bow").getBuyPrice() << " dust." << endl;
					Charac.dust = Charac.dust - WeaponTable.generate("Wooden Bow").getBuyPrice();
					Charac.inventory.addItem(WeaponTable.generate("Wooden Bow"));
					wait_enter();
					break;
				}
				break;
			case 2:
				if (Charac.dust < WeaponTable.generate("Reinforced Bow").getBuyPrice()) {
					cout << "You do not have enough dust." << endl;
					wait_enter();
					break;
				}
				else if (Charac.dust >= WeaponTable.generate("Reinforced Bow").getBuyPrice()) {
					cout << "You buy the Reinforced Bow for " << WeaponTable.generate("Reinforced Bow").getBuyPrice() << " dust." << endl;
					Charac.dust = Charac.dust - WeaponTable.generate("Reinforced Bow").getBuyPrice();
					Charac.inventory.addItem(WeaponTable.generate("Reinforced Bow"));
					wait_enter();
					break;
				}
				break;
			case 3:
				if (Charac.dust < WeaponTable.generate("Iron Bow").getBuyPrice()) {
					cout << "You do not have enough dust." << endl;
					wait_enter();
					break;
				}
				else if (Charac.dust >= WeaponTable.generate("Iron Bow").getBuyPrice()) {
					cout << "You buy the Iron Bow for " << WeaponTable.generate("Iron Bow").getBuyPrice() << " dust." << endl;
					Charac.dust = Charac.dust - WeaponTable.generate("Iron Bow").getBuyPrice();
					Charac.inventory.addItem(WeaponTable.generate("Iron Bow"));
					wait_enter();
					break;
				}
				break;
			case 4:
				if (Charac.dust < WeaponTable.generate("Tactical Compound Bow").getBuyPrice()) {
					cout << "You do not have enough dust." << endl;
					wait_enter();
					break;
				}
				else if (Charac.dust >= WeaponTable.generate("Tactical Compound Bow").getBuyPrice()) {
					cout << "You buy the Tactical Compound Bow for " << WeaponTable.generate("Tactical Compound Bow").getBuyPrice() << " dust." << endl;
					Charac.dust = Charac.dust - WeaponTable.generate("Tactical Compound Bow").getBuyPrice();
					Charac.inventory.addItem(WeaponTable.generate("Tactical Compound Bow"));
					wait_enter();
					break;
				}
				break;
			case 5:
				if (Charac.dust < WeaponTable.generate("Meteor Bow").getBuyPrice()) {
					cout << "You do not have enough dust." << endl;
					wait_enter();
					break;
				}
				else if (Charac.dust >= WeaponTable.generate("Meteor Bow").getBuyPrice()) {
					cout << "You buy the Meteor Bow for " << WeaponTable.generate("Meteor Bow").getBuyPrice() << " dust." << endl;
					Charac.dust = Charac.dust - WeaponTable.generate("Meteor Bow").getBuyPrice();
					Charac.inventory.addItem(WeaponTable.generate("Meteor Bow"));
					wait_enter();
					break;
				}
				break;
			case 6:
				if (Charac.dust < WeaponTable.generate("Star Bow").getBuyPrice()) {
					cout << "You do not have enough dust." << endl;
					wait_enter();
					break;
				}
				else if (Charac.dust >= WeaponTable.generate("Star Bow").getBuyPrice()) {
					cout << "You buy the Star Bow for " << WeaponTable.generate("Star Bow").getBuyPrice() << " dust." << endl;
					Charac.dust = Charac.dust - WeaponTable.generate("Star Bow").getBuyPrice();
					Charac.inventory.addItem(WeaponTable.generate("Star Bow"));
					wait_enter();
					break;
				}
				break;
			}
			break;
		case 3:
			ClearScreen();
			cout << "-*- The Magic's Gathering -*-" << endl;
			cout << "\nYou walk into the Magic's Gathering. A very happy human greets you\n'W-we-we have D&D Sessions on thursdays...' He says\nHe hands you a flyer\n'OH, and I-I also sell things...' He says." << endl;
			cout << "\n1) Wooden Staff - " << WeaponTable.generate("Wooden Staff").getBuyPrice() << " Dust\n2) Infused Staff - " << WeaponTable.generate("Infused Staff").getBuyPrice() << " Dust\n3) Cut Wand - " << WeaponTable.generate("Cut Wand").getBuyPrice() << " Dust\n4) Nuja Wand - " << WeaponTable.generate("Nuja Wand").getBuyPrice() << " Dust" << endl;
			cout << "5) F.I.L.O. - " << WeaponTable.generate("F.I.L.O.").getBuyPrice() << " Dust\n6) Staff of Mythos - " << WeaponTable.generate("Staff of Mythos").getBuyPrice() << " Dust" << endl;
			cout << "\n0) Exit" << endl;
			cin >> input2;
			switch (input2) {
			case 1:
				if (Charac.dust < WeaponTable.generate("Wooden Staff").getBuyPrice()) {
					cout << "You do not have enough dust." << endl;
					wait_enter();
					break;
				}
				else if (Charac.dust >= WeaponTable.generate("Wooden Staff").getBuyPrice()) {
					cout << "You buy the Wooden Staff for " << WeaponTable.generate("Wooden Staff").getBuyPrice() << " dust." << endl;
					Charac.dust = Charac.dust - WeaponTable.generate("Wooden Staff").getBuyPrice();
					Charac.inventory.addItem(WeaponTable.generate("Wooden Staff"));
					wait_enter();
					break;
				}
				break;
			case 2:
				if (Charac.dust < WeaponTable.generate("Infused Staff").getBuyPrice()) {
					cout << "You do not have enough dust." << endl;
					wait_enter();
					break;
				}
				else if (Charac.dust >= WeaponTable.generate("Infused Staff").getBuyPrice()) {
					cout << "You buy the Infused Staff for " << WeaponTable.generate("Infused Staff").getBuyPrice() << " dust." << endl;
					Charac.dust = Charac.dust - WeaponTable.generate("Infused Staff").getBuyPrice();
					Charac.inventory.addItem(WeaponTable.generate("Infused Staff"));
					wait_enter();
					break;
				}
				break;
			case 3:
				if (Charac.dust < WeaponTable.generate("Cut Wand").getBuyPrice()) {
					cout << "You do not have enough dust." << endl;
					wait_enter();
					break;
				}
				else if (Charac.dust >= WeaponTable.generate("Cut Wand").getBuyPrice()) {
					cout << "You buy the Cut Wand for " << WeaponTable.generate("Cut Wand").getBuyPrice() << " dust." << endl;
					Charac.dust = Charac.dust - WeaponTable.generate("Cut Wand").getBuyPrice();
					Charac.inventory.addItem(WeaponTable.generate("Cut Wand"));
					wait_enter();
					break;
				}
				break;
			case 4:
				if (Charac.dust < WeaponTable.generate("Nuja Wand").getBuyPrice()) {
					cout << "You do not have enough dust." << endl;
					wait_enter();
					break;
				}
				else if (Charac.dust >= WeaponTable.generate("Nuja Wand").getBuyPrice()) {
					cout << "You buy the Nuja Wand for " << WeaponTable.generate("Nuja Wand").getBuyPrice() << " dust." << endl;
					Charac.dust = Charac.dust - WeaponTable.generate("Nuja Wand").getBuyPrice();
					Charac.inventory.addItem(WeaponTable.generate("Nuja Wand"));
					wait_enter();
					break;
				}
				break;
			case 5:
				if (Charac.dust < WeaponTable.generate("F.I.L.O.").getBuyPrice()) {
					cout << "You do not have enough dust." << endl;
					wait_enter();
					break;
				}
				else if (Charac.dust >= WeaponTable.generate("F.I.L.O.").getBuyPrice()) {
					cout << "You buy F.I.L.O. for " << WeaponTable.generate("F.I.L.O.").getBuyPrice() << " dust." << endl;
					Charac.dust = Charac.dust - WeaponTable.generate("F.I.L.O.").getBuyPrice();
					Charac.inventory.addItem(WeaponTable.generate("F.I.L.O."));
					wait_enter();
					break;
				}
				break;
			case 6:
				if (Charac.dust < WeaponTable.generate("Staff of Mythos").getBuyPrice()) {
					cout << "You do not have enough dust." << endl;
					wait_enter();
					break;
				}
				else if (Charac.dust >= WeaponTable.generate("Staff of Mythos").getBuyPrice()) {
					cout << "You buy the Staff of Mythos for " << WeaponTable.generate("Staff of Mythos").getBuyPrice() << " dust." << endl;
					Charac.dust = Charac.dust - WeaponTable.generate("Staff of Mythos").getBuyPrice();
					Charac.inventory.addItem(WeaponTable.generate("Staff of Mythos"));
					wait_enter();
					break;
				}
				break;
			}
			break;
		case 4:
			ClearScreen();
			cout << "-*- Rocket Wrestling -*-" << endl;
			cout << "\nAs you walk in, a massive explosion rings out and two skeleton samurais\njump down from nowhere. They greet you with power gloves primed.\nThey lift up their weapons and smile. They show you around." << endl;
			cout << "\n1) Leather Gloves - " << WeaponTable.generate("Leather Gloves").getBuyPrice() << " Dust\n2) Red Rubber Gloves - " << WeaponTable.generate("Red Rubber Gloves").getBuyPrice() << " Dust\n3) Brass Knuckles - " << WeaponTable.generate("Brass Knuckles").getBuyPrice() << " Dust\n4) Power Glove - " << WeaponTable.generate("Power Glove").getBuyPrice() << " Dust" << endl;
			cout << "5) Torched Wristband - " << WeaponTable.generate("Torched Wristband").getBuyPrice() << " Dust\n6) Hell-Forged Wristband - " << WeaponTable.generate("Hell-Forged Wristband").getBuyPrice() << " Dust" << endl;
			cout << "\n0) Exit" << endl;
			cin >> input2;
			switch (input2) {
			case 1:
				if (Charac.dust < WeaponTable.generate("Leather Gloves").getBuyPrice()) {
					cout << "You do not have enough dust." << endl;
					wait_enter();
					break;
				}
				else if (Charac.dust >= WeaponTable.generate("Leather Gloves").getBuyPrice()) {
					cout << "You buy the Leather Gloves for " << WeaponTable.generate("Leather Gloves").getBuyPrice() << " dust." << endl;
					Charac.dust = Charac.dust - WeaponTable.generate("Leather Gloves").getBuyPrice();
					Charac.inventory.addItem(WeaponTable.generate("Leather Gloves"));
					wait_enter();
					break;
				}
				break;
			case 2:
				if (Charac.dust < WeaponTable.generate("Red Rubber Gloves").getBuyPrice()) {
					cout << "You do not have enough dust." << endl;
					wait_enter();
					break;
				}
				else if (Charac.dust >= WeaponTable.generate("Red Rubber Gloves").getBuyPrice()) {
					cout << "You buy the Red Rubber Gloves for " << WeaponTable.generate("Red Rubber Gloves").getBuyPrice() << " dust." << endl;
					Charac.dust = Charac.dust - WeaponTable.generate("Red Rubber Gloves").getBuyPrice();
					Charac.inventory.addItem(WeaponTable.generate("Red Rubber Gloves"));
					wait_enter();
					break;
				}
				break;
			case 3:
				if (Charac.dust < WeaponTable.generate("Brass Knuckles").getBuyPrice()) {
					cout << "You do not have enough dust." << endl;
					wait_enter();
					break;
				}
				else if (Charac.dust >= WeaponTable.generate("Brass Knuckles").getBuyPrice()) {
					cout << "You buy the Brass Knuckles for " << WeaponTable.generate("Brass Knuckles").getBuyPrice() << " dust." << endl;
					Charac.dust = Charac.dust - WeaponTable.generate("Brass Knuckles").getBuyPrice();
					Charac.inventory.addItem(WeaponTable.generate("Brass Knuckles"));
					wait_enter();
					break;
				}
				break;
			case 4:
				if (Charac.dust < WeaponTable.generate("Power Glove").getBuyPrice()) {
					cout << "You do not have enough dust." << endl;
					wait_enter();
					break;
				}
				else if (Charac.dust >= WeaponTable.generate("Power Glove").getBuyPrice()) {
					cout << "You buy the Power Glove for " << WeaponTable.generate("Power Glove").getBuyPrice() << " dust." << endl;
					Charac.dust = Charac.dust - WeaponTable.generate("Power Glove").getBuyPrice();
					Charac.inventory.addItem(WeaponTable.generate("Power Glove"));
					wait_enter();
					break;
				}
				break;
			case 5:
				if (Charac.dust < WeaponTable.generate("Torched Wristband").getBuyPrice()) {
					cout << "You do not have enough dust." << endl;
					wait_enter();
					break;
				}
				else if (Charac.dust >= WeaponTable.generate("Torched Wristband").getBuyPrice()) {
					cout << "You buy the Torched Wristband for " << WeaponTable.generate("Torched Wristband").getBuyPrice() << " dust." << endl;
					Charac.dust = Charac.dust - WeaponTable.generate("Torched Wristband").getBuyPrice();
					Charac.inventory.addItem(WeaponTable.generate("Torched Wristband"));
					wait_enter();
					break;
				}
				break;
			case 6:
				if (Charac.dust < WeaponTable.generate("Hell-Forged Wristband").getBuyPrice()) {
					cout << "You do not have enough dust." << endl;
					wait_enter();
					break;
				}
				else if (Charac.dust >= WeaponTable.generate("Hell-Forged Wristband").getBuyPrice()) {
					cout << "You buy the Hell-Forged Wristband for " << WeaponTable.generate("Hell-Forged Wristband").getBuyPrice() << " dust." << endl;
					Charac.dust = Charac.dust - WeaponTable.generate("Hell-Forged Wristband").getBuyPrice();
					Charac.inventory.addItem(WeaponTable.generate("Hell-Forged Wristband"));
					wait_enter();
					break;
				}
				break;
			}
			break;
		case 5:
			ClearScreen();
			cout << "-*- Mike's Friendly Store -*-" << endl;
			cout << "A very disgusting looking teen at the counter greets you as you walk in\n'Welcome to the store. SIR.' He says, with a very punchable face." << endl;
			cout << "\n1) Normal Health Potion - " << ConsumableTable.generate("Normal Health Potion").getBuyPrice() << " Dust\n2) Greater Health Potion - " << ConsumableTable.generate("Greater Health Potion").getBuyPrice() << " Dust\n3) Super Health Potion - " << ConsumableTable.generate("Super Health Potion").getBuyPrice() << " Dust"<< endl;
			cout << "4) Full Health Potion - " << ConsumableTable.generate("Full Health Potion").getBuyPrice() << " Dust\n\n5) Normal Mana Potion - " << ConsumableTable.generate("Normal Mana Potion").getBuyPrice() << " Dust\n6) Greater Mana Potion - " << ConsumableTable.generate("Greater Mana Potion").getBuyPrice() << " Dust" << endl;
			cout << "6) Super Mana Potion - " << ConsumableTable.generate("Super Mana Potion").getBuyPrice() << " Dust\n7) Full Mana Potion - " << ConsumableTable.generate("Full Mana Potion").getBuyPrice() << " Dust" << endl;
			cin >> input2;
			switch (input2) {
			case 1:
				cout << "How many would you like to buy? (" << ConsumableTable.generate("Normal Health Potion").getBuyPrice() << " Each)" << endl;
				cin >> input2;
				if (input2 * ConsumableTable.generate("Normal Health Potion").getBuyPrice() > Charac.dust) {
					cout << "You do not have enough dust!" << endl;
					wait_enter();
					home();
				}
				else if (input2 * ConsumableTable.generate("Normal Health Potion").getBuyPrice() <= Charac.dust) {
					cout << "You bought " << input2 << " Normal Health Potions for " << input2 * ConsumableTable.generate("Normal Health Potion").getBuyPrice() << " dust" << endl;
					Charac.dust -= input2 * ConsumableTable.generate("Normal Health Potion").getBuyPrice();
					for (std::size_t i = 0; i < input2; ++i)
						Charac.inventory.addItem(ConsumableTable.generate("Normal Health Potion"));
					wait_enter();
				}
				break;
				case 2:
				cout << "How many would you like to buy? (" << ConsumableTable.generate("Greater Health Potion").getBuyPrice() << " Each)" << endl;
				cin >> input2;
				if (input2 * ConsumableTable.generate("Greater Health Potion").getBuyPrice() > Charac.dust) {
					cout << "You do not have enough dust!" << endl;
					wait_enter();
					home();
				}
				else if (input2 * ConsumableTable.generate("Greater Health Potion").getBuyPrice() <= Charac.dust) {
					cout << "You bought " << input2 << " Greater Health Potions for " << input2 * ConsumableTable.generate("Greater Health Potion").getBuyPrice() << " dust" << endl;
					Charac.dust -= input2 * ConsumableTable.generate("Greater Health Potion").getBuyPrice();
					for (std::size_t i = 0; i < input2; ++i)
						Charac.inventory.addItem(ConsumableTable.generate("Greater Health Potion"));
					wait_enter();
				}
				break;
			}
			break;
		}
	}
}

void home() {
	bool homemenu = true;
	while (homemenu == true) {
		ClearScreen();
		cout << "-*- Home -*-" << endl;
		cout << "1) Explore\n2) Workshop\n3) Black Market\n4) Inventory\n5) Save" << endl;
		cout << "\n-*- Quick Stats -*-\nHP: " << Charac.hp << "        MP: " << Charac.mp << "\nDust: " << Charac.dust << endl;
		cin >> input;
		switch (input) {
		case 1:
			explore();
			break;
		case 2:
			workshop();
			break;
		case 3:
			blackmarket();
			break;
		case 4:
			inventory();
			break;
		}
	}
}

void pastselec() {

	int pastchoice[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	ClearScreen();
	cout << "-*- Past Selection -*-" << endl;
	cout << "Q1) Where did you come from?\n1) Fields of Forgiveness (Easiest)\n2) Dusty Farms (Easy)\n3) Scorched Forest (Normal)\n4) Corrupted Pastures (Hard)\n5) Doomed Lands (Doom)\n6) The Gates of Hell (Brutal)" << endl;
	cin >> pastchoice[0];
	if (pastchoice[0] < 1 || pastchoice[0] > 6) {
		cout << "That choice does not exist... Defaulting to 3. (Normal Difficulty)" << endl;
		pastchoice[0] = 3;
	}
	switch (pastchoice[0]) {
	case 1:
		Charac.difficultyN = "Easiest";
		Charac.difficultyD = .5;
		break;
	case 2:
		Charac.difficultyN = "Easy";
		Charac.difficultyD = .75;
		break;
	case 3:
		Charac.difficultyN = "Normal";
		Charac.difficultyD = 1;
		break; case 3267:
			cout << "Quickstart activated. Giving DEV Weapon." << endl;
			Charac.inventory.addItem(WeaponTable.generate("Modal Soul"));
			wait_enter();
			home();
			break;
		case 4:
			Charac.difficultyN = "Hard";
			Charac.difficultyD = 1.5;
			break;
		case 5:
			Charac.difficultyN = "Doom";
			Charac.difficultyD = 2.25;
			break;
		case 6:
			Charac.difficultyN = "Brutal";
			Charac.difficultyD = 3;
			break;
	}
	ClearScreen();
	cout << "Q2) What was your past profession?\n1) Fighter\n2) Summoner\n3) Hunter\n4) Scout\n5) Soldier" << endl;
	cin >> pastchoice[1];
	if (pastchoice[1] < 1 || pastchoice[1] > 5) {
		cout << "That choice does not exist... Defaulting to 1." << endl;
		pastchoice[1] = 1;
	}
	switch (pastchoice[1]) {
	case 1:
		Charac.strprof = Charac.strprof + .1;
		Charac.profession = "Fighter";
		break;
	case 2:
		Charac.itlprof = Charac.itlprof + .1;
		Charac.profession = "Summoner";
		break;
	case 3:
		Charac.crt = Charac.crt + 2;
		Acc.headdamagex = Acc.headdamagex + .25;
		Acc.chestdamagex = Acc.chestdamagex + .15;
		Acc.rightarmdamagex = Acc.rightarmdamagex + .1;
		Acc.leftarmdamagex = Acc.leftarmdamagex + .1;
		Acc.rightlegdamagex = Acc.rightlegdamagex + .1;
		Acc.leftlegdamagex = Acc.leftlegdamagex + .1;
		Charac.profession = "Hunter";
		break;
	case 4:
		Charac.spdprof = Charac.spdprof + .1;
		Charac.profession = "Scout";
		break;
	case 5:
		Charac.defprof = Charac.defprof + .1;
		Charac.profession = "Soldier";
		break;
	}
	ClearScreen();
	cout << "Q3) By whom were you necromanced?\n1) A Necromancer\n2) A Friend\n3) No-one." << endl;
	cin >> pastchoice[2];
	if (pastchoice[2] < 1 || pastchoice[2] > 3) {
		cout << "That choice does not exist... Defaulting to 1." << endl;
		pastchoice[2] = 1;
	}
	switch (pastchoice[2]) {
	case 1:
		Charac.str = Charac.str + 1;
		Charac.itl = Charac.itl + 1;
		break;
	case 2:
		Charac.def = Charac.def + 3;
		break;
	case 3:
		Charac.crt = Charac.crt + 1;
		Charac.spdprof = Charac.spdprof + .05;
	}
	ClearScreen();
	cout << "Q4) What weapon were you skilled with?\n1) Bow\n2) Sword\n3) Staff\n4) Fists." << endl;
	cin >> pastchoice[3];
	if (pastchoice[3] < 1 || pastchoice[3] > 4) {
		cout << "That choice does not exist... Defaulting to 1." << endl;
		pastchoice[3] = 1;
	}
	switch (pastchoice[3]) {
	case 1:
		Charac.bowprof = Charac.bowprof + .1;
		break;
	case 2:
		Charac.swordprof = Charac.swordprof + .1;
		break;
	case 3:
		Charac.staffprof = Charac.staffprof + .1;
		break;
	case 4:
		Charac.unarmedprof = Charac.unarmedprof + .1;
		break;
	}
	ClearScreen();
	cout << "Q5) " << endl;
	ClearScreen();
	cout << "Q10) Finally, what is your father's name? (No Spaces)" << endl;
	cin >> Charac.dad;
	for (size_t i = 0; i < Charac.dad.size(); i++) {
		Charac.seed += int(Charac.dad[i]);
	}
	srand(Charac.seed);
	Charac.maxHP = Charac.str * Charac.def * Charac.lvl + Charac.difficultyD;
	Charac.maxMP = Charac.itl * Charac.def * Charac.lvl + Charac.difficultyD;
	Charac.hp = Charac.maxHP;
	Charac.mp = Charac.maxMP;
	if (Charac.maxHP < 10) {
		Charac.maxHP = 10;
		Charac.hp = 10;
	}
	if (Charac.maxMP < 5) {
		Charac.maxMP = 5;
		Charac.mp = 5;
	}
	ClearScreen();
	cout << "Do these stats look ok?\n\nName: " << Charac.name << "\nRace: " << Charac.race << "\nClass: " << Charac.clas << "\nProfession: " << Charac.profession << "\n\nMax Health: " << Charac.maxHP << "\nMax Mana: " << Charac.maxMP << "\n\nStrength: " << Charac.str << "\nDefense: " << Charac.def << "\nIntelligence: " << Charac.itl << "\nSpeed: " << Charac.spd << "\nCritical Chance: " << Charac.crt << "\n\nDifficulty: " << Charac.difficultyN << endl;
	cout << "\n1) Yes \n2) No" << endl;
	cin >> input;
	switch (input) {
	case 1:
		Charac.maxHP = Charac.hp;
		Charac.maxMP = Charac.mp;
		Charac.inventory.addItem(WeaponTable.generate("Stick"));
		Charac.equipped = const_cast<Weapon*>(dynamic_cast<const Weapon*>(Charac.inventory.inspectItem(0)));
		home();
		break;
	case 2:
		Charac.str = 1;
		Charac.def = 1;
		Charac.itl = 1;
		Charac.spd = 1;
		Charac.crt = 1;
		Charac.strprof = 1.00;
		Charac.defprof = 1.00;
		Charac.spdprof = 1.00;
		Charac.itlprof = 1.00;
		Charac.bowprof = 1.00;
		Charac.swordprof = 1.00;
		Charac.staffprof = 1.00;
		Charac.unarmedprof = 1.00;
		Acc.headdamagex = 2;
		Acc.chestdamagex = 1;
		Acc.rightarmdamagex = 1;
		Acc.leftarmdamagex = 1;
		Acc.rightlegdamagex = 1;
		Acc.leftlegdamagex = 1;
		Charac.race = "None";
		Charac.clas = "None";
		chargen();
		break;
	}
}

void chargen() {
	bool chargenboolfin = false;
	while (chargenboolfin == false) {
		ClearScreen();
		cout << "-*- Character Generation -*-" << endl;
		cout << "1) Name" << endl;
		cout << "2) Class" << endl;
		cout << "3) Race" << endl;
		cout << "4) Continue to Past Selection" << endl;
		cout << "\n-*- Current Skeleton -*-" << endl;
		cout << "Name: " << Charac.name << "\nRace: " << Charac.race << "\nClass: " << Charac.clas << endl;
		cout << "\n-*- Stats -*- \nStrength: " << Charac.str << "\nDefense: " << Charac.def << "\nIntelligence: " << Charac.itl << "\nSpeed: " << Charac.spd << "\nCritical Chance: " << Charac.crt << endl;
		cin >> input;
		switch (input) {
		case 1:
			cout << "Input your name. No Spaces." << endl;
			cin >> Charac.name;
			continue;
		case 2:
			ClearScreen();
			cout << "-*- Classes -*-" << endl;
			cout << "1) Skeleton Warrior - \nA warrior with more attack spells\n\n2) Skeleton Mage - \nA mage with destructive and healing powers\n\n3) Skeleton Warlock - \nA dangerous class with more spells focusing on damage\n\n4) Bone Baron -\nA skeleton with no spells, only melee" << endl;
			cin >> input;
			if (input < 1 || input > 4) {
				cout << "You cannot do that." << endl;
				wait_enter();
				continue;
			}
			switch (input) {
			case 1:
				Charac.clas = "Skeleton Warrior";
				continue;
			case 2:
				Charac.clas = "Skeleton Mage";
				continue;
			case 3:
				Charac.clas = "Skeleton Warlock";
				continue;
			case 4:
				Charac.clas = "Bone Baron";
				continue;
			}
			break;
		case 4:
			if (Charac.race == "None" || Charac.clas == "None") {
				cout << "You cannot do that." << endl;
				wait_enter();
				continue;
			}
			pastselec();
			break;
		case 3:
			ClearScreen();
			Charac.str = 1;
			Charac.itl = 1;
			Charac.def = 1;
			Charac.crt = 1;
			Charac.spd = 1;
			ClearScreen();
			cout << "-*- Race -*-" << endl;
			cout << "1) Human Skeleton - \n+3 Str || +2 Def\n\n2) Kobold Skeleton -\n+3 Crt || +2 Spd\n\n3) Bone Dragonborn - \n+5 Str \n\n4) Skeleton Scholar - \n+4 Itl || +1 Spd \n\n5) Coag Skeleton - \n+5 Def\n\n6) Dust Skeleton - \n+1 All" << endl;
			cin >> input;
			switch (input) {
			case 1:
				Charac.race = "Human Skeleton";
				Charac.str = Charac.str + 3;
				Charac.def = Charac.def + 2;
				continue;
			case 2:
				Charac.race = "Kobold Skeleton";
				Charac.crt = Charac.crt + 3;
				Charac.spd = Charac.spd + 2;
				continue;
			case 3:
				Charac.race = "Bone Dragonborn";
				Charac.str = Charac.str + 5;
				continue;
			case 4:
				Charac.race = "Skeleton Scholar";
				Charac.itl = Charac.itl + 4;
				Charac.spd = Charac.spd + 1;
				continue;
			case 5:
				Charac.race = "Coag Skeleton";
				Charac.def = Charac.def + 5;
				continue;
			case 6:
				Charac.race = "Dust Skeleton";
				Charac.str = Charac.str + 1;
				Charac.def = Charac.def + 1;
				Charac.crt = Charac.crt + 1;
				Charac.spd = Charac.spd + 1;
				Charac.itl = Charac.itl + 1;
				continue;
			}
		}
		break;
	}
}

int main()
{
	cout << "-*- Bones -*-\n1) Start\n2) Load\n\nWARNING: Loads don't work." << endl; //Start Screen
	cin >> input;
	switch (input) { //Switch statement for the starting, can either be chargen or load
	case 1:
		chargen();
		break;
	case 2:
		break;
	case 3267:
		cout << "Quickstart activated. Giving DEV Weapon." << endl;
		Charac.inventory.addItem(WeaponTable.generate("Modal Soul"));
		Charac.equipped = const_cast<Weapon*>(dynamic_cast<const Weapon*>(Charac.inventory.inspectItem(0)));
		Charac.dust = 99999;
		cin >> Charac.dad;
		for (size_t i = 0; i < Charac.dad.size(); i++) {
			Charac.seed += int(Charac.dad[i]);
		}
		srand(Charac.seed);
		wait_enter();
		Charac.inventory.addItem(ConsumableTable.generate("Normal Health Potion"));
		Charac.inventory.addItem(ConsumableTable.generate("Normal Health Potion"));
		Charac.inventory.addItem(ConsumableTable.generate("Greater Health Potion"));
		Charac.inventory.addItem(ConsumableTable.generate("Super Health Potion"));
		home();
		break;
	}
	return 0;
}
