//============================================================================
// Name        : DungeonMasterCampaignCreator.cpp
// Author      : Bradley Poleski
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Created for DMs to create and manage their own world/campaign/game
//============================================================================

#include <iostream>
#include <array>
#include <string>
#include <sstream>
#include <sstream>
#include <MMSystem.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <fstream>		//Needed to read and write files
#include <SFML/Graphics.hpp>
#include <graphics.h>
#include <conio.h>
#include <windows.h>

using namespace std;

/*Races
 * AARAKOCRA
 * 	DEX: +1
 * 	WIS: +1
 * 	AGE: 3-30
 * 	ALIGNMENT: GOOD
 * 	SIZE: 5 FT 80-100LBS
 * 	SPEED: 25FT
 * 	FLIGHT: 50 FT W/O MED OR HEAVY ARMOR
 * 	TALONS: UNARMED STRIKES 1D4 SLASH ON HIT
 * 	LANG: COMMON, AARAKOCRA, AURAN
 *
 * DRAGONBORN
 * 	STR: +2
 * 	CHA: +1
 * 	AGE: 15-80
 * 	ALIGNMENT: GOOD
 * 	SIZE: >6 FT 250LBS MED
 * 	SPEED: 30FT
 * 	DRACONIC ANCESTRY:
 * 		Dragon		Damage Type		Breath Weapon
		Black		Acid			5 by 30 ft. line (Dex. save)
		Blue		Lightning		5 by 30 ft. line (Dex. save)
		Brass		Fire			5 by 30 ft. line (Dex. save)
		Bronze		Lightning		5 by 30 ft. line (Dex. save)
		Copper		Acid			5 by 30 ft. line (Dex. save)
		Gold		Fire			15 ft. cone (Dex. save)
		Green		Poison			15 ft. cone (Con. save)
		Red			Fire			15 ft. cone (Dex. save)
		Silver		Cold			15 ft. cone (Con. save)
		White		Cold			15 ft. cone (Con. save)
 * 	BREATH WEAPON: You can use your action to exhale destructive energy. Your draconic ancestry determines the size, shape, and damage type of the exhalation. When you use your breath weapon, each creature in the area of the exhalation must make a saving throw, the type of which is determined by your draconic ancestry. The DC for this saving throw equals 8 + your Constitution modifier + your proficiency bonus. A creature takes 2d6 damage on a failed save, and half as much damage on a successful one. The damage increases to 3d6 at 6th level, 4d6 at 11th level, and 5d6 at 16th level. After you use your breath weapon, you can’t use it again until you complete a short or long rest.
 *  DAMAGE RESISTANCE TO TYPE OF DRACONIC ANCESTRY
 * 	LANG: COMMON, DRACONIC
 *
 * DWARF
 * 	SUBRACE: HILL
 * 	CON: +2
 * 	WIS: +1
 * 	HP +1 (+1) EVERY LEVEL
 * 	AGE: 50-350
 * 	ALIGNMENT: GOOD
 * 	SIZE: 4-5 FT 150LBS MED
 * 	SPEED: 25FT NOT REDUCED BY ARMOR
 * 	DARKVISION: Accustomed to life underground, you have superior vision in dark and dim conditions. You can see in dim light within 60 feet of you as if it were bright light, and in darkness as if it were dim light. You can’t discern color in darkness, only shades of gray.
 * 	DWARVEN RESILIENCE: You have advantage on saving throws against poison, and you have resistance against poison damage (explained in the “Combat” section).
 *  DWARVEN COMBAT TRAINING:  You have advantage on saving throws against poison, and you have resistance against poison damage (explained in the “Combat” section).
 * 	TOOL PROF: You gain proficiency with the artisan’s tools of your choice: smith’s tools, brewer’s supplies, or mason’s tools.
 * 	STONE CUTTING: Whenever you make an Intelligence (History) check related to the origin of stonework, you are considered proficient in the History skill and add double your proficiency bonus to the check, instead of your normal proficiency bonus.
 * 	LANG: COMMON, DWARVISH
 *
 * 	SUBRACE: MOUNTAIN
 * 	CON: +2
 * 	STR: +2
 * 	AGE: 50-350
 * 	ALIGNMENT: GOOD
 * 	SIZE: 4-5 FT 150LBS MED
 * 	SPEED: 25FT NOT REDUCED BY ARMOR
 * 	DARKVISION: Accustomed to life underground, you have superior vision in dark and dim conditions. You can see in dim light within 60 feet of you as if it were bright light, and in darkness as if it were dim light. You can’t discern color in darkness, only shades of gray.
 * 	DWARVEN RESILIENCE: You have advantage on saving throws against poison, and you have resistance against poison damage (explained in the “Combat” section).
 *  DWARVEN COMBAT TRAINING:  You have advantage on saving throws against poison, and you have resistance against poison damage (explained in the “Combat” section).
 * 	TOOL PROF: You gain proficiency with the artisan’s tools of your choice: smith’s tools, brewer’s supplies, or mason’s tools.
 * 	STONE CUTTING: Whenever you make an Intelligence (History) check related to the origin of stonework, you are considered proficient in the History skill and add double your proficiency bonus to the check, instead of your normal proficiency bonus.
 * 	LANG: COMMON, DWARVISH
 * 	ARMOR TRAINING: PROF IN LIGHT & MED ARMOR
 *
 * ELF
 * 	SUBRACE: ELADRIN
 * 		DEX: +2
 * 		AGE: 100-750
 * 		ALIGN: CHAOTIC GOOD
 * 		SIZE: 5-6FT MED
 * 		SPEED: 30FT
 * 		DARKVISION: Accustomed to twilit forests and the night sky, you have superior vision in dark and dim conditions. You can see in dim light within 60 feet of you as if it were bright light, and in darkness as if it were dim light. You can’t discern color in darkness, only shades of gray. *
 * 		KEEN SENSES: PROF IN PERCEPTION
 * 		FEY ANCESTRY: You have advantage on saving throws against being charmed, and magic can’t put you to sleep.
 * 		TRANCE: Elves don’t need to sleep. Instead, they meditate deeply, remaining semiconscious, for 4 hours a day. (The Common word for such meditation is “trance.”) While meditating, you can dream after a fashion; such dreams are actually mental exercises that have become reflexive through years of practice. After resting in this way, you gain the same benefit that a human does from 8 hours of sleep.
 * 		LANG: COMMON, ELVISH
 * 		INT: +1
 * 		ELF WEAPON TRAINING: You have proficiency with the longsword, shortsword, shortbow, and longbow.
 * 		FEY STEP: You can cast the misty step spell once using this trait. You regain the ability to do so when you finish a short or long rest.
 * 	SUBRACE: HIGH
 * 		DEX: +2
 * 		AGE: 100-750
 * 		ALIGN: CHAOTIC GOOD
 * 		SIZE: 5-6FT MED
 * 		SPEED: 30FT
 * 		DARKVISION: Accustomed to twilit forests and the night sky, you have superior vision in dark and dim conditions. You can see in dim light within 60 feet of you as if it were bright light, and in darkness as if it were dim light. You can’t discern color in darkness, only shades of gray. *
 * 		KEEN SENSES: PROF IN PERCEPTION
 * 		FEY ANCESTRY: You have advantage on saving throws against being charmed, and magic can’t put you to sleep.
 * 		TRANCE: Elves don’t need to sleep. Instead, they meditate deeply, remaining semiconscious, for 4 hours a day. (The Common word for such meditation is “trance.”) While meditating, you can dream after a fashion; such dreams are actually mental exercises that have become reflexive through years of practice. After resting in this way, you gain the same benefit that a human does from 8 hours of sleep.
 * 		LANG: COMMON, ELVISH
 * 		INT: +1
 * 		ELF WEAPON TRAINING: You have proficiency with the longsword, shortsword, shortbow, and longbow.
 * 		CANTRIP: You know one cantrip of your choice from the wizard spell list. Intelligence is your spellcasting ability for it.
 * 		EXTRA LANGUAGE
 *
 * 	SUBRACE: WOOD
 * 		DEX: +2
 * 		AGE: 100-750
 * 		ALIGN: CHAOTIC GOOD
 * 		SIZE: 5-6FT MED
 * 		SPEED: 30FT
 * 		DARKVISION: Accustomed to twilit forests and the night sky, you have superior vision in dark and dim conditions. You can see in dim light within 60 feet of you as if it were bright light, and in darkness as if it were dim light. You can’t discern color in darkness, only shades of gray. *
 * 		KEEN SENSES: PROF IN PERCEPTION
 * 		FEY ANCESTRY: You have advantage on saving throws against being charmed, and magic can’t put you to sleep.
 * 		TRANCE: Elves don’t need to sleep. Instead, they meditate deeply, remaining semiconscious, for 4 hours a day. (The Common word for such meditation is “trance.”) While meditating, you can dream after a fashion; such dreams are actually mental exercises that have become reflexive through years of practice. After resting in this way, you gain the same benefit that a human does from 8 hours of sleep.
 * 		LANG: COMMON, ELVISH
 * 		WIS: +1
 * 		ELF WEAPON TRAINING: You have proficiency with the longsword, shortsword, shortbow, and longbow.
 * 		FLEET OF FOOT: SPEED 35 FT
 * 		MASK OF THE WILD: You can attempt to hide even when you are only lightly obscured by foliage, heavy rain, falling snow, mist, and other natural phenomena.
 * GENASI
 * 	SUBRACE: AIR
 * 		CONST: +2
 * 		AGE: 18-120
 * 		ALIGN: NEUTRAL
 * 		SIZE: 5-6FT MED
 * 		SPEED: 30FT
 * 		UNENDING BREATH: You can hold your breath indefinitely while you’re not incapacitated.
 * 		MINGLE WITH THE WIND: You can cast the levitate spell once with this trait, requiring no material components, and you regain the ability to cast it this way when you finish a long rest. Constitution is your spellcasting ability for this spell.
 * 		LANG: COMMON, PRIMORDIAL
 * 		DEX: +1
 *
 * 	SUBRACE: EARTH
 * 		CONST: +2
 * 		AGE: 18-120
 * 		ALIGN: NEUTRAL
 * 		SIZE: 5-6FT MED
 * 		SPEED: 30FT
 * 		EARTH WALK: You can move across difficult terrain made of earth or stone without expending extra movement. * 		MINGLE WITH THE WIND: You can cast the levitate spell once with this trait, requiring no material components, and you regain the ability to cast it this way when you finish a long rest. Constitution is your spellcasting ability for this spell.
 * 		MERGE WITH STONE: You can cast the pass without trace spell once with this trait, requiring no material components, and you regain the ability to cast it this way when you finish a long rest. Constitution is your spellcasting ability for this spell.
 * 		LANG: COMMON, PRIMORDIAL
 * 		STR: +1
 *
 * 	SUBRACE: FIRE
 * 		CONST: +2
 * 		AGE: 18-120
 * 		ALIGN: NEUTRAL
 * 		SIZE: 5-6FT MED
 * 		SPEED: 30FT
 *		DARKVISION: You can see in dim light within 60 feet of you as if it were bright light, and in darkness as if it were dim light. Your ties to the Elemental Plane of Fire make your darkvision unusual: everything you see in darkness is in a shade of red.
 * 		FIRE RESITANCE
 * 		REACH THE BLAZE: You know the produce flame cantrip. Once you reach 3rd level, you can cast the burning hands spell once with this trait as a 1st-level spell, and you regain the ability to cast it this way when you finish a long rest. Constitution is your spellcasting ability for these spells.
 * 		LANG: COMMON, PRIMORDIAL
 * 		INT: +1
 *
 * 	SUBRACE: WATER
 * 		CONST: +2
 * 		AGE: 18-120
 * 		ALIGN: NEUTRAL
 * 		SIZE: 5-6FT MED
 * 		SPEED: 30FT
 * 		ACID RESITANCE
 * 		AMPHIBIOUS:  CAN BREATHE AIR AND WATER
 * 		SWIM: SPEED 30FT
 * 		CALL TO THE WAVE: You know the shape water cantrip. When you reach 3rd level, you can cast the create or destroy water spell as a 2nd-level spell once with this trait, and you regain the ability to cast it this way when you finish a long rest. Constitution is your spellcasting ability for these spells.
 * 		LANG: COMMON, PRIMORDIAL
 * 		INT: +1
 *
 * GNOME
 * 	SUBRACE: DEEP
 * 		INT: +2
 * 		AGE: 25-200/250
 * 		ALIGN: NEUTRAL
 * 		SIZE: 3-3.5FT 80-120LBS SM
 * 		SPEED: 25FT
 * 		GNOME CUNNING: ADV ON INT, WIS AND CHAR THROW AGAINST MAGIC
 * 		SUPERIOR DARKVISION: Your darkvision has a radius of 120 feet.
 * 		STONE CAMO: You have advantage on Dexterity (stealth) checks to hide in rocky terrain.
 * 		LANG: COMMON, GNOMISH AND UNDERCOMMON
 * 		DEX: +1
 *
 * 	SUBRACE: ROCK
 * 		INT: +2
 * 		AGE: 25-200/250
 * 		ALIGN: NEUTRAL
 * 		SIZE: 3-4FT 40LBS SM
 * 		SPEED: 25FT
 * 		GNOME CUNNING: ADV ON INT, WIS AND CHAR THROW AGAINST MAGIC
 * 		DARKVISION: Accustomed to life underground, you have superior vision in dark and dim conditions. You can see in dim light within 60 feet of you as if it were bright light, and in darkness as if it were dim light. You can’t discern color in darkness, only shades of gray. * 		STONE CAMO: You have advantage on Dexterity (stealth) checks to hide in rocky terrain.
 * 		LANG: COMMON GNOMISH
 * 		ARTIFICER'S LORE: Whenever you make an Intelligence (History) check related to magic items, alchemical objects, or technological devices, you can add twice your proficiency bonus, instead of any proficiency bonus you normally apply.
 * 		TINKER: You have proficiency with artisan’s tools (tinker’s tools). Using those tools, you can spend 1 hour and 10 gp worth of materials to construct a Tiny clockwork device (AC 5, 1 hp). The device ceases to function after 24 hours (unless you spend 1 hour repairing it to keep the device functioning), or when you use your action to dismantle it; at that time, you can reclaim the materials used to create it. You can have up to three such devices active at a time.
			When you create a device, choose one of the following options:
			Clockwork Toy. This toy is a clockwork animal, monster, or person, such as a frog, mouse, bird, dragon, or soldier. When placed on the ground, the toy moves 5 feet across the ground on each of your turns in a random direction. It makes noises as appropriate to the creature it represents.
			Fire Starter. The device produces a miniature flame, which you can use to light a candle, torch, or campfire. Using the device requires your action.
			Music Box. When opened, this music box plays a single song at a moderate volume.
			The box stops playing when it reaches the song’s end or when it is closed.
 * 		CONS: +1
 *
 * GOLIATH
 * 	STR: +2
 * 	CON: +1
 * 	AGE: 18-<100
 * 	ALIGN: NEUTRAL
 * 	SIZE: 7-8FT 280-340LBS MED
 * 	SPEED: 30 FT
 * 	NATURAL ATHELETE: PROF IN ATHLETICS
 * 	STONE'S ENDURANCE: You can focus yourself to occasionally shrug off injury. When you take damage, you can use your reaction to roll a d12. Add your Constitution modifier to the number rolled, and reduce the damage by that total. After you use this trait, you can’t use it again until you finish a short or long rest.
 * 	POWERFUL BUILD: You count as one size larger when determining your carrying capacity and the weight you can push, drag, or lift.
 * 	MOUNTAIN BORN: You’re acclimated to high altitude, including elevations above 20,000 feet. You’re also naturally adapted to cold climates, as described in chapter 5 of the Dungeon Master’s Guide.
 * 	LANG: COMMON, GIANT
 *
 * HALF-ELF
 * 	CHAR: +2
 * 	+1 TO TWO OTHER ABILITIES
 * 	AGE: 20-180
 * 	SIZE: 5-6FT MED
 * 	SPEED: 30 FT
 * 	DARKVISION: Thanks to your elf blood, you have superior vision in dark and dim conditions. You can see in dim light within 60 feet of you as if it were bright light, and in darkness as if it were dim light. You can’t discern color in darkness, only shades of gray.
 * 	FEY ANCESTRY: You have advantage on saving throws against being charmed, and magic can’t put you to sleep.
 * 	SKILL VERSATILITY: You gain proficiency in two skills of your choice.
 * 	LANG: COMMON ELVISH +1 OTHER
 *
 * HALF-ORC
 * 	STR: +2
 * 	CON: +1
 * 	AGE: 14-75
 * 	SIZE: 5-6FT MED
 * 	SPEED: 30FT
 * 	DARKVISION:Thanks to your orc blood, you have superior vision in dark and dim conditions. You can see in dim light within 60 feet of you as if it were bright light, and in darkness as if it were dim light. You can’t discern color in darkness, only shades of gray.
 * 	MENACING:You gain proficiency in the Intimidation skill.
 * 	RELENTLESS ENDURANCE:When you are reduced to 0 hit points but not killed outright, you can drop to 1 hit point instead. You can’t use this feature again until you finish a long rest.
 * 	SAVAGE ATTACKS:When you score a critical hit with a melee weapon attack, you can roll one of the weapon’s damage dice one additional time and add it to the extra damage of the critical hit.
 * 	LANG: COMMON AND ORC
 *
 * HAFLING
 * HUMAN
 * TIEFLING
 * AASIMAR
 */
