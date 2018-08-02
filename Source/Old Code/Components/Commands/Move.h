#include "stdafx.h"
#include "Command.h"

class MoveRight : public Command
{
	void			execute() override
	{
		move(20, 0);
	}
};
class MoveLeft : public Command
{
	void			execute() override
	{
		move(20, 0);
	}
};