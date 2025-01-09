
---
# BarGraph 5 Click

> [BarGraph 5 Click](https://www.mikroe.com/?pid_product=MIKROE-6293) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6293&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of BarGraph 5 Click board by changing the level of all BarGraph output channels.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BarGraph5

### Example Key Functions

- `bargraph5_cfg_setup` Config Object Initialization function.
```c
void bargraph5_cfg_setup ( bargraph5_cfg_t *cfg );
```

- `bargraph5_init` Initialization function.
```c
err_t bargraph5_init ( bargraph5_t *ctx, bargraph5_cfg_t *cfg );
```

- `bargraph5_default_cfg` Click Default Configuration function.
```c
err_t bargraph5_default_cfg ( bargraph5_t *ctx );
```

- `bargraph5_set_bar_level` This function sets the level of a selected BarGraph channel at the selected brightness.
```c
err_t bargraph5_set_bar_level ( bargraph5_t *ctx, bargraph5_bar_sel_t bar_num, bargraph5_level_t level, uint16_t brightness );
```

- `bargraph5_output_enable` This function enables the BarGraph LEDs output by setting the BLANK pin to low logic state.
```c
void bargraph5_output_enable ( bargraph5_t *ctx );
```

- `bargraph5_output_disable` This function disables the BarGraph LEDs output by setting the BLANK pin to high logic state.
```c
void bargraph5_output_disable ( bargraph5_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    bargraph5_cfg_t bargraph5_cfg;  /**< Click config object. */

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
    bargraph5_cfg_setup( &bargraph5_cfg );
    BARGRAPH5_MAP_MIKROBUS( bargraph5_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == bargraph5_init( &bargraph5, &bargraph5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BARGRAPH5_ERROR == bargraph5_default_cfg ( &bargraph5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the level of all BarGraph channels once per second. The channels level is displayed on the USB UART.

```c
void application_task ( void )
{
    for ( bargraph5_level_t cnt = BARGRAPH5_LEVEL_0; cnt <= BARGRAPH5_LEVEL_4; cnt++ )
    {
        bargraph5_set_bar_level ( &bargraph5, BARGRAPH5_BAR_0, cnt, BARGRAPH5_BRIGHTNESS_DEFAULT );
        bargraph5_set_bar_level ( &bargraph5, BARGRAPH5_BAR_1, BARGRAPH5_LEVEL_4 - cnt, BARGRAPH5_BRIGHTNESS_DEFAULT );
        bargraph5_set_bar_level ( &bargraph5, BARGRAPH5_BAR_2, cnt, BARGRAPH5_BRIGHTNESS_DEFAULT );
        bargraph5_set_bar_level ( &bargraph5, BARGRAPH5_BAR_3, BARGRAPH5_LEVEL_4 - cnt, BARGRAPH5_BRIGHTNESS_DEFAULT );
        bargraph5_set_bar_level ( &bargraph5, BARGRAPH5_BAR_4, cnt, BARGRAPH5_BRIGHTNESS_DEFAULT );
        bargraph5_set_bar_level ( &bargraph5, BARGRAPH5_BAR_5, BARGRAPH5_LEVEL_4 - cnt, BARGRAPH5_BRIGHTNESS_DEFAULT );
        log_printf( &logger, " Bars 0-2-4 level: %u\r\n", ( uint16_t ) cnt );
        log_printf( &logger, " Bars 1-3-5 level: %u\r\n\n", ( uint16_t ) ( BARGRAPH5_LEVEL_4 - cnt ) );
        Delay_ms ( 1000 );
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
