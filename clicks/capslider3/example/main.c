/*!
 * @file main.c
 * @brief Cap Slider 3 Click example
 *
 * # Description
 * This example demonstrates the use of the Cap Slider 3 Click board by initializing
 * the device and reading the current slider position. The application logs the detected
 * slider position in real-time.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and the Cap Slider 3 Click driver.
 *
 * ## Application Task
 * Continuously reads and logs the slider position detected by the Cap Slider 3 Click board.
 * 
 * @note
 * Functions for logging gestures and statuses are available but not used in this example.
 *
 * @author Stefan Filipovic
 *
 */


#include "board.h"
#include "log.h"
#include "capslider3.h"

static capslider3_t capslider3;
static log_t logger;

/**
 * @brief Cap Slider 3 log status function.
 * @details This function logs the power mode, touch, and proximity status of the Cap Slider 3 Click board.
 * @param[in] status : Status data to be logged (sys_info.sys_status).
 * @note None.
 */
static void capslider3_log_status ( uint16_t status );

/**
 * @brief Cap Slider 3 log gesture function.
 * @details This function logs the detected gestures of the Cap Slider 3 Click board.
 * @param[in] gesture : Gesture data to be logged (sys_info.gestures).
 * @note None.
 */
static void capslider3_log_gesture ( uint16_t gesture );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    capslider3_cfg_t capslider3_cfg;  /**< Click config object. */

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
    capslider3_cfg_setup( &capslider3_cfg );
    CAPSLIDER3_MAP_MIKROBUS( capslider3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == capslider3_init( &capslider3, &capslider3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CAPSLIDER3_ERROR == capslider3_default_cfg ( &capslider3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    capslider3_data_t sys_info;
    if ( CAPSLIDER3_OK == capslider3_read_data ( &capslider3, &sys_info ) )
    {
        if ( CAPSLIDER3_SLIDER_IDLE != sys_info.slider )
        {
            log_printf ( &logger, " Slider: - %u -\r\n\n", sys_info.slider );
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

static void capslider3_log_status ( uint16_t status )
{
    log_printf ( &logger, "--- STATUS ---\r\n" );
    log_printf ( &logger, " Power mode: " );
    switch ( status & CAPSLIDER3_SYSTEM_STATUS_POWER_MODE_MASK )
    {
        case CAPSLIDER3_SYSTEM_STATUS_POWER_MODE_NORMAL:
        {
            log_printf ( &logger, "NORMAL" );
            break;
        }
        case CAPSLIDER3_SYSTEM_STATUS_POWER_MODE_LP:
        {
            log_printf ( &logger, "LOW POWER" );
            break;
        }
        case CAPSLIDER3_SYSTEM_STATUS_POWER_MODE_ULP:
        {
            log_printf ( &logger, "ULTRA LOW POWER" );
            break;
        }
        case CAPSLIDER3_SYSTEM_STATUS_POWER_MODE_HALT:
        {
            log_printf ( &logger, "HALT" );
            break;
        }
        default:
        {
            break;
        }
    }

    log_printf ( &logger, "\r\n Channels in Touch: - " );
    if ( status & ( CAPSLIDER3_SYSTEM_STATUS_CH0_TOUCH | 
                    CAPSLIDER3_SYSTEM_STATUS_CH1_TOUCH | 
                    CAPSLIDER3_SYSTEM_STATUS_CH2_TOUCH ) )
    {
        if ( status & CAPSLIDER3_SYSTEM_STATUS_CH0_TOUCH )
        {
            log_printf ( &logger, "0 - " );
        }
        if ( status & CAPSLIDER3_SYSTEM_STATUS_CH1_TOUCH )
        {
            log_printf ( &logger, "1 - " );
        }
        if ( status & CAPSLIDER3_SYSTEM_STATUS_CH2_TOUCH )
        {
            log_printf ( &logger, "2 - " );
        }  
    }
    else
    {
        log_printf ( &logger, "NONE - " );
    }

    log_printf ( &logger, "\r\n Channels in Prox: - " );
    if ( status & ( CAPSLIDER3_SYSTEM_STATUS_CH0_PROX | 
                    CAPSLIDER3_SYSTEM_STATUS_CH1_PROX | 
                    CAPSLIDER3_SYSTEM_STATUS_CH2_PROX ) )
    {
        if ( status & CAPSLIDER3_SYSTEM_STATUS_CH0_PROX )
        {
            log_printf ( &logger, "0 - " );
        }
        if ( status & CAPSLIDER3_SYSTEM_STATUS_CH1_PROX )
        {
            log_printf ( &logger, "1 - " );
        }
        if ( status & CAPSLIDER3_SYSTEM_STATUS_CH2_PROX )
        {
            log_printf ( &logger, "2 - " );
        }  
    }
    else
    {
        log_printf ( &logger, "NONE - " );
    }
    log_printf ( &logger, "\r\n" );
}

static void capslider3_log_gesture ( uint16_t gesture )
{
    static uint16_t gesture_type_old = 0;
    uint16_t gesture_type = 0;
    if ( gesture & CAPSLIDER3_GESTURES_TAP )
    {
        gesture_type = CAPSLIDER3_GESTURES_TAP;
    }
    else if ( gesture & CAPSLIDER3_GESTURES_FLICK_POS )
    {
        gesture_type = CAPSLIDER3_GESTURES_FLICK_POS;
    }
    else if ( gesture & CAPSLIDER3_GESTURES_FLICK_NEG )
    {
        gesture_type = CAPSLIDER3_GESTURES_FLICK_NEG;
    }
    else if ( gesture & CAPSLIDER3_GESTURES_SWIPE_POS )
    {
        gesture_type = CAPSLIDER3_GESTURES_SWIPE_POS;
    }
    else if ( gesture & CAPSLIDER3_GESTURES_SWIPE_NEG )
    {
        gesture_type = CAPSLIDER3_GESTURES_SWIPE_NEG;
    }
    else if ( gesture & CAPSLIDER3_GESTURES_HOLD )
    {
        gesture_type = CAPSLIDER3_GESTURES_HOLD;
    }
    else if ( gesture & CAPSLIDER3_GESTURES_EVENT )
    {
        gesture_type = CAPSLIDER3_GESTURES_EVENT;
    }
    else if ( gesture & CAPSLIDER3_GESTURES_BUSY )
    {
        gesture_type = CAPSLIDER3_GESTURES_BUSY;
    }
    
    if ( gesture_type_old != gesture_type )
    {
        log_printf ( &logger, " Gesture: - " );
        if ( gesture_type & CAPSLIDER3_GESTURES_TAP )
        {
            log_printf ( &logger, "TAP" );
        }
        else if ( gesture_type & CAPSLIDER3_GESTURES_FLICK_POS )
        {
            log_printf ( &logger, "FLICK POSITIVE" );
        }
        else if ( gesture_type & CAPSLIDER3_GESTURES_FLICK_NEG )
        {
            log_printf ( &logger, "FLICK NEGATIVE" );
        }
        else if ( gesture_type & CAPSLIDER3_GESTURES_SWIPE_POS )
        {
            log_printf ( &logger, "SWIPE POSITIVE" );
        }
        else if ( gesture_type & CAPSLIDER3_GESTURES_SWIPE_NEG )
        {
            log_printf ( &logger, "SWIPE NEGATIVE" );
        }
        else if ( gesture_type & CAPSLIDER3_GESTURES_HOLD )
        {
            log_printf ( &logger, "HOLD" );
        }
        else if ( gesture_type & CAPSLIDER3_GESTURES_EVENT )
        {
            log_printf ( &logger, "EVENT" );
        }
        else if ( gesture_type & CAPSLIDER3_GESTURES_BUSY )
        {
            log_printf ( &logger, "BUSY" );
        }
        else
        {
            log_printf ( &logger, "NONE" );
        }
        log_printf ( &logger, " -\r\n" );
        gesture_type_old = gesture_type;
    }
}

// ------------------------------------------------------------------------ END
