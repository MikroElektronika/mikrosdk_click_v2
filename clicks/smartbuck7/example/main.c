/*!
 * @file main.c
 * @brief Smart Buck 7 Click example
 *
 * # Description
 * This example demonstrates the use of the Smart Buck 7 Click board. The application cyclically enables 
 * different combinations of the four buck converter outputs (1.2V, 1.8V, 2.5V, and 3.3V) and logs which 
 * outputs are currently active. It also monitors the PG (Power Good) pin and logs any fault conditions, 
 * including undervoltage and over-temperature events.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the Smart Buck 7 Click driver, and applies the default configuration.
 *
 * ## Application Task
 * Cycles through various buck output combinations, logs the enabled outputs, 
 * checks the PG pin for fault indication, and logs any detected fault status.
 *
 * @note
 * Ensure all outputs are properly loaded and that the input voltage is within recommended levels 
 * to evaluate fault detection reliably.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "smartbuck7.h"

static smartbuck7_t smartbuck7;
static log_t logger;

/**
 * @brief Smart Buck 7 display status function.
 * @details This function parses and logs all detected status flags from the Smart Buck 7 Click board
 * including over-temperature and power-good conditions.
 * @param[in] status : Status register structure.
 * See #smartbuck7_status_t object definition for detailed explanation.
 * @return None.
 * @note This function outputs human-readable messages via the logger for each active status flag.
 */
static void smartbuck7_display_status ( smartbuck7_status_t status );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartbuck7_cfg_t smartbuck7_cfg;  /**< Click config object. */

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
    smartbuck7_cfg_setup( &smartbuck7_cfg );
    SMARTBUCK7_MAP_MIKROBUS( smartbuck7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == smartbuck7_init( &smartbuck7, &smartbuck7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SMARTBUCK7_ERROR == smartbuck7_default_cfg ( &smartbuck7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    smartbuck7_status_t status;
    static uint8_t buck_en = SMARTBUCK7_BUCK_4;
    if ( smartbuck7_get_pg_pin ( &smartbuck7 ) )
    {
        log_printf( &logger, "\r\n Fault indication detected via PG pin!\r\n" );
        if ( SMARTBUCK7_OK == smartbuck7_read_status ( &smartbuck7, &status ) )
        {
            smartbuck7_display_status ( status );
        }
        smartbuck7_clear_status( &smartbuck7 );
    }
    if ( buck_en > SMARTBUCK7_BUCK_ALL )
    {
        if ( SMARTBUCK7_OK == smartbuck7_disable_buck ( &smartbuck7, SMARTBUCK7_BUCK_ALL ) )
        {
            log_printf( &logger, "\r\n Outputs enabled: - NONE -\r\n" );
            buck_en = SMARTBUCK7_BUCK_4;
        }
    }
    else if ( SMARTBUCK7_OK == smartbuck7_enable_buck ( &smartbuck7, buck_en ) )
    {
        log_printf( &logger, "\r\n Outputs enabled: -" );
        if ( buck_en & SMARTBUCK7_BUCK_3 )
        {
            log_printf( &logger, " 3.3V -" );
        }
        if ( buck_en & SMARTBUCK7_BUCK_1 )
        {
            log_printf( &logger, " 1.2V -" );
        }
        if ( buck_en & SMARTBUCK7_BUCK_2 )
        {
            log_printf( &logger, " 1.8V -" );
        }
        if ( buck_en & SMARTBUCK7_BUCK_4 )
        {
            log_printf( &logger, " 2.5V -" );
        }
        log_printf( &logger, "\r\n" );
        buck_en = ( buck_en << 1 ) | SMARTBUCK7_BUCK_4;
    }
    Delay_ms ( 1000 );
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

static void smartbuck7_display_status ( smartbuck7_status_t status )
{
    if ( !status.status_1 )
    {
        if ( !( status.status_1 & SMARTBUCK7_STATUS_1_PGBUCK4 ) )
        {
            log_printf ( &logger, " Buck 4 low output voltage\r\n" );
        }
        if ( !( status.status_1 & SMARTBUCK7_STATUS_1_PGBUCK3 ) )
        {
            log_printf ( &logger, " Buck 3 low output voltage\r\n" );
        }
        if ( !( status.status_1 & SMARTBUCK7_STATUS_1_PGBUCK2 ) )
        {
            log_printf ( &logger, " Buck 2 low output voltage\r\n" );
        }
        if ( !( status.status_1 & SMARTBUCK7_STATUS_1_PGBUCK1 ) )
        {
            log_printf ( &logger, " Buck 1 low output voltage\r\n" );
        }
    }
    if ( status.status_2 )
    {
        if ( status.status_1 & SMARTBUCK7_STATUS_2_OTWARNING )
        {
            log_printf ( &logger, " Die temperature early warning\r\n" );
        }
        if ( status.status_1 & SMARTBUCK7_STATUS_2_OTEMPP )
        {
            log_printf ( &logger, " Over temperature fault\r\n" );
        }
    }
}

// ------------------------------------------------------------------------ END
