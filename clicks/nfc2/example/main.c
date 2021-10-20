/*!
 * @file main.c
 * @brief NFC2 Click example
 *
 * # Description
 * This is an example which demonstrates the usage of NFC 2 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enables - I2C,
 * hw reset, reseteting and initialize core, disabling standby mode, 
 * starting test procedure, set configuration and start discovery, also write log.
 *
 * ## Application Task
 * NFC 2 Click board can be used for detection of RFiD tag
 * and displays it's value via USART terminal.
 * All data logs write on USB uart changes for every 1 sec.
 *
 * Additional Functions :
 *  -void display_packet ( control_packet_t *ctrl_pck ) - Display packet log data.
 *  -void display_nfc_data ( control_packet_t *ctrl_pck ) - Display packet log data.
 *  -void nfc2_read_nfc_data ( nfc2_t *ctx, control_packet_t *ctrl_pck ) - Read nfc data function.
 *  -void nfc2_test_antenna ( nfc2_t *ctx, control_packet_t *ctrl_pck ) - Testing Antenna function.
 * 
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "nfc2.h"

static nfc2_t nfc2;
static log_t logger;
uint8_t n_cnt;

control_packet_t ctrl_pck_data;

/**
 * @brief NFC 2 display packet function.
 * @details This function displays data values.
 */
void display_packet ( control_packet_t *ctrl_pck );

/**
 * @brief NFC 2 display nfc data function.
 * @details This function displays nfc data values.
 */
void display_nfc_data ( control_packet_t *ctrl_pck );

/**
 * @brief NFC 2 read nfc data function.
 * @details This function reads nfc data and displays data.
 */
void nfc2_read_nfc_data ( nfc2_t *ctx, control_packet_t *ctrl_pck );

/**
 * @brief NFC 2  test antena function.
 * @details This function tests antenna and displays data.
 */
