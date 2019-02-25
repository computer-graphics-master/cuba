#ifndef __CUBA_ANIMATOR_H
#define __CUBA_ANIMATOR_H

namespace cuba::Animation::Primitive {


class Animator {
public:
	virtual ~Animator() = default;

	virtual void update(const int delta) = 0;

	virtual bool isOver() const = 0;
};


}

#endif
