#ifndef _OFFER_HPP_
#define _OFFER_HPP_

#include <string>

class Offer {
public:
	Offer(std::string, std::string, double, double, int);
	void decrease_count_by_one();
	bool same_ingredient(std::string ing) { return ing == ingredient; };
	void edit_offer(std::string, double, int);
	double calculate_price() { return price + packaging; };
	bool still_available() { return count > 0; };
	std::string get_supplier() { return supplier_name; };
	double get_price() { return packaging + price; };
	bool is_deleted() { return deleted; };
	void delete_offer() { deleted = true; };
	int count_of_ingredient() { return count; };
private:
	std::string supplier_name;
	std::string ingredient;
	double price;
	double packaging;
	int count;
	bool deleted = false;
};

#endif
