#include "stdafx.h"
#include "Test.h"

Test::Test(Entity* ent)
	: Component{ ent }
	, test{ 100 }
{

}

int Test::getTest() const
{
	return test;
}