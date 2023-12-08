/*!
 * \file 
 * \brief RemoteTemp Click example
 * 
 * # Description
 * This application reads remote temperature data.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C driver, sets range, configures device and sets threshold values.
 * 
 * ## Application Task  
 * Executes all 'remotetemp_aux_getXxx()' functions.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "remotetemp.h"

// ------------------------------------------------------------------ VARIABLES

static remotetemp_t remotetemp;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void remotetemp_aux_get_fault ( remotetemp_t *ctx )
{
    uint8_t aux_byte[ 1 ];

    remotetemp_read( ctx, REMOTETEMP_EXTERNAL_DIODE_FAULT_STATUS, &aux_byte[ 0 ], 1 );
    if ( aux_byte[ 0 ] != 0 )
    {
        if ( ( aux_byte[ 0 ] & 0x02 ) == 0x02 )
        {
            log_printf( &logger, "  - external diode 1 \r\n" );
        }
    }
}

void remotetemp_aux_get_high_limit_status ( remotetemp_t *ctx )
{
    float internal_temp;
    float external_1_temp;
    float external_2_temp;
    uint8_t aux_byte[ 1 ];
    
    remotetemp_read( ctx, REMOTETEMP_HIGH_LIMIT_STATUS, &aux_byte[ 0 ], 1 );
    if ( aux_byte[ 0 ] != 0 )
    {
        log_printf( &logger, "> high threshold limit exceeded by : \r\n" );

        if ( ( aux_byte[ 0 ] & 0x01 ) == 0x01 )
        {
            log_printf( &logger, "  - internal diode \r\n" );
            internal_temp = remotetemp_get_internal_diode( ctx );
            log_printf( &logger, "  - temperature : %f degC \r\n", internal_temp );
        }
        if ( ( aux_byte[ 0 ] & 0x02 ) == 0x02 )
        {
            log_printf( &logger, "  - external diode 1 \r\n" );
            external_1_temp = remotetemp_get_external_diode( ctx, 1 );
            log_printf( &logger, "  - temperature : %f degC \r\n", external_1_temp );
        }
        if ( ( aux_byte[ 0 ] & 0x04 ) == 0x04 )
        {
            log_printf( &logger, "  - external diode 2 \r\n" );
            external_2_temp = remotetemp_get_external_diode( ctx, 2 );
            log_printf( &logger, "  - temperature : %f degC \r\n", external_2_temp );
        }
    }
}

void remotetemp_aux_get_low_limit_status ( remotetemp_t *ctx )
{
    float internal_temp;
    float external_1_temp;
    float external_2_temp;
    uint8_t aux_byte[ 1 ];
    
    remotetemp_read( ctx, REMOTETEMP_LOW_LIMIT_STATUS, &aux_byte[ 0 ], 1 );
    if ( aux_byte[ 0 ] != 0 )
    {
        log_printf( &logger, "> > low threshold limit exceeded by : \r\n" );

        if ( ( aux_byte[ 0 ] & 0x01 ) == 0x01 )
        {
            log_printf( &logger, "  - internal diode \r\n" );
            internal_temp = remotetemp_get_internal_diode( ctx );
            log_printf( &logger, "  - temperature : %f degC \r\n", internal_temp );
        }
        if ( ( aux_byte[ 0 ] & 0x02 ) == 0x02 )
        {
            log_printf( &logger, "  - external diode 1 \r\n" );
            external_1_temp = remotetemp_get_external_diode( ctx, 1 );
            log_printf( &logger, "  - temperature : %f degC \r\n", external_1_temp );
        }
        if ( ( aux_byte[ 0 ] & 0x04 ) == 0x04 )
        {
            log_printf( &logger, "  - external diode 2 \r\n" );
            external_2_temp = remotetemp_get_external_diode( ctx, 2 );
            log_printf( &logger, "  - temperature : %f degC \r\n", external_2_temp );
        }
    }
}

void remotetemp_aux_get_therm_limit_status ( remotetemp_t *ctx )
{
    float internal_temp;
    float external_1_temp;
    float external_2_temp;
    uint8_t aux_byte[ 1 ];
    
    remotetemp_read( ctx, REMOTETEMP_THERM_LIMIT_STATUS, &aux_byte[ 0 ], 1 );
    if ( aux_byte[ 0 ] != 0 )
    {
        log_printf( &logger, "> therm threshold limit exceeded by : \r\n" );

        if ( ( aux_byte[ 0 ] & 0x01 ) == 0x01 )
        {
            log_printf( &logger, "  - internal diode \r\n" );
            internal_temp = remotetemp_get_internal_diode( ctx );
            log_printf( &logger, "  - temperature : %f degC \r\n", internal_temp );
        }
        if ( ( aux_byte[ 0 ] & 0x02 ) == 0x02 )
        {
            log_printf( &logger, "  - external diode 1 \r\n" );
            external_1_temp = remotetemp_get_external_diode( ctx, 1 );
            log_printf( &logger, "  - temperature : %f degC \r\n", external_1_temp );
        }
        if ( ( aux_byte[ 0 ] & 0x04 ) == 0x04 )
        {
            log_printf( &logger, "  - external diode 2 \r\n" );
            external_2_temp = remotetemp_get_external_diode( ctx, 2 );
            log_printf( &logger, "  - temperature : %f degC \r\n", external_2_temp );
        }
    }
}

void remotetemp_aux_get_hottest_status ( remotetemp_t *ctx )
{
    float hottest_temp;
    uint8_t aux_byte[ 1 ];
    
    remotetemp_read( ctx, REMOTETEMP_HOTTEST_STATUS, &aux_byte[ 0 ], 1 );
    if ( aux_byte[ 0 ] != 0 )
    {
        log_printf( &logger, "> hottest diode : \r\n" );

        if ( ( aux_byte[ 0 ] & 0x01 ) == 0x01 )
        {
            log_printf( &logger, " - internal diode \r\n" );
        }
        else if ( ( aux_byte[ 0 ] & 0x02 ) == 0x02 )
        {
            log_printf( &logger, "  - external diode 1 \r\n" );
        }
        else if ( ( aux_byte[ 0 ] & 0x04 ) == 0x04 )
        {
            log_printf( &logger, "  - external diode 2 \r\n" );
        }
        hottest_temp = remotetemp_get_hottest_diode( ctx );
        log_printf( &logger, "  - temperature : %.2f degC \r\n", hottest_temp );
    }   
    log_printf( &logger, "\r\n" );
}

void application_init ( void )
{
    log_cfg_t log_cfg;
    remotetemp_cfg_t cfg;

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

    remotetemp_cfg_setup( &cfg );
    REMOTETEMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    remotetemp_init( &remotetemp, &cfg );
    
    Delay_ms( 300 );
    remotetemp_default_cfg( &remotetemp );
    log_printf( &logger, "> app init done \r\n" );
}

void application_task ( void )
{
    remotetemp_aux_get_fault( &remotetemp );
    remotetemp_aux_get_high_limit_status( &remotetemp );
    remotetemp_aux_get_low_limit_status( &remotetemp );
    remotetemp_aux_get_therm_limit_status( &remotetemp );
    remotetemp_aux_get_hottest_status( &remotetemp );
    Delay_ms( 1000 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
