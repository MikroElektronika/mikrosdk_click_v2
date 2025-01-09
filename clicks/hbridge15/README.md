
---
# H-Bridge 15 Click

> [H-Bridge 15 Click](https://www.mikroe.com/?pid_product=MIKROE-5913) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5913&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the H-Bridge 15 Click board by
  driving the motor in both directions with braking and freewheeling. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge15

### Example Key Functions

- `hbridge15_cfg_setup` Config Object Initialization function.
```c
void hbridge15_cfg_setup ( hbridge15_cfg_t *cfg );
```

- `hbridge15_init` Initialization function.
```c
err_t hbridge15_init ( hbridge15_t *ctx, hbridge15_cfg_t *cfg );
```

- `hbridge15_default_cfg` Click Default Configuration function.
```c
err_t hbridge15_default_cfg ( hbridge15_t *ctx );
```

- `hbridge15_set_pins` H-Bridge 15 set pins function.
```c
err_t hbridge15_set_pins ( hbridge15_t *ctx, uint8_t set_mask, uint8_t clr_mask );
```

- `hbridge15_set_sleep` H-Bridge 15 set sleep function.
```c
err_t hbridge15_set_sleep ( hbridge15_t *ctx, uint8_t sleep_state );
```

- `hbridge15_set_out_state` H-Bridge 15 set output function.
```c
err_t hbridge15_set_out_state ( hbridge15_t *ctx, uint8_t out_state );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge15_cfg_t hbridge15_cfg;  /**< Click config object. */

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
    hbridge15_cfg_setup( &hbridge15_cfg );
    HBRIDGE15_MAP_MIKROBUS( hbridge15_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hbridge15_init( &hbridge15, &hbridge15_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HBRIDGE15_ERROR == hbridge15_default_cfg ( &hbridge15 ) )
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
    hbridge15_set_out_state( &hbridge15, HBRIDGE15_DRIVE_MOTOR_FORWARD );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Motor brake is on \r\n" );
    hbridge15_set_out_state( &hbridge15, HBRIDGE15_DRIVE_MOTOR_BRAKE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Motor in reverse mode. \r\n" );
    hbridge15_set_out_state( &hbridge15, HBRIDGE15_DRIVE_MOTOR_REVERSE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Motor is coasting \r\n" );
    hbridge15_set_out_state( &hbridge15, HBRIDGE15_DRIVE_MOTOR_FREEWHEEL );
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
