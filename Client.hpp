#ifndef _Client_HPP_
#define _Client_HPP_

#include "Recipe.hpp"
#include "Orders.hpp"

class Shelf;

class Client {
public:
	Client(std::string, std::string);
	bool same_username(std::string);
	bool correct_password(std::string);
	virtual void add_recipe(Recipe*) = 0;
	virtual void show_your_recipes() {};
	virtual Recipe* find_recipe_by_id(int) = 0;
	virtual void rate_recipe(Recipe*, double) = 0;
	virtual bool has_already_rated_this_recipe(Recipe*) = 0;
	virtual void update_rating(Recipe*, double) = 0;
	virtual void add_shelf(Shelf*) = 0;
	virtual bool has_shelves() = 0;
	virtual void print_shelves(int) = 0;
	virtual Shelf* find_shelf_by_id(int) = 0;
	virtual bool has_this_shelf(Shelf*) = 0;
	virtual bool is_allowed_to_enter_user_commands() = 0;
	virtual std::string get_chef_username() = 0;
	virtual void print_chef() = 0;
	virtual void print_user() = 0;
	virtual std::string get_user_username() = 0;
	virtual bool same_username_as_chef(std::string) = 0;
	virtual void get_chef_info() = 0;
	virtual bool same_email(std::string email) { return false; };
	virtual bool same_name_as_supplier(std::string name) { return false; };
	virtual void add_offer(std::string, double, int, double);
	virtual void edit_offer(std::string, double, int);
	virtual void show_credits() = 0;
	virtual void add_credits(int) = 0;
	virtual Offer* find_offer_by_ingredient(std::string) = 0;
	virtual double ingredient_price(std::string) = 0;
	virtual std::string get_name() = 0;
	virtual void add_orders(Orders*) = 0;
	virtual void pay(double) = 0;
	virtual bool same_name(std::string) = 0;
	virtual void increase_credits(double) = 0;
	virtual void delete_offer(std::string) = 0;
	virtual void show_orders() = 0;
	virtual int count_of_ingredient(std::string) { return 0; };
protected:
	std::string username;
	std::string password;
	double credit = 0;
};

class User : public Client {
public:
	User(std::string, std::string);
	void add_recipe(Recipe*);
	void show_your_recipes();
	Recipe* find_recipe_by_id(int);
	void rate_recipe(Recipe*, double);
	bool has_already_rated_this_recipe(Recipe*);
	void update_rating(Recipe*, double);
	void add_shelf(Shelf*);
	bool has_shelves() { return true; };
	void print_shelves(int);
	Shelf* find_shelf_by_id(int);
	bool has_this_shelf(Shelf*);
	bool is_allowed_to_enter_user_commands() { return true; };
	std::string get_chef_username();
	void print_chef();
	std::string get_user_username();
	void print_user();
	bool same_username_as_chef(std::string);
	void get_chef_info();
	void add_offer(std::string, double, int, double);
	void edit_offer(std::string, double, int);
	void show_credits();
	void add_credits(int);
	Offer* find_offer_by_ingredient(std::string) { return NULL; };
	double ingredient_price(std::string);
	std::string get_name();
	void add_orders(Orders* _orders) { orders.push_back(_orders); };
	void pay(double);
	bool same_name(std::string) { return false; };
	void increase_credits(double) {};
	void delete_offer(std::string) { throw PermissionDenied(); };
	void show_orders();
private:
	Rated_Recipes rated_recipes;
	Shelves shelves;
	double credits = 0;
	std::vector<Orders*> orders;

};

class Chef : public Client {
public:
	Chef(std::string, std::string);
	void add_recipe(Recipe*);
	void show_your_recipes();
	Recipe* find_recipe_by_id(int);
	Recipe* find_recipe_by_title(std::string);
	void rate_recipe(Recipe*, double);
	bool has_already_rated_this_recipe(Recipe*);
	void update_rating(Recipe*, double);
	void add_shelf(Shelf*);
	bool has_shelves() { return false; };
	void print_shelves(int);
	Shelf* find_shelf_by_id(int);
	bool has_this_shelf(Shelf*);
	bool is_allowed_to_enter_user_commands() { return false; };
	std::string get_chef_username();
	void print_chef();
	double chef_score();
	void print_user();
	std::string get_user_username();
	bool same_username_as_chef(std::string);
	void get_chef_info();
	void add_offer(std::string, double, int, double);
	void edit_offer(std::string, double, int);
	void show_credits();
	void add_credits(int);
	Offer* find_offer_by_ingredient(std::string) { return NULL; };
	double ingredient_price(std::string);
	std::string get_name();
	void add_orders(Orders* orders) {};
	void pay(double) { return; };
	bool same_name(std::string) { return false; };
	void increase_credits(double) {};
	void delete_offer(std::string) { throw PermissionDenied(); };
	void show_orders() { throw PermissionDenied(); };
private:
	Recipes recipes;
};





class Supplier : public Client {
public:
	Supplier(std::string, std::string, std::string);
	void add_recipe(Recipe*);
	void show_your_recipes();
	Recipe* find_recipe_by_id(int);
	void rate_recipe(Recipe*, double);
	bool has_already_rated_this_recipe(Recipe*);
	void update_rating(Recipe*, double);
	void add_shelf(Shelf*);
	bool has_shelves() { return false; };
	void print_shelves(int);
	Shelf* find_shelf_by_id(int);
	bool has_this_shelf(Shelf*);
	bool is_allowed_to_enter_user_commands() { return false; };
	std::string get_chef_username();
	void print_chef();
	std::string get_user_username();
	void print_user();
	bool same_username_as_chef(std::string);
	void get_chef_info();
	bool same_email(std::string _email) { return _email == username; };
	bool same_name_as_supplier(std::string _name) { return _name == name; };
	void add_offer(std::string, double, int, double);
	bool ingredient_is_unique(std::string);
	void edit_offer(std::string, double, int);
	void show_credits();
	void add_credits(int);
	Offer* find_offer_by_ingredient(std::string);
	double ingredient_price(std::string);
	std::string get_name();
	void add_orders(Orders* orders) {};
	void pay(double) { return; };
	bool same_name(std::string _name) { return name == _name; };
	void increase_credits(double money) { credit += money; };
	void delete_offer(std::string);
	void show_orders() { throw PermissionDenied(); };
	int count_of_ingredient(std::string);
private:	
	std::string name;
	double credit = 0;
	Offers offers;
};




#endif