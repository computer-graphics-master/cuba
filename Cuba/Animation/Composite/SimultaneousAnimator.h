#ifndef __CUBA_SIMULTANEOUS_ANIMATOR_H
#define __CUBA_SIMULTANEOUS_ANIMATOR_H

#include <memory>
#include <vector>

#include "../Primitive/FiniteAnimator.h"


namespace cuba::Animation::Composite {


using namespace cuba::Animation::Primitive;


class SimultaneousAnimator : public FiniteAnimator {
public:
	SimultaneousAnimator(std::vector<std::unique_ptr<FiniteAnimator>> animators, const int duration) :
		FiniteAnimator(duration), animators(std::move(animators))
	{}
	
	virtual void resetProgress() override {
		FiniteAnimator::resetProgress();

		for (auto& animator : animators) {
			animator->resetProgress();
		}
	}

protected:
    virtual void innerUpdate(const int delta) override {
		for (auto &animator : animators) {
			animator->update(delta);
		}
	}

private:
	std::vector<std::unique_ptr<FiniteAnimator>> animators;
};


}

#endif
