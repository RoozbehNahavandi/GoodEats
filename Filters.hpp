#ifndef _FILTERS_HPP_
#define _FILTERS_HPP_

#include <string>
#include "Recipe.hpp"
#include "Defines.hpp"
#include <iostream>

class Filter {
public:
	virtual void set_default() {};
	virtual void update_tag_filter(std::string) = 0;
	virtual void update_veg_filter() {};
	virtual void update_minutes_filter(int, int) {};
	virtual void update_rating_filter(double, double) {};
	virtual Recipes apply(Recipes recipes) { return recipes; };

};




class TagFilter : public Filter {
public:
	TagFilter(std::string _tag = DEFAULT_TAG) : tag(_tag) {};
	void set_default();
	void update_tag_filter(std::string);
	void update_veg_filter() {};
	void update_minutes_filter(int, int) {};
	void update_rating_filter(double, double) {};
	Recipes apply(Recipes);
private:
	std::string tag;
};





class VeganFilter : public Filter {
public:
	VeganFilter() : applied(false) {};
	void set_default();
	void update_tag_filter(std::string) {};
	void update_veg_filter();
	void update_minutes_filter(int, int) {};
	void update_rating_filter(double, double) {};
	Recipes apply(Recipes);

private:
	bool applied;
};



class MinutesFilter : public Filter {
public:
	MinutesFilter(int min = DEFAULT_MIN, int max = DEFAULT_MAX) : min_minutes(min), max_minutes(max) {};
	void set_default();
	void update_tag_filter(std::string) {};
	void update_veg_filter() {};
	void update_minutes_filter(int, int);
	void update_rating_filter(double, double) {};
	Recipes apply(Recipes);

private:
	int max_minutes;
	int min_minutes;
};





class RatingFilter : public Filter {
public:
	RatingFilter(double min = DEFAULT_MIN_RATE, double max = DEFAULT_MAX_RATE) : min_rating(min), max_rating(max) {};
	void set_default();
	void update_tag_filter(std::string) {};
	void update_veg_filter() {};
	void update_minutes_filter(int, int) {};
	void update_rating_filter(double, double);
	Recipes apply(Recipes);

private:
	double max_rating;
	double min_rating;
};



#endif