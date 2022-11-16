#include "Manager.hpp"
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

void print_empty() { cout << "Empty" << endl; };


Manager::Manager() {
	filters.push_back(new TagFilter());
	filters.push_back(new VeganFilter());
	filters.push_back(new MinutesFilter());
	filters.push_back(new RatingFilter());
}


void Manager::add_member(string username, string password, string type) {
	if (current_member != NULL) 
		throw PermissionDenied();
	if (username_is_unique(username)) {
		if (type == CHEF) {
			Chef* new_chef = new Chef(username, password);
			members.push_back(new_chef);
		}
		else if (type == USER) {
			User* new_user = new User(username, password);
			members.push_back(new_user);
		}
		current_member = members[members.size()-1];
	}
	else 
		throw BadRequest();
}

bool Manager::username_is_unique(string username) {
	for (auto x : members)
		if (x->same_username(username))
			return false;
		return true;
}

void Manager::logout_member() {
	if (!current_member)
		throw PermissionDenied();

	current_member = NULL;
for (auto filter : filters) 
	filter->set_default();	
}

void Manager::login_member(string _username, string _password) {
	if (current_member)
		throw BadRequest();
	Client* _curr = find_member_by_username(_username);
	if (!_curr)
		throw BadRequest();
	if (_curr->correct_password(_password)) {
		current_member = _curr;

	}
	else throw BadRequest();
}

void Manager::login_supplier(string _email, string _password) {
	if (current_member)
		throw BadRequest();
	Client* curr = find_supplier_by_email(_email);
	if (!curr)
		throw BadRequest();
	if (curr->correct_password(_password)) {
		current_member = curr;
	}
}

Client* Manager::find_supplier_by_email(string email) {
	for (auto x : members)
		if (x->same_email(email))
			return x;
	return NULL;
}

Client* Manager::find_member_by_username(string username) {
	for (auto x : members)
		if (x->same_username(username))
			return x;
	return NULL;
}

void Manager::add_recipe(Title title, Ingredients ingredients, Vegetarian vegetarian, 
	int minutes_to_ready, Tags tags, Image_address image_address) {
	if (!current_member) 
		throw PermissionDenied();
	int next_id;
	if (recipes.size() == 0) 
		next_id = 1;
	else 
		next_id =  find_next_id();
	Recipe* new_recipe = new Recipe(next_id, title, ingredients, vegetarian, minutes_to_ready, tags, image_address);
	current_member->add_recipe(new_recipe);
	recipes.push_back(new_recipe);
	cout << next_id << endl;


}

int Manager::find_next_id() {
	vector<int> ids;
	for (auto x : recipes) 
		ids.push_back(x->get_id());
	sort(ids.begin(), ids.end());
	return ids[ids.size() - 1] + 1;
}

void Manager::show_chef_recipes() {
	if (!current_member)
		throw PermissionDenied();
	current_member->show_your_recipes();

}

void Manager::delete_recipe(int id) {
	if (!current_member) 
		throw PermissionDenied();
	Recipe* target_recipe = current_member->find_recipe_by_id(id);
	if (target_recipe == NULL)
		throw PermissionDenied();
	target_recipe->delete_recipe();
}

void Manager::show_recipes() {
	if (!current_member)
		throw PermissionDenied();
	if (current_member->is_allowed_to_enter_user_commands()) {
		vector<string> titles;
		Recipes filtered_recipes = apply_filters(recipes);
		for (auto x : filtered_recipes)
			if (x->is_not_deleted())
				titles.push_back(x->get_title());
			if (titles.size() == 0)
				print_empty();
		sort(titles.begin(), titles.end());
		for (auto x : titles)
			find_recipe_by_title(x)->print_recipe_for_user();
	}
	else throw PermissionDenied();
	
}

Recipe* Manager::find_recipe_by_title(string title) {
	for (auto x : recipes)
		if (x->same_title(title))
			return x;
	return NULL;
}

void Manager::show_recipe(int id) {
	if (!current_member)
		throw PermissionDenied();
	if (current_member->is_allowed_to_enter_user_commands()) {
		Recipe* to_show_recipe = find_recipe_by_id(id);
		if (to_show_recipe == NULL) 
			throw NotFound();
		to_show_recipe->print_recipe();
	}
	else throw PermissionDenied();
}

Recipe* Manager::find_recipe_by_id(int id) {
	for (auto x : recipes)
		if (x->same_id(id))
			if (x->is_not_deleted())
				return x;
	return NULL;
}

void Manager::rate_recipe(int id, double score) {
	if (!current_member)
		throw PermissionDenied();
	check_score_boundary(score);
	Recipe* to_rate_recipe = find_recipe_by_id(id);
	if (to_rate_recipe == NULL) 
		throw NotFound();
	if (current_member->has_already_rated_this_recipe(to_rate_recipe)) 
		throw BadRequest();
	current_member->rate_recipe(to_rate_recipe, score);
}

void Manager::check_score_boundary(double score) {
	if (score < 1 || score > 5)
		throw BadRequest();
}

