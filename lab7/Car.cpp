//WARNING: It is expressly forbidden to modify any part of this document, including its name
#include "Car.h"
using namespace std;

//---------------------------------------------------------------------------------------
Car::Car(string name_in, string color_in, double price_in)
{
	name = name_in;
	color = color_in;
	price = price_in;
}
Car::~Car(){}
//---------------------------------------------------------------------------------------
string Car::get_name() const
{
	return name;
}
string Car::get_color() const
{
	return color;
}
double Car::get_price() const
{
	return price;
}
//---------------------------------------------------------------------------------------
void Car::paint(string new_color)
{
	color = new_color;
	price += 1000;
}
//---------------------------------------------------------------------------------------
string Car::to_string() const
{
	stringstream ss;
	ss << "Name: " << name << endl;
	ss << "Color: " << color << endl;
	ss << "Price: $" << price << endl;
	return ss.str();
}
//---------------------------------------------------------------------------------------
