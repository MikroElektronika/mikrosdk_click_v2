/*!
 * @file main.c
 * @brief Proximity12 Click example
 *
 * # Description
 * This function demonstrates the use of Proximity 12 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads the proximity and ALS values and displays the results on the USB UART 
 * approximately every 100ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "proximity12.h"

static proximity12_t proximity12;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    proximity12_cfg_t proximity12_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.
    proximity12_cfg_setup( &proximity12_cfg );
    PROXIMITY12_MAP_MIKROBUS( proximity12_cfg, MIKROBUS_1 );
    err_t init_flag = proximity12_init( &proximity12, &proximity12_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    init_flag = proximity12_default_cfg ( &proximity12 );
    if ( PROXIMITY12_ERROR == init_flag ) 
    {
        log_error( &logger, " Default Cfg Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint16_t prox_data = 0;
    proximity12_als_data_t als;
    err_t error_flag = proximity12_read_proximity ( &proximity12, &prox_data );
    error_flag |= proximity12_read_als ( &proximity12, &als );

    if ( PROXIMITY12_OK == error_flag )
    {
        log_printf( &logger, " - Proximity data -\r\n" );
        log_printf( &logger, " Proximity: %u\r\n", prox_data );
        log_printf( &logger, " - ALS data -\r\n" );
        log_printf( &logger, " Clear: %lu - Red: %lu - Green: %lu - Blue: %lu\r\n", als.clear,
                                                                                    als.red,
                                                                                    als.green, 
                                                                                    als.blue );
        
        log_printf( &logger, " Leakage: %lu - Wideband: %lu - IR1: %lu - IR2: %lu\r\n\r\n", als.leakage,
                                                                                            als.wideband,
                                                                                            als.ir1, 
                                                                                            als.ir2 );
    }
    Delay_ms ( 100 );
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
