/*!
 * \file main.c
 * \brief Temp-Log 2 Click example
 *
 * # Description
 * This example demonstrates the use of the Temp-Log 2 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes peripherals and pins.
 * Initializes I2C driver and performs device configuration.
 * Sets total active conversion time to 250 ms and 8 average samples.
 * Also sets Shutdown Mode as default mode, and after device reset puts device
 * in Continuous Conversion Mode.
 * High limit status will be set when temperature cross over the determined
 * high limit temperature value.
 * Low limit status will be set when temperature falls below the determined
 * low limit temperature value.
 *
 * ## Application Task
 * Reads temperature value calculated to Celsius degrees.
 *
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "templog2.h"


// ------------------------------------------------------------------ VARIABLES

static templog2_t templog2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init( void )
{
    templog2_cfg_t templog2_cfg;
    log_cfg_t logger_cfg;

    //  Click initialization.
    templog2_cfg_setup( &templog2_cfg );
    TEMPLOG2_MAP_MIKROBUS( templog2_cfg, MIKROBUS_1 );
    templog2_init( &templog2, &templog2_cfg );

    //  Click default configuration.
    templog2_default_config( &templog2 );

    //  Logger console initialization.
    LOG_MAP_USB_UART( logger_cfg );
    logger_cfg.level = LOG_LEVEL_DEBUG;
	logger_cfg.baud = 57600;
    log_init( &logger, &logger_cfg );
    log_info( &logger, "----  Temp-Log 2 Application Init Done  ----\r\n" );
}

void application_task( void )
{
    float temperature;
    uint8_t temp_status;
    uint8_t cnt;

    temp_status = templog2_data_ready( &templog2 );

    if (temp_status & TEMPLOG2_DATA_READY_MASK)
    {
        temperature = templog2_read_temp( &templog2 );

        log_printf( &logger, " > Temperature : %.2f\r\n", temperature );

        if (temp_status & TEMPLOG2_LOW_LIMIT_MASK)
        {
            log_printf( &logger, " LOW LIMIT DETECTED!\r\n" );
        }

        if (temp_status & TEMPLOG2_HIGH_LIMIT_MASK)
        {
            log_printf( &logger, " HIGH LIMIT DETECTED!\r\n" );
        }
    }
}

void main( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
