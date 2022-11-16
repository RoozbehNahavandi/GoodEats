#include "Interface.hpp"
#include <iostream>

using namespace std;

void print_ok() { 
	cout << COMMAND_RECIEVED << endl;
}


vector<string> split(string str) {
	stringstream s(str);
	string word;
	vector<string> result;
	while (getline(s, word, ',')) {
		result.push_back(word);
	}
	return result;
}

void Interface::run() {

	Command_Type cmd_type;
	while (cin >> cmd_type) {
		try {
			if (cmd_type == POST_COMMAND_TYPE)
				post_type();
			else if (cmd_type == GET_COMMAND_TYPE)
				get_type();
			else if (cmd_type == PUT_COMMAND_TYPE)
				put_type();
			else if (cmd_type == DELETE_COMMAND_TYPE)
				delete_type();
			else {
				string dummy_line;
				getline(cin, dummy_line);
			 throw NotFound();
			}
		} catch (Exception& ex) {
			cout << ex.Description() << endl;
		}
	}
}

void Interface::post_type() {
	Command cmd;
	cin >> cmd;
	if (cmd == SIGNUP_COMMAND)
		signup_Client();
	else if (cmd == SIGNUP_SUPPLIER_COMMAND)
		signup_supplier();
	else if (cmd == LOGOUT_COMMAND)
		logout();
	else if (cmd == LOGIN_COMMAND)
		login();
	else if (cmd == RECIPES_COMMAND)
		get_recipe();
	else if (cmd == RATE_COMMAND)
		get_rating();
	else if (cmd == ADD_SHELF_COMMAND)
		add_shelf();
	else if (cmd == FILTER_COMMAND)
		get_filter();
	else if (cmd == OFFERS_COMMAND)
		get_offer();
	else if (cmd == ORDERS)
		get_orders();
	else  throw NotFound();
}

void Interface::get_type() {
	Command cmd;
	cin >> cmd;
	if (cmd == MY_RECIPES_COMMAND)
		goodeats_manager.show_chef_recipes();
	else if (cmd == GET_RECIPES)
		show_recipe();
	else if (cmd == GET_SHELVES_COMMAND)
		get_shelves();
	else if (cmd == GET_SHELVES_RECIPES)
		show_shelves_recipes();
	else if (cmd == GET_CHEFS) 
		get_chefs();
	else if (cmd == GET_USERS)
		get_users();
	else if (cmd == GET_CREDITS_COMMAND)
		goodeats_manager.get_credits();
	else if (cmd == GET_ORDERS_COMMAND)
		goodeats_manager.show_orders();

}

void Interface::delete_type() {
	Command cmd;
	cin >> cmd;
	if (cmd == DELETE_RECIPE_COMMAND) 
		delete_recipe();
	if (cmd == DELETE_SHELF_RECIPE)
		delete_shelf_recipe();
	if (cmd == DELETE_FILTERS) {
		goodeats_manager.delete_filters();
		print_ok();
	}
	if (cmd == DELETE_OFFER)
		delete_offer();
}

void Interface::put_type() {
	Command cmd;
	cin >> cmd;
	if (cmd == EDIT_RATING)
		edit_rating();
	if (cmd == ADD_RECIPE_TO_SHELF)
		add_recipe_to_shelf();
	if (cmd == EDIT_OFFER)
		edit_offer();
	if (cmd == EDIT_CREDITS)
		edit_credits();
}

void Interface::delete_offer() {
	char q;
	string ingredient, dummy_ingredient;
	cin >> q >> dummy_ingredient >> ingredient;
	if (q != '?')
		throw BadRequest();
	if (dummy_ingredient != "ingredient")
		throw BadRequest();
	goodeats_manager.delete_ingredient_offer(ingredient);
	print_ok();
}

void Interface::edit_credits() {
	char q;
	string dummy_money;
	double money;
	cin >> q >> dummy_money >> money;
	if (q != '?')
		throw BadRequest();
	if (dummy_money != "money")
		throw BadRequest();
	goodeats_manager.edit_credits(money);
	print_ok();
}

void Interface::get_orders() {
	char q;
	string dummy_recipe_id;
	int id;
	cin >> q >> dummy_recipe_id >> id;
	if (q != '?')
		throw BadRequest();
	if (dummy_recipe_id != "recipe_id")
		throw BadRequest();
	goodeats_manager.get_orders(id);
}

void Interface::edit_offer() {
	char q;
	string dummy_ingredients, dummy_price, dummy_count, dummy_packaging;
	Ingredient ingredient;
	double price, packaging;
	int count;
	cin >> q >> dummy_ingredients >> ingredient >> 
	dummy_price >> price >> dummy_count >> count;
	if (q != '?')
		throw BadRequest();
	if (dummy_ingredients != "ingredient")
		throw BadRequest();
	if (dummy_count != "count")
		throw BadRequest();
	goodeats_manager.edit_offer(ingredient, price, count);
	print_ok(); 
}

