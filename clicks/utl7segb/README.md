
---
# UT-L 7-SEG B Click

> [UT-L 7-SEG B Click](https://www.mikroe.com/?pid_product=MIKROE-5824) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5824&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the UT-L 7-SEG B Click board&trade; 
> by writing and displaying the desired numbers on the screen.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.UTL7SEGB

### Example Key Functions

- `utl7segb_cfg_setup` Config Object Initialization function.
```c
void utl7segb_cfg_setup ( utl7segb_cfg_t *cfg );
```

- `utl7segb_init` Initialization function.
```c
err_t utl7segb_init ( utl7segb_t *ctx, utl7segb_cfg_t *cfg );
```

- `utl7segb_default_cfg` Click Default Configuration function.
```c
err_t utl7segb_default_cfg ( utl7segb_t *ctx );
```

- `utl7segb_display_number` UT-L 7-SEG B display number function.
```c
err_t utl7segb_display_number ( utl7segb_t *ctx, uint8_t base, uint8_t num, uint8_t dot_pos );
```

- `utl7segb_enable`  UT-L 7-SEG B enable function.
```c
void utl7segb_enable ( utl7segb_t *ctx );
```

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    utl7segb_cfg_t utl7segb_cfg;  /**< Click config object. */

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
    utl7segb_cfg_setup( &utl7segb_cfg );
    UTL7SEGB_MAP_MIKROBUS( utl7segb_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == utl7segb_init( &utl7segb, &utl7segb_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( UTL7SEGB_ERROR == utl7segb_default_cfg ( &utl7segb ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> The demo application draws numbers, in hexadecimal format, from 0h to FFh on the display.

```c
void application_task ( void )
{
    for ( uint8_t hex_num = 0x00; hex_num < 0xFF; hex_num++ ) 
    {
        if ( UTL7SEGB_OK == utl7segb_display_number( &utl7segb, 
                                                     UTL7SEGB_BASE_NUM_SYS_HEXADECIMAL, 
                                                     hex_num, 
                                                     UTL7SEGB_NO_DOT ) )
        {
            log_printf( &logger, " --- %.2X ---\r\n", ( uint16_t ) hex_num );
            Delay_ms ( 500 );
        }
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