void Manager::edit_rating(int id, double score) {

	if (!current_member) 
		throw PermissionDenied();
	check_score_boundary(score);
	Recipe* to_rate_recipe = find_recipe_by_id(id);
	if (to_rate_recipe == NULL) 
		throw BadRequest();
	if (!current_member->has_already_rated_this_recipe(to_rate_recipe))
		throw BadRequest();
	current_member->update_rating(to_rate_recipe, score);
}

void Manager::add_shelf(string shelf_name) {
	if (!current_member)
		throw PermissionDenied();
	int next_id;
	if (shelves.size() == 0) 
		next_id = 1;
	else next_id = find_next_shelf_id();
	Shelf* new_shelf = new Shelf(next_id, shelf_name);
	current_member->add_shelf(new_shelf);
	shelves.push_back(new_shelf);
	cout << next_id << endl;
}

int Manager::find_next_shelf_id() {
	vector<int> ids;
	for (auto x : shelves) 
		ids.push_back(x->get_id());
	sort(ids.begin(), ids.end());
	return ids[ids.size() - 1] + 1;
}

void Manager::get_shelves(string username, int limit) {
	if (!current_member)
		throw PermissionDenied();
	if (current_member->is_allowed_to_enter_user_commands()) {
		Client* user = find_user_by_username(username);
		if (user == NULL) 
			throw BadRequest();
		if (user->has_shelves()) 
			user->print_shelves(limit);
		else 
			throw BadRequest();
	}
	else 
		throw PermissionDenied();
}

Client* Manager::find_user_by_username(string username) {
	for (auto x : members)
		if (x->same_username(username))
			return x;
		return NULL;
}

void Manager::add_recipe_to_shelf(int shelf_id, int recipe_id) {
	if (!current_member)
		throw PermissionDenied();
	Shelf* shelf = find_shelf_by_id(shelf_id);
	Recipe* recipe = find_recipe_by_id(recipe_id);
	if (shelf == NULL)
		throw BadRequest();
	if (recipe == NULL) 
		throw BadRequest();
	if (!current_member->has_this_shelf(shelf))
		throw PermissionDenied();
	shelf->add_recipe(recipe);

}
void Manager::show_shelf_recipes(int shelf_id) {
	if (!current_member)
		throw PermissionDenied();
	if (!current_member->is_allowed_to_enter_user_commands())
		throw PermissionDenied();
	Shelf* shelf = find_shelf_by_id(shelf_id);
	if (shelf == NULL)
		throw BadRequest();
	shelf->show_recipes();
}

Shelf* Manager::find_shelf_by_id(int id) {
	for (auto x : shelves)
		if (x->same_id(id))
			return x;
	return NULL;
}

void Manager::remove_recipe_from_shelf(int shelf_id, int recipe_id) {
	if (!current_member)
		throw PermissionDenied();
	if (current_member->is_allowed_to_enter_user_commands()) {
		Shelf* shelf = find_shelf_by_id(shelf_id);
		Recipe* recipe = find_recipe_by_id(recipe_id);
		if (current_member->has_this_shelf(shelf)) {
			int idx = shelf->find_recipe_idx(recipe);
			if (idx != NOT_FOUND)
				shelf->remove_recipe(idx);
			else throw BadRequest();

		}
		else throw PermissionDenied();
	}
	else throw PermissionDenied();
}

void Manager::get_chefs() {
	if (!current_member)
		throw PermissionDenied();
	if (current_member->is_allowed_to_enter_user_commands()) {
		vector<string> usernames;
		for (auto member : members)  {
			string username = member->get_chef_username();
			if (username != "")
			usernames.push_back(username);
		}
		sort(usernames.begin(), usernames.end());
		if (usernames.size() == 0)
			print_empty();
		else {
			for (auto x : usernames) 
				find_member_by_username(x)->print_chef();
		}
	}
	else throw PermissionDenied();
}

void Manager::get_users() {
	if (!current_member)
		throw PermissionDenied();
	if (!current_member->is_allowed_to_enter_user_commands())
		throw PermissionDenied();
	vector<string> usernames;
	for (auto member : members) {
		string username = member->get_user_username();
		if (username != "")
			usernames.push_back(username);
	}
	sort(usernames.begin(), usernames.end());
	if (usernames.size() == 0)
		print_empty();
	else {
		for (auto x : usernames) {
			Client* member = find_member_by_username(x);
			if (member != current_member)
				member->print_user();
		}
	}
}

void Manager::show_chef_info(string username) {
	if (!current_member)
		throw PermissionDenied();
	if (!current_member->is_allowed_to_enter_user_commands())
		throw PermissionDenied();
	Client* chef = find_chef_by_username(username);
	if (chef == NULL) 
		throw NotFound();
	chef->get_chef_info();

}

Client* Manager::find_chef_by_username(string username) {
	for (auto x : members) 
		if (x->same_username_as_chef(username))
			return x;
	return NULL;
}


void Manager::add_tag_filter(string tag) {
	if (!current_member)
		throw PermissionDenied();
	if (!current_member->is_allowed_to_enter_user_commands())
		throw PermissionDenied();
	for (auto filter : filters) 
		filter->update_tag_filter(tag);
}

