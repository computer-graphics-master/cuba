#ifndef __CUBA_REPEATING_ANIMATOR_H
#define __CUBA_REPEATING_ANIMATOR_H

#include <functional>
#include <memory>

#include "../Primitive/FiniteAnimator.h"


namespace cuba::Animation::Composite {


using namespace cuba::Animation::Primitive;


class RepeatingAnimator : public FiniteAnimator {
public:
	RepeatingAnimator(std::unique_ptr<FiniteAnimator> baseAnimator, int count) :
		FiniteAnimator(baseAnimator->getDuration() * count), baseAnimator(std::move(baseAnimator)), count(count), elapsedCount(0)
	{}

protected:
    virtual void innerUpdate(const int delta) override {
        if (baseAnimator->isOver()) {
            ++elapsedCount;

            baseAnimator->resetProgress();
        }

        if (elapsedCount < count) {
            baseAnimator->update(delta);
        }
    }

private:
	std::unique_ptr<FiniteAnimator> baseAnimator;

	int count;

	int elapsedCount;
};


}

#endif
