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
orxFLOAT StandAlone::zoom;

std::list<Character*> StandAlone::chars;
orxFLOAT StandAlone::secondsSinceSpawn = 0;

int StandAlone::HP = 100;
int StandAlone::score = 0;

orxOBJECT* StandAlone::gameOver;
orxOBJECT* StandAlone::scoreLabel;
orxOBJECT* StandAlone::HPBar;
orxOBJECT* StandAlone::zoomLabel;

StandAlone* StandAlone::Instance() {
	if (m_Instance != orxNULL) {
		return m_Instance;
	}
	m_Instance = new StandAlone();
	return m_Instance;
}

StandAlone::StandAlone() {}

orxSTATUS orxFASTCALL StandAlone::Init() {
	orxMath_InitRandom((orxU32)time(0));
	orxVIEWPORT* viewport = orxViewport_CreateFromConfig("Viewport");
	camera = orxViewport_GetCamera(viewport);

	zoom = orxCamera_GetZoom(camera);

	orxCLOCK* upClock = orxClock_FindFirst(-1.0f, orxCLOCK_TYPE_CORE);
	orxClock_Register(upClock, Update, orxNULL, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_NORMAL);

	chars = std::list<Character*>();

	gameOver = orxObject_CreateFromConfig("GameOver");
	orxObject_Enable(gameOver, orxFALSE);
	orxObject_SetParent(gameOver, camera);

	scoreLabel = orxObject_CreateFromConfig("Score");
	orxObject_SetParent(scoreLabel, camera);

	orxOBJECT* hplbl = orxObject_CreateFromConfig("Health");
	orxObject_SetParent(hplbl, camera);

	HPBar = orxObject_CreateFromConfig("HPBar");
	orxObject_SetParent(HPBar, camera);

	zoomLabel = orxObject_CreateFromConfig("Zoom");
	orxObject_SetParent(zoomLabel, camera);

	orxObject_CreateFromConfig("Player");

	Character::initColors();

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

void StandAlone::changeScore(int delta) {
	score += delta;
	orxCHAR text[100];
	orxString_Print(text, "Score: %d", score);
	orxObject_SetTextString(scoreLabel, text);
}

void StandAlone::changeHP(int delta) {
	HP += delta;
	orxVECTOR scale = {(orxFLOAT)HP, 1, 1};
	orxObject_SetScale(HPBar, &scale);
}

void orxFASTCALL StandAlone::Update(const orxCLOCK_INFO* clockInfo, void* context) {
	if (HP <= 0) {
		orxKEYBOARD_KEY key = orxKeyboard_ReadKey();
		orxKeyboard_ClearBuffer();
		if (key == orxKEYBOARD_KEY_RETURN) {
			orxObject_Enable(gameOver, orxFALSE);
			changeScore(-score);
			changeHP(100 - HP);
			secondsSinceSpawn = 0;
			for (std::list<Character*>::iterator it = chars.begin(); it != chars.end();) {
				(*it)->despawn(nullptr, nullptr);
				chars.erase(it++);
			}
		} else {
			return;
		}
	}
	secondsSinceSpawn += clockInfo->fDT;
	if (secondsSinceSpawn > pow(2, zoom - 2)) {
		secondsSinceSpawn = 0;
		spawnChar();
	}
	orxKEYBOARD_KEY key = orxKeyboard_ReadKey();
	if (key != orxKEYBOARD_KEY_NONE) {
		orxFLOAT dZ = 0.1;
		if (key == orxKEYBOARD_KEY_SPACE) {
			dZ *= -1;
		}
		zoom += dZ;
		orxCamera_SetZoom(camera, zoom);
		orxCHAR text[20];
		orxString_Print(text, "Zoom: %.2fx", zoom);
		orxObject_SetTextString(zoomLabel, text);
		orxKeyboard_ClearBuffer();
	}
	for (std::list<Character*>::iterator it = chars.begin(); it != chars.end();) {
		(*it)->update(clockInfo);
		bool destroyed = key != orxKEYBOARD_KEY_NONE && (*it)->getKey() == key;
		orxVECTOR pos = (*it)->getPosition();
		bool atOrigin = orxVector_GetSize(&pos) < 25;
		if (destroyed || atOrigin) {
			if (destroyed) {
				(*it)->despawn(&HP, &score);
				changeScore(10);
				key = orxKEYBOARD_KEY_NONE;
			} else {
				(*it)->despawn(nullptr, nullptr);
				changeHP(-5);
				if (HP <= 0) {
					orxObject_Enable(gameOver, orxTRUE);
					zoom = 1;
					orxCamera_SetZoom(camera, zoom);
				}
			}
			chars.erase(it++);
		} else {
			it++;
		}
	}
}
