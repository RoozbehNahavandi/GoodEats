
#include "Orders.hpp"
#include <vector>
#include <string>
using namespace std;

Orders::Orders(int id) 
: total_price(0), recipe_id(id) {}

void Orders::add_ingredient(string _supplier_name, string ingredient) {
	for (auto &x : orderlines) {
		if (x.supplier_name ==  _supplier_name) {
			x.ingredients.push_back(ingredient);
			return;
		}
	}
	OrderLine new_orderline;
	new_orderline.supplier_name = _supplier_name;
	new_orderline.ingredients.push_back(ingredient);
	orderlines.push_back(new_orderline);
}

bool sort_orderlines(OrderLine& ol1, OrderLine& ol2) {
	return ol1.supplier_name < ol2.supplier_name;
}

void Orders::print_orders() {
	sort(orderlines.begin(), orderlines.end(), sort_orderlines);
	for (auto x : orderlines)
		x.print_orderlines();
	cout << total_price << endl;
}

void Orders::print_all_info() {
	cout << recipe_id << endl;
	for (auto x : orderlines)
		x.print_orderlines();
	cout << total_price << endl;
}