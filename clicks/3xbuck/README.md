
---
# 3 x Buck Click

> [3 x Buck Click](https://www.mikroe.com/?pid_product=MIKROE-3201) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3201&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Petar Suknjaja
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the 3 x Buck Click Board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.3xBuck

### Example Key Functions

- `c3xbuck_cfg_setup` Config Object Initialization function. 
```c
void c3xbuck_cfg_setup ( c3xbuck_cfg_t *cfg );
``` 
 
- `c3xbuck_init` Initialization function. 
```c
err_t c3xbuck_init ( c3xbuck_t *ctx, c3xbuck_cfg_t *cfg );
```

- `c3xbuck_default_cfg` Click Default Configuration function. 
```c
void c3xbuck_default_cfg ( c3xbuck_t *ctx );
```

- `c3xbuck_enable_buck` This function enables desired Buck on the Click. 
```c
void c3xbuck_enable_buck ( c3xbuck_t *ctx, uint8_t buck );
```
 
- `c3xbuck_disable_buck` This function disables desired Buck on the Click. 
```c
void c3xbuck_disable_buck ( c3xbuck_t *ctx, uint8_t buck );
```

- `c3xbuck_set_voltage` This function sets voltage on desired Buck. 
```c
void c3xbuck_set_voltage ( c3xbuck_t *ctx, uint8_t buck, uint8_t voltage );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c3xbuck_cfg_t cfg;

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

    c3xbuck_cfg_setup( &cfg );
    C3XBUCK_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3xbuck_init( &c3xbuck, &cfg );
    Delay_ms ( 100 );
    
    c3xbuck_default_cfg ( &c3xbuck );
    log_info( &logger, "---- Application Task ----" );
}
```

### Application Task

> Alternates between predefined and default values for the Bucks output and logs the current set values on the USB UART.

```c
void application_task ( void )
{
    //  Task implementation.
    log_printf( &logger, "Setting predefined values : \r\n" );
    log_printf( &logger, "Buck 1 : 1000 mV\r\n");
    log_printf( &logger, "Buck 2 : 1250 mV\r\n");
    log_printf( &logger, "Buck 3 : 1500 mV\r\n");
    
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_1, C3XBUCK_OUTPUT_VOLTAGE_1000mV );
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_2, C3XBUCK_OUTPUT_VOLTAGE_1250mV );
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_3, C3XBUCK_OUTPUT_VOLTAGE_1500mV );
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "Setting default values: \r\n");
    log_printf( &logger, "Buck 1 : 1800 mV\r\n");
    log_printf( &logger, "Buck 2 : 3300 mV\r\n");
    log_printf( &logger, "Buck 3 : 5000 mV\r\n");
    
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_1, C3XBUCK_BUCK_DEFAULT_OUTPUT_VOLTAGE );
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_2, C3XBUCK_BUCK_DEFAULT_OUTPUT_VOLTAGE );
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_3, C3XBUCK_BUCK_DEFAULT_OUTPUT_VOLTAGE );
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> The default output voltage on Buck 1 is 1800mV, Buck 2 is 3300mV, and Buck 3 is 5000mV.
> Configurable output voltage on all Bucks ranges from 680mV to 1950mV.

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
