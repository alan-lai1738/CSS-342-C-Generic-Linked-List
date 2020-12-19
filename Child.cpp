/*
 * Child.cpp
 *
 * Child.cpp Definition
 *
 * CSS 342: Assignment 3
 *
 * Definitions for Child CLass
 *
 * 11/6-15/2020
 * Alan Lai
 * alan.lai1738@gmail.com
 *
 */
#include "Child.h"
#include <string>
#include <iostream>
using namespace std;

Child::Child() {
	first_name_ = "";
	last_name_ = "";
	age_ = 0;
}

Child::Child(const Child& other)
{
	first_name_ = other.first_name_;
	last_name_ = other.last_name_;
	age_ = other.age_;
}

Child::Child(string first, string last, int age)
{
	first_name_ = first;
	last_name_ = last;
	age_ = age;
}

int Child::getAge() const
{
	return this->age_;
}

string Child::getFirstName() const
{
	return this->first_name_;
}

string Child::getLastName() const
{
	return this->last_name_;
}

bool Child::operator<(const Child& to_compare) const
{
	if (this->last_name_ < to_compare.getLastName())
	{
		return true;
	}
	else if (this->last_name_ == to_compare.getLastName())
	{
		if (this->first_name_ == to_compare.getFirstName())
		{
			if (age_ < to_compare.age_)
			{
				return true;
			}
		}
		else if (first_name_ < to_compare.first_name_)
		{
			return true;
		}
		return false;
	}
}

bool Child::operator>(const Child& to_compare) const
{
	if (this->last_name_ > to_compare.getLastName())
	{
		return true;
	}
	else if (this->last_name_ == to_compare.getLastName())
	{
		if (this->first_name_ == to_compare.getFirstName())
		{
			if (age_ > to_compare.age_)
			{
				return true;
			}
		}
		else if (first_name_ > to_compare.first_name_)
		{
			return true;
		}
		return false;
	}
}

	bool Child::operator==(const Child & to_compare) const
	{
		if (this->last_name_ != to_compare.getLastName())
		{
			return false;
		}
		if (this->first_name_ != to_compare.getFirstName())
		{
			return false;
		}
		if (this->age_ != to_compare.getAge())
		{
			return false;
		}
		return true;
	}


bool Child::operator!=(const Child& to_compare) const
{
	return !(*this == to_compare);
}

Child Child::operator=(const Child& right_hand_side)
{
	this->first_name_ = right_hand_side.first_name_;
	this->last_name_ = right_hand_side.last_name_;
	this->age_ = right_hand_side.age_;
	return *this;
}

ostream& operator<<(ostream& out_stream, const Child& right_hand_side)
{
	cout << right_hand_side.getFirstName() << right_hand_side.getLastName() << right_hand_side.age_;
	return out_stream;
}

istream& operator>>(istream& in_stream, Child &right_hand_side)
{
	in_stream >> right_hand_side.first_name_ >> right_hand_side.last_name_ >> right_hand_side.age_;
	return in_stream;
}
