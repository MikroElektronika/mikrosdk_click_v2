/*!
 * @file main.c
 * @brief eFuse 8 Click example
 *
 * # Description
 * This example demonstrates the use of the eFuse 8 Click board by changing
 * the current limit through a range of values, reading it back and monitoring 
 * the supply good indication.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Steps the current limit through a table of values from 1 to 8 A. For each
 * value it reads back the resulting current limit from the device
 * and logs them together with the state of the supply good pin.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "efuse8.h"

#ifndef MIKROBUS_POSITION_EFUSE8
    #define MIKROBUS_POSITION_EFUSE8 MIKROBUS_1
#endif

/**
 * @brief eFuse 8 current limit table size setting.
 * @details Specified setting for current limit table size of eFuse 8 Click driver.
 */
#define EFUSE8_ILIM_TABLE_SIZE      8

static efuse8_t efuse8;
static log_t logger;

/**
 * @brief eFuse 8 current limit table.
 * @details Specified current limit values in milliamperes.
 */
static const uint16_t ilim_table[ EFUSE8_ILIM_TABLE_SIZE ] = 
{
    1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000
};

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    efuse8_cfg_t efuse8_cfg;  /**< Click config object. */

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
    efuse8_cfg_setup( &efuse8_cfg );
    EFUSE8_MAP_MIKROBUS( efuse8_cfg, MIKROBUS_POSITION_EFUSE8 );
    if ( I2C_MASTER_ERROR == efuse8_init( &efuse8, &efuse8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EFUSE8_ERROR == efuse8_default_cfg ( &efuse8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    for ( uint8_t cnt = 0; cnt < EFUSE8_ILIM_TABLE_SIZE; cnt++ )
    {
        uint16_t ilim_ma = 0;
        err_t error_flag = EFUSE8_OK;

        error_flag |= efuse8_set_current_limit( &efuse8, ilim_table[ cnt ] );
        error_flag |= efuse8_get_current_limit( &efuse8, &ilim_ma );

        if ( EFUSE8_OK == error_flag )
        {
            log_printf( &logger, " Set limit  : %u mA\r\n", ilim_table[ cnt ] );
            log_printf( &logger, " Read limit : %u mA\r\n", ilim_ma );
            if ( EFUSE8_SUPPLY_GOOD == efuse8_get_pgd_pin( &efuse8 ) )
            {
                log_printf( &logger, " Supply good: YES\r\n" );
            }
            else
            {
                log_printf( &logger, " Supply good: NO\r\n" );
            }
            log_printf( &logger, " -------------------------------\r\n" );
        }
        else
        {
            log_error( &logger, " Communication." );
        }

        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
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
