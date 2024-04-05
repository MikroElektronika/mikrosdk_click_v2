/*!
 * @file main.c
 * @brief Ambient 23 Click example
 *
 * # Description
 * This example demonstrates the use of Ambient 23 click board by measuring 
 * the ambient light level in Lux.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, checks communication by reading part ID
 * and performs the click default configuration.
 *
 * ## Application Task
 * Measuring ambient light level by reading data from the Ambient 23 click board
 * and displaying it using UART Serial terminal.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "ambient23.h"

static ambient23_t ambient23;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient23_cfg_t ambient23_cfg;  /**< Click config object. */

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
    ambient23_cfg_setup( &ambient23_cfg );
    AMBIENT23_MAP_MIKROBUS( ambient23_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient23_init( &ambient23, &ambient23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    uint16_t part_id = 0;
    ambient23_reg_read( &ambient23, AMBIENT23_REG_DEVICE_ID, &part_id );
    if ( AMBIENT23_PART_ID != ( uint8_t ) part_id )
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    
    if ( AMBIENT23_ERROR == ambient23_default_cfg ( &ambient23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float data_tmp;
    
    ambient23_read_light_data( &ambient23, &data_tmp );
    log_printf( &logger, "Data: %.2f lux\r\n", data_tmp );
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