void nfc2_test_antenna ( nfc2_t *ctx, control_packet_t *ctrl_pck );

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    nfc2_cfg_t nfc2_cfg;  /**< Click config object. */

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
    nfc2_cfg_setup( &nfc2_cfg );
    NFC2_MAP_MIKROBUS( nfc2_cfg, MIKROBUS_1 );
    err_t init_flag = nfc2_init( &nfc2, &nfc2_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_printf( &logger, "        HW Reset       \r\n" );
    nfc2_hw_reset( &nfc2 );
    Delay_ms( 100 );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, " Reset and Init. Core  \r\n" );
    nfc2_cmd_core_reset( &nfc2 );
    Delay_ms( 100 );

    nfc2_read_ctrl_packet_data( &nfc2, &ctrl_pck_data );
    Delay_ms( 100 );

    nfc2_cmd_core_init( &nfc2 );
    Delay_ms( 100 );

    nfc2_read_ctrl_packet_data( &nfc2, &ctrl_pck_data );
    Delay_ms( 100 );
    display_packet( &ctrl_pck_data );

    while ( nfc2_check_irq( &nfc2 ) == NFC2_IRQ_STATE_HIGH );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, " Disabling Standby Mode \r\n" );
    nfc2_cmd_disable_standby_mode( &nfc2 );
    Delay_ms( 100 );

    nfc2_read_ctrl_packet_data( &nfc2, &ctrl_pck_data );
    Delay_ms( 100 );
    display_packet( &ctrl_pck_data );

    nfc2_test_antenna( &nfc2, &ctrl_pck_data );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "Starting Test Procedure\r\n" );
    nfc2_cmd_test_procedure( &nfc2 );
    Delay_ms( 100 );

    nfc2_read_ctrl_packet_data( &nfc2, &ctrl_pck_data );
    Delay_ms( 100 );
    display_packet( &ctrl_pck_data );

    nfc2_hw_reset( &nfc2 );
    Delay_ms( 100 );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "       NFC Config.     \r\n" );
    nfc2_default_cfg ( &nfc2, &ctrl_pck_data );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "     Discovery Start   \r\n" );
    nfc2_cmd_start_discovery( &nfc2 );
    Delay_ms( 100 );

    nfc2_read_ctrl_packet_data( &nfc2, &ctrl_pck_data );
    Delay_ms( 100 );
    display_packet( &ctrl_pck_data );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "-------- START --------\r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms( 500 );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    while ( nfc2_check_irq( &nfc2 ) == NFC2_IRQ_STATE_HIGH ) {
        nfc2_read_nfc_data ( &nfc2, &ctrl_pck_data );
    }

    while ( nfc2_check_irq( &nfc2 ) == NFC2_IRQ_STATE_LOW );

    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms( 1000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

void display_packet ( control_packet_t *ctrl_pck ) {
    log_printf( &logger, "- - - - - - - - - - - -\r\n" );
    log_printf( &logger, " Message Type   = %d\r\n", ( uint16_t ) ctrl_pck->message_type );
    log_printf( &logger, " Pck Bound Flag = %d\r\n", ( uint16_t ) ctrl_pck->pck_bound_flag );
    log_printf( &logger, " Group Ident    = %d\r\n", ( uint16_t ) ctrl_pck->group_ident );
    log_printf( &logger, " Opcode Ident   = %d\r\n", ( uint16_t ) ctrl_pck->opcode_ident );
    log_printf( &logger, " Payload Length = %d\r\n", ( uint16_t ) ctrl_pck->payload_length );
    log_printf( &logger, "- - - - - - - - - - - -\r\n" );

    for ( n_cnt = 0; n_cnt < ctrl_pck_data.payload_length; n_cnt++ ) {
        log_printf( &logger, " Payload[ %.2d ]  = 0x%.2X\r\n", ( uint16_t ) n_cnt, ( uint16_t ) ( uint16_t ) ctrl_pck_data.payload[ n_cnt ]  );
    }

    log_printf( &logger, "- - - - - - - - - - - -\r\n" );
    memset( ctrl_pck_data.payload, 0x00, 255 );
}

void display_nfc_data ( control_packet_t *ctrl_pck ) {
    log_printf( &logger, "- - - - - - - - - - - -\r\n");
    log_printf( &logger, " Read Block:\r\n");

    for ( n_cnt = 1; n_cnt < ctrl_pck->payload_length - 2; n_cnt++ ) {
        log_printf( &logger, "\t 0x%.2X \r\n", ( uint16_t ) ctrl_pck->payload[ n_cnt ] );
    }
    log_printf( &logger, "\t 0x%.2X \r\n", ( uint16_t ) ctrl_pck->payload[ ctrl_pck->payload_length - 2 ] );

    log_printf( &logger, "- - - - - - - - - - - -\r\n" );
    memset( ctrl_pck->payload, 0x00, 255 );
}

void nfc2_read_nfc_data ( nfc2_t *ctx, control_packet_t *ctrl_pck ){
    nfc2_read_ctrl_packet_data( ctx, ctrl_pck );
    Delay_ms( 100 );

    nfc2_activate_rmt_mifare_card( ctx );
    Delay_ms( 100 );
    nfc2_read_ctrl_packet_data( ctx, ctrl_pck );
    Delay_ms( 10 );

    while ( nfc2_check_irq( ctx ) == NFC2_IRQ_STATE_LOW );

    nfc2_read_ctrl_packet_data( ctx, ctrl_pck );
    nfc2_cmd_authenticate_sector( ctx, 0x30 );
    Delay_ms( 100 );
    nfc2_read_ctrl_packet_data( ctx, ctrl_pck );
    Delay_ms( 10 );

    while ( nfc2_check_irq( ctx ) == NFC2_IRQ_STATE_LOW );

    nfc2_read_ctrl_packet_data( ctx, ctrl_pck );
    display_nfc_data( ctrl_pck );
    log_printf( &logger, "    Disconnect Card    \r\n" );
    nfc2_cmd_card_disconnected( ctx );
    Delay_ms( 10 );
    nfc2_read_ctrl_packet_data( ctx, ctrl_pck );
    Delay_ms( 10 );

    while ( nfc2_check_irq( ctx ) == NFC2_IRQ_STATE_LOW );

    nfc2_read_ctrl_packet_data( ctx, ctrl_pck );
    Delay_ms( 100 );
}

void nfc2_test_antenna ( nfc2_t *ctx, control_packet_t *ctrl_pck ) {
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "    Testing Antenna    " );
    nfc2_cmd_antenna_test( ctx, 0x01 );
    Delay_ms( 100 );

    nfc2_read_ctrl_packet_data( ctx, ctrl_pck );
    Delay_ms( 100 );

    nfc2_cmd_antenna_test( ctx, 0x07 );
    Delay_ms( 100 );
    nfc2_read_ctrl_packet_data( ctx, ctrl_pck );
    Delay_ms( 100 );

    nfc2_cmd_antenna_test( ctx, 0x0F );
    Delay_ms( 100 );
    nfc2_read_ctrl_packet_data( ctx, ctrl_pck );
    Delay_ms( 100 );
    display_packet( ctrl_pck );
}
// ------------------------------------------------------------------------ END
