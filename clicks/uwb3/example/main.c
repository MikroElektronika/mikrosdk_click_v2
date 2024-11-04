/*!
 * @file main.c
 * @brief UWB 3 Click Example.
 *
 * # Description
 * This example demonstrates the use of an UWB 3 Click board by showing
 * the communication between the two Click boards.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and configures the Click board for the selected
 * application mode.
 *
 * ## Application Task
 * Reads and processes all incoming ranging block messages and displays them
 * on the USB UART. One Click board should be configured to initiator mode and
 * the others to responder 1 or 2. The initiator Click displays the address
 * and distance of each responder nodes, while the responder Click boards displays
 * the address and distance of the initiator Click board.
 *
 * ## Additional Function
 * - static void uwb3_clear_app_buf ( void )
 * - static void uwb3_log_app_buf ( void )
 * - static err_t uwb3_process ( uwb3_t *ctx )
 * - static err_t uwb3_display_response ( uwb3_t *ctx )
 * - static err_t uwb3_parse_ranging_block ( void )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "uwb3.h"

// Demo aplication selection macros
#define APP_INITIATOR               0
#define APP_RESPONDER_1             1
#define APP_RESPONDER_2             2
#define DEMO_APP                    APP_INITIATOR

/** INITF/RESPF parameter list and default value
 * Order    Config Param            Default value           Description
 * #1       RFRAME BPRF             4                       RFRAME BRFF set as per FiRa spec: 
 *                                                          4 - SP3 SFD4Z, 6 - SP3 SFD4A
 * #2       RSTU slot duration      2400                    Duration of the slot in RSTU time units.
 *                                                          1ms = 1200 RSTU
 * #3       Block duration ms       200                     Duration of the FiRa ranging block in ms
 * #4       Round duration slots    25                      Duration of the FiRa ranging round inside
 *                                                          the block
 * #5       Ranging Round usage     2                       0 - Not used, 1 - SS-TWR, 2 - DS-TWR
 * #6       Session ID              42                      Session ID
 * #7       vupper64                01:02:03:04:05:06:07:08 Eight hexadecimal numbers, represented
 *                                                          static part of the STS in FiRa standard, 
 *                                                          Hex values separated by ":"
 * #8       Multi node mode         0                       0 for unicast, 1 for multi-node configuration
 * #9       Round hopping           0                       0 for no round hopping, 1 for round hopping
 * #10      Initiator address       0                       Address of FiRa Initiator, Decimal value 0-65535
 * #11      Responder address       1                       Address of responder or set of addresses for
 *                                                          multiple responders, Decimal value 0-65535
 */
#define INITIATOR_CONFIG            "4 2400 200 25 2 42 01:02:03:04:05:06:07:08 1 0 0 1 2"
#define RESPONDER_1_CONFIG          "4 2400 200 25 2 42 01:02:03:04:05:06:07:08 1 0 0 1"
#define RESPONDER_2_CONFIG          "4 2400 200 25 2 42 01:02:03:04:05:06:07:08 1 0 0 2"

// Application buffer size
#define APP_BUFFER_SIZE             800
#define PROCESS_BUFFER_SIZE         200

static uwb3_t uwb3;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief UWB 3 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void uwb3_clear_app_buf ( void );

/**
 * @brief UWB 3 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void uwb3_log_app_buf ( void );

/**
 * @brief UWB 3 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #uwb3_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t uwb3_process ( uwb3_t *ctx );

/**
 * @brief UWB 3 display response function.
 * @details This function reads and displays the response to previously sent command.
 * @param[in] ctx : Click context object.
 * See #uwb3_t object definition for detailed explanation.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 */
static err_t uwb3_display_response ( uwb3_t *ctx );

/**
 * @brief UWB 3 parse ranging block function.
 * @details This function parses the ranging block results from application buffer and
 * displays it to the USB UART.
 * @return @li @c  0 - Ranging block data parsed successfully.
 *         @li @c -1 - No valid ranging block data in application buffer.
 * See #err_t definition for detailed explanation.
 */
