/*!
 * @file main.c
 * @brief 4D - display Click Example.
 *
 * # Description
 * This example demonstrates the use of 4D - display Click with a ViSi-Genie display.
 * The Start switch enables a simulated speed sweep from 0 to 300 and back to 0,
 * shown on the slider, gauge, digits, and speed indicators.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger, maps the Click pins, and opens the display UART at 115200 baud.
 *
 * ## Application Task
 * Resets and configures the display, initializes its objects, and turns on the Ready LED.
 * Polls the Start switch and updates the speed display while the switch is enabled.
 * Stopping clears the speed indicators. Communication errors restart display initialization.
 *
 * @note
 * Create a Workshop4 ViSi-Genie project for the connected display, using the standard
 * serial protocol at 115200 baud, 8 data bits, no parity, and one stop bit (not multidrop).
 * Make Form0 the startup form and place these objects on it, keeping the indexes shown:
 * - Dipswitch0: two positions, value 0 for Stop and 1 for Start.
 * - Slider0 and Coolgauge0: minimum 0 and maximum 300.
 * - Leddigits0: four digits and one decimal place; the host sends 3000 to display 300.0.
 * - Led0: Start status; Led1: Ready status. Both use 0 for off and 1 for on.
 * - Userled0: Fast (speed >= 200); Userled1: Medium (speed >= 100);
 *   Userled2: Slow (speed > 0). These indicators also use values 0 and 1.
 * Set initial values to zero. Leave form and object event handlers empty, including
 * OnChanged and OnChanging: no automatic reports or object links are needed, as the
 * host polls Dipswitch0 and writes the other objects. Labels and positions may be changed.
 * Compile and program the display project with a suitable 4D Systems programming adapter.
 * Copy its generated graphics files to a microSD card formatted for the selected display,
 * then insert the card before power-up. The Click board does not create or upload the UI.
 * Wait for Ready before enabling Start. Use a separate UART for the logger.
 * Select a suitable 5 V supply with PWR SEL and connect the display with power removed.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "c4ddisplay.h"

#ifndef MIKROBUS_POSITION_4DDISPLAY
    #define MIKROBUS_POSITION_4DDISPLAY MIKROBUS_1
#endif

/**
 * @brief 4D - display Click example object indexes.
 * @details These macros identify the display object instances required by this example.
 * @note Dipswitch, Slider, Coolgauge, and Leddigits each use instance zero.
 */
#define APP_OBJECT_INDEX                0
#define APP_START_LED                   0
#define APP_READY_LED                   1
#define APP_FAST_LED                    0
#define APP_MEDIUM_LED                  1
#define APP_SLOW_LED                    2

/**
 * @brief 4D - display Click example speed settings.
 * @details These macros define the simulated speed range, step, and indicator thresholds.
 * @note Leddigits0 has one decimal place, so its integer value is multiplied by ten.
 */
#define APP_SPEED_MAX                   300
#define APP_SPEED_STEP                  5
#define APP_SPEED_MEDIUM                100
#define APP_SPEED_FAST                  200
#define APP_DIGITS_SCALE                10

static c4ddisplay_t c4ddisplay;         /**< Click context object. */
static log_t logger;                    /**< Logger context object. */
static uint16_t app_speed = 0;          /**< Last successfully displayed speed. */
static uint8_t app_speed_rising = 1;    /**< Nonzero during the increasing half of the sweep. */
static uint8_t app_running = 0;         /**< Last displayed Start state. */
static uint8_t app_ready = 0;           /**< Nonzero after every startup command succeeds. */

/**
 * @brief 4D - display Click example startup function.
 * @details This function resets the display, clears the demo objects, and enables the Ready LED.
 * @param[in,out] ctx : Click context object.
 * See #c4ddisplay_t object definition for detailed explanation.
 * @return Success or a negative #c4ddisplay_return_value_t error.
 * @note Ready is enabled only after the display acknowledges all initial object values.
 */
static err_t c4ddisplay_app_start ( c4ddisplay_t *ctx );

/**
 * @brief 4D - display Click example speed update function.
 * @details This function polls the Start switch and advances or clears the simulated speed.
 * @param[in,out] ctx : Click context object.
 * See #c4ddisplay_t object definition for detailed explanation.
 * @return Success or a negative #c4ddisplay_return_value_t error.
 * @note Leave automatic touch reports disabled in Workshop4; this example polls the switch.
 */
static err_t c4ddisplay_app_update ( c4ddisplay_t *ctx );

/**
 * @brief 4D - display Click example object update function.
 * @details This function writes the speed and running state to the configured display indicators.
 * @param[in,out] ctx : Click context object.
 * See #c4ddisplay_t object definition for detailed explanation.
 * @param[in] speed : Simulated speed from zero to APP_SPEED_MAX.
 * @param[in] running : Zero when stopped; nonzero when the Start switch is enabled.
 * @return Success or a negative #c4ddisplay_return_value_t error.
 * @note Object updates stop at the first failed acknowledgment.
 */
static err_t c4ddisplay_app_show ( c4ddisplay_t *ctx, uint16_t speed, uint8_t running );

