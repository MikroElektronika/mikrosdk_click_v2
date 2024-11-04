/*!
 * \file 
 * \brief LR4 Click example
 * 
 * # Description
 * This example reads and processes data from LR 4 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver, and resets the Click board to factory default configuration.
 * Then performs a group of commands for getting the FW version, the serial number, and the DevEUI.
 * After that executes the join activation by personalization command.
 * 
 * ## Application Task  
 * Checks the activation and session status and displays the results on the USB UART.
 * 
 * ## Additional Function
 * - response_handler - Parses and logs all the module responses on the USB UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "lr4.h"
#include "string.h"

// ------------------------------------------------------------------ VARIABLES

static lr4_t lr4;
static lr4_tx_msg_t lr4_tx_msg;
static log_t logger;

// -------------------------------------------------------- ADDITIONAL FUNCTIONS

static void response_handler( uint8_t *cmd, uint8_t *pl_size, uint8_t *pl_buffer )
{
    log_printf( &logger, "IND TYPE: 0x%.2X\r\n", ( uint16_t ) *cmd );
    
    log_printf( &logger, "PAYLOAD : " );
    
    for ( uint8_t cnt = 0; cnt < *pl_size; cnt++ )
    {
        log_printf( &logger, "0x%.2X ", ( uint16_t ) pl_buffer[ cnt ] );
    }
    log_printf( &logger, "\r\n" );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    lr4_cfg_t cfg;

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

    lr4_cfg_setup( &cfg );
    LR4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lr4_init( &lr4, &cfg );

    Delay_ms ( 100 );
    lr4_set_ind_handler( &lr4, response_handler );
    log_printf( &logger, "Hard reset!\r\n" );
    lr4_hard_reset( &lr4 );
    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, "Factory reset!\r\n" );
    lr4_factory_reset( &lr4 );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
    uint32_t tmp_data = 0;
    log_printf( &logger, "Get FW version!\r\n" );
    lr4_get_fw_version( &lr4, &tmp_data );
    log_printf( &logger, "FW vesion is: 0x%.8LX\r\n", tmp_data );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
    log_printf( &logger, "Get Serial Number!\r\n" );
    lr4_get_serial_no( &lr4, &tmp_data );
    log_printf( &logger, "Serial Number is: 0x%.8LX\r\n", tmp_data );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
    uint8_t tmp_buf[ 8 ] = { 0 };
    log_printf( &logger, "Get Dev EUI!\r\n" );
    lr4_get_dev_eui( &lr4, tmp_buf );
    log_printf( &logger, "Dev EUI is: 0x%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X\r\n", ( uint16_t ) tmp_buf[ 7 ],
                                                                               ( uint16_t ) tmp_buf[ 6 ],
                                                                               ( uint16_t ) tmp_buf[ 5 ],
                                                                               ( uint16_t ) tmp_buf[ 4 ],
                                                                               ( uint16_t ) tmp_buf[ 3 ],
                                                                               ( uint16_t ) tmp_buf[ 2 ],
                                                                               ( uint16_t ) tmp_buf[ 1 ],
                                                                               ( uint16_t ) tmp_buf[ 0 ] );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
    log_printf( &logger, "Join Network!\r\n" );
    lr4_join_network( &lr4, LR4_JOIN_ACTIVATION_BY_PERSONALIZATION_MODE );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    log_printf( &logger, "Get Activation Status!\r\n" );
    uint8_t status = lr4_get_status( &lr4, LR4_GET_ACTIVATION_MODE );
    log_printf( &logger, "Status: " );
    switch ( status )
    {
        case LR4_STATUS_NOT_ACTIVATED :
        {
            log_printf( &logger, "Not activated.\r\n" );
            break;
        }
        case LR4_STATUS_JOINING :
        {
            log_printf( &logger, "Joining...\r\n" );
            break;
        }
        case LR4_STATUS_JOINED :
        {
            log_printf( &logger, "Joined.\r\n" );
            break;
        }
        case LR4_STATUS_MAC_ERROR :
        {
            log_printf( &logger, "MAC ERROR.\r\n" );
            break;
        }
        default :
        {
            break;
        }
    }
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
    log_printf( &logger, "Get Session Status!\r\n" );
    status = lr4_get_status( &lr4, LR4_GET_SESSION_STATUS_MODE );
    log_printf( &logger, "Status: " );
    switch ( status )
    {
        case LR4_STATUS_IDLE :
        {
            log_printf( &logger, "Idle.\r\n" );
            break;
        }
        case LR4_STATUS_BUSY :
        {
            log_printf( &logger, "Busy (LR session running).\r\n" );
            break;
        }
        case LR4_STATUS_DEV_NOT_ACTIVATED :
        {
            log_printf( &logger, "Device not activated.\r\n" );
            break;
        }
        case LR4_STATUS_DELAYED :
        {
            log_printf( &logger, "Delayed (LR session paused due to Duty-cycle).\r\n" );
            break;
        }
        default :
        {
            break;
        }
    }
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
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
