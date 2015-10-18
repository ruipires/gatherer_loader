#define CATCH_CONFIG_MAIN
#include <diego/catch/catch.hpp>
#include "../gatherer_loader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <Document.h>
#include <Selection.h>
#include <Node.h>
#include <boost/algorithm/string/trim_all.hpp>


using std::string;
using std::istream;
using std::ifstream;

namespace
{
string readFullStream(istream &in)
{
	string result;

	for(int c = in.get(); in && c!=EOF; c=in.get())
		result += c;

	return result;
}
}

TEST_CASE( "Load text from gatherer card details page", "[gatherer single_card]" )
{
	using gatherer::Card;

	ifstream input("sennin/gatherer_loader/data/402093.html");
	REQUIRE(input);

	string in = readFullStream(input);
	CDocument doc;
	doc.parse(in.c_str());

	Card card = gatherer::load_single_card(doc);

	REQUIRE(card.name == "Void Winnower");
	REQUIRE(card.manaCost == "{9}");
	REQUIRE(card.convertedManaCost == 9);
	REQUIRE(card.types == "Creature — Eldrazi");
	REQUIRE(card.text == "Your opponents can't cast spells with even converted mana costs. <i>(Zero is even.)</i>\n"
		"Your opponents can't block with creatures with even converted mana costs.");

	REQUIRE(card.flavour == "\"Have you ever seen a world fall to its knees? Watch, and learn.\"—Ob Nixilis");
	REQUIRE(card.powerThoughness == "11 / 9");
//	REQUIRE(card.expansion == "Battle for Zendikar");
	REQUIRE(card.rarity == "Mythic Rare");
	REQUIRE(card.cardNumber == 17);
	REQUIRE(card.artist == "Chase Stone");
}
