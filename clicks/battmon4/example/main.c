/*!
 * @file main.c
 * @brief BATTMON4 Click example
 *
 * # Description
 * This example demonstrates the use of BATT-MON 4 click board by reading
 * the battery voltage and the chip internal temperature.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads the chip DIE temperature and voltage from BATT IN and BATT OUT and displays
 * the results on the USB UART approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "battmon4.h"

static battmon4_t battmon4;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    battmon4_cfg_t battmon4_cfg;  /**< Click config object. */

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
    battmon4_cfg_setup( &battmon4_cfg );
    BATTMON4_MAP_MIKROBUS( battmon4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == battmon4_init( &battmon4, &battmon4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float die_temperature, batt_in_v_ipeak_on, batt_in_v_ipeak_off, batt_out_v_ipeak_on, batt_out_v_ipeak_off;

    if ( BATTMON4_OK == battmon4_get_die_temperature ( &battmon4, &die_temperature ) )
    {
        log_printf ( &logger, " Die Temperature: %.2f C \r\n\n", die_temperature );
    }
    
    if ( BATTMON4_OK == battmon4_get_batt_in_voltage ( &battmon4, &batt_in_v_ipeak_on, &batt_in_v_ipeak_off ) )
    {
        log_printf ( &logger, " BATT IN \r\n Ipeak ON: %.1f mV \r\n Ipeak OFF: %.1f mV \r\n\n", 
                     batt_in_v_ipeak_on, batt_in_v_ipeak_off );
    }
    
    if ( BATTMON4_OK == battmon4_get_batt_out_voltage ( &battmon4, &batt_out_v_ipeak_on, &batt_out_v_ipeak_off ) )
    {
        log_printf ( &logger, " BATT OUT \r\n Ipeak ON: %.1f mV \r\n Ipeak OFF: %.1f mV \r\n\n", 
                     batt_out_v_ipeak_on, batt_out_v_ipeak_off );
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
