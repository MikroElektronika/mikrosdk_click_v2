/*!
 * @file main.c
 * @brief LightMixSens Click example
 * 
 * # Description
 * This example show usage of Light Mix Sens Click. It switches the IR light for separate and 
 * measure sectar of RGB lights. Click also measure proximity from the object using light source.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes all necessary peripherals and pins, initializes I2C driver and performs 
 * the Click board default configuration to allow ALS/Color and Proximity measurements.
 * 
 * ## Application Task  
 * Waits until ALS/Color integration cycle was done and then reads the entire measurement.
 * The all results will be sent to the selected UART terminal.
 * 
 * ## Additional Functions :
 * - prox_app - This is application function which determines the proximity results.
 * 
 *
 * @author MikroE Team
 *
 */

#include "board.h"
#include "log.h"
#include "lightmixsens.h"


static lightmixsens_t lightmixsens;
static log_t logger;
lightmixsens_data_obj lightmixsens_data;
char prox_str[ 20 ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

/**
 * @brief Light mix sens proximity function.
 * @details This is function which determines the proximity results.
 */
void prox_app ( void );

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    lightmixsens_cfg_t cfg;

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

    lightmixsens_cfg_setup( &cfg );
    LIGHTMIXSENS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lightmixsens_init( &lightmixsens, &cfg );

    lightmixsens_default_cfg( &lightmixsens );

    lightmixsens_data.lightmixsens_cdata = LIGHTMIXSENS_DUMMY_DATA;
    lightmixsens_data.lightmixsens_rdata = LIGHTMIXSENS_DUMMY_DATA;
    lightmixsens_data.lightmixsens_gdata = LIGHTMIXSENS_DUMMY_DATA;
    lightmixsens_data.lightmixsens_bdata = LIGHTMIXSENS_DUMMY_DATA;
    lightmixsens_data.lightmixsens_pdata = LIGHTMIXSENS_DUMMY_DATA;

    log_printf( &logger, "*  Light mix-sens click initialization done.  *\r\n" );
}

void application_task ( void )
{
    lightmixsens_wait_atime( &lightmixsens );
    
    lightmixsens_read_word( &lightmixsens, LIGHTMIXSENS_REG_CDATA, 
                            &lightmixsens_data.lightmixsens_cdata );
    lightmixsens_read_word( &lightmixsens, LIGHTMIXSENS_REG_RDATA, 
                            &lightmixsens_data.lightmixsens_rdata );
    lightmixsens_read_word( &lightmixsens, LIGHTMIXSENS_REG_GDATA_IRDATA, 
                            &lightmixsens_data.lightmixsens_gdata );
    lightmixsens_read_word( &lightmixsens, LIGHTMIXSENS_REG_BDATA, 
                            &lightmixsens_data.lightmixsens_bdata );
    lightmixsens_read_byte( &lightmixsens, LIGHTMIXSENS_REG_PDATA, 
                            &lightmixsens_data.lightmixsens_pdata );
    
    log_printf( &logger, "- Clear light:  %.3d lx\r\n", lightmixsens_data.lightmixsens_cdata );
    log_printf( &logger, "- Red light:    %.3d lx\r\n", lightmixsens_data.lightmixsens_rdata );
    log_printf( &logger, "- Green light:  %.3d lx\r\n", lightmixsens_data.lightmixsens_gdata );
    log_printf( &logger, "- Blue light:   %.3d lx\r\n", lightmixsens_data.lightmixsens_bdata );
    
    prox_app( );
    log_printf( &logger, "** Proximity:   %s\r\n", prox_str );
    
    log_printf( &logger, "\r\n" );
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

void prox_app ( void )
{
    float prox;
    uint8_t cnt;
    
    prox = lightmixsens_data.lightmixsens_pdata;
    prox /= 255;
    prox *= 16;
    
    for ( cnt = 0; cnt < ( uint8_t ) prox; cnt++ ) {
        prox_str[ cnt ] = '|';
    }
    
    prox_str[ cnt ] = 0;
}

// ------------------------------------------------------------------------ END
