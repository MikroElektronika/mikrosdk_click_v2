/*!
 * \file 
 * \brief Presence Click example
 * 
 * # Description
 * This application enables usage of sensor for motion and presence sensing and measuring of object's and ambient temperature.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init, start eeprom process and configuration chip for measurement.
 * 
 * ## Application Task  
 * Check whether a new event (Motion, Presence or Temp threshold exceeded) is detected.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "presence.h"

// ------------------------------------------------------------------ VARIABLES

static presence_t presence;
static log_t logger;

static uint16_t log_counter = 0;
#define LOG_INT               1000

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    presence_cfg_t cfg;

    uint8_t tmp;
    uint8_t w_temp;

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

    presence_cfg_setup( &cfg );
    PRESENCE_MAP_MIKROBUS( cfg, MIKROBUS_4 );
    presence_init( &presence, &cfg );

    // General call address

    presence_general_call_addr( &presence );
    Delay_1sec( );

    // EEPROM
    
    tmp = presence_eeprom_process( &presence );
    if ( tmp == 0 )
    {
        log_printf( &logger, "----- EEPROM READ OK! ------\r\n" );
    }
    else
    {
        log_printf( &logger, "---- EEPROM READ ERROR! ----\r\n" );
        log_printf( &logger, "----------------------------\r\n" );

        while ( 1 );
    }
    Delay_ms( 2000 );
    w_temp = PRESENCE_INT_MASK1_TP_OT | PRESENCE_INT_MASK1_MOTION | PRESENCE_INT_MASK1_PRESENCE;
    presence_generic_write( &presence, PRESENCE_REG_INTERRUPT_MASK_1, &w_temp, 1 );
    w_temp = PRESENCE_INT_MASK2_TPOT_DIR | PRESENCE_INT_MASK2_SRC_LP1_LP2 | PRESENCE_INT_MASK2_CYCLE_TIME_30ms;
    presence_generic_write( &presence, PRESENCE_REG_INTERRUPT_MASK_2, &w_temp, 1 );
    
    w_temp = PRESENCE_LOW_PASS_TIME_1s;
    presence_generic_write( &presence, PRESENCE_REG_LOW_PASS_TIME_1, &w_temp, 1 );
    
    w_temp = 0x22;
    presence_generic_write( &presence, PRESENCE_REG_TP_PRESENCE_THR, &w_temp, 1 );
    w_temp = 0x0A;
    presence_generic_write( &presence, PRESENCE_REG_TP_MOTION_THR, &w_temp, 1 );
    presence_generic_write( &presence, PRESENCE_REG_TP_OT_THR_1, &w_temp, 1 );
    w_temp = 0x00;
    presence_generic_write( &presence, PRESENCE_REG_TP_OT_THR_2, &w_temp, 1 );
    
    log_printf( &logger, "-------- INIT DONE ---------\r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms( 3000 );
}

void application_task ( void )
{
    //  Task implementation.

    uint8_t int_status;
    volatile float tamb;
    volatile float tobj;

    presence_generic_read( &presence, PRESENCE_REG_INTERRUPT_STATUS, &int_status, 1 );
    
    if ( log_counter++ > LOG_INT )
    {
        tamb = presence_ambient_temperature( &presence );
        log_printf( &logger, "---- Ambient Temperature: %.2f\r\n", tamb );

        tobj = presence_object_temperature( &presence );
        log_printf( &logger, "---- Object Temperature: %.2f\r\n", tobj );
    }
        
    if ( ( int_status & 0x08 ) != 0 )
    {
        log_printf( &logger, "--- Presence detected! ---\r\n" );
    }
    else if ( ( int_status & 0x04 ) != 0 )
    {
        log_printf( &logger, "--- Motion detected! ---\r\n" );
    }
    else if ( ( int_status & 0x10 ) != 0 )
    {
        log_printf( &logger, "--- Temp threshold exceeded! ---\r\n" );
    }


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
