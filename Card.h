#ifndef GATHERER_LOADER_CARD_H
#define GATHERER_LOADER_CARD_H

#include <string>

namespace gatherer
{

class Card
{
public:
	std::string name;
	std::string manaCost;
	uint8_t convertedManaCost;
	std::string types;
	std::string text;
	std::string flavour;
	std::string powerThoughness;
	std::string expansion;
	std::string rarity;
	uint8_t cardNumber;
	std::string artist;
	std::string url;

	//TODO:RP missing list of rulings.
};


}

#endif
