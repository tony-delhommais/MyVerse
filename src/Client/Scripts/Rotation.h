//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_ROTATION_H
#define MYVERSE_ROTATION_H

#include "Core/Common/Application.h"

using namespace Core;

class Rotation : public Script
{
public:
	void Update(float p_deltaTime) override;

	void SetIndice(float p_indice);

private:
	static bool s_isRegistered;

	float m_indice = 1.0f;
};

#endif // MYVERSE_ROTATION_H