static err_t uwb3_parse_ranging_block ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uwb3_cfg_t uwb3_cfg;  /**< Click config object. */

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
    uwb3_cfg_setup( &uwb3_cfg );
    UWB3_MAP_MIKROBUS( uwb3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == uwb3_init( &uwb3, &uwb3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    // Clear buffers
    uwb3_process( &uwb3 );
    uwb3_clear_app_buf( );
    
    // Switch to stop mode
    uwb3_send_cmd ( &uwb3, UWB3_CMD_STOP );
    uwb3_display_response ( &uwb3 );
    Delay_ms ( 1000 );
    
#if ( DEMO_APP == APP_RESPONDER_1 )
    uwb3_send_cmd_with_parameter ( &uwb3, UWB3_CMD_RESPF, RESPONDER_1_CONFIG );
    uwb3_display_response ( &uwb3 );
    log_printf( &logger, "Application Mode: Responder 1\r\n" );
#elif ( DEMO_APP == APP_RESPONDER_2 )
    uwb3_send_cmd_with_parameter ( &uwb3, UWB3_CMD_RESPF, RESPONDER_2_CONFIG );
    uwb3_display_response ( &uwb3 );
    log_printf( &logger, "Application Mode: Responder 2\r\n" );
#else
    uwb3_send_cmd_with_parameter ( &uwb3, UWB3_CMD_INITF, INITIATOR_CONFIG );
    uwb3_display_response ( &uwb3 );
    log_printf( &logger, "Application Mode: Initiator\r\n" );
#endif
    
    uwb3_clear_app_buf( );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( UWB3_OK == uwb3_process( &uwb3 ) ) 
    {
        if ( UWB3_OK == uwb3_parse_ranging_block ( ) )
        {
            uwb3_clear_app_buf( );
        }
    }
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

static void uwb3_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void uwb3_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t uwb3_process ( uwb3_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = uwb3_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    if ( ( rx_size > 0 ) && ( rx_size <= APP_BUFFER_SIZE ) ) 
    {
        if ( ( app_buf_len + rx_size ) > APP_BUFFER_SIZE ) 
        {
            overflow_bytes = ( app_buf_len + rx_size ) - APP_BUFFER_SIZE;
            app_buf_len = APP_BUFFER_SIZE - rx_size;
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
        return UWB3_OK;
    }
    return UWB3_ERROR;
}

static err_t uwb3_display_response ( uwb3_t *ctx )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 10000;
    uwb3_clear_app_buf( );
    uwb3_process( ctx );
    while ( ( 0 == strstr( app_buf, UWB3_RSP_OK ) ) && 
            ( 0 == strstr( app_buf, UWB3_RSP_ERROR ) ) )
    {
        uwb3_process( ctx );
        if ( timeout_cnt++ > timeout )
        {
            uwb3_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return UWB3_ERROR_TIMEOUT;
        }
        Delay_ms ( 1 );
    }
    Delay_ms ( 100 );
    uwb3_process( ctx );
    uwb3_log_app_buf ( );
    log_printf( &logger, "--------------------------\r\n" );
    return UWB3_OK;
}

static err_t uwb3_parse_ranging_block ( void )
{
    uint8_t * __generic_ptr start_block_ptr = NULL;
    uint8_t * __generic_ptr end_block_ptr = NULL;
    uint8_t * __generic_ptr results_ptr = NULL;
    start_block_ptr = &app_buf[ 0 ];
    for ( ; ; )
    {
        start_block_ptr = strstr( start_block_ptr, "\"Block\"" );
        if ( !start_block_ptr )
        {
            return UWB3_ERROR;
        }
        end_block_ptr = strstr( start_block_ptr, "\r\n" );
        if ( !end_block_ptr )
        {
            return UWB3_ERROR;
        }
        results_ptr = strstr( start_block_ptr, "\"Status\":\"Ok\"" );
        if ( results_ptr && ( ( uint32_t ) results_ptr < ( uint32_t ) end_block_ptr ) )
        {
            log_printf( &logger, "######### " );
            while ( ',' != *start_block_ptr )
            {
                log_printf( &logger, "%c", *start_block_ptr );
                start_block_ptr++;
            }
            log_printf( &logger, " #########\r\n\n" );
            
            while ( results_ptr && ( ( uint32_t ) results_ptr < ( uint32_t ) end_block_ptr ) )
            {
                // Display node address
                results_ptr -= 16;
                while ( ',' != *results_ptr )
                {
                    log_printf( &logger, "%c", *results_ptr );
                    results_ptr++;
                }
                log_printf( &logger, "\r\n" );
                // Display node distance
                results_ptr = strstr( results_ptr, "\"D_cm\"" );
                while ( ',' != *results_ptr )
                {
                    log_printf( &logger, "%c", *results_ptr );
                    results_ptr++;
                }
                log_printf( &logger, "\r\n\n" );
                results_ptr = strstr( results_ptr, "\"Status\":\"Ok\"" );
            }
            return UWB3_OK;
        }
        start_block_ptr = end_block_ptr;
    }
}

// ------------------------------------------------------------------------ END
