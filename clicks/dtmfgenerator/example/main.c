/*!
 * @file main.c
 * @brief DTMF Generator Click Example.
 *
 * # Description
 * This is an example which demonstrates the use of DTMF Generator Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enables - GPIO,
 * run the power-on sequence, also write log.
 *
 * ## Application Task
 * DTMF Generator click board DTMF generator transmits the signal 
 * for generating tone for digits :
 * "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
 * "A", "B", "C", "D", "*" and "#".
 * All data logs write on USB uart changes.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "dtmfgenerator.h"

static dtmfgenerator_t dtmfgenerator;   /**< DTMF Generator Click driver object. */
static log_t logger;    /**< Logger object. */

static uint16_t signal_duration = 500;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    dtmfgenerator_cfg_t dtmfgenerator_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    dtmfgenerator_cfg_setup( &dtmfgenerator_cfg );
    DTMFGENERATOR_MAP_MIKROBUS( dtmfgenerator_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == dtmfgenerator_init( &dtmfgenerator, &dtmfgenerator_cfg ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_printf( &logger, " Powering on device \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    dtmfgenerator_power_on( &dtmfgenerator );
    Delay_ms( 1000 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    log_printf( &logger, " TONE      '0' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_0, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      '1' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_1, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      '2' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_2, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      '3' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_3, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      '4' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_4, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      '5' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_5, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      '6' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_6, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      '7' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_7, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      '8' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_8, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      '9' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_9, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      'A' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_A, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      'B' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_B, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      'C' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_C, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      'D' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_D, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      '*' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_ASTERISK, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
    
    log_printf( &logger, " TONE      '#' \r\n");
    log_printf( &logger, "---------------\r\n" );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_HASH, signal_duration );
    dtmfgenerator_transmit_out_tone( &dtmfgenerator, DTMFGENERATOR_OUT_TONE_STOP, signal_duration );
 }

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
