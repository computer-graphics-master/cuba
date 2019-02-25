#ifndef __CUBA_SEQUENTIAL_ANIMATION_BUILDER_H
#define __CUBA_SEQUENTIAL_ANIMATION_BUILDER_H

#include <memory>
#include <vector>

#include "../Composite/SequentialAnimator.h"
#include "../Primitive/FiniteAnimator.h"


namespace cuba::Animation::DSL {


using namespace cuba::Animation::Composite;
using namespace cuba::Animation::Primitive;


class SequentialAnimationBuilder {
public:
    SequentialAnimationBuilder(std::unique_ptr<FiniteAnimator> animator) {
        animators.push_back(std::move(animator));
    }

	SequentialAnimationBuilder &then(std::unique_ptr<FiniteAnimator> animator) {
		animators.push_back(std::move(animator));

		return *this;
	}

	std::unique_ptr<SequentialAnimator> build() {
		int totalDuration = 0;
		for (const auto& animator : animators) {
			totalDuration += animator->getDuration();
		}
		
		return std::unique_ptr<SequentialAnimator>(new SequentialAnimator(std::move(animators), totalDuration));
	}

private:
	std::vector<std::unique_ptr<FiniteAnimator>> animators;
};


}

#endif
