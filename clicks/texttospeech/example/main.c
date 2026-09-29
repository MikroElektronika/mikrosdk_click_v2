/*!
 * @file main.c
 * @brief TextToSpeech Click Example.
 *
 * # Description
 * This example demonstrates the use of TextToSpeech Click for converting a text message
 * into speech with selectable voice, language, speaking rate, and volume.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and driver, uploads the firmware, displays version information,
 * and configures the speech and audio settings.
 *
 * ## Application Task
 * Speaks the example text, waits for playback completion, and stops synthesis without resetting TTS.
 * Repeats the message after a five-second pause.
 *
 * @note
 * Connect a speaker to the 3.5 mm audio output and match the I/O SEL jumper to the MCU logic voltage.
 * The supplied firmware image occupies 31208 bytes of program memory and is uploaded at every reset.
 * Allow additional Flash for the driver and application; the vendor recommends an MCU with at least 45 KB.
 * Configure the example with APP_VOICE, APP_LANGUAGE, APP_SPEAKING_RATE, APP_VOLUME_DB, and APP_PARSER.
 * Text uses ISO-8859-1 encoding and should end with sentence punctuation.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "texttospeech.h"

#ifndef MIKROBUS_POSITION_TEXTTOSPEECH
    #define MIKROBUS_POSITION_TEXTTOSPEECH MIKROBUS_1
#endif

/** Speech settings and text sent to the synthesizer. */
#define APP_VOICE                   TEXTTOSPEECH_VOICE_PAUL
#define APP_LANGUAGE                TEXTTOSPEECH_LANGUAGE_US_ENGLISH
#define APP_SPEAKING_RATE           200
#define APP_VOLUME_DB               (-12)
#define APP_PARSER                  TEXTTOSPEECH_PARSER_DECTALK
#define APP_TEXT_MESSAGE            "Hello from Text to Speech Click. This message is generated from text."
#define APP_SPEECH_TIMEOUT_MS       30000

static texttospeech_t texttospeech;   /**< Click driver object. */
static log_t logger;                  /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    texttospeech_cfg_t texttospeech_cfg;  /**< Click config object. */

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
    texttospeech_cfg_setup( &texttospeech_cfg );
    TEXTTOSPEECH_MAP_MIKROBUS( texttospeech_cfg, MIKROBUS_POSITION_TEXTTOSPEECH );
    if ( TEXTTOSPEECH_OK != texttospeech_init( &texttospeech, &texttospeech_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    texttospeech_version_t version;
    err_t error_flag = TEXTTOSPEECH_OK;
    log_printf( &logger, " Uploading firmware...\r\n" );
    error_flag = texttospeech_default_cfg( &texttospeech );
    if ( TEXTTOSPEECH_OK == error_flag )
    {
        error_flag = texttospeech_get_version( &texttospeech, &version );
    }
    if ( TEXTTOSPEECH_OK == error_flag )
    {
        log_printf( &logger, " Hardware version: %u.%u\r\n", ( uint16_t ) version.hardware_major,
                    ( uint16_t ) version.hardware_minor );
        log_printf( &logger, " Firmware version: %u.%u.%u\r\n", ( uint16_t ) version.firmware_major,
                    ( uint16_t ) version.firmware_minor, ( uint16_t ) version.firmware_patch );
        error_flag = texttospeech_set_volume( &texttospeech, APP_VOLUME_DB );
    }
    if ( TEXTTOSPEECH_OK == error_flag )
    {
        error_flag = texttospeech_set_config( &texttospeech, APP_VOICE, APP_LANGUAGE, APP_SPEAKING_RATE, APP_PARSER );
    }
    if ( TEXTTOSPEECH_OK != error_flag )
    {
        log_error( &logger, " Configuration: %d | Device status: 0x%.4X", ( int16_t ) error_flag,
                   ( uint16_t ) texttospeech.device_status );
        for ( ; ; );
    }

    log_printf( &logger, " Voice: %u | Language: %u | Rate: %u words/min | Volume: %d dB\r\n",
                ( uint16_t ) APP_VOICE, ( uint16_t ) APP_LANGUAGE,
                ( uint16_t ) APP_SPEAKING_RATE, ( int16_t ) APP_VOLUME_DB );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    err_t error_flag = TEXTTOSPEECH_OK;
    err_t stop_error = TEXTTOSPEECH_OK;

    log_printf( &logger, " Speaking: %s\r\n", APP_TEXT_MESSAGE );
    error_flag = texttospeech_speak( &texttospeech, APP_TEXT_MESSAGE );
    if ( TEXTTOSPEECH_OK == error_flag )
    {
        // Wait for the actual finished indication, not just acknowledgement of the text.
        error_flag = texttospeech_wait_complete( &texttospeech, APP_SPEECH_TIMEOUT_MS );
        if ( TEXTTOSPEECH_OK == error_flag )
        {
            log_printf( &logger, " Speech completed.\r\n" );
        }
        else
        {
            log_error( &logger, " Speech wait: %d | Device status: 0x%.4X", ( int16_t ) error_flag,
                       ( uint16_t ) texttospeech.device_status );
        }

        // Clear pending text, or stop playback if its wait expired; keep the speech configuration.
        stop_error = texttospeech_stop( &texttospeech );
        if ( TEXTTOSPEECH_OK != stop_error )
        {
            log_error( &logger, " Stop speech: %d", ( int16_t ) stop_error );
        }
    }
    else
    {
        log_error( &logger, " Speak request: %d | Device status: 0x%.4X", ( int16_t ) error_flag,
                   ( uint16_t ) texttospeech.device_status );
    }

    log_printf( &logger, "\r\n" );
    Delay_ms( 5000 );
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
