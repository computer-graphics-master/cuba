#ifndef __CUBA_SEQUENTIAL_ANIMATOR_H
#define __CUBA_SEQUENTIAL_ANIMATOR_H

#include <memory>
#include <vector>

#include "../Primitive/FiniteAnimator.h"


namespace cuba::Animation::Composite {


using namespace cuba::Animation::Primitive;


class SequentialAnimator : public FiniteAnimator {
public:
    SequentialAnimator(std::vector<std::unique_ptr<FiniteAnimator>> animators, const int duration) :
		FiniteAnimator(duration), animators(std::move(animators)), currentAnimator(nullptr)
	{}

	virtual void resetProgress() override {
		FiniteAnimator::resetProgress();

		for (auto& animator : animators) {
			animator->resetProgress();
		}
	}

protected:
    virtual void innerUpdate(const int delta) override {
        checkCurrentAnimator();

        currentAnimator->update(delta);
	}

private:
	FiniteAnimator *currentAnimator;

	std::vector<std::unique_ptr<FiniteAnimator>> animators;

	void checkCurrentAnimator() {
		int animatorActivationProgress = 0;
		for (auto& animator : animators) {
			if (getProgress() >= animatorActivationProgress) {
				currentAnimator = animator.get();
			}

			animatorActivationProgress += animator->getDuration();
		}
	}
};


}

#endif
