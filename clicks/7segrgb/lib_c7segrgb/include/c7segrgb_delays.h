/**
 * Timing sequence chart:
 *          -----------|     T0L
 *              T0H    |______________
 * Logic 0: 
 *          T0H: 400ns (+/-150ns)
 *          T0L: 850ns (+/-150ns)
 * 
 *          -----------|     T1L
 *              T1H    |______________
 * Logic 1: 
 *          T1H: 850ns (+/-150ns)
 *          T1L: 400ns (+/-150ns)
 */
 
#ifndef C7SEGRGB_DELAYS_H
#define C7SEGRGB_DELAYS_H

// Delay adjustment for specific systems.
// Adjusted specifically for NECTO v6.1.0 and mikroSDK v2.11.0.
#ifdef __MIKROC_AI__
    #ifdef STM32F407ZG
        /*< Adjusted for STM32F407ZG */
        #define DELAY_TOH Delay_Cyc( 4 );   // ~400ns
        #define DELAY_TOL Delay_Cyc( 7 );   // ~850ns
        #define DELAY_T1H Delay_Cyc( 12 );  // ~820ns
        #define DELAY_T1L                   // ~390ns
    #elif MK64FN1M0VDC12
        /*< Adjusted for MK64FN1M0VDC12 */
        #define DELAY_TOH Delay_Cyc( 3 );   // ~380ns
        #define DELAY_TOL Delay_Cyc( 5 );   // ~870ns
        #define DELAY_T1H Delay_Cyc( 8 );   // ~800ns
        #define DELAY_T1L                   // ~470ns
    #elif TM4C129XNCZAD
        /*< Adjusted for TM4C129XNCZAD */
        #define DELAY_TOH                   // ~400ns
        #define DELAY_TOL                   // ~860ns
        #define DELAY_T1H Delay_Cyc( 4 );   // ~800ns
        #define DELAY_T1L                   // ~910ns
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
                    asm nop; \
                    asm nop; \
                    asm nop;                // ~430ns
        #define DELAY_TOL                   // ~900ns
        #define DELAY_T1H Delay_Cyc( 4 );   // ~870ns
        #define DELAY_T1L                   // ~1000ns
    #else
        #error "Logic delays are not defined for the selected MCU"
    #endif
#elif __clang__
    #ifdef STM32F407ZG
        /*< Adjusted for STM32F407ZG */
        #define DELAY_TOH Delay_Cyc( 3 );   // ~420ns
        #define DELAY_TOL Delay_Cyc( 6 );   // ~840ns
        #define DELAY_T1H Delay_Cyc( 12 );  // ~840ns
        #define DELAY_T1L asm("nop");       // ~410ns
    #elif MK64
        /*< Adjusted for MK64FN1M0VDC12 */
        #define DELAY_TOH Delay_Cyc( 2 );   // ~360ns
        #define DELAY_TOL Delay_Cyc( 4 );   // ~770ns
        #define DELAY_T1H Delay_Cyc( 16 );  // ~830ns
        #define DELAY_T1L                   // ~500ns
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
                    asm("nop");             // ~800ns
        #define DELAY_T1H Delay_Cyc( 6 );   // ~840ns
        #define DELAY_T1L                   // ~700ns
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
                    asm("nop");             // ~390ns
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
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");             // ~800ns
        #define DELAY_T1H Delay_Cyc( 3 );   // ~790ns
        #define DELAY_T1L                   // ~560ns
    #else
        #error "Logic delays are not defined for the selected MCU"
    #endif
#elif __GNUC__
    #ifdef STM32F407ZG
        /*< Adjusted for STM32F407ZG */
        #define DELAY_TOH Delay_Cyc( 2 );   // ~470ns
        #define DELAY_TOL Delay_Cyc( 5 );   // ~860ns
        #define DELAY_T1H Delay_Cyc( 10 );  // ~850ns
        #define DELAY_T1L asm("nop");       // ~410ns
    #elif MK64
        /*< Adjusted for MK64FN1M0VDC12 */
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
                    asm("nop");             // ~380ns
        #define DELAY_TOL Delay_Cyc( 2 );   // ~830ns
        #define DELAY_T1H Delay_Cyc( 16 );  // ~850ns
        #define DELAY_T1L                   // ~430ns
    #elif TM4C129
        /*< Adjusted for TM4C129XNCZAD */
        #define DELAY_TOH                   // ~440ns
        #define DELAY_TOL                   // ~990ns
        #define DELAY_T1H Delay_Cyc( 2 );   // ~970ns
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
                    asm("nop");             // ~420ns
        #define DELAY_TOL Delay_Cyc( 2 );   // ~830ns
        #define DELAY_T1H Delay_Cyc( 5 );   // ~850ns
        #define DELAY_T1L                   // ~460ns
    #else
        #error "Logic delays are not defined for the selected MCU"
    #endif
#else
    #error "Logic delays are not defined for the selected toolchain"
#endif

#endif  // C7SEGRGB_DELAYS_H