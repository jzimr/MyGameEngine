#pragma once
#include "stdafx.h"
#include "BaseProperty.h"
#include <string>

//template<typename T>
//class Property : public BaseProperty
//{
//public:
//	Property(std::string id, T val);
//	T operator ()() const;
//	void suhDud();
//
//private:
//	T value;
//
//};
//
//#include "Property.inl"



template <typename T>
class Property
{
public:
	Property(std::string identifier, T val);
	
	//	If it is too confusing using Property.value to get the value,
	//	simply add some operator overloading here

	std::string getID() const;				//	Can't change ID after it's initialized

public:
	T value;

private:
	std::string	id;
};

#include "Property.inl"

