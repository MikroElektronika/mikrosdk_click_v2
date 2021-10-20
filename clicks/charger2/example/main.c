/*!
 * \file 
 * \brief Charger2 Click example
 * 
 * # Description
 * This app charges the battery.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device.
 * 
 * ## Application Task  
 * Reads the all necessary information for the battery charging status and logs this results on UART.
 * Repeats operation every second.
 * The LED diodes are used to indicate the Vcc presence when this voltage is in operating range, and to show the charging status.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "charger2.h"

// ------------------------------------------------------------------ VARIABLES

static charger2_t charger2;
static log_t logger;
uint32_t battery_data;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void results_logger ( charger2_t *ctx )
{
    switch ( ctx->unit_mode )
    {
        case CHARGER2_GAS_GAUGE_CHARGE_DATA :
        {
            log_printf( &logger, "Gas gauge charge data is: %u uV.h \r\n", battery_data );
            break;
        }
        case CHARGER2_CONV_NUMBER :
        {
            log_printf( &logger, "Number of conversions is: %u \r\n", battery_data );
            break;
        }
        case CHARGER2_SHUNT_VOLTAGE :
        {
            log_printf( &logger, "Voltage on shunt (CG pin): %u uV \r\n", battery_data );
            break;
        }
        case CHARGER2_BATTERY_VOLTAGE :
        {
            log_printf( &logger, "Battery voltage is: %u mV \r\n", battery_data );
            break;
        }
        case CHARGER2_TEMPERATURE :
        {
            log_printf( &logger, "Temperature is: %u Celsius \r\n", battery_data );
            break;
        }
        case CHARGER2_BATTERY_CURRENT :
        {
            log_printf( &logger, "Battery current is:  %u uA \r\n", battery_data );
            break;
        }
        default :
        {
            break;
        }
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    charger2_cfg_t cfg;

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

    charger2_cfg_setup( &cfg );
    CHARGER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    charger2_init( &charger2, &cfg );

    Delay_ms( 500 );
    
    charger2_reset( &charger2, CHARGER2_RESET_COUNTER_MODE );
    Delay_ms( 1000 );
    charger2_write_reg( &charger2, CHARGER2_REG_MODE, CHARGER2_AUTO_DETECT | CHARGER2_14_BITS_RESOLUTION | CHARGER2_OPERATING_MODE );
    log_printf( &logger, "Charger 2 is initialized \r\n" );
    log_printf( &logger, "------------------------------ \r\n" );
    Delay_ms( 300 );
}

void application_task ( void )
{
    charger2_read_data( &charger2, CHARGER2_GAS_GAUGE_CHARGE_DATA, &battery_data );
    results_logger( &charger2 );
    charger2_read_data( &charger2, CHARGER2_CONV_NUMBER, &battery_data );
    results_logger( &charger2 );
    charger2_read_data( &charger2, CHARGER2_SHUNT_VOLTAGE, &battery_data );
    results_logger( &charger2 );
    charger2_read_data( &charger2, CHARGER2_BATTERY_VOLTAGE, &battery_data );
    results_logger( &charger2 );
    charger2_read_data( &charger2, CHARGER2_TEMPERATURE, &battery_data );
    results_logger( &charger2 );
    charger2_read_data( &charger2, CHARGER2_BATTERY_CURRENT, &battery_data );
    results_logger( &charger2 );
    
    log_printf( &logger, "------------------------------ \r\n" );
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
