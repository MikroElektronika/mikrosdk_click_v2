/**
 * Timing sequence chart:
 *          -----------|     T0L
 *              T0H    |______________
 * Logic 0: 
 *          T0H ~ 200-400ns
 *          T0L ~ 600-1000ns
 * 
 *          -----------|     T1L
 *              T1H    |______________
 * Logic 1: 
 *          T1H ~ 600-1000ns
 *          T1L ~ 600-1000ns
 */
 
#ifndef C10X10RGB_DELAYS_H
#define C10X10RGB_DELAYS_H

// Delay adjustment for specific systems.
// Adjusted specifically for NECTO v6.1.0 and mikroSDK v2.11.0.
#ifdef __MIKROC_AI__
    #ifdef STM32F407ZG
        /*< Adjusted for STM32F407ZG */
        #define DELAY_TOH Delay_Cyc( 3 );   // ~280ns
        #define DELAY_TOL Delay_Cyc( 7 );   // ~790ns
        #define DELAY_T1H Delay_Cyc( 12 );  // ~820ns
        #define DELAY_T1L Delay_Cyc( 8 );   // ~840ns
    #elif MK64FN1M0VDC12
        /*< Adjusted for MK64FN1M0VDC12 */
        #define DELAY_TOH Delay_Cyc( 2 );   // ~300ns
        #define DELAY_TOL Delay_Cyc( 4 );   // ~780ns
        #define DELAY_T1H Delay_Cyc( 7 );   // ~790ns
        #define DELAY_T1L Delay_Cyc( 3 );   // ~810ns
    #elif TM4C129XNCZAD
        /*< Adjusted for TM4C129XNCZAD */
        #define DELAY_TOH                   // ~420ns
        #define DELAY_TOL asm nop;          // ~930ns
        #define DELAY_T1H Delay_Cyc( 4 );   // ~790ns
        #define DELAY_T1L                   // ~960ns
    #elif PIC32MX795F512L
        /*< Adjusted for PIC32MX795F512L */
        #define DELAY_TOH                   // ~250ns
        #define DELAY_TOL                   // ~710ns
        #define DELAY_T1H Delay_Cyc( 4 );   // ~830ns
        #define DELAY_T1L                   // ~900ns
    #else
        #error "Logic delays are not defined for the selected MCU"
    #endif
#elif __clang__
    #ifdef STM32F407ZG
        /*< Adjusted for STM32F407ZG */
        #define DELAY_TOH Delay_Cyc( 2 );   // ~370ns
        #define DELAY_TOL Delay_Cyc( 4 );   // ~740ns
        #define DELAY_T1H Delay_Cyc( 10 );  // ~740ns
        #define DELAY_T1L Delay_Cyc( 4 );   // ~750ns
    #elif MK64
        /*< Adjusted for MK64FN1M0VDC12 */
        #define DELAY_TOH Delay_Cyc( 2 );   // ~360ns
        #define DELAY_TOL Delay_Cyc( 2 );   // ~700ns
        #define DELAY_T1H Delay_Cyc( 12 );  // ~740ns
        #define DELAY_T1L Delay_Cyc( 2 );   // ~760ns
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
                    asm("nop");             // ~280ns
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
                    asm("nop");             // ~760ns
        #define DELAY_T1H Delay_Cyc( 6 );   // ~820ns
        #define DELAY_T1L \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");             // ~730ns
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
                    asm("nop");             // ~300ns
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
                    asm("nop");             // ~680ns
        #define DELAY_T1H Delay_Cyc( 2 );   // ~680ns
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
                    asm("nop");             // ~730ns
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
                    asm("nop");             // ~260ns
        #define DELAY_TOL Delay_Cyc( 2 );   // ~740ns
        #define DELAY_T1H Delay_Cyc( 7 );   // ~710ns
        #define DELAY_T1L Delay_Cyc( 2 );   // ~740ns
    #elif MK64
        /*< Adjusted for MK64FN1M0VDC12 */
        #define DELAY_TOH Delay_Cyc( 2 );   // ~390ns
        #define DELAY_TOL Delay_Cyc( 2 );   // ~720ns
        #define DELAY_T1H Delay_Cyc( 10 );  // ~680ns
        #define DELAY_T1L Delay_Cyc( 4 );   // ~780ns
    #elif TM4C129
        /*< Adjusted for TM4C129XNCZAD */
        #define DELAY_TOH                   // ~470ns
        #define DELAY_TOL                   // ~950ns
        #define DELAY_T1H Delay_Cyc( 2 );   // ~1000ns
        #define DELAY_T1L                   // ~950ns
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
                    asm("nop");             // ~270ns
        #define DELAY_TOL Delay_Cyc( 2 );   // ~850ns
        #define DELAY_T1H Delay_Cyc( 4 );   // ~770ns
        #define DELAY_T1L Delay_Cyc( 2 );   // ~850ns
    #else
        #error "Logic delays are not defined for the selected MCU"
    #endif
#else
    #error "Logic delays are not defined for the selected toolchain"
#endif

#endif  // _C10X10RGB_H_