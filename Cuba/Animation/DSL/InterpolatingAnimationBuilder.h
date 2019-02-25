#ifndef __CUBA_INTERPOLATING_ANIMATION_BUILDER_H
#define __CUBA_INTERPOLATING_ANIMATION_BUILDER_H

#include <memory>

#include "../Composite/CallbackInterpolatingAnimator.h"
#include "../Primitive/InterpolatingAnimator.h"
#include "../../Parameter/ParameterSource.h"


namespace cuba::Animation::DSL {


using namespace cuba::Animation::Composite;
using namespace cuba::Animation::Primitive;
using namespace cuba::Parameter;


template<typename T>
class InterpolatingAnimationBuilder {
public:
	InterpolatingAnimationBuilder(T left, T right): left(left), right(right)
	{}

	InterpolatingAnimationBuilder &parameterizedBy(std::shared_ptr<ParameterSource> parameterSource) {
		this->parameterSource = parameterSource;

		return *this;
	}

	InterpolatingAnimationBuilder &withMotion(std::shared_ptr<ParameterSource> parameterSource) {
		this->parameterSource = parameterSource;

		return *this;
	}

	InterpolatingAnimationBuilder &forDuration(const int duration) {
		this->duration = duration;

		return *this;
	}

	InterpolatingAnimationBuilder &calling(std::function<void(T)> callback) {
		this->callback = callback;

		return *this;
	}

	InterpolatingAnimationBuilder &property(std::function<void(T)> callback) {
		this->callback = callback;

		return *this;
	}

	std::unique_ptr<CallbackInterpolatingAnimator<T>> build() {
		std::unique_ptr<InterpolatingAnimator<T>> baseAnimator(new InterpolatingAnimator<T>(
			duration, parameterSource, left, right
			));

		return std::unique_ptr<CallbackInterpolatingAnimator<T>>(new CallbackInterpolatingAnimator<T>(
			callback, std::move(baseAnimator)
			));
	}

private:
	std::function<void(T)> callback;

	std::shared_ptr<ParameterSource> parameterSource;

	int duration;

	T left;

	T right;
};


}

#endif
