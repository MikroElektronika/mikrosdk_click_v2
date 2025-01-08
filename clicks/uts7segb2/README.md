
---
# UT-S 7-SEG B 2 Click

> [UT-S 7-SEG B 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5912) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5912&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Mikroe Team
- **Date**          : Nov 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the UT-S 7-SEG B 2 Click board
> by writing and displaying the desired numbers on the screen.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.UTS7SEGB2

### Example Key Functions

- `uts7segb2_cfg_setup` Config Object Initialization function.
```c
void uts7segb2_cfg_setup ( uts7segb2_cfg_t *cfg );
```

- `uts7segb2_init` Initialization function.
```c
err_t uts7segb2_init ( uts7segb2_t *ctx, uts7segb2_cfg_t *cfg );
```

- `uts7segb2_default_cfg` Click Default Configuration function.
```c
err_t uts7segb2_default_cfg ( uts7segb2_t *ctx );
```

- `uts7segb2_display_number` This function displays the desired number and brightness on the selected segments.
```c
err_t uts7segb2_display_number ( uts7segb2_t *ctx, uts7segb2_number_cfg_t number );
```

- `uts7segb2_display_character` This function displays the desired characters and brightness on the selected segments.
```c
err_t uts7segb2_display_character ( uts7segb2_t *ctx, uts7segb2_character_cfg_t ascii_char );
```

- `uts7segb2_set_led_output` This function sets the LED driver output.
```c
err_t uts7segb2_set_led_output ( uts7segb2_t *ctx, uts7segb2_seg_sel_t seg_sel, 
                                 uint32_t seg_bit_mask, uint16_t brightness );
```

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uts7segb2_cfg_t uts7segb2_cfg;  /**< Click config object. */

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
    uts7segb2_cfg_setup( &uts7segb2_cfg );
    UTS7SEGB2_MAP_MIKROBUS( uts7segb2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == uts7segb2_init( &uts7segb2, &uts7segb2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( UTS7SEGB2_ERROR == uts7segb2_default_cfg ( &uts7segb2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    number.brightness_top = UTS7SEGB2_BRIGHTNESS_DEFAULT;
    number.brightness_bottom = UTS7SEGB2_BRIGHTNESS_DEFAULT;
    number.base = UTS7SEGB2_BASE_NUM_SYS_HEXADECIMAL;
    number.dot_bit_mask = UTS7SEGB2_TOP_SEG_NO_DOT | UTS7SEGB2_BOTTOM_SEG_NO_DOT;
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application draws numbers, in hexadecimal format, 
> from 0h to FFFh on the top segment group and from FFFh to 0h on the bottom segment group.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    for ( uint16_t num_cnt = 0; num_cnt <= UTS7SEGB2_HEXADECIMAL_NUM_MAX; num_cnt++ )
    {
        number.num_top = num_cnt;
        number.num_bottom = UTS7SEGB2_HEXADECIMAL_NUM_MAX - num_cnt;
        if ( UTS7SEGB2_OK == uts7segb2_display_number( &uts7segb2, number ) )
        {
            log_printf( &logger, " %.3X\r\n", number.num_top );
            log_printf( &logger, " %.3X\r\n\n", number.num_bottom );
            Delay_ms ( 100 );
        }
    }
    log_printf( &logger, " --------------\r\n\n" );
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
