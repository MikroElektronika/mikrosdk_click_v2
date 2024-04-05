/*!
 * \file 
 * \brief AdSwio2 Click example
 * 
 * # Description
 * This Click is a quad-channel software configurable input/output solution for building 
 * and process control application. The AD-SWIO 2 Click contains four 13-bit DACs, one 
 * per chanal, and 16-bit Σ-∆ ADC. These options give a lot of flexibility in choosing 
 * functionality for analog output, analog input, digital input, resistance temperature 
 * detector (RTD), and thermocouple measurements integrated into a single chip solution 
 * with a serial peripheral interface (SPI).
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Performs a hardware reset of the click board and
 * executes a default configuration that enables channel A and sets it to measure voltage
 * input in the range from 0V to 10V, with 4800 SPS.
 * 
 * ## Application Task  
 * Waits for the data ready and then reads the results of ADC conversion from channel A
 * and if response is ok, then prints the results on the uart console.
 *  
 * ## Additional Functions
 *
 * - void application_default_handler ( uint8_t *err_msg ) - Sends an error report messages from click
 * driver to initialized console module. It must be set using adswio2_set_handler function.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "adswio2.h"

// ------------------------------------------------------------------ VARIABLES

static adswio2_t adswio2;
static log_t logger;

static uint8_t adswio2_rdy;
static adswio2_err_t adswio2_err;
static uint16_t adswio2_ch_a;
static uint16_t timeout;
static float adswio2_res;

const uint16_t ADSWIO2_RANGE_VOLT_MV = 10000;
const uint32_t ADSWIO2_RANGE_RESOLUTION = 65536;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void application_default_handler ( uint8_t *err_msg )
{
    char *err_ptr = err_msg;

    log_printf( &logger, "\r\n" );
    log_printf( &logger, "[ERROR] : %s", err_ptr );
    log_printf( &logger, "\r\n" );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    adswio2_cfg_t cfg;

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

    adswio2_cfg_setup( &cfg );
    ADSWIO2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adswio2_init( &adswio2, &cfg );
    Delay_ms ( 100 );
    
    adswio2_default_cfg( &adswio2 );
    Delay_ms ( 1000 );

    adswio2_rdy  = DUMMY;
    adswio2_ch_a = DUMMY;
    adswio2_res  = DUMMY;
    adswio2_err  = ADSWIO2_ERR_STATUS_OK;
    log_printf( &logger, " AD-SWIO 2 click initialization done \r\n");
    log_printf( &logger, "************************************\r\n");
}

void application_task ( void )
{
    timeout = 0;
    do
    {
        Delay_1ms( );
        timeout++;
        adswio2_rdy = adswio2_status_pin_ready( &adswio2 );
        if ( timeout > 3000 ) 
        {
            timeout = 0;
            log_printf( &logger, " Reinitializing...");
            adswio2_default_cfg( &adswio2 );
            log_printf( &logger, "Done\r\n");
        }
    }
    while ( adswio2_rdy != 0 );
    
    adswio2_err = adswio2_get_conv_results( &adswio2, ADSWIO2_SETUP_CONV_EN_CHA, &adswio2_ch_a );
    
    if ( adswio2_err == ADSWIO2_ERR_STATUS_OK )
    {
        adswio2_res = adswio2_ch_a;
        adswio2_res /= ADSWIO2_RANGE_RESOLUTION;
        adswio2_res *= ADSWIO2_RANGE_VOLT_MV;
        adswio2_ch_a = adswio2_res;

        log_printf( &logger, " Voltage from channel A: %d mV\r\n", adswio2_ch_a );
        
        log_printf( &logger, "-----------------------------------\r\n\r\n" );
        Delay_ms ( 200 );
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
