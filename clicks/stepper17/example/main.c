/*!
 * @file main.c
 * @brief Stepper17 Click example
 *
 * # Description
 * This is an example application for showing Stepper 17 click 
 * ability to control motor. First, it sets default configuration, 
 * then runs motor on every turn it stops when makes a full circle 
 * and it changes direction on every iteration and on every CW 
 * movement changes step resolution.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of UART(for logging states and errors), I2C and PWM 
 * modules and additional GPIO's. Sets default configuration for click 
 * board and starts motor rotating in CW direction in 1/32 step resolution.
 *
 * ## Application Task
 * Runs motor one circle, stops and pauses for 2seconds, 
 * and runs motor in opposite direction. On every CW run it changes step 
 * resolution. It loops from 1/2 step resolution to 1/32 resolution.
 *
 * @note
 * Click is tested with motor with 1 step = 1.8degree with PWM 
 * configured with 1500Hz. You may need to lower MCU frequency 
 * to reach 1500Hz PWM frequency.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepper17.h"

#define FULL_CIRCLE 50

static stepper17_t stepper17;
static log_t logger;

/**
 * @brief Stepper 17 change step resolution.
 * @details This function changes step resolution for given diveder.
 * @param[in] resolution : step divider
 * @return Nothing.
 */
static void stepper17_set_step_resolution( uint8_t resolution );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper17_cfg_t stepper17_cfg;  /**< Click config object. */

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

    stepper17_cfg_setup( &stepper17_cfg );
    STEPPER17_MAP_MIKROBUS( stepper17_cfg, MIKROBUS_1 );
    err_t init_flag = stepper17_init( &stepper17, &stepper17_cfg );
    
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    if ( stepper17_default_cfg ( &stepper17 ) < 0 ) 
    {
        log_error( &logger, " Default Configuration. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    
    stepper17_step_resolution( &stepper17, STEPPER17_STEP_HALF_A );
    stepper17_set_dir_state( &stepper17, 1 );
    stepper17_set_en_state( &stepper17, 1 );
    
    log_info( &logger, " Application Task " );
    log_info( &logger, " Move motor CW." );
}

void application_task ( void ) 
{
    static uint32_t counter = 0;
    static uint8_t run = 1;
    static uint8_t dir = 1;
    static uint8_t turns = 1;
    static uint8_t step = 2;
    
    if ( ( 0 == stepper17_get_int_state( &stepper17 ) ) && run )
    {
        counter++;
        
        if ( counter == ( FULL_CIRCLE * turns ) )
        {
            //Stop motor
            stepper17_set_en_state( &stepper17, 0 );
            run = 0;
            log_info( &logger, " Stop motor." );

            Delay_ms( 2000 );
            
            //Change direction
            if ( dir )
            {
                log_info( &logger, " Move motor CCW." );
                dir = 0;
                stepper17_set_dir_state( &stepper17, dir );
            }
            else
            {
                log_info( &logger, " Move motor CW." );
                dir = 1;
                stepper17_set_dir_state( &stepper17, dir );
                
                if ( 32 == step )
                {
                    step = 2;
                }
                else
                {
                    step *= 2;
                }
                stepper17_set_step_resolution( step );
            }
            
            //Move motor
            stepper17_set_en_state( &stepper17, 1 );
            counter = 0;
            run = 1;
        }
        else
        {
            while ( 0 == stepper17_get_int_state( &stepper17 ) );
        }
    }
    
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

static void stepper17_set_step_resolution( uint8_t resolution )
{
    switch ( resolution )
    {
        case 2:
        {
            stepper17_step_resolution( &stepper17, STEPPER17_STEP_HALF_A );
            break;
        }
        case 4:
        {
            stepper17_step_resolution( &stepper17, STEPPER17_STEP_QUARTER );
            break;
        }
        case 8:
        {
            stepper17_step_resolution( &stepper17, STEPPER17_STEP_1DIV8 );
            break;
        }
        case 16:
        {
            stepper17_step_resolution( &stepper17, STEPPER17_STEP_1DIV16 );
            break;
        }
        case 32:
        {
            stepper17_step_resolution( &stepper17, STEPPER17_STEP_1DIV32 );
            break;
        }
        default:
        {
            log_error( &logger, " Step Resolution" );
        }
    }
}

// ------------------------------------------------------------------------ END
