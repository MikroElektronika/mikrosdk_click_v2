/*!
 * \file 
 * \brief I2cMux3 Click example
 * 
 * # Description
 * This example demonstrates the use of I2C MUX 3 Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes the driver, preforms hardware reset, then enables channel 0 and 
 * makes an initial log.
 * 
 * ## Application Task  
 * Reads the device ID of a 6DOF IMU 12 Click (dev ID: 0x24) and displays it 
 * on the USB UART each second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "i2cmux3.h"

// ------------------------------------------------------------------ VARIABLES

static i2cmux3_t i2cmux3;
static log_t logger;

uint8_t id_val;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    i2cmux3_cfg_t cfg;

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

    i2cmux3_cfg_setup( &cfg );
    I2CMUX3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cmux3_init( &i2cmux3, &cfg );
    Delay_ms ( 100 );
    
    i2cmux3_hw_rst( &i2cmux3 );
    Delay_ms ( 100 );
    i2cmux3_ch_sel( &i2cmux3, 0 );
    log_printf( &logger, " Please connect a 6DOF IMU 12 Click to channel 0\r\n" );
    log_printf( &logger, "-------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    i2cmux3_rd_slv ( &i2cmux3, 0x68, 0x00, &id_val, 1 );
    log_printf( &logger, " The Click device ID is:  0x%.2X \r\n", ( uint16_t ) id_val );
    log_printf( &logger, "-------------------------------\r\n" );
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
