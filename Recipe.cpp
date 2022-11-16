#include "Recipe.hpp"
#include <iostream>
#include "Defines.hpp"
#include <iomanip>
#include <cmath>
#include "Filters.hpp"
using namespace std;


void print_id(int id) {
	cout << id << endl;
}
void print_title(string title) {
	cout << title << endl;
}
void print_vegetarian(Vegetarian veg) {
	cout << "vegetarian: ";
	if (veg == Yes)
		cout << "Yes" << endl;
	else cout << "No" << endl;
}
void print_ingredients(Ingredients ingredients) {
	cout << "ingredients: [";
	for (int i = 0; i < ingredients.size() - 1; i++)
		cout << ingredients[i] << ", ";
	cout << ingredients[ingredients.size()-1] << "]";
	cout << endl;
}
void print_minutes_to_ready(int mins) {
	cout << "minutes to ready: " << mins << endl;
}
void print_tags(Tags tags) {
	cout << "tags: [";
	for (int i = 0; i < tags.size() - 1; i++)
		cout << tags[i] << ", ";
	cout << tags[tags.size()-1] << "]";
	cout << endl;
}
void Recipe::print_rating() {
	double rate = calculate_rating();
	cout << fixed;
	cout << "rating: " << setprecision(PRECISION) <<  rate << endl;
}

double Recipe::calculate_rating() {
	if (rates.size() == 0)
		return 0;
	double sum = 0; 
	for (Rate x : rates) {
		sum += x.second;
	}
	double avg = sum / rates.size();
	avg = ceil(avg*10)/10;
	return avg;
}

Recipe::Recipe(int _id, Title _title, Ingredients _ingredients, Vegetarian _veg, int _minutes_to_ready,
			   Tags _tags, Image_address _img_address) 
	: id(_id), title(_title), ingredients(_ingredients), veg(_veg),
	 minutes_to_ready(_minutes_to_ready), tags(_tags), image_address(_img_address) {};

void Recipe::print_recipe() {
	print_id(id);
	print_title(title);
	print_vegetarian(veg);
	print_ingredients(ingredients);
	print_minutes_to_ready(minutes_to_ready);
	print_tags(tags);
	print_rating();
}

bool Recipe::same_id(int _id) { return id == _id; };

void Recipe::delete_recipe() { deleted = Yes; };

bool Recipe::same_title(string _title) { return title == _title; };

void Recipe::print_recipe_for_user() {
	cout << id << " " << title << " ";
	if (veg)
		cout << "Yes ";
	else cout << "No ";
	cout << minutes_to_ready << endl;
}
void Recipe::add_rating(Client* Client, double score) {
	Rate rate;
	rate.first = Client;
	rate.second = score;
	rates.push_back(rate);
}

void Recipe::update_rating(Client* Client, double score) {
	for (auto &x : rates)
		if (x.first == Client)
			x.second = score;
}

double Recipe::sum_of_scores() {
	double sum = 0;
	for (auto rate : rates)
		sum += rate.second;
	return sum;
}

void Recipe::print_recipe_with_rating() {
	cout << id << " " << title << " ";
	if (veg)
		cout << "Yes ";
	else cout << "No ";
	double score = calculate_rating();
	cout << minutes_to_ready << " " << score << endl;
}

bool Recipe::same_tag(Tag tag) {
	for (Tag t : tags) 
		if (t == tag) 
			return true;
	return false;
}

bool Recipe::ready_time_is_in_boundary(int min, int max) {
	if (min <= minutes_to_ready && minutes_to_ready <= max)
		return true;
	return false;
}

bool Recipe::rate_is_in_boundary(double min, double max) {
	double score = calculate_rating();
	if (min <= score && score <= max)
		return true;
	return false;
}