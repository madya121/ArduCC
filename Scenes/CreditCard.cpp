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
        int address = 256;
        EEPROM.get(address, content);
        
        for (int i = 0; i < 20; i++) {
            if (content[i] < 0)
                content[i] = defaultContent[i];
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
        
        // MASTER CARD LOGO
        engine.arduboy->fillRect(95, 10, 20, 20, WHITE);
        engine.arduboy->fillRect(80, 5, 20, 20, WHITE);
        engine.arduboy->fillRect(82, 7, 16, 16, BLACK);
        engine.arduboy->fillRect(95, 10, 5, 15, BLACK);
        
        // CHIP
        engine.arduboy->drawRoundRect(10, 5, 40, 25, 5, WHITE);
        engine.arduboy->drawLine(15, 5, 30, 12, WHITE);
        engine.arduboy->drawLine(45, 5, 30, 12, WHITE);
        engine.arduboy->drawLine(10, 17, 49, 17, WHITE);
        engine.arduboy->drawLine(25, 17, 25, 29, WHITE);
        engine.arduboy->drawLine(10, 22, 25, 22, WHITE);
        
        for (int x = 95; x <= 100; x++) {
            for (int y = 10; y <= 25; y++) {
                if ((x + y) % 2 == 0)
                    engine.arduboy->drawPixel(x, y, WHITE);
            }
        }
        
        for (int i = 0; i < 16; i++) {
            engine.arduboy->setCursor(cursorX[i], 35);
            engine.arduboy->print(content[i]);
        }
        
        engine.arduboy->setCursor(58, 50);
        engine.arduboy->print("Valid: ");
        
        for (int i = 16; i < 20; i++) {
            engine.arduboy->setCursor(cursorX[i], 50);
            engine.arduboy->print(content[i]);
        }
        
        engine.arduboy->setCursor(107, 50);
        engine.arduboy->print("/");
        
        if (showCursor) {
            engine.arduboy->fillRect(cursorX[currentCursor], cursorY[currentCursor], 5, 1, WHITE);
        }
        
        cursorTime += 1;
        if (cursorTime > 15) {
            showCursor ^= true;
            cursorTime = 0;
        }
        
        // INPUT
        if (engine.arduboy->justPressed(RIGHT_BUTTON)) {
          currentCursor = (currentCursor + 1) % 20;
        } 
        
        if (engine.arduboy->justPressed(LEFT_BUTTON)) {
          currentCursor = ((currentCursor - 1) + 20) % 20;
        }
        
        if (engine.arduboy->justPressed(UP_BUTTON)) {
            content[currentCursor] = (content[currentCursor] + 1) % 10;
            
            save = true;
        }
        
        if (engine.arduboy->justPressed(DOWN_BUTTON)) {
            content[currentCursor] = ((content[currentCursor] - 1) + 10) % 10;
            
            save = true;
        }
        
        if (save) {
            engine.arduboy->setCursor(4, 50);
            engine.arduboy->print("(A)save");
        }
        
        if (save && engine.arduboy->justPressed(A_BUTTON)) {
            int address = 256;
            
            EEPROM.put(address, content);
            
            save = false;
        }
        
        if (engine.arduboy->justPressed(B_BUTTON)) {
            engine.SetScene(BACK_CREDIT_CARD_SCENE_ID);
        }
	}
	
	void Destroy(ArduEngine &engine)
	{
		// This will be called once everytime we leave this scene
	}
	

private:
	  ArduSprite *logo;
      int cursorX[20] = {4, 10, 16, 22, 34, 40, 46, 52, 64, 70, 76, 82, 94, 100, 106, 112, 95, 101, 113, 119};
      int cursorY[20] = {43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 58, 58, 58, 58};
      int content[20] = {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1};
      int defaultContent[20] = {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1};
      int currentCursor = 0;
      bool save = false;
      
      bool showCursor = true;
      int cursorTime = 0;
};


#endif
