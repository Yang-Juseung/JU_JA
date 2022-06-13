/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Rect.h
Project: CS230
Author: Juseung Yang
Creation date: 4/5/2022
-----------------------------------------------------------------*/

#pragma once

//Todo: Create a simple struct for a rectangle.
//You should create a rect2and irect2 for the vec2and ivec2(you can make these into templates if you like).
//It will need a bottomLeftand topRight position(using the correct vector class)

namespace math
{
	struct rect2
	{
		math::vec2 bottomLeft;
		math::vec2 topRight;
	};

	struct irect2
	{
		math::ivec2 bottomLeft;
		math::ivec2 topRight;
	};
}
