#include "gatherer_loader.h"
#include <Document.h>
#include <Selection.h>
#include <Node.h>
#include <boost/algorithm/string/trim_all.hpp>
#include <boost/algorithm/clamp.hpp>
#include <limits>

#include <iostream>

namespace
{
using std::string;

template<typename TARGET, typename SOURCE>
void clamp(TARGET &target, SOURCE source)
{
	using std::numeric_limits;
	target = boost::algorithm::clamp(source, numeric_limits<TARGET>::min(), numeric_limits<TARGET>::max());
};

string load_text(CDocument& doc, string const& selector)
{
	string result;
	CSelection c = doc.find(selector);

	if(c.nodeNum() > 0)
	{
		CNode node = c.nodeAt(0);
		result = boost::trim_all_copy(node.text());
	}

	return result;
}

string load_rules_text(CDocument& doc, string const& selector="#ctl00_ctl00_ctl00_MainContent_SubContent_SubContent_textRow .value")
{
	string result;
	CSelection c = doc.find(selector);

	CSelection cardTextBoxes = c.find(".cardtextbox");

	for(int i=0, size=cardTextBoxes.nodeNum(); i!=size; ++i)
	{
		if(i!=0)
			result+="\n";

		CNode node = cardTextBoxes.nodeAt(i);

		for(int j=0, size2=node.childNum(); j!=size2; ++j)
		{
			CNode innerNode = node.childAt(j);
			if(innerNode.tag() == "i")
				result += "<i>";

			result += innerNode.text();

			if(innerNode.tag() == "i")
				result += "</i>";
		}
	}

	return result;
}

string load_mana_cost(CDocument& doc, string const& selector)
{
	string result;
	CSelection c = doc.find(selector);

	if(c.nodeNum() > 0)
	{
		CNode node = c.nodeAt(0);
		string mana = node.attribute("alt");
		if(mana != "")
		{
			result = string("{") + mana + "}";
		}
	}

	return result;
}

}

namespace gatherer
{

Card load_single_card(CDocument& doc)
{
	using std::stoi;

	Card result;

	result.name = load_text(doc, "#ctl00_ctl00_ctl00_MainContent_SubContent_SubContent_nameRow .value");
	result.manaCost = load_mana_cost(doc, "#ctl00_ctl00_ctl00_MainContent_SubContent_SubContent_manaRow .value img");

	int i = stoi(load_text(doc, "#ctl00_ctl00_ctl00_MainContent_SubContent_SubContent_cmcRow .value"));
	clamp(result.convertedManaCost, i);

	result.types = load_text(doc, "#ctl00_ctl00_ctl00_MainContent_SubContent_SubContent_typeRow .value");
	result.text = load_rules_text(doc, "#ctl00_ctl00_ctl00_MainContent_SubContent_SubContent_textRow .value");

	result.flavour = load_text(doc, "#ctl00_ctl00_ctl00_MainContent_SubContent_SubContent_FlavorText .flavortextbox");

	result.powerThoughness = load_text(doc, "#ctl00_ctl00_ctl00_MainContent_SubContent_SubContent_ptRow .value");
	//result.expansion = load_text(doc, "#ctl00_ctl00_ctl00_MainContent_SubContent_SubContent_setRow .value");
	result.rarity = load_text(doc, "#ctl00_ctl00_ctl00_MainContent_SubContent_SubContent_rarityRow .value");

	i = stoi(load_text(doc, "#ctl00_ctl00_ctl00_MainContent_SubContent_SubContent_numberRow .value"));
	clamp(result.cardNumber, i);

	result.artist = load_text(doc, "#ctl00_ctl00_ctl00_MainContent_SubContent_SubContent_artistRow .value");

	return result;
}


}