class Civilization {
	/*
	concepts
	Town
	Village
	Tribe
	has market?
	has inn?
	has armory?
	has general store?
	race living there


	*/

};

class Scene {
	/*
	picture
	music
	characters
		movement
	text

	*/

};

class MapOctogon {
	/*Map Concepts
	Mountain
	Desert
	Forest
	Swamp
	Tundra
	plains
	ocean
	lake
	river
	village/city/town etc.

	*/

private:



 };
 

 class Monster{
	 //variables
	 char size, type, alignment;
	 int level, armorClass, hitPoints, speed, strength, constitution, intelligence, wisdom, charisma;



	 //setters

	 //getters

	 //constructors

	 //methods


 };

 class Dice{
 private:
	 //variables
	 int sides, roll;

 public:
	 //setters
	 void setSides(int dnum){
		 sides=dnum;
	 }
	 void setRoll(int rollNum) {
		 roll = rollNum;
	 }

	 //getters
	 int getSides(){
		 return sides;
	 }

	 //constructors
	 Dice(){
		 setSides(6);
	 }

	 Dice(int dnum){
		 setSides(dnum);
	 }
	 //methods
	 void printDiceSides(){
		 cout << sides;
	 }

	 int diceRoll() {
		 roll = rand() % sides + 1;
		 return roll;
	 }


 };

 

 class Weapon {
	 //variables
	 string name, properties, damageName, damageType;//Damage name includes whole damage description ie 1d6/2d20
	 float weight;
	 int weaponNum, cost, damageDie, damageRoll; //Damage die is used for how many die are used for the weapon roll, Damage roll is used for how many sides the die have

 public:
	 //setters
	 void setWeaponNum(int permWeaponNum) {
		 weaponNum = permWeaponNum;
	 }

	 void setDamage(string damage) {
		 damageName = damage;
		 int tempDie, tempDieRoll;

		 if (damage.length() == 3) { //takes d out of damage  for 3 char string ie 1d6 and assigns die and sides of dice to roll
			 stringstream stringToInt(damage[0]);
			 stringToInt >> damageDie;
		 }
		 else { //takes d out of damage  for 4 char string ie 1d20 and assigns die and sides of dice to roll

			 stringstream dieToInt(damage.substr(0, 1));

			 dieToInt >> tempDie;
			 damageDie = tempDie;

			 stringstream rollToInt(damage.substr(2, 1));

			 rollToInt >> tempDieRoll;
			 damageRoll = tempDieRoll;

		 }

	 }
	 void setProperties(string weapondescription) {
		 properties = weapondescription;
	 }

	 void setDamageType(string typeDamage) {
		 damageType = typeDamage;
	 }

	void setName(string weaponName) {
		 name = weaponName;
	 }

	 void setWeight(float weaponWeight) {
		 weight = weaponWeight;
	 }

	 void setCost(int weaponCost) {
		 cost = weaponCost;
	 }

	 //getters
	
	 int getNum() {
		 return weaponNum;
	 }

	string getName() { 
		 return name;
	 }
	 string getProperties() {
		 return properties;
	 }
	 string getDamageName() {
		 return damageName;
	 }
	 string getDamageType() {
		 return damageType;
	 }
	 float getWeight() {
		 return weight;
	 }
	 int getCost() {
		 return cost;
	 }
	 int getDamageDie() {
		 return damageDie;
	 }
	 int getDamageRoll(){
		 return damageRoll;
	 }


	 //constructors
	 Weapon() {}



	 Weapon(string weaponName, int weaponCost, string weaponDamage, float weaponWeight, string weaponProperties) {
		 setName(weaponName);
		 setDamage(weaponDamage);
		 setWeight(weaponWeight);
		 setCost(weaponCost);
		 setProperties(weaponProperties);
	 }

	 //methods
	 void printWeaponProps() {
		 cout << "------------------------" << endl;
		 cout << "Name: " << name << endl;
		 cout << "Value: " << cost << " GP" << endl;
		 cout << "Damage: " << damageName << endl;
		 cout << "Weight: " << weight << endl;
		 cout << "Properties: " << endl;
		 int propCharSpot=0;
		 while (propCharSpot < properties.length()) {
			 for (int j = 0; j < 24; j++) {
				 cout << properties[propCharSpot];
				 propCharSpot++;
			 }
			 cout << endl;
		 }
		 cout << "------------------------" << endl;
	 }
 };

 

 class Consumables {

 };

 class Character {
 protected:
	 //variables
	 string name;
	 int hitPoints, armorRating, inventorySpace=0;
	 Weapon weaponInventory[100];

	 //setters
	 void setName(string charName) {
		 name = charName;
	 }
	 void setHP(int hp) {
		 hitPoints = hp;
	 }
	 void setarmorRating(int ar) {
		 armorRating = ar;
	 }
	 //getters
	 int getInventorySpace(){
		 return inventorySpace;
	 }
	 Weapon getInventoryWeapon(int inventorySlot) {
		 return weaponInventory[inventorySlot];
	 }

 public:

	 //constructors
	 Character() {}
	 Character(string charName) {
		 setName(charName);
	 }
	 Character(string charName, int hp) {
		 setName(charName);
		 setHP(hp);
	 }
	 Character(string charName, int hp, int ar) {
		 setName(charName);
		 setHP(hp);
		 setarmorRating(ar);
	 }

	 //methods
	 void addWeapontoInventory(Weapon newItem) {
		 weaponInventory[inventorySpace] = newItem;
		 inventorySpace++;
	 }

	 /*
	 void attackByWeaponName(Character character1, string attkweapname, Character character2) {
		 Weapon weaponUsed;
		 Dice dice;
				for (int i = 0; i < character1.getInventorySpace(); i++) {
					Weapon tempItem = character1.getInventoryWeapon(i);
					string tempItemName = tempItem.getName();

					if(tempItemName == attackByWeaponName)
						weaponUsed = character1.getInventoryWeapon(i);
					}

		 }

	 void attackByWeaponNum(Character character1, int attkweapnum, Character character2) {
		 Weapon weaponUsed;
		 for (int i = 0; i < character1.getInventorySpace(); i++) {
			 if (attkweapnum == character1.getInventoryWeapon().getNum()) {
				 weaponUsed = character1.getInventoryWeapon();
			 }
			 else {}
		 }
	 }*/
 };


int main() {
	srand(time(NULL)); //Randomizes time for rolls

	/* Test for substrings
	string testString = "This is the string I plan to test";	
	string segmentString = testString.substr(0, 4);

	string newString = testString.substr(6, 1);



	cout << segmentString;
	cout << endl;
	cout << newString;*/ 

	
	/* Test for string to int
	string damage = "1d6";
	int die, roll;

	stringstream stringToInt(damage.substr(0,1));

	 stringToInt >> die;

	 cout << die << endl;;

	 stringstream rollToInt(damage.substr(2, 1));

	 rollToInt >> roll;

	 cout << roll;*/ 

	/*
	string line;
	ifstream weaponFile("WeaponList.txt");
	if (weaponFile.is_open())*/


	//Graphic 
	/*sf::RenderWindow window(sf::VideoMode(800, 600), "Title");

	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
	}*/

	return 0;

}
