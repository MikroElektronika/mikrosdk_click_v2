/*!
 * \file 
 * \brief Accel6 Click example
 * 
 * # Description
 * This application allows acceleration measurement in three perpendicular axes.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes Driver init and settings accelerometer data range, 
 * bandwidth, mode and sleep timer which are necessary for the init chip.
 * 
 * ## Application Task  
 * Reads the accel X / Y / Z axis data in mg, 
 * Temperature data in C, detects the orientation of the X,Y and Z axis
 * and checking on which axis the tap is detected.
 * All data logs on usb uart for every 500 ms.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "accel6.h"

// ------------------------------------------------------------------ VARIABLES

static accel6_t accel6;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    accel6_cfg_t cfg;

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

    accel6_cfg_setup( &cfg );
    ACCEL6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel6_init( &accel6, &cfg );

    accel6_soft_reset( &accel6 );
    Delay_1sec();
    log_info( &logger, "---- Device reset done ----" );
    
    accel6_default_cfg( &accel6, ACCEL6_PMU_RANGE_4g, 
                                          ACCEL6_PMU_BW_125Hz, 
                                          ACCEL6_PMU_LPW_NORMAL_MODE | 
                                          ACCEL6_PMU_LPW_SLEEP_10ms );
    
    log_info( &logger, "---- Device configuration done ----" );
    
    Delay_1sec();
}

void application_task ( )
{
    uint8_t tap_detect;
    uint8_t orient;
    uint8_t z_orient;
    uint8_t xy_orient;
    float f_axis = 0.0;
    float temp = 0.0;
    
    f_axis = accel6_get_axis ( &accel6, ACCEL6_AXIS_X );
    log_printf( &logger, " X axis: %f mg \r\n ", f_axis );


    f_axis = accel6_get_axis ( &accel6, ACCEL6_AXIS_Y );
    log_printf( &logger, " Y axis: %f mg \r\n ", f_axis );

    f_axis = accel6_get_axis ( &accel6, ACCEL6_AXIS_Z );
    log_printf( &logger, " Z axis: %f mg \r\n ", f_axis );

    temp = accel6_get_temperature( &accel6 );
    log_printf( &logger, " Temperature: %.2f C \r\n ", temp );

    accel6_get_orient( &accel6, &z_orient, &xy_orient );
    
    switch ( z_orient )
    {
        case 1:
        {
            log_printf( &logger, " Z orient : UPWARD looking \r\n " );
            break;
        }
        case 2:
        {
            log_printf( &logger, " Z orient : DOWNWARD looking \r\n " );
            break;
        }
        default:
        {
            break;
        }
    }

    switch ( xy_orient )
    {
        case 1:
        {
            log_printf( &logger, " XY orient : UPSIDE DOWN \r\n " );
            break;
        }
        case 2:
        {
            log_printf( &logger, " XY orient : LANDSCAPE LEFT \r\n " );
            break;
        }
        case 3:
        {
            log_printf( &logger, " XY orient : LANDSCAPE RIGHT \r\n " );
            break;
        }
        case 4:
        {
            log_printf( &logger, " XY orient : UPRIGHT \r\n " );
            break;
        }
        default:
        {
            break;
        }
    }
	
	tap_detect = accel6_get_tap_status( &accel6 );
    switch ( tap_detect )
    {
        case 1:
        {
            log_printf( &logger, " Tap status : X negative \r\n " );
            break;
        }
        case 2:
        {
            log_printf( &logger, " Tap status : Y negative \r\n " );
            break;
        }
        case 3:
        {
            log_printf( &logger, " Tap status : Z negative \r\n " );
            break;
        }
        case 4:
        {
            log_printf( &logger, " Tap status : X positive \r\n " );
            break;
        }
        case 5:
        {
            log_printf( &logger, " Tap status : Y positive \r\n " );
            break;
        }
        case 6:
        {
            log_printf( &logger, " Tap status : Z positive \r\n " );
            break;
        }
        default:
        {
            break;
        }
    }
	
    log_printf( &logger, "   \r\n" );
    Delay_ms( 2000 );
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
