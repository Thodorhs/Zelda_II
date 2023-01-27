//#include "GameCharacters.h"
#include "GreatPalaceBot.h"
#include "Guma.h"

GameCharacter* GameCharacter::create(Character_t type) {
	switch (type) {
	case GreatPalaceBot_t:
		return new GreatPalaceBot();
		break;

	case Wosu_t:
		//return new Wosu();
		break;
	case Guma_t:
		return new Guma();
		break;
	case Stalfos_t:
		//return new Stalfos();
		break;
	default:
		break;
	}
}