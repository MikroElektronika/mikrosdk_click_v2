/*!
 * @file main.c
 * @brief EERAM5V Click example
 *
 * # Description
 * This example show using EERAM click to store the data to the SRAM ( static RAM ) memory.
 * The data is read and written by the I2C serial communication bus, and the memory cells 
 * are organized into 2048 bytes, each 8bit wide.
 * 
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * EERAM driver initialization.
 *
 * ## Application Task
 * Writing data to click memory and displaying the read data via UART. 
 *
 * @author Jelena Milosavljevic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "eeram5v.h"

// ------------------------------------------------------------------ VARIABLES

static eeram5v_t eeram5v;
static log_t logger;

static char wr_data[ 20 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };
static char rd_data[ 20 ];

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void ) {
    log_cfg_t log_cfg;            /**< Logger config object. */
    eeram5v_cfg_t eeram5v_cfg;    /**< Click config object. */

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
    
    eeram5v_cfg_setup( &eeram5v_cfg );
    EERAM5V_MAP_MIKROBUS( eeram5v_cfg, MIKROBUS_1 );
    err_t init_flag = eeram5v_init( &eeram5v, &eeram5v_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    log_info( &logger, "Writing MikroE to  SRAM memory, from address 0x0150:" );
    eeram5v_write( &eeram5v, 0x0150, &wr_data, 9 );
    log_info( &logger, "Reading 9 bytes of SRAM memory, from address 0x0150:" );
    eeram5v_read( &eeram5v, 0x0150, &rd_data, 9 );
    log_info( &logger, "Data read: %s", rd_data );
    Delay_ms( 1000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
