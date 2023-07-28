/*!
 * @file main.c
 * @brief AM/FM 2 Click example
 *
 * # Description
 * This example demonstrates the use of the AM/FM 2 Click board™.
 * The app represents a radio tuner that supports worldwide AM/FM bands 
 * and has features such as automatic frequency control, seek station, and volume control.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C module and log UART.
 * After driver initialization, the app sets the default configuration 
 * and searches and memorizes for a valid frequency of the 5 radio stations.
 *
 * ## Application Task
 * This example demonstrates the use of the AM/FM 2 Click board™.
 * The application switches all 5 previously memorized radio frequencies every 10 seconds.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "amfm2.h"

static amfm2_t amfm2;
static log_t logger;

static float mem_station_freq[ 5 ] = { 0 };
static uint8_t rsp_status = 0;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    amfm2_cfg_t amfm2_cfg;  /**< Click config object. */

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
    amfm2_cfg_setup( &amfm2_cfg );
    AMFM2_MAP_MIKROBUS( amfm2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == amfm2_init( &amfm2, &amfm2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMFM2_ERROR == amfm2_default_cfg ( &amfm2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    log_printf( &logger, " Begins searching for a valid frequency...\r\n" );
    log_printf( &logger, "--------------------\r\n" );
    for ( uint8_t n_cnt = 0; n_cnt < 5; n_cnt++ )
    {
        if ( AMFM2_OK == amfm2_seek_station( &amfm2, &rsp_status ) )
        {
            if ( AMFM2_RSP_STATUS_CTS & rsp_status )
            {
                log_printf( &logger, " The search is done.\r\n" );
                if ( AMFM2_OK == amfm2_get_tuning_freq( &amfm2, &mem_station_freq[ n_cnt ] ) )
                {
                    log_printf( &logger, " Frequency: %.2f MHz \r\n", mem_station_freq[ n_cnt ] );
                    log_printf( &logger, "- - - - - - - - - - \r\n" );
                    Delay_ms( 100 );
                }
            }
        }
    }
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms( 100 );
    
    if ( AMFM2_OK == amfm2_set_volume( &amfm2, AMFM2_SET_VOLUME_MAX, &rsp_status ) )
    {
        log_printf( &logger, " Set max volume \r\n" );
        Delay_ms( 100 );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    for ( uint8_t n_cnt = 0; n_cnt < 5; n_cnt++ )
    {
        if ( AMFM2_OK == amfm2_tuning_freq( &amfm2, mem_station_freq[ n_cnt ], &rsp_status ) )
        {
            log_printf( &logger, " FM Station %d \r\nFrequency: %.2f MHz\r\n", 
                       ( uint16_t ) ( n_cnt + 1 ), mem_station_freq[ n_cnt ] );
            log_printf( &logger, "--------------------\r\n" );
            Delay_ms( 10000 );
        }
    }
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
