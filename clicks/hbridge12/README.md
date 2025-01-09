
---
# H-Bridge 12 Click

> [H-Bridge 12 Click](https://www.mikroe.com/?pid_product=MIKROE-5690) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5690&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Apr 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the H-Bridge 12 Click board by
  driving the motor connected to OUT A and OUT B, in both directions with braking and freewheeling. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge12

### Example Key Functions

- `hbridge12_cfg_setup` Config Object Initialization function.
```c
void hbridge12_cfg_setup ( hbridge12_cfg_t *cfg );
```

- `hbridge12_init` Initialization function.
```c
err_t hbridge12_init ( hbridge12_t *ctx, hbridge12_cfg_t *cfg );
```

- `hbridge12_default_cfg` Click Default Configuration function.
```c
err_t hbridge12_default_cfg ( hbridge12_t *ctx );
```

- `hbridge12_write_config` H-Bridge 12 write settings function.
```c
err_t hbridge12_write_config ( hbridge12_t *ctx, hbridge12_config_t config_data );
```

- `hbridge12_set_current_scale` H-Bridge 12 set current scale function.
```c
void hbridge12_set_current_scale ( hbridge12_t *ctx, uint8_t channel_sel, uint8_t out1_curr_scale, uint8_t out2_curr_scale );
```

- `hbridge12_turn_clockwise` H-Bridge 12 turn motor clockwise function.
```c
err_t hbridge12_turn_clockwise ( hbridge12_t *ctx, uint8_t channel_sel );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge12_cfg_t hbridge12_cfg;  /**< Click config object. */

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
    hbridge12_cfg_setup( &hbridge12_cfg );
    HBRIDGE12_MAP_MIKROBUS( hbridge12_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == hbridge12_init( &hbridge12, &hbridge12_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HBRIDGE12_ERROR == hbridge12_default_cfg ( &hbridge12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Driving motor in both directions for 5 seconds with a motor braking and freewheeling in between.

```c
void application_task ( void )
{
    log_printf( &logger, " Turning motor counterclockwise \r\n" );
    hbridge12_turn_counterclockwise( &hbridge12, HBRIDGE12_AB_BRIDGE_SEL );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Turning motor brake on \r\n" );
    hbridge12_turn_brake_on( &hbridge12, HBRIDGE12_AB_BRIDGE_SEL );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Turning motor clockwise \r\n" );
    hbridge12_turn_clockwise( &hbridge12, HBRIDGE12_AB_BRIDGE_SEL );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Motor freewheeling \r\n" );
    hbridge12_freewheeling_on( &hbridge12, HBRIDGE12_AB_BRIDGE_SEL );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
