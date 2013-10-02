#ifndef TRANSITPARAMS_H
#define TRANSITPARAMS_H

#include "darekninglaw.h"

namespace Transit {

/**
 * @brief The TransitParams class holds the system parameters required for later computation.
 * This was added in order for the library to support parallel computation of different phases
 * of the same planet-star system. You can pass a reference to the system's data to multiple
 * instances of the Transit class.
 * @see Transit()
 * @author Itay Grudev
 * @version 1.0.0
 * @since 1.0.0
 */
struct TransitParams {
    /**
     * @brief The radius of the planet's orbit
     * @see m_planetOrbit
     */
    double planetOrbit() const;
    /**
     * @brief Sets the planetOrbit
     * @see m_planetOrbit
     */
    void planetOrbit(double);
    /**
     * @brief The planet's radius
     * @see m_planetRadius
     */
    double planetRadius() const;
    /**
     * @brief Sets the planetRadius
     * @see m_planetRadius
     */
    void planetRadius(double);
    /**
     * @brief The star's radius
     * @see m_starRadius
     */
    double starRadius() const;
    /**
     * @brief Sets the starRadius
     * @see m_starRadius
     */
    void starRadius(double);
    /**
     * @brief The planet's temperature
     * @see m_planetTemperature
     */
    double planetTemperature() const;
    /**
     * @brief Sets the planetTemperature
     * @see m_planetTemperature
     */
    void planetTemperature(double);
    /**
     * @brief The star's temperature
     * @see m_starTemperature
     */
    double starTemperature() const;
    /**
     * @brief Sets the starTemperature
     * @see m_starTemperature
     */
    void starTemperature(double);
    /**
     * @brief Orbital inclination of the planet in degrees
     * @see m_inclination()
     */
    double inclination() const;
    /**
     * @brief Sets the planet's orbital inclination in degrees
     * @see m_inclination
     */
    void inclination(double);
    /**
     * @brief Limb darkening
     * @see m_darkeningLawlaw type
     */
    DarkeningLaw darkeningLaw() const;
    /**
     * @brief Sets the darkeningLaw
     * @see m_darkeningLaw
     */
    void darkeningLaw(DarkeningLaw);
    /**
     * @brief Limb darkening law
     * @see m_darkeningCoeff1first coefficient
     */
    double darkeningCoeff1() const;
    /**
     * @brief Sets the darkeningCoeff1
     * @see m_darkeningCoeff1
     */
    void darkeningCoeff1(double);
    /**
     * @brief Limb darkening law second coefficient
     * @note Not used with Linear
     * @see m_darkeningCoeff2limb darkening law
     */
    double darkeningCoeff2() const;
    /**
     * @brief Sets the darkeningCoeff2
     * @see m_darkeningCoeff2
     */
    void darkeningCoeff2(double);
    /**
     * @brief Calculates the relative parameters
     * Whenever any of the planet/star/planet orbit radius have changed
     * or any of the planet/star temperatures have changed this method
     * should be called in order to calculate the new relative parameters
     * used by the Transit class.
     * @note The orbital inclination is transformed to radians from
     *  degrees and the inclination limits for partial/total are calculated
     * @see Transit()
     * @see r_planetRadius;
     * @see r_starRadius;
     * @see r_temperature;
     * @since 1.0.0
     */
    void updateRelativeParams();
private:
    /**
     * @brief The radius of the planet's orbit
     */
    double m_planetOrbit;
    /**
     * @brief The planet's radius
     */
    double m_planetRadius;
    /**
     * @brief The star's radius
     */
    double m_starRadius;
    /**
     * @brief The planet's temperature
     */
    double m_planetTemperature;
    /**
     * @brief The star's temperature
     */
    double m_starTemperature;
    /**
     * @brief Orbital inclination of the planet in radians
     */
    double m_inclination;
    /**
     * @brief Limb darkening law type
     */
    DarkeningLaw m_darkeningLaw;
    /**
     * @brief Limb darkening law first coefficient
     */
    double m_darkeningCoeff1;
    /**
     * @brief Limb darkening law second coefficient
     * @note Not used with Linear limb darkening law
     */
    double m_darkeningCoeff2;
    /**
     * @brief Relative planet radius
     */
    double r_planetRadius;
    /**
     * @brief Relative star radius
     */
    double r_starRadius;
    /**
     * @brief Planet/Star temperature ratio
     * Stored to the power of four
     */
    double r_temperature;
    /**
     * @brief Inclination limit for partial transit
     */
    double r_i1;
    /**
     * @brief Inclination limit for total transit
     */
    double r_i2;
    /**
     * @brief Inclination limit for total transit thorugh the stellar center
     */
    double r_i3;

// Private properties should be accessible from the Transit and it's implementation class
friend class Transit;
friend class TransitPrivate;
};

}

#endif // TRANSITPARAMS_H
