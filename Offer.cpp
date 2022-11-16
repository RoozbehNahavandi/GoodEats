#include "Offer.hpp"
#include <string>

using namespace std;

Offer::Offer(string _name, string ing, double _price, double _packing, int cnt)
 : supplier_name(_name), ingredient(ing), price(_price), packaging(_packing), count(cnt) {};

 void Offer::decrease_count_by_one() { count -= 1; };

 void Offer::edit_offer(string ing, double _price, int _count) {
 	ingredient = ing;
 	price = _price;
 	count = _count;
 }