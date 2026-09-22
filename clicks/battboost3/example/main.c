/*!
 * @file main.c
 * @brief BATT Boost 3 Click example
 *
 * # Description
 * This example demonstrates the use of BATT Boost 3 Click board by configuring
 * and monitoring the TLV61290 battery front-end boost converter with true-bypass.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration,
 * reads the device ID and displays it via USB UART.
 *
 * ## Application Task
 * Reads the status register approximately once per second and displays the
 * power-good state, operating mode, and current-limit or thermal warning flags.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "battboost3.h"

#ifndef MIKROBUS_POSITION_BATTBOOST3
    #define MIKROBUS_POSITION_BATTBOOST3 MIKROBUS_1
#endif

static battboost3_t battboost3;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    battboost3_cfg_t battboost3_cfg;  /**< Click config object. */

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
    battboost3_cfg_setup( &battboost3_cfg );
    BATTBOOST3_MAP_MIKROBUS( battboost3_cfg, MIKROBUS_POSITION_BATTBOOST3 );
    if ( I2C_MASTER_ERROR == battboost3_init( &battboost3, &battboost3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BATTBOOST3_ERROR == battboost3_default_cfg ( &battboost3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    uint8_t device_id = 0;

    if ( BATTBOOST3_OK == battboost3_get_device_id( &battboost3, &device_id ) )
    {
        log_printf( &logger, " Device ID: 0x%.2X\r\n", ( uint16_t ) device_id );
    }
        
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t status = 0;

    if ( BATTBOOST3_OK == battboost3_get_status( &battboost3, &status ) )
    {
        if ( status & BATTBOOST3_STATUS_PGOOD )
        {
            log_printf( &logger, " Power good: Yes\r\n" );
        }
        else
        {
            log_printf( &logger, " Power good: No\r\n" );
        }

        if ( status & BATTBOOST3_STATUS_OPMODE )
        {
            log_printf( &logger, " Operating mode: Boost\r\n" );
        }
        else
        {
            log_printf( &logger, " Operating mode: Bypass\r\n" );
        }

        if ( status & BATTBOOST3_STATUS_TSD )
        {
            log_printf( &logger, " Warning: Thermal shutdown detected.\r\n" );
        }

        if ( status & BATTBOOST3_STATUS_ILIMBST )
        {
            log_printf( &logger, " Warning: Boost current limit detected.\r\n" );
        }

        if ( status & BATTBOOST3_STATUS_ILIMPT )
        {
            log_printf( &logger, " Warning: Bypass current limit detected.\r\n" );
        }

        if ( status & BATTBOOST3_STATUS_FL_LD )
        {
            log_printf( &logger, " Warning: Heavy load/current limit flag detected.\r\n" );
        }
    }
    else
    {
        log_error( &logger, " Failed status read." );
    }
    
    Delay_ms( 1000 );
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
