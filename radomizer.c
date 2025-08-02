/**
 * randomizer.c
 * Implementation of a basic pseudo-random number generator for audio DSP.
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

#include "randomizer.h"

#define LCG_A 1664525u
#define LCG_C 1013904223u
#define LCG_M 0xFFFFFFFFu  /**< Modulus for 32-bit LCG */

/** Default fixed seed for reproducibility */
static const uint32_t qx_randomizer_default_seed = 0x12345678u;

/**
 * Internal structure for the randomizer state.
 */
struct qx_randomizer {
        float min;        /**< Minimum value (inclusive) */
        float max;        /**< Maximum value (inclusive) */
        float resolution; /**< Step size for quantizing output */
        uint32_t seed;    /**< Internal seed/state for PRNG */
};

/**
 * @brief Advance the seed using a simple Linear Congruential Generator (LCG).
 *
 * @param current_seed Current seed/state
 * @return Next seed/state
 */
static uint32_t qx_randomizer_next_seed(uint32_t current_seed)
{
        return (LCG_A * current_seed + LCG_C) & LCG_M;
}

void qx_randomizer_init(qx_randomizer *rand, float min, float max, float resolution)
{
        if (!rand)
                return;

        rand->min = min;
        rand->max = max;
        rand->resolution = (resolution <= 0.0f) ? 1.0f : resolution;
        rand->seed = qx_randomizer_default_seed;
}

void qx_randomizer_set_seed(qx_randomizer *rand, uint32_t seed)
{
        if (!rand)
                return;

        rand->seed = seed;
}

float qx_randomizer_get_float(qx_randomizer *rand)
{
        if (!rand)
                return 0.0f;

        rand->seed = qx_randomizer_next_seed(rand->seed);

        float normalized = (float)(rand->seed) / (float)UINT32_MAX;

        float range = rand->max - rand->min;
        float value = rand->min + normalized * range;

        float steps = (value - rand->min) / rand->resolution;
        int steps_int = (int)(steps + 0.5f);

        float quantized_value = rand->min + steps_int * rand->resolution;

        if (quantized_value < rand->min)
                quantized_value = rand->min;
        else if (quantized_value > rand->max)
                quantized_value = rand->max;

        return quantized_value;
}