void Interface::get_offer() {
	char q;
	string dummy_ingredients, dummy_price, dummy_count, dummy_packaging;
	Ingredient ingredient;
	double price, packaging;
	int count;
	cin >> q >> dummy_ingredients >> ingredient >> 
	dummy_price >> price >> dummy_count >> count >> dummy_packaging >> packaging;
	if (q != '?')
		throw BadRequest();
	if (dummy_ingredients != "ingredient")
		throw BadRequest();
	if (dummy_count != "count")
		throw BadRequest();
	if (dummy_packaging != "packaging")
		throw BadRequest();
	goodeats_manager.add_offer(ingredient, price, count, packaging);
	print_ok();

}

void Interface::signup_supplier() {
	char q;
	string dummy_name, name, dummy_email, email, dummy_password, password;
	cin >> q >> dummy_name >> name >> dummy_email >> email >> dummy_password >> password;
	if (q != '?')
		throw BadRequest();

	if (dummy_name != "name")
		throw BadRequest();

	if (dummy_email != "email")
		throw BadRequest();

	if (dummy_password != "password")
		throw BadRequest();

	goodeats_manager.add_supplier(name, email, password);
	print_ok();
}

void Interface::get_filter() {
	char q;
	string filter_type;
	cin >> q >> filter_type;
	if (q != '?')
		throw BadRequest();
	if (filter_type == TAG_FILTER)
		get_tag_filter();
	else if (filter_type == VEG_FILTER) {
		goodeats_manager.add_veg_filter();
		print_ok();
	}
	else if (filter_type == MINUTES_FILTER)
		get_minutes_filter();
	else if (filter_type == RATING_FILTER)
		get_rating_filter();
	else throw NotFound();
}

void Interface::get_tag_filter() {
	string tag;
	cin >> tag;
	goodeats_manager.add_tag_filter(tag);
	print_ok();
}

void Interface::get_minutes_filter() {
	int min, max;
	string dummy_max_minutes;
	cin >> min >> dummy_max_minutes >> max;
	if (min > max)
		throw BadRequest();
	string dummy;
	getline(cin, dummy);
	if (dummy != "")
		throw BadRequest();
	goodeats_manager.add_minutes_filter(min, max);
	print_ok();
}

void Interface::get_rating_filter() {
	double min, max;
	string dummy_max_rating;
	cin >> min >> dummy_max_rating >> max;
	if (min > max)
		throw BadRequest();
	if (min < 0 || min > 5)
		throw BadRequest();
	if (max < 0 || max > 5)
		throw BadRequest();
	goodeats_manager.add_rating_filter(min, max);
	print_ok();
}

void Interface::get_users() {
	goodeats_manager.get_users();
}

void Interface::get_chefs() {
	string arguments;
	getline(cin, arguments);
	if (arguments == "")
		goodeats_manager.get_chefs();
	else {
		stringstream s(arguments);
		char q;
		string dummy_username, username;
		s >> q >> dummy_username >> username;
		if (q != '?')
			throw BadRequest();
		if (dummy_username != "chef_username")
			throw BadRequest();
		goodeats_manager.show_chef_info(username);
	}
}

void Interface::delete_shelf_recipe() {
	char q;
	string dummy_shelf_id, dummy_recipe_id;
	int shelf_id, recipe_id;
	cin >> q >> dummy_shelf_id >> shelf_id >> dummy_recipe_id >> recipe_id;
	if (q != '?')
		throw BadRequest();
	if (dummy_shelf_id != "shelf_id")
		throw BadRequest();
	if (dummy_recipe_id != "recipe_id")
		throw BadRequest();
	goodeats_manager.remove_recipe_from_shelf(shelf_id, recipe_id);
	print_ok();
}

void Interface::show_shelves_recipes() {
	char q;
	string dummy_shelf_id;
	int shelf_id;
	cin >> q >> dummy_shelf_id >> shelf_id;
	if (q != '?')
		throw BadRequest();
	if (dummy_shelf_id != "shelf_id")
		throw BadRequest();
	goodeats_manager.show_shelf_recipes(shelf_id);
}

void Interface::add_recipe_to_shelf() {
	char q;
	string dummy_shelf_id, dummy_recipe_id;
	int shelf_id, recipe_id;
	cin >> q >> dummy_shelf_id >> shelf_id >> dummy_recipe_id >> recipe_id;
	if (q != '?')
		throw BadRequest();
	if (dummy_shelf_id != "shelf_id")
		throw BadRequest();
	if (dummy_recipe_id != "recipe_id")
		throw BadRequest();
	goodeats_manager.add_recipe_to_shelf(shelf_id, recipe_id);
	print_ok();

}

void Interface::get_shelves() {
	char q;
	string dummy_username, username, dummy_limit;
	int limit;
	cin >> q >> dummy_username >> username >> dummy_limit >> limit;
	if (q != '?') 
		throw BadRequest();
	if (dummy_username != "username")
		throw BadRequest();
	if (dummy_limit != "limit")
		throw BadRequest();
	goodeats_manager.get_shelves(username, limit);

}

