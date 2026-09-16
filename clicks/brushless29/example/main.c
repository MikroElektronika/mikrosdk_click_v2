/*!
 * @file main.c
 * @brief Brushless 29 Click example
 *
 * # Description
 * This example demonstrates motor speed and direction control with Brushless 29 Click. 
 * It sweeps the common motor command from zero to maximum and back to zero in both
 * directions using the selected PWM or SPI speed mode.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the communication and applies the default motor-control configuration.
 *
 * ## Application Task
 * Reads the controller status, runs a stepped motor-speed sweep clockwise,
 * waits for the motor to stop, and repeats the sweep counter-clockwise.
 *
 * @note
 * Connect the external motor supply to VM, the three motor phases to SHA, SHB, and SHC,
 * and the Hall sensor connector to J2 before running the example. The library applies
 * each command through the speed mode selected by #BRUSHLESS29_SPEED_MODE.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "brushless29.h"

#ifndef MIKROBUS_POSITION_BRUSHLESS29
    #define MIKROBUS_POSITION_BRUSHLESS29 MIKROBUS_1
#endif

static brushless29_t brushless29;
static log_t logger;

/**
 * @brief Brushless 29 motor speed sweep function.
 * @details This function increases the common motor speed command from zero
 * to maximum and then decreases it back to zero in #APP_SPEED_STEP increments.
 * The library applies each command through the speed mode selected by #BRUSHLESS29_SPEED_MODE.
 * The first active command is held before acceleration resumes.
 * @param[in] direction : Motor rotation direction.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The motor is returned to zero speed before this function exits.
 */
static err_t application_speed_sweep ( uint8_t direction );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless29_cfg_t brushless29_cfg;  /**< Click config object. */

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
    brushless29_cfg_setup( &brushless29_cfg );
    BRUSHLESS29_MAP_MIKROBUS( brushless29_cfg, MIKROBUS_POSITION_BRUSHLESS29 );
    if ( BRUSHLESS29_OK != brushless29_init( &brushless29, &brushless29_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS29_OK != brushless29_default_cfg ( &brushless29 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t pin_status = 0;
    err_t error_flag = BRUSHLESS29_OK;

    if ( !brushless29_get_int_pin ( &brushless29 ) )
    {
        error_flag = brushless29_read_exp_reg ( &brushless29, BRUSHLESS29_EXP_REG_INPUT, &pin_status );
        if ( BRUSHLESS29_ERROR == error_flag )
        {
            log_error( &logger, " Status read." );
            brushless29_stop_motor( &brushless29 );
        }
        else
        {
            if ( 0 == ( pin_status & BRUSHLESS29_EXP_PIN_PG ) )
            {
                log_error( &logger, " Motor supply is not ready." );
                error_flag = BRUSHLESS29_ERROR; 
            }
            if ( 0 == ( pin_status & BRUSHLESS29_EXP_PIN_FAULT ) )
            {
                log_error( &logger, " Gate driver fault." );
                brushless29_stop_motor( &brushless29 );
                error_flag = BRUSHLESS29_ERROR; 
            }
        }
    }

    if ( BRUSHLESS29_OK == error_flag )
    {
        log_printf( &logger, " Direction: clockwise\r\n" );
        error_flag = application_speed_sweep( BRUSHLESS29_DIR_CW );

        if ( BRUSHLESS29_OK == error_flag )
        {
            log_printf( &logger, " Stop motor\r\n\n" );
            error_flag = brushless29_stop_motor( &brushless29 );
        }

        if ( BRUSHLESS29_OK == error_flag )
        {
            log_printf( &logger, " Direction: counter-clockwise\r\n" );
            error_flag = application_speed_sweep( BRUSHLESS29_DIR_CCW );
        }

        if ( BRUSHLESS29_ERROR == error_flag )
        {
            log_error( &logger, " Motor control." );
        }

        log_printf( &logger, " Stop motor\r\n\n" );
        brushless29_stop_motor( &brushless29 );
    }

    Delay_ms( 1000 );
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

static err_t application_speed_sweep ( uint8_t direction )
{
    #define APP_SPEED_STEP  16
    #define APP_START_SPEED 32

    uint16_t speed = APP_START_SPEED;
    err_t error_flag = BRUSHLESS29_OK;

    // The driver converts this command to PWM duty or a register 13 value.
    while ( ( BRUSHLESS29_OK == error_flag ) && ( speed <= BRUSHLESS29_SPEED_MAX ) )
    {
        error_flag = brushless29_run_motor( &brushless29, direction, speed );

        if ( BRUSHLESS29_OK == error_flag )
        {
            log_printf( &logger, " Speed command: %u\r\n", speed );

            // Hold the first active command for forced commutation startup.
            if ( APP_START_SPEED == speed )
            {
                log_printf( &logger, " Startup delay\r\n" );
                Delay_ms( 1000 );
                Delay_ms( 1000 );
                Delay_ms( 1000 );
                Delay_ms( 1000 );
            }
            else
            {
                Delay_ms( 100 );
            }
            speed += APP_SPEED_STEP;
        }
    }

    // Return to zero so the direction can be changed without applied drive.
    if ( BRUSHLESS29_OK == error_flag )
    {
        speed = BRUSHLESS29_SPEED_MAX - APP_SPEED_STEP;
    }

    while ( ( BRUSHLESS29_OK == error_flag ) && ( speed > BRUSHLESS29_SPEED_MIN ) )
    {
        error_flag = brushless29_run_motor( &brushless29, direction, speed );

        if ( BRUSHLESS29_OK == error_flag )
        {
            log_printf( &logger, " Speed command: %u\r\n", speed );
            Delay_ms( 100 );
            speed -= APP_SPEED_STEP;
        }
    }

    if ( BRUSHLESS29_OK == error_flag )
    {
        error_flag = brushless29_run_motor( &brushless29, direction, BRUSHLESS29_SPEED_MIN );
        log_printf( &logger, " Speed command: 0\r\n" );
    }

    return error_flag;
}

// ------------------------------------------------------------------------ END
