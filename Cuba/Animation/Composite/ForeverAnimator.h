#ifndef __CUBA_FOREVER_ANIMATOR_H
#define __CUBA_FOREVER_ANIMATOR_H

#include <functional>
#include <memory>

#include "../Primitive/Animator.h"
#include "../Primitive/FiniteAnimator.h"


namespace cuba::Animation::Composite {


using namespace cuba::Animation::Primitive;


class ForeverAnimator : public Animator {
public:
	ForeverAnimator(std::unique_ptr<FiniteAnimator> animator) :
		animator(std::move(animator))
	{}

	virtual void update(const int delta) override {
		animator->update(delta);

		if (animator->isOver()) {
			animator->resetProgress();
		}
	}

	virtual bool isOver() const override {
		return false;
	}

private:
	std::unique_ptr<FiniteAnimator> animator;
};


}

#endif
