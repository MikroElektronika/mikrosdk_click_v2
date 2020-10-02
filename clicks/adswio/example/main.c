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
 * executes a default configuration which includes that channel A will be
 * enabled to measure voltage input in the range from 0V to 10V, with 4k8 SPS
 * sample rating. In this function also Silicon Revision ID will be checked.
 * 
 * ## Application Task  
 * Waits until data from the enabled channel
 * is ready and then reads results of conversion for channel A and if response
 * is ok, prints the results on the uart console.
 * 
 * *note:*'
 * <pre> 
 * Additional Functions :
 *
 * Application Default Handler - Used to send error report messages from click
 * driver to initialized console module.
 * </pre> 
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
    Delay_ms( 100 );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    uint16_t id = DUMMY;
    log_cfg_t log_cfg;
    adswio_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 57600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    adswio_cfg_setup( &cfg );
    ADSWIO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adswio_init( &adswio, &cfg );

    adswio_set_handler( &adswio, &application_default_handler );
    Delay_ms( 200 );

    adswio_reset( &adswio );
    adswio_default_cfg( &adswio );

    adswio_rdy  = DUMMY;
    adswio_ch_a = DUMMY;
    adswio_res  = DUMMY;
    adswio_err  = ADSWIO_ERR_STATUS_OK;

    log_printf( &logger, " AD-SDIO click initialization done \r\n");
    log_printf( &logger, "************************************\r\n");
    Delay_ms( 100 );

    while ( id != ADSWIO_ID_SILICON_REV )
    {
        adswio_generic_read( &adswio, ADSWIO_REG_SILICON_REV, &id, ADSWIO_NULL );
    }
}

void application_task ( void )
{
    adswio_rdy = adswio_status_pin_ready( &adswio );

    while ( adswio_rdy == 0 )
    {
        adswio_rdy = adswio_status_pin_ready( &adswio );
    }

    adswio_err = adswio_get_conv_results( &adswio, ADSWIO_SETUP_CONV_EN_CHA, &adswio_ch_a );

    if ( adswio_err == ADSWIO_ERR_STATUS_OK )
    {
        adswio_res = adswio_ch_a;
        adswio_res /= ADSWIO_RANGE_RESOLUTION;
        adswio_res *= ADSWIO_RANGE_VOLT_MV;
        adswio_ch_a = adswio_res;

        log_printf( &logger, "* CH A converted result is %d mV\r\n", adswio_ch_a );
        Delay_ms( 100 );
    }
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
