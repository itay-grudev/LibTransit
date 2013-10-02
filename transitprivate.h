#ifndef TRANSITPRIVATE_H
#define TRANSITPRIVATE_H

#include "transit.h"
#include <functional>

namespace Transit {

    struct PhaseProperties {
        double phase;
        double x0;
        double y0;
        double q;
        double q2; // q squared
        double x1;
        double y1;
        double x2;
        double y2;
        double b;
        double b2; // b squared
        double c2; // c squared
        double sq4b2q2_c4;
        double f1;
        double f2;
    };

    typedef std::function < void(PhaseProperties &) > TransitIntegral;

    class TransitPrivate {

	private:
		Transit * parent;

    public:
        TransitPrivate(Transit*);
        PhaseProperties properties;

        /* Pre-computed parameters */
        // Inclination limits
        double i1, i2, i3;
        // Phase limits
        double f1, f2, f3, f4, f5, f6;
        // Star & Planet - Intensity and Luminosity
        double starIntensity;
        double planetIntensity;
        double starLuminosity;
        double planetLuminosity;

        // Precomputed formulas
        double toFlux;

        // Methods
        static double getLimbDarkeningLaw(TransitParams *, PhaseProperties *);
        static double getLuminosityDarkeningLaw(TransitParams *, PhaseProperties *);

        // Integrals
        double quad(std::function <double (TransitParams *, PhaseProperties *)>, double, double, double);
        static double j1(TransitParams *, PhaseProperties *);
        static double j2(const double, const double, const double, const double);
        static double j3(const double, const double, const double, const double);
        static double j4(const double, const double, const double, const double);
        static double j5(const double, const double, const double, const double);
        static double j6(const double, const double, const double, const double);
    };

}

#endif // TRANSITPRIVATE_H
