
---
# Smoke Click

> [Smoke Click](https://www.mikroe.com/?pid_product=MIKROE-2560) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2560&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type

# Software Support

## Example Description

>  This Click includes internal LEDs, photodetectors, optical elements, and low-noise electronics 
> with ambient light rejection. The sensor can detect a wide variety of smoke particle sizes. 
> It also has an on-chip temperature sensor for calibrating the temperature dependence of the 
> particle sensing subsystem. The temperature sensor has an inherent resolution 0.0625°C.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Smoke

### Example Key Functions

- `smoke_cfg_setup` Config Object Initialization function. 
```c
void smoke_cfg_setup ( smoke_cfg_t *cfg );
``` 
 
- `smoke_init` Initialization function. 
```c
err_t smoke_init ( smoke_t *ctx, smoke_cfg_t *cfg );
```

- `smoke_default_cfg` Click Default Configuration function. 
```c
void smoke_default_cfg ( smoke_t *ctx );
```

- `smoke_set_registers` Set registers values function. 
```c
uint8_t smoke_set_registers ( smoke_t *ctx, smoke_set_registers_t *registers );
```

- `smoke_enable_disable_interrupts` Enable or disable interrupt function. 
```c
uint8_t smoke_enable_disable_interrupts ( smoke_t *ctx, uint8_t interrupt_flag, uint8_t enable_flag );
```
 
- `smoke_read_leds` Function for reading enabled led values. 
```c
uint8_t smoke_read_leds ( smoke_t *ctx );
```

### Application Init

> Initalizes I2C driver, and sets default configuration of         device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    smoke_cfg_t cfg;

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

    smoke_cfg_setup( &cfg );
    SMOKE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    smoke_init( &smoke, &cfg );

    smoke_reset( &smoke );
    smoke_default_cfg ( &smoke );

    log_info( &logger, "---- Application Task ----" );
    Delay_ms ( 100 );
    if ( smoke_read_leds( &smoke ) != SMOKE_OK )
    {
        log_info( &logger, "---- Init Error ----" );
        for( ; ; );
    }
}
```

### Application Task

> This example demonstrates the use of Smoke Click board. It reads reflected red, ir,
    green and temperature values from an internal sensor and displays and logs it.

```c
void application_task ( void )
{
    smoke_read_leds( &smoke );
    
    log_printf( &logger, "Red : %llu\r\n", smoke.red_value );
    log_printf( &logger, "IR : %llu\r\n", smoke.ir_value );
    log_printf( &logger, "Green : %llu\r\n", smoke.green_value );
    log_printf( &logger, "------------------------------\r\n" );
    
    temperature = smoke_read_temp( &smoke );
    
    log_printf( &logger, "Read Temperature[ degC ]: %.2f\r\n",  temperature );
    log_printf( &logger, "------------------------------\r\n" );

    Delay_ms ( 500 );
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
