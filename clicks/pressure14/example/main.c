/*!
 * @file main.c
 * @brief Pressure14 Click example
 *
 * # Description
 * This examples used ABP2 Series are piezoresistive silicon pressure sensors offering a digital output for reading pressure over the specified full scale pressure 
 * span and temperature range. They are calibrated and temperature compensated for sensor offset, sensitivity, temperature effects and accuracy errors (which include
 * non-linearity, repeatability and hysteresis) using an on-board Application Specific Integrated
 * Circuit (ASIC).
 * 
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enables I2C.
 *
 * ## Application Task
 * The output measurement command is sent first forcing the ABP2 pressure sensor to exit standby mode and enter operating mode. The device busy state is evaluated via 
 * the end-of-conversion pin ( INT ) following the pressure and temperature data acquisition and calculation. The results are being sent to the Usart Terminaland repeats every 5 seconds.
 *
 * @author Jelena Milosavljevic
 *
 */

// ------------------------------------------------------------------- INCLUDES
#include "board.h"
#include "log.h"
#include "pressure14.h"


// ------------------------------------------------------------------ VARIABLES
static pressure14_t pressure14;
static log_t logger;
static uint8_t status;
static uint32_t pressure_tmp;
static uint32_t temperature_tmp;
static float pressure;
static float temperature;

void application_init ( void ) {
    log_cfg_t log_cfg;                  /**< Logger config object. */
    pressure14_cfg_t pressure14_cfg;    /**< Click config object. */

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
    pressure14_cfg_setup( &pressure14_cfg );
    PRESSURE14_MAP_MIKROBUS( pressure14_cfg, MIKROBUS_1 );
    err_t init_flag = pressure14_init( &pressure14, &pressure14_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {       
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    pressure14_measure_cmd( &pressure14 );
    Delay_ms ( 10 );
    
    if ( pressure14_check_busy_flag_int( &pressure14 ) == 1 ) {
        pressure14_read_press_and_temp ( &pressure14, &status, &pressure_tmp, &temperature_tmp );    
        pressure = pressure14_get_pressure( pressure_tmp, PRESSURE14_CONV_UNIT_MILIBAR );
        temperature = pressure14_get_temperature( temperature_tmp, PRESSURE14_CONV_UNIT_CELSIUS );
    
        log_printf( &logger, " Pressure    : %.2f mbar \r\n", pressure );
        log_printf( &logger, " Temperature : %.2f C \r\n", temperature );
        log_printf( &logger, "-------------------------\r\n" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
