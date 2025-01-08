
---
# Boost 6 Click

> [Boost 6 Click](https://www.mikroe.com/?pid_product=MIKROE-3813) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3813&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This app enable or disable monolithic high-voltage switching regulator.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Boost6

### Example Key Functions

- `boost6_cfg_setup` Config Object Initialization function. 
```c
void boost6_cfg_setup ( boost6_cfg_t *cfg );
``` 
 
- `boost6_init` Initialization function. 
```c
err_t boost6_init ( boost6_t *ctx, boost6_cfg_t *cfg );
```

- `boost6_default_cfg` Click Default Configuration function. 
```c
void boost6_default_cfg ( boost6_t *ctx );
```

- This function hardware reset the TPS55332-Q1 60-V Output Step Up DC/DC Converter
- on Boost 6 Click by cleared to '0' state of the RST pin,
- `boost6_hw_reset` wait the 100 ms, sets to '1' state of the RST pin and wait another the 100 ms. 
```c
void boost6_hw_reset ( boost6_t *ctx );
```
 
- This function power OFF provides electrical off control of the regulator
- TPS55332-Q1 60-V Output Step Up DC/DC Converter
- `boost6_power_off` on Boost 6 Click by cleared to '0' state of the EN pin. 
```c
void boost6_power_off ( boost6_t *ctx );
```

- This function power ON provides electrical off control of the regulator
- TPS55332-Q1 60-V Output Step Up DC/DC Converter
- `boost6_power_on` on Boost 6 Click by sets to '1' state of the EN pin. 
```c
void boost6_power_on ( boost6_t *ctx );
```

### Application Init

> Initializes device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    boost6_cfg_t cfg;

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

    boost6_cfg_setup( &cfg );
    BOOST6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    boost6_init( &boost6, &cfg );

    log_printf( &logger, "-----------------\r\n" );
    log_printf( &logger, "  Boost 6 Click  \r\n" );
    log_printf( &logger, "-----------------\r\n" );

    log_printf( &logger, "-----------------\r\n" );
    log_printf( &logger, " Hardware  Reset \r\n" );
    log_printf( &logger, "-----------------\r\n" );
    boost6_hw_reset ( &boost6 );
    Delay_100ms( );

    boost6_power_off(  &boost6  );
    log_printf( &logger, "     Disable     \r\n" );
    log_printf( &logger, "-----------------\r\n" );
    Delay_100ms( );
}
```

### Application Task

> This is an example which demonstrates the use of Boost 6 Click board.
> Enable device 5000ms and disable device 5000ms.

```c
void application_task ( void )
{
    boost6_power_on( &boost6 );
    log_printf( &logger, "     Enable      \r\n" );
    log_printf( &logger, "-----------------\r\n" );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    boost6_power_off(  &boost6  );
    log_printf( &logger, "     Disable     \r\n" );
    log_printf( &logger, "-----------------\r\n" );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
