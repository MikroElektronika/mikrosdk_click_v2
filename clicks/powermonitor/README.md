
---
# Power Monitor Click

> [Power Monitor Click](https://www.mikroe.com/?pid_product=MIKROE-4810) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4810&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for Power Monitor Click driver.
> The library initializes and defines the I2C bus drivers 
> to write and read data from registers. 
> The library also includes a function for reading 
> Shunt and Bus voltage ( mV ), Current ( mA ), Power ( W ), Energy ( J ),   
> as well as the Temperature in degrees Celsius.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PowerMonitor

### Example Key Functions

- `powermonitor_cfg_setup` Config Object Initialization function.
```c
void powermonitor_cfg_setup ( powermonitor_cfg_t *cfg );
```

- `powermonitor_init` Initialization function.
```c
err_t powermonitor_init ( powermonitor_t *ctx, powermonitor_cfg_t *cfg );
```

- `powermonitor_default_cfg` Click Default Configuration function.
```c
err_t powermonitor_default_cfg ( powermonitor_t *ctx );
```

- `powermonitor_get_vshunt` Power Monitor get shunt voltage function.
```c
err_t powermonitor_get_vshunt ( powermonitor_t *ctx, float *vshunt );
```

- `powermonitor_get_vbus` Power Monitor get bus voltage function.
```c
err_t powermonitor_get_vbus ( powermonitor_t *ctx, float *vbus );
```

- `powermonitor_get_current` Power Monitor get current function.
```c
err_t powermonitor_get_current ( powermonitor_t *ctx, float *current );
```

### Application Init

> The initialization of I2C  module, log UART, and additional pins. 
> After the driver init and then executes a default configuration, 
> the app checks communication, display Manufacturer, Stores Device and Revision ID. 

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;                    /**< Logger config object. */
    powermonitor_cfg_t powermonitor_cfg;  /**< Click config object. */
    static uint8_t manufacturer_id[ 2 ];
    static uint16_t dieid;
    static uint8_t rev_id;
    
    powermonitor.shunt = 0.28;

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
    powermonitor_cfg_setup( &powermonitor_cfg );
    POWERMONITOR_MAP_MIKROBUS( powermonitor_cfg, MIKROBUS_1 );
    err_t init_flag = powermonitor_init( &powermonitor, &powermonitor_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    powermonitor_default_cfg ( &powermonitor );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms ( 100 );
    
    powermonitor_get_id( &powermonitor, &manufacturer_id, &dieid, &rev_id );
    log_printf( &logger, "  Manufacturer ID  : %.2s\r\n", manufacturer_id );
    log_printf( &logger, "  Stores Device ID : 0x%.3X\r\n", dieid );
    log_printf( &logger, "  Revision ID      : 0x%.1X\r\n", rev_id );
    log_printf( &logger, "----------------------------\r\n" );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that shows the use of a Power Monitor Click board&trade;.
> Measures and displays Shunt voltage ( mV ), Bus voltage ( mV ), 
> Current ( mA ), Power ( W ), Energy ( J ) and Temperature ( degrees Celsius ). 
> Results are being sent to the USART terminal where the user can track their changes. 
> This task repeats every 2.5 sec.

```c
void application_task ( void ) 
{
    static float vshunt, vbus, current, power, energy, temperature;
    
    powermonitor_get_vshunt( &powermonitor, &vshunt );
    log_printf( &logger, " Shunt voltage : %.2f mV\r\n", vshunt );
    Delay_ms ( 100 ); 
    
    powermonitor_get_vbus( &powermonitor, &vbus );
    log_printf( &logger, " BUS voltage   : %.2f mV\r\n", vbus );
    Delay_ms ( 100 );
    
    powermonitor_get_current( &powermonitor, &current );
    log_printf( &logger, " Current       : %.2f mA\r\n", current );
    Delay_ms ( 100 ); 
    
    powermonitor_get_power( &powermonitor, &power );
    log_printf( &logger, " Power         : %.6f W\r\n", power );
    Delay_ms ( 100 ); 
    
    powermonitor_get_energy( &powermonitor, &energy );
    log_printf( &logger, " Energy        : %.6f J\r\n", energy );
    log_printf( &logger, "- - - - - - - - - - - - - - \r\n" );
    Delay_ms ( 100 ); 
    
    powermonitor_get_temperature( &powermonitor, &temperature );
    log_printf( &logger, " Temperature   : %.2f C\r\n", temperature );
    log_printf( &logger, "----------------------------\r\n" );
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
