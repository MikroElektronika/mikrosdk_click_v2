/*!
 * \file 
 * \brief Eeram Click example
 * 
 * # Description
 * This example show using EERAM click to store the data to the SRAM ( static RAM ) memory.
 * The data is read and written by the I2C serial communication bus, and the memory cells 
 * are organized into 2048 bytes, each 8bit wide.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * EERAM driver nitialization
 * 
 * ## Application Task  
 * Writing data to click memory and displaying the read data via UART. 
 * 
 * *note:* 
 * <pre>
 * Input Voltage:	
 *       5V ( on EERAM 5V Click)
 *       3.3V ( on EERAM 3.3V Click)
 * </pre>
 *
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "eeram.h"

// ------------------------------------------------------------------ VARIABLES

static eeram_t eeram;
static log_t logger;

static char wr_data[ 20 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };
static char rd_data[ 20 ];

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    eeram_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    eeram_cfg_setup( &cfg );
    EERAM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    eeram_init( &eeram, &cfg );
}

void application_task ( void )
{
    log_info( &logger, "Writing MikroE to  SRAM memory, from address 0x0150:" );
    eeram_write( &eeram, 0x0150, &wr_data, 9 );
    log_info( &logger, "Reading 9 bytes of SRAM memory, from address 0x0150:" );
    eeram_read( &eeram, 0x0150, &rd_data, 9 );
    log_info( &logger, "Data read: %s", rd_data );
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
