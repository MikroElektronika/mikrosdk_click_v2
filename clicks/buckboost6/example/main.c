/*!
 * @file main.c
 * @brief Buck-Boost 6 Click example
 *
 * # Description
 * This example demonstrates the use of the Buck-Boost 6 Click board for
 * output voltage control. The application periodically sets the output
 * voltage across the supported range and monitors the device status register
 * for fault conditions.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and Buck-Boost 6 Click driver, and applies the
 * default configuration.
 *
 * ## Application Task
 * Steps the output voltage from minimum to maximum value, reads the status
 * register, and logs detected faults such as input undervoltage, output
 * undervoltage, overcurrent, thermal shutdown, and power-not-good state.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "buckboost6.h"

#ifndef MIKROBUS_POSITION_BUCKBOOST6
    #define MIKROBUS_POSITION_BUCKBOOST6 MIKROBUS_1
#endif

static buckboost6_t buckboost6;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buckboost6_cfg_t buckboost6_cfg;  /**< Click config object. */

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
    buckboost6_cfg_setup( &buckboost6_cfg );
    BUCKBOOST6_MAP_MIKROBUS( buckboost6_cfg, MIKROBUS_POSITION_BUCKBOOST6 );
    if ( I2C_MASTER_ERROR == buckboost6_init( &buckboost6, &buckboost6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BUCKBOOST6_ERROR == buckboost6_default_cfg ( &buckboost6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint16_t voltage_mv = BUCKBOOST6_VOUT_MIN_MV;
    uint8_t status = 0;

    if ( BUCKBOOST6_OK == buckboost6_set_vout ( &buckboost6, voltage_mv ) )
    {
        log_printf( &logger, " Set voltage : %u mV\r\n", voltage_mv );

        if ( BUCKBOOST6_OK == buckboost6_read_reg( &buckboost6, BUCKBOOST6_REG_STATUS, &status ) )
        {
            if ( status & BUCKBOOST6_STATUS_VINUV )
            {
                log_error( &logger, " VIN UV fault" );
            }

            if ( status & BUCKBOOST6_STATUS_UV )
            {
                log_error( &logger, " Output UV fault" );
            }

            if ( status & BUCKBOOST6_STATUS_OC )
            {
                log_error( &logger, " Overcurrent fault" );
            }

            if ( status & BUCKBOOST6_STATUS_TSD )
            {
                log_error( &logger, " Thermal shutdown" );
            }

            if ( status & BUCKBOOST6_STATUS_NPG )
            {
                log_error( &logger, " Power not good" );
            }
        }

        log_printf( &logger, "-----------------------------\r\n" );
    }

    voltage_mv += BUCKBOOST6_VOUT_STEP_MV;

    if ( voltage_mv > BUCKBOOST6_VOUT_MAX_MV )
    {
        voltage_mv = BUCKBOOST6_VOUT_MIN_MV;
    }

    Delay_ms ( 1000 );
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
