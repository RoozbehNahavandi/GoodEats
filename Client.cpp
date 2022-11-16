#include "Client.hpp"
#include <iostream>
#include <algorithm>
#include "Shelf.hpp"
#include <cmath>
#include <sstream>
using namespace std;

Client::Client(string _username, string _password) : username(_username), password(_password) {}

bool Client::same_username(string _username) {
	return username == _username;
}

bool Client::correct_password(string _password) { return _password == password; };

void Client::add_offer(string ing, double price, int count, double pack) { throw PermissionDenied(); };

void Client::edit_offer(string ing, double price, int count) { throw PermissionDenied(); };














bool User::same_username_as_chef(string username) { return false; };


User::User(string _username, string _password) : Client(_username, _password) {}

void User::add_recipe(Recipe*) { throw PermissionDenied(); };
void User::show_your_recipes() { throw PermissionDenied(); };
Recipe* User::find_recipe_by_id(int id) { throw PermissionDenied(); };
void User::rate_recipe(Recipe* recipe, double score) {
	rated_recipes.push_back(recipe);
	recipe->add_rating(this, score);
}
bool User::has_already_rated_this_recipe(Recipe* recipe) {
	int recipe_id = recipe->get_id();
	for (auto x : rated_recipes) {
		if (x->same_id(recipe_id))
			return true;
	}
	return false;
}

void User::update_rating(Recipe* recipe, double score) {
	recipe->update_rating(this, score);
}

void User::add_shelf(Shelf* shelf) { shelves.push_back(shelf); };

void User::print_shelves(int limit) {
	if (shelves.size() == 0)
		cout << "Empty" << endl;
	else {
		int l = 0;
		for (auto x : shelves) {
			if (l == limit)
				break;
			l++;
			x->show();
		}
	}
}

Shelf* User::find_shelf_by_id(int id) {
	for (auto x : shelves)
		if (x->same_id(id))
			if (!x->is_deleted())
				return x;
	return NULL;
}

bool User::has_this_shelf(Shelf* shelf) {
	for (auto x : shelves)
		if (x == shelf)
			return true;
	return false;
}


string User::get_chef_username() { return ""; };

void User::print_chef() {};

string User::get_user_username() { return username; };

void User::print_user() {
	cout << username << endl;
}

void User::get_chef_info() {}

void User::add_offer(string ing, double price, int count, double pack) { throw PermissionDenied(); };

void User::edit_offer(string ing, double price, int count) { throw PermissionDenied(); };


void User::show_credits() {
	cout << credits << endl;
}

void User::add_credits(int money) { credits += money; };

double User::ingredient_price(string ing) { return 0; };

string User::get_name() { throw PermissionDenied(); };

void User::pay(double money) {
	if (money > credits)
		throw BadRequest();
	credits -= money;
}

void User::show_orders() {
	for (int i = 0; i < orders.size(); i++) {
		ostringstream os;
		os << "====" << "order_" << i+1 << "====" << endl;
		cout << os.str();
		orders[i]->print_all_info();
	}
}










Chef::Chef(string _username, string _password) : Client(_username, _password) {}

void Chef::add_recipe(Recipe* recipe) {
	recipes.push_back(recipe);
}

void Chef::show_your_recipes() {
	vector<string> titles;
	for (auto x : recipes)
		if (x->is_not_deleted())
			titles.push_back(x->get_title());
	sort(titles.begin(), titles.end());
	for (auto x : titles) {
		find_recipe_by_title(x)->print_recipe();
		cout << endl;
	}
		
}

Recipe* Chef::find_recipe_by_id(int id) {
	for (auto x : recipes)
		if (x->same_id(id))
			if (x->is_not_deleted())
				return x;
	return NULL;
}

Recipe* Chef::find_recipe_by_title(string title) {
	for (auto x : recipes)
		if (x->same_title(title))
			return x;
	return NULL;
}

void Chef::rate_recipe(Recipe* recipe, double score) { throw PermissionDenied(); };

bool Chef::has_already_rated_this_recipe(Recipe* recipe) { throw PermissionDenied(); };

void Chef::update_rating(Recipe* recipe, double score) { throw PermissionDenied(); };

void Chef::add_shelf(Shelf* shelf) { throw PermissionDenied(); };

void Chef::print_shelves(int limit) { throw PermissionDenied(); };

Shelf* Chef::find_shelf_by_id(int id) { throw PermissionDenied(); };

bool Chef::has_this_shelf(Shelf* shelf) { throw PermissionDenied(); };

