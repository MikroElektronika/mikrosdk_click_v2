/*!
 * @file main.c
 * @brief DSP Click Example.
 *
 * # Description
 * This application controls reverb and multi-effects Digital Multi-Effects DSP 
 * provides different sound performance of the DSP Click.  
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes GPIO driver, set the default configuration and start to write log.
 *
 * ## Application Task
 * This is an example that shows the use of a DSP click board.
 * In this example, we change different sound effects
 * such as multiple reverbs, echo, phaser, chorus, flanger, etc. every 10 sec.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dsp.h"

static dsp_t dsp;       /**< DSP Click driver object. */
static log_t logger;    /**< Logger object. */
static uint8_t effects = DSP_SET_EFFECT_MEDIUM; 


void display_effects ( void ) {
    switch ( effects ) {
        case DSP_SET_EFFECT_MEDIUM: {
            log_printf( &logger, " Reverb, Small hall (1.5 sec.)\r\n" );
            break;
        }
        case DSP_SET_EFFECT_CHAMBR7B: {
            log_printf( &logger, " Reverb, Big hall (2.8 sec.)\r\n" );
            break;
        }
        case DSP_SET_EFFECT_ROOM3B: {
            log_printf( &logger, " Reverb, Room (1.8 sec.)\r\n" );
            break;
        }
        case DSP_SET_EFFECT_CHAMBER2: {
            log_printf( &logger, " Reverb, Church (7 sec.)\r\n" );
            break;
        }
        case DSP_SET_EFFECT_REVERS3B: {
            log_printf( &logger, " Reverb Reverse (1.2 sec.)\r\n" );
            break;
        }
        case DSP_SET_EFFECT_GATED4B: {
            log_printf( &logger, " Reverb Gated (0.8 sec.)\r\n" );
            break;
        }
        case DSP_SET_EFFECT_ROOM2A: {
            log_printf( &logger, " Reverb Chapel (3 sec.)\r\n" );
            break;
        }
        case DSP_SET_EFFECT_SPRING3B: {
            log_printf( &logger, " Reverb Spring (2 sec.)\r\n" );
            break;
        } 
        case DSP_SET_EFFECT_PHASER1: {
            log_printf( &logger, " Phaser\r\n" );
            break;
        }
        case DSP_SET_EFFECT_FLANGER2: {
            log_printf( &logger, " Flanger\r\n" );
            break;
        }
        case DSP_SET_EFFECT_DELAY7: {
            log_printf( &logger, " Echo\r\n" );
            break;
        }
        case DSP_SET_EFFECT_CHORUS4: {
            log_printf( &logger, " Chorus\r\n" );
            break;
        }
        case DSP_SET_EFFECT_EARLREF4: {
            log_printf( &logger, " Early Reflection\r\n" );
            break;
        }
        case DSP_SET_EFFECT_AMB4: {
            log_printf( &logger, " Big Ambience\r\n" );
            break;
        }
        case DSP_SET_EFFECT_DELAY3: {
            log_printf( &logger, " Stereo Delay\r\n" );
            break;
        }
        case DSP_SET_EFFECT_DELAY1: {
            log_printf( &logger, " Slap-back Delay\r\n" );
            break;
        }
        default: {
            log_error( &logger, " Error" );
            break;
        }
    }     
}

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    dsp_cfg_t dsp_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    dsp_cfg_setup( &dsp_cfg );
    DSP_MAP_MIKROBUS( dsp_cfg, MIKROBUS_1 );
    if ( dsp_init( &dsp, &dsp_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    dsp_default_cfg ( &dsp );   
    log_info( &logger, " Application Task \r\n" );
    Delay_ms( 100 );
    
    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, "           DSP click           \r\n" );
    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, "     Digital Multi-Effects     \r\n" );
}

void application_task ( void ) {
    log_printf( &logger, "-------------------------------\r\n" );
    dsp_set_effect( &dsp, effects );
    display_effects( );
    
    effects++;
    if ( effects > DSP_SET_EFFECT_DELAY1 ) {
        effects = DSP_SET_EFFECT_MEDIUM;
    }

    Delay_ms( 10000 );  
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
