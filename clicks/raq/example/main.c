/*!
 * @file main.c
 * @brief RAQ Click example
 *
 * # Description
 * This example demonstrates the use of RAQ Click board (ZMOD4450) in continuous measurement mode.
 * The device is initialized, basic sensor information (PID, CONF and production data) is read and
 * logged, then the sensor is calibrated/initialized to obtain MOX_LR and MOX_ER parameters.
 * After that, the continuous measurement sequence is configured and started, and the calculated
 * RMOX value is periodically read and logged to the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs a hardware reset. Reads and logs the sensor PID, CONF and
 * production data. Runs the initialization flow (HSPF calculation + INIT command) to obtain
 * MOX_LR and MOX_ER calibration parameters, then configures and starts the continuous measurement
 * sequencer.
 *
 * ## Application Task
 * Polls the sensor sequencer, reads the latest ADC sample and computes the RMOX value using the
 * cached MOX_LR/MOX_ER parameters. The resulting RMOX value is logged to the terminal.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "raq.h"

#ifndef MIKROBUS_POSITION_RAQ
    #define MIKROBUS_POSITION_RAQ MIKROBUS_1
#endif

static raq_t raq;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    raq_cfg_t raq_cfg;          /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    raq_cfg_setup( &raq_cfg );
    RAQ_MAP_MIKROBUS( raq_cfg, MIKROBUS_POSITION_RAQ );
    if ( I2C_MASTER_ERROR == raq_init( &raq, &raq_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    /* HW reset */
    raq_hw_reset( &raq );
    
    /* Read basic sensor info */
    raq_info_t info;
    if ( RAQ_OK != raq_get_sensor_info( &raq, &info ) )
    {
        log_error( &logger, " Sensor info read failed." );
        for ( ; ; );
    }

    log_printf( &logger, " PID: 0x%.4X\r\n", info.pid );
  
    /* init sensor -> get MOX_LR / MOX_ER */
    uint16_t mox_lr = 0, mox_er = 0;
    err_t ret = raq_init_sensor( &raq, &mox_lr, &mox_er );

    if ( RAQ_OK != ret )
    {
        log_error( &logger, " Sensor calib/init failed (code=%ld).", ret );
        for ( ; ; );
    }

    log_printf( &logger, " MOX_LR: 0x%.4X  MOX_ER: 0x%.4X\r\n", mox_lr, mox_er );

    /* continuous mode init sequence */
    ret = raq_init_measurement( &raq );
    if ( RAQ_OK != ret )
    {
        log_error( &logger, " Init measurement failed (code=%ld).", ret );
        for ( ; ; );
    }

    ret = raq_cont_init( &raq );
    if ( RAQ_OK != ret )
    {
        log_error( &logger, " Continuous init failed (code=%ld).", ret );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float rmox = 0;
    err_t ret = raq_cont_run( &raq, &rmox );

    if ( RAQ_OK == ret )
    {
        log_printf( &logger, "RMOX: %.3f\r\n", rmox );
    }
    else
    {
        log_printf( &logger, "Error: %ld\r\n", ret );
    }

    Delay_100ms( );
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
