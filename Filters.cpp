#include "Filters.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

void TagFilter::set_default() {
	tag = DEFAULT_TAG;
}

void TagFilter::update_tag_filter(string new_tag) {
	tag = new_tag;
}

Recipes TagFilter::apply(Recipes recipes) {
	Recipes filtered_recipes;
	if (tag == DEFAULT_TAG) 
		return recipes;
	for (auto recipe : recipes)
		if (recipe->same_tag(tag))
			filtered_recipes.push_back(recipe);
	return filtered_recipes;
}



// ************************************** //



void VeganFilter::set_default() {
	applied = false;
}

void VeganFilter::update_veg_filter() {
	applied = true;
}

Recipes VeganFilter::apply(Recipes recipes) {
	if (!applied)
		return recipes;
	Recipes filtered_recipes;
	for (auto recipe : recipes)
		if (recipe->is_vegan())
			filtered_recipes.push_back(recipe);
	return filtered_recipes;
}





// ************************************** //





void MinutesFilter::set_default() {
	min_minutes = DEFAULT_MIN;
	max_minutes = DEFAULT_MAX;
}

void MinutesFilter::update_minutes_filter(int min, int max) {
	min_minutes = min;
	max_minutes = max;
}

Recipes MinutesFilter::apply(Recipes recipes) {
	if (min_minutes == DEFAULT_MIN)
		return recipes;
	Recipes filtered_recipes;
	for (auto recipe : recipes)
		if (recipe->ready_time_is_in_boundary(min_minutes, max_minutes))
			filtered_recipes.push_back(recipe);
	return filtered_recipes;
}


// ************************************** //



void RatingFilter::set_default() {
	min_rating = DEFAULT_MIN_RATE;
	max_rating = DEFAULT_MAX_RATE;
}

void RatingFilter::update_rating_filter(double min, double max) {
	min_rating = min;
	max_rating = max;
}

Recipes RatingFilter::apply(Recipes recipes) {
	if (min_rating == DEFAULT_MAX_RATE)
		return recipes;
	Recipes filtered_recipes;
	for (auto recipe : recipes)
		if (recipe->rate_is_in_boundary(min_rating, max_rating)) 
			filtered_recipes.push_back(recipe);
	return filtered_recipes;
}