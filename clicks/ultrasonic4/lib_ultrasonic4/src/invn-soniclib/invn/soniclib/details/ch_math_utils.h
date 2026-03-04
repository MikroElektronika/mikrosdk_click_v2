/*!
 * \file ch_math_utils.h
 * \date July 20, 2017
 * \author nparikh
 * \copyright Copyright 2017 Chirp Microsystems.  All rights reserved.
 * \brief Functions for performing fixed point arithmetic.
 *        https://github.com/dmoulding/log2fix
 *        https://github.com/chmike/fpsqrt
 */

#ifndef CH_MATH_UTILS_H_
#define CH_MATH_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <math.h>
#include <stdint.h>

#define FRACT_BITS 16

#define INT2FIXED(x)   ((x) << FRACT_BITS)
#define FLOAT2FIXED(x) ((fixed_t)((x) * (1 << FRACT_BITS)))

#define FIXED2INT(x)   ((x) >> FRACT_BITS)
#define FIXED2FLOAT(x) (((float)(x)) / (1 << FRACT_BITS))

#define FIXEDDIV(x, y) ((fixed_t)(((uint64_t)(x) << FRACT_BITS) / (y)))
#define FIXEDMUL(x, y) ((fixed_t)(((x) >> (FRACT_BITS / 2)) * ((y) >> (FRACT_BITS / 2))))

#define FIXED_PI 0x3243FU

#define INV_LOG2_E_Q1DOT31 0x58b90bfcU  // Inverse log base 2 of e, Q1.31 format

#define Q31_TO_Q16_SHIFT_BITS 15  // Shift Q31 format by 15 bits to give Q16
#define Q31_TO_Q16_SHIFT_1    10  // Number of bits to shift in first step
#define Q31_TO_Q16_SHIFT_2    (Q31_TO_Q16_SHIFT_BITS - Q31_TO_Q16_SHIFT_1)
// Number of bits to shift in second step

typedef uint32_t fixed_t;

fixed_t FP_sqrt(fixed_t x);

/*!
 * \brief Find the base 2 logarithm in UQ16.16 fixed-point format
 *
 * \param x  Find the log base-2 of the provided number. This number is
 *           is UQ16.16 fixed-point format.
 *
 * \return The log base-2 of x in UQ16.16 format.
 *
 * This function is adapted from work by dmoulding with very minor changes. The
 * source for the original function, log2fix, can be found here:
 *
 * https://github.com/dmoulding/log2fix/blob/master/log2fix.c
 */
fixed_t FP_log2(fixed_t x);

/*!
 * \brief Find the natural logarithm in UQ16.16 fixed-point format
 *
 * \param x  Find the natural log of the provided number. This number is
 *           is UQ16.16 fixed-point format.
 *
 * \return The natural log of x in UQ16.16 format.
 *
 * This function is adapted from work by dmoulding with very minor changes. The
 * source for the original function, logfix, can be found here:
 *
 * https://github.com/dmoulding/log2fix/blob/master/log2fix.c
 */
fixed_t FP_log(fixed_t x);

/*!
 * \brief Compute the square root of a 32-bit integer.
 *
 * \param x  Find the square root of the provided integer.
 *
 * \return The square root of x as a 32-bit integer.
 *
 * This function is adapted from work by chmike with very minor changes. The
 * source for the original function, sqrt_i32, can be found here:
 *
 * https://github.com/chmike/fpsqrt/blob/master/fpsqrt.c
 */
int32_t sqrt_int32(int32_t v);

#ifdef __cplusplus
}
#endif

#endif /* CH_MATH_UTILS_H_ */
