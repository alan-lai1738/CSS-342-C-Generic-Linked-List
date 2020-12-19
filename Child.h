/*
 * Child.h
 *
 * Child.h Declaration
 *
 * CSS 342: Assignment 3
 *
 * Declaration for Child CLass
 *
 * 11/6-15/2020
 * Alan Lai
 * alan.lai1738@gmail.com
 *
 */
#pragma once
#include <string>
using namespace std;
class Child
{
public:
	Child();
	Child(const Child &other);
	Child(string first, string last, int age);

	int getAge() const;
	string getFirstName() const;
	string getLastName() const;

	bool operator<(const Child& to_compare) const;
	bool operator>(const Child& to_compare) const;
	bool operator==(const Child& to_compare) const;
	bool operator!=(const Child& to_compare) const;
	Child operator=(const Child& right_hand_side);

	friend ostream& operator<<(ostream& out_stream, const Child& right_hand_side);
	friend istream& operator>>(istream& in_stream, Child& right_hand_side);

private:
	string first_name_;
	string last_name_;
	int age_;

};

