#ifndef _ORDERS_HPP_
#define _ORDERS_HPP_

#include <vector>
#include <string>
#include "Defines.hpp"
#include <iostream>
#include <algorithm>

struct  OrderLine
{
	std::string supplier_name;
	std::vector<std::string> ingredients;

	void print_orderlines() {
		sort(ingredients.begin(), ingredients.end());
		std::cout << supplier_name;
		for (auto x : ingredients)
			std::cout << " " << x;
		std::cout << std::endl;
	}
};

class Orders {
public:
	Orders(int);
	void add_ingredient(std::string, std::string);
	void set_total_price(double price) { total_price = price; };
	void print_orders();
	void print_all_info();
private:
	int recipe_id;
	std::vector<OrderLine> orderlines;
	double total_price;
};

#endif