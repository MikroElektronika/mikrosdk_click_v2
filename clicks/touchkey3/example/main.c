/*!
 * \file 
 * \brief TouchKey3 Click example
 * 
 * # Description
 * This click uses 7 capacitive sensing channels, with the #CHANGE pin routed to the INT pin of the mikroBUS™, 
 * so that an interrupt can be triggered if any of the sensors detect a touch event. 
 * This can be used to trigger an SPI read cycle only when the key is actually pressed, 
 * avoiding the need for constant polling of the sensor registers.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes click driver and performs a soft reset of the click.
 * 
 * ## Application Task  
 * Reads the status of the keys, and outputs a message if a key is touched.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "touchkey3.h"


// ------------------------------------------------------------------ VARIABLES

static touchkey3_t touchkey3;
static log_t logger;

static uint8_t return_data[ 2 ];
static uint8_t counter;
static uint8_t temp;
static uint8_t old_state;
static const uint16_t timeout_state = 1000;
static uint16_t timeout_cnt;

// ------------------------------------------------------ APPLICATION FUNCTIONS

uint8_t calculationt_index ( uint8_t data_in )
{
    uint8_t counter = 2;
    
    if ( data_in <= 2 )
    {
        return data_in;
    }
    
    while ( data_in > 2 )
    {
        data_in /= 2;
        counter++;
    }
    
    return counter;
}

void application_init ( void )
{
    log_cfg_t log_cfg;
    touchkey3_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    touchkey3_cfg_setup( &cfg );
    TOUCHKEY3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    touchkey3_init( &touchkey3, &cfg );

    touchkey3_reset( &touchkey3 );
    touchkey3_send_command( &touchkey3, TOUCHKEY3_CMD_RESET );
    timeout_cnt = timeout_state;
    
    Delay_ms ( 300 );
}

void application_task ( void )
{   
    touchkey3_send_request( &touchkey3, TOUCHKEY3_REQ_ALL_KEYS, &return_data );

    for ( counter = 0; counter < 7; counter++ )
    {
        if ( ( return_data[ 1 ] >> counter ) & 0x01 )
        {
            log_printf( &logger, "Touch detected on key %d\r\n", ( uint16_t )(counter+1) );
            Delay_ms ( 1000 );
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