void Interface::add_shelf() {
	char q;
	string dummy_name, shelf_name;
	cin >> q >> dummy_name >> shelf_name;
	if (q != '?')
		throw BadRequest();
	if (dummy_name != "name")
		throw BadRequest();
	goodeats_manager.add_shelf(shelf_name);
}

void Interface::get_rating() {
	char q;
	string dummy_id, dummy_score;
	int id;
	double score;
	cin >> q >> dummy_id >> id >> dummy_score >> score;
	if (q != '?') 
		throw BadRequest();
	if (dummy_id != "recipe_id")
		throw BadRequest();
	if (dummy_score != "score")
		throw BadRequest();
	goodeats_manager.rate_recipe(id, score);
	print_ok();
}

void Interface::edit_rating() {
	char q;
	string dummy_id, dummy_score;
	int id;
	double score;
	cin >> q >> dummy_id >> id >> dummy_score >> score;
	if (q != '?')
		throw BadRequest();
	if (dummy_id != "recipe_id")
		throw BadRequest();
	if (dummy_score != "score")
		throw BadRequest();
	goodeats_manager.edit_rating(id, score);
	print_ok();
}


void Interface::delete_recipe() {
	char q;
	string dummy_id;
	int id;
	cin >> q >> dummy_id >> id;
	if (q != '?') 
		throw BadRequest();
	if (dummy_id != "id")
		throw BadRequest();
	goodeats_manager.delete_recipe(id);
	print_ok();
}

void Interface::show_recipe() {
	string arguments;
	getline(cin, arguments);
	if (arguments == "")
		goodeats_manager.show_recipes();
	else {
		stringstream s(arguments);
		char q;
		string dummy_id;
		int id;
		s >> q >> dummy_id >> id;
		if (q != '?')
			throw BadRequest();
		if (dummy_id != "id")
			throw BadRequest();
		goodeats_manager.show_recipe(id);

	}
}



void Interface::signup_Client() {
	char q;
	string arguments;
	getline(cin, arguments);
	stringstream s(arguments);
	string dummy_username, username, dummy_password, password, dummy_type, type, dummy;
	s >> q;
	if (q != '?')
		throw BadRequest();
	s >> dummy_username >> username;
	if (dummy_username != "username")
		throw BadRequest();
	s >> dummy_password >> password;
	if (dummy_password != "password")
		throw BadRequest();
	s >> dummy_type >> type;
	if (dummy_type != "type")
		throw BadRequest();
	getline(s, dummy);
	if (dummy != "")
		throw BadRequest();
	goodeats_manager.add_member(username, password, type);
	print_ok();
}

void Interface::logout() {
	goodeats_manager.logout_member();
	print_ok();
}

void Interface::login() {
	char q;
	string arguments;
	getline(cin, arguments);
	stringstream s(arguments);
	string dummy_username, username, dummy_password, password;
	s >> q;
	if (q != '?')
		throw BadRequest();
	s >> dummy_username >> username;
	if (dummy_username != "username" && dummy_username != "email")
		throw BadRequest();
	s >> dummy_password >> password;
	if (dummy_password != "password")
		throw BadRequest();
	string dummy;
	getline(s, dummy);
	if (dummy != "")
		throw BadRequest();
	if (dummy_username == "username")
		goodeats_manager.login_member(username, password);
	if (dummy_username == "email")
		goodeats_manager.login_supplier(username, password);
	print_ok();
}

void Interface::get_recipe() {
	char q;
	string arguments;
	getline(cin, arguments);
	stringstream s(arguments);
	string dummy_title, title, dummy_ingredients, ingredients, dummy_vegetarian, vegetarian,
	dummy_minutes, dummy_tags, tags, dummy_image_address, image_address;
	int minutes_to_ready;
	s >> q;
	if (q != '?')
		throw BadRequest();
	s >> dummy_title >> title >> dummy_ingredients >> ingredients >> dummy_vegetarian >> vegetarian
	  >> dummy_minutes >> minutes_to_ready >> dummy_tags >> tags >> dummy_image_address >> image_address;
	if (dummy_title != "title")
		throw BadRequest();
	if (dummy_ingredients != "ingredients")
		throw BadRequest();
	if (dummy_vegetarian != "vegetarian")
		throw BadRequest();
	if (dummy_minutes != "minutes_to_ready")
		throw BadRequest();
	if (dummy_tags != "tags")
		throw BadRequest();
	if (dummy_image_address != "image_address")
		throw BadRequest();
	Ingredients _ingredients = split(ingredients);
	Tags _tags = split(tags);
	Vegetarian veg;
	if (vegetarian == "Yes")
		veg = Yes;
	else if (vegetarian == "No")
		veg = No;
	goodeats_manager.add_recipe(title, _ingredients, veg, minutes_to_ready, _tags, image_address);

}

