/*!
 * @file main.c
 * @brief Boost-INV 3 Click example
 *
 * # Description
 * This library contains API for the Boost-INV 3 Click driver.
 * This driver provides the functions to set the output voltage treshold.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, default settings enable the positive and 
 * negative output and sets the output voltage to 4 V.
 *
 * ## Application Task
 * This example demonstrates the use of the Boost-INV 3 Click board by changing 
 * output voltage every 5 seconds starting from 4 V up to 6 V.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "boostinv3.h"

#define BOOSTINV3_MIN_VOL_LVL           4.0f
#define BOOSTINV3_INCREMENT             0.1f

static boostinv3_t boostinv3;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    boostinv3_cfg_t boostinv3_cfg;  /**< Click config object. */

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
    boostinv3_cfg_setup( &boostinv3_cfg );
    BOOSTINV3_MAP_MIKROBUS( boostinv3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == boostinv3_init( &boostinv3, &boostinv3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( BOOSTINV3_ERROR == boostinv3_default_cfg ( &boostinv3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    for ( uint8_t n_cnt = BOOSTINV3_OUT_VOLTAGE_4V; n_cnt <= BOOSTINV3_OUT_VOLTAGE_6V; n_cnt++ )
    {
        err_t error_flag = boostinv3_set_pos_out( &boostinv3, n_cnt );
        error_flag |= boostinv3_set_neg_out( &boostinv3, n_cnt );
        if ( BOOSTINV3_OK == error_flag )
        {
            log_printf( &logger, " Set positive and negative voltage to %.1f V \r\n", 
                        ( BOOSTINV3_MIN_VOL_LVL + n_cnt * BOOSTINV3_INCREMENT ) );
        }
        else
        {
            log_printf( &logger, " Error has occurred!!! \r\n" );
        }
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
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
