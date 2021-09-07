//
//  Shape.cpp
//


#include <string>
#include <iostream>
#include <cassert>

#include "Shape.h"

using namespace std;


Shape shapeCalculate(bool is_open_north,
	bool is_open_south,
	bool is_open_east,
	bool is_open_west)
{
	//
	//  Method 1: Using a 4D array
	//

	Shape AAAA_SHAPE[2][2][2][2] =
	{
		{
			{ { SHAPE_BUBBLE,			SHAPE_W_DEAD_END, },
			{ SHAPE_S_DEAD_END,		SHAPE_SW_CORNER, }, },
			{ { SHAPE_E_DEAD_END,		SHAPE_EW_STRAIGHT, },
			{ SHAPE_SE_CORNER,		SHAPE_SEW_T_JUNCTION, }, },
		},
		{
			{ { SHAPE_N_DEAD_END,		SHAPE_NW_CORNER, },
			{ SHAPE_NS_STRAIGHT,		SHAPE_NSW_T_JUNCTION, }, },
			{ { SHAPE_NE_CORNER,		SHAPE_NEW_T_JUNCTION, },
			{ SHAPE_NSE_T_JUNCTION,	SHAPE_NSEW_CROSSROAD, }, },
		},
	};

	return AAAA_SHAPE[is_open_north]   // The C++ standard states that
		[is_open_east]   //  -> false converts to 0
	[is_open_south]   //  -> true  converts to 1 (not just any non-zero value)
	[is_open_west];  // so this is legal code

					 //
					 //  Method 2: Using 4 levels of nested if statements
					 //

	if (is_open_north)
	{
		if (is_open_east)
		{
			if (is_open_south)
			{
				if (is_open_west)
					return SHAPE_NSEW_CROSSROAD;
				else
					return SHAPE_NSE_T_JUNCTION;
			}
			else
			{
				if (is_open_west)
					return SHAPE_NEW_T_JUNCTION;
				else
					return SHAPE_NE_CORNER;
			}
		}
		else
		{
			if (is_open_south)
			{
				if (is_open_west)
					return SHAPE_NSW_T_JUNCTION;
				else
					return SHAPE_NS_STRAIGHT;
			}
			else
			{
				if (is_open_west)
					return SHAPE_NW_CORNER;
				else
					return SHAPE_N_DEAD_END;
			}
		}
	}
	else
	{
		if (is_open_east)
		{
			if (is_open_south)
			{
				if (is_open_west)
					return SHAPE_SEW_T_JUNCTION;
				else
					return SHAPE_SE_CORNER;
			}
			else
			{
				if (is_open_west)
					return SHAPE_EW_STRAIGHT;
				else
					return SHAPE_E_DEAD_END;
			}
		}
		else
		{
			if (is_open_south)
			{
				if (is_open_west)
					return SHAPE_SW_CORNER;
				else
					return SHAPE_S_DEAD_END;
			}
			else
			{
				if (is_open_west)
					return SHAPE_W_DEAD_END;
				else
					return SHAPE_BUBBLE;
			}
		}
	}
}

bool shapeIsTunnel(Shape shape)
{
	return shape < SHAPE_SOLID;
}

bool shapeIsCavern(Shape shape)
{
	return shape >= SHAPE_FIRST_CAVERN;
}

unsigned int shapeGetCavernIndex(Shape shape)
{
	return shape - SHAPE_FIRST_CAVERN;
}

Shape shapeGetCavernShape(unsigned int cavern_index)
{
	return cavern_index + SHAPE_FIRST_CAVERN;
}

char shapeGetMapChar(Shape shape)
{
	static const char A_SHAPE_CHARACTERS[SHAPE_COUNT] =
	{
		'O',  'N',  'S',  'E',  'W',  '|',  '-',  '\\',
		'/',  '/',  '\\', '>',  '<',  '^',  'v',  '+',
		' ',
	};

	if (shapeIsCavern(shape))
	{
		if (shape % 2 == 0)
			return ':';
		else
			return '.';
	}
	else
		return A_SHAPE_CHARACTERS[shape];
}


bool shapeIsTunnelStraight(Shape shape)
{
	assert(shapeIsTunnel(shape));

	if ((shape == SHAPE_NS_STRAIGHT) || (shape == SHAPE_EW_STRAIGHT))
		return true;
	else
		return false;
}


bool shapeIsTunnelDirection(Shape shape, Direction direction)
{
	assert((shapeIsTunnel(shape))&&(direction<DIRECTION_COUNT));

	bool A_SHAPE_CHARACTERS[SHAPE_COUNT][DIRECTION_COUNT] =
	{
		{
			false,false,false,false
		},

		{
			true,false,false,false
		},

		{
			false,true,false,false
		},
		{
			false,false,true,false
		},
		{
			false,false,false,true
		},
		{
			true,true,false,false
		},
		{
			false,false,true,true
		},
		{
			true,false,true,false
		},
		{
			true,false,false,true
		},
		{
			false,true,true,false
		},
		{
			false,true,false,true
		},
		{
			true,true,true,false
		},
		{
			true,true,false,true
		},
		{
			true,false,true,true
		},
		{
			false,true,true,true
		},
		{
			true,true,true,true
		},
	};
	return A_SHAPE_CHARACTERS[shape][direction];

}