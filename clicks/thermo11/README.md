
---
# Thermo 11 Click

> [Thermo 11 Click](https://www.mikroe.com/?pid_product=MIKROE-3600) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3600&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> The application measures temperature 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo11

### Example Key Functions

- `thermo11_cfg_setup` Config Object Initialization function. 
```c
void thermo11_cfg_setup ( thermo11_cfg_t *cfg );
``` 
 
- `thermo11_init` Initialization function. 
```c
err_t thermo11_init ( thermo11_t *ctx, thermo11_cfg_t *cfg );
```

- `thermo11_default_cfg` Click Default Configuration function. 
```c
void thermo11_default_cfg ( thermo11_t *ctx );
```

- `thermo11_get_temp` Temperature Get function. 
```c
float thermo11_get_temp ( thermo11_t *ctx, uint8_t temp_addr );
```
 
- `thermo11_sw_reset` Software Reset Command. 
```c
void thermo11_sw_reset ( thermo11_t *ctx );
```

- Temperature Set function
err_t thermo11_set_temp ( thermo11_t *ctx, uint8_t temp_addr, float temp_value );

### Application Init

> Initializes I2C serial interface and performs a software reset command

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo11_cfg_t cfg;

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

    thermo11_cfg_setup( &cfg );
    THERMO11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo11_init( &thermo11, &cfg );

    thermo11_sw_reset( &thermo11 );

    thermo11_default_cfg( &thermo11 );
    
    log_printf( &logger, "** Thermo 11 is initialized ** \r\n" );
    log_printf( &logger, "************************************************ \r\n \r\n" );
    
    Delay_ms ( 500 );
}
```

### Application Task

> Waits until data was ready and conversion cycle was done, and then reads 

```c
void application_task ( void )
{
    uint8_t response_check;
    float temperature;
    
    response_check = thermo11_get_int(  &thermo11 );
    while ( response_check == THERMO11_FLAG_IS_CLEARED )
    {
        response_check = thermo11_get_int( &thermo11 );
    }

    temperature = thermo11_get_temp(  &thermo11, THERMO11_TEMPERATURE_REG );
    response_check = thermo11_check_status( &thermo11 );
    
    log_printf( &logger, "*Temperature is: %.2f \r\n", temperature );

    
    if ( ( response_check & THERMO11_HIGH_ALERT_FLAG ) != THERMO11_FLAG_IS_CLEARED )
    {
        log_printf( &logger, "*HIGH limit detection! \r\n" );
    }
    if ( ( response_check & THERMO11_LOW_ALERT_FLAG ) != THERMO11_FLAG_IS_CLEARED )
    {
         log_printf( &logger, "*LOW limit detection! \r\n" );
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
