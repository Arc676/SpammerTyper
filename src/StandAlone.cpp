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

#include "StandAlone.h"

StandAlone* StandAlone::m_Instance = orxNULL;
orxCAMERA* StandAlone::camera = orxNULL;
orxVECTOR StandAlone::camPos;
std::list<Character*> StandAlone::chars;
orxFLOAT StandAlone::secondsSinceSpawn = 0;

StandAlone* StandAlone::Instance() {
	if (m_Instance != orxNULL) {
		return m_Instance;
	}
	m_Instance = new StandAlone();
	return m_Instance;
}

StandAlone::StandAlone() {}

orxSTATUS orxFASTCALL StandAlone::Init() {
	orxVIEWPORT* viewport = orxViewport_CreateFromConfig("Viewport");
	camera = orxViewport_GetCamera(viewport);

	orxCamera_GetPosition(camera, &camPos);

	orxCLOCK* upClock = orxClock_FindFirst(-1.0f, orxCLOCK_TYPE_CORE);
	orxClock_Register(upClock, Update, orxNULL, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_NORMAL);

	orxEvent_AddHandler(orxEVENT_TYPE_PHYSICS, StandAlone::EventHandler);

	chars = std::list<Character*>();

	return orxSTATUS_SUCCESS;
}

orxSTATUS orxFASTCALL StandAlone::Run() {
	return orxSTATUS_SUCCESS;
}

void orxFASTCALL StandAlone::Exit() {
	return;
}

void StandAlone::spawnChar() {
	orxVECTOR pos = {
		orxMath_GetRandomFloat(100, 500),
		orxMath_GetRandomFloat(100, 300),
		0
	};
	if (orxMath_GetRandomU32(0, 99) < 50) {
		pos.fX *= -1;
	}
	if (orxMath_GetRandomU32(0, 99) < 50) {
		pos.fY *= -1;
	}
	Character* c = new Character(pos,
		(orxKEYBOARD_KEY)orxMath_GetRandomU32(0, orxKEYBOARD_KEY_9));
	chars.push_back(c);
}

void orxFASTCALL StandAlone::Update(const orxCLOCK_INFO* clockInfo, void* context) {
	secondsSinceSpawn += clockInfo->fDT;
	if (secondsSinceSpawn > 1) {
		secondsSinceSpawn = 0;
		spawnChar();
	}
	for (auto it : chars) {
		it->update(clockInfo);
	}
	orxKEYBOARD_KEY key = orxKeyboard_ReadKey();
	if (key != orxKEYBOARD_KEY_NONE) {
		orxFLOAT dZ = 0;
		switch (key) {
		case orxKEYBOARD_KEY_SPACE:
			dZ = -0.1;
			break;
		default:
			dZ = 0.1;
			break;
		}
		camPos.fZ += dZ;
		orxCamera_SetPosition(camera, &camPos);
		orxKeyboard_ClearBuffer();
	}
}

orxSTATUS orxFASTCALL StandAlone::EventHandler(const orxEVENT* currentEvent) {
	return orxSTATUS_SUCCESS;
}
