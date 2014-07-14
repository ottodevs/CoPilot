#include "hs/concepts.h"

std::map<std::string,CardBase> CardBase::CardList=std::map<std::string,CardBase>();
/*
Card::Card(void) : cost(0),type(creature),rarity(common),
	set(basic),card_class(Hero::none) {
}

void Card::Print(void) {
	std::cout<<"CardList:\n";
	for(std::map<std::string,Card>::const_iterator itr=CardList.begin();
	itr!=CardList.end();++itr) {
		std::cout<<itr->first<<"{"<<itr->second.cost<<","
			<<itr->second.type<<","<<itr->second.rarity<<","
			<<itr->second.set<<","<<itr->second.card_class
		<<"}"<<std::endl;
	}
	std::cout<<"CardList end"<<std::endl;
}

std::unordered_set<StrEnum,StrEnum::StrHash> Hero::type=std::unordered_set<StrEnum,StrEnum::StrHash>({
	StrEnum("none"),StrEnum("Druid"),StrEnum("Hunter"),StrEnum("Mage"),StrEnum("Paladin"),
	StrEnum("Priest"),StrEnum("Rogue"),StrEnum("Shaman"),StrEnum("Warlock"),StrEnum("Warrior")});
*/
