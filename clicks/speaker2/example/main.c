/*!
 * @file main.c
 * @brief Speaker 2 Click example
 *
 * # Description
 * This example demonstrates the use of the Speaker 2 Click board. It initializes the board
 * and plays predefined voice messages or sound effects through the speaker module.
 * Supported voices include numbers (ONE to SIX) and sound effects like FAST BEEP.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger module, configures the Speaker 2 Click board, and applies the
 * default settings to reset the device, power it up, verify communication, and load an example
 * audio project into the device memory.
 *
 * ## Application Task
 * Sequentially plays predefined voice messages and sound effects from the Speaker 2 Click board
 * while logging the playback status (DONE or ERROR) for each sound.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "speaker2.h"

static speaker2_t speaker2;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    speaker2_cfg_t speaker2_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    speaker2_cfg_setup( &speaker2_cfg );
    SPEAKER2_MAP_MIKROBUS( speaker2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == speaker2_init( &speaker2, &speaker2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SPEAKER2_ERROR == speaker2_default_cfg ( &speaker2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    log_printf ( &logger, " Playing voice ONE: %s\r\n\n", ( char * ) 
                 ( ( SPEAKER2_OK == speaker2_play_voice ( &speaker2, SPEAKER2_VP9_ONE ) ) ? "DONE" : "ERROR" ) );
    log_printf ( &logger, " Playing voice TWO: %s\r\n\n", ( char * ) 
                 ( ( SPEAKER2_OK == speaker2_play_voice ( &speaker2, SPEAKER2_VP10_TWO ) ) ? "DONE" : "ERROR" ) );
    log_printf ( &logger, " Playing voice THREE: %s\r\n\n", ( char * ) 
                 ( ( SPEAKER2_OK == speaker2_play_voice ( &speaker2, SPEAKER2_VP11_THREE ) ) ? "DONE" : "ERROR" ) );
    log_printf ( &logger, " Playing voice FOUR: %s\r\n\n", ( char * ) 
                 ( ( SPEAKER2_OK == speaker2_play_voice ( &speaker2, SPEAKER2_VP12_FOUR ) ) ? "DONE" : "ERROR" ) );
    log_printf ( &logger, " Playing voice FIVE: %s\r\n\n", ( char * ) 
                 ( ( SPEAKER2_OK == speaker2_play_voice ( &speaker2, SPEAKER2_VP13_FIVE ) ) ? "DONE" : "ERROR" ) );
    log_printf ( &logger, " Playing voice SIX: %s\r\n\n", ( char * ) 
                 ( ( SPEAKER2_OK == speaker2_play_voice ( &speaker2, SPEAKER2_VP14_SIX ) ) ? "DONE" : "ERROR" ) );
    log_printf ( &logger, " Playing voice FAST BEEP: %s\r\n\n", ( char * ) 
                 ( ( SPEAKER2_OK == speaker2_play_voice ( &speaker2, SPEAKER2_VP15_FAST_BEEP ) ) ? "DONE" : "ERROR" ) );
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
