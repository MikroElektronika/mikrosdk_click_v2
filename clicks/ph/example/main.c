/*!
 * @file main.c
 * @brief pH Click Example.
 *
 * # Description
 * This example reads and processes data from pH clicks.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes UART driver, performing a factory reset of the device, disabling continuous read,
 * and performing calibration at the midpoint on the pH scale.
 *
 * ## Application Task
 * This example shows the capabilities of the pH Click board by performing a reading of the 
 * pH value of the substance in which the probe is submerged and displaying readings via the 
 * USART terminal.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "ph.h"

#define PROCESS_BUFFER_SIZE 200

static ph_t ph;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ph_cfg_t ph_cfg;  /**< Click config object. */

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
    ph_cfg_setup( &ph_cfg );
    PH_MAP_MIKROBUS( ph_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ph_init( &ph, &ph_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    ph_factory_rst( &ph, app_buf );
    Delay_ms( 1000 );
    
    ph_cont_read( &ph, 0, app_buf );
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "   -- Initialized --   \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "  Place probe into pH  \r\n" );
    log_printf( &logger, " neutral substance for \r\n" );
    log_printf( &logger, " mid point calibration \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    for ( uint8_t n_cnt = 0; n_cnt < 20; n_cnt++ )
    {
        Delay_ms( 1000 );
    }
    log_printf( &logger, " Starting calibration  \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    ph_perf_calib ( &ph, PH_CMD_CALIB_MID, 7.000, app_buf );
    Delay_ms( 1000 );
    log_printf( &logger, " Calibration done!     \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    
    log_printf( &logger, " - Application  task -\r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    ph_send_cmd( &ph, PH_CMD_DIS_RSP_CODES );
    Delay_ms( 1000 );
    ph_clr_log_buf( app_buf );
}

void application_task ( void ) 
{
    ph_send_cmd ( &ph, PH_CMD_SET_SNGL_READ );
    ph_response( &ph, app_buf );
    log_printf( &logger, " pH value: %s ", app_buf );
    log_printf( &logger, "-----------------------\r\n" );
    ph_clr_log_buf( app_buf );
    Delay_ms( 1000 );
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
