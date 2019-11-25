/*
	@author Marcello Sgarbi
	@date 14-Feb-2019
*/

#include "readingXML.h"

int rxml::returnInt(char * value)
{
	return std::atoi(value);
}

double rxml::returnDouble(char * value)
{
	return std::atof(value);
}


std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>> rxml::readfileXMLSignals(const char* filepath)
{
	rapidxml::file<> xmlFile(filepath);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	rapidxml::xml_node<> *pRoot = doc.first_node();

	std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>> container;
	std::array<double, 4> keycont;
	keycont.at(0) = rxml::returnDouble(pRoot->first_node("key1")->value());
	keycont.at(1) = rxml::returnDouble(pRoot->first_node("key2")->value());
	keycont.at(2) = rxml::returnDouble(pRoot->first_node("key3")->value());
	keycont.at(3) = rxml::returnDouble(pRoot->first_node("key4")->value());

	for (rapidxml::xml_node<> *pNode = pRoot->first_node("element"); pNode; pNode = pNode->next_sibling())
	{
		rapidxml::xml_node<> *h1 = pNode->first_node("h1");
		rapidxml::xml_node<> *h2 = pNode->first_node("h2");
		rapidxml::xml_node<> *h3 = pNode->first_node("h3");
		rapidxml::xml_node<> *h4 = pNode->first_node("h4");
		rapidxml::xml_node<> *s1 = pNode->first_node("s1");
		rapidxml::xml_node<> *s2 = pNode->first_node("s2");
		rapidxml::xml_node<> *s3 = pNode->first_node("s3");
		rapidxml::xml_node<> *s4 = pNode->first_node("s4");

		std::array<std::pair<int, int>, 4 > aux;
		aux.at(0) = std::make_pair(rxml::returnInt(h1->value()), rxml::returnInt(s1->value()));
		aux.at(1) = std::make_pair(rxml::returnInt(h2->value()), rxml::returnInt(s2->value()));
		aux.at(2) = std::make_pair(rxml::returnInt(h3->value()), rxml::returnInt(s3->value()));
		aux.at(3) = std::make_pair(rxml::returnInt(h4->value()), rxml::returnInt(s4->value()));
		
		mapFun::setMapElement(container, keycont, aux);
		
		
	}
	return container;

}


std::map<int, int> rxml::vehicleSignals(const char* path)
{
	rapidxml::file<> xmlFile(path);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	std::map<std::string, int> routeMap;

	rapidxml::xml_node<> *pRoot = doc.first_node("routes");

	rapidxml::xml_node<> *route = pRoot->first_node("route");

	//Read route definition, values can NOT be repeted
	int sem = 0;
	while (route <= pRoot->last_node("route"))
	{
		std::string attribute = route->first_attribute()->value();

		//straight
		if (attribute == "route1" || attribute == "route2" || attribute == "route3" || attribute == "route4") {
			routeMap[attribute] = 0;
		}
		//left
		if (attribute == "route5" || attribute == "route7" || attribute == "route9" || attribute == "route12") {
			routeMap[attribute] = 1;
		}
		//Right
		if (attribute == "route6" || attribute == "route8" || attribute == "route10" || attribute == "route11") {
			routeMap[attribute] = 2;
		}
		if (sem == 1) break;
		if (route->first_attribute()->value() <= pRoot->last_node("route")->first_attribute()->value()) {
			route = route->next_sibling();
			if (route->first_attribute()->value() == pRoot->last_node("route")->first_attribute()->value()) sem = 1;
		}
	}

	//Read vehicle value
	rapidxml::xml_node<> *vehicle = pRoot->first_node("vehicle");
	std::map<int, int> outMap;

	int semaphore2 = 0;

	while (std::stoi(vehicle->first_attribute("id")->value()) <= std::stoi(pRoot->last_node("vehicle")->first_attribute("id")->value()))
	{
		rapidxml::xml_attribute<> *vid = vehicle->first_attribute("id");
		rapidxml::xml_attribute<> *vroute = vehicle->first_attribute("route");
		std::map<std::string, int>::iterator findit = routeMap.find(vroute->value());

		outMap[std::stoi(vid->value())] = findit->second;

		if (semaphore2 == 1) break;
		if (vehicle->first_attribute("id")->value() <= pRoot->last_node("vehicle")->first_attribute("id")->value()) {
			vehicle = vehicle->next_sibling();
			if (vehicle->first_attribute("id")->value() == pRoot->last_node("vehicle")->first_attribute("id")->value()) semaphore2 = 1;
		}
	}
	return outMap;
}
