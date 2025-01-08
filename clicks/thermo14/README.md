
---
# Thermo 14 Click

> [Thermo 14 Click](https://www.mikroe.com/?pid_product=MIKROE-4132) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4132&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> Thermo 14 Click provides an accuracy of ±0.5°C in the range from -10°C to 60°C.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo14

### Example Key Functions

- `thermo14_cfg_setup` Config Object Initialization function. 
```c
void thermo14_cfg_setup ( thermo14_cfg_t *cfg );
``` 
 
- `thermo14_init` Initialization function. 
```c
err_t thermo14_init ( thermo14_t *ctx, thermo14_cfg_t *cfg );
```

- `thermo14_reset` Reset function. 
```c
void thermo14_reset ( thermo14_t *ctx );
```
 
- `thermo14_sensor_enable` Sensor enable function. 
```c
void thermo14_sensor_enable ( thermo14_t *ctx );
```

- `thermo14_temp_raw_get` Get Raw Temperature Data function. 
```c
int16_t thermo14_temp_raw_get ( thermo14_t *ctx );
```

### Application Init

> Initalizes I2C driver, sets up the device. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo14_cfg_t cfg;
    
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

    thermo14_cfg_setup( &cfg );
    THERMO14_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo14_init( &thermo14, &cfg );

    Delay_ms ( 100 );
    thermo14_default_cfg( &thermo14 );
}
```

### Application Task

> This example shows capabilities of Thermo 14 Click by measuring
   temperature every 3 seconds and displaying temperature in degrres Celsius via USART terminal. 

```c
void application_task ( void )
{
    temp_val = thermo14_get_temperature( &thermo14 );

    log_printf( &logger, " Temperature: %.2f C \r\n ", temp_val );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```## Application Output

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
