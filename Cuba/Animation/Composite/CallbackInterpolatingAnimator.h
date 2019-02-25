#ifndef __CUBA_CALLBACK_INTERPOLATING_ANIMATOR_H
#define __CUBA_CALLBACK_INTERPOLATING_ANIMATOR_H

#include <functional>
#include <memory>

#include "../Primitive/FiniteAnimator.h"
#include "../Primitive/InterpolatingAnimator.h"


namespace cuba::Animation::Composite {


using namespace cuba::Animation::Primitive;


template<typename T>
class CallbackInterpolatingAnimator : public FiniteAnimator {
public:
	CallbackInterpolatingAnimator(std::function<void(T)> callback, std::unique_ptr<InterpolatingAnimator<T>> animator) :
		FiniteAnimator(animator->getDuration()), callback(callback), animator(std::move(animator))
	{}

	virtual void resetProgress() {
		FiniteAnimator::resetProgress();

		animator->resetProgress();
	}

protected:
    virtual void innerUpdate(const int delta) override {
        animator->update(delta);

        callback(animator->getCurrentValue());
	}

private:
	std::function<void(T)> callback;

	std::unique_ptr<InterpolatingAnimator<T>> animator;
};


}

#endif
