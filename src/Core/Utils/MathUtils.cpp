//
// Created by Tony on 29/06/2022.
//

#include "Core/Utils/MathUtils.h"

namespace Core
{

	namespace Math
	{

		float Clamp(const float min, const float max, const float f)
		{
			if (f < min) return min;
			if (f > max) return max;

			return f;
		}

		double Clamp(const double min, const double max, const double f)
		{
			if (f < min) return min;
			if (f > max) return max;

			return f;
		}

		float Lerp(const float a, const float b, const float f)
		{
			float n_f = Clamp(0.0f, 1.0f, f);
			return (a * (1.0f - n_f)) + (b * n_f);
		}

		double Lerp(const double a, const double b, const double f)
		{
			double n_f = Clamp(0.0, 1.0, f);
			return (a * (1.0 - n_f)) + (b * n_f);
		}

		glm::vec3 Lerp(const glm::vec3& a, const glm::vec3& b, const float f)
		{
			return glm::vec3(Lerp(a.x, b.x, f), Lerp(a.y, b.y, f), Lerp(a.z, b.z, f));
		}

	} // Math

} // Core
