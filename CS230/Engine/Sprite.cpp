/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Sprite.cpp
Project: CS230
Author: Juseung Yang
Creation date: 3/24/2022
-----------------------------------------------------------------*/

#include "Sprite.h"
#include "Animation.h"
#include "Engine.h" 

CS230::Sprite::Sprite() {}

CS230::Sprite::~Sprite() {
	for (Animation* anim : animations) {
		delete anim;
	}
	animations.clear();
}

void CS230::Sprite::Load(const std::filesystem::path& spriteInfoFile) 
{
	animations.clear();
	hotSpotList.clear();
	frameTexel.clear();

	if (spriteInfoFile.extension() != ".spt") {
		throw std::runtime_error("Bad Filetype.  " + spriteInfoFile.generic_string() + " not a sprite info file (.spt)");
	}
	std::ifstream inFile(spriteInfoFile);

	if (inFile.is_open() == false) {
		throw std::runtime_error("Failed to load " + spriteInfoFile.generic_string());
	}

	std::string text;
	inFile >> text;
	texture.Load(text);
	frameSize = texture.GetSize();

	inFile >> text;
	while (inFile.eof() == false) {
		if (text == "FrameSize") {
			inFile >> frameSize.x;
			inFile >> frameSize.y;
		}
		else if (text == "NumFrames") {
			int numFrames;
			inFile >> numFrames;
			for (int i = 0; i < numFrames; i++) {
				frameTexel.push_back({ frameSize.x * i, 0 });
			}
		}
		else if (text == "Frame") {
			int frameLocationX, frameLocationY;
			inFile >> frameLocationX;
			inFile >> frameLocationY;
			frameTexel.push_back({ frameLocationX, frameLocationY });
		}
		else if (text == "HotSpot") {
			int hotSpotX, hotSpotY;
			inFile >> hotSpotX;
			inFile >> hotSpotY;
			hotSpotList.push_back({ hotSpotX, hotSpotY });
		}
		else if (text == "Anim")
		{
			inFile >> text;
			animations.push_back(new Animation(text));
		}
		else {
			Engine::GetLogger().LogError("Unknown spt command " + text);
		}
		inFile >> text;
	}
	if (frameTexel.empty() == true) {
		frameTexel.push_back({ 0,0 });
	}

	if (animations.empty() == true)
	{
		animations.push_back(new Animation());
		PlayAnimation(0);
	}
}

math::ivec2 CS230::Sprite::GetHotSpot(int index)
{

	if (index >= hotSpotList.size() )
	{
		Engine::GetLogger().LogError("Sprite is missing hotspot index: "+ std::to_string(index));
		return { 0,0 };
	}

	return hotSpotList[index];
}

void CS230::Sprite::PlayAnimation(int anim)
{
	if ( anim < 0 || anim >= animations.size() )
	{
		Engine::GetLogger().LogError("Animation "+std::to_string(anim)+" not found");
		currAnim = 0;
	}
	else
	{
		currAnim = anim;
		animations[currAnim]->ResetAnimation();
	}
}

bool CS230::Sprite::IsAnimationDone()
{
	return animations[currAnim]->IsAnimationDone();
}

void CS230::Sprite::Update(double dt)
{
	animations[currAnim]->Update(dt);
}

math::ivec2 CS230::Sprite::GetFrameSize() const
{
	return frameSize;
}

math::ivec2 CS230::Sprite::GetFrameTexel(int frameNum) const
{
	if ( frameNum < 0 || frameNum >= frameTexel.size() )
	{
		Engine::GetLogger().LogError( "Bad frame request: " + std::to_string(frameNum) );
		return { 0,0 };
	}
	else
	{
		return frameTexel[frameNum];
	}
}

void CS230::Sprite::Draw(math::TransformMatrix displayMatrix)
{
	texture.Draw(displayMatrix * math::TranslateMatrix(-GetHotSpot(0)), GetFrameTexel(animations[currAnim]->GetDisplayFrame()), GetFrameSize());
}