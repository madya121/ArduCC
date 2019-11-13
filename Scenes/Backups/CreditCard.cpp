#ifndef CreditCard_CPP
#define CreditCard_CPP

#include "../ArduEngine/ArduEngine.h"

#include "../Images.h"
#include "../SceneManager.cpp"

class CreditCard : public ArduScene
{
public:
	CreditCard(ArduEngine &engine, uint8_t sceneID) : ArduScene(sceneID, engine)
	{
		// This will be called once when the game start
		logo = new ArduSprite(0, 0, 128, 64, WHITE, arduengine_splash, engine);
	}
	
	void Load(ArduEngine &engine)
	{
		// This will be called once everytime we enter this scene
	}
	
	void Run(ArduEngine &engine)
	{
		// This will be called every frame when we're in this scene
	}
	
	void Destroy(ArduEngine &engine)
	{
		// This will be called once everytime we leave this scene
	}
	

private:
	  ArduSprite *logo;
};


#endif
