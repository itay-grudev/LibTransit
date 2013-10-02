#ifndef TRANSIT_H
#define TRANSIT_H

#include <vector>
#include "transitparams.h"

namespace Transit {
	/**
	 * @brief The TransitPrivate class contains the private implementation of the Transit library
	 * @author Itay Grudev
	 * @version 1.0.0
	 * @see Transit
	 * @since 1.0.0
	 */
	class TransitPrivate;

	/**
	 * @brief Provides the means of computation of phases of the transit by specifying the system properties.
	 * @author Itay Grudev
	 * @version 1.0.0
	 * @since 1.0.0
	 */
	class Transit
    {

	public:
        /**
         * @brief Constructor
         * Initializes a the class with the provided system parameters
         * @param params - pointer to a the system parameters object
         */
        Transit(TransitParams * params);
		/**
		 * @brief Calculates a given phase of the transit specified by the phase argument.
		 * Optionally by setting the second argument you cen set the precision of the phase
		 * calculation by specifying the number of stellar isolines to be calculated (integration steps).
		 * @param phase - the required phase to calculate
		 * @param isolines - number of isolines to use when integrating (Default: 1000)
		 * @return The calculated flux for the given phase
		 */
		double calculatePhase(double phase, double isolines=1000);

    protected:
        TransitParams * params;

    private:
        TransitPrivate * pimpl;

    // Private properties should be accessible from the TransitPrivate (implementation) class
    friend class TransitPrivate;
	};
}

#endif // TRANSIT_H
