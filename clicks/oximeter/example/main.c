/*!
 * \file 
 * \brief Oximeter Click example
 * 
 * # Description
 * This application collects data from the sensor, calculates it and then logs
 * the result.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and performs the device configuration which puts Time Slot A
 * in enabled mode and LEDX2 (IR diode) to active state.  Before the device configuration, the
 * SW reset will be performed and in this way we will put the registers in initial state.
 * 
 * ## Application Task  
 * Logs PD1-PD4 data on USB UART
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "oximeter.h"

// ------------------------------------------------------------------ VARIABLES

static oximeter_t oximeter;
static log_t logger;

static uint32_t res_slot[ 100 ] = { 0 };

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void oximeter_write_res ( uint32_t data_write )
{
    log_printf( &logger, "%u\r\n", data_write );
}

void oximeter_plot ( uint32_t buff1, uint32_t buff2 )
{
    log_printf( &logger, "%u, %u\r\n", buff1, buff2 );
}

void oximeter_plot_display ( void )
{
    uint8_t num_sampl = 0;
    oximeter_enable_t main_enable;
    res_slot[ 1 ] = 0;
    res_slot[ 2 ] = 0;

    for ( num_sampl = 0; num_sampl < 10; num_sampl++ )
    {
        oximeter_set_mode( &oximeter, OXIMETER_DEV_PROGRAM_OP_MODE );

        main_enable.enable_slot = OXIMETER_DIS_SLOT;
        main_enable.enable_photodiode = OXIMETER_PD1_PD2_PD3_PD4_CONN;
        main_enable.enable_led = OXIMETER_LEDX1_EN;

        oximeter_set_time_slot_b( &oximeter, &main_enable, OXIMETER_SLOT_NORM_OP_MODE );

        main_enable.enable_slot = OXIMETER_EN_SLOT;
        main_enable.enable_photodiode = OXIMETER_PD1_PD2_PD3_PD4_CONN;
        main_enable.enable_led = OXIMETER_LEDX2_EN;

        oximeter_set_time_slot_a( &oximeter, &main_enable, OXIMETER_SLOT_NORM_OP_MODE );

        oximeter_set_mode( &oximeter, OXIMETER_DEV_NORMAL_OP_MODE );

        oximeter_read_data( &oximeter, &res_slot[ 0 ], OXIMETER_AVERAGE_RES_MODE );
        res_slot[ 1 ] += res_slot[ 0 ];

        oximeter_set_mode( &oximeter, OXIMETER_DEV_PROGRAM_OP_MODE );

        main_enable.enable_slot = OXIMETER_DIS_SLOT;
        main_enable.enable_photodiode = OXIMETER_PD1_PD2_PD3_PD4_CONN;
        main_enable.enable_led = OXIMETER_LEDX2_EN;

        oximeter_set_time_slot_a( &oximeter, &main_enable, OXIMETER_SLOT_NORM_OP_MODE );

        main_enable.enable_slot = OXIMETER_EN_SLOT;
        main_enable.enable_photodiode = OXIMETER_PD1_PD2_PD3_PD4_CONN;
        main_enable.enable_led = OXIMETER_LEDX1_EN;

        oximeter_set_time_slot_b( &oximeter, &main_enable, OXIMETER_SLOT_NORM_OP_MODE );
        oximeter_set_mode( &oximeter, OXIMETER_DEV_NORMAL_OP_MODE );

        oximeter_read_data( &oximeter, &res_slot[ 0 ], OXIMETER_AVERAGE_RES_MODE );
        res_slot[ 2 ] += res_slot[ 0 ];
    }

    res_slot[ 1 ] /= 10;
    res_slot[ 2 ] /= 10;
    oximeter_plot( res_slot[ 1 ], res_slot[ 2 ] );
}

void oximeter_uart_display ( void )
{
    uint8_t num_sampl = 0;
    oximeter_enable_t main_enable;
    uint8_t temp_cnt = 0;
    uint32_t tmp_data = 0;
    uint32_t res_slot_b[ 100 ] = { 0 };
    oximeter_set_mode( &oximeter, OXIMETER_DEV_PROGRAM_OP_MODE );

    main_enable.enable_slot = OXIMETER_DIS_SLOT;
    main_enable.enable_photodiode = OXIMETER_PD1_PD2_PD3_PD4_CONN;
    main_enable.enable_led = OXIMETER_LEDX1_EN;

    oximeter_set_time_slot_b( &oximeter, &main_enable, OXIMETER_SLOT_NORM_OP_MODE );

    main_enable.enable_slot = OXIMETER_EN_SLOT;
    main_enable.enable_photodiode = OXIMETER_PD1_PD2_PD3_PD4_CONN;
    main_enable.enable_led = OXIMETER_LEDX2_EN;

    oximeter_set_time_slot_a( &oximeter, &main_enable, OXIMETER_SLOT_NORM_OP_MODE );
    oximeter_set_mode( &oximeter, OXIMETER_DEV_NORMAL_OP_MODE );

    for ( num_sampl = 0; num_sampl < 100; num_sampl++ )
    {
        oximeter_read_data( &oximeter, &tmp_data, OXIMETER_AVERAGE_RES_MODE );
        res_slot[ num_sampl ] = tmp_data;
    }
    Delay_ms ( 300 );

    oximeter_set_mode( &oximeter, OXIMETER_DEV_PROGRAM_OP_MODE );

    main_enable.enable_slot = OXIMETER_DIS_SLOT;
    main_enable.enable_photodiode = OXIMETER_PD1_PD2_PD3_PD4_CONN;
    main_enable.enable_led = OXIMETER_LEDX2_EN;

    oximeter_set_time_slot_a( &oximeter, &main_enable, OXIMETER_SLOT_NORM_OP_MODE );

    main_enable.enable_slot = OXIMETER_EN_SLOT;
    main_enable.enable_photodiode = OXIMETER_PD1_PD2_PD3_PD4_CONN;
    main_enable.enable_led = OXIMETER_LEDX1_EN;

    oximeter_set_time_slot_b( &oximeter, &main_enable, OXIMETER_SLOT_NORM_OP_MODE );
    oximeter_set_mode( &oximeter, OXIMETER_DEV_NORMAL_OP_MODE );
    for ( num_sampl = 0; num_sampl < 100; num_sampl++ )
    {
        oximeter_read_data( &oximeter, &tmp_data, OXIMETER_AVERAGE_RES_MODE );
        res_slot_b[ num_sampl ] = tmp_data;
    }
    Delay_ms ( 300 );

    oximeter_set_mode( &oximeter, OXIMETER_DEV_PROGRAM_OP_MODE );

    main_enable.enable_slot = OXIMETER_DIS_SLOT;
    main_enable.enable_photodiode = OXIMETER_PD1_PD2_PD3_PD4_CONN;
    main_enable.enable_led = OXIMETER_LEDX1_EN;

    oximeter_set_time_slot_b( &oximeter, &main_enable, OXIMETER_SLOT_NORM_OP_MODE );

    main_enable.enable_slot = OXIMETER_DIS_SLOT;
    main_enable.enable_photodiode = OXIMETER_PD1_PD2_PD3_PD4_CONN;
    main_enable.enable_led = OXIMETER_LEDX2_EN;

    oximeter_set_time_slot_a( &oximeter, &main_enable, OXIMETER_SLOT_NORM_OP_MODE );
    oximeter_set_mode( &oximeter, OXIMETER_DEV_NORMAL_OP_MODE );

    for ( num_sampl = 0; num_sampl < 100; num_sampl++ )
    {
        temp_cnt = 0;
        while ( res_slot[ num_sampl ] >= 100 )
        {
            log_printf( &logger, "." );
            temp_cnt++;
            res_slot[ num_sampl ] -= 100;
        }
        while ( temp_cnt <= 35 )
        {
            log_printf( &logger, "_" );
            temp_cnt++;
        }
        log_printf( &logger, "|||" );

        temp_cnt = 0;
        while ( res_slot_b[ num_sampl ] >= 100 )
        {
            log_printf( &logger, "." );
            temp_cnt++;
            res_slot_b[ num_sampl ] -= 100;
        }
        while ( temp_cnt <= 35 )
        {
            log_printf( &logger, "_" );
            temp_cnt++;
        }
        log_printf( &logger, "\r\n" );

        Delay_ms ( 10 );
    }
}

void oximeter_logs_results( void )
{
    oximeter_read_data( &oximeter, &res_slot[ 0 ], OXIMETER_AVERAGE_RES_MODE );

    if ( oximeter.result_mode_check == 0 )
    {
        log_printf( &logger, "Average result is: \r\n" );
    }
    else
    {
        log_printf( &logger, "Sum result is: \r\n" );
    }

    switch ( oximeter.enabled_chann )
    {
        case OXIMETER_CH1_EN:
        {
            log_printf( &logger, "PD1: " );
            oximeter_write_res( res_slot[ 0 ] );
            break;
        }
        case OXIMETER_CH2_EN:
        {
            log_printf(&logger, "PD2: ");
            oximeter_write_res( res_slot[ 1 ] );
            break;
        }
        case OXIMETER_CH1_CH2_EN:
        {
            log_printf( &logger, "PD1: " );
            oximeter_write_res( res_slot[ 0 ] );
            log_printf( &logger, "PD2: " );
            oximeter_write_res( res_slot[ 1 ] );
            break;
        }
        case OXIMETER_CH3_CH4_EN:
        {
            log_printf( &logger, "PD3: " );
            oximeter_write_res( res_slot[ 2 ] );
            log_printf( &logger, "PD4: " );
            oximeter_write_res( res_slot[ 3 ] );
            break;
        }
        case OXIMETER_CH2_CH3_CH4_EN:
        {
            log_printf( &logger, "PD2: " );
            oximeter_write_res( res_slot[ 1 ] );
            log_printf( &logger, "PD3: " );
            oximeter_write_res( res_slot[ 2 ] );
            log_printf( &logger, "PD4: " );
            oximeter_write_res( res_slot[ 3 ] );
            break;
        }
        case OXIMETER_ALL_CHANN_EN:
        {
            log_printf( &logger, "PD1: " );
            oximeter_write_res( res_slot[ 0 ] );
            log_printf( &logger, "PD2: " );
            oximeter_write_res( res_slot[ 1 ] );
            log_printf( &logger, "PD3: " );
            oximeter_write_res( res_slot[ 2 ] );
            log_printf( &logger, "PD4: " );
            oximeter_write_res( res_slot[ 3 ]);
            break;
        }
        default:
        {
            break;
        }
    }
    log_printf( &logger, "-------------------------\r\n" );

    Delay_ms ( 300 );
}
// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    oximeter_cfg_t cfg;

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
    oximeter_cfg_setup( &cfg );
    OXIMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    oximeter_init( &oximeter, &cfg );
    oximeter_default_cfg( &oximeter );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    oximeter_logs_results( );
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


// ------------------------------------------------------------------------ END
