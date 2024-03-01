/*!
 * @file main.c
 * @brief 7-SEG 2 Click example
 *
 * # Description
 * The example demonstrates the use of the 7-SEG 2 click board by displaying
 * a counter number [0.00-9.99] which is incremented by 0.01 at a desired rate.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs default configuration, sets the device
 * in output enabled mode and checks communication by reading device ID.
 *
 * ## Application Task
 * Writes a counter number [0.00-9.99] to the display as frequently as possible.
 * The displayed counter value is incremented by 0.01 at a rate defined with
 * the C7SEG2_NUM_COUNTER_RATE macro.
 *
 * @author MikroE Team
 *
 */

#include "board.h"
#include "log.h"
#include "c7seg2.h"

// Number of display updates (see 7-SEG 2 refresh rate setting) before the displayed counter is incremented.
#define C7SEG2_NUM_COUNTER_RATE             10

static c7seg2_t c7seg2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c7seg2_cfg_t c7seg2_pnp_cfg;  /**< Click config object. */

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
    c7seg2_cfg_setup( &c7seg2_pnp_cfg );
    C7SEG2_MAP_MIKROBUS( c7seg2_pnp_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == c7seg2_init( &c7seg2, &c7seg2_pnp_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    uint8_t device_id = 0;
    c7seg2_read_reg( &c7seg2, C7SEG2_REG_DEVICE_ID, &device_id );
    if ( C7SEG2_DEVICE_ID != device_id )
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    
    if ( C7SEG2_ERROR == c7seg2_default_cfg ( &c7seg2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint16_t counter = 0;
    static uint16_t time = 0;
    
    c7seg2_write_number( &c7seg2, counter, C7SEG2_DP_AT_SEGMENT_2 );
    
    if ( ++time >= C7SEG2_NUM_COUNTER_RATE ) 
    {
        if ( ++counter > C7SEG2_MAX_NUMBER )
        {
            counter = 0;
        }
        time = 0;
    }
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
