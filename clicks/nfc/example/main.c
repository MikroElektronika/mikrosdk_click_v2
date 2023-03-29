/*!
 * @file main.c
 * @brief NFC Click example
 *
 * # Description
 * This is an example which demonstrates the usage of NFC Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes driver and logger, then performs hardware reset, puts the device in operating mode by 
 * disabling standby mode, performs test procedure, and configures the device to start discovery.
 *
 * ## Application Task
 * NFC Click board can be used for detection of RFiD tag
 * and displays it's value via USART terminal.
 * All data logs write on USB uart changes for every 1 sec.
 *
 * Additional Functions :
 *  -void display_packet ( control_packet_t *ctrl_pck ) - Display packet log data.
 *  -void display_nfc_data ( control_packet_t *ctrl_pck ) - Display packet log data.
 *  -void nfc_read_nfc_data ( nfc_t *ctx, control_packet_t *ctrl_pck ) - Read nfc data function.
 *  -void nfc_test_antenna ( nfc_t *ctx, control_packet_t *ctrl_pck ) - Testing Antenna function.
 * 
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "nfc.h"

static nfc_t nfc;
static log_t logger;
uint8_t n_cnt;

control_packet_t ctrl_pck_data;

/**
 * @brief NFC display packet function.
 * @details This function displays data values.
 */
void display_packet ( control_packet_t *ctrl_pck );

/**
 * @brief NFC display tag info.
 * @details This function displays tag info data.
 */
void nfc_print_info (  control_packet_t *ctrl_pck );

/**
 * @brief NFC display nfc data function.
 * @details This function displays nfc data values.
 */
void display_nfc_data ( control_packet_t *ctrl_pck );

/**
 * @brief NFC read nfc data function.
 * @details This function reads nfc data and displays data.
 */
void nfc_read_nfc_data ( nfc_t *ctx, control_packet_t *ctrl_pck );

/**
 * @brief NFC test antena function.
 * @details This function tests antenna and displays data.
 */
void nfc_test_antenna ( nfc_t *ctx, control_packet_t *ctrl_pck );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nfc_cfg_t nfc_cfg;  /**< Click config object. */

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
    nfc_cfg_setup( &nfc_cfg );
    NFC_MAP_MIKROBUS( nfc_cfg, MIKROBUS_1 );
    err_t init_flag = nfc_init( &nfc, &nfc_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_printf( &logger, "        HW Reset       \r\n" );
    nfc_hw_reset( &nfc );
    Delay_ms( 100 );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, " Reset and Init. Core  \r\n" );
    nfc_cmd_core_reset( &nfc );
    Delay_ms( 100 );

    nfc_read_ctrl_packet_data( &nfc, &ctrl_pck_data );
    Delay_ms( 100 );

    nfc_cmd_core_init( &nfc );
    Delay_ms( 100 );

    nfc_read_ctrl_packet_data( &nfc, &ctrl_pck_data );
    Delay_ms( 100 );
    display_packet( &ctrl_pck_data );

    while ( nfc_check_irq( &nfc ) == NFC_IRQ_STATE_HIGH );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, " Disabling Standby Mode \r\n" );
    nfc_cmd_disable_standby_mode( &nfc );
    Delay_ms( 100 );

    nfc_read_ctrl_packet_data( &nfc, &ctrl_pck_data );
    Delay_ms( 100 );
    display_packet( &ctrl_pck_data );

    nfc_test_antenna( &nfc, &ctrl_pck_data );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "Starting Test Procedure\r\n" );
    nfc_cmd_test_procedure( &nfc );
    Delay_ms( 100 );

    nfc_read_ctrl_packet_data( &nfc, &ctrl_pck_data );
    Delay_ms( 100 );
    display_packet( &ctrl_pck_data );

    nfc_hw_reset( &nfc );
    Delay_ms( 100 );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "       NFC Config.     \r\n" );
    nfc_default_cfg ( &nfc, &ctrl_pck_data );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "     Discovery Start   \r\n" );
    nfc_cmd_start_discovery( &nfc );
    Delay_ms( 100 );

    nfc_read_ctrl_packet_data( &nfc, &ctrl_pck_data );
    Delay_ms( 100 );
    display_packet( &ctrl_pck_data );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "-------- START --------\r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms( 500 );

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    while ( nfc_check_irq( &nfc ) == NFC_IRQ_STATE_HIGH ) 
    {
        nfc_read_nfc_data ( &nfc, &ctrl_pck_data );
    }

    while ( nfc_check_irq( &nfc ) == NFC_IRQ_STATE_LOW );

    log_printf( &logger, "-----------------------\r\n" );
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

void display_packet ( control_packet_t *ctrl_pck ) 
{
    log_printf( &logger, "- - - - - - - - - - - -\r\n" );
    log_printf( &logger, " Message Type   = %d\r\n", ( uint16_t ) ctrl_pck->message_type );
    log_printf( &logger, " Pck Bound Flag = %d\r\n", ( uint16_t ) ctrl_pck->pck_bound_flag );
    log_printf( &logger, " Group Ident    = %d\r\n", ( uint16_t ) ctrl_pck->group_ident );
    log_printf( &logger, " Opcode Ident   = %d\r\n", ( uint16_t ) ctrl_pck->opcode_ident );
    log_printf( &logger, " Payload Length = %d\r\n", ( uint16_t ) ctrl_pck->payload_length );
    log_printf( &logger, "- - - - - - - - - - - -\r\n" );

    for ( n_cnt = 0; n_cnt < ctrl_pck_data.payload_length; n_cnt++ ) 
    {
        log_printf( &logger, " Payload[ %.2d ]  = 0x%.2X\r\n", ( uint16_t ) n_cnt, ( uint16_t ) ctrl_pck_data.payload[ n_cnt ]  );
    }

    log_printf( &logger, "- - - - - - - - - - - -\r\n" );
    memset( ctrl_pck_data.payload, 0x00, 255 );
}

void nfc_print_info ( control_packet_t *ctrl_pck )
{
    log_printf( &logger, "    NFC Tag info    \r\n" );
    log_printf( &logger, "- - - - - - - - - - - -\r\n" );
    log_printf( &logger, " Serial number = %.2X:%.2X:%.2X:%.2X\r\n", 
                ( uint16_t ) ctrl_pck_data.payload[ 10 ], ( uint16_t ) ctrl_pck_data.payload[ 11 ], 
                ( uint16_t ) ctrl_pck_data.payload[ 12 ], ( uint16_t ) ctrl_pck_data.payload[ 13 ] );
    log_printf( &logger, " ATQA = 0x%.2X%.2X\r\n",  ( uint16_t ) ctrl_pck_data.payload[ 8 ], 
                ( uint16_t ) ctrl_pck_data.payload[ 9 ]  );
    log_printf( &logger, " SAK = 0x%.2X\r\n",  ( uint16_t ) ctrl_pck_data.payload[ 15 ]  );
    
}

void display_nfc_data ( control_packet_t *ctrl_pck ) 
{
    log_printf( &logger, "- - - - - - - - - - - -\r\n");
    log_printf( &logger, " Read Block:\r\n");

    for ( n_cnt = 0; n_cnt < ctrl_pck->payload_length; n_cnt++ )
    {
        log_printf( &logger, "\t 0x%.2X \r\n", ( uint16_t ) ctrl_pck->payload[ n_cnt ] );
    }
    log_printf( &logger, "\t 0x%.2X \r\n", ( uint16_t ) ctrl_pck->payload[ ctrl_pck->payload_length - 2 ] );

    log_printf( &logger, "- - - - - - - - - - - -\r\n" );
    memset( ctrl_pck->payload, 0x00, 255 );
}

void nfc_read_nfc_data ( nfc_t *ctx, control_packet_t *ctrl_pck )
{
    nfc_read_ctrl_packet_data( ctx, ctrl_pck );
    nfc_print_info( ctrl_pck );
    Delay_ms( 100 );

    nfc_activate_rmt_mifare_card( ctx );
    Delay_ms( 100 );
    nfc_read_ctrl_packet_data( ctx, ctrl_pck );
    Delay_ms( 10 );

    while ( nfc_check_irq( ctx ) == NFC_IRQ_STATE_LOW );

    nfc_read_ctrl_packet_data( ctx, ctrl_pck );
    nfc_cmd_authenticate_sector( ctx, 0x30 );
    Delay_ms( 100 );
    nfc_read_ctrl_packet_data( ctx, ctrl_pck );
    Delay_ms( 10 );

    while ( nfc_check_irq( ctx ) == NFC_IRQ_STATE_LOW );

    nfc_read_ctrl_packet_data( ctx, ctrl_pck );
    display_nfc_data( ctrl_pck );
    log_printf( &logger, "    Disconnect Card    \r\n" );
    nfc_cmd_card_disconnected( ctx );
    Delay_ms( 10 );
    nfc_read_ctrl_packet_data( ctx, ctrl_pck );
    Delay_ms( 10 );

    while ( nfc_check_irq( ctx ) == NFC_IRQ_STATE_LOW );

    nfc_read_ctrl_packet_data( ctx, ctrl_pck );
    Delay_ms( 100 );
}

void nfc_test_antenna ( nfc_t *ctx, control_packet_t *ctrl_pck )
{
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "    Testing Antenna    " );
    nfc_cmd_antenna_test( ctx, 0x01 );
    Delay_ms( 100 );

    nfc_read_ctrl_packet_data( ctx, ctrl_pck );
    Delay_ms( 100 );

    nfc_cmd_antenna_test( ctx, 0x07 );
    Delay_ms( 100 );
    nfc_read_ctrl_packet_data( ctx, ctrl_pck );
    Delay_ms( 100 );

    nfc_cmd_antenna_test( ctx, 0x0F );
    Delay_ms( 100 );
    nfc_read_ctrl_packet_data( ctx, ctrl_pck );
    Delay_ms( 100 );
    display_packet( ctrl_pck );
}
// ------------------------------------------------------------------------ END
