#ifndef _RECIPE_HPP_
#define _RECIPE_HPP_

#include <string>
#include "Exceptions.hpp"
#include "Defines.hpp"
class Client;

class Recipe {
public:
	Recipe(int, Title, Ingredients, Vegetarian, int, Tags, Image_address);
	int get_id() { return id; };
	void print_recipe();
	bool same_id(int);
	void delete_recipe();
	bool is_not_deleted() { return !deleted; };
	bool same_title(std::string);
	std::string get_title() { return title; };
	void print_recipe_for_user();
	void add_rating(Client*, double);
	void update_rating(Client*, double);
	double number_of_people_scored() { return rates.size(); };
	double sum_of_scores();
	void print_recipe_with_rating();
	double calculate_rating();
	void print_rating();
	double num_of_rates() { return rates.size(); };
	bool same_tag(std::string);
	bool is_vegan() { return veg; };
	bool ready_time_is_in_boundary(int, int);
	bool rate_is_in_boundary(double, double);
	Ingredients get_ingredients() { return ingredients; };


private:
	int id;
	Title title;
	Ingredients ingredients;
	Vegetarian veg;
	int minutes_to_ready;
	Tags tags;
	Image_address image_address;
	Deleted deleted = No;
	Rates rates;
};

#endif