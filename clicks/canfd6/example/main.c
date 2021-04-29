/*!
 * @file main.c
 * @brief CANFD6 Click example
 *
 * # Description
 * This application presents the capabilities of the
 * CAN FD 6 click board. The board can be used both
 * as a receiver and a transmitter. Use def directive
 * to define the receive or transmit app.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The app starts by initializing the UART LOG and
 * SPI drivers. The default cfg function performs the
 * mandatory settings of the device. The user's default
 * configuration can be modified ( for more information
 * about device configuration, check the datasheet ).
 * Additionally, the app writes two messages to the FIFO
 * buffer and sends them if the transmit buffer content
 * event is triggered.
 *
 * ## Application Task
 * Depending on the defined app option, the application
 * task performs the following procedure. If the transmitter
 * is preferred, the application task triggers the transmit
 * buffer contents event of the first message and, later on,
 * the second message. On the other hand, the receiver waits
 * for the CAN FD interrupt, where the payload is read along
 * with the header ID.
 *
 * @author Stefan Nikolic
 *
 */

#include "board.h"
#include "log.h"
#include "canfd6.h"

// #define APP_TRANSMITTER
#define APP_RECEIVER

#define CANFD6_FIRST_MSG                        0
#define CANFD6_SECOND_MSG                       1

static canfd6_t canfd6;
static log_t logger;

static canfd6_mcan_tx_header_t canfd6_header = { 0 };
static uint8_t data_send_buf[ 64 ] = { 'M', 'i', 'k', 'r', 'o', 'E' };

void application_init ( void ) {
    log_cfg_t log_cfg;        /**< Logger config object. */
    canfd6_cfg_t canfd6_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    canfd6_cfg_setup( &canfd6_cfg );
    CANFD6_MAP_MIKROBUS( canfd6_cfg, MIKROBUS_1 );
    err_t init_flag = canfd6_init( &canfd6, &canfd6_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    canfd6_default_cfg( &canfd6 );
    Delay_ms( 100 );
    
    canfd6_header.DLC = CANFD6_MCAN_DLC_6B;
    canfd6_header.ID = 0x123;
    canfd6_header.FDF = 1;
    canfd6_header.BRS = 1;
    canfd6_header.EFC = 0;
    canfd6_header.MM  = 0;
    canfd6_header.RTR = 0;
    canfd6_header.XTD = 0;
    canfd6_header.ESI = 0;
    canfd6_mcan_write_txbuffer( &canfd6, CANFD6_FIRST_MSG, &canfd6_header, data_send_buf );

    data_send_buf[ 0 ] = '2';
    data_send_buf[ 1 ] = '0';
    data_send_buf[ 2 ] = '2';
    data_send_buf[ 3 ] = '1';
    canfd6_header.DLC = CANFD6_MCAN_DLC_4B;
    canfd6_header.ID = 0x456;
    canfd6_header.FDF = 1;
    canfd6_header.BRS = 1;
    canfd6_header.EFC = 0;
    canfd6_header.MM  = 0;
    canfd6_header.RTR = 0;
    canfd6_header.XTD = 0;
    canfd6_header.ESI = 0;
    canfd6_mcan_write_txbuffer( &canfd6, CANFD6_SECOND_MSG, &canfd6_header, data_send_buf );
    
    Delay_ms( 100 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    #ifdef APP_TRANSMITTER
    canfd6_mcan_transmit_buffer_contents( &canfd6, CANFD6_FIRST_MSG );
    Delay_ms( 1000 );
    canfd6_mcan_transmit_buffer_contents( &canfd6, CANFD6_SECOND_MSG );
    Delay_ms( 3000 );
    #endif
    
    #ifdef APP_RECEIVER
    uint8_t cnt = 0;
    if ( !canfd6_get_int_pin( &canfd6 ) ) {
        canfd6_device_interrupts_t canfd6_dev_ir = { 0 };
        canfd6_mcan_interrupts_t canfd6_mcan_ir = { 0 };
        canfd6_device_read_interrupts( &canfd6, &canfd6_dev_ir );
        canfd6_mcan_read_interrupts( &canfd6, &canfd6_mcan_ir );

        if ( canfd6_dev_ir.SPIERR ) {
            canfd6_device_clear_spierr( &canfd6 );
        }

        if ( canfd6_mcan_ir.RF0N ) {
            canfd6_mcan_rx_header_t canfd6_msg_header = { 0 };
            uint8_t num_bytes = 0;
            uint8_t data_payload[ 64 ] = { 0 };

            canfd6_mcan_clear_interrupts( &canfd6, &canfd6_mcan_ir );

            num_bytes = canfd6_mcan_read_nextfifo( &canfd6, CANFD6_RXFIFO0, &canfd6_msg_header, data_payload );
            
            log_printf( &logger, "Message received ID[ 0x%X ]: ", canfd6_msg_header.ID );

            while ( cnt < 64 ) {
                if ( data_payload[ cnt ] ) {
                    log_printf( &logger, "%c", data_payload[ cnt ] );
                    cnt++;
                } else {
                    log_printf( &logger, "\r\n" );
                    cnt = 64;
                }
            }
        }
    }
    #endif
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
