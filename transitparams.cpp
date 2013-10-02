#include "transit.h"

#include <boost/math/constants/constants.hpp>
#include <cmath>

namespace Transit {

    const double DecToRad = boost::math::constants::two_pi<double>() / 180;
    const double RadToDeg = 180 / boost::math::constants::pi<double>();

    void TransitParams::updateRelativeParams()
    {
        // Update relative parameters
        r_planetRadius = m_planetRadius / m_planetOrbit;
        r_starRadius = m_starRadius / m_planetOrbit;
        r_temperature = pow(m_planetTemperature / m_starTemperature, 4);

        // Inclination limits of partial transit
        r_i1 = acos(r_starRadius + r_planetRadius);
        r_i2 = acos(r_starRadius - r_planetRadius);
        r_i3 = acos(r_planetRadius); // Inclination limit of total transit
    }

    double TransitParams::planetOrbit() const
    {
        return m_planetOrbit;
    }

    void TransitParams::planetOrbit(double s_planetOrbit)
    {
        m_planetOrbit = s_planetOrbit;
    }

    void TransitParams::planetRadius(double s_planetRadius)
    {
        m_planetRadius = s_planetRadius;
    }

    double TransitParams::planetRadius() const
    {
        return m_planetRadius;
    }

    void TransitParams::starRadius(double s_starRadius)
    {
        m_starRadius = s_starRadius;
    }

    double TransitParams::starRadius() const
    {
        return m_starRadius;
    }

    void TransitParams::planetTemperature(double s_planetTemperature)
    {
        m_planetTemperature = s_planetTemperature;
    }

    double TransitParams::planetTemperature() const
    {
        return m_planetTemperature;
    }

    void TransitParams::starTemperature(double s_starTemperature)
    {
        m_starTemperature = s_starTemperature;
    }

    double TransitParams::starTemperature() const
    {
        return m_starTemperature;
    }

    void TransitParams::inclination(double s_inclination)
    {
        m_inclination = s_inclination * DecToRad;
    }

    double TransitParams::inclination() const
    {
        return m_inclination * RadToDeg;
    }

    void TransitParams::darkeningLaw(DarkeningLaw s_darkeningLaw)
    {
        m_darkeningLaw = s_darkeningLaw;
    }

    DarkeningLaw TransitParams::darkeningLaw() const
    {
        return m_darkeningLaw;
    }

    void TransitParams::darkeningCoeff1(double s_darkeningCoeff1)
    {
        m_darkeningCoeff1 = s_darkeningCoeff1;
    }

    double TransitParams::darkeningCoeff1() const
    {
        return m_darkeningCoeff1;
    }

    void TransitParams::darkeningCoeff2(double s_darkeningCoeff2)
    {
        m_darkeningCoeff2 = s_darkeningCoeff2;
    }

    double TransitParams::darkeningCoeff2() const
    {
        return m_darkeningCoeff2;
    }

}
