#include "Background.h"
#include "..\Engine\Camera.h"
#include "..\Engine\TransformMatrix.h"

void Background::Add(const std::filesystem::path& texturePath, int level)
{
	backgrounds.push_back(ParallaxInfo{ CS230::Texture(texturePath),level });
}

void Background::Unload()
{
	backgrounds.clear();
}

void Background::Draw(const CS230::Camera& camera)
{
	for (int i = 0; i < backgrounds.size(); i++)
	{
		math::vec2 BackgroundVec (-camera.GetPosition() / backgrounds[i].level);
		backgrounds[i].texture.Draw(math::TranslateMatrix(BackgroundVec));
	}
}

math::ivec2 Background::Size()
{
	for (int i = 0; i < backgrounds.size(); i++)
	{
		if (backgrounds[i].level == 1)
		{
			return backgrounds[i].texture.GetSize();
		}
	}

	return math::ivec2(0);
}
