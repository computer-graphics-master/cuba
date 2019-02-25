#ifndef __CUBA_PARAMETER_SOURCE_H
#define __CUBA_PARAMETER_SOURCE_H

namespace cuba::Parameter {


class ParameterSource {
public:
	virtual ~ParameterSource() = default;

	virtual double map(const double t) const = 0;
};


}

#endif
