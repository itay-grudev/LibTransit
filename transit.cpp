#include "transit.h"
#include "transitprivate.h"
#include <cmath>

#include <boost/math/constants/constants.hpp>

namespace Transit {

    const double pi = boost::math::constants::pi<double>();
    const double two_pi = boost::math::constants::two_pi<double>();
	const double half_pi = pi / 2;
    const double epsilon = 1.11e-16;

    Transit::Transit(TransitParams * s_params)
        : params(s_params), pimpl(new TransitPrivate(this))
    {

    }

    double Transit::calculatePhase(double phase, double isolines)
    {
        // Calculate phase parameters
        pimpl->properties.x0 = sin(two_pi * phase);
        pimpl->properties.y0 = cos(params->inclination()) * cos(two_pi * phase);
        pimpl->properties.b = pimpl->properties.x0 * pimpl->properties.x0 + pimpl->properties.y0 * pimpl->properties.y0;

        pimpl->properties.x0 = sin(two_pi * phase);
        pimpl->properties.y0 = cos(params->m_inclination) * cos(two_pi * phase);

		double result, qmin, qmax, dq;

        // Case A: Partial transit
        if( params->r_i1 <= params->m_inclination and params->m_inclination <= params->r_i2)
        {
            // Check if the given phase is in the outer contact phase range
            pimpl->properties.f1 = 1 / two_pi * asin( sqrt( pow(params->r_starRadius + params->r_planetRadius, 2) - cos( pow(params->m_inclination, 2) ) ) / sin(params->m_inclination) );
            if(0 <= phase and phase <= pimpl->properties.f1)
            {
                double sqrtExpression = sqrt( pow(params->r_planetRadius, 2) - pow(pimpl->properties.y0, 2) );
                // Case A.1
                if(pimpl->properties.x0 - sqrtExpression >= params->r_planetRadius)
				{
                    pimpl->properties.b2 = pow(pimpl->properties.x0, 2) + pow(pimpl->properties.y0, 2);
                    pimpl-> properties.b = sqrt(pimpl->properties.b);
                    qmin = pimpl->properties.b - params->r_planetRadius;
                    qmax = params->r_starRadius;
                    result = pimpl->quad(TransitPrivate::j1, qmin, qmax, (qmax - qmin) / isolines);
                }
                // Case A.2
                if(pimpl->properties.x0 - sqrtExpression <= params->r_planetRadius and params->r_planetRadius <= pimpl->properties.x0 + sqrtExpression)
                {

                }
                // Case A.3
				if(pimpl->properties.x0 - sqrtExpression <= params->r_planetRadius)
				{

                }
            }

            return 1;
        }

        // Case B: Total transit out of the stellar center
        if(params->r_i2 <= params->m_inclination and params->m_inclination <= params->r_i3)
        {

            return 0;
        }

        // Case C: Total transit through the stellar center
        if(params->r_i3 <= params->m_inclination and params->m_inclination <= half_pi )
        {

            return 0;
        }

		return 1;
    }

}
