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
	orxVector_Mulf(&direction, &direction, 40.0f);
}

void Character::update(const orxCLOCK_INFO* clock) {
	orxVECTOR ds;
	orxVector_Copy(&ds, &direction);
	orxVector_Mulf(&ds, &ds, clock->fDT);
	orxVector_Add(&position, &position, &ds);
	orxObject_SetPosition(entity, &position);
}

void Character::despawn() {
	orxObject_SetLifeTime(entity, 0);
}

orxKEYBOARD_KEY Character::getKey() {
	return key;
}

orxVECTOR Character::getPosition() {
	return position;
}
