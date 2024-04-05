/*!
 * \file 
 * \brief Oximeter3 Click example
 * 
 * # Description
 * This example demonstrates the use of Oximeter 3 Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver, checks the device ID then configures the device for the selected mode.
 * 
 * ## Application Task  
 * Depending on the selected mode it reads heart rate data (OXIMETER3_HEART_RATE mode) or
 * values of proximity and ambient light sensor (OXIMETER3_PROX or OXIMETER3_ALS modes).
 * All data is being logged on USB UART where you can track their changes.
 * 
 * @note
 * In the case of heart rate, please use a Serial Plot application for data plotting.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "oximeter3.h"

// ------------------------------------------------------------------ VARIABLES

static oximeter3_t oximeter3;
static log_t logger;

uint8_t dev_mode = 0;
uint16_t rd_val = 0;
uint16_t counter = 2500;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    oximeter3_cfg_t cfg;

    uint8_t dev_status;

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

    oximeter3_cfg_setup( &cfg );
    OXIMETER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    oximeter3_init( &oximeter3, &cfg );

    dev_status = oximeter3_generic_read( &oximeter3, OXIMETER3_REG_PRODUCT_ID );
    
    if ( dev_status != OXIMETER3_ID_VAL )
    {
        log_printf( &logger, " *****  ERROR!  ***** \r\n" );
        for ( ; ; );
    }

    dev_mode = OXIMETER3_HEART_RATE;
    
    oximeter3_generic_write( &oximeter3, OXIMETER3_REG_COMMAND,
                                         OXIMETER3_CMD_MEASUREMENT_DISABLE );
    
    oximeter3_generic_write( &oximeter3, OXIMETER3_REG_INTERRUPT_CTRL,
                                         OXIMETER3_INT_STATUS_PROX );
    
    if ( OXIMETER3_HEART_RATE == dev_mode )
    {
        oximeter3_generic_write( &oximeter3, OXIMETER3_REG_LED_CURRENT, 
                                             OXIMETER3_LED_CURR_MID );
        oximeter3_generic_write( &oximeter3, OXIMETER3_REG_PROX_MODULATOR_TIMING,
                                             OXIMETER3_PROX_TIMING_FREQ_390p625_KHZ );
    }
    else
    {
        oximeter3_generic_write( &oximeter3, OXIMETER3_REG_LED_CURRENT, 
                                             OXIMETER3_LED_CURR_MIN );
        oximeter3_generic_write( &oximeter3, OXIMETER3_REG_PROX_MODULATOR_TIMING,
                                             OXIMETER3_PROX_TIMING_FREQ_3p125_MHZ );
    }
    
    oximeter3_generic_write( &oximeter3, OXIMETER3_REG_PROX_RATE,
                                         OXIMETER3_PROX_RATE_250_MPS );

    oximeter3_generic_write( &oximeter3, OXIMETER3_REG_COMMAND,
                                         OXIMETER3_CMD_MEASUREMENT_ENABLE |
                                         OXIMETER3_CMD_PROX_PERIODIC_MEASUREMENT_ENABLE |
                                         OXIMETER3_CMD_ALS_PERIODIC_MEASUREMENT_ENABLE );

    log_printf( &logger, " ***** APP TASK ***** \r\n" );
}

void application_task ( void )
{
    if ( OXIMETER3_HEART_RATE == dev_mode )
    {
        if( !oximeter3_get_int_status( &oximeter3 ) )
        {
            rd_val = oximeter3_read_value( &oximeter3, OXIMETER3_PROX );
            oximeter3_generic_write( &oximeter3, OXIMETER3_REG_INTERRUPT_STATUS, 
                                                 OXIMETER3_INT_STATUS_PROX );
            
            counter++;
            if ( rd_val > 10000 )
            {
                log_printf( &logger, "%u\r\n", rd_val );
                counter = 2500;
            }
            else if ( counter > 2500 )
            {
                log_printf( &logger, "Please place your index finger on the sensor.\r\n" );
                counter = 0;
            }
        }
    }
    else if ( OXIMETER3_PROX == dev_mode || OXIMETER3_ALS == dev_mode )
    {
        if( !oximeter3_get_int_status( &oximeter3 ) )
        {
            rd_val = oximeter3_read_value( &oximeter3, OXIMETER3_PROX );
            oximeter3_generic_write( &oximeter3, OXIMETER3_REG_INTERRUPT_STATUS, 
                                                 OXIMETER3_INT_STATUS_PROX );
            
            log_printf( &logger, " * Proximity: %u \r\n", rd_val );
        
            rd_val = oximeter3_read_value( &oximeter3, OXIMETER3_ALS );
            log_printf( &logger, " * ALS: %u \r\n", rd_val );
            
            log_printf( &logger, "******************** \r\n" );
            
            Delay_ms ( 500 );
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
