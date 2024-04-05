/*!
 * @file main.c
 * @brief Touchpad3 Click example
 *
 * # Description
 * This example prints the coordinate points of the position we touch on a click. We use RST and INT
 * pins. The whole project is done through i2c communication.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enables - Initializes I2C, set RST pin as an output, set INT pin as input and start to write log. 
 * I2C, perform a hardware reset, configuration (general, decoding, sensor mapping), get device ID and enable the touch, also write log.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the TouchPad 3 click board. TouchPad 3 click board uses USB UART log to display
 * X and Y coordinates of the touch, depending on the selected Touch ID.
 *
 * @author Jelena Milosavljevic
 *
 */

#include "board.h"
#include "log.h"
#include "touchpad3.h"

static touchpad3_t touchpad3;
static log_t logger;
uint8_t touch_id_state;
uint8_t status_data;
uint16_t x_axis; 
uint16_t y_axis;
uint32_t device_id;
touch_data_t touch_data;

void display_status ( void ) {
    
    switch ( status_data ) {
        case ( TOUCHPAD3_CMD_STATUS_SUCCESS ) : { 
            log_printf( &logger, " Command execution successful " );
            Delay_ms ( 10 );
            break;
        }
        case ( TOUCHPAD3_CMD_STATUS_PARAM_OUT_OF_RANGE ) : {  
            log_printf( &logger, "    Parameter out of range    " );
            Delay_ms ( 10 );
            break;
        }
        case TOUCHPAD3_CMD_STATUS_TIMEOUT: { 
            log_printf( &logger,"           Timeout :          " );
            log_printf( &logger, "  not enough bytes received   " );
            Delay_ms ( 10 );
            break;
        }
        case TOUCHPAD3_CMD_STATUS_UNRECOGNIZED: { 
            log_printf( &logger, "     Unrecognized command     ");
            Delay_ms ( 10 );
            break;
        }
        case TOUCHPAD3_CMD_STATUS_INVALID_PARAM: {
            log_printf( &logger, "       Invalid parameter      " );
            Delay_ms ( 10 );
            break;
        }
        case TOUCHPAD3_CMD_STATUS_MISSING_OR_EXTRA_PARAM: {
            log_printf( &logger, "  Missing or extra parameter  " );
            Delay_ms ( 10 );
            break;
        }
        default: { 
            break;
        }
    }
}

void application_init ( void ) {
    log_cfg_t log_cfg;                 /**< Logger config object. */
    touchpad3_cfg_t touchpad3_cfg;     /**< Click config object. */

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
    touchpad3_cfg_setup( &touchpad3_cfg );
    TOUCHPAD3_MAP_MIKROBUS( touchpad3_cfg, MIKROBUS_1 );
    err_t init_flag = touchpad3_init( &touchpad3, &touchpad3_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) { 
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    touchpad3_default_cfg ( &touchpad3 );
    
    touch_id_state = 0;
    log_printf( &logger, "------------------------------\r\n" );
    device_id = touchpad3_get_device_id( &touchpad3 );
    Delay_ms ( 100 );
    log_printf( &logger, "     Get Device ID : %d \r\n      ", device_id );
    log_printf( &logger, "------------------------------\r\n" );
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
    
    status_data = touchpad3_config_touch( &touchpad3, TOUCHPAD3_TOUCH_GESTURE_ENABLE );
    
    log_printf( &logger, "     Touch Enable Status:     \r\n");
    display_status( );
    log_printf( &logger, "------------------------------\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void ) {
    if ( touchpad3_get_int( &touchpad3 ) == TOUCHPAD3_INT_STATUS_HIGH ) {
       
       touchpad3_get_touch( &touchpad3, &touch_data, &x_axis, &y_axis );
       Delay_ms ( 100 );

        if ( ( touch_data.tch_state == TOUCHPAD3_STATE_TCH ) && ( touch_data.touch_id == touch_id_state ) ) {   
            log_printf( &logger, "  X Coordinate : %d   \r\n" , x_axis );
            log_printf( &logger, "  Y Coordinate : %d   \r\n" , y_axis );
            log_printf( &logger, "------------------------------\r\n" );
            Delay_ms ( 100 );
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
