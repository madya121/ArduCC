#include <Arduboy2.h>
#include <ArduboyTones.h>

#include "ArduEngine/ArduRect.cpp"
#include "ArduEngine/ArduSprite.cpp"
#include "ArduEngine/ArduText.cpp"
#include "ArduEngine/ArduEngine.cpp"

#include "SceneManager.cpp"

#include "Images.h"

Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);
ArduEngine *arduEngine = new ArduEngine(arduboy);

SceneManager *sceneManager = new SceneManager(*arduEngine);

void setup()
{
	arduboy.begin();
	arduboy.setFrameRate(30);
	arduboy.initRandomSeed();

	arduEngine->SetScene(CREDIT_CARD_SCENE_ID);
}

void loop()
{
	if (!(arduboy.nextFrame())) return;
	arduboy.pollButtons();
	arduboy.clear();

	arduEngine->Update(arduboy);

	arduboy.display();
}
