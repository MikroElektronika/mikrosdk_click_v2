/**
 * Timing sequence chart:
 *          -----------|     T0L
 *              T0H    |______________
 * Logic 0: 
 *          T0H: 300ns (+/-150ns)
 *          T0L: 900ns (+/-150ns)
 * 
 *          -----------|     T1L
 *              T1H    |______________
 * Logic 1: 
 *          T1H: 900ns (+/-150ns)
 *          T1L: 300ns (+/-150ns)
 */
 
#ifndef RGBRING_DELAYS_H
#define RGBRING_DELAYS_H

// Delay adjustment for specific systems.
// Adjusted specifically for NECTO v7.0.2 and mikroSDK v2.11.1.
#ifdef __MIKROC_AI__
    #ifdef STM32F407ZG
        /*< Adjusted for STM32F407ZG */
        #define DELAY_TOH Delay_Cyc( 2 );   // ~280ns
        #define DELAY_TOL Delay_Cyc( 8 );   // ~940ns
        #define DELAY_T1H Delay_Cyc( 13 );  // ~880ns
        #define DELAY_T1L                   // ~420ns
    #elif MK64FN1M0VDC12
        /*< Adjusted for MK64FN1M0VDC12 */
        #define DELAY_TOH Delay_Cyc( 2 );   // ~300ns
        #define DELAY_TOL Delay_Cyc( 4 );   // ~910ns
        #define DELAY_T1H Delay_Cyc( 9 );   // ~880ns
        #define DELAY_T1L                   // ~510ns
    #elif TM4C129
        /*< Adjusted for TM4C129XNCZAD */
        #define DELAY_TOH                   // ~390ns
        #define DELAY_TOL                   // ~920ns
        #define DELAY_T1H Delay_Cyc( 6 );   // ~950ns
        #define DELAY_T1L                   // ~950ns
    #elif PIC32MX795F512L
        /*< Adjusted for PIC32MX795F512L */
        #define DELAY_TOH \
                    asm nop; \
                    asm nop; \
                    asm nop;                // ~300ns
        #define DELAY_TOL \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop;                // ~950ns
        #define DELAY_T1H Delay_Cyc( 4 );   // ~840ns
        #define DELAY_T1L                   // ~1050ns
    #else
        #error "Logic delays are not defined for the selected MCU"
    #endif
#elif __clang__
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
                    asm("nop");             // ~300ns
        #define DELAY_TOL Delay_Cyc( 7 );   // ~920ns
        #define DELAY_T1H Delay_Cyc( 13 );  // ~890ns
        #define DELAY_T1L                   // ~440ns
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
                    asm("nop");             // ~290ns
        #define DELAY_TOL Delay_Cyc( 4 );   // ~960ns
        #define DELAY_T1H Delay_Cyc( 18 );  // ~900ns
        #define DELAY_T1L                   // ~540ns
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
                    asm("nop");             // ~320ns
        #define DELAY_TOL \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");             // ~930ns
        #define DELAY_T1H Delay_Cyc( 7 );   // ~860ns
        #define DELAY_T1L                   // ~770ns
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
                    asm("nop");             // ~290ns
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
                    asm("nop");             // ~920ns
        #define DELAY_T1H Delay_Cyc( 3 );   // ~900ns
        #define DELAY_T1L                   // ~650ns
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
                    asm("nop");             // ~300ns
        #define DELAY_TOL Delay_Cyc( 5 );   // ~920ns
        #define DELAY_T1H Delay_Cyc( 11 );  // ~900ns
        #define DELAY_T1L                   // ~420ns
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
                    asm("nop");             // ~310ns
        #define DELAY_TOL Delay_Cyc( 2 );   // ~940ns
        #define DELAY_T1H Delay_Cyc( 16 );  // ~860ns
        #define DELAY_T1L                   // ~490ns
    #elif TM4C129
        /*< Adjusted for TM4C129XNCZAD */
        #define DELAY_TOH                   // ~460ns
        #define DELAY_TOL                   // ~1040ns
        #define DELAY_T1H Delay_Cyc( 2 );   // ~920ns
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
                    asm("nop");             // ~310ns
        #define DELAY_TOL Delay_Cyc( 2 );   // ~970ns
        #define DELAY_T1H Delay_Cyc( 5 );   // ~960ns
        #define DELAY_T1L                   // ~550ns
    #else
        #error "Logic delays are not defined for the selected MCU"
    #endif
#else
    #error "Logic delays are not defined for the selected toolchain"
#endif

#endif  // RGBRING_DELAYS_H