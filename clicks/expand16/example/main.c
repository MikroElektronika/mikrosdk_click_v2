/*!
 * @file main.c
 * @brief Expand 16 Click example
 *
 * # Description
 * This example demonstrates the use of Expand 16 click board by setting and reading 
 * the ports state.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration which sets 
 * half of the pins as output ( GPIO4, GPIO5, GPIO6 and GPIO7 ) and the 
 * other half of the pins as inputs ( GPIO0, GPIO1, GPIO2 and GPIO3 ).
 *
 * ## Application Task
 * Sets the state of the output pins and then reads the status of input pins
 * and displays the results on the USB UART approximately 2 seconds.
 *
 * @note
 * In order for this example to work as intended it is necessary to connect the input and output pins 
 * eg. GPIO0 and GPIO4, GPIO1 and GPIO5 etc. Floating input pins will be shown as a low state.
 * 
 * ## Additional Function
 * - static void show_input_pin_state ( uint8_t pin_state )
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "expand16.h"

static expand16_t expand16;
static log_t logger;

/**
 * @brief Expand 16 show input pins state function.
 * @details This function is used to show states of the input pins on UART terminal.
 * @param[in] pin_state : Read input pins state.
 * @return Nothing.
 * @note None.
 */
static void show_input_pin_state ( uint8_t pin_state );

void application_init ( void ) 
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    expand16_cfg_t expand16_cfg;    /**< Click config object. */

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
    expand16_cfg_setup( &expand16_cfg );
    EXPAND16_MAP_MIKROBUS( expand16_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == expand16_init( &expand16, &expand16_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    uint8_t dev_id = 0;
    expand16_read_reg( &expand16, EXPAND16_REG_DEV_ID_AND_CTRL, &dev_id ); 
    if ( EXPAND16_DEVICE_ID != ( dev_id & EXPAND16_DEVICE_ID_MASK ) )
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    
    if ( EXPAND16_ERROR == expand16_default_cfg ( &expand16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t tmp_data = 0;

    log_printf( &logger, "Output pins state: HIGH \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    expand16_set_output_state( &expand16, EXPAND16_PIN_MASK_NONE, EXPAND16_PIN_MASK_GPIO_4 | 
                                          EXPAND16_PIN_MASK_GPIO_5 | EXPAND16_PIN_MASK_GPIO_6 | 
                                          EXPAND16_PIN_MASK_GPIO_7 );
    expand16_read_reg( &expand16, EXPAND16_REG_INPUT_STATE, &tmp_data ); 
    show_input_pin_state( tmp_data );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "Output pins state: LOW \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    expand16_set_output_state( &expand16, EXPAND16_PIN_MASK_GPIO_4 | EXPAND16_PIN_MASK_GPIO_5 | 
                                          EXPAND16_PIN_MASK_GPIO_6 | EXPAND16_PIN_MASK_GPIO_7, 
                                          EXPAND16_PIN_MASK_NONE );
    expand16_read_reg( &expand16, EXPAND16_REG_INPUT_STATE, &tmp_data ); 
    show_input_pin_state( tmp_data );
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

static void show_input_pin_state ( uint8_t pin_state )
{
    log_printf( &logger, "Pin GPIO0 state: " );
    if ( pin_state & EXPAND16_PIN_MASK_GPIO_0 )
    {
        log_printf( &logger, "HIGH \r\n" );
    }
    else
    {
        log_printf( &logger, "LOW \r\n" );
    }

    log_printf( &logger, "Pin GPIO1 state: " );
    if ( pin_state & EXPAND16_PIN_MASK_GPIO_1 )
    {
        log_printf( &logger, "HIGH \r\n" );
    }
    else
    {
        log_printf( &logger, "LOW \r\n" );
    }

    
    log_printf( &logger, "Pin GPIO2 state: " );
    if ( pin_state & EXPAND16_PIN_MASK_GPIO_2 )
    {
        log_printf( &logger, "HIGH \r\n" );
    }
    else
    {
        log_printf( &logger, "LOW \r\n" );
    }

    
    log_printf( &logger, "Pin GPIO3 state: " );
    if ( pin_state & EXPAND16_PIN_MASK_GPIO_3 )
    {
        log_printf( &logger, "HIGH \r\n" );
    }
    else
    {
        log_printf( &logger, "LOW \r\n" );
    }
    log_printf( &logger, "- - - - - - - - - - - - -\r\n\n" );
}

// ------------------------------------------------------------------------ END
