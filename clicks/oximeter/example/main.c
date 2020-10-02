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
 * in enabled mode and LEDX2 (IR diode) to active state. On Oximeter click the photodiode is connected on PD1 input,
 * and because we will observe the Channel 1 in this example (CH1 is enabled). Before the device configuration, the
 * SW reset will be performed and on this way we will put the registers in initial state.
 * 
 * ## Application Task  
 * Gets data when IR diode (LEDX2) is enabled, and after that gets data when LED diode
 * (LEDX1) is enabled. Repeats operation 10 times and then calculates the average value for both results.
 * This results logs on serial plot as graphic view.
 * Note: For this example you must have the serial plot application.
 * The IR diode is internal connected on LEDX2 input, and the LED diode is internal connected on LEDX1 input.
 * The photodiode is internal connected on PD1 input.
 * When we want to perform some register configuration we must first put the device in Program Operating Mode, then we can
 * set the desired register to the desired value, and when we finished, then we can put the device back to the Normal Operating Mode.
 * 

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

static uint32_t res_slot[ 100 ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void oxim_write_res ( uint32_t data_write )
{
    log_printf( &logger, "%d\r\n", data_write );
}

void oxim_plot ( uint32_t buff1, uint32_t buff2 )
{
    log_printf( &logger, "%d, %d\r\n", buff1, buff2 );
}

void oxim_plot_display ( void )
{
    uint8_t num_sampl;
    enable_t main_enable;
    res_slot[ 1 ] = 0;
    res_slot[ 2 ] = 0;

    for ( num_sampl = 0; num_sampl < 10; num_sampl++ )
    {
        oxim_set_mode( &oximeter, OXIM_DEV_PROGRAM_OP_MODE );

        main_enable.enable_slot = OXIM_DIS_SLOT;
        main_enable.enable_photodiode = OXIM_PD1_PD2_PD3_PD4_CONN;
        main_enable.enable_led = OXIM_LEDX1_EN;

        oxim_set_time_slot_b( &oximeter, &main_enable, OXIM_SLOT_NORM_OP_MODE );

        main_enable.enable_slot = OXIM_EN_SLOT;
        main_enable.enable_photodiode = OXIM_PD1_PD2_PD3_PD4_CONN;
        main_enable.enable_led = OXIM_LEDX2_EN;

        oxim_set_time_slot_a( &oximeter, &main_enable, OXIM_SLOT_NORM_OP_MODE );

        oxim_set_mode( &oximeter, OXIM_DEV_NORMAL_OP_MODE );

        oxim_read_data( &oximeter, &res_slot[ 0 ], OXIM_AVERAGE_RES_MODE );
        res_slot[ 1 ] += res_slot[ 0 ];

        oxim_set_mode( &oximeter, OXIM_DEV_PROGRAM_OP_MODE );

        main_enable.enable_slot = OXIM_DIS_SLOT;
        main_enable.enable_photodiode = OXIM_PD1_PD2_PD3_PD4_CONN;
        main_enable.enable_led = OXIM_LEDX2_EN;

        oxim_set_time_slot_a( &oximeter, &main_enable, OXIM_SLOT_NORM_OP_MODE );

        main_enable.enable_slot = OXIM_EN_SLOT;
        main_enable.enable_photodiode = OXIM_PD1_PD2_PD3_PD4_CONN;
        main_enable.enable_led = OXIM_LEDX1_EN;

        oxim_set_time_slot_b( &oximeter, &main_enable, OXIM_SLOT_NORM_OP_MODE );
        oxim_set_mode( &oximeter, OXIM_DEV_NORMAL_OP_MODE );

        oxim_read_data( &oximeter, &res_slot[ 0 ], OXIM_AVERAGE_RES_MODE );
        res_slot[ 2 ] += res_slot[ 0 ];
    }

    res_slot[ 1 ] /= 10;
    res_slot[ 2 ] /= 10;
    oxim_plot( res_slot[ 1 ], res_slot[ 2 ] );
}

void oxim_uart_display ( void )
{
    uint8_t num_sampl;
    enable_t main_enable;
    uint8_t temp_cnt;
    uint32_t tmp_data;
    uint32_t res_slot_b[ 100 ];
    oxim_set_mode( &oximeter, OXIM_DEV_PROGRAM_OP_MODE );

    main_enable.enable_slot = OXIM_DIS_SLOT;
    main_enable.enable_photodiode = OXIM_PD1_PD2_PD3_PD4_CONN;
    main_enable.enable_led = OXIM_LEDX1_EN;

    oxim_set_time_slot_b( &oximeter, &main_enable, OXIM_SLOT_NORM_OP_MODE );

    main_enable.enable_slot = OXIM_EN_SLOT;
    main_enable.enable_photodiode = OXIM_PD1_PD2_PD3_PD4_CONN;
    main_enable.enable_led = OXIM_LEDX2_EN;

    oxim_set_time_slot_a( &oximeter, &main_enable, OXIM_SLOT_NORM_OP_MODE );
    oxim_set_mode( &oximeter, OXIM_DEV_NORMAL_OP_MODE );

    for ( num_sampl = 0; num_sampl < 100; num_sampl++ )
    {
        oxim_read_data( &oximeter, &tmp_data, OXIM_AVERAGE_RES_MODE );
        res_slot[ num_sampl ] = tmp_data;
    }
    Delay_ms( 300 );

    oxim_set_mode( &oximeter, OXIM_DEV_PROGRAM_OP_MODE );

    main_enable.enable_slot = OXIM_DIS_SLOT;
    main_enable.enable_photodiode = OXIM_PD1_PD2_PD3_PD4_CONN;
    main_enable.enable_led = OXIM_LEDX2_EN;

    oxim_set_time_slot_a( &oximeter, &main_enable, OXIM_SLOT_NORM_OP_MODE );

    main_enable.enable_slot = OXIM_EN_SLOT;
    main_enable.enable_photodiode = OXIM_PD1_PD2_PD3_PD4_CONN;
    main_enable.enable_led = OXIM_LEDX1_EN;

    oxim_set_time_slot_b( &oximeter, &main_enable, OXIM_SLOT_NORM_OP_MODE );
    oxim_set_mode( &oximeter, OXIM_DEV_NORMAL_OP_MODE );
    for ( num_sampl = 0; num_sampl < 100; num_sampl++ )
    {
        oxim_read_data( &oximeter, &tmp_data, OXIM_AVERAGE_RES_MODE );
        res_slot_b[ num_sampl ] = tmp_data;
    }
    Delay_ms( 300 );

    oxim_set_mode( &oximeter, OXIM_DEV_PROGRAM_OP_MODE );

    main_enable.enable_slot = OXIM_DIS_SLOT;
    main_enable.enable_photodiode = OXIM_PD1_PD2_PD3_PD4_CONN;
    main_enable.enable_led = OXIM_LEDX1_EN;

    oxim_set_time_slot_b( &oximeter, &main_enable, OXIM_SLOT_NORM_OP_MODE );

    main_enable.enable_slot = OXIM_DIS_SLOT;
    main_enable.enable_photodiode = OXIM_PD1_PD2_PD3_PD4_CONN;
    main_enable.enable_led = OXIM_LEDX2_EN;

    oxim_set_time_slot_a( &oximeter, &main_enable, OXIM_SLOT_NORM_OP_MODE );
    oxim_set_mode( &oximeter, OXIM_DEV_NORMAL_OP_MODE );

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

        Delay_ms( 10 );
    }
}

