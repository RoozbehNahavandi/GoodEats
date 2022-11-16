#ifndef _MANAGER_HPP_
#define _MANAGER_HPP_
#include <vector>
#include "Client.hpp"
#include "Shelf.hpp"
#include "Defines.hpp"
#include "Filters.hpp"
#include <sstream>
#include <iostream>

class Manager {
public:
	Manager();
	//~Manager();
	void add_member(std::string, std::string, std::string);
	void logout_member();
	void login_member(std::string, std::string);
	void add_recipe(Title, Ingredients, Vegetarian, int, Tags, Image_address);
	void show_chef_recipes();
	void delete_recipe(int);
	void show_recipes();
	void show_recipe(int);
	void rate_recipe(int, double);
	void edit_rating(int, double);
	void add_shelf(std::string);
	void get_shelves(std::string, int);
	void add_recipe_to_shelf(int, int);
	void show_shelf_recipes(int);
	void remove_recipe_from_shelf(int, int);
	void get_chefs();
	void get_users();
	void show_chef_info(std::string);

	void add_tag_filter(std::string);
	void add_veg_filter();
	void add_minutes_filter(int, int);
	void add_rating_filter(double, double);
	void delete_filters();
	Recipes apply_filters(Recipes);
	void add_supplier(std::string, std::string, std::string);
	bool email_is_unique(std::string);
	void login_supplier(std::string, std::string);
	void add_offer(std::string, double, int, double);
	void edit_offer(std::string, double, int);
	void get_credits();
	void edit_credits(int);
	void get_orders(int);
	void delete_ingredient_offer(std::string);
	void show_orders();
private:
	bool username_is_unique(std::string);
	bool name_is_unique(std::string);
	Client* find_member_by_username(std::string);
	int find_next_id();
	int find_next_shelf_id();
	Recipe* find_recipe_by_id(int);
	void check_score_boundary(double);
	Shelf* find_shelf_by_id(int);
	Recipe* find_recipe_by_title(std::string);
	Client* find_user_by_username(std::string);
	Client* find_chef_by_username(std::string);
	Client* find_supplier_by_email(std::string);
	Offer* find_best_offer(std::string);
	Client* find_supplier_by_name(std::string);
	bool is_off(std::string);

	Client* current_member = NULL;
	Members members;
	Recipes recipes;
	Shelves shelves;
	Filters filters;
};



#endif