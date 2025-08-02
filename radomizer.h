/**
 * @file randomizer.h
 * @brief A small C library for audio DSP: basic pseudo-random number generator.
 *
 * Project: Quamplex DSP Tools (A small C library of tools for audio DSP processing)
 * Website: https://quamplex.com
 *
 * Copyright (C) 2025 Iurie Nistor
 *
 * This file is part of Quamplex DSP Tools.
 *
 * Quamplex DSP Tools is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef QX_RANDOMIZER_H
#define QX_RANDOMIZER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

        /**
         * @brief Basic pseudo-random number generator configuration and state.
         *
         * This randomizer is designed with audio DSP in mind:
         * - Uses a lightweight PRNG for efficiency in real-time audio processing.
         * - Provides sufficient randomness quality for typical audio purposes,
         *   prioritizing speed and repeatability over cryptographic-grade randomness.
         * - Given the same seed, the generated pattern is reproducible.
         * - No global state; multiple instances can coexist without interference.
         *
         * @note Not thread-safe.
         */

        struct qx_randomizer;

        /**
         * @brief Initialize the randomizer parameters.
         *
         * Sets the minimum and maximum values for the output range, and the resolution
         * (step size) for generated random values. The seed is initialized to a default
         * value.
         *
         * @param[in,out] rand Pointer to the randomizer instance to initialize.
         * @param[in] min The minimum value (inclusive) of the random range.
         * @param[in] max The maximum value (inclusive) of the random range.
         * @param[in] resolution The step size for quantizing output values. Must be > 0.
         *                       If zero or negative, defaults to 1.0f.
         */
        void qx_randomizer_init(qx_randomizer *rand, float min, float max, float resolution);

        /**
         * @brief Set or reset the RNG seed.
         *
         * @param[in,out] rand Pointer to the randomizer instance.
         * @param[in] seed The seed value to initialize the random sequence.
         */
        void qx_randomizer_set_seed(qx_randomizer *rand, uint32_t seed);

        /**
         * @brief Generate a random float value in [min, max] stepped by resolution.
         *
         * @param[in,out] rand Pointer to the randomizer instance.
         * @return A random float within the configured range, quantized by resolution.
         */
        float qx_randomizer_get_float(qx_randomizer *rand);

#ifdef __cplusplus
}
#endif

#endif // QX_RANDOMIZER_H
