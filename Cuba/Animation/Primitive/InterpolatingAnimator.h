#ifndef __CUBA_INTERPOLATING_ANIMATOR_H
#define __CUBA_INTERPOLATING_ANIMATOR_H

#include <memory>

#include "./FiniteAnimator.h"
#include "../../Parameter/ParameterSource.h"


namespace cuba::Animation::Primitive {


using namespace cuba::Parameter;


template<typename T>
class InterpolatingAnimator : public FiniteAnimator {
public:
	InterpolatingAnimator(const int duration, std::shared_ptr<ParameterSource> parameterSource,
						  const T left, const T right) :
		FiniteAnimator(duration), parameterSource(parameterSource), left(left), right(right)
	{}

	virtual T getCurrentValue() {
		const double t = ((double)getProgress()) / ((double)getDuration());

		return calculateValue(t);
	}

private:
	std::shared_ptr<ParameterSource> parameterSource;

	T left;

	T right;

	T calculateValue(const double t) {
		const double parameter = parameterSource->map(t);

		return (T)((1.0 - parameter) * left + parameter * right);
	}
};


}

#endif
