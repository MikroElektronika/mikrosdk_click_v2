/*!
 * @file main.c
 * @brief LightRanger5 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the LightRanger 5 click board.
 * This demo application shows an example of distance measurement.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module, log UART and additional pins.
 * After driver initialization and default settings,
 * the app performs and check factory calibrationa and 
 * check and wait for OK status. This process takes a few seconds, so please wait.
 * After current status is OK, app performs the configuration of the TMF8801 sensor:
 * read and write calibration data, set algorithm state and command data. 
 * 
 *
 * ## Application Task
 * This is an example that shows the use of a LightRanger 5 click board.
 * A new data ready is checked as soon as possible which signals 
 * the time required for the ranging sensor to perform the distance measurement.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "lightranger5.h"

static lightranger5_t lightranger5;
static log_t logger;

static uint8_t status_old = 255;
static uint8_t status;
static uint8_t factory_calib_data[ 14 ];
static uint8_t tmf8801_algo_state[ 11 ] = { 0xB1, 0xA9, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static uint8_t command_data[ 9 ] = { 0x03, 0x23, 0x00, 0x00, 0x00, 0x64, 0xFF, 0xFF, 0x02 };
static uint8_t appid_data;

void display_status_no_error ( void ) {
    log_printf( &logger, "\r\n STATUS : No error\r\n" );
    
    switch ( status ) {
        case LIGHTRANGER5_STATUS_IDLE : {
            log_printf( &logger, " Information that internal state machine is idling.\r\n" );
            break;
        }
        case LIGHTRANGER5_STATUS_DIAGNOSTIC : {
            log_printf( &logger, " Information that internal state machine is in diagnostic mode.\r\n" );
            break;
        }
        case LIGHTRANGER5_STATUS_START : {
            log_printf( &logger, " Internal state machine is in initialization phase.\r\n" );
            break;
        }
        case LIGHTRANGER5_STATUS_CALIBRATION : {
            log_printf( &logger, " Internal state machine is in the calibration phase. \r\n" );
            break;
        }
        case LIGHTRANGER5_STATUS_LIGHTCOL : {
            log_printf( &logger, " Internal state machine is performing HW measurements and running the proximity algorithm.\r\n" );
            break;
        }
        case LIGHTRANGER5_STATUS_ALGORITHM : {
            log_printf( &logger, " Internal state machine is running the distance algorithm.\r\n" );
            break;
        }
        case LIGHTRANGER5_STATUS_STARTUP : {
            log_printf( &logger, " Internal state machine is initializing HW and SW.\r\n" );
            break;
        }
    }    
}

void display_status_error ( void ) {
    log_printf( &logger, "\r\n STATUS : Error\r\n" );
    
    switch ( status ) {
        case LIGHTRANGER5_STATUS_VCSEL_PWR_FAIL : {
            log_printf( &logger, " Eye safety check failed, VCSEL is disabled by HW circuit.\r\n" );
            break;
        }
        case LIGHTRANGER5_STATUS_VCSEL_LED_A_FAIL : {
            log_printf( &logger, " Eye safety check failed for anode. VCSEL is disabled by HW circuit.\r\n" );
            break;
        }
        case LIGHTRANGER5_STATUS_VCSEL_LED_K_FAIL : {
            log_printf( &logger, " Eye safety check failed for cathode. VCSEL is disabled by HW circuit.\r\n" );
            break;
        }
        case LIGHTRANGER5_STATUS_INVALID_PARAM : {
            log_printf( &logger, " Internal program error. A parameter to a function call was out of range.\r\n" );
            break;
        }
        case LIGHTRANGER5_STATUS_INVALID_DEVICE : {
            log_printf( &logger, " A status information that a measurement got interrupted.\r\n" );
            break;
        }
        case LIGHTRANGER5_STATUS_CALIB_ERROR : {
            log_printf( &logger, " Electrical calibration failed. No two peaks found to calibrate.\r\n" );
            break;
        }
        case LIGHTRANGER5_STATUS_INVALID_COMMAND : {
            log_printf( &logger, " Command was sent while the application was busy executing the previous command.\r\n" );
            break;
        }
        case LIGHTRANGER5_STATUS_INVALID_STATE : {
            log_printf( &logger, " Internal program error.\r\n" );
            break;
        }
        case LIGHTRANGER5_STATUS_ERR_ALGORITHM : {
            log_printf( &logger, " Internal error in algorithm.\r\n" );
            break;
        }
    }    
}

void application_init ( void ) {
    log_cfg_t log_cfg;                    /**< Logger config object. */
    lightranger5_cfg_t lightranger5_cfg;  /**< Click config object. */

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

    lightranger5_cfg_setup( &lightranger5_cfg );
    LIGHTRANGER5_MAP_MIKROBUS( lightranger5_cfg, MIKROBUS_1 );
    err_t init_flag = lightranger5_init( &lightranger5, &lightranger5_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    lightranger5_default_cfg( &lightranger5 );
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
    
    if ( !lightranger5_check_factory_calibration( &lightranger5 ) ) {
        log_info( &logger, " Factory calibration success." );
    } else {
        log_info( &logger, " Factory calibration FAILED." );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    do {
        lightranger5_get_status( &lightranger5, &status );
        
        if ( status_old != status ) {
            if ( status < LIGHTRANGER5_STATUS_OK ) {
                display_status_no_error( );    
            } else {
                display_status_error( );   
            }  
            status_old = status;
        }
        Delay_ms( 100 );
    } while ( status );
    
    lightranger5_get_factory_calib_data( &lightranger5, factory_calib_data );
    
    log_printf( &logger, "------------------------------\r\n" );
    log_printf( &logger, " factory_calib_data[ 14 ] =\r\n { " );
    
    for ( uint8_t n_cnt = 0 ; n_cnt < 14 ; n_cnt++ ) {
        log_printf( &logger, "0x%.2X, ", factory_calib_data[ n_cnt ] );
    }
    
    log_printf( &logger, "};\r\n" );
    log_printf( &logger, "------------------------------\r\n" );
    
    lightranger5_set_command( &lightranger5, LIGHTRANGER5_CMD_DL_CALIB_AND_STATE );

    lightranger5_set_factory_calib_data( &lightranger5, factory_calib_data );

    lightranger5_set_algorithm_state_data( &lightranger5, tmf8801_algo_state );
    
    lightranger5_set_command_data( &lightranger5, command_data );
    
    lightranger5_get_status( &lightranger5, &status );
        
    if ( status_old != status ) {
        if ( status < LIGHTRANGER5_STATUS_OK ) {
            display_status_no_error( );    
        } else {
            display_status_error( );   
        }  
        status_old = status;
    }
    
    lightranger5_get_currently_run_app( &lightranger5, &appid_data );
    
    if ( appid_data == LIGHTRANGER5_APPID_MEASUREMENT ) {
        log_printf( &logger, " Measurement app running.\r\n" );
    }
    else if ( appid_data == LIGHTRANGER5_APPID_BOOTLOADER ) {
        log_printf( &logger, " Bootloader running.\r\n" );
    } else {
        log_printf( &logger, " Result: 0x%X\r\n", appid_data );    
    }
    
    log_printf( &logger, "------------------------------\r\n" );
}

void application_task ( void ) {
    
    if ( lightranger5_check_data_ready( &lightranger5 ) == LIGHTRANGER5_DATA_IS_READY ) {
        uint16_t distance_mm = lightranger5_measure_distance( &lightranger5 );
        
        if ( distance_mm ) {
            log_printf( &logger, "       Distance : %d mm\r\n", distance_mm );    
        } else {
            log_printf( &logger, "         Out of range    \r\n", distance_mm );    
        }
        
        log_printf( &logger, "------------------------------\r\n" );
    }
    
    Delay_ms( 1000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
