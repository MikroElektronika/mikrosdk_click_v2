/*!
 * @file main.c
 * @brief AMRAngle Click example
 *
 * # Description
 * This demo application shows the performance of AMR Angle
 * click by reading and presenting the temperature and angle
 * results on the UART log.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Starts up the UART LOG, SPI and ADC drivers. Performs the
 * default settings like setting the adc vref, resolution and 
 * gpio pins.
 *
 * ## Application Task
 * The application task consists of reading the temperature
 * and angle data from the sensor and sending that data to the
 * UART log every second.
 *
 * @author Stefan Nikolic
 *
 */

#include "board.h"
#include "log.h"
#include "amrangle.h"

static amrangle_t amrangle;
static log_t logger;

static float temperature_res;
static float angle_res;

void application_init ( void ) {
    log_cfg_t log_cfg;              /**< Logger config object. */
    amrangle_cfg_t amrangle_cfg;    /**< Click config object. */

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

    amrangle_cfg_setup( &amrangle_cfg, AMRANGLE_ARM_TOOLCHAIN );  // Change when switching profile
    AMRANGLE_MAP_MIKROBUS( amrangle_cfg, MIKROBUS_1 );
    err_t init_flag = amrangle_init( &amrangle, &amrangle_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    amrangle_default_cfg( &amrangle );
    Delay_ms( 500 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    temperature_res = amrangle_read_vtp_temp( &amrangle );
    angle_res = amrangle_angle_read( &amrangle );
    log_printf( &logger, " Temperature: %.2f C\r\n", temperature_res );
    log_printf( &logger, " Angle: %.2f degrees\r\n", angle_res );
    log_printf( &logger, " --------------------------\r\n" );
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
