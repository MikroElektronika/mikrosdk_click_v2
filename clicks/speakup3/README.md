
---
# SpeakUp 3 Click

> [SpeakUp 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5420) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5420&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2022.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of the SpeakUp 3 Click board by reading and displaying the voice commands reply messages.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SpeakUp3

### Example Key Functions

- `speakup3_cfg_setup` Config Object Initialization function.
```c
void speakup3_cfg_setup ( speakup3_cfg_t *cfg );
```

- `speakup3_init` Initialization function.
```c
err_t speakup3_init ( speakup3_t *ctx, speakup3_cfg_t *cfg );
```

- `speakup3_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t speakup3_generic_read ( speakup3_t *ctx, char *data_out, uint16_t len );
```

- `speakup3_wait_for_reply` This function waits up to @b wait_ms for a reply to the voice command.
```c
err_t speakup3_wait_for_reply ( speakup3_t *ctx, uint8_t *reply_ins, uint32_t wait_ms );
```

### Application Init

> Initializes driver and logger.

```c
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
```

### Application Task

> Waits for the reply message to a voice command and displays it on the USB UART.

```c
void application_task ( void )
{
    uint8_t reply_ins;
    if ( SPEAKUP3_OK == speakup3_wait_for_reply ( &speakup3, &reply_ins, 1000 ) )
    {
        speakup3_display_reply ( reply_ins );
    }
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
