/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Texture.cpp
Purpose: Wrapper class for doodle::Image
Project: CS230
Author: Juseung Yang
Creation date: 3/24/2022
-----------------------------------------------------------------*/
#include <doodle/drawing.hpp>	
#include "Texture.h"
#include "TransformMatrix.h"

CS230::Texture::Texture() {}

CS230::Texture::Texture(const std::filesystem::path& filePath)
{
	Load(filePath);
} 


void CS230::Texture::Load(const std::filesystem::path& filePath) {
	image = doodle::Image{ filePath };
}

void CS230::Texture::Draw(math::TransformMatrix displayMatrix) 
{
    doodle::push_settings();
    doodle::apply_matrix(displayMatrix[0][0], displayMatrix[1][0], displayMatrix[0][1], displayMatrix[1][1], displayMatrix[0][2], displayMatrix[1][2]);
    doodle::draw_image(image, 0, 0);
    doodle::pop_settings();
}

void CS230::Texture::Draw(math::TransformMatrix displayMatrix, math::ivec2 texelPos, math::ivec2 frameSize)
{
    doodle::push_settings();
    doodle::apply_matrix(displayMatrix[0][0], displayMatrix[1][0], displayMatrix[0][1], displayMatrix[1][1], displayMatrix[0][2], displayMatrix[1][2]);
    doodle::draw_image(image, 0, 0, static_cast<double>(frameSize.x), static_cast<double>(frameSize.y), texelPos.x, texelPos.y);
    doodle::pop_settings();
}

math::ivec2 CS230::Texture::GetSize() { return { image.GetWidth(), image.GetHeight() }; }