#ifndef __CUBA_SIMULTANEOUS_ANIMATION_BUILDER_H
#define __CUBA_SIMULTANEOUS_ANIMATION_BUILDER_H

#include <memory>
#include <vector>

#include "../Composite/SimultaneousAnimator.h"
#include "../Primitive/FiniteAnimator.h"

namespace cuba::Animation::DSL {


using namespace cuba::Animation::Composite;
using namespace cuba::Animation::Primitive;


class SimultaneousAnimationBuilder {
public:
	SimultaneousAnimationBuilder(std::unique_ptr<FiniteAnimator> animator) {
        animators.push_back(std::move(animator));
    }

	SimultaneousAnimationBuilder &togetherWith(std::unique_ptr<FiniteAnimator> animator) {
		animators.push_back(std::move(animator));

		return *this;
	}

	std::unique_ptr<SimultaneousAnimator> build() {
		int maxDuration = animators[0]->getDuration();
		for (const auto& animator : animators) {
			if (animator->getDuration() > maxDuration) {
				maxDuration = animator->getDuration();
			}
		}
		
		return std::unique_ptr<SimultaneousAnimator>(new SimultaneousAnimator(std::move(animators), maxDuration));
	}

private:
	std::vector<std::unique_ptr<FiniteAnimator>> animators;
};


}

#endif
