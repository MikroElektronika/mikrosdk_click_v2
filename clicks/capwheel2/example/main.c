/*!
 * \file 
 * \brief CapWheel2 Click example
 * 
 * # Description
 * This example sets basic device configuration; Contains function for waiting RDY(INT) pin, function for getting RDY(INT) pin state,
 * function for I2C read and write with waiting for RDY(INT) pin and without waiting for RDY(INT) pin.
 * 
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes CAP Wheel 2 device
 * 
 * ## Application Task  
 * Executes one of three 'capwheel2_get_xxx_task( )' functions
 * 
 * Additional Functions :
 * 
 * - capwheel2_error( ) - Logs error message and blocks code execution in endless while loop
 * - capwheel2_get_channels_task( ) - Logs active channels in touch and halt bytes ( channels: CH0 - proximity channel, CH1, CH2, CH3 )
 * - capwheel2_get_gesture_task( ) - Logs active gestures ( gestures: tap, touch, proximity )
 * - capwheel2_get_channel_counts_task( ) - Logs channel count values for each channel
 * - capwheel2_get_channels_touch( ) - Logs touch byte active channels ( exectuted by 'capwheel2_get_channels_task( )' function )
 * - capwheel2_get_channels_halt( ) - Logs halt byte active channels ( exectuted by 'capwheel2_get_channels_task( )' function )

 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "capwheel2.h"

// ------------------------------------------------------------------ VARIABLES

static capwheel2_t capwheel2;
static log_t logger;

static uint8_t data_buffer[ 30 ];

static uint16_t channel_0_counts;
static uint16_t channel_1_counts;
static uint16_t channel_2_counts;
static uint16_t channel_3_counts;
// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void capwheel2_error( )
{
    log_info( &logger, "> error : reset system" );
    while( 1 );
}

void capwheel2_get_channels_touch( )
{
    switch ( data_buffer[ 0 ] )
    {
        case 0x00 :
        {
            log_printf( &logger, ">     |     |     |     <   \r\n" );
            break;
        }
        case 0x01 :
        {
            log_printf( &logger, ">     |     |     | CH0 <   \r\n" );
            break;
        }
        case 0x02 :
        {
            log_printf( &logger, ">     |     | CH1 |     <   \r\n" );
            break;
        }
        case 0x03 :
        {
            log_printf( &logger, ">     |     | CH1 | CH0 <   \r\n" );
            break;
        }
        case 0x04 :
        {
            log_printf( &logger, ">     | CH2 |     |     <   \r\n" );
            break;
        }
        case 0x05 :
        {
            log_printf( &logger, ">     | CH2 |     | CH0 <   \r\n" );
            break;
        }
        case 0x06 :
        {
            log_printf( &logger, ">     | CH2 | CH1 |     <   \r\n" );
            break;
        }
        case 0x07 :
        {
            log_printf( &logger, ">     | CH2 | CH1 | CH0 <   \r\n" );
            break;
        }
        case 0x08 :
        {
            log_printf( &logger, "> CH3 |     |     |     <   \r\n" );
            break;
        }
        case 0x09 :
        {
            log_printf( &logger, "> CH3 |     |     | CH0 <   \r\n" );
            break;
        }
        case 0x0A :
        {
            log_printf( &logger, "> CH3 |     | CH1 |     <   \r\n" );
            break;
        }
        case 0x0B :
        {
            log_printf( &logger, "> CH3 |     | CH1 | CH0 <   \r\n" );
            break;
        }
        case 0x0C :
        {
            log_printf( &logger, "> CH3 | CH2 |     |     <   \r\n" );
            break;
        }
        case 0x0D :
        {
            log_printf( &logger, "> CH3 | CH2 |     | CH0 <   \r\n" );
            break;
        }
        case 0x0E :
        {
            log_printf( &logger, "> CH3 | CH2 | CH1 |     <   \r\n" );
            break;
        }
        case 0x0F :
        {
            log_printf( &logger, "> CH3 | CH2 | CH1 | CH0 <   \r\n" );
            break;
        }
        default :
        {
            break;
        }
    }
}

void capwheel2_get_channels_halt( )
{
    switch ( data_buffer[ 1 ] )
    {
        case 0x00 :
        {
            log_printf( &logger, ">     |     |     |     <\r\n" );
            break;
        }
        case 0x01 :
        {
            log_printf( &logger, ">     |     |     | CH0 <\r\n" );
            break;
        }
        case 0x02 :
        {
            log_printf( &logger, ">     |     | CH1 |     <\r\n" );
            break;
        }
        case 0x03 :
        {
            log_printf( &logger, ">     |     | CH1 | CH0 <\r\n" );
            break;
        }
        case 0x04 :
        {
            log_printf( &logger, ">     | CH2 |     |     <\r\n" );
            break;
        }
        case 0x05 :
        {
            log_printf( &logger, ">     | CH2 |     | CH0 <\r\n" );
            break;
        }
        case 0x06 :
        {
            log_printf( &logger, ">     | CH2 | CH1 |     <\r\n" );
            break;
        }
        case 0x07 :
        {
            log_printf( &logger, ">     | CH2 | CH1 | CH0 <\r\n" );
            break;
        }
        case 0x08 :
        {
            log_printf( &logger, "> CH3 |     |     |     <\r\n" );
            break;
        }
        case 0x09 :
        {
            log_printf( &logger, "> CH3 |     |     | CH0 <\r\n" );
            break;
        }
        case 0x0A :
        {
            log_printf( &logger, "> CH3 |     | CH1 |     <\r\n" );
            break;
        }
        case 0x0B :
        {
            log_printf( &logger, "> CH3 |     | CH1 | CH0 <\r\n" );
            break;
        }
        case 0x0C :
        {
            log_printf( &logger, "> CH3 | CH2 |     |     <\r\n" );
            break;
        }
        case 0x0D :
        {
            log_printf( &logger, "> CH3 | CH2 |     | CH0 <\r\n" );
            break;
        }
        case 0x0E :
        {
            log_printf( &logger, "> CH3 | CH2 | CH1 |     <\r\n" );
            break;
        }
        case 0x0F :
        {
            log_printf( &logger, "> CH3 | CH2 | CH1 | CH0 <\r\n" );
            break;
        }
        default :
        {
            break;
        }
    }
}

void capwheel2_get_channels_task( )
{
    if ( capwheel2_i2c_read_wait( &capwheel2, CAPWHEEL2_TOUCH_BYTES, &data_buffer[ 0 ], 2 ) )
    {
        capwheel2_error( );
    }
    log_printf( &logger, " ");
    log_printf( &logger, ">      TOUCH BYTES      <\r\n" );
    log_printf( &logger, ">      HALT  BYTES      <\r\n" );
    capwheel2_get_channels_touch( );
    capwheel2_get_channels_halt( );
    Delay_ms( 150 );
}

void capwheel2_get_gesture_task( )
{
    if ( capwheel2_i2c_read_wait( &capwheel2, CAPWHEEL2_SYS_FLAGS, &data_buffer[ 0 ], 2 ) )
    {
        capwheel2_error( );
    }

    if ( ( data_buffer[ 1 ] & CAPWHEEL2_TAP_MASK ) == CAPWHEEL2_TAP_MASK)
    {
        log_printf( &logger, "> TAP\r\n" );
    }
    else if ( ( data_buffer[ 1 ] & CAPWHEEL2_TOUCH_MASK ) == CAPWHEEL2_TOUCH_MASK)
    {
        log_printf( &logger, "> TOUCH\r\n" );
    }
    else if ( ( data_buffer[ 1 ] & CAPWHEEL2_PROX_MASK ) == CAPWHEEL2_PROX_MASK)
    {
        log_printf( &logger, "> PROX\r\n" );
    }
    Delay_ms( 800 );
}

void capwheel2_get_channel_counts_task( )
{
    if (capwheel2_i2c_read_wait( &capwheel2, CAPWHEEL2_COUNTS, &data_buffer[ 0 ], 10))
    {
        capwheel2_error( );
    }
    channel_0_counts = data_buffer[ 3 ];
    channel_0_counts <<= 8;
    channel_0_counts |= data_buffer[ 2 ];
    channel_1_counts = data_buffer[ 5 ];
    channel_1_counts <<= 8;
    channel_1_counts |= data_buffer[ 4 ];
    channel_2_counts = data_buffer[ 7 ];
    channel_2_counts <<= 8;
    channel_2_counts |= data_buffer[ 6 ];
    channel_3_counts = data_buffer[ 9 ];
    channel_3_counts <<= 8;
    channel_3_counts |= data_buffer[ 8 ];

    log_printf( &logger, "> Channel 0  counts : %u \r\n", channel_0_counts );
    log_printf( &logger, "> Channel 1  counts : %u \r\n", channel_1_counts );
    log_printf( &logger, "> Channel 2  counts : %u \r\n", channel_2_counts );

    log_info( &logger, " ");
    Delay_ms( 150 );
}


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    capwheel2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    capwheel2_cfg_setup( &cfg );
    CAPWHEEL2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    capwheel2_init( &capwheel2, &cfg );
}

void application_task ( void )
{
    capwheel2_get_channels_task( );
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
