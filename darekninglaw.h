#ifndef DAREKNINGLAW_H
#define DAREKNINGLAW_H

namespace Transit {

    /**
     * @brief The DarkeningLaw enumerator is provided for simplification of choosing a predefined Limb Darkening law functions
     * @author Itay Grudev
     * @version 1.0.0
     * @see Transit
     * @since 1.0.0
     */
    enum DarkeningLaw {
        Linear = 0x00,
        Quadratic = 0x02,
        SquareRoot = 0x04,
        Logarithmic = 0x08
    };

}

#endif // DAREKNINGLAW_H
