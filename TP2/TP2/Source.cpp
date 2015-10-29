//#include <vld.h>
#define _USE_MATH_DEFINES
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Personnage.h"
#include "Mur.h"


using namespace sf;

const int WIDHT = 1280;
const int HEIGHT = 720;

const int VITESSE = 10;

const float ZONE_TANGEANTE1 = tanf(M_PI / 8);
const float DIAGONALE = cos(M_PI_4);
const float ZONE_TANGEANTE2 = tanf((M_PI * 3) / 8);

const int NB_FRAME_IMMOBILE = 16;
const int NB_FRAME_MOUV = 8;
const int NB_FRAME_ATTAQUE = 18;
const int NB_NIVEAUX = 8;

RenderWindow mainWin(VideoMode(WIDHT, HEIGHT, 32), "Fury");
View view(mainWin.getDefaultView());
Event event;

Sprite background1;
Texture Tbackground1;

Sprite background2;
Texture Tbackground2;

Personnage * Personnage1;
Vector2f interfaceDeplacement;

bool Init();
void GetInputs();
void Update();
void Draw();

void KeyboardMouvement();

int main()
{
	if (!Init())
	{
		return EXIT_FAILURE;
	}

	while (mainWin.isOpen())
	{
		GetInputs();
		Update();
		Draw();
	}

	delete Personnage1;

	return EXIT_SUCCESS;
}

bool Init()
{
	mainWin.setFramerateLimit(60);

	if (!Tbackground1.loadFromFile("Sprites\\tile1.png"))
	{
		return false;
	}

	//if (!Tbackground2.loadFromFile("Sprites\\tile2.png"))
	//{
	//	return false;
	//}

	if (!Personnage::ChargerTextures("Sprites\\PersoIddle.png", "Sprites\\PersoCourse.png", "Sprites\\attaque.png"))
	{
		return false;
	}

	Tbackground1.setRepeated(true);
	//Tbackground2.setRepeated(true);

	background1.setTexture(Tbackground1);
	background1.setTextureRect(IntRect(0, 0, 1280, 720));
	//background2.setTexture(Tbackground2);
	//background2.setTextureRect(IntRect(640, 360, 1280, 720));


	Personnage1 = new Personnage(WIDHT / 2, 100.0f, VITESSE, 6, NB_NIVEAUX, NB_FRAME_IMMOBILE, NB_FRAME_MOUV, NB_FRAME_ATTAQUE, &mainWin);
	Personnage1->AjustementsVisuels();

	interfaceDeplacement.x = 0;
	interfaceDeplacement.y = 0;

	return true;
}

void GetInputs()
{
	while (mainWin.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			mainWin.close();
		}
	}

	KeyboardMouvement();
}

void Update()
{
	Personnage1->Deplacement(interfaceDeplacement.x, interfaceDeplacement.y);
}

void Draw()
{
	mainWin.clear();

	mainWin.draw(background1);
	//mainWin.draw(background2);

	mainWin.draw(*Personnage1);

	mainWin.display();
}

void KeyboardMouvement()
{
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			interfaceDeplacement.x = -DIAGONALE;
			interfaceDeplacement.y = -DIAGONALE;
			Personnage1->AjustementsDuCadran(NO);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			interfaceDeplacement.x = -DIAGONALE;
			interfaceDeplacement.y = DIAGONALE;
			Personnage1->AjustementsDuCadran(SO);
		}
		else
		{
			interfaceDeplacement.x = -1;
			interfaceDeplacement.y = 0;
			Personnage1->AjustementsDuCadran(O);
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			interfaceDeplacement.x = DIAGONALE;
			interfaceDeplacement.y = -DIAGONALE;
			Personnage1->AjustementsDuCadran(NE);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			interfaceDeplacement.x = DIAGONALE;
			interfaceDeplacement.y = DIAGONALE;
			Personnage1->AjustementsDuCadran(SE);
		}
		else
		{
			interfaceDeplacement.x = 1;
			interfaceDeplacement.y = 0;
			Personnage1->AjustementsDuCadran(E);
		}
	}
	else
	{
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			interfaceDeplacement.x = 0;
			interfaceDeplacement.y = -1;
			Personnage1->AjustementsDuCadran(N);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			interfaceDeplacement.x = 0;
			interfaceDeplacement.y = 1;
			Personnage1->AjustementsDuCadran(S);
		}
		else
		{
			interfaceDeplacement.x = 0;
			interfaceDeplacement.y = 0;
			Personnage1->AjustementsDuCadran(IMMOBILE);
		}
	}
}