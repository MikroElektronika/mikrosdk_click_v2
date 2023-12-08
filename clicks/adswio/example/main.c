/*!
 * \file 
 * \brief AdSwio Click example
 * 
 * # Description
 * This click provides a fully integrated single chip solution for input and output operation. 
 * The AD-SWIO Click contains four 13-bit DACs, one per chanal, and 16-bit Σ-∆ ADC. 
 * These options give a lot of flexibility in choosing functionality for analog output, 
 * analog input, digital input, resistance temperature detector (RTD), and thermocouple 
 * measurements integrated into a single chip solution with a serial peripheral interface (SPI).
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
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "adswio.h"

// ------------------------------------------------------------------ VARIABLES

static adswio_t adswio;
static log_t logger;

static uint8_t adswio_rdy;
static adswio_err_t adswio_err;
static uint16_t adswio_ch_a;
static float adswio_res;

const uint16_t ADSWIO_RANGE_VOLT_MV = 10000;
const uint32_t ADSWIO_RANGE_RESOLUTION = 65536;

// ------------------------------------------------------ ADDITIONAL FUNCTIONS

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
    adswio_cfg_t cfg;

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

    adswio_cfg_setup( &cfg );
    ADSWIO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adswio_init( &adswio, &cfg );
    Delay_ms( 100 );

    adswio_default_cfg( &adswio );
    Delay_ms( 1000 );

    adswio_rdy  = DUMMY;
    adswio_ch_a = DUMMY;
    adswio_res  = DUMMY;
    adswio_err  = ADSWIO_ERR_STATUS_OK;

    log_printf( &logger, " AD-SWIO click initialization done \r\n");
    log_printf( &logger, "************************************\r\n");
}

void application_task ( void )
{
    uint16_t timeout = 0;
    do
    {
        Delay_1ms( );
        timeout++;
        adswio_rdy = adswio_status_pin_ready( &adswio );
        if ( timeout > 3000 ) 
        {
            timeout = 0;
            log_printf( &logger, " Reinitializing...");
            adswio_default_cfg( &adswio );
            log_printf( &logger, "Done\r\n");
        }
    }
    while ( adswio_rdy != 0 );

    adswio_err = adswio_get_conv_results( &adswio, ADSWIO_SETUP_CONV_EN_CHA, &adswio_ch_a );

    if ( adswio_err == ADSWIO_ERR_STATUS_OK )
    {
        adswio_res = adswio_ch_a;
        adswio_res /= ADSWIO_RANGE_RESOLUTION;
        adswio_res *= ADSWIO_RANGE_VOLT_MV;
        adswio_ch_a = adswio_res;

        log_printf( &logger, " Voltage from channel A: %d mV\r\n", adswio_ch_a );
        
        log_printf( &logger, "-----------------------------------\r\n\r\n" );
        Delay_ms( 200 );
    }
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
