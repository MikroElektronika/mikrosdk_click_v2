/*!
 * \file 
 * \brief Color9 Click example
 * 
 * # Description
 * This application collects data from the sensor and logs green, blue and red 
 * measurement readings.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialize the driver and test if the sensor is
 * present. If the ID read from the sensor is correct
 * execute the initialization procedure.
 * 
 * ## Application Task  
 * Wait for the color data to be available then read the data
 * and send it to the serial port.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "color9.h"

// ------------------------------------------------------------------ VARIABLES

static color9_t color9;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    color9_cfg_t cfg;

    uint8_t id;
    
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

    color9_cfg_setup( &cfg );
    COLOR9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    color9_init( &color9, &cfg );

    id = color9_read( &color9, COLOR9_PART_ID );

    if ( id == 0xB2 )
    {
        log_printf( &logger, "Register id 0x%x\r\n", id );
        color9_meas_rate( &color9, COLOR9_LS_MEAS_BITWIDTH_13, COLOR9_LS_MEAS_RATE_1000ms );
        color9_reg_ctrl( &color9, COLOR9_MAIN_CTRL_CS_MODE | COLOR9_MAIN_CTRL_LS_EN );
    }
    else
    {
        log_printf( &logger, "Error\r\n" );
        while ( 1 );
    }
}

void application_task ( void )
{
    uint8_t conv_complete;
    uint32_t measurement_data;

    conv_complete = color9_get_status_reg( &color9 );

    if ( conv_complete & 0x08 )
    {
        conv_complete = 0;
        measurement_data = color9_get_Ir( &color9 );
        log_printf( &logger, "Ir: %d\r\n", measurement_data );

        measurement_data = color9_get_green( &color9 );
        log_printf(&logger, "Green: %d\r\n", measurement_data);

        measurement_data = color9_get_blue( &color9 );
        log_printf(&logger, "Blue: %d\r\n", measurement_data);

        measurement_data = color9_get_red( &color9 );
        log_printf(&logger, "Red: %d\r\n", measurement_data);
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
