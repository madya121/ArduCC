#ifndef SCENE_MANAGER_CPP
#define SCENE_MANAGER_CPP

const int BACK_CREDIT_CARD_SCENE_ID = 0;
const int CREDIT_CARD_SCENE_ID = 2;

#include "Scenes/BackCreditCard.cpp"
#include "Scenes/CreditCard.cpp"

class SceneManager
{
public:
	BackCreditCard *backCreditCard;
	CreditCard *creditCard;
	
	SceneManager(ArduEngine &engine)
	{
		backCreditCard = new BackCreditCard(engine, BACK_CREDIT_CARD_SCENE_ID);
		creditCard = new CreditCard(engine, CREDIT_CARD_SCENE_ID);
	}
};
#endif
