#ifndef __CUBA_IDENTITY_PARAMETER_SOURCE_H
#define __CUBA_IDENTITY_PARAMETER_SOURCE_H

#include "./ParameterSource.h"

namespace cuba::Parameter {


class IdentityParameterSource : public ParameterSource {
public:
	virtual double map(const double t) const override {
		return t;
	}
};


}

#endif
