/*!
 * \file 
 * \brief I2Cisolator Click example
 * 
 * # Description
 * This is an example which demonstrates the use of I2C Isolator Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - I2C,
 * sets configuration of TMP007 sensor on IrThermo 2 click and start to write log.
 * 
 * ## Application Task  
 * In this example we use IrThermo 2 click measures the temperature 
 * and calculate the temperature in degrees Celsius [ C ].
 * Results are being sent to the USART Terminal where you can track their changes.
 * All data logs on usb uart for approximately every 1 sec when the data value changes.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "i2cisolator.h"

// ------------------------------------------------------------------ VARIABLES

static i2cisolator_t i2cisolator;
static log_t logger;
static float temperature;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void i2cisolator_get_temperature ( void )
{
    uint8_t temp_data[ 2 ];
    uint16_t temp;
    
    i2cisolator_generic_read( &i2cisolator, I2CISOLATOR_IRTHERMO2_OBJECT_TEMPERATURE, temp_data, 2 );
    
    temp = temp_data[ 0 ];
    temp <<= 8;
    temp |= temp_data[ 1 ];
    temp >>= 2;
    temperature = ( float ) temp;
    temperature *= 0.03125;
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    i2cisolator_cfg_t cfg;
    uint8_t tmp;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    i2cisolator_cfg_setup( &cfg );
    I2CISOLATOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cisolator_init( &i2cisolator, &cfg );

    log_printf( &logger, "    Driver  Initialized\r\n" );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms( 100 );
    

    tmp = I2CISOLATOR_IRTHERMO2_CONFIGURATION 
        | I2CISOLATOR_IRTHERMO2_CFG_MODEON 
        | I2CISOLATOR_IRTHERMO2_CFG_ALERTEN 
        | I2CISOLATOR_IRTHERMO2_CFG_TRANSC 
        | I2CISOLATOR_IRTHERMO2_CFG_16SAMPLE;
    i2cisolator_generic_write( &i2cisolator, I2CISOLATOR_IRTHERMO2_CONFIGURATION, &tmp, 1 );

    tmp = I2CISOLATOR_IRTHERMO2_STATUS_MASK_AND_ENABLE 
        | I2CISOLATOR_IRTHERMO2_STAT_ALERTEN 
        | I2CISOLATOR_IRTHERMO2_STAT_CRTEN;
    i2cisolator_generic_write( &i2cisolator, I2CISOLATOR_IRTHERMO2_STATUS_MASK_AND_ENABLE, &tmp, 1 );    
    
    log_printf( &logger, "       Configuration\r\n" );
    log_printf( &logger, "      IrThermo 2 Click\r\n" );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    i2cisolator_get_temperature( );   
    
    log_printf( &logger, " Temperature : %0.2f C\r\n", temperature );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms( 1000 );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}


// ------------------------------------------------------------------------ END
