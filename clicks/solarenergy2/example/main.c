/*!
 * @file main.c
 * @brief Solar Energy 2 Click example
 *
 * # Description
 * This library contains API for the Solar Energy 2 Click driver.
 * This driver provides functions to configure the
 * power management controller with an energy harvesting interface.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, the app set default settings.
 *
 * ## Application Task
 * This is an example that shows the use of Solar Energy 2 Click board™.
 * The following example will charge the battery 
 * if it is below the maximum voltage of the application of 3.40 V, 
 * stop charging when the battery is full and monitor additional status and 
 * storage element voltage information.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "solarenergy2.h"

static solarenergy2_t solarenergy2;
static log_t logger;
static solarenergy2_status_t status;
static solarenergy2_bat_vtg_status_t vld_status;

void display_status ( void )
{
    log_printf( &logger, "----------------------------\r\n" );
    if ( status.hrv_low )
    {
        log_printf( &logger, " HRV energy level too low for harvesting.\r\n" );
    }
    else
    {
        log_printf( &logger, " HRV has enough energy to be harvested.\r\n" );
    }
    
    if ( status.bat_low )
    {
        log_printf( &logger, " LTS voltage lower than min battery maintenance voltage.\r\n" );
    }
    else
    {
        log_printf( &logger, " LTS voltage higher than min battery maintenance voltage.\r\n" );
    }

    if ( status.sw_vdcdc_lts_nsts )
    {
        if ( vld_status.sts_apl_max_lo || vld_status.sts_apl_max_hi )
        {
            log_printf( &logger, " The battery is not charging.\r\n" );
        }
        else
        {
            log_printf( &logger, " The battery is charging.\r\n" );
        }
    }

    if ( status.sw_vdcdc_lts_nsts )
    {
        log_printf( &logger, " The power supply has been detected.\r\n" );
    }
    else
    {
        log_printf( &logger, " No power supply.\r\n" );
    }
}

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    solarenergy2_cfg_t solarenergy2_cfg;  /**< Click config object. */

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
    solarenergy2_cfg_setup( &solarenergy2_cfg );
    SOLARENERGY2_MAP_MIKROBUS( solarenergy2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == solarenergy2_init( &solarenergy2, &solarenergy2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SOLARENERGY2_ERROR == solarenergy2_default_cfg ( &solarenergy2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );    
}

void application_task ( void ) 
{   
    if ( SOLARENERGY2_OK == solarenergy2_get_status( &solarenergy2, &status ) )
    {
        if  ( SOLARENERGY2_OK == solarenergy2_get_bat_vtg_status( &solarenergy2, &vld_status ) )
        {
            display_status( );    
        }
    }
    Delay_ms( 5000 );
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
