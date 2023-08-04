/*!
 * @file main.c
 * @brief Smoke2 Click example
 *
 * # Description
 * This example is made to see how Smoke 2 clicks work. The purpose of this example is that,
 * depending on the way we choose, it collects data from the external environment about smoke,
 * processes it, and prints it via the UART terminal.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of communication modules, additional pins, Mapping pins and configures 
 * device for measurement.
 *
 * ## Application Task
 * Example shows module working depending on example mode. We can choose between:
 * EXAMPLE_MODE_PROXIMITY and EXAMPLE_MODE_SMOKE.
 *
 * Additional Functions :
 * - void smoke_example ( smoke2_t *ctx ) - Example checks if sensor data goes over threshold set.
 * - void proximity_example ( void ) - Reads sensor data and logs it.
 *
 * @author Jelena Milosavljevic
 *
 */

#include "board.h"
#include "log.h"
#include "smoke2.h"

static smoke2_t smoke2;
static log_t logger;

#define EXAMPLE_MODE_SMOKE      0
#define EXAMPLE_MODE_PROXIMITY  1

#define EXAMPLE_MODE            EXAMPLE_MODE_SMOKE

/**
 * @brief Smoke 2 Smoke example.
 * @details This function checks if sensor data is gone over thershold set.
 */
void smoke_example ( smoke2_t *ctx );

/**
 * @brief Smoke 2 Proximity example.
 * @details This function reads sensor data and logs it.
 */
void proximity_example ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    smoke2_cfg_t smoke2_cfg;      /**< Click config object. */
    
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
    smoke2_cfg_setup( &smoke2_cfg );
    SMOKE2_MAP_MIKROBUS( smoke2_cfg, MIKROBUS_1 );
    err_t init_flag  = smoke2_init( &smoke2, &smoke2_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    smoke2_soft_reset( &smoke2 );
    smoke2_set_mode( &smoke2, SMOKE2_MODE_IDLE );

    uint16_t devid = smoke2_read_data( &smoke2, SMOKE2_REG_DEVID );
    log_printf( &logger, ">> ID:  0x%.2X\r\n", ( uint16_t ) ( devid & 0xFF ) );  
    log_printf( &logger, ">> REV: 0x%.2X\r\n", ( uint16_t ) ( ( devid >> 8 ) & 0xFF ) );
    Delay_ms( 1000 );
    
    log_printf( &logger, ">> Configuration <<\r\n" );
    smoke2_default_cfg( &smoke2 ); 
    Delay_ms( 1000 ); 
    
#if ( EXAMPLE_MODE == EXAMPLE_MODE_SMOKE )
    log_printf( &logger, ">> SMOKE MODE <<\r\n" );
    log_printf( &logger, ">> Calibration <<\r\n" );
    uint16_t calib_data = smoke2_smoke_calibration( &smoke2, 500 );
    log_printf( &logger, ">> Calibration data: %u\r\n", calib_data );
#elif ( EXAMPLE_MODE == EXAMPLE_MODE_PROXIMITY )
    log_printf( &logger, ">> PROXIMITY MODE <<\r\n" );
#endif
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
#if ( EXAMPLE_MODE == EXAMPLE_MODE_SMOKE )
    smoke_example( &smoke2 );
#elif ( EXAMPLE_MODE == EXAMPLE_MODE_PROXIMITY )
    proximity_example( );
#endif
}

void main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }
}

void smoke_example ( smoke2_t *ctx ) 
{
    static uint8_t last_state = 0;
    uint8_t smoke_detected = smoke2_check_smoke( &smoke2 );
    if ( last_state != smoke_detected ) 
    {
        if ( SMOKE2_SMOKE_DETECTED == smoke_detected ) 
        {
            log_printf( &logger, ">> SMOKE_DETECTED <<\r\n" );
        }
        else if ( SMOKE2_SMOKE_NOT_DETECTED == smoke_detected ) 
        {
            log_printf( &logger, ">> SMOKE_CLEAR <<\r\n" );
        }
        else 
        {
            log_printf( &logger, ">> ERROR <<\r\n" );
            for( ; ; );
        }
        last_state = smoke_detected;
    }
}

void proximity_example ( void ) 
{
    uint16_t sens_data = 0;
    uint8_t fifo_int = 0;
    uint8_t slot_a_int = 0;
    uint8_t slot_b_int = 0;
    if ( 0 == smoke2_get_int_pin( &smoke2 ) ) 
    {
        smoke2_get_int( &smoke2, &fifo_int, &slot_a_int, &slot_b_int );
        if ( 0 != slot_a_int ) 
        {
            sens_data = smoke2_read_sens_data( &smoke2, SMOKE2_SLOT_A, SMOKE2_CHN_1 );
            log_printf( &logger, ">> DATA A: %d\r\n", sens_data );
            slot_a_int = 0;
            Delay_ms( 100 );
        }
        if ( 0 != slot_b_int ) 
        {
            sens_data = smoke2_read_sens_data( &smoke2, SMOKE2_SLOT_B, SMOKE2_CHN_1 );
            log_printf( &logger, ">> DATA B: %d\r\n", sens_data );
            slot_b_int = 0;
            Delay_ms( 100 );
        }
        if ( 0 != fifo_int ) 
        {
            log_printf( &logger, " \r\n", fifo_int );
            for ( uint8_t fifo_cnt = 0; fifo_cnt < fifo_int; fifo_cnt++ ) 
            {
                sens_data = smoke2_read_data( &smoke2, SMOKE2_REG_FIFO_ACCESS );
                log_printf( &logger, ">> FIFO: %d\r\n", sens_data );
            }
            Delay_ms( 100 );
        }
    }
}

// ------------------------------------------------------------------------ END
