/*!
 * \file 
 * \brief ProxFusion2 Click example
 * 
 * # Description
 * This example demontrates the use of ProxFusion 2 Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes Driver init and configuraton and init chip
 * 
 * ## Application Task  
 * 1) Checks whether Touch is detected and measures the output detection.
 * 2) Measures Ambient lighting - whether it's Light or Dark, ALS range and ALS output.
 * 3) Checks the orientation of the magnet and measures the HALL output.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "proxfusion2.h"

// ------------------------------------------------------------------ VARIABLES

static proxfusion2_t proxfusion2;
static log_t logger;

static uint8_t als_range;
static uint8_t dark_light_ambient;
static uint8_t hall_detect;
static uint8_t touch;
static uint16_t data_read;


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    proxfusion2_cfg_t cfg;
    uint8_t check_init;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    proxfusion2_cfg_setup( &cfg );
    PROXFUSION2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    check_init = proxfusion2_init( &proxfusion2, &cfg );
    Delay_ms( 300 );
    if ( check_init == PROXFUSION2_INIT_ERROR )
    {
        log_info( &logger, "---- !ERROR INIT! ----" );
        for( ; ; );
    }
    check_init = proxfusion2_default_cfg( &proxfusion2 );
    
    if ( check_init != 0 )
    {
        log_printf( &logger, "---- !ERROR CFG! ----\r\n" );
        for( ; ; );
    }
}

void application_task ( void )
{

    touch = proxfusion2_read_byte( &proxfusion2 , 0x13);
    if ( ( touch & 0x02 ) != 0 )
    {
        log_printf( &logger, "TOUCH: YES    ");
    }
    else
    {
        log_printf( &logger, "TOUCH: NO     ");
    }
    data_read = proxfusion2_read_data( &proxfusion2 , PROXFUSION2_HYSTERESIS_UI_OUTPUT );
    log_printf( &logger, "T - UI: %d        ", data_read);
 
    dark_light_ambient = proxfusion2_detect_dark_light( &proxfusion2, &als_range );
    if ( dark_light_ambient == PROXFUSION2_DARK_AMBIENT )
    {
        log_printf( &logger, "AMBIENT: DARK     " );
    }
    else
    {
        log_printf( &logger, "AMBIENT: LIGHT        " );
    }
    log_printf( &logger, "ALS RANGE: %d     ", als_range );
 
    data_read = proxfusion2_read_data( &proxfusion2, PROXFUSION2_ALS_UI_OUTPUT );

    log_printf( &logger, "ALS UI: %d        ", data_read );
 
    hall_detect = proxfusion2_detect_hall( &proxfusion2 );
    if ( hall_detect != 0)
    {
        if ( hall_detect == 1 )
        {
            log_printf( &logger, "HALL: NORTH       " );
        }
        else
        {
            log_printf( &logger, "HALL: SOUTH       " );
        }
    }
    data_read = proxfusion2_read_data( &proxfusion2, PROXFUSION2_HALL_EFFECT_UI_OUTPUT );
    log_printf( &logger, "HALL UI: %d\r\n", data_read );
    
    Delay_ms( 1000 );
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
