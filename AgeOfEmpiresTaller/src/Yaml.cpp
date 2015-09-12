/*
 * Yaml.cpp
 *
 *  Created on: 12 de set. de 2015
 *      Author: andres
 */

#include "Yaml.h"

Yaml::Yaml() {
	// TODO Auto-generated constructor stub

}
// our data types
struct Vec3 {
   float x, y, z;
};

struct Power {
   std::string name;
   int damage;
};

struct Monster {
   std::string name;
   Vec3 position;
   std::vector <Power> powers;
};

// now the extraction operators for these types
void operator >> (const YAML::Node& node, Vec3& v) {
   node[0] >> v.x;
   node[1] >> v.y;
   node[2] >> v.z;
}

void operator >> (const YAML::Node& node, Power& power) {
   node["name"] >> power.name;
   node["damage"] >> power.damage;
}

void operator >> (const YAML::Node& node, Monster& monster) {
   node["name"] >> monster.name;
   node["position"] >> monster.position;
   const YAML::Node& powers = node["powers"];
   for(unsigned i=0;i<powers.size();i++) {
      Power power;
      powers[i] >> power;
      monster.powers.push_back(power);
   }
}

int Yaml::read()
{
   std::ifstream fin("YAML/monsters.yaml");
   YAML::Parser parser(fin);
   YAML::Node doc;
   parser.GetNextDocument(doc);

   for(unsigned i=0;i<doc.size();i++) {
        Monster monster;
        doc[i] >> monster;
        std::cout << monster.name << "\n";
     }
   std::cout << "end\n";
   return 0;
}

Yaml::~Yaml() {
	// TODO Auto-generated destructor stub
}

