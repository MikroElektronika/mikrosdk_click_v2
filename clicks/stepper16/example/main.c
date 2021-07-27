/*!
 * @file main.c
 * @brief Stepper16 Click example
 *
 * # Description
 * This example showcases the device's ability to control the motor.
 * It initializes the device for control and moves the motor in two 
 * directions in a variety of speeds and step resolutions for 360 degrees.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes UART and SPI communication modules, and additional  
 * pins for motor control, resets device, set's default configuration,
 * and reads its ID and sets
 *
 * ## Application Task
 * First it move motor clockwise for 360 degrees in medium speed and 
 * full step resolution. Then changes direction and moves motor for 
 * 180 degrees in slow speed and quarter step, and additional 180 degrees
 * in fast speed and 1/16 step resolution.
 *
 * @note
 * Device is powered by externam VM so for communication to work Click 
 * board should be connected on power supply from 6V to 29V. At the start of
 * application user should reset device and read it's Status register 1 to clear it.
 * After that it can communicate with device and control it noramaly.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepper16.h"

static stepper16_t stepper16;
static log_t logger;

/**
 * @brief Check error
 * @details Checks if one of error flags in context 
 * object is set and logs flag error.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @return Nothing.
 */
static void check_error ( stepper16_t *ctx );

void application_init ( void ) 
{
    uint16_t read_data = 0;
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper16_cfg_t stepper16_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    stepper16_cfg_setup( &stepper16_cfg );
    STEPPER16_MAP_MIKROBUS( stepper16_cfg, MIKROBUS_1 );
    err_t init_flag  = stepper16_init( &stepper16, &stepper16_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    if ( STEPPER16_ERROR == stepper16_default_cfg ( &stepper16 ) ) 
    {
        log_error( &logger, " Default configuration. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    stepper16_generic_read( &stepper16, STEPPER16_REG_SR4, &read_data );
    log_info( &logger, "DEV ID: %d ", ( read_data >> 3 ) );
    log_info( &logger, "REV ID: %d ", ( read_data & 3 ) );

    log_info( &logger, " Application Task " );
    stepper16_set_dir( &stepper16, 0 );
}

void application_task ( void ) 
{
    static uint8_t direction = 0;
    log_printf( &logger, "> Move 360deg in CW direction.\r\n" );
    stepper16_set_step_resolution( &stepper16, STEPPER16_STEP_RES_FULL );
    check_error( &stepper16 );
    stepper16_move_motor_angle( &stepper16, 360, STEPPER16_SPEED_MEDIUM );
    direction = !direction;
    stepper16_set_dir( &stepper16, direction );
    Delay_ms( 500 );
    log_printf( &logger, "> Move 180deg in CCW direction.\r\n" );
    stepper16_set_step_resolution( &stepper16, STEPPER16_STEP_RES_QUARTER );
    check_error( &stepper16 );
    stepper16_move_motor_angle( &stepper16, 180, STEPPER16_SPEED_SLOW );
    Delay_ms( 1000 );
    log_printf( &logger, "> Move 180deg in CCW direcion.\r\n" );
    stepper16_set_step_resolution( &stepper16, STEPPER16_STEP_RES_1div16 );
    check_error( &stepper16 );
    stepper16_move_motor_angle( &stepper16, 180, STEPPER16_SPEED_FAST );
    direction = !direction;
    stepper16_set_dir( &stepper16, direction );
    Delay_ms( 2000 );
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

static void check_error ( stepper16_t *ctx )
{
    if ( ctx->spierr )
        log_error( &logger, "SPI" );
    if ( ctx->uv )
        log_error( &logger, "Under voltage detection." );
    if ( ctx->eldef )
        log_error( &logger, "Eletrical defect." );
    if ( ctx->tsd )
        log_error( &logger, "Thermal shutdown." );
    if ( ctx->tw )
        log_error( &logger, "Thermal warning." );
}

// ------------------------------------------------------------------------ END
