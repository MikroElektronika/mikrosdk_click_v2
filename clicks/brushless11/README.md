
---
# Brushless 11 Click

> [Brushless 11 Click](https://www.mikroe.com/?pid_product=MIKROE-5865) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5865&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2023.
- **Type**          : PWM type

# Software Support

## Example Description

> This example demonstrates the use of the Brushless 11 Click board by driving the 
  motor at different speeds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless11

### Example Key Functions

- `brushless11_cfg_setup` Config Object Initialization function.
```c
void brushless11_cfg_setup ( brushless11_cfg_t *cfg );
```

- `brushless11_init` Initialization function.
```c
err_t brushless11_init ( brushless11_t *ctx, brushless11_cfg_t *cfg );
```

- `brushless11_default_cfg` Click Default Configuration function.
```c
err_t brushless11_default_cfg ( brushless11_t *ctx );
```

- `brushless11_get_fg1_pin` Brushless 11 get FG1 pin state function.
```c
uint8_t brushless11_get_fg1_pin ( brushless11_t *ctx );
```

- `brushless11_set_brake` Brushless 11 set motor brake state function.
```c
void brushless11_set_brake ( brushless11_t *ctx, uint8_t brake_state );
```

- `brushless11_set_speed` Brushless 11 set motor speed.
```c
err_t brushless11_set_speed ( brushless11_t *ctx, uint8_t speed );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless11_cfg_t brushless11_cfg;  /**< Click config object. */

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
    brushless11_cfg_setup( &brushless11_cfg );
    BRUSHLESS11_MAP_MIKROBUS( brushless11_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == brushless11_init( &brushless11, &brushless11_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS11_ERROR == brushless11_default_cfg ( &brushless11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Controls the motor speed by changing the PWM duty cycle every second.
  The duty cycle ranges from 10% to 100%.
  Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void ) 
{
    log_printf( &logger, " Motor brake is off \r\n" );
    brushless11_set_brake( &brushless11, BRUSHLESS11_BRAKE_OFF );
    for ( uint8_t speed_cnt = 10; speed_cnt <= 100; speed_cnt += 10 )
    {
        brushless11_set_speed( &brushless11, speed_cnt );
        log_printf( &logger, " Speed is: %d%% \r\n", ( uint16_t ) speed_cnt );
        Delay_ms ( 1000 );
    }
    log_printf( &logger, " Motor brake is on \r\n" );
    brushless11_set_brake( &brushless11, BRUSHLESS11_BRAKE_ON );
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
