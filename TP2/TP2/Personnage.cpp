#include "Personnage.h"

Texture Personnage::textureAttaque;
Texture Personnage::textureIddle;
Texture Personnage::textureMove;

Personnage::Personnage(const float posX, const float posY, const float speed, const int cadran, const int nbrNiveaux, const int nbrAnimsIddle, const int nbrAnimsMouv, const int nbrAnimsAttaque, RenderWindow* const renderWindow)
	:vitesse(vitesse), cadran(cadran), NBR_NIVEAUX(nbrNiveaux), NBR_ANIMS_IMMOBILE(nbrAnimsIddle), NBR_ANIMS_MOUVEMENT(nbrAnimsMouv), NBR_ANIMS_ATTAQUE(nbrAnimsAttaque), NBR_ANIMS(nbrAnimsAttaque + nbrAnimsIddle + nbrAnimsMouv), renderWindow(renderWindow), animateur(0), animateurImmobile(0), directionImmobile(1), estMobile(false), attaque(false)
{
	setPosition(posX, posY);
}

Personnage::~Personnage()
{
	for (int i = 0; i < NBR_NIVEAUX; i++)
	{
		delete[] intRectsImmobile[i];
		delete[] intRectsMouvement[i];
		delete[] intRectsAttaque[i];
	}
	delete[] intRectsImmobile;
	delete[] intRectsMouvement;
	delete[] intRectsAttaque;

}

bool Personnage::ChargerTextures(const char texturePathIddle[], const char texturePathMouv[], const char texturePathAttaque[])
{
	if (!textureIddle.loadFromFile(texturePathIddle))
	{
		return false;
	}
	if (!textureMove.loadFromFile(texturePathMouv))
	{
		return false;
	}
	if (!textureAttaque.loadFromFile(texturePathAttaque))
	{
		return false;
	}

	textureIddle.setSmooth(true);
	textureMove.setSmooth(true);
	textureAttaque.setSmooth(true);

	return true;
}

void Personnage::AjustementsVisuels()
{
	setTexture(textureIddle);

	intRectsImmobile = new IntRect*[NBR_NIVEAUX];
	intRectsMouvement = new IntRect*[NBR_NIVEAUX];
	intRectsAttaque = new IntRect*[NBR_NIVEAUX];

	for (int i = 0; i < NBR_NIVEAUX; i++)
	{
		intRectsImmobile[i] = new IntRect[NBR_ANIMS_IMMOBILE];

		int largeur = textureIddle.getSize().x / NBR_ANIMS_IMMOBILE;
		int hauteur = textureIddle.getSize().y / NBR_NIVEAUX;

		for (int j = 0; j < NBR_ANIMS_IMMOBILE; j++)
		{
			intRectsImmobile[i][j].left = largeur * j;
			intRectsImmobile[i][j].top = hauteur * i;
			intRectsImmobile[i][j].width = largeur;
			intRectsImmobile[i][j].height = hauteur;
		}
	}

	for (int i = 0; i < NBR_NIVEAUX; i++)
	{
		intRectsMouvement[i] = new IntRect[NBR_ANIMS_MOUVEMENT];

		int largeur = textureMove.getSize().x / NBR_ANIMS_MOUVEMENT;
		int hauteur = textureMove.getSize().y / NBR_NIVEAUX;

		for (int j = 0; j < NBR_ANIMS_MOUVEMENT; j++)
		{
			intRectsMouvement[i][j].left = largeur * j;
			intRectsMouvement[i][j].top = hauteur * i;
			intRectsMouvement[i][j].width = largeur;
			intRectsMouvement[i][j].height = hauteur;
		}
	}

	for (int i = 0; i < NBR_NIVEAUX; i++)
	{
		intRectsAttaque[i] = new IntRect[NBR_ANIMS_ATTAQUE];

		int largeur = textureAttaque.getSize().x / NBR_ANIMS_ATTAQUE;
		int hauteur = textureAttaque.getSize().y / NBR_NIVEAUX;

		for (int j = 0; j < NBR_ANIMS_ATTAQUE; j++)
		{
			intRectsAttaque[i][j].left = largeur * j;
			intRectsAttaque[i][j].top = hauteur * i;
			intRectsAttaque[i][j].width = largeur;
			intRectsAttaque[i][j].height = hauteur;
		}
	}

	setTextureRect(intRectsImmobile[cadran][0]);

	setOrigin(intRectsImmobile[0][0].height / 2, intRectsImmobile[0][0].width / 2);
}

void Personnage::AjustementsDuCadran(int cadran)
{
	if (cadran == -1 && estMobile)
	{
		estMobile = false;
		animateur = 0;
	}
	else if (cadran > -1)
	{
		if (!estMobile)
		{
			estMobile = true;
			animateur = 0;
		}

		this->cadran = cadran;
	}
}

void Personnage::Deplacement(float axeX, float axeY)
{
	move(axeX * vitesse, axeY * vitesse);

	setPosition(AutreCote(getPosition().x, renderWindow->getSize().x, (textureMove.getSize().x / NBR_ANIMS_MOUVEMENT) / 2), AutreCote(getPosition().y, renderWindow->getSize().y, (textureMove.getSize().y / NBR_NIVEAUX) / 2));

	if (estMobile)
	{
		setTexture(textureMove);
		if (animateur++ % SPEED_ANIMATION == 0)
		{
			setTextureRect(intRectsMouvement[cadran][(animateur / SPEED_ANIMATION) % NBR_ANIMS_MOUVEMENT]);
		}
	}
	else
	{
		if (animateur++ % SPEED_ANIMATION == 0)
		{
			setTexture(textureIddle);
			setTextureRect(intRectsImmobile[cadran][animateurImmobile]);
			animateurImmobile += directionImmobile;

			if (animateurImmobile == 0 || animateurImmobile == (NBR_ANIMS_IMMOBILE - 1))
			{
				directionImmobile *= -1;
			}
		}
	}
}

float Personnage::AutreCote(float positionDansAxe, const int tailleEcran, const int demiTaillePersonnage)
{
	if (positionDansAxe > tailleEcran + demiTaillePersonnage)
	{
		positionDansAxe -= tailleEcran + demiTaillePersonnage * 2;
	}
	else if (positionDansAxe < -demiTaillePersonnage)
	{
		positionDansAxe += tailleEcran + demiTaillePersonnage * 2;
	}
	return positionDansAxe;
}