//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_MATH_UTILS_H
#define MYVERSE_MATH_UTILS_H

#define GLM_FORCE_SWIZZLE

#include "glm.hpp"
#include "ext.hpp"
#include "gtx/matrix_decompose.hpp"
#include "gtx/quaternion.hpp"

namespace Client
{

	namespace Math
	{

		float Clamp(const float min, const float max, const float f);
		double Clamp(const double min, const double max, const double f);

		float Lerp(const float a, const float b, const float f);
		double Lerp(const double a, const double b, const double f);
		glm::vec3 Lerp(const glm::vec3& a, const glm::vec3& b, const float f);

		void DecomposeMatrix(glm::mat4& p_matrix, glm::vec3& p_position, glm::quat& p_rotation, glm::vec3& p_scale);
		void ComposeMatrix(glm::mat4& p_matrix, glm::vec3& p_position, glm::quat& p_rotation, glm::vec3& p_scale);

	} // Math

} // Client

#endif // MYVERSE_MATH_UTILS_H
