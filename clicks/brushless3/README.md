
---
# Brushless 3 Click

> [Brushless 3 Click](https://www.mikroe.com/?pid_product=MIKROE-2766) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2766&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This Click has three-phase sensorless motor driver and with an external power supply it drives a brushless DC motor. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless3

### Example Key Functions

- `brushless3_cfg_setup` Config Object Initialization function.
```c
void brushless3_cfg_setup ( brushless3_cfg_t *cfg );
```

- `brushless3_init` Initialization function.
```c
err_t brushless3_init ( brushless3_t *ctx, brushless3_cfg_t *cfg );
```

- `brushless3_default_cfg` Click Default Configuration function.
```c
err_t brushless3_default_cfg ( brushless3_t *ctx );
```

- `brushless3_set_speed` Set speed function
```c
err_t brushless3_set_speed ( brushless3_t *ctx, uint16_t motor_speed_hz );
```

- `brushless3_get_speed` Get speed function
```c
err_t brushless3_get_speed ( brushless3_t *ctx, float *speed );
```

- `brushless3_forward_direction` Set the direction of rotation in the forward direction function
```c
void brushless3_forward_direction ( brushless3_t *ctx );
```

### Application Init

> Initialization driver enable's - I2C, set default parameter value.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    brushless3_cfg_t cfg;

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

    //  Click initialization.
    brushless3_cfg_setup( &cfg );
    BRUSHLESS3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    brushless3_init( &brushless3, &cfg );
    
    if ( BRUSHLESS3_ERROR == brushless3_default_cfg ( &brushless3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
}
```

### Application Task

> This is an example which demonstrates the use of Brushless 3 Click board.
> Read and display float motor frequency value from the DRV10983 sensorless 
> BLDC motor driver on Brushless 3 Click board. Results are being sent to 
> the Usart Terminal where you can track their changes. 

```c
void application_task ( void )
{
    log_printf( &logger, "    acceleration      \r\n" );
    
    for ( speed = 100; speed <= BRUSHLESS3_MAX_SPEED; speed += 20 )
    {
        brushless3_set_speed( &brushless3, speed );
        brushless3_get_speed( &brushless3, &velocity );
        log_printf( &logger, " Motor frequency: %.2f Hz\r\n", velocity );
        Delay_ms ( 100 );
    }

    log_printf( &logger,  "\r\n ---------------------- \r\n" ); 
    log_printf( &logger, "    slowing down     \r\n" );
    
    for ( speed = BRUSHLESS3_MAX_SPEED; speed >= 50; speed -= 20 )
    {
        brushless3_set_speed( &brushless3, speed );
        brushless3_get_speed( &brushless3, &velocity );
        log_printf( &logger, " Motor frequency: %.2f Hz\r\n", velocity );
        Delay_ms ( 100 );
    }
    
    log_printf( &logger, "-----------------------\r\n" );
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
