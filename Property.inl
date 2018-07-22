//#include "Property.h"		//	Not needed
//
//template<typename T>
//Property<T>::Property(std::string id, T val)
//	: value{ val }
//	, BaseProperty{ id }		//	Send the property ID to the abstract base class
//{
//}
//
//template<typename T>
//Property<T>::operator()() const
//{
//	return value;
//}





template<typename T>
Property<T>::Property(std::string identifier, T val)
	: id{ identifier }
	, value{ val }
{
}

template<typename T>
std::string Property<T>::getID() const
{
	return id;
}



