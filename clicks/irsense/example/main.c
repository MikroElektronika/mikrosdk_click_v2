/*!
 * \file 
 * \brief IrSense Click example
 * 
 * # Description
 * This application return the temperature of object.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - I2C, enable sensor,
 * set soft reset, set Continuous Mode 0,  also write log.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of IR Sense Click board.
 * Detects the temperature of objects and detects the motion in observable area of the AK9750 sensor.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on usb uart changes for every 1 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "irsense.h"

// ------------------------------------------------------------------ VARIABLES

static irsense_t irsense;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    irsense_cfg_t cfg;
    irsense_eint_t eint;
    
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

    irsense_cfg_setup( &cfg );
    IRSENSE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irsense_init( &irsense, &cfg );

    eint.ir13h = IRSENSE_EINTEN_IR13_HIGH_INT_DISABLE;
    eint.ir13l = IRSENSE_EINTEN_IR13_HIGH_INT_DISABLE;
    eint.ir24h = IRSENSE_EINTEN_IR13_HIGH_INT_DISABLE;
    eint.ir24l = IRSENSE_EINTEN_IR13_HIGH_INT_DISABLE;
    eint.dr = IRSENSE_EINTEN_IR13_HIGH_INT_DISABLE;
    
    log_printf( &logger, "     I2C Driver Init       \r\n"  );
    Delay_ms( 100 );
    log_printf( &logger, "---------------------------\r\n"  );

    irsense_power_on( &irsense );
    log_printf( &logger, "         Power On          \r\n"  );
    Delay_ms( 1000 );
    log_printf( &logger, "---------------------------\r\n"  );

    irsense_soft_reset( &irsense );
    log_printf( &logger, "        Soft Reset         \r\n"  );
    Delay_ms( 1000 );
    log_printf( &logger, "---------------------------\r\n"  );

    irsense_set_mode( &irsense, IRSENSE_ECNTL1_MODE_CONTINUOUS_0 );
    irsense_set_cutoff_frequency( &irsense, IRSENSE_ECNTL1_CUTOFF_FREQUENCY_0_6_Hz );
    log_printf( &logger, "  Set Continuous Mode 0    \r\n"  );
    log_printf( &logger, "Set cutoff frequency 0.6 Hz\r\n"  );
    Delay_ms( 100 );
    log_printf( &logger, "---------------------------\r\n"  );

    irsense_set_interrupts_reg( &irsense, &eint );

    log_printf( &logger, " Interrupt Source Setting  \r\n"  );
    log_printf( &logger, "Enable Data Ready Interrupt\r\n"  );
    Delay_ms( 100 );
    log_printf( &logger, "---------------------------\r\n"  );
    log_printf( &logger, "      IR Sense  Click      \r\n"  );
    log_printf( &logger, "---------------------------\r\n"  );
    log_printf( &logger, "      Observable Area      \r\n"  );

}

void application_task ( void )
{
   irsense_ir_data_t ir_data;
   float temperature;

   if ( irsense_check_available( &irsense ) )
    {
        irsense_get_ir_sense( &irsense, &ir_data );

        log_printf( &logger, "- - - - - - - - -\r\n" );
        log_printf( &logger, " Bottom : %d \r\n", ir_data.bottom_area );

        log_printf( &logger, " Left   : %d \r\n", ir_data.left_area );

        log_printf( &logger, " Top    : %d \r\n", ir_data.top_area );

        log_printf( &logger, " Right  : %d \r\n", ir_data.right_area );
        log_printf( &logger, "- - - - - - - - -\r\n" );

        temperature = irsense_get_temperature( &irsense );
        log_printf( &logger, " Temperature: %f \r\n", temperature );
        log_printf( &logger, "---------------------------\r\n" );

        irsense_refresh( &irsense );
        Delay_ms( 1000 );
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