void Manager::add_veg_filter() {
	if (!current_member)
		throw PermissionDenied();
	if (!current_member->is_allowed_to_enter_user_commands())
		throw PermissionDenied();
	for (auto filter : filters)
		filter->update_veg_filter();
}

void Manager::add_minutes_filter(int min, int max) {
	if (!current_member)
		throw PermissionDenied();
	if (!current_member->is_allowed_to_enter_user_commands())
		throw PermissionDenied();
	for (auto filter : filters)
		filter->update_minutes_filter(min, max);
}

void Manager::add_rating_filter(double min, double max) {
	if (!current_member)
		throw PermissionDenied();
	if (!current_member->is_allowed_to_enter_user_commands())
		throw PermissionDenied();
	for (auto filter : filters)
		filter->update_rating_filter(min, max);
}

void Manager::delete_filters() {
	if (!current_member)
		throw PermissionDenied();
	if (!current_member->is_allowed_to_enter_user_commands())
		throw PermissionDenied();
	for (auto filter : filters) 
		filter->set_default();
}

Recipes Manager::apply_filters(Recipes recipes) {
	Recipes filtered_recipes = recipes;
	for (auto filter : filters)
		filtered_recipes = filter->apply(filtered_recipes);
	return filtered_recipes;
}

void Manager::add_supplier(string name, string email, string password) {
	if (current_member) {
		throw PermissionDenied();
	}
	if (!email_is_unique(email)) 
		throw BadRequest();
	if (!name_is_unique(name))
		throw BadRequest();

	Supplier* new_supplier = new Supplier(name, email, password);
	members.push_back(new_supplier);
	current_member = members[members.size() - 1];
}

bool Manager::email_is_unique(string email) {
	for (auto member : members)
		if (member->same_email(email))
			return false;
	return true;
}

bool Manager::name_is_unique(string name) {
	for (auto member : members) 
		if (member->same_name_as_supplier(name))
			return false;
	return true;
}

void Manager::add_offer(string ingredient, double price, int count, double packaging) {
	if (!current_member)
		throw PermissionDenied();
	current_member->add_offer(ingredient, price, count, packaging);
}

void Manager::edit_offer(string ingredient, double price, int count) {
	if (!current_member)
		throw PermissionDenied();
	current_member->edit_offer(ingredient, price, count);
}

bool Manager::is_off(string ingredient) {
	int count = 0;
	for (auto x : members)
		count += x->count_of_ingredient(ingredient);

	return count >= OFF_COUNT;
}


void Manager::get_orders(int recipe_id) {
	double coeff = 1;
	if (!current_member)
		throw PermissionDenied();
	if (!current_member->is_allowed_to_enter_user_commands())
		throw PermissionDenied();
	vector<Offer*> _offers;
	Recipe* recipe = find_recipe_by_id(recipe_id);
	if (recipe == NULL)
		throw NotFound();
	Orders* new_orders = new Orders(recipe_id);
	double total_price =0;
	int ing_price;
	Ingredients ingredients = recipe->get_ingredients();
	for (string x : ingredients) {
		coeff = 1;
		if (is_off(x))
			coeff = OFF;
		Offer* offer = find_best_offer(x);
		if (offer == NULL) {
			delete new_orders;
			throw NotFound();
		}
		ing_price = offer->calculate_price() * coeff;
		total_price += ing_price;
		new_orders->add_ingredient(offer->get_supplier(), x);
		_offers.push_back(offer);
	}
	new_orders->set_total_price(total_price);
	current_member->pay(total_price);
	new_orders->print_orders();
	for (auto x : _offers) {
		double money = x->get_price();
		find_supplier_by_name(x->get_supplier())->increase_credits(money);
		x->decrease_count_by_one();
	}
	current_member->add_orders(new_orders);
}

Client* Manager::find_supplier_by_name(string name) {
	for (auto x : members)
		if (x->same_name(name))
			return x;
	return NULL;
}

void Manager::get_credits() {
	if (!current_member)
		throw PermissionDenied();
	current_member->show_credits();
}

void Manager::edit_credits(int money) {
	if (!current_member)
		throw PermissionDenied();
	current_member->add_credits(money);
}

bool sort_by_price(Offer* no1, Offer* no2) {
	double no1_price, no2_price;
	no1_price = no1->calculate_price();
	no2_price = no2->calculate_price();
	if (no1_price == no2_price) {
		string no1_supplier = no1->get_supplier();
		string no2_supplier = no2->get_supplier();
		return no1_supplier > no2_supplier;
	}
	return no1_price > no2_price;
}

Offer* Manager::find_best_offer(string ingredient) {
	vector<Offer*> offers;
	for (auto x : members) {
		Offer* offer = x->find_offer_by_ingredient(ingredient);
		if (offer)
			offers.push_back(offer);
	}
	if (offers.size() == 0)
		return NULL;
	sort(offers.begin(), offers.end(), sort_by_price);
	return offers [offers.size() - 1];
}

void Manager::delete_ingredient_offer(string ing) {
	if (!current_member)
		throw PermissionDenied();
	current_member->delete_offer(ing);
}

void Manager::show_orders() {
	if (!current_member)
		throw PermissionDenied();
	current_member->show_orders();

}