
---
# UT-L 7-SEG R Click

> [UT-L 7-SEG R Click](https://www.mikroe.com/?pid_product=MIKROE-2743) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2743&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> The demo application shows basic usage of the UT 7 SEG display.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.UT-L7-SEGR

### Example Key Functions

- `utl7segr_cfg_setup` Config Object Initialization function.
```c
void utl7segr_cfg_setup ( utl7segr_cfg_t *cfg );
```

- `utl7segr_init` Initialization function.
```c
err_t utl7segr_init ( utl7segr_t *ctx, utl7segr_cfg_t *cfg );
```

- `utl7segr_default_cfg` Click Default Configuration function.
```c
void utl7segr_default_cfg ( utl7segr_t *ctx );
```

- `utl7segr_generic_write` This function writes a desired number of data bytes starting from the selected register by using SPI serial interface.
```c
err_t utl7segr_generic_write ( utl7segr_t *ctx, uint8_t *data_in );
```

- `utl7segr_display_state` This function turns display on and off.
```c
void utl7segr_display_state ( utl7segr_t *ctx, uint8_t state );

```

- `utl7segr_display_number` This function is used to show the number on the display.
```c
void utl7segr_display_number ( utl7segr_t *ctx, uint8_t number, uint8_t dot_pos );
```

### Application Init

> Configuring Clicks and log objects. Settings the Click in the default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    utl7segr_cfg_t utl7segr_cfg;  /**< Click config object.  */

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
    log_info( &logger, "---- Application Init ----" );

    // Click initialization.

    utl7segr_cfg_setup( &utl7segr_cfg );
    UTL7SEGR_MAP_MIKROBUS( utl7segr_cfg, MIKROBUS_1 );
    err_t init_flag  = utl7segr_init( &utl7segr, &utl7segr_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    utl7segr_default_cfg ( &utl7segr );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Draws numbers from 0 to 99 on the screen.

```c
void application_task ( void ) 
{  
    log_info( &logger, "---- Number counter ----" );

    for ( uint8_t cnt = 0; cnt < 100; cnt++ ) {
        utl7segr_display_number( &utl7segr, cnt, UTL7SEGR_DOT_LEFT );
        Delay_ms ( 500 );
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
