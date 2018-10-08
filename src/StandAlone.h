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

#ifndef StandAlone_h
#define StandAlone_h

#include <list>
#include <ctime>
#include <cmath>

#include "orx.h"
#include "Character.h"

class StandAlone {
public:
	static StandAlone* Instance();

	static orxSTATUS orxFASTCALL Init();
	static orxSTATUS orxFASTCALL Run();

	static void orxFASTCALL Exit();

	static void orxFASTCALL Update(const orxCLOCK_INFO*, void*);
protected:
	StandAlone();
	StandAlone(const StandAlone&);
	StandAlone& operator= (const StandAlone&);
private:
	static StandAlone* m_Instance;

	// camera state
	static orxCAMERA* camera;
	static orxFLOAT zoom;

	// characters to destroy
	static std::list<Character*> chars;
	static orxFLOAT secondsSinceSpawn;

	/**
	 * Spawns a new random character at a random location
	 */
	static void spawnChar();

	// player state
	static int HP, score;

	/**
	 * Alters the player's score by the given delta
	 * @param delta Amount by which to change score
	 */
	static void changeScore(int delta);

	// UI elements
	static orxOBJECT *gameOver, *scoreLabel;
};

#endif
