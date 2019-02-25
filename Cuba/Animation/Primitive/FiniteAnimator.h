#ifndef __CUBA_FINITE_ANIMATOR_H
#define __CUBA_FINITE_ANIMATOR_H

#include "./Animator.h"


namespace cuba::Animation::Primitive {


class FiniteAnimator : public Animator {
public:
	FiniteAnimator(const int duration) : Animator(), progress(0), duration(duration)
	{}

	virtual void update(const int delta) override {
		if (!isOver()) {
			progress += delta;

			innerUpdate(delta);
		}
	}

	virtual bool isOver() const override {
		return progress >= duration;
	}

	int getProgress() const {
		return progress;
	}

	int getDuration() const {
		return duration;
	}

	virtual void resetProgress() {
		progress = 0;
	}

protected:
	virtual void innerUpdate(const int delta) {}

private:
	int progress;

	int duration;
};


}

#endif
