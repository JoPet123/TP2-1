#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

class Personnage : public Sprite
{
private:
	const int SPEED_ANIMATION = 10;
	static Texture textureIddle;
	static Texture textureMove;
	static Texture textureAttaque;

	RenderWindow* renderWindow;
	float vitesse;

	int animateur;
	int cadran;

	int animateurImmobile;
	int directionImmobile;
	bool estMobile;
	bool attaque;

	IntRect** intRectsImmobile;
	IntRect** intRectsMouvement;
	IntRect** intRectsAttaque;

	const int NBR_NIVEAUX;
	const int NBR_ANIMS_IMMOBILE;
	const int NBR_ANIMS_MOUVEMENT;
	const int NBR_ANIMS_ATTAQUE;
	const int NBR_ANIMS;

	float AutreCote(float positionDansAxe, const int tailleEcran, const int demiTailleVaisseau);

public:
	Personnage(const float posX, const float posY, const float speed, const int cadran, const int nbrNiveaux, const int nbrAnimsIddle, const int nbrAnimsMouv, const int nbrAnimsAttaque, RenderWindow* const renderWindow);
	~Personnage();

	static bool ChargerTextures(const char texturePathIddle[], const char texturePathMouv[], const char texturePathAttaque[]);
	void AjustementsVisuels();

	void AjustementsDuCadran(int cadran);
	void Deplacement(float axeX, float axeY);
};