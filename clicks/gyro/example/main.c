/*!
 * \file 
 * \brief Gyro Click example
 * 
 * # Description
 * This example displays values of Gyro sensor (x, y, z axis).
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver, initialize L3GD20 register and start write log.
 * 
 * ## Application Task  
 * (code snippet) This is a example which demonstrates the use of Gyro Click board.
 *  Measured Gyro coordinates ( X-axis, Y-axis, Z-axis ) and temperature in degrees C are being sent
 *  to the Usart Terminal where you can track their changes.
 *  All data logs on usb uart for every 2 sec.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "gyro.h"

// ------------------------------------------------------------------ VARIABLES

static gyro_t gyro;
static log_t logger;
static int16_t gyrox;
static int16_t gyroy;
static int16_t gyroz;
static int8_t temperature;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    gyro_cfg_t cfg;

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

    gyro_cfg_setup( &cfg );
    GYRO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gyro_init( &gyro, &cfg );
    gyro_default_cfg ( &gyro);
}

void application_task ( void )
{
    //  Task implementation.

    gyro_read_gyro(  &gyro, &gyrox,  &gyroy, &gyroz );

    log_printf( &logger, " Axis X : %d \r\n", gyrox );
    log_printf( &logger, " Axis Y : %d \r\n", gyroy );
    log_printf( &logger, " Axis Z : %d \r\n", gyroz );
    log_printf( &logger, "*****************************\r\n" );

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


// ------------------------------------------------------------------------ END
