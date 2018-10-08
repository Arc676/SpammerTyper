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

#include "Character.h"

orxCOLOR Character::green;
orxCOLOR Character::red;

void Character::initColors() {
	orxVECTOR rgb;
	rgb.fX = 1;
	rgb.fY = 0;
	rgb.fZ = 0;

	red.vRGB = rgb;
	red.fAlpha = 1;

	rgb.fX = 0;
	rgb.fY = 1;

	green.vRGB = rgb;
	green.fAlpha = 1;
}

Character::Character(orxVECTOR pos, orxKEYBOARD_KEY character) {
	// copy character properties
	orxVector_Copy(&position, &pos);
	key = character;

	// obtain corresponding character from key code
	entity = orxObject_CreateFromConfig("Character");
	orxObject_SetPosition(entity, &position);
	const orxSTRING name = orxKeyboard_GetKeyName(character);
	const orxSTRING c = name + orxString_GetLength(name) - 1;
	orxObject_SetTextString(entity, c);

	// determine movement vector
	orxVector_Mulf(&direction, &pos, -1.0f);
	orxVector_Normalize(&direction, &direction);
	orxVector_Mulf(&direction, &direction, 50.0f);

	switch (orxMath_GetRandomU32(0, 2)) {
	case 1:
		hpGain = orxMath_GetRandomU32(5, 20);
		orxObject_SetColorRecursive(entity, &Character::red);
		break;
	case 2:
		scoreGain = orxMath_GetRandomU32(10, 50);
		orxObject_SetColorRecursive(entity, &Character::green);
		break;
	default:
		break;
	}
}

void Character::update(const orxCLOCK_INFO* clock) {
	orxVECTOR ds;
	orxVector_Copy(&ds, &direction);
	orxVector_Mulf(&ds, &ds, clock->fDT);
	orxVector_Add(&position, &position, &ds);
	orxObject_SetPosition(entity, &position);
}

void Character::despawn(int* HP, int* score) {
	orxObject_SetLifeTime(entity, 0);
	// if HP and score aren't null pointers
	if (HP && score) {
		*HP += hpGain;
		*score += scoreGain;
	}
}

orxKEYBOARD_KEY Character::getKey() {
	return key;
}

orxVECTOR Character::getPosition() {
	return position;
}
