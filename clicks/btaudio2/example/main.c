/*!
 * @file main.c
 * @brief BT Audio 2 Click Example.
 *
 * # Description
 * This example demonstrates the use of BT Audio 2 Click board by reading the commands
 * received from remote device and performing adequate actions accordingly.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and configures the Click board.
 *
 * ## Application Task
 * Reads all the received events and parses them.
 *
 * ## Additional Function
 * - static err_t btaudio2_event_handler ( btaudio2_t *ctx ) - This function handles SPP data event 
 * and several BTM state events added in. The other events will just be displayed on the USB UART in hex format.
 *
 * @note
 * We have used the Serial Bluetooth Terminal smartphone application for the test. 
 * A smartphone and the Click board must be paired in order to exchange messages
 * with each other. So make sure to pair your device with the Click board and
 * connect it to using the Serial Bluetooth Terminal application, then you will be able 
 * to send commands listed below.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "btaudio2.h"

static btaudio2_t btaudio2;
static log_t logger;

// Bluetooth device name
#define DEVICE_NAME                 "BT Audio 2 Click"

// SPP Commands list
#define COMMAND_PLAY                "play"          // play music
#define COMMAND_PAUSE               "pause"         // pause music
#define COMMAND_STOP                "stop"          // stop music
#define COMMAND_NEXT                "next"          // next song
#define COMMAND_PREVIOUS            "prev"          // previous song
#define COMMAND_VOLUME_UP           "up"            // volume up
#define COMMAND_VOLUME_DOWN         "down"          // volume down
#define COMMAND_MODE_UP             "mode"          // switch equalizer mode
#define COMMAND_CALL                "call"          // call command followed by the number
#define COMMAND_VOICE               "voice"         // start voice recognition app

/**
 * @brief BT Audio 2 event handler function.
 * @details This function handles SPP data event and several BTM state events added in.
 * The other events will just be displayed on the USB UART in hex format.
 * @param[in] ctx : Click context object.
 * See #btaudio2_t object definition for detailed explanation.
 * @return @li @c  >=0 - Command ACK event response,
 *         @li @c   -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t btaudio2_event_handler ( btaudio2_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    btaudio2_cfg_t btaudio2_cfg;  /**< Click config object. */

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
    btaudio2_cfg_setup( &btaudio2_cfg );
    BTAUDIO2_MAP_MIKROBUS( btaudio2_cfg, MIKROBUS_1 );
    if ( UART_ERROR == btaudio2_init( &btaudio2, &btaudio2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BTAUDIO2_OK != btaudio2_default_cfg ( &btaudio2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    if ( BTAUDIO2_OK != btaudio2_set_device_name ( &btaudio2, DEVICE_NAME ) )
    {
        log_error( &logger, " Set device name." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( BTAUDIO2_OK == btaudio2_read_event ( &btaudio2 ) ) 
    {
        btaudio2_event_handler ( &btaudio2 );
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

static err_t btaudio2_event_handler ( btaudio2_t *ctx )
{
    err_t error_flag = BTAUDIO2_OK;
    static btaudio2_eq_mode_t eq_mode = BTAUDIO2_EQ_MODE_OFF;
    switch ( ctx->event_packet.opcode )
    {
        case BTAUDIO2_EVT_REPORT_SPP_DATA:
        {
            if ( 0 == ctx->event_packet.param_buf[ 1 ] ) // single packet
            {                
                uint16_t payload_len = ( ( uint16_t ) ctx->event_packet.param_buf[ 4 ] << 8 ) | 
                                                      ctx->event_packet.param_buf[ 5 ];
                if ( strstr ( &ctx->event_packet.param_buf[ 6 ], COMMAND_PLAY ) )
                {
                    error_flag |= btaudio2_send_mmi_action ( ctx, 0, BTAUDIO2_MMI_PLAY_PAUSE_MUSIC );
                    log_printf( &logger, " > play music\r\n\n" );
                } 
                else if ( strstr ( &ctx->event_packet.param_buf[ 6 ], COMMAND_PAUSE ) )
                {
                    error_flag |= btaudio2_send_mmi_action ( ctx, 0, BTAUDIO2_MMI_PLAY_PAUSE_MUSIC );
                    log_printf( &logger, " > pause music\r\n\n" );
                }
                else if ( strstr ( &ctx->event_packet.param_buf[ 6 ], COMMAND_STOP ) )
                {
                    error_flag |= btaudio2_send_mmi_action ( ctx, 0, BTAUDIO2_MMI_STOP_MUSIC );
                    log_printf( &logger, " > stop music\r\n\n" );
                }
                else if ( strstr ( &ctx->event_packet.param_buf[ 6 ], COMMAND_NEXT ) )
                {
                    error_flag |= btaudio2_send_mmi_action ( ctx, 0, BTAUDIO2_MMI_NEXT_SONG );
                    log_printf( &logger, " > next song\r\n\n" );
                }
                else if ( strstr ( &ctx->event_packet.param_buf[ 6 ], COMMAND_PREVIOUS ) )
                {
                    error_flag |= btaudio2_send_mmi_action ( ctx, 0, BTAUDIO2_MMI_PREVIOUS_SONG );
                    log_printf( &logger, " > previous song\r\n\n" );
                }
                else if ( strstr ( &ctx->event_packet.param_buf[ 6 ], COMMAND_VOLUME_UP ) )
                {
                    error_flag |= btaudio2_volume_up ( &btaudio2, 0, BTAUDIO2_VOLUME_MASK_A2DP );
                    log_printf( &logger, " > volume up\r\n\n" );
                }
                else if ( strstr ( &ctx->event_packet.param_buf[ 6 ], COMMAND_VOLUME_DOWN ) )
                {
                    error_flag |= btaudio2_volume_down ( &btaudio2, 0, BTAUDIO2_VOLUME_MASK_A2DP );
                    log_printf( &logger, " > volume down\r\n\n" );
                }
                else if ( strstr ( &ctx->event_packet.param_buf[ 6 ], COMMAND_CALL ) )
                {
                    uint8_t phone_number[ 19 ] = { 0 };
                    memcpy ( phone_number, strstr ( &ctx->event_packet.param_buf[ 6 ], COMMAND_CALL ) + 5, payload_len - 7 );
                    error_flag |= btaudio2_make_call ( &btaudio2, 0x00, phone_number );
                    log_printf( &logger, " > calling number: %s\r\n\n", phone_number );
                }
                else if ( strstr ( &ctx->event_packet.param_buf[ 6 ], COMMAND_VOICE ) )
                {
                    error_flag |= btaudio2_send_mmi_action ( ctx, 0, BTAUDIO2_MMI_VOICE_DIAL );
                    log_printf( &logger, " > start voice recognition\r\n\n" );
                }
                else if ( strstr ( &ctx->event_packet.param_buf[ 6 ], COMMAND_MODE_UP ) )
                {
                    if ( BTAUDIO2_EQ_MODE_USER1 == eq_mode )
                    {
                        eq_mode = BTAUDIO2_EQ_MODE_OFF;
                    }
                    else
                    {
                        eq_mode++;
                    }
                    btaudio2_set_eq_mode ( &btaudio2, eq_mode );
                    log_printf( &logger, " > equalizer mode: " );
                    switch ( eq_mode )
                    {
                        case BTAUDIO2_EQ_MODE_OFF:
                        {
                            log_printf( &logger, "off\r\n\n" );
                            break;
                        }
                        case BTAUDIO2_EQ_MODE_SOFT:
                        {
                            log_printf( &logger, "soft\r\n\n" );
                            break;
                        }
                        case BTAUDIO2_EQ_MODE_BASS:
                        {
                            log_printf( &logger, "bass\r\n\n" );
                            break;
                        } 
                        case BTAUDIO2_EQ_MODE_TREBLE:
                        {
                            log_printf( &logger, "treble\r\n\n" );
                            break;
                        }  
                        case BTAUDIO2_EQ_MODE_CLASSIC:
                        {
                            log_printf( &logger, "classic\r\n\n" );
                            break;
                        }
                        case BTAUDIO2_EQ_MODE_ROCK:
                        {
                            log_printf( &logger, "rock\r\n\n" );
                            break;
                        }
                        case BTAUDIO2_EQ_MODE_JAZZ:
                        {
                            log_printf( &logger, "jazz\r\n\n" );
                            break;
                        }
                        case BTAUDIO2_EQ_MODE_POP:
                        {
                            log_printf( &logger, "pop\r\n\n" );
                            break;
                        }
                        case BTAUDIO2_EQ_MODE_DANCE:
                        {
                            log_printf( &logger, "dance\r\n\n" );
                            break;
                        }
                        case BTAUDIO2_EQ_MODE_RNB:
                        {
                            log_printf( &logger, "rnb\r\n\n" );
                            break;
                        }
                        case BTAUDIO2_EQ_MODE_USER1:
                        {
                            log_printf( &logger, "user1\r\n\n" );
                            break;
                        }
                        default:
                        {
                            log_printf( &logger, "unknown\r\n\n" );
                            break;
                        }
                    }
                }
                else
                {
                    log_printf( &logger, " Unknown command: ", &ctx->event_packet.param_buf[ 6 ] );
                    for ( uint16_t cnt = 0; cnt < payload_len; cnt++ )
                    {
                        log_printf( &logger, "%c", ctx->event_packet.param_buf[ cnt + 6 ] );
                    }
                    log_printf( &logger, "\r\n\n" );
                }
            }
            break;
        }
        case BTAUDIO2_EVT_BTM_STATE:
        {
            switch ( ctx->event_packet.param_buf[ 0 ] )
            {
                case BTAUDIO2_BTM_STATE_PAIRING_SUCCESSFULL:
                {
                    log_printf( &logger, " < Pairing successfull - linked device ID: %u\r\n\n", 
                                ( uint16_t ) ctx->event_packet.param_buf[ 1 ] );
                    break;
                }
                case BTAUDIO2_BTM_STATE_SCO_LINK_CONNECTED:
                {
                    log_printf( &logger, " < SCO link connected - linked device ID: %u\r\n\n", 
                                ( uint16_t ) ctx->event_packet.param_buf[ 1 ] );
                    break;
                }
                case BTAUDIO2_BTM_STATE_SCO_LINK_DISCONNECTED:
                {
                    log_printf( &logger, " < SCO link disconnected - linked device ID: %u\r\n\n", 
                                ( uint16_t ) ctx->event_packet.param_buf[ 1 ] );
                    break;
                }
                case BTAUDIO2_BTM_STATE_ACL_CONNECTED:
                {
                    log_printf( &logger, " < ACL connected - linked data base: %u\r\n\n", 
                                ( uint16_t ) ctx->event_packet.param_buf[ 1 ] );
                    break;
                }
                case BTAUDIO2_BTM_STATE_ACL_DISCONNECTED:
                {
                    log_printf( &logger, " < ACL disconnected - " );
                    if ( 0 == ctx->event_packet.param_buf[ 1 ] )
                    {
                        log_printf( &logger, "disconnection\r\n\n" );
                    }
                    else if ( 1 == ctx->event_packet.param_buf[ 1 ] )
                    {
                        log_printf( &logger, "link loss\r\n\n" );
                    }
                    break;
                }
                case BTAUDIO2_BTM_STATE_STANDBY_STATE:
                {
                    log_printf( &logger, " < Standby state\r\n\n" );
                    break;
                }
                case BTAUDIO2_BTM_STATE_UNKNOWN_AUDIO_SOURCE:
                {
                    log_printf( &logger, " < Unknown audio source\r\n\n" );
                    break;
                }
                case BTAUDIO2_BTM_STATE_AUX_IN_AUDIO_SOURCE:
                {
                    log_printf( &logger, " < AUX-IN audio source\r\n\n" );
                    break;
                }
                case BTAUDIO2_BTM_STATE_A2DP_AUDIO_SOURCE:
                {
                    log_printf( &logger, " < A2DP audio source\r\n\n" );
                    break;
                }
                default:
                {
                    log_printf( &logger, " < EVENT BTM STATE: " );
                    for ( uint16_t cnt = 0; cnt < ctx->event_packet.param_len; cnt++ )
                    {
                        log_printf( &logger, "0x%.2X ", ( uint16_t ) ctx->event_packet.param_buf[ cnt ] );
                    }
                    log_printf( &logger, "\r\n\n" );
                    break;
                }
            }
            break;
        }
        default: 
        {
            log_printf( &logger, " < EVENT 0x%.2X: ", ( uint16_t ) ctx->event_packet.opcode );
            for ( uint16_t cnt = 0; cnt < ctx->event_packet.param_len; cnt++ )
            {
                log_printf( &logger, "0x%.2X ", ( uint16_t ) ctx->event_packet.param_buf[ cnt ] );
            }
            log_printf( &logger, "\r\n\n" );
            break;
        }
    }
    return error_flag;
}

// ------------------------------------------------------------------------ END
