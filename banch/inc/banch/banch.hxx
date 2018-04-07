#ifndef BANCH_HXX
#define BANCH_HXX

#include "nostl/string.hxx"
#include "nostl/set.hxx"

namespace banch {

class Ingredient {
public:
	virtual void print() const;

	virtual bool operator==(const Ingredient&);

	virtual ~Ingredient(); // virtual destructor for this class shall be derived later
};

class Recipe {
public:
	Recipe() : number_of_ingredients_(0) { ingredients_ = new nostl::Set<Ingredient>; }

	void add(const Ingredient& addendum) { this->ingredients_->insert(addendum); }
	void remove(const Ingredient& delendum) { this->ingredients_->remove(delendum); }

	void show() const;

	void save() const;
	void load();

	~Recipe() { delete ingredients_; }

private:
	nostl::Set<Ingredient> * ingredients_; // heterogenous container
	unsigned int number_of_ingredients_;
}; // class Recipe

} // namespace banch

#endif // BANCH_HXX
