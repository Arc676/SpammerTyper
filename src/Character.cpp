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
	orxVector_Copy(&position, &pos);
	key = character;

	entity = orxObject_CreateFromConfig("Character");
	orxObject_SetPosition(entity, &position);
	orxObject_SetTextString(entity, orxKeyboard_GetKeyName(key));

	orxVector_Mulf(&direction, &pos, -1.0f);
	orxVector_Normalize(&direction, &direction);
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
