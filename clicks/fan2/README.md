
---
# Fan 2 Click

> [Fan 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2708) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2708&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nemanja Medakovic
- **Date**          : Nov 2019.
- **Type**          : I2C type

# Software Support

## Example Description

>
> This example demonstrates the use of Fan 2 Click board.
> It demonstrates sensor measurements and fan control.
>

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Fan2

### Example Key Functions

- `fan2_cfg_setup` Configuration Object Initialization function. 
```c
void fan2_cfg_setup ( fan2_cfg_t *cfg );
```
 
- `fan2_init` Click Initialization function. 
```c
fan2_err_t fan2_init ( fan2_t *ctx, fan2_cfg_t *cfg );
```

- `fan2_default_cfg` Click Default Configuration function. 
```c
void fan2_default_cfg ( fan2_t *ctx, fan2_wire_t n_wires );
```

- `fan2_generic_write_byte` Generic Byte Write function. 
```c
fan2_err_t fan2_generic_write_byte ( fan2_t *ctx, uint8_t reg_addr, uint8_t data_in );
```
 
- `fan2_read_tacho` Tachometer Read function. 
```c
fan2_err_t fan2_read_tacho ( fan2_t *ctx, uint8_t tacho_addr, uint32_t *tacho_rpm );
```

- `fan2_direct_speed_control` Direct Fan Speed Control function. 
```c
fan2_err_t fan2_direct_speed_control ( fan2_t *ctx, float speed_per );
```

### Application Init

>
> Initializes I2C driver and executes a default configuration for Fan 2 Click.
> Also initializes UART logger for results logging.
>

```c
void application_init( void )
{
    fan2_cfg_t fan2_cfg;
    log_cfg_t log_cfg;

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
    fan2_cfg_setup( &fan2_cfg );
    FAN2_MAP_MIKROBUS( fan2_cfg, MIKROBUS_1 );
    fan2_init( &fan2, &fan2_cfg );
    
    fan2_default_cfg( &fan2 );
    fan2_speed = FAN2_HALF_SPEED_PER;
    Delay_ms ( 1000 );

    log_printf( &logger, "* * *  Fan 2 initialization done  * * *\r\n" );
    log_printf( &logger, "***************************************\r\n" );
    flag = 0;
}
```

### Application Task

>
> Increments the fan speed from half speed to maximum, and on each step measures
> the current fan speed in RPM and the remote temperature in Celsius.
> Fan speed will be incremented/decremented each second for 10 percents.
>

```c
void application_task( void )
{
    fan2_direct_speed_control( &fan2, fan2_speed );

    Delay_ms ( 1000 );
    fan2_read_tacho( &fan2, FAN2_REG_TACH1_CNT, &fan2_curr_speed );
    
    fan2_read_temp( &fan2, FAN2_REG_REMOTE_TEMP_READ, &fan2_temp );

    log_printf( &logger, "* Fan 2 set speed : %.2f %%\r\n", fan2_speed );
    log_printf( &logger, "* Fan 2 current speed : %u RPM\r\n", fan2_curr_speed );
    log_printf( &logger, "* Fan 2 remote temperature : %.2f %s\r\n", fan2_temp, deg_cels );
    log_printf( &logger, "***************************************\r\n" );
    
    if ( flag == 0 ) {
        if ( fan2_speed < FAN2_MAX_SPEED_PER)
            fan2_speed += 10;
        else
            flag = 1;
    }
    
    if ( flag == 1 ) {
        if ( fan2_speed > FAN2_MIN_SPEED_PER)
            fan2_speed -= 10;
        else {
            fan2_speed = FAN2_HALF_SPEED_PER;
            flag = 0;
        }
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
