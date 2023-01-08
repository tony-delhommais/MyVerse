//
// Created by Tony on 17/08/2022.
//

#ifndef MYVERSE_PLAYER_H
#define MYVERSE_PLAYER_H

#include "Utils.h"

#include "Entity.h"

namespace Client
{

	class Player : public Entity
	{
	public:
		Player() = default;
		~Player() = default;

	private:
		static bool s_isPlayerMakerRegistered;
	};

} // Client

#endif // MYVERSE_PLAYER_H
