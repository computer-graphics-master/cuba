#ifndef __CUBA_ALTERNATING_PARAMETER_SOURCE_H
#define __CUBA_ALTERNATING_PARAMETER_SOURCE_H

#include <memory>

#include "./ParameterSource.h"


namespace cuba::Parameter {


class AlternatingParameterSource : public ParameterSource {
public:
	AlternatingParameterSource(std::shared_ptr<ParameterSource> parameterSource):
		parameterSource(parameterSource)
	{}

	virtual double map(const double t) const override {
		if (t < 0.5) {
			return parameterSource->map(2.0 * t);
		} else {
			return parameterSource->map(2.0 * (1 - t));
		}
	}

private:
	std::shared_ptr<ParameterSource> parameterSource;
};


}

#endif
