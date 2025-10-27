/*!
 * \file 
 * \brief Proximity10 Click example
 * 
 * # Description
 * This application enables proximity sensor to detect objects from distance up to 20cm.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C serial interface and performs a device wake up, reset and 
 * all necessary configurations.
 * The device will wake up and performs measurements every 10 milliseconds.
 * 
 * ## Application Task  
 * Reads the proximity PS1 data value and sends result to the uart terminal.
 * If measured proximity value is greater than selected proximity threshold value, the interrupt will be generated and
 * the message will be showed on the uart terminal.
 * 
 * *note:* 
 * Additional Functions :
 * - check_response - Sends an error code message to the uart terminal if error code is detected in the response.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "proximity10.h"

// ------------------------------------------------------------------ VARIABLES

static proximity10_t proximity10;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void check_response ( uint8_t cmd_resp )
{
    switch ( cmd_resp )
    {
        case PROXIMITY10_INVALID_CMD_ENCOUNT :
        {
            log_printf( &logger, "** Invalid Command Encountered during command processing **\r\n" );
            break;
        }
        case PROXIMITY10_ADC_OVRFLOW_ENCOUNT_PS1 :
        {
            log_printf( &logger, "** ADC Overflow Encountered during PS1 measurement **\r\n" );
            break;
        }
        case PROXIMITY10_ADC_OVRFLOW_ENCOUNT_PS2 :
        {
            log_printf( &logger, "** ADC Overflow Encountered during PS2 measurement **\r\n" );
            break;
        }
        case PROXIMITY10_ADC_OVRFLOW_ENCOUNT_PS3 :
        {
            log_printf( &logger, "** ADC Overflow Encountered during PS3 measurement **\r\n" );
            break;
        }
        case PROXIMITY10_ADC_OVRFLOW_ENCOUNT_ALS_VIS :
        {
            log_printf( &logger, "** ADC Overflow Encountered during ALS-VIS measurement **\r\n" );
            break;
        }
        case PROXIMITY10_ADC_OVRFLOW_ENCOUNT_ALS_IR :
        {
            log_printf( &logger, "** ADC Overflow Encountered during ALS-IR measurement **\r\n" );
            break;
        }
        case PROXIMITY10_ADC_OVRFLOW_ENCOUNT_AUX :
        {
            log_printf( &logger, "** ADC Overflow Encountered during AUX measurement **\r\n" );
            break;
        }
        default :
        {
            break;
        }
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity10_cfg_t cfg;

    uint8_t w_temp;
    uint8_t cmd_resp;

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

    proximity10_cfg_setup( &cfg );
    PROXIMITY10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity10_init( &proximity10, &cfg );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    w_temp = PROXIMITY10_HW_KEY;
    proximity10_generic_write( &proximity10, PROXIMITY10_HW_KEY_REG, &w_temp, 1 );
    
    cmd_resp = proximity10_send_command( &proximity10, PROXIMITY10_NOP_CMD );
    check_response( cmd_resp );
    cmd_resp = proximity10_send_command( &proximity10, PROXIMITY10_RESET_CMD );
    check_response( cmd_resp );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    cmd_resp = proximity10_param_set( &proximity10, PROXIMITY10_CHLIST_PARAM, PROXIMITY10_EN_AUX | PROXIMITY10_EN_ALS_IR | PROXIMITY10_EN_ALS_VIS | PROXIMITY10_EN_PS1 );
    check_response( cmd_resp );
    cmd_resp = proximity10_param_set( &proximity10, PROXIMITY10_PSLED12_SEL_PARAM, PROXIMITY10_LED1_DRIVE_EN );
    check_response( cmd_resp );
    cmd_resp = proximity10_param_set( &proximity10, PROXIMITY10_PS_ADC_MISC_PARAM, PROXIMITY10_NORMAL_SIGNAL_RANGE | PROXIMITY10_NORMAL_PROX_MEAS_MODE );
    check_response( cmd_resp );
    cmd_resp = proximity10_param_set( &proximity10, PROXIMITY10_PS_ADC_GAIN_PARAM, PROXIMITY10_ADC_CLOCK_DIV_4 );
    check_response( cmd_resp );

    proximity10_default_cfg ( &proximity10 );

    cmd_resp = proximity10_send_command( &proximity10, PROXIMITY10_PS_AUTO_CMD );
    check_response( cmd_resp );
    
    log_printf( &logger, "** Proximity 10 is initialized **\r\n" );
    log_printf( &logger, "**************************************\r\n" );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    //  Task implementation.

    uint32_t proximity;
    uint8_t temp_read[ 2 ];
    uint8_t int_status;

    proximity10_generic_read( &proximity10, PROXIMITY10_PS1_DATA_REG, &temp_read, 2 );
    proximity = temp_read[ 1 ];
    proximity <<= 8;
    proximity |= temp_read[ 0 ];
    
    log_printf( &logger, "** Proximity PS1 : %u \r\n", proximity );
    
    int_status = proximity10_check_int_status( &proximity10, PROXIMITY10_PS1_INT_FLAG, PROXIMITY10_INT_CLEAR_DIS );
    
    if ( int_status == PROXIMITY10_PS1_INT_FLAG )
    {
        log_printf( &logger, "** Object is detected **\r\n" );
        Delay_ms ( 1000 );
    }
    else
    {
        Delay_ms ( 1000 );
    }
    log_printf( &logger, "**************************************\r\n" );
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
