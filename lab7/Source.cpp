/*Test case 1: input-0 - expected output-go back to the root menu. - output-went back to the root menu.

			   input-1 - expected output-show the inventory. - output-showed the inventory.
			   
Test case 2:   input-2 - expected output-show the balance. - output-showed the balance.

Test case 3:   input-potato - expected output-go back to the root menu. - output-went back to the root menu.

			   input-3 - expected output-go to buy a car menu. - output-went to buy a car menu.

			   input-KIA - expected output-ask for the color. - output-asked for the color.

			   input-Black - expected output-ask for the price. - output-ask for the price.

			   input-3100 - expected output-add the car. - output-did it as expected.
			 
			   input-1 - expected output-show the car added. - output-showed the added car.

			   input-2 - expected output-show the new balance. - output-showed the new balance.

Test case 4:   input-8 - expected output-quit the program. - output-quitted the program.*/

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <iomanip>
#include "Car.h"
#include <fstream>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::fixed;
using std::setprecision;

const int MAX_OPITION = 8;

int wrong(){

	int again = 1;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(std::numeric_limits<int>::max(), '\n');

		return again;
	}
}

int find_name(const vector <Car> cars, string car_name){
	
	int finder = 0;
	string car_name2;

	for (int slot = 0; slot < cars.size(); slot++)
	{
		car_name2 = cars[slot].get_name();

		if (car_name2 != car_name){

			finder++;
		}
		if (car_name2 == car_name){

			return slot;
		}
		if (finder == cars.size()){
			return -1;
		}
	}
}

void buy(double& balance, string car_name, string car_color, double car_price, vector <Car>& cars){
	if (balance >= 0){
		cout << "\nYou added this car.\n\n";

		if (cars[0].get_name() == ""){
			cars[0] = Car(car_name, car_color, car_price);
		}
		else{
			cars.push_back(Car(car_name, car_color, car_price));
		}
	}
	else{
		balance = balance + car_price;

		cout << "\nYou do not have the balance available to buy this car.\n\n";
	}
}

void sell(double& balance, vector <Car>& cars, int slot){
	
	balance = balance + cars[slot].get_price();
	cout << "\nYou removed this car.\n\n";
	if (cars.size() == 1){
		cars[0] = Car("", "", 0);
	}
	else{
		cars.erase(cars.begin() + slot);
	}
}

void paint(string car_color, vector <Car>& cars, int slot){
	
	cout << "\nEnter the new color of the car:\n\n";

	cin >> car_color;

	cout << endl;

	cout << "\nYou changed this car's color.\n\n";

	cars[slot].paint(car_color);
}

void load(string file_name, double& balance, vector <Car>& cars){
	ifstream in_file;
	
	in_file.open(file_name);

	if (in_file.fail())
	{
		cout << "\nCouldn't load file\n\n" << endl;
	}
	else{
		string str;
		string color;
		double prise;
		double rest;

		in_file >> rest;

		balance = balance + rest;

		for (int i = 0; getline(in_file, str); i++)
		{
			in_file >> str >> color >> prise;

			if (cars[0].get_name() == ""){
				cars[0] = Car(str, color, prise);
			}
			else{
				cars.push_back(Car(str, color, prise));
			}

		}
		in_file.close();
	}
}

int main(){

	string next_line;
	ifstream in_file;
	ofstream myfile;
	string file_name;
	int slot = 0;
	double car_price = 0;
	string car_color;
	string car_name;
	double balance = 10000;
	int while1=0;
	vector<Car>cars;

	cars.push_back(Car("", "", 0));

	do
	{

		cout << "Show Current Inventory: <Type 1>\n" <<
			"\nShow Current Balance: <Type 2>\n" <<
			"\nBuy a Car: <Type 3>\n" <<
			"\nSell a Car: <Type 4>\n" <<
			"\nPaint a Car: <Type 5>\n" <<
			"\nLoad File: <Type 6>\n" <<
			"\nSave File: <Type 7>\n" <<
			"\nQuit the program: <Type 8>\n\n";
	
		int choice;
		choice = 0;
		cin >> choice;

		cout << endl;
		
		while1 = wrong();

		if (while1 == 1){
			cout << "\nThat was not a valid number. Try it again!!!\n\n";
		}
		else if ((choice < 1) || (choice > MAX_OPITION))
		{
			cout << "\nThat was not a valid number. Try it again!!!\n\n";
			while1++;
		}
		switch (choice)
		{
		case 1:
			
			if (cars[0].get_name() == ""){
				cout << "\nYour inventory is empty.\n\n";
			}
			else{
				for (int q = 0; q < cars.size(); q++){
					cout << cars[q].to_string() << endl;
				}
			}
			while1++;
		
			break;

		case 2:

			cout << "\nYour Balance is $"<<fixed<< setprecision(2)<< balance<<"\n\n";
			
			while1++;
			
			break;

		case 3:
			
			cout << "\nEnter the name of the car you bought:\n\n";
			
			cin >> car_name;

			slot = find_name(cars, car_name);

			if (slot == -1){
			
			cout << "\nEnter the color of the car:\n\n";

			cin >> car_color;

			cout << "\nEnter the cost of the car:\n\n";

			cin >> car_price;
			cout << endl;
					
				balance = balance - car_price;
				
				buy(balance, car_name, car_color, car_price, cars);						
			}
			else{
				cout << "\nThis car is in your inventory already.\n\n";
			}
			while1++;

			break;

		case 4:
			
			cout << "\nEnter the name of the car you sold:\n\n";

			cin >> car_name;

			cout << endl;
						
			slot = find_name(cars, car_name);

			if (slot == -1){

				cout << "\nThis car is not in your inventory.\n\n";				
			}
			else{
				
				sell(balance, cars, slot);			
			}			
			while1++;

			break;

		case 5:
			
			cout << "\nEnter the name of the car you painted:\n\n";

			cin >> car_name;

			slot = find_name(cars, car_name);

			if (slot == -1){

				cout << "\nThis car is not in your inventory.\n\n";
			}
			else{
			
				paint(car_color, cars, slot);							
			}
			while1++;

			break;
		
		case 6:
		
			cout << "\nEnter the name of your file:\n\n";
			
			cin >> file_name;
						
			load(file_name, balance, cars);
				
			while1++;

			break;

		case 7:

			cout << "\nEnter a name to your file:\n\n";

			cin >> file_name;

			cout << endl;
			myfile.open(file_name);

			if (myfile.fail())
			{
				cout << "\nCouldn't write to file\n\n" << endl;
			}

			myfile << fixed<<setprecision(2)<<balance;
			for (int i = 0; i < cars.size(); i++)
			{
				myfile << endl << cars[i].get_name() << " " << cars[i].get_color() << " " << fixed << setprecision(2) << cars[i].get_price();
			}
			myfile.close();

			cout << "\nThe file was saved successufully.\n\n";

			while1++;
			
			break;
		case 8:
			return 0;
		}
	} while (while1 != 0);

	return 0;
}