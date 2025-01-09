
---
# OSD Click

> [OSD Click](https://www.mikroe.com/?pid_product=MIKROE-1366) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1366&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This demo performs basic OSD Click functionality - write text on screen.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.OSD

### Example Key Functions

- `osd_cfg_setup` Config Object Initialization function.
```c
void osd_cfg_setup ( osd_cfg_t *cfg ); 
```

- `osd_init` Initialization function.
```c
err_t osd_init ( osd_t *ctx, osd_cfg_t *cfg );
```

- `osd_default_cfg` Click Default Configuration function.
```c
void osd_default_cfg ( osd_t *ctx );
```

- `osd_clear_display_memory` This function clears display memory.
```c
void osd_clear_display_memory( osd_t *ctx );
```

- `osd_insert_custom_char` This function writes custom character.
```c
void osd_insert_custom_char( osd_t *ctx, uint8_t chr_address, uint8_t custom_char );
```

- `osd_enable_video_buffer` This function enables video buffer.
```c
void osd_enable_video_buffer( osd_t *ctx );
```

### Application Init

> Device initialization.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    osd_cfg_t cfg;

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
    osd_cfg_setup( &cfg );
    OSD_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    osd_init( &osd, &cfg );

    osd_default_cfg( &osd );
    osd_clears_char_places( &osd, 0, 0, 16, 30 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Write text on the screen, write character per 1 second in the first, seventh and fifteenth row of the screen.

```c
void application_task ( void )
{
    log_printf( &logger, "\r\n Writing characters on the screen...\r\n" );
    for ( uint8_t cnt = 0; cnt < 30; cnt++ )
    {
        if ( HEADER_TEXT[ cnt ] != ' ' )
        {
            osd_write_character( &osd, 1, cnt, HEADER_TEXT[ cnt ] );
        }

        if ( MESSAGE_TEXT[ cnt ] != ' ' )
        {
            osd_write_character( &osd, 7, cnt, MESSAGE_TEXT[ cnt ] );
        }

        if ( FOOTER_TEXT[ cnt ] != ' ' )
        {
            osd_write_character( &osd, 14, cnt, FOOTER_TEXT[ cnt ] );
        }

        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " Clear display\r\n" );
    osd_clears_char_places( &osd, 0, 0, 16, 30 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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