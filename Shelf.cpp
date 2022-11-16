#include "Shelf.hpp"
#include <algorithm>
using namespace std;

Shelf::Shelf(int _id, string _name) : id(_id), name(_name) {}

void Shelf::show() {
	cout << id << " " << name << endl;
}

void Shelf::add_recipe(Recipe* recipe) {
	recipes.push_back(recipe);
}

void Shelf::show_recipes() {
	vector<string> names;
	for (auto x : recipes)
		names.push_back(x->get_title());
	if (names.size() == 0)
		cout << "Empty" << endl;
	else {
		sort(names.begin(), names.end());
		for (string x : names)
			find_recipe_by_title(x)->print_recipe_for_user();
	}

}

Recipe* Shelf::find_recipe_by_title(string title) {
	for (auto x : recipes)
		if (x->same_title(title))
			return x;
	return NULL;
}

int Shelf::find_recipe_idx(Recipe* recipe) {
	for (int i = 0; i < recipes.size(); i++)
		if (recipes[i] == recipe)
			return i;
	return NOT_FOUND;
}

void Shelf::remove_recipe(int idx) {
	recipes.erase(recipes.begin() + idx);

}