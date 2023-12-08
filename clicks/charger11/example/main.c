/*!
 * @file main.c
 * @brief Charger11 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the Charger 11 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initalizes INT ( ST ), PWM ( LG ), AN ( LR ) pins and SPI, I2C, LOG modules.
 *
 * ## Application Task
 * Waits for user input in order to increment, decrement wiper or log report 
 * (Wiper position and Output voltage)
 * 
 * Additional Functions :
 * - charger11_log_wiper_position( charger11_t *ctx ) - Logs current Wiper position.
 * - charger11_case_plus( charger11_t *ctx ) - Increments Wiper position.
 * - charger11_case_minus( charger11_t *ctx ) - Decrements Wiper position.
 * - charger11_case_report( charger11_t *ctx ) - Logs current Wiper position and Output voltage.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "charger11.h"

static charger11_t charger11;
static log_t logger;

/**
 * @brief Charger 11 log wiper position.
 * @details This function reads wiper position and logs it on UART terminal.
 */
void charger11_log_wiper_position( charger11_t *ctx );

/**
 * @brief Charger 11 increase wiper position.
 * @details This function increases wiper position and logs it on UART terminal.
 */
void charger11_case_plus( charger11_t *ctx );

/**
 * @brief Charger 11 decrease wiper position.
 * @details This function decreases wiper position and logs it on UART terminal.
 */
void charger11_case_minus( charger11_t *ctx );

/**
 * @brief Charger 11 log wiper position and voltage.
 * @details This function reads wiper position and voltage and logs them on UART terminal.
 */
void charger11_case_report( charger11_t *ctx );

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger11_cfg_t charger11_cfg;  /**< Click config object. */

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
    charger11_cfg_setup( &charger11_cfg );
    CHARGER11_MAP_MIKROBUS( charger11_cfg, MIKROBUS_1 );
    err_t init_flag  = charger11_init( &charger11, &charger11_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    charger11_case_report( &charger11 );
}

void application_task ( void ) {
    char uart_char;
    if ( log_read( &logger, &uart_char, 1 ) ) {
        switch (uart_char) {
            case '+' : {
                charger11_case_plus( &charger11 );
                break;
            }
            case '-' : {
                charger11_case_minus( &charger11 );
                break;
            }
            case 'r' : {
                charger11_case_report( &charger11 );
                break;
            }
            default : {
                log_printf( &logger, "> Invalid command \r\n" );
                break;
            }
        }
    }
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

void charger11_log_wiper_position( charger11_t *ctx ) {
    float wiper_position;
    uint8_t aux_wiper_position;
    aux_wiper_position = charger11_spi_get_wiper_position( ctx );

    wiper_position = ( float ) aux_wiper_position / 255.0;
    wiper_position *= 100.0;
    log_printf( &logger, "> Wiper position : %.2f %%\r\n", wiper_position );
}

void charger11_case_plus( charger11_t *ctx ) {
    log_printf( &logger, "> Wiper incremented\r\n" );
    charger11_spi_increment_wiper( ctx );
    charger11_log_wiper_position( ctx );
}

void charger11_case_minus( charger11_t *ctx ) {
    log_printf( &logger, "> Wiper decremented\r\n" );
    charger11_spi_decrement_wiper( ctx );
    charger11_log_wiper_position( ctx );
}

void charger11_case_report( charger11_t *ctx ) {
    float volt_data;
    charger11_log_wiper_position( ctx );
    volt_data = charger11_i2c_get_volt( ctx, 4096.0 );
    log_printf( &logger, "> Output voltage : %d mV\r\n", ( uint16_t ) volt_data );
}

// ------------------------------------------------------------------------ END
