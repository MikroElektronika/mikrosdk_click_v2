/*!
 * \file 
 * \brief Magneto4 Click example
 * 
 * # Description
 * Reads and logs magnetic field strength values
 * if magnetic field strength values bigger than 3000, 
 * start magnetic linear position mode,   
 * when moving the sensor from left to right the position for 1 step is reduced.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes Driver init and sets start encoder position on the zero.
 * Reads and logs magnetic field strength values.
 * For starting an encoder, it is necessary that the magnetic field strength 
 * is greater than 3000.
 * 
 * ## Application Task  
 * When moving the sensor from left to right, one step is added 
 * and when moving from right to left, the position for 1 step is reduced.
 * 
 * \author Luka Filipovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "magneto4.h"

// ------------------------------------------------------------------ VARIABLES

static magneto4_t magneto4;
static log_t logger;

static int32_t enc_position;
static int32_t old_position = 255;
static int16_t magnetic_field = 0;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    magneto4_cfg_t cfg;

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

    magneto4_cfg_setup( &cfg );
    MAGNETO4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    magneto4_init( &magneto4, &cfg );
    
    magneto4_default_cfg ( &magneto4 );
    
    log_printf( &logger, " --- Please, bring the magnet close ---\r\n" );

    while ( magnetic_field < MAGNETO4_MAX_MAGNETIC_FIELD_VALUE )
    {
        magnetic_field = magneto4_get_magnetic_field( &magneto4 );
        log_printf( &logger, " Magnetic field strength : %d\r\n", magnetic_field );
        Delay_ms( 1000 );
    }
    
    Delay_ms( 1500 );
    log_printf( &logger, " --- Magnetic Linear Position ---\r\n" );
}

void application_task ( void )
{
    //  Task implementation.
    
    magneto4_get_encoder_position( &magneto4 );
    
    enc_position = magneto4.encoder_position;

    if ( old_position != enc_position )
    {
        log_printf( &logger, " Encoder position : %d\r\n", enc_position );
        log_printf( &logger, " ------------------------\r\n" );
    }
    
    old_position = enc_position;
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
