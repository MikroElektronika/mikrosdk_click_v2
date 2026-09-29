
---
# TextToSpeech Click

> [TextToSpeech Click](https://www.mikroe.com/?pid_product=MIKROE-2253) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2253&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of TextToSpeech Click for converting a text message
into speech with selectable voice, language, speaking rate, and volume.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TextToSpeech

### Example Key Functions

- `texttospeech_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void texttospeech_cfg_setup ( texttospeech_cfg_t *cfg );
```

- `texttospeech_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t texttospeech_init ( texttospeech_t *ctx, texttospeech_cfg_t *cfg );
```

- `texttospeech_default_cfg` This function resets the device, uploads the supplied firmware and registers the host.
```c
err_t texttospeech_default_cfg ( texttospeech_t *ctx );
```

- `texttospeech_set_volume` This function sets absolute analogue gain and configures mono 11.025 kHz audio output.
```c
err_t texttospeech_set_volume ( texttospeech_t *ctx, int8_t gain_db );
```

- `texttospeech_speak` This function sends a null-terminated text message and verifies that speech was accepted.
```c
err_t texttospeech_speak ( texttospeech_t *ctx, char *text );
```

- `texttospeech_wait_complete` This function processes received messages until speech is finished and TTS is ready.
```c
err_t texttospeech_wait_complete ( texttospeech_t *ctx, uint32_t timeout_ms );
```

### Application Init

> Initializes the logger and driver, uploads the firmware, displays version information,
and configures the speech and audio settings.

```c
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
```

### Application Task

> Speaks the example text, waits for playback completion, and stops synthesis without resetting TTS.
Repeats the message after a five-second pause.

```c
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
```

### Note

> Connect a speaker to the 3.5 mm audio output and match the I/O SEL jumper to the MCU logic voltage.
The supplied firmware image occupies 31208 bytes of program memory and is uploaded at every reset.
Allow additional Flash for the driver and application; the vendor recommends an MCU with at least 45 KB.
Configure the example with APP_VOICE, APP_LANGUAGE, APP_SPEAKING_RATE, APP_VOLUME_DB, and APP_PARSER.
Text uses ISO-8859-1 encoding and should end with sentence punctuation.

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
