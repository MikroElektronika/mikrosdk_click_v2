/*!
 * @file main.c
 * @brief TempHum14 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the Temp-Hum 14 Click board.
 * Temp-Hum 14 Click board can be used to measure temperature
 * and relative humidity.
 * All data logs write on USB uart changes every 3 sec.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enables I2C, and
 * hardware reset the device and read the serial number.
 *
 * ## Application Task
 * Reading temperature and humidity, and loging it on the USB uart. 
 * 
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "temphum14.h"

static temphum14_t temphum14;
static log_t logger;
static temphum14_diagn_t status_data;
static float temperature;
static float humidity;
uint32_t ser_numb;

void display_diagnostic ( void ) {
    log_printf( &logger, "-----------------------------\r\n" );
    log_printf( &logger, "\r\n NVM Error        :" );
    if ( status_data.nvm_error == TEMPHUM14_STATUS_ON ) {
        log_printf( &logger, " Error \r\n" );
    } else {
        log_printf( &logger, " No Error \r\n" );
    }

    log_printf( &logger, "\r\n Humidity U/O     :" );
    if ( status_data.hum_un_over == TEMPHUM14_STATUS_ON ) {
        log_printf( &logger, " Under/Overrun \r\n" );
    } else {
        log_printf( &logger, " No Error \r\n" );
    }

    log_printf( &logger, "\r\n Humidity Error   :" );
    if ( status_data.hum_h_err == TEMPHUM14_STATUS_ON ) {
        log_printf( &logger, " Below -10%% RH \r\n" );
    } else if ( status_data.hum_l_err == TEMPHUM14_STATUS_ON ) {
        log_printf( &logger, " Above 120%% RH \r\n" );
    } else {
        log_printf( &logger, " No Error \r\n" );
    }
    
    log_printf( &logger, "\r\n Temperature U/O  :" );
    if ( status_data.temp_un_over == TEMPHUM14_STATUS_ON ) {
        log_printf( &logger, " Under/Overrun \r\n" );
    } else {
        log_printf( &logger, " No Error \r\n" );
    }

    log_printf( &logger, "\r\n Temperature Error:" );
    if ( status_data.temp_h_err == TEMPHUM14_STATUS_ON ) {
        log_printf( &logger, " Below -50 C \r\n" );
    } else if ( status_data.temp_l_err == TEMPHUM14_STATUS_ON ) {
        log_printf( &logger, " Above 150 C \r\n" );
    } else {
        log_printf( &logger, " No Error \r\n" );
    }

    log_printf( &logger, "\r\n Heater Status    :" );
    if ( status_data.heater_on == TEMPHUM14_STATUS_ON ) {
        log_printf( &logger, " ON \r\n" );
    } else {
        log_printf( &logger, " OFF \r\n" );
    }

    log_printf( &logger, "-----------------------------\r\n" );
}

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum14_cfg_t temphum14_cfg;  /**< Click config object. */

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
    log_printf( &logger, "-----------------------------\r\n" );
    log_info( &logger, " Application Init " );
    log_printf( &logger, "-----------------------------\r\n" );

    // Click initialization.
    temphum14_cfg_setup( &temphum14_cfg );
    TEMPHUM14_MAP_MIKROBUS( temphum14_cfg, MIKROBUS_1 );
    err_t init_flag = temphum14_init( &temphum14, &temphum14_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms ( 100 );
    log_printf( &logger, "-----------------------------\r\n" );
    log_printf( &logger, " Hardware Reset \r\n" );
    temphum14_hw_reset( &temphum14 );
    Delay_ms ( 100 );
    
    ser_numb = temphum14_get_serial_number( &temphum14 );
    log_printf( &logger, "-----------------------------\r\n" );
    log_printf( &logger, " Serial Number : %lu \r\n", ser_numb );
    log_printf( &logger, "-----------------------------\r\n" );
    log_printf( &logger, " Software Reset \r\n" );
    temphum14_soft_reset( &temphum14 );
    Delay_ms ( 100 );
    
    temphum14_get_diagnostic( &temphum14, &status_data );
    Delay_ms ( 100 );

    display_diagnostic( );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-----------------------------\r\n" );
}

void application_task ( void ) {
    temphum14_set_conversion( &temphum14, TEMPHUM14_CONVERSION_HUM_OSR_0_020, TEMPHUM14_CONVERSION_TEMP_0_040 );
    Delay_ms ( 10 );
    
    temphum14_get_temp_and_hum( &temphum14, &temperature, &humidity );
    Delay_ms ( 10 );
    
    log_printf( &logger, "  Temperature : %.2f C \r\n", temperature );
    log_printf( &logger, "  Humidity    : %.2f %% \r\n", humidity );
    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms ( 1000 );
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
