//Copyright (C) 2018 Arc676/Alessandro Vinciguerra <alesvinciguerra@gmail.com>

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation (version 3)

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.
//See README and LICENSE for more details

#ifndef Character_h
#define Character_h

#include "orx.h"

class Character {
	orxOBJECT* entity;
	orxVECTOR position, direction;
	orxKEYBOARD_KEY key;

	int hpGain = 0, scoreGain = 0;

	static orxCOLOR red, green;
public:
	/**
	 * Initializes color constants
	 */
	static void initColors();

	/**
	 * Constructs a new character
	 * @param HP Player's current health
	 * @param pos Initial position for the character
	 * @param character The character to display (and to type to destroy this entity)
	 */
	Character(int HP, orxVECTOR pos, orxKEYBOARD_KEY character);

	/**
	 * Update the character's position
	 * @param clock Time information for the update
	 */
	void update(const orxCLOCK_INFO* clock);

	/**
	 * Destroy the associated entity
	 * @param HP Pointer to player health if HP gain should be applied
	 * @param score Pointer to player score if score bonuses should be applied
	 */
	void despawn(int* HP, int* score);

	/**
	 * Gets the associated key
	 * @return Key code for the character
	 */
	orxKEYBOARD_KEY getKey();

	/**
	 * Gets the character's position in the world
	 * @return Current position vector for the character
	 */
	orxVECTOR getPosition();
};

#endif
