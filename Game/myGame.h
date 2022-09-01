#pragma once
#include "Framework/game.h"

class myGame : public tech::Game
{
public:
	virtual void Initialize() override;
	virtual void Shutdown() override;
	virtual void Update() override;
	virtual void Draw(tech::Renderer& renderer) override;
	

private:
	float spawntimer = 0;
};