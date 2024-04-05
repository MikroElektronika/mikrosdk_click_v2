/*!
 * @file main.c
 * @brief iButton Click Example.
 *
 * # Description
 * This example demonstrates the use of the iButton click boards by registering a DS1990A Serial Number iButton
 * key and then waiting until a key is detected on the reader and identifying if the key matches one of
 * those stored in RAM.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and registers a new DS1990A Serial Number iButton key and stores it in RAM.
 * 
 * ## Application Task  
 * Waits until a key is detected on the reader, and checks if there's a key found in the library that matches
 * the one it has just read. All data is being logged on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ibutton.h"

#define NUMBER_OF_KEYS  1   // Number of keys to register.

static ibutton_t ibutton;
static log_t logger;

/**
 * @brief iButton led indication function.
 * @details This function indicates the selected state over LEDs indication.
 * @param[in] ctx : Click context object.
 * See #ibutton_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Disable LEDs.
 *                    @li @c 1 - Wait for a key.
 *                    @li @c 2 - Operation successfull.
 *                    @li @c 3 - Wrong key found.
 * @return None.
 * @note None.
 */
static void ibutton_led_indication ( ibutton_t *ctx, ibutton_led_state_t state );

/**
 * @brief iButton register keys function.
 * @details This function registers a desired number of keys.
 * Each step will be logged on the USB UART where you can track the function flow.
 * @param[in] ctx : Click context object.
 * See #ibutton_t object definition for detailed explanation.
 * @param[in] num_keys : Number of keys to register.
 * @return None.
 * @note None.
 */
static void ibutton_register_keys ( ibutton_t *ctx, uint8_t num_keys );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ibutton_cfg_t ibutton_cfg;  /**< Click config object. */

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
    ibutton_cfg_setup( &ibutton_cfg );
    IBUTTON_MAP_MIKROBUS( ibutton_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == ibutton_init( &ibutton, &ibutton_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    ibutton_register_keys ( &ibutton, NUMBER_OF_KEYS );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    err_t error_flag = IBUTTON_OK;
    ibutton_led_indication ( &ibutton, IBUTTON_LED_DISABLE );
    log_printf( &logger, " >>> Waiting for a key <<<\r\n" );
    do
    {
        ibutton_led_indication ( &ibutton, IBUTTON_LED_WAIT_KEY );
        error_flag = ibutton_check_key ( &ibutton );
    }
    while ( IBUTTON_ERROR == error_flag );

    ibutton_led_indication ( &ibutton, IBUTTON_LED_DISABLE );
    if ( IBUTTON_OK == error_flag )
    {
        log_printf( &logger, " MATCH, access allowed!\r\n" );
        ibutton_led_indication ( &ibutton, IBUTTON_LED_SUCCESS );
    }
    else if ( IBUTTON_KEY_NO_MATCH == error_flag )
    {
        log_printf( &logger, " NO MATCH, access denied!\r\n" );
        ibutton_led_indication ( &ibutton, IBUTTON_LED_WRONG_KEY );
    }
    ibutton_led_indication ( &ibutton, IBUTTON_LED_DISABLE );
    log_printf( &logger, "--------------------------------\r\n\n" );
    Delay_ms ( 500 );
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

static void ibutton_led_indication ( ibutton_t *ctx, ibutton_led_state_t state )
{
    switch ( state )
    {
        case IBUTTON_LED_DISABLE:
        {
            ibutton_disable_green_led ( ctx );
            ibutton_disable_red_led ( ctx );
            break;
        }
        case IBUTTON_LED_WAIT_KEY:
        {
            ibutton_enable_green_led ( &ibutton );
            Delay_ms ( 250 );
            ibutton_disable_green_led ( &ibutton );
            ibutton_enable_red_led ( &ibutton );
            Delay_ms ( 250 );
            ibutton_disable_red_led ( &ibutton );
            break;
        }
        case IBUTTON_LED_SUCCESS:
        {
            ibutton_enable_green_led ( &ibutton );
            Delay_ms ( 250 );
            ibutton_disable_green_led ( &ibutton );
            Delay_ms ( 250 );
            ibutton_enable_green_led ( &ibutton );
            Delay_ms ( 250 );
            ibutton_disable_green_led ( &ibutton );
            Delay_ms ( 250 );
            break;
        }
        case IBUTTON_LED_WRONG_KEY:
        {
            ibutton_enable_red_led ( &ibutton );
            Delay_ms ( 250 );
            ibutton_disable_red_led ( &ibutton );
            Delay_ms ( 250 );
            ibutton_enable_red_led ( &ibutton );
            Delay_ms ( 250 );
            ibutton_disable_red_led ( &ibutton );
            Delay_ms ( 250 );
            break;
        }
        default:
        {
            break;
        }
    }
}

static void ibutton_register_keys ( ibutton_t *ctx, uint8_t num_keys )
{
    err_t error_flag = IBUTTON_OK;
    uint8_t key_cnt = 1;
    while ( key_cnt <= num_keys )
    {
        ibutton_led_indication ( &ibutton, IBUTTON_LED_DISABLE );
        log_printf( &logger, " >>> Registering key %u of %u <<<\r\n", ( uint16_t ) key_cnt, ( uint16_t ) num_keys );
        log_printf( &logger, " Insert a DS1990A Serial Number iButton to click board reader plate\r\n" );
        do
        {
            ibutton_led_indication ( &ibutton, IBUTTON_LED_WAIT_KEY );
            error_flag = ibutton_add_key ( &ibutton );
        }
        while ( IBUTTON_ERROR == error_flag );

        ibutton_led_indication ( &ibutton, IBUTTON_LED_DISABLE );
        if ( IBUTTON_KEY_ALREADY_EXIST == error_flag )
        {
            log_printf( &logger, " This key is already registered!\r\n" );
            log_printf( &logger, " Use another key or decrease the number of keys\r\n" );
            ibutton_led_indication ( &ibutton, IBUTTON_LED_WRONG_KEY );
        }
        else if ( IBUTTON_OK == error_flag )
        {
            log_printf( &logger, " The key is registered successfully!\r\n" );
            ibutton_led_indication ( &ibutton, IBUTTON_LED_SUCCESS );
            key_cnt++;
        }
        ibutton_led_indication ( &ibutton, IBUTTON_LED_DISABLE );
        log_printf( &logger, "--------------------------------\r\n\n" );
        Delay_ms ( 500 );
    }
}

// ------------------------------------------------------------------------ END