void application_init ( void )
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    c4ddisplay_cfg_t c4ddisplay_cfg;    /**< Click config object. */

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

    // The first task call resets the display and configures the demo objects.
    c4ddisplay_cfg_setup( &c4ddisplay_cfg );
    C4DDISPLAY_MAP_MIKROBUS( c4ddisplay_cfg, MIKROBUS_POSITION_4DDISPLAY );
    if ( C4DDISPLAY_OK != c4ddisplay_init( &c4ddisplay, &c4ddisplay_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    err_t error_flag;

    if ( app_ready )
    {
        error_flag = c4ddisplay_app_update( &c4ddisplay );
    }
    else
    {
        error_flag = c4ddisplay_app_start( &c4ddisplay );
    }

    if ( C4DDISPLAY_OK != error_flag )
    {
        log_error( &logger, " Display communication: %ld", error_flag );
        app_ready = 0;
        Delay_ms( 1000 );
    }
    Delay_ms( 100 );
}

int main ( void )
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    application_init();
    for ( ; ; )
    {
        application_task();
    }
    return 0;
}

static err_t c4ddisplay_app_start ( c4ddisplay_t *ctx )
{
    err_t error_flag;

    log_printf( &logger, ">>> Initialize ViSi-Genie display.\r\n" );
    error_flag = c4ddisplay_default_cfg( ctx );
    if ( C4DDISPLAY_OK == error_flag )
    {
        error_flag = c4ddisplay_write_object( ctx, C4DDISPLAY_OBJ_LED, APP_READY_LED, 0 );
    }
    if ( C4DDISPLAY_OK == error_flag )
    {
        error_flag = c4ddisplay_write_object( ctx, C4DDISPLAY_OBJ_DIPSWITCH, APP_OBJECT_INDEX, 0 );
    }
    if ( C4DDISPLAY_OK == error_flag )
    {
        error_flag = c4ddisplay_app_show( ctx, 0, 0 );
    }
    if ( C4DDISPLAY_OK == error_flag )
    {
        error_flag = c4ddisplay_write_object( ctx, C4DDISPLAY_OBJ_LED, APP_READY_LED, 1 );
    }
    if ( C4DDISPLAY_OK == error_flag )
    {
        app_speed = 0;
        app_speed_rising = 1;
        app_running = 0;
        app_ready = 1;
        log_printf( &logger, ">>> Display ready. Enable the Start switch.\r\n" );
    }
    return error_flag;
}

static err_t c4ddisplay_app_update ( c4ddisplay_t *ctx )
{
    err_t error_flag;
    uint16_t start_value;
    uint16_t speed = app_speed;
    uint8_t running;

    error_flag = c4ddisplay_read_object( ctx, C4DDISPLAY_OBJ_DIPSWITCH, APP_OBJECT_INDEX, &start_value );
    if ( C4DDISPLAY_OK == error_flag )
    {
        running = ( 0 != start_value );
        if ( running )
        {
            // Keep the speed within the display project's 0..300 range.
            if ( app_speed_rising )
            {
                speed += APP_SPEED_STEP;
                if ( speed >= APP_SPEED_MAX )
                {
                    speed = APP_SPEED_MAX;
                    app_speed_rising = 0;
                }
            }
            else if ( speed > APP_SPEED_STEP )
            {
                speed -= APP_SPEED_STEP;
            }
            else
            {
                speed = 0;
                app_speed_rising = 1;
            }
        }
        else
        {
            speed = 0;
            app_speed_rising = 1;
        }

        // A stopped display needs no repeated writes once its indicators have been cleared.
        if ( ( speed != app_speed ) || ( running != app_running ) )
        {
            error_flag = c4ddisplay_app_show( ctx, speed, running );
            if ( C4DDISPLAY_OK == error_flag )
            {
                app_speed = speed;
                app_running = running;
                log_printf( &logger, " Speed: %u\r\n", app_speed );
            }
        }
    }
    return error_flag;
}

static err_t c4ddisplay_app_show ( c4ddisplay_t *ctx, uint16_t speed, uint8_t running )
{
    err_t error_flag;

    error_flag = c4ddisplay_write_object( ctx, C4DDISPLAY_OBJ_SLIDER, APP_OBJECT_INDEX, speed );
    if ( C4DDISPLAY_OK == error_flag )
    {
        error_flag = c4ddisplay_write_object( ctx, C4DDISPLAY_OBJ_LED_DIGITS,
                                              APP_OBJECT_INDEX, speed * APP_DIGITS_SCALE );
    }
    if ( C4DDISPLAY_OK == error_flag )
    {
        error_flag = c4ddisplay_write_object( ctx, C4DDISPLAY_OBJ_COOL_GAUGE, APP_OBJECT_INDEX, speed );
    }
    if ( C4DDISPLAY_OK == error_flag )
    {
        error_flag = c4ddisplay_write_object( ctx, C4DDISPLAY_OBJ_USER_LED,
                                              APP_FAST_LED, speed >= APP_SPEED_FAST );
    }
    if ( C4DDISPLAY_OK == error_flag )
    {
        error_flag = c4ddisplay_write_object( ctx, C4DDISPLAY_OBJ_USER_LED,
                                              APP_MEDIUM_LED, speed >= APP_SPEED_MEDIUM );
    }
    if ( C4DDISPLAY_OK == error_flag )
    {
        error_flag = c4ddisplay_write_object( ctx, C4DDISPLAY_OBJ_USER_LED, APP_SLOW_LED, speed > 0 );
    }
    if ( C4DDISPLAY_OK == error_flag )
    {
        error_flag = c4ddisplay_write_object( ctx, C4DDISPLAY_OBJ_LED, APP_START_LED, running );
    }
    return error_flag;
}

// ------------------------------------------------------------------------ END
