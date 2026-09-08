/*!
 * @file main.c
 * @brief Haptic 6 Click example
 *
 * # Description
 * This example initializes Haptic 6 Click and the IQS397 haptic controller.
 * The application waits for a button press, drives the LRA motor while the
 * button remains pressed and stops the vibration when the finger is lifted.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger, click driver and default IQS397 haptic settings.
 *
 * ## Application Task
 * Waits for a button event, repeatedly triggers haptic feedback while the
 * button event remains active and cancels the active haptic output after the
 * release debounce expires.
 *
 * @note
 * Connect an LRA motor to the M+ and M- terminal block before running the example. 
 * A Vibration LRA Motor 240Hz - LRA0825BC-0167F [MIKROE-6809] is recommended.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "haptic6.h"

#ifndef MIKROBUS_POSITION_HAPTIC6
    #define MIKROBUS_POSITION_HAPTIC6 MIKROBUS_1
#endif

static haptic6_t haptic6;
static log_t logger;

/**
 * @brief Haptic 6 get button state function.
 * @details This function reads the IQS397 Button Event Flags register and
 * applies a short release debounce to filter short gaps between event reports.
 * @param[out] state : Button state, 1 for pressed and 0 for released.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t haptic6_get_button_state ( uint8_t *state );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    haptic6_cfg_t haptic6_cfg;  /**< Click config object. */

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
    haptic6_cfg_setup( &haptic6_cfg );
    HAPTIC6_MAP_MIKROBUS( haptic6_cfg, MIKROBUS_POSITION_HAPTIC6 );
    if ( I2C_MASTER_ERROR == haptic6_init( &haptic6, &haptic6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HAPTIC6_ERROR == haptic6_default_cfg ( &haptic6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t button_state = 0;
    static uint8_t haptic_state = 0;
    
    log_printf( &logger, "\r\n Waiting for button press...\r\n" );

    for ( ; ; )
    {
        if ( HAPTIC6_OK == haptic6_get_button_state( &button_state ) )
        {
            if ( button_state )
            {
                if ( 0 == haptic_state )
                {
                    log_printf( &logger, " Button pressed - Haptic active\r\n" );
                    haptic_state = 1;
                }
                haptic6_trigger( &haptic6 );
            }
            else if ( haptic_state )
            {
                haptic6_cancel( &haptic6 );
                haptic_state = 0;
                log_printf( &logger, " Button released - Haptic idle\r\n" );
                break;
            }
        }
        else
        {
            log_error( &logger, " Button state read." );
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

static err_t haptic6_get_button_state ( uint8_t *state )
{
    static uint8_t release_cnt = 0;
    uint8_t button_event = 0;

    if ( HAPTIC6_OK != haptic6_read_reg( &haptic6, HAPTIC6_REG_BUTTON_EVENTS, &button_event ) )
    {
        return HAPTIC6_ERROR;
    }

    if ( button_event & ( HAPTIC6_BUTTON_PROX | HAPTIC6_BUTTON_TOUCH ) )
    {
        release_cnt = 0;
        *state = 1;
    }
    else if ( ++release_cnt > 10 )
    {
        // Release debounced
        *state = 0;
        release_cnt = 0;
    }

    return HAPTIC6_OK;
}

// ------------------------------------------------------------------------ END
