/*!
 * \file 
 * \brief Pollution Click example
 * 
 * # Description
 * Pollution click carries the VOC gas sensor and has high sensitivity to organic gases 
 * such as methanal (also known as formaldehyde), benzene, alcohol, toluene, etc.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Application Init performs Logger and Click initialization.
 * 
 * ## Application Task  
 * This is an example which demonstrates the usage of Pollution Click board.
 * Pollution Click reads ADC value, load voltage from ADC value, and reads corrected 
 * resistance of the sensor where results are being sent to the UART terminal 
 * where you can track changes.
 * 
 * \author Mihajlo Djordjevic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pollution.h"

float value_volt;
float value_res;

// ------------------------------------------------------------------ VARIABLES

static pollution_t pollution;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pollution_cfg_t cfg;

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
    Delay_ms ( 1000 );

    //  Click initialization.

    pollution_cfg_setup( &cfg );
    POLLUTION_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pollution_init( &pollution, &cfg );
    
    log_printf( &logger, "-------------------------------------\r\n" );
    log_printf( &logger, "---------- Pollution Click ----------\r\n" );
    log_printf( &logger, "-------------------------------------\r\n" );
    Delay_ms ( 1000 );
    
    pollution_default_cfg( &pollution );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "--------- ADC Initializated ---------\r\n" );
    log_printf( &logger, "-------------------------------------\r\n" );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    pollution_data_t tmp;
    
    tmp = pollution_generic_read( &pollution );
    log_printf( &logger, " ADC value            : %u ppm\r\n", tmp );
    Delay_ms( 1000 );
    
    value_volt = pollution_measure_load_voltage( &pollution );
    log_printf( &logger, " Load voltage         : %.2f V\r\n", value_volt );
    Delay_ms( 1000 );
    
    value_res = pollution_get_corrected_resistance( &pollution );
    log_printf( &logger, " Corrected resistance : %.2f kOhm\r\n", value_res );
    log_printf( &logger, "-------------------------------------\r\n" );
    Delay_ms( 1000 );
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
