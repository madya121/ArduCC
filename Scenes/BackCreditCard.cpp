#ifndef BackCreditCard_CPP
#define BackCreditCard_CPP

#include "../ArduEngine/ArduEngine.h"

#include "../Images.h"
#include "../SceneManager.cpp"

class BackCreditCard : public ArduScene
{
public:
	BackCreditCard(ArduEngine &engine, uint8_t sceneID) : ArduScene(sceneID, engine)
	{
		int address = 128;
        EEPROM.get(address, this->content);
        
        for (int i = 0; i < 3; i++) {
            if (this->content[i] < 0)
                this->content[i] = this->defaultContent[i];
        }
	}
	
	void Load(ArduEngine &engine)
	{
		// This will be called once everytime we enter this scene
	}
	
	void Run(ArduEngine &engine)
	{
        // BOX
        engine.arduboy->fillRect(0, 0, 128, 2, WHITE);
        engine.arduboy->fillRect(0, 62, 128, 2, WHITE);
        engine.arduboy->fillRect(0, 0, 2, 64, WHITE);
        engine.arduboy->fillRect(126, 0, 2, 64, WHITE);
        
		// This will be called every frame when we're in this scene
        for (int x = 0; x <= 128; x++) {
            for (int y = 10; y <= 30; y++) {
                if ((x + y) % 2 == 0) {
                    engine.arduboy->drawPixel(x, y, WHITE);
                }
            }
        }
        
        for (int i = 0; i < 3; i++) {
            engine.arduboy->setCursor(cursor[i], 15);
            engine.arduboy->print(this->content[i]);
        }
        
        if (sc) {
            engine.arduboy->fillRect(cursor[cc], 23, 5, 1, WHITE);
        }
        
        this->cursorTime += 1;
        if (this->cursorTime > 15) {
            sc ^= true;
            this->cursorTime = 0;
        }
        
        if (engine.arduboy->justPressed(RIGHT_BUTTON)) {
          cc = (cc + 1) % 3;
        } 
        
        if (engine.arduboy->justPressed(LEFT_BUTTON)) {
          cc = ((cc - 1) + 3) % 3;
        }
        
        if (engine.arduboy->justPressed(UP_BUTTON)) {
            this->content[cc] = (this->content[cc] + 1) % 10;
            
            this->save = true;
        }
        
        if (engine.arduboy->justPressed(DOWN_BUTTON)) {
            this->content[cc] = ((this->content[cc] - 1) + 10) % 10;
            
            this->save = true;
        }
        
        if (this->save) {
            engine.arduboy->setCursor(4, 50);
            engine.arduboy->print("(A)save");
        }
        
        if (this->save && engine.arduboy->justPressed(A_BUTTON)) {
            int address = 128;
            
            EEPROM.put(address, this->content);
            
            this->save = false;
        }
        
        engine.arduboy->setCursor(4, 40);
        engine.arduboy->print("Developer: GrimPros");
        
        if (engine.arduboy->justPressed(B_BUTTON)) {
            engine.SetScene(CREDIT_CARD_SCENE_ID);
        }
	}
	
	void Destroy(ArduEngine &engine)
	{
		// This will be called once everytime we leave this scene
	}
	

private:
	  ArduSprite *logo;
      int cursor[3] = {20, 26, 32};
      int content[3] = {5, 8, 2};
      int defaultContent[3] = {5, 8, 2};
      int cc = 0;
      int cursorTime = 0;
      
      bool sc = true;
      bool save = false;
};


#endif
