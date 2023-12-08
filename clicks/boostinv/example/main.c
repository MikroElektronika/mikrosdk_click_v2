/*!
 * \file 
 * \brief BoostInv Click example
 * 
 * # Description
 * Changes the positive and negative output voltage. Input Voltage 3.3V.
 * Positive output voltage goes from 3200mV, 7750mV, 12000mV and 7750mV.
 * Negative output voltage goes from -1450mV, -6700mV, -11050mV and -6700mV.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C module and sets EN ( RST ) pin as output.
 * 
 * ## Application Task  
 * Changes the positive and negative output voltage every 5 sec.
 * 
 * \author Luka FIlipovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "boostinv.h"

// ------------------------------------------------------------------ VARIABLES

static boostinv_t boostinv;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    boostinv_cfg_t cfg;

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

    boostinv_cfg_setup( &cfg );
    BOOSTINV_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    boostinv_init( &boostinv, &cfg );
    
    boostinv_default_cfg ( &boostinv );
    log_printf( &logger, "     Boost INV Click\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    // Sets Positive output voltage
    
    log_printf( &logger, " Positive output voltage \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "          3200 mV\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    boostinv_set_positive_voltage( &boostinv, BOOSTINV_VOLTAGE_POSITIVE_3200_mV );
    Delay_ms( 5000 );
    
    log_printf( &logger, "          7750 mV\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    boostinv_set_positive_voltage( &boostinv, BOOSTINV_VOLTAGE_POSITIVE_7750_mV );
    Delay_ms( 5000 );
    
    log_printf( &logger, "        12000 mV\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    boostinv_set_positive_voltage( &boostinv, BOOSTINV_VOLTAGE_POSITIVE_12000_mV );
    Delay_ms( 5000 );
    
    log_printf( &logger, "         7750 mV\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    boostinv_set_positive_voltage( &boostinv, BOOSTINV_VOLTAGE_POSITIVE_7750_mV );
    Delay_ms( 5000 );
    
    // Sets Negative output voltage
    
    log_printf( &logger, " Negative output voltage \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "        -1450 mV\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    boostinv_set_negative_voltage( &boostinv, BOOSTINV_VOLTAGE_NEGATIVE_1450_mV );
    Delay_ms( 5000 );
    
    log_printf( &logger, "       - 6700 mV\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    boostinv_set_negative_voltage( &boostinv, BOOSTINV_VOLTAGE_NEGATIVE_6700_mV );
    Delay_ms( 5000 );
    
    log_printf( &logger, "       - 11050 mV\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    boostinv_set_negative_voltage( &boostinv, BOOSTINV_VOLTAGE_NEGATIVE_11050_mV );
    Delay_ms( 5000 );
    
    log_printf( &logger, "       - 6700 mV\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    boostinv_set_negative_voltage( &boostinv, BOOSTINV_VOLTAGE_NEGATIVE_6700_mV );
    Delay_ms( 5000 );
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