void oxim_logs_results( void )
{
    oxim_read_data( &oximeter, &res_slot[ 0 ], OXIM_AVERAGE_RES_MODE );

    if ( oximeter.result_mode_check == 0 )
    {
        log_printf( &logger, "Average result is: " );
    }
    else
    {
        log_printf( &logger, "Sum result is: " );
    }

    switch ( oximeter.enabled_chann )
    {
        case OXIM_CH1_EN:
        {
            log_printf( &logger, "PD1: " );
            oxim_write_res( res_slot[ 0 ] );
            break;
        }
        case OXIM_CH2_EN:
        {
            log_printf(&logger, "PD2: ");
            oxim_write_res( res_slot[ 1 ] );
            break;
        }
        case OXIM_CH1_CH2_EN:
        {
            log_printf( &logger, "PD1: " );
            oxim_write_res( res_slot[ 0 ] );
            log_printf( &logger, "PD2: " );
            oxim_write_res( res_slot[ 1 ] );
            break;
        }
        case OXIM_CH3_CH4_EN:
        {
            log_printf( &logger, "PD3: " );
            oxim_write_res( res_slot[ 2 ] );
            log_printf( &logger, "PD4: " );
            oxim_write_res( res_slot[ 3 ] );
            break;
        }
        case OXIM_CH2_CH3_CH4_EN:
        {
            log_printf( &logger, "PD2: " );
            oxim_write_res( res_slot[ 1 ] );
            log_printf( &logger, "PD3: " );
            oxim_write_res( res_slot[ 2 ] );
            log_printf( &logger, "PD4: " );
            oxim_write_res( res_slot[ 3 ] );
            break;
        }
        case OXIM_ALL_CHANN_EN:
        {
            log_printf( &logger, "PD1: " );
            oxim_write_res( res_slot[ 0 ] );
            log_printf( &logger, "PD2: " );
            oxim_write_res( res_slot[ 1 ] );
            log_printf( &logger, "PD3: " );
            oxim_write_res( res_slot[ 2 ] );
            log_printf( &logger, "PD4: " );
            oxim_write_res( res_slot[ 3 ]);
            break;
        }
        default:
        {
            break;
        }
    }
    log_printf( &logger, "\r\n" );

    Delay_ms( 200 );
}
// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    oximeter_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    oximeter_cfg_setup( &cfg );
    OXIMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    oximeter_init( &oximeter, &cfg );
    oximeter_default_cfg( &oximeter );
}

void application_task ( void )
{
    oxim_plot_display();
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}


// ------------------------------------------------------------------------ END
