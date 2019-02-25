#ifndef __CUBA_CUBIC_BEZIER_PARAMETER_SOURCE_H
#define __CUBA_CUBIC_BEZIER_PARAMETER_SOURCE_H

#include "./ParameterSource.h"

#include <cmath>
#include <iostream>


namespace cuba::Parameter {


class CubicBezierParameterSource : public ParameterSource {
public:
	CubicBezierParameterSource(const double x1, const double y1, const double x2, const double y2) :
		x1(x1), y1(y1), x2(x2), y2(y2)
	{}

	virtual double map(const double t) const override {
		const double xWeAreLookingFor = t;
		double calculatedX;
		double left = 0.0, right = 1.0;
		double currentParameter;

		do {
			currentParameter = (right + left) / 2.0;
			calculatedX = bezier(currentParameter, x1, x2);

			if (calculatedX < xWeAreLookingFor) {
				left = currentParameter + EPSILON;
			} else {
				right = currentParameter - EPSILON;
			}

		} while (std::abs(xWeAreLookingFor - calculatedX) >= EPSILON);

		const double y = bezier(currentParameter, y1, y2);

		return y;
	}

private:
	static constexpr double EPSILON = 0.001;

	const double x1, y1, x2, y2;

	double bezier(const double t, const double p1, const double p2) const {
		const double q = 3 * (1 - t) * t;

		const double coeff1 = q * (1 - t);
		const double coeff2 = q * t;
		const double coeff3 = t * t * t;

		return coeff1 * p1 + coeff2 * p2 + coeff3;
	}
};

}

#endif
