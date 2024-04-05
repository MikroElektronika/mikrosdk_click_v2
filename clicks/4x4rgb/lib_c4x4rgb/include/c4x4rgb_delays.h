/**
 * Timing sequence chart:
 *          -----------|     T0L
 *              T0H    |______________
 * Logic 0: 
 *          T0H: 350ns (+/-150ns)
 *          T0L: 800ns (+/-150ns)
 * 
 *          -----------|     T1L
 *              T1H    |______________
 * Logic 1: 
 *          T1H: 700ns (+/-150ns)
 *          T1L: 600ns (+/-150ns)
 */
 
#ifndef C4X4RGB_DELAYS_H
#define C4X4RGB_DELAYS_H

// Delay adjustment for specific systems.
// Adjusted specifically for NECTO v6.1.0 and mikroSDK v2.11.0.
#ifdef __MIKROC_AI__
    #ifdef STM32F407ZG
        /*< Adjusted for STM32F407ZG */
        #define DELAY_TOH Delay_Cyc( 3 );   // ~290ns
        #define DELAY_TOL Delay_Cyc( 5 );   // ~730ns
        #define DELAY_T1H Delay_Cyc( 9 );   // ~640ns
        #define DELAY_T1L Delay_Cyc( 2 );   // ~550ns
    #elif MK64FN1M0VDC12
        /*< Adjusted for MK64FN1M0VDC12 */
        #define DELAY_TOH Delay_Cyc( 2 );   // ~300ns
        #define DELAY_TOL Delay_Cyc( 3 );   // ~870ns
        #define DELAY_T1H Delay_Cyc( 7 );   // ~720ns
        #define DELAY_T1L Delay_Cyc( 2 );   // ~700ns
    #elif TM4C129XNCZAD
        /*< Adjusted for TM4C129XNCZAD */
        #define DELAY_TOH                   // ~420ns
        #define DELAY_TOL                   // ~1000ns
        #define DELAY_T1H Delay_Cyc( 2 );   // ~690ns
        #define DELAY_T1L                   // ~1000ns
    #elif PIC32MX795F512L
        /*< Adjusted for PIC32MX795F512L */
        #define DELAY_TOH \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop;                // ~350ns
        #define DELAY_TOL                   // ~880ns
        #define DELAY_T1H Delay_Cyc( 3 );   // ~700ns
        #define DELAY_T1L                   // ~1000ns
    #else
        #error "Logic delays are not defined for the selected MCU"
    #endif
#elif __clang__
    #ifdef STM32F407ZG
        /*< Adjusted for STM32F407ZG */
        #define DELAY_TOH Delay_Cyc( 2 );   // ~370ns
        #define DELAY_TOL Delay_Cyc( 4 );   // ~790ns
        #define DELAY_T1H Delay_Cyc( 9 );   // ~700ns
        #define DELAY_T1L Delay_Cyc( 2 );   // ~690ns
    #elif MK64
        /*< Adjusted for MK64FN1M0VDC12 */
        #define DELAY_TOH Delay_Cyc( 2 );   // ~370ns
        #define DELAY_TOL Delay_Cyc( 3 );   // ~780ns
        #define DELAY_T1H Delay_Cyc( 12 );  // ~700ns
        #define DELAY_T1L \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");             // ~610ns
    #elif TM4C129
        /*< Adjusted for TM4C129XNCZAD */
        #define DELAY_TOH \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");             // ~380ns
        #define DELAY_TOL \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");             // ~750ns
        #define DELAY_T1H Delay_Cyc( 4 );   // ~690ns
        #define DELAY_T1L                   // ~750ns
    #elif GD32VF103VBT6
        /*< Adjusted for GD32VF103VBT6 */
        #define DELAY_TOH \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");             // ~350ns
        #define DELAY_TOL \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");             // ~780ns
        #define DELAY_T1H Delay_Cyc( 2 );   // ~690ns
        #define DELAY_T1L \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");             // ~620ns
    #else
        #error "Logic delays are not defined for the selected MCU"
    #endif
#elif __GNUC__
    #ifdef STM32F407ZG
        /*< Adjusted for STM32F407ZG */
        #define DELAY_TOH \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");             // ~310ns
        #define DELAY_TOL Delay_Cyc( 2 );   // ~760ns
        #define DELAY_T1H Delay_Cyc( 7 );   // ~710ns
        #define DELAY_T1L \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");             // ~600ns
    #elif MK64
        /*< Adjusted for MK64FN1M0VDC12 */
        #define DELAY_TOH Delay_Cyc( 2 );   // ~390ns
        #define DELAY_TOL Delay_Cyc( 3 );   // ~780ns
        #define DELAY_T1H Delay_Cyc( 11 );  // ~690ns
        #define DELAY_T1L \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");             // ~610ns
    #elif TM4C129
        /*< Adjusted for TM4C129XNCZAD */
        #define DELAY_TOH                   // ~450ns
        #define DELAY_TOL                   // ~960ns
        #define DELAY_T1H \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");             // ~720ns
        #define DELAY_T1L                   // ~1020ns
    #elif GD32VF103VBT6
        /*< Adjusted for GD32VF103VBT6 */
        #define DELAY_TOH \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");             // ~350ns
        #define DELAY_TOL Delay_Cyc( 2 );   // ~860ns
        #define DELAY_T1H Delay_Cyc( 4 );   // ~760ns
        #define DELAY_T1L \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");             // ~600ns
    #else
        #error "Logic delays are not defined for the selected MCU"
    #endif
#else
    #error "Logic delays are not defined for the selected toolchain"
#endif

#endif  // C4X4RGB_DELAYS_H