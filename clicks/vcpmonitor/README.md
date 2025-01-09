
---
# VCP Monitor Click

> [VCP Monitor Click](https://www.mikroe.com/?pid_product=MIKROE-4039) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4039&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> The VCP Monitor Click is add-on board power monitor system. This Click board is 
> based on precision digital current and power monitor with low-drift, integrated 
> precision shunt resistor. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.VCPmonitor

### Example Key Functions

- `vcpmonitor_cfg_setup` Config Object Initialization function. 
```c
void vcpmonitor_cfg_setup ( vcpmonitor_cfg_t *cfg );
``` 
 
- `vcpmonitor_init` Initialization function. 
```c
err_t vcpmonitor_init ( vcpmonitor_t *ctx, vcpmonitor_cfg_t *cfg );
```

- `vcpmonitor_default_cfg` Click Default Configuration function. 
```c
void vcpmonitor_default_cfg ( vcpmonitor_t *ctx );
```

- `vcpmonitor_get_current` This function reads current data in mA. 
```c
float vcpmonitor_get_current ( vcpmonitor_t *ctx );
```
 
- `vcpmonitor_get_power` This function reads power data in mW. 
```c
float vcpmonitor_get_power ( vcpmonitor_t *ctx );
```

- `vcpmonitor_get_voltage` This function reads voltage data in mV. 
```c
float vcpmonitor_get_voltage ( vcpmonitor_t *ctx );
```

### Application Init

> Initiaizes the driver, and checks the communication by reading the device and manufacture IDs.
> After that, performs the device default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    vcpmonitor_cfg_t cfg;

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
    
    vcpmonitor_cfg_setup( &cfg );
    VCPMONITOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vcpmonitor_init( &vcpmonitor, &cfg );
    
    if ( VCPMONITOR_OK == vcpmonitor_get_id_value( &vcpmonitor, &manufacture_id, &did_id ) )
    {
        log_printf( &logger, ">> Manufacture ID: 0x%.4X\r\n", manufacture_id );
        log_printf( &logger, ">> Device ID: 0x%.4X\r\n", did_id );
    }
    else
    {
        log_error( &logger, " WRONG ID READ! " );
        log_printf( &logger, "Please restart your system.\r\n" );
        for ( ; ; );
    }
    
    vcpmonitor_default_cfg(&vcpmonitor );
    Delay_ms ( 500 );
}
```

### Application Task

> Displays the voltage, current, and power measured by the sensor on the USB UART every 2 seconds.

```c
void application_task ( void )
{
    float current_data;
    float voltage_data;
    float power_data;
    
    current_data = vcpmonitor_get_current( &vcpmonitor );
    log_printf( &logger, ">> Current : %.2f mA\r\n", current_data );
     
    voltage_data = vcpmonitor_get_voltage( &vcpmonitor );
    log_printf( &logger, ">> Voltage : %.2f mV\r\n", voltage_data );
    
    power_data = vcpmonitor_get_power( &vcpmonitor );
    log_printf( &logger, ">> Power : %.2f mW\r\n", power_data );
    
    log_printf( &logger, "-------------------------------\r\n" );
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
