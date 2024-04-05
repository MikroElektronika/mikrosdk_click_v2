/*!
 * @file main.c
 * @brief SpeakUp 3 Click Example.
 *
 * # Description
 * This example demonstrates the use of the SpeakUp 3 click board by reading
 * and displaying the voice commands reply messages.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes driver and logger.
 *
 * ## Application Task
 * Waits for the reply message to a voice command and displays it on the USB UART.
 *
 * ## Additional Function
 * - static void speakup3_display_reply ( void )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "speakup3.h"

static speakup3_t speakup3;
static log_t logger;

/**
 * @brief SpeakUp 3 display reply function.
 * @details This function displays on the USB UART the reply message for the selected
 * reply instruction code.
 * @param[in] reply_ins : Reply instruction code.
 * @return None.
 * @note None.
 */
static void speakup3_display_reply ( uint8_t reply_ins );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    speakup3_cfg_t speakup3_cfg;  /**< Click config object. */

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
    speakup3_cfg_setup( &speakup3_cfg );
    SPEAKUP3_MAP_MIKROBUS( speakup3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == speakup3_init( &speakup3, &speakup3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t reply_ins;
    if ( SPEAKUP3_OK == speakup3_wait_for_reply ( &speakup3, &reply_ins, 1000 ) )
    {
        speakup3_display_reply ( reply_ins );
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

static void speakup3_display_reply ( uint8_t reply_ins )
{
    log_printf( &logger, " Reply: " );
    switch ( reply_ins )
    {
        case SPEAKUP3_INS_ENTER_WAKE_UP:
        {
            log_printf( &logger, "Hi, how can I help? / Hi, what's up? / Yes, I'm here.\r\n" );
            break;
        }
        case SPEAKUP3_INS_EXIT_WAKE_UP:
        {
            log_printf( &logger, "See you later.\r\n" );
            break;
        }
        case SPEAKUP3_INS_LEARN_MATCH_AC:
        {
            log_printf( &logger, "OK, match the air conditioner.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_TURN_ON:
        {
            log_printf( &logger, "OK, turn on the air conditioner.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_TURN_OFF:
        {
            log_printf( &logger, "OK, turn off the air conditioner.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_MODE_AUTO:
        {
            log_printf( &logger, "OK, automatic mode.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_MODE_COLD:
        {
            log_printf( &logger, "OK, cold mode.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_MODE_HEAT:
        {
            log_printf( &logger, "OK, heat mode.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_MODE_DRY:
        {
            log_printf( &logger, "OK, dry mode.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_MODE_FAN:
        {
            log_printf( &logger, "OK, fan mode.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_MODE_SLEEP:
        {
            log_printf( &logger, "OK, sleeping mode.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_WIND_AUTO:
        {
            log_printf( &logger, "OK, automatic fan.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_WIND_LOW:
        {
            log_printf( &logger, "OK, low fan.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_WIND_MID:
        {
            log_printf( &logger, "OK, medium fan.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_WIND_HIGH:
        {
            log_printf( &logger, "OK, high fan.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_WIND_INC:
        {
            log_printf( &logger, "OK, higher the fan.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_WIND_DEC:
        {
            log_printf( &logger, "OK, lower the fan.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_TMP_16:
        {
            log_printf( &logger, "OK, sixteen centigrade.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_TMP_17:
        {
            log_printf( &logger, "OK, seventeen centigrade.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_TMP_18:
        {
            log_printf( &logger, "OK, eighteen centigrade.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_TMP_19:
        {
            log_printf( &logger, "OK, nineteen centigrade.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_TMP_20:
        {
            log_printf( &logger, "OK, twenty centigrade.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_TMP_21:
        {
            log_printf( &logger, "OK, twenty one centigrade.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_TMP_22:
        {
            log_printf( &logger, "OK, twenty two centigrade.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_TMP_23:
        {
            log_printf( &logger, "OK, twenty three centigrade.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_TMP_24:
        {
            log_printf( &logger, "OK, twenty four centigrade.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_TMP_25:
        {
            log_printf( &logger, "OK, twenty five centigrade.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_TMP_26:
        {
            log_printf( &logger, "OK, twenty six centigrade.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_TMP_27:
        {
            log_printf( &logger, "OK, twenty seven centigrade.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_TMP_28:
        {
            log_printf( &logger, "OK, twenty eight centigrade.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_TMP_29:
        {
            log_printf( &logger, "OK, twenty nine centigrade.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_TMP_30:
        {
            log_printf( &logger, "OK, thirty centigrade.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_TMP_INC:
        {
            log_printf( &logger, "OK, warmer.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_TMP_DEC:
        {
            log_printf( &logger, "OK, cooler.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_SWEPT_ON:
        {
            log_printf( &logger, "OK, start to fan.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_SWEPT_OFF:
        {
            log_printf( &logger, "OK, stop to fan.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_SWEPT_VERT:
        {
            log_printf( &logger, "OK, air swing up and down.\r\n" );
            break;
        }
        case SPEAKUP3_INS_AC_SWEPT_CROSS:
        {
            log_printf( &logger, "OK, air swing left and right.\r\n" );
            break;
        }
        case SPEAKUP3_INS_SET_RESTORE:
        {
            log_printf( &logger, "OK, air conditioner reset.\r\n" );
            break;
        }
        default:
        {
            log_printf( &logger, "Unknown.\r\n" );
            break;
        }
    }
}

// ------------------------------------------------------------------------ END
