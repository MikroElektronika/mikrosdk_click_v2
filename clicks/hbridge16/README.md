
---
# H-Bridge 16 Click

> [H-Bridge 16 Click](https://www.mikroe.com/?pid_product=MIKROE-5926) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5926&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the H-Bridge 16 Click board by
  driving the motor in both directions with braking and freewheeling.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge16

### Example Key Functions

- `hbridge16_cfg_setup` Config Object Initialization function.
```c
void hbridge16_cfg_setup ( hbridge16_cfg_t *cfg );
```

- `hbridge16_init` Initialization function.
```c
err_t hbridge16_init ( hbridge16_t *ctx, hbridge16_cfg_t *cfg );
```

- `hbridge16_default_cfg` Click Default Configuration function.
```c
err_t hbridge16_default_cfg ( hbridge16_t *ctx );
```

- `hbridge16_set_pins` H-Bridge 16 set pins function.
```c
err_t hbridge16_set_pins ( hbridge16_t *ctx, uint8_t set_mask, uint8_t clr_mask );
```

- `hbridge16_set_mode` H-Bridge 16 set mode function.
```c
err_t hbridge16_set_mode ( hbridge16_t *ctx, uint8_t mode_sel );
```

- `hbridge16_set_out_state` H-Bridge 16 set output function.
```c
err_t hbridge16_set_out_state ( hbridge16_t *ctx, uint8_t out_state );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge16_cfg_t hbridge16_cfg;  /**< Click config object. */

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
    hbridge16_cfg_setup( &hbridge16_cfg );
    HBRIDGE16_MAP_MIKROBUS( hbridge16_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hbridge16_init( &hbridge16, &hbridge16_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HBRIDGE16_ERROR == hbridge16_default_cfg ( &hbridge16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example is driving a motor in both directions with 
  motor braking and freewheeling in between.

```c
void application_task ( void ) 
{
    log_printf( &logger, " Motor in forward mode. \r\n" );
    hbridge16_set_out_state( &hbridge16, HBRIDGE16_DRIVE_MOTOR_FORWARD );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Motor brake is on \r\n" );
    hbridge16_set_out_state( &hbridge16, HBRIDGE16_DRIVE_MOTOR_BRAKE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Motor in reverse mode. \r\n" );
    hbridge16_set_out_state( &hbridge16, HBRIDGE16_DRIVE_MOTOR_REVERSE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Motor is coasting \r\n" );
    hbridge16_set_out_state( &hbridge16, HBRIDGE16_DRIVE_MOTOR_FREEWHEEL );
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
