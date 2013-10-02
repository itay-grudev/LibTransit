#include "transitprivate.h"
#include <boost/math/constants/constants.hpp>
#include <cmath>

#define PI 3.141592653589793
#define PI2 6.283185307179586 // Added for faster and percise calculations
#define MACHEPS 1.11e-16

namespace Transit {

    const double pi = boost::math::constants::pi<double>();
    const double pi2 = pi * 2;
    const double epsilon = 1.11e-16;

    TransitPrivate::TransitPrivate(Transit * s_parent)
        : parent(s_parent), properties()
    {
    }

    double TransitPrivate::getLimbDarkeningLaw(TransitParams * params, PhaseProperties * props)
    {
        switch(params->darkeningLaw())
        {
            default:
            case DarkeningLaw::Linear:
                return 1 - params->m_darkeningCoeff1 + params->m_darkeningCoeff1 * sqrt(1 - pow(props->q / params->r_starRadius, 2) );
            case DarkeningLaw::Quadratic:
                return 1 - params->m_darkeningCoeff1 * (1 - sqrt(1 - pow(props->q / params->r_starRadius, 2) )) - params->m_darkeningCoeff2 * pow(1 - sqrt(1 - pow(props->q / params->r_starRadius, 2)), 2);
            case DarkeningLaw::SquareRoot:
                return 1 - params->m_darkeningCoeff1 * (1 - sqrt(1 - pow(props->q / params->r_starRadius, 2) )) - params->m_darkeningCoeff2 * pow(1 - (1 - pow(props->q / params->r_starRadius, 2)), (1.0 / 4.0));
            case DarkeningLaw::Logarithmic:
                return 1 - params->m_darkeningCoeff1 * (1 - sqrt(1 - pow(props->q / params->r_starRadius, 2))) - params->m_darkeningCoeff2 * sqrt(1 - pow(props->q / params->r_starRadius, 2)) * log(sqrt(1 - pow(props->q / params->r_starRadius, 2)));
        }
    }

    double TransitPrivate::getLuminosityDarkeningLaw(TransitParams * params, PhaseProperties * props)
    {
        switch(params->m_darkeningLaw)
        {
            default:
            case DarkeningLaw::Linear:
                return 1 - params->m_darkeningCoeff1 / 3;
            case DarkeningLaw::Quadratic:
                return 1 - params->m_darkeningCoeff1 / 3 - params->m_darkeningCoeff2 / 6;
            case DarkeningLaw::SquareRoot:
                return 1 - params->m_darkeningCoeff1 / 3 - params->m_darkeningCoeff2 / 5;
            case DarkeningLaw::Logarithmic:
                return 1 - params->m_darkeningCoeff1 / 3 - 2 * params->m_darkeningCoeff2 / 9;
        }
    }

    double TransitPrivate::c(double & q, double & b) const
    {
        return q * q + b * b - pow(parent->params->r_planetRadius, 2);
    }

	double TransitPrivate::quad(std::function <double (TransitParams*, PhaseProperties *)> function, double qmin, double qmax, double dq)
    {
        if(qmax - qmin < MACHEPS)return 0;
        double sum = 0;
        for(double q = qmin; q <= qmax; q += dq)
        {
            properties.q = q;
            properties.q2 = q * q;
            properties.c2 = properties.q2 + properties.b2 - parent->params->r_planetRadius;
            properties.sq4b2q2_c4 = sqrt(4 * properties.b2 + properties.q2 + pow(properties.c2, 2));
            properties.x1 = properties.c2 * properties.x0 + properties.y0 * properties.sq4b2q2_c4;
            properties.y1 = properties.c2 * properties.y0 - properties.x0 * properties.sq4b2q2_c4;
            properties.x2 = properties.c2 * properties.x0 - properties.y0 * properties.sq4b2q2_c4;

			sum += function(parent->params, &properties) * dq;
        }
        return sum;
    }

	double TransitPrivate::j1(TransitParams * params, PhaseProperties * props)
    {
        return getLimbDarkeningLaw(props->q) * props->q * ( acos(props->x2 / props->q) - acos(props->x1 / props->q) );
    }

    double TransitPrivate::j2(double q, double b, double x0, double y0)
    {
        return getLimbDarkeningLaw(q) * q * (acos((x0 * (b * b + q * q - pow(parent->params->r_planetRadius, 2)) - y0 * sqrt(4 * b * b * q * q - pow(b * b + q * q - pow(parent->params->r_planetRadius, 2), 2))) / (2 * b * b * q)) + acos((x0 * (b * b + q * q - pow(parent->params->r_planetRadius, 2)) + y0 * sqrt(4 * b * b * q * q - pow(b * b + q * q - pow(parent->params->r_planetRadius, 2), 2))) / (2 * b * b * q)));
    }

    double TransitPrivate::j3(double q, double b, double x0, double y0)
    {
        return 0;
    //	return getLimbDarkeningLaw(q) * q * ((2 * pi) - acos(abs((x0 * (b ** 2 + q ** 2 - rp ** 2) + y0 * sqrt(4 * b ** 2 * q ** 2 - (b ** 2 + q ** 2 - rp ** 2) ** 2)) / (2 * b ** 2)) / q) + acos(abs((x0 * (b ** 2 + q ** 2 - rp ** 2) - y0 * sqrt(4 * b ** 2 * q ** 2 - (b ** 2 + q ** 2 - rp ** 2) ** 2)) / (2 * b ** 2)) / q));
    }

    double TransitPrivate::j4(double q, double b, double x0, double y0)
    {
        return 0;
    //	return getLimbDarkeningLaw(q) * q * (pi + acos(abs((x0 * (b ** 2 + q ** 2 - rp ** 2) + y0 * sqrt(4 * b ** 2 * q ** 2 - (b ** 2 + q ** 2 - rp ** 2) ** 2)) / (2 * b ** 2)) / q) + acos(abs((x0 * (b ** 2 + q ** 2 - rp ** 2) - y0 * sqrt(4 * b ** 2 * q ** 2 - (b ** 2 + q ** 2 - rp ** 2) ** 2)) / (2 * b ** 2)) / q));
    }

    double TransitPrivate::j5(double q, double b, double x0, double y0)
    {
        return 0;
    }

    double TransitPrivate::j6(double q, double b, double x0, double y0)
    {
        return 0;
    }

}
