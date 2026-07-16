/*!
 * @file main.c
 * @brief Smart Buck 9 Click example
 *
 * # Description
 * This example demonstrates the use of the Smart Buck 9 Click board for
 * output voltage control. The application periodically sets the output
 * voltage across the supported range and monitors the device status register
 * for fault conditions.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and Smart Buck 9 Click driver, and applies the
 * default configuration.
 *
 * ## Application Task
 * Steps the output voltage from minimum to maximum value, reads the status
 * register, and logs detected faults such as input overvoltage, output
 * overvoltage, overcurrent, thermal shutdown, and power-not-good state.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "smartbuck9.h"

#ifndef MIKROBUS_POSITION_SMARTBUCK9
    #define MIKROBUS_POSITION_SMARTBUCK9 MIKROBUS_1
#endif

static smartbuck9_t smartbuck9;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartbuck9_cfg_t smartbuck9_cfg;  /**< Click config object. */

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
    smartbuck9_cfg_setup( &smartbuck9_cfg );
    SMARTBUCK9_MAP_MIKROBUS( smartbuck9_cfg, MIKROBUS_POSITION_SMARTBUCK9 );
    if ( I2C_MASTER_ERROR == smartbuck9_init( &smartbuck9, &smartbuck9_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SMARTBUCK9_ERROR == smartbuck9_default_cfg ( &smartbuck9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint16_t voltage_mv = SMARTBUCK9_VOUT_MIN_MV;
    uint8_t status = 0;

    if ( SMARTBUCK9_OK == smartbuck9_set_vout ( &smartbuck9, voltage_mv ) )
    {
        log_printf( &logger, " Set voltage : %u mV\r\n", voltage_mv );

        if ( SMARTBUCK9_OK == smartbuck9_read_reg( &smartbuck9, SMARTBUCK9_REG_STATUS, &status ) )
        {
            if ( status & SMARTBUCK9_STATUS_TSHDN )
            {
                log_error( &logger, " Thermal shutdown, junction temperature over 150 degC" );
            }

            if ( status & SMARTBUCK9_STATUS_VI_OVP )
            {
                log_error( &logger, " Input voltage over 6.5V" );
            }

            if ( status & SMARTBUCK9_STATUS_VO_OVP )
            {
                log_error( &logger, " Output voltage over 110 percents of VOUT set" );
            }

            if ( status & SMARTBUCK9_STATUS_OCP )
            {
                log_error( &logger, " Overcurrent fault" );
            }
        }

        if ( !smartbuck9_get_pg_pin ( &smartbuck9 ) )
        {
            log_error( &logger, " Power not good" );
        }

        log_printf( &logger, "-----------------------------\r\n" );
    }

    voltage_mv += SMARTBUCK9_VOUT_STEP_MV;

    if ( voltage_mv > SMARTBUCK9_VOUT_MAX_MV )
    {
        voltage_mv = SMARTBUCK9_VOUT_MIN_MV;
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
