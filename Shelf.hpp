#ifndef _SHELF_HPP_
#define _SHELF_HPP_

#include "Recipe.hpp"
#include <vector>
#include <iostream>

class Shelf {
public:
	Shelf(int, std::string);
	int get_id() { return id; };
	void show();
	bool same_id(int _id) { return _id == id; };
	bool is_deleted() { return deleted; };
	void add_recipe(Recipe*);
	void show_recipes();
	Recipe* find_recipe_by_title(std::string);
	int find_recipe_idx(Recipe*);
	void remove_recipe(int);
private:
	Deleted deleted = No;
	int id;
	std::string name;
	Recipes recipes;
};

#endif