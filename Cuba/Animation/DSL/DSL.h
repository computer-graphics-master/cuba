#ifndef __CUBA_DSL_H
#define __CUBA_DSL_H

#include <cmath>
#include <functional>
#include <memory>
#include <vector>

#include "./InterpolatingAnimationBuilder.h"
#include "./SequentialAnimationBuilder.h"
#include "./SimultaneousAnimationBuilder.h"
#include "../Composite/RepeatingAnimator.h"
#include "../Composite/ForeverAnimator.h"
#include "../../Parameter/AlternatingParameterSource.h"
#include "../../Parameter/CubicBezierParameterSource.h"
#include "../../Parameter/IdentityParameterSource.h"
#include "../../Parameter/ParameterSource.h"


namespace cuba::Animation::DSL {


using namespace cuba::Animation::Composite;
using namespace cuba::Parameter;


std::unique_ptr<AlternatingParameterSource> alternating(std::shared_ptr<ParameterSource> parameterSource) {
	return std::unique_ptr<AlternatingParameterSource>(new AlternatingParameterSource(parameterSource));
}

std::unique_ptr<IdentityParameterSource> identity() {
	return std::unique_ptr<IdentityParameterSource>(new IdentityParameterSource());
}

std::unique_ptr<IdentityParameterSource> linear() {
	return std::unique_ptr<IdentityParameterSource>(new IdentityParameterSource());
}

std::unique_ptr<CubicBezierParameterSource> cubicBezier(const double x1, const double y1, const double x2, const double y2) {
	return std::unique_ptr<CubicBezierParameterSource>(new CubicBezierParameterSource(x1, y1, x2, y2));
}


template<typename T>
InterpolatingAnimationBuilder<T> interpolatingBetween(T left, T right) {
	return InterpolatingAnimationBuilder<T>(left, right);
}

SequentialAnimationBuilder sequenceStartingWith(std::unique_ptr<FiniteAnimator> animator) {
	return SequentialAnimationBuilder(std::move(animator));
}

SimultaneousAnimationBuilder simultaneously(std::unique_ptr<FiniteAnimator> animator) {
	return SimultaneousAnimationBuilder(std::move(animator));
}


std::unique_ptr<RepeatingAnimator> repeat(std::unique_ptr<FiniteAnimator> baseAnimator, const int count) {
	return std::unique_ptr<RepeatingAnimator>(new RepeatingAnimator(std::move(baseAnimator), count));
}

std::unique_ptr<ForeverAnimator> forever(std::unique_ptr<FiniteAnimator> baseAnimator) {
	return std::unique_ptr<ForeverAnimator>(new ForeverAnimator(std::move(baseAnimator)));
}


int seconds(float s) {
	return (int)(s * 1000.f);
}


}

#endif
