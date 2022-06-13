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

namespace math
{
	struct [[nodiscard]] rect2
	{
		math::vec2 bottomLeft{ 0.0,0.0 };
		math::vec2 topRight{ 0.0,0.0 };
	};

	struct [[nodiscard]] irect2
	{
		math::ivec2 bottomLeft{ 0,0 };
		math::ivec2 topRight{ 0,0 };
	};
}