string Chef::get_chef_username() { return username; };

void Chef::print_chef() {
	double score = chef_score();
	cout << username << " " << score << endl;
}

double Chef::chef_score() {
	double nums = 0;
	double sum = 0;
	for (auto x : recipes) {
		if (x->is_not_deleted()) {
			sum += x->sum_of_scores();
			nums += x->num_of_rates();
		}
	}
	if (nums == 0)
		return 0;
	double avg = sum / nums;
	avg = ceil(avg*10)/10;
	return avg;
}

string Chef::get_user_username() { return ""; };

void Chef::print_user() {};

bool Chef::same_username_as_chef(string _username) { return username == _username; };

void Chef::get_chef_info() {
	cout << username << endl;
	double score = chef_score();
	cout << score << endl;
	vector<string> names;
	cout << "recipes:\n";
	for (auto x : recipes)
		if (x->is_not_deleted())
			names.push_back(x->get_title());
	sort(names.begin(), names.end());
	for (auto x : names)
			find_recipe_by_title(x)->print_recipe_with_rating();
}

void Chef::add_offer(string ing, double price, int count, double pack) { throw PermissionDenied(); };

void Chef::edit_offer(string ing, double price, int count) { throw PermissionDenied(); };

void Chef::show_credits() { throw PermissionDenied(); };

void Chef::add_credits(int money) { throw PermissionDenied(); };


double Chef::ingredient_price(string ing) { return 0; };

string Chef::get_name() { throw PermissionDenied(); };









Supplier::Supplier(string name, string email, string password)
: Client(email, password) {
	this->name = name;
}


void Supplier::add_recipe(Recipe* recipe) { throw PermissionDenied(); }
void Supplier::show_your_recipes() { throw PermissionDenied(); }
Recipe* Supplier::find_recipe_by_id(int id) { throw PermissionDenied(); }
void Supplier::rate_recipe(Recipe* recipe, double score) { throw PermissionDenied(); }
bool Supplier::has_already_rated_this_recipe(Recipe* recipe) { throw PermissionDenied(); }
void Supplier::update_rating(Recipe* recipe, double d) { throw PermissionDenied(); };
void Supplier::add_shelf(Shelf* shelf) { throw PermissionDenied(); }
void Supplier::print_shelves(int limit) { throw PermissionDenied(); }
Shelf* Supplier::find_shelf_by_id(int id) { throw PermissionDenied(); }; 
bool Supplier::has_this_shelf(Shelf* shelf) { throw PermissionDenied(); }
std::string Supplier::get_chef_username() { return ""; }
void Supplier::print_chef() {}
std::string Supplier::get_user_username() { return ""; }
void Supplier::print_user() {}
bool Supplier::same_username_as_chef(std::string) { return false; }
void Supplier::get_chef_info() { throw PermissionDenied(); };

void Supplier::add_offer(string ing, double price, int count, double pack) {
	if (ingredient_is_unique(ing)) {
		Offer* new_offer = new Offer(name, ing, price, pack, count);
		offers.push_back(new_offer);
	}
	else throw BadRequest();
}

bool Supplier::ingredient_is_unique(string ing) {
	for (auto x : offers)
		if (x->same_ingredient(ing))
			if (!x->is_deleted())
				return false;
	return true;
}

void Supplier::edit_offer(string ing, double price, int count) {
	if (ingredient_is_unique(ing))
		throw BadRequest();
	for (auto x : offers)
		if (x->same_ingredient(ing))
			x->edit_offer(ing, price, count);
}

void Supplier::show_credits() { throw PermissionDenied(); };

void Supplier::add_credits(int money) { throw PermissionDenied(); };

Offer* Supplier::find_offer_by_ingredient(string ing) {
	for (auto offer : offers)
		if (offer->same_ingredient(ing))
			if (offer->still_available())
				if (!offer->is_deleted())
					return offer;
	return NULL;
}

double Supplier::ingredient_price(string ing) {
	double total_price = 0;
	for (auto offer : offers) {
		Offer* of = find_offer_by_ingredient(ing);
		of->calculate_price();
	}
	return total_price;
}

string Supplier::get_name() { return name; };

void Supplier::delete_offer(string ing) {
	find_offer_by_ingredient(ing)->delete_offer();		
}

int Supplier::count_of_ingredient(string ing) {
	Offer* offer = find_offer_by_ingredient(ing);
	if (offer == NULL)
		return 0;
	return offer->count_of_ingredient();
}