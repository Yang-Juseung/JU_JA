/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Camera.cpp
Project: CS230
Author: Juseung Yang
Creation date: 4/5/2022
-----------------------------------------------------------------*/

#include "Camera.h"
#include "TransformMatrix.h"

CS230::Camera::Camera(math::rect2 movableRange)
	: movableRange(movableRange)
{
}

void CS230::Camera::SetPosition(math::vec2 newPosition)
{
    position = newPosition;
}

const math::vec2& CS230::Camera::GetPosition() const
{
	return position;
}

void CS230::Camera::SetExtent(math::irect2 newExtent)
{
    extent = newExtent;
}

math::TransformMatrix CS230::Camera::GetMatrix()
{
    return math::TranslateMatrix(-position);
}

void CS230::Camera::Update(const math::vec2& followObjPos)
{
    if (followObjPos.x <= movableRange.bottomLeft.x+ position.x)
    {
        position.x = followObjPos.x - movableRange.bottomLeft.x;
    }

    if (followObjPos.x >= movableRange.topRight.x+ position.x)
    {
        position.x = followObjPos.x - movableRange.topRight.x;
    }

    if (position.x >= extent.topRight.x)
    {
        position.x = extent.topRight.x;
    }

    if (position.x <= extent.bottomLeft.x)
    {
        position.x = extent.bottomLeft.x;
    }

    if (followObjPos.y <= movableRange.bottomLeft.y + position.y)
    {
        position.y = followObjPos.y - movableRange.bottomLeft.y;
    }

    if (followObjPos.y >= movableRange.topRight.y + position.y)
    {
        position.y = followObjPos.y - movableRange.topRight.y;
    }

    if (position.y >= extent.topRight.y)
    {
        position.y = extent.topRight.y;
    }

    if (position.y <= extent.bottomLeft.y)
    {
        position.y = extent.bottomLeft.y;
    }
}
