/*!
 * @file main.c
 * @brief VavPress Click example
 *
 * # Description
 * This library contains API for the Vav Press Click driver.
 * This demo application shows an example of 
 * differential pressure and temperature measurement.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization and default settings, 
 * the app display retrieve the electronic signature 
 * and set the sensor parameters data.
 *
 * ## Application Task
 * This is an example that shows the use of a Vav Press Click board™.
 * Logs pressure difference value [ Pa ] and temperature [ degree Celsius ] value.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "vavpress.h"

static vavpress_t vavpress;
static log_t logger;
static float diff_press;
static float temperature;
vavpress_el_signature_data_t el_signature_data;
vavpress_sensor_param_data_t param_data;

void application_init ( void ) {
    log_cfg_t log_cfg;            /**< Logger config object. */
    vavpress_cfg_t vavpress_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    vavpress_cfg_setup( &vavpress_cfg );
    VAVPRESS_MAP_MIKROBUS( vavpress_cfg, MIKROBUS_1 );
    err_t init_flag = vavpress_init( &vavpress, &vavpress_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    vavpress_default_cfg ( &vavpress );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
    
    vavpress_retrieve_electronic_signature( &vavpress, &el_signature_data );
    Delay_ms ( 100 );

    log_printf( &logger, "--------------------------------\r\n" );
    log_printf( &logger, " Firmware Version : %.3f        \r\n", el_signature_data.firmware_version );
    log_printf( &logger, " Pressure Range   : %d Pa       \r\n", el_signature_data.pressure_range );
    log_printf( &logger, " Part #           : %.11s       \r\n", el_signature_data.part_number );
    log_printf( &logger, " Lot #            : %.7s        \r\n", el_signature_data.lot_number );
    log_printf( &logger, " Output Type      : %c          \r\n", el_signature_data.output_type );
    log_printf( &logger, " Scale Factor     : %d          \r\n", el_signature_data.scale_factor );
    log_printf( &logger, " Calibration ID   : %.2s        \r\n", el_signature_data.calibration_id );
    log_printf( &logger, " Week number      : %d          \r\n", el_signature_data.week_number );
    log_printf( &logger, " Year number      : %d          \r\n", el_signature_data.year_number );
    log_printf( &logger, " Sequence number  : %d          \r\n", el_signature_data.sequence_number );
    log_printf( &logger, "--------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    param_data.scale_factor_temp = 72;
    param_data.scale_factor_press = el_signature_data.scale_factor;
    param_data.readout_at_known_temperature = 50;
    param_data.known_temperature_c = 24.0;
    Delay_ms ( 100 );
}

void application_task ( void ) {   
    err_t error_flag = vavpress_get_dif_press_and_temp( &vavpress, &param_data, &diff_press, &temperature );
    if ( error_flag == VAVPRESS_OK ) {
        log_printf( &logger, " Diff. Pressure    : %.4f Pa\r\n", diff_press );
        log_printf( &logger, " Temperature       : %.4f C\r\n", temperature );
        log_printf( &logger, "--------------------------------\r\n" );
        Delay_ms ( 1000 ); 
        Delay_ms ( 1000 );
    } else {
        log_error( &logger, " Communcation Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
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
