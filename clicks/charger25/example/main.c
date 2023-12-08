/*!
 * @file main.c
 * @brief Charger 25 Click example
 *
 * # Description
 * This example demonstrates the use of Charger 25 click board™ 
 * by enabling battery charging and displaying battery voltage and charging status.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, the app executes a default configuration.
 *
 * ## Application Task
 * The demo application reads and displays the results of the battery voltage, 
 * minimal system voltage, battery voltage limit and charging status.
 * Results are being sent to the UART Terminal, where you can track their changes.
 * 
 * ## Additional Function
 * - static void charger25_display_status ( void )
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "charger25.h"

static charger25_t charger25;
static log_t logger;

static charger25_status_t status;

/**
 * @brief Charger 25 displays the status.
 * @details This function displays  the charging status.
 * @note None.
 */
static void charger25_display_status ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger25_cfg_t charger25_cfg;  /**< Click config object. */

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
    charger25_cfg_setup( &charger25_cfg );
    CHARGER25_MAP_MIKROBUS( charger25_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == charger25_init( &charger25, &charger25_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CHARGER25_ERROR == charger25_default_cfg ( &charger25 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ----------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    static uint16_t vtg_data = 0;
    if ( CHARGER25_OK == charger25_get_status ( &charger25, &status ) )
    {
        charger25_display_status( );
    }
    Delay_ms( 100 );
    
    if ( CHARGER25_OK == charger25_get_vbat( &charger25, &vtg_data ) )
    {
        log_printf( &logger, " VBAT: %u [mV]\r\n", vtg_data );
    }
    Delay_ms( 100 );
    
    if ( CHARGER25_OK == charger25_get_vsys_min( &charger25, &vtg_data ) )
    {
        log_printf( &logger, " VMIN: %u [mV]\r\n", vtg_data );
    }
    Delay_ms( 100 );
    
    if ( CHARGER25_OK == charger25_get_vbat_lim( &charger25, &vtg_data ) )
    {
        log_printf( &logger, " VLIM: %u [mV]\r\n", vtg_data );
    }
    log_printf( &logger, " ----------------\r\n" );
    Delay_ms( 1000 );
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

static void charger25_display_status ( void ) 
{
    log_printf( &logger, " Charge Status: " );
    switch ( status.chg_stat )
    {
        case CHARGER25_CH_STAT_NOT_CHARGING: 
        {
            log_printf( &logger, " Not Charging\r\n" );
            break;
        }
        case CHARGER25_CH_STAT_TRICKLE_CHARGE: 
        {
            log_printf( &logger, " Trickle Charge\r\n" );
            break;
        }
        case CHARGER25_CH_STAT_PRE_CHARGE: 
        {
            log_printf( &logger, "  Pre-charge\r\n" );
            break;
        }
        case CHARGER25_CH_STAT_FAST_CHARGE: 
        {
            log_printf( &logger, " Fast charge \r\n" );
            break;
        }
        case CHARGER25_CH_STAT_TAPER_CHARGE: 
        {
            log_printf( &logger, " Taper Charge\r\n" );
            break;
        }
        case CHARGER25_CH_STAT_TIMER_ACT_CHARGING: 
        {
            log_printf( &logger, " Top-off Timer Active Charging\r\n" );
            break;
        }
        case CHARGER25_CH_STAT_CHARGE_TERMIN_DONE: 
        {
            log_printf( &logger, " Charge Termination Done\r\n" );
            break;
        }
        default: 
        {
            log_printf( &logger, " Unknown\r\n" );
            break;
        }
    }
    
    log_printf( &logger, " Battery Status: " );
    if ( status.vbat_present_stat )
    {
        log_printf( &logger, " Battery present\r\n" );
    }
    else
    {
        log_printf( &logger, " No battery\r\n" );
    }
    log_printf( &logger, " - - - - - - - - \r\n" );
}

// ------------------------------------------------------------------------ END
