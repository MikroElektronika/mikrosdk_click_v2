/*!
 * @file main.c
 * @brief IR Sense 4 Click example
 *
 * # Description
 * This example demonstrates the use of theIR Sense 4 Click board™, 
 * by showing parameters for detection of the presence and motion as well as ambient temperature.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C or SPI module and log UART.
 * After driver initialization, the app sets the default configuration.
 *
 * ## Application Task
 * The application checks for the human presence and motion detection 
 * and display output data, using embedded algorithms, and ambient temperature in degrees Celsius.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "irsense4.h"

static irsense4_t irsense4;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irsense4_cfg_t irsense4_cfg;  /**< Click config object. */

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
    irsense4_cfg_setup( &irsense4_cfg );
    IRSENSE4_MAP_MIKROBUS( irsense4_cfg, MIKROBUS_1 );
    err_t init_flag = irsense4_init( &irsense4, &irsense4_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( IRSENSE4_ERROR == irsense4_default_cfg ( &irsense4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ------------------------\r\n" );
}

void application_task ( void )
{ 
    static float temperature = 0.0;
    static int16_t detection_data = 0;
    static uint8_t status = 0;
    while ( IRSENSE4_OK != irsense4_wait_new_data_ready( &irsense4 ) );
    if ( IRSENSE4_OK == irsense4_get_status( &irsense4, &status ) )
    {
        if ( status & IRSENSE4_STATUS_DETECT_FLAG )
        {
            if ( ( IRSENSE4_OK == irsense4_get_presence_data( &irsense4, &detection_data ) ) && 
                 ( status & IRSENSE4_STATUS_PRES_FLAG ) )
            {
                log_printf( &logger, " Presence: %d \r\n", detection_data );
            }
    
            if ( ( IRSENSE4_OK == irsense4_get_motion_data( &irsense4, &detection_data ) ) && 
                 ( status & IRSENSE4_STATUS_MOT_FLAG ) )
            {
                log_printf( &logger, " Motion: %d \r\n", detection_data );
            }
            
            if ( IRSENSE4_OK == irsense4_get_amb_temperature( &irsense4, &temperature ) )
            {
                log_printf( &logger, " Temperature: %.2f C\r\n", temperature );
            }
            log_printf( &logger, " ------------------------\r\n" );
            Delay_ms ( 100 );
        }
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
