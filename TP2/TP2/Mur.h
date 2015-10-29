#pragma once

#include <vld.h>
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Orientation.h"

namespace niveau
{
	class Mur
	{
	private:
		float longueure;
		float largeur;
		float posX;
		float posY;
		Orientation ori;
	public:
		Mur(const float posX, const float posY, const float largeur, const float longueure, const Orientation ori);
		~Mur();
		void Generer();
	};
}