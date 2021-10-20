/*!
 * @file main.c
 * @brief I2CIsolator3 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the I2C Isolator 3 click board. In this example, we measure temperature
 * from the Thermo 20 click connected to the I2C Isolator 3 click board. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C and start to write log. Initialization driver enables - I2C,
 * set I2C slave address of the Thermo 20 click, performs software reset, also write log.
 *
 * ## Application Task
 * In this example via Thermo 20 click we get the data processed by the function. When the function processes the data, we get
 * the temperature information. All data logs write on USB UART changes every 3 sec.
 *
 * Additional Functions :
 * - void calculate_temperature( ) - Calculate temperature in degrees Celsius.
 *
 * @author Jelena Milosavljevic
 *
 */

#include "board.h"
#include "log.h"
#include "i2cisolator3.h"

static i2cisolator3_t i2cisolator3;
static log_t logger;
static float temperature;
static char log_text[ 50 ];

void calculate_temperature ( ) {
    uint16_t res_adc;
    uint8_t rx_buf[ 3 ];

    i2cisolator3_burst_read ( &i2cisolator3, I2CISOLATOR3_THERMO20_CMD_READ_ADC, rx_buf, 3 );

    res_adc = rx_buf[ 0 ];
    res_adc <<= 8;
    res_adc |= rx_buf[ 1 ];

    temperature = ( float ) res_adc;
    temperature /= 65535.0;
    temperature *= 165.0;
    temperature -= 40.0;
}

void application_init ( void ) {
    log_cfg_t log_cfg;                         /**< Logger config object. */
    i2cisolator3_cfg_t i2cisolator3_cfg;       /**< Click config object. */

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
    i2cisolator3_cfg_setup( &i2cisolator3_cfg );
    I2CISOLATOR3_MAP_MIKROBUS( i2cisolator3_cfg, MIKROBUS_1 );
    err_t init_flag = i2cisolator3_init( &i2cisolator3, &i2cisolator3_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_printf( &logger, "  Driver Init. Done  \r\n" );
    log_printf( &logger, "  Set I2C Slave Address   \r\n" );
    log_printf( &logger, "  of the Thermo 20 click   \r\n" );
    Delay_ms( 100 );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "      Software Reset      \r\n" );
    i2cisolator3_send_cmd(  &i2cisolator3, I2CISOLATOR3_THERMO20_CMD_RESET );
    Delay_ms( 100 );

    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "     Start Measuring      \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 100 );

    log_info( &logger, " Application Task \r\n" );
}

void application_task ( void ) {
    i2cisolator3_send_cmd( &i2cisolator3, I2CISOLATOR3_THERMO20_CMD_CONVERSION );
    Delay_ms( 100 );

    calculate_temperature( );

    log_printf( &logger, "Temperature : %.2f \r\n", temperature );
    Delay_ms( 3000 );    
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
