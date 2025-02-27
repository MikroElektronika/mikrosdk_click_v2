
---
# Speaker 2 Click

> [Speaker 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6515) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6515&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2024.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the Speaker 2 Click board. It initializes the board
and plays predefined voice messages or sound effects through the speaker module.
Supported voices include numbers (ONE to SIX) and sound effects like FAST BEEP.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Speaker2

### Example Key Functions

- `speaker2_cfg_setup` Config Object Initialization function.
```c
void speaker2_cfg_setup ( speaker2_cfg_t *cfg );
```

- `speaker2_init` Initialization function.
```c
err_t speaker2_init ( speaker2_t *ctx, speaker2_cfg_t *cfg );
```

- `speaker2_default_cfg` Click Default Configuration function.
```c
err_t speaker2_default_cfg ( speaker2_t *ctx );
```

- `speaker2_play_voice` This function plays a voice at the specified index.
```c
err_t speaker2_play_voice ( speaker2_t *ctx, uint16_t index );
```

- `speaker2_play_macro` This function executes a macro command at the specified index.
```c
err_t speaker2_play_macro ( speaker2_t *ctx, uint16_t index );
```

- `speaker2_play_voice_loop` This function plays a voice in a loop for a specified number of iterations.
```c
err_t speaker2_play_voice_loop ( speaker2_t *ctx, uint16_t index, uint16_t loop_cnt );
```

### Application Init

> Initializes the logger module, configures the Speaker 2 Click board, and applies the
default settings to reset the device, power it up, verify communication, and load an example
audio project into the device memory.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    speaker2_cfg_t speaker2_cfg;  /**< Click config object. */

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
    speaker2_cfg_setup( &speaker2_cfg );
    SPEAKER2_MAP_MIKROBUS( speaker2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == speaker2_init( &speaker2, &speaker2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SPEAKER2_ERROR == speaker2_default_cfg ( &speaker2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Sequentially plays predefined voice messages and sound effects from the Speaker 2 Click board
while logging the playback status (DONE or ERROR) for each sound.

```c
void application_task ( void )
{
    log_printf ( &logger, " Playing voice ONE: %s\r\n\n", ( char * ) 
                 ( ( SPEAKER2_OK == speaker2_play_voice ( &speaker2, SPEAKER2_VP9_ONE ) ) ? "DONE" : "ERROR" ) );
    log_printf ( &logger, " Playing voice TWO: %s\r\n\n", ( char * ) 
                 ( ( SPEAKER2_OK == speaker2_play_voice ( &speaker2, SPEAKER2_VP10_TWO ) ) ? "DONE" : "ERROR" ) );
    log_printf ( &logger, " Playing voice THREE: %s\r\n\n", ( char * ) 
                 ( ( SPEAKER2_OK == speaker2_play_voice ( &speaker2, SPEAKER2_VP11_THREE ) ) ? "DONE" : "ERROR" ) );
    log_printf ( &logger, " Playing voice FOUR: %s\r\n\n", ( char * ) 
                 ( ( SPEAKER2_OK == speaker2_play_voice ( &speaker2, SPEAKER2_VP12_FOUR ) ) ? "DONE" : "ERROR" ) );
    log_printf ( &logger, " Playing voice FIVE: %s\r\n\n", ( char * ) 
                 ( ( SPEAKER2_OK == speaker2_play_voice ( &speaker2, SPEAKER2_VP13_FIVE ) ) ? "DONE" : "ERROR" ) );
    log_printf ( &logger, " Playing voice SIX: %s\r\n\n", ( char * ) 
                 ( ( SPEAKER2_OK == speaker2_play_voice ( &speaker2, SPEAKER2_VP14_SIX ) ) ? "DONE" : "ERROR" ) );
    log_printf ( &logger, " Playing voice FAST BEEP: %s\r\n\n", ( char * ) 
                 ( ( SPEAKER2_OK == speaker2_play_voice ( &speaker2, SPEAKER2_VP15_FAST_BEEP ) ) ? "DONE" : "ERROR" ) );
}
```

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
