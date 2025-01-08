
---
# BarGraph 4 Click

> [BarGraph 4 Click](https://www.mikroe.com/?pid_product=MIKROE-4782) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4782&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of BarGraph 4 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BarGraph4

### Example Key Functions

- `bargraph4_cfg_setup` Config Object Initialization function.
```c
void bargraph4_cfg_setup ( bargraph4_cfg_t *cfg );
```

- `bargraph4_init` Initialization function.
```c
err_t bargraph4_init ( bargraph4_t *ctx, bargraph4_cfg_t *cfg );
```

- `bargraph4_enable_output` This function enables all outputs.
```c
void bargraph4_enable_output ( bargraph4_t *ctx );
```

- `bargraph4_set_output` This function sets all outputs to desired value by using SPI serial interface.
```c
err_t bargraph4_set_output ( bargraph4_t *ctx, uint16_t ch_mask );
```

- `bargraph4_set_channel_level` This function sets the level of a desired bar graph channel.
```c
err_t bargraph4_set_channel_level ( bargraph4_t *ctx, bargraph4_sel_ch_t channel, bargraph4_level_t level );
```

### Application Init

> Initializes the driver and enables output.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    bargraph4_cfg_t bargraph4_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    bargraph4_cfg_setup( &bargraph4_cfg );
    BARGRAPH4_MAP_MIKROBUS( bargraph4_cfg, MIKROBUS_1 );
    err_t init_flag  = bargraph4_init( &bargraph4, &bargraph4_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    bargraph4_enable_output( &bargraph4 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the level of all bar graph channels every second. The channels level will be logged on the USB UART.

```c
void application_task ( void )
{
    for ( bargraph4_level_t cnt = BARGRAPH4_LEVEL_0; cnt <= BARGRAPH4_LEVEL_4; cnt++ )
    {
        bargraph4_set_channel_level( &bargraph4, BARGRAPH4_CHANNEL_A, cnt );
        bargraph4_set_channel_level( &bargraph4, BARGRAPH4_CHANNEL_B, cnt );
        bargraph4_set_channel_level( &bargraph4, BARGRAPH4_CHANNEL_C, cnt );
        bargraph4_set_channel_level( &bargraph4, BARGRAPH4_CHANNEL_D, cnt );
        log_printf( &logger, " All channels set to level %u\r\n\n", ( uint16_t ) cnt );
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
