#ifndef _INTERFACE_HPP_
#define _INTERFACE_HPP_

#include "Manager.hpp"

class Interface {
public:
	Interface() {};
	//~Interface();
	void run();
private:
	void post_type();
	void put_type();
	void delete_type();
	void get_type();
	void signup_Client();
	void signup_supplier();
	void logout();
	void login();
	void get_recipe();
	void delete_recipe();
	void show_recipe();
	void get_rating();
	void edit_rating();
	void add_shelf();
	void get_shelves();
	void add_recipe_to_shelf();
	void show_shelves_recipes();
	void delete_shelf_recipe();
	void get_chefs();
	void get_users();
	void get_filter();
	void get_tag_filter();
	void get_minutes_filter();
	void get_rating_filter();
	void get_offer();
	void edit_offer();
	void get_orders();
	void edit_credits();
	void delete_offer();

	Manager goodeats_manager;
};


#endif