/*!
 * @file main.c
 * @brief RTLS UWB Click Example.
 *
 * # Description
 * This example demonstrates the use of an RTLS UWB Click board by showing
 * the two-way ranging (TWR) communication between two or three Click boards.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and RTLS UWB Click driver, resets the device,
 * switches it to stop mode, and configures the selected application mode
 * as initiator or responder.
 *
 * ## Application Task
 * Reads and displays all incoming messages on the USB UART. One Click board
 * should be configured to APP_INITIATOR and the others to APP_RESPONDER_1 and APP_RESPONDER_2.
 * The initiator Click displays the address and distance of each responder nodes, while
 * the responder Click boards displays the address and distance of the initiator Click board.
 *
 * ## Additional Function
 * - static void rtlsuwb_clear_app_buf ( void )
 * - static void rtlsuwb_log_app_buf ( void )
 * - static err_t rtlsuwb_process ( rtlsuwb_t *ctx )
 * - static err_t rtlsuwb_read_response ( rtlsuwb_t *ctx, uint8_t *rsp, uint32_t max_rsp_time )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rtlsuwb.h"

#ifndef MIKROBUS_POSITION_RTLSUWB
    #define MIKROBUS_POSITION_RTLSUWB MIKROBUS_1
#endif

// Demo aplication selection macros
#define APP_INITIATOR               0
#define APP_RESPONDER_1             1
#define APP_RESPONDER_2             2
#define DEMO_APP                    APP_INITIATOR

/** INITF/RESPF parameter list and default value
 *  Option      Default Value           Range                   Description
 *  CHAN        9                       5 or 9                  Channel number
 *  PRFSET      BPRF4                   BPRF3                   Pulse Repetition Frequency parameter sets
 *                                      BPRF4                   See BPRF mode operating parameter sets
 *                                      BPRF5
 *                                      BPRF6
 *  PCODE       10                      9 to 12                 Preamble code index
 *  SLOT        2400                    2400 to 65535           Duration of the slot in RSTU. 1 ms = 1200 RSTU
 *  BLOCK       1000                    1 to 65535              Duration of the ranging block in ms
 *  ROUND       25                      1 to 255                Number of slots inside a ranging round
 *  RRU         DSTWR                   SSTWR                   Ranging round usage
 *                                      DSTWR                   SSTWR: Single-Sided Two-Way Ranging with Deferred mode
 *                                      SSTWRNDEF               DSTWR: Double-Sided Two-Way Ranging with Deferred mode
 *                                      DSTWRNDEF               SSTWRNDEF: Single-Sided Two-Way Ranging with Non-Deferred mode
 *                                                              DSTWRNDEF: Double-Sided Two-Way Ranging with Non-Deferred mode
 *  ID          42                      1 to 65535              Session ID
 *  VUPPER      01:02:03:04:05:06:07:08 00:00:00:00:00:00:00:00 vUpper64
 *                                      to                      Eight hexadecimal numbers, representing
 *                                      FF:FF:FF:FF:FF:FF:FF:FF static part of the STS in FiRa standard
 *  MULTI       Activated                                       Activate one-to-many mode (instead of unicast mode)
 *  HOP         Not activated                                   Activate round hopping
 *  ADDR        Initiator: 0            0 to 65535              Device own address
 *              Responder: 1 or 2
 *  PADDR       Initiator: 1,2          0 to 65535              Address(es) of peer devices
 *              Responder: 0                                    For Responder, it is the Initiator address (only one)
 *                                                              For Initiator, it is the Responder address or the
 *                                                              list of multiple Responder addresses
 */
#define INITIATOR_CONFIG            "-block=1000 -multi -addr=0 -paddr=[1,2]"
#define RESPONDER_1_CONFIG          "-block=1000 -multi -paddr=0 -addr=1"
#define RESPONDER_2_CONFIG          "-block=1000 -multi -paddr=0 -addr=2"

// Application buffer size
#define APP_BUFFER_SIZE             500
#define PROCESS_BUFFER_SIZE         200

static rtlsuwb_t rtlsuwb;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE + 1 ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief RTLS UWB clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @return None.
 * @note None.
 */
static void rtlsuwb_clear_app_buf ( void );

/**
 * @brief RTLS UWB log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @return None.
 * @note None.
 */
static void rtlsuwb_log_app_buf ( void );

/**
 * @brief RTLS UWB data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #rtlsuwb_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rtlsuwb_process ( rtlsuwb_t *ctx );

/**
 * @brief RTLS UWB read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #rtlsuwb_t object definition for detailed explanation.
 * @param[in] rsp : Expected response.
 * @param[in] max_rsp_time : Maximum response time in milliseconds.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rtlsuwb_read_response ( rtlsuwb_t *ctx, uint8_t *rsp, uint32_t max_rsp_time );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtlsuwb_cfg_t rtlsuwb_cfg;  /**< Click config object. */

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
    rtlsuwb_cfg_setup( &rtlsuwb_cfg );
    RTLSUWB_MAP_MIKROBUS( rtlsuwb_cfg, MIKROBUS_POSITION_RTLSUWB );
    if ( UART_ERROR == rtlsuwb_init( &rtlsuwb, &rtlsuwb_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    rtlsuwb_reset_device ( &rtlsuwb );
    
    log_printf( &logger, ">>> Switch to stop mode.\r\n" );
    rtlsuwb_cmd_run( &rtlsuwb, RTLSUWB_CMD_STOP );
    rtlsuwb_read_response( &rtlsuwb, RTLSUWB_RSP_OK, RTLSUWB_MAX_RSP_TIME_DEFAULT );
    Delay_ms ( 1000 );
    
#if ( DEMO_APP == APP_RESPONDER_1 )
    rtlsuwb_cmd_set ( &rtlsuwb, RTLSUWB_CMD_RESPF, RESPONDER_1_CONFIG );
    rtlsuwb_read_response( &rtlsuwb, RTLSUWB_RSP_OK, RTLSUWB_MAX_RSP_TIME_DEFAULT );
    log_printf( &logger, "Application Mode: Responder 1\r\n" );
#elif ( DEMO_APP == APP_RESPONDER_2 )
    rtlsuwb_cmd_set ( &rtlsuwb, RTLSUWB_CMD_RESPF, RESPONDER_2_CONFIG );
    rtlsuwb_read_response( &rtlsuwb, RTLSUWB_RSP_OK, RTLSUWB_MAX_RSP_TIME_DEFAULT );
    log_printf( &logger, "Application Mode: Responder 2\r\n" );
#else
    rtlsuwb_cmd_set ( &rtlsuwb, RTLSUWB_CMD_INITF, INITIATOR_CONFIG );
    rtlsuwb_read_response( &rtlsuwb, RTLSUWB_RSP_OK, RTLSUWB_MAX_RSP_TIME_DEFAULT );
    log_printf( &logger, "Application Mode: Initiator\r\n" );
#endif
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    rtlsuwb_read_response( &rtlsuwb, RTLSUWB_RSP_BLOCK_END, RTLSUWB_MAX_RSP_TIME_DEFAULT );
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

static void rtlsuwb_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void rtlsuwb_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t rtlsuwb_process ( rtlsuwb_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = rtlsuwb_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    if ( ( rx_size > 0 ) && ( rx_size <= APP_BUFFER_SIZE ) ) 
    {
        if ( ( app_buf_len + rx_size ) > APP_BUFFER_SIZE ) 
        {
            overflow_bytes = ( app_buf_len + rx_size ) - APP_BUFFER_SIZE;
            app_buf_len = APP_BUFFER_SIZE - rx_size;
            for ( int32_t buf_cnt = 0; buf_cnt < overflow_bytes; buf_cnt++ )
            {
                log_printf( &logger, "%c", app_buf[ buf_cnt ] );
            }
            memmove ( app_buf, &app_buf[ overflow_bytes ], app_buf_len );
            memset ( &app_buf[ app_buf_len ], 0, overflow_bytes );
        }
        for ( rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) 
        {
            if ( rx_buf[ rx_cnt ] ) 
            {
                app_buf[ app_buf_len++ ] = rx_buf[ rx_cnt ];
            }
        }
        return RTLSUWB_OK;
    }
    return RTLSUWB_ERROR;
}

static err_t rtlsuwb_read_response ( rtlsuwb_t *ctx, uint8_t *rsp, uint32_t max_rsp_time ) 
{
    uint32_t timeout_cnt = 0;
    rtlsuwb_clear_app_buf ( );
    rtlsuwb_process( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, RTLSUWB_RSP_ERROR ) ) )
    {
        rtlsuwb_process( ctx );
        if ( timeout_cnt++ > max_rsp_time )
        {
            rtlsuwb_log_app_buf( );
            rtlsuwb_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return RTLSUWB_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms ( 1 );
    rtlsuwb_process( ctx );
    rtlsuwb_log_app_buf( );
    if ( strstr( app_buf, rsp ) )
    {
        return RTLSUWB_OK;
    }
    return RTLSUWB_ERROR_CMD;
}

// ------------------------------------------------------------------------ END
