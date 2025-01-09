
---
# H-Bridge 4 Click

> [H-Bridge 4 Click](https://www.mikroe.com/?pid_product=MIKROE-3787) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3787&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application is used to turn on DC or Stepper motors.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge4

### Example Key Functions

- `hbridge4_cfg_setup` Config Object Initialization function. 
```c
void hbridge4_cfg_setup ( hbridge4_cfg_t *cfg );
``` 
 
- `hbridge4_init` Initialization function. 
```c
err_t hbridge4_init ( hbridge4_t *ctx, hbridge4_cfg_t *cfg );
```

- `hbridge4_enable` Enable the device function. 
```c
void hbridge4_enable ( hbridge4_t *ctx, uint8_t state );
```
 
- `hbridge4_set_in1` Set IN1 function. 
```c
void hbridge4_set_in1 ( hbridge4_t *ctx, uint8_t state );
```

- `hbridge4_motor_a_standby` Motor A standby function. 
```c
void hbridge4_motor_a_standby ( hbridge4_t *ctx );
```

### Application Init

> Initialization driver enables GPIO and also starts write log. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    hbridge4_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    hbridge4_cfg_setup( &cfg );
    HBRIDGE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hbridge4_init( &hbridge4, &cfg );

    hbridge4_enable( &hbridge4, 1 );
    Delay_ms ( 100 );
    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, " H-Bridge 4 Click \r\n" );
    log_printf( &logger, "------------------- \r\n" );
}
```

### Application Task

> This example demonstrates the use of H-Bridge 4 Click board by putting A motor
> in standby mode, then spining it in clockwise direction and applying brake function, and then
> spining it in counter-clockwise direction and applying brake function again.

```c
void application_task ( )
{
    log_printf( &logger, "The motor A is in standby mode \r\n" );
    hbridge4_motor_a_standby( &hbridge4 );
    Delay_ms ( 100 );
    log_printf( &logger, "The motor A turns clockwise \r\n" );
    hbridge4_motor_acw( &hbridge4 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "The motor A applies brake \r\n" );
    hbridge4_motor_a_brake( &hbridge4 );
    Delay_ms ( 1000 );
    log_printf( &logger, "The motor A turns counter-clockwise \r\n" );
    hbridge4_motor_accw( &hbridge4 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "The motor A applies brake \r\n" );
    hbridge4_motor_a_brake( &hbridge4 );
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
