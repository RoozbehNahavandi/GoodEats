#ifndef _DEFINES_HPP_
#define _DEFINES_HPP_

#include <string>
#include <vector>
#include <utility>
#include "Offer.hpp"

class Client;
class Shelf;
class Recipe;
class Filter;

typedef std::string Command_Type;
typedef std::string Command;
typedef std::vector<Client*> Members;
typedef std::vector<Recipe*> Recipes;
typedef std::vector<Shelf*> Shelves;
typedef std::string Member_Type;
typedef std::string Ingredient;
typedef std::vector<Ingredient> Ingredients;
typedef bool Vegetarian;
typedef std::string Title;
typedef std::string Tag;
typedef std::vector<Tag> Tags;
typedef std::string Image_address;
typedef bool Deleted;
typedef std::vector<Recipe*> Rated_Recipes;
typedef std::pair<Client*, double> Rate;
typedef std::vector<Rate> Rates;
typedef std::vector<Filter*> Filters;
typedef std::vector<Offer*> Offers;


const Command_Type COMMAND_RECIEVED = "OK";
const Command_Type PUT_COMMAND_TYPE = "PUT";
const Command_Type POST_COMMAND_TYPE = "POST";
const Command_Type DELETE_COMMAND_TYPE = "DELETE";
const Command_Type GET_COMMAND_TYPE = "GET";

const Member_Type CHEF = "chef";
const Member_Type USER = "user";

const Command SIGNUP_COMMAND = "signup";
const Command LOGOUT_COMMAND = "logout";
const Command LOGIN_COMMAND = "login";
const Command RECIPES_COMMAND = "recipes";
const Command MY_RECIPES_COMMAND = "my_recipes";
const Command DELETE_RECIPE_COMMAND = "recipes";
const Command GET_RECIPES = "recipes";
const Command RATE_COMMAND = "rates";
const Command EDIT_RATING = "rates";
const Command ADD_SHELF_COMMAND = "shelves";
const Command GET_SHELVES_COMMAND = "shelves";
const Command ADD_RECIPE_TO_SHELF = "shelves_recipes";
const Command GET_SHELVES_RECIPES = "shelves_recipes";
const Command DELETE_SHELF_RECIPE = "shelves_recipes";
const Command GET_CHEFS = "chefs";
const Command GET_USERS = "users";
const Command FILTER_COMMAND = "filters";
const Command SIGNUP_SUPPLIER_COMMAND = "signup_supplier";
const Command OFFERS_COMMAND = "offers";
const Command EDIT_OFFER = "offers";
const Command OFFERS = "offers";
const Command ORDERS = "orders";
const Command GET_CREDITS_COMMAND = "credits";
const Command EDIT_CREDITS = "credits";
const Command DELETE_OFFER = "offers";
const Command GET_ORDERS_COMMAND = "orders";


const std::string TAG_FILTER = "tag";
const std::string VEG_FILTER = "vegetarian";
const std::string MINUTES_FILTER = "min-minutes";
const std::string RATING_FILTER = "min_rating";
const std::string DELETE_FILTERS = "filters";
const int DEFAULT_MIN = -1;
const int DEFAULT_MAX = -1;
const double DEFAULT_MIN_RATE = -1;
const double DEFAULT_MAX_RATE = -1;
const std::string DEFAULT_TAG = "";
const int PRECISION = 1;
const int NOT_FOUND = -1;
const int OFF_COUNT = 20;
const bool Yes = true;
const bool No = false;
const double OFF = 0.9;

#endif