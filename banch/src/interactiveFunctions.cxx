/// \file interactiveFunctions.hxx
///
/// \brief function definitons for interactiveFunctions.hxx

#include "banch/interactiveFunctions.hxx"

/// \brief namespace for the banch project
namespace banch {

// class Fadd_beverage //

void Fadd_beverage::operator()()
{
	// prompt for Beverage name
	this->os_ << "Please enter the beverage's name: ";
	std::string name;
	getline(this->is_, name);

	// prompt for Beverage quantity
	this->os_ << "Please enter how many units of the beverage is needed: ";
	std::string quantaString;
	int quanta;
	do
	{
		getline(this->is_, quantaString);
	}
	while (!(std::stringstream(quantaString) >> quanta) || quanta <= 0);

	// confirm
	std::stringstream tmp;
	tmp << quanta << " units of " << name;
	if (confirm(this->os_, this->is_, tmp.str()))
	{
		this->recipe_.add(new Beverage(name, quanta));
	}
}

	
// class Fadd_extra //

void Fadd_extra::operator()()
{
	this->os_ << "Please enter the extra (garnish, decoration, etc): ";
	std::string extra;
	getline(this->is_, extra);

	if (confirm(this->os_, this->is_, extra))
	{
		this->recipe_.add(new Extra(extra));
	}
}


// class Fremove_ingredient //

void Fremove_ingredient::operator()()
{
	// list Ingredients
	this->os_ << "0) cancel";
	this->recipe_.showNumbered(this->os_);
	this->os_ << std::endl;

	// make user choose one
	this->os_ << "Please enter number of ingredient to remove (0 to cancel): ";
	std::string input;
	int selection;
	do
	{
		getline(this->is_, input);
	}
	while (!(std::stringstream(input) >> selection) ||
			selection < 0 || selection > this->recipe_.number_of_ingredients());

	// 0 cancels
	if (selection == 0)
	{
		return;
	}

	std::stringstream tmp;
	tmp << "Will remove: " << selection << ')';
	if (confirm(this->os_, this->is_, tmp.str()))
	{
		this->recipe_.remove(selection);
	}
}


// class Fadd_recipe //

void Fadd_recipe::operator()()
{
	// create recipe with chosen name
	this->os_ << "Please enter a name for the new recipe: ";
	std::string recipename;
	getline(this->is_, recipename);
	Recipe * recipe = new Recipe(recipename);

	menu::Menu menu(this->os_, this->is_);
	menu.add(menu::Option("add new beverage ingredient",
						std::function<void()>(Fadd_beverage(this->os_,
															this->is_,
															*recipe)
												)
					)
			);
	menu.add(menu::Option("add new extra ingredient",
						std::function<void()>(Fadd_extra(this->os_,
															this->is_,
															*recipe)
												)
					)
			);
	menu();

	std::stringstream tmp;
	recipe->show(tmp);
	if (confirm(this->os_, this->is_, tmp.str()))
	{
		this->book_.add(recipe);
	}
}


// class Fmodify_recipe //

void Fmodify_recipe::operator()()
{
	// list Recipes for the user
	Flist_recipes(this->os_, this->book_)();
	//
}

} // namespace banch
