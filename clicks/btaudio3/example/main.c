/*!
 * @file main.c
 * @brief BT Audio 3 Click Example.
 *
 * # Description
 * This example demonstrates the use of BT Audio 3 click board by reading the commands
 * received from remote device and performing adequate actions accordingly.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and configures the click board.
 *
 * ## Application Task
 * Reads all the received events and parses them.
 *
 * ## Additional Function
 * - static err_t btaudio3_event_handler ( btaudio3_t *ctx ) - This function handles SPP data event 
 * and several BTM state events added in. The other events will just be displayed on the USB UART in hex format.
 *
 * @note
 * We have used the Serial Bluetooth Terminal smartphone application for the test. 
 * A smartphone and the click board must be paired in order to exchange messages
 * with each other. So make sure to pair your device with the click board and
 * connect it to using the Serial Bluetooth Terminal application, then you will be able 
 * to send commands listed below.
 * 
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "btaudio3.h"

static btaudio3_t btaudio3;
static log_t logger;

// Bluetooth device name
#define DEVICE_NAME                 "BT Audio 3 click"

// SPP Commands list
#define COMMAND_PLAY                "play"          // play music
#define COMMAND_PAUSE               "pause"         // pause music
#define COMMAND_STOP                "stop"          // stop music
#define COMMAND_NEXT                "next"          // next song
#define COMMAND_PREVIOUS            "prev"          // previous song
#define COMMAND_VOLUME_UP           "up"            // volume up
#define COMMAND_VOLUME_DOWN         "down"          // volume down
#define COMMAND_UNMUTE              "unmute"        // unmute output
#define COMMAND_MUTE                "mute"          // mute output
#define COMMAND_MODE_UP             "mode"          // switch equalizer mode
#define COMMAND_CALL                "call"          // call command followed by the nuber
#define COMMAND_VOICE               "voice"         // start voice recognition app

/**
 * @brief BT Audio 3 event handler function.
 * @details This function handles SPP data event and several BTM state events added in.
 * The other events will just be displayed on the USB UART in hex format.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @return @li @c  >=0 - Command ACK event response,
 *         @li @c   -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t btaudio3_event_handler ( btaudio3_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    btaudio3_cfg_t btaudio3_cfg;  /**< Click config object. */

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
    btaudio3_cfg_setup( &btaudio3_cfg );
    BTAUDIO3_MAP_MIKROBUS( btaudio3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == btaudio3_init( &btaudio3, &btaudio3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BTAUDIO3_OK != btaudio3_default_cfg ( &btaudio3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    if ( BTAUDIO3_OK != btaudio3_set_device_name ( &btaudio3, DEVICE_NAME ) )
    {
        log_error( &logger, " Set device name." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( BTAUDIO3_OK == btaudio3_read_event ( &btaudio3 ) ) 
    {
        btaudio3_event_handler ( &btaudio3 );
    }
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

static err_t btaudio3_event_handler ( btaudio3_t *ctx )
{
    err_t error_flag = BTAUDIO3_OK;
    static btaudio3_eq_mode_t eq_mode = BTAUDIO2_EQ_MODE_OFF;
    switch ( ctx->event_packet.opcode )
    {
        case BTAUDIO3_EVT_REPORT_SPP_DATA:
        {
            if ( 0 == ctx->event_packet.param_buf[ 1 ] ) // single packet
            {                
                uint16_t payload_len = ( ( uint16_t ) ctx->event_packet.param_buf[ 4 ] << 8 ) | 
                                                      ctx->event_packet.param_buf[ 5 ];
                if ( strstr ( &ctx->event_packet.param_buf[ 6 ], COMMAND_PLAY ) )
                {
                    error_flag |= btaudio3_music_control ( &btaudio3, BTAUDIO3_PLAY );
                    log_printf( &logger, " > play music\r\n\n" );
                } 
                else if ( strstr ( &ctx->event_packet.param_buf[ 6 ], COMMAND_PAUSE ) )
                {
                    error_flag |= btaudio3_music_control ( &btaudio3, BTAUDIO3_PAUSE );
                    log_printf( &logger, " > pause music\r\n\n" );
                }
                else if ( strstr ( &ctx->event_packet.param_buf[ 6 ], COMMAND_STOP ) )
                {
                    error_flag |= btaudio3_music_control ( &btaudio3, BTAUDIO3_STOP );
                    log_printf( &logger, " > stop music\r\n\n" );
                }
                else if ( strstr ( &ctx->event_packet.param_buf[ 6 ], COMMAND_NEXT ) )
                {
                    error_flag |= btaudio3_music_control ( &btaudio3, BTAUDIO3_NEXT_SONG );
                    log_printf( &logger, " > next song\r\n\n" );
                }
                else if ( strstr ( &ctx->event_packet.param_buf[ 6 ], COMMAND_PREVIOUS ) )
                {
                    error_flag |= btaudio3_music_control ( &btaudio3, BTAUDIO3_PREVIOUS_SONG );
                    log_printf( &logger, " > previous song\r\n\n" );
                }
                else if ( strstr ( &ctx->event_packet.param_buf[ 6 ], COMMAND_VOLUME_UP ) )
                {
                    error_flag |= btaudio3_volume_up ( &btaudio3, 0, BTAUDIO3_VOLUME_MASK_A2DP );
                    log_printf( &logger, " > volume up\r\n\n" );
                }
                else if ( strstr ( &ctx->event_packet.param_buf[ 6 ], COMMAND_VOLUME_DOWN ) )
                {
                    error_flag |= btaudio3_volume_down ( &btaudio3, 0, BTAUDIO3_VOLUME_MASK_A2DP );
                    log_printf( &logger, " > volume down\r\n\n" );
                }
                else if ( strstr ( &ctx->event_packet.param_buf[ 6 ], COMMAND_UNMUTE ) )
                {
                    btaudio3_soft_unmute_output ( &btaudio3 );
                    log_printf( &logger, " > unmute output\r\n\n" );
                }
                else if ( strstr ( &ctx->event_packet.param_buf[ 6 ], COMMAND_MUTE ) )
                {
                    btaudio3_soft_mute_output ( &btaudio3 );
                    log_printf( &logger, " > mute output\r\n\n" );
                }
                else if ( strstr ( &ctx->event_packet.param_buf[ 6 ], COMMAND_CALL ) )
                {
                    uint8_t phone_number[ 19 ] = { 0 };
                    memcpy ( phone_number, strstr ( &ctx->event_packet.param_buf[ 6 ], COMMAND_CALL ) + 5, payload_len - 7 );
                    error_flag |= btaudio3_make_call ( &btaudio3, 0x00, phone_number );
                    log_printf( &logger, " > calling number: %s\r\n\n", phone_number );
                }
                else if ( strstr ( &ctx->event_packet.param_buf[ 6 ], COMMAND_VOICE ) )
                {
                    error_flag |= btaudio3_send_mmi_action ( ctx, 0, BTAUDIO3_MMI_VOICE_DIAL );
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
                    btaudio3_set_eq_mode ( &btaudio3, eq_mode );
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
        case BTAUDIO3_EVT_BTM_STATE:
        {
            switch ( ctx->event_packet.param_buf[ 0 ] )
            {
                case BTAUDIO3_BTM_STATE_PAIRING_SUCCESSFULL:
                {
                    log_printf( &logger, " < Pairing successfull - linked device ID: %u\r\n\n", 
                                ( uint16_t ) ctx->event_packet.param_buf[ 1 ] );
                    break;
                }
                case BTAUDIO3_BTM_STATE_SCO_LINK_CONNECTED:
                {
                    log_printf( &logger, " < SCO link connected - linked device ID: %u\r\n\n", 
                                ( uint16_t ) ctx->event_packet.param_buf[ 1 ] );
                    break;
                }
                case BTAUDIO3_BTM_STATE_SCO_LINK_DISCONNECTED:
                {
                    log_printf( &logger, " < SCO link disconnected - linked device ID: %u\r\n\n", 
                                ( uint16_t ) ctx->event_packet.param_buf[ 1 ] );
                    break;
                }
                case BTAUDIO3_BTM_STATE_ACL_CONNECTED:
                {
                    log_printf( &logger, " < ACL connected - linked data base: %u\r\n\n", 
                                ( uint16_t ) ctx->event_packet.param_buf[ 1 ] );
                    break;
                }
                case BTAUDIO3_BTM_STATE_ACL_DISCONNECTED:
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
                case BTAUDIO3_BTM_STATE_STANDBY_STATE:
                {
                    log_printf( &logger, " < Standby state\r\n\n" );
                    log_printf( &logger, " > ReEnter pairing mode\r\n\n" );
                    error_flag |= btaudio3_enter_pairing_mode ( &btaudio3 );
                    break;
                }
                case BTAUDIO3_BTM_STATE_UNKNOWN_AUDIO_SOURCE:
                {
                    log_printf( &logger, " < Unknown audio source\r\n\n" );
                    break;
                }
                case BTAUDIO3_BTM_STATE_AUX_IN_AUDIO_SOURCE:
                {
                    log_printf( &logger, " < AUX-IN audio source\r\n\n" );
                    break;
                }
                case BTAUDIO3_BTM_STATE_A2DP_AUDIO_SOURCE:
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
