
---
# eFuse Click

> [eFuse Click](https://www.mikroe.com/?pid_product=MIKROE-4726) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4726&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jun 2021.
- **Type**          : GPIO type

# Software Support

## Example Description

> This library contains API for the eFuse Click driver.
> This demo application shows use of a eFuse Click board&trade;.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.eFuse

### Example Key Functions

- `efuse_cfg_setup` Config Object Initialization function.
```c
void efuse_cfg_setup ( efuse_cfg_t *cfg );
```

- `efuse_init` Initialization function.
```c
err_t efuse_init ( efuse_t *ctx, efuse_cfg_t *cfg );
```

- `efuse_default_cfg` Click Default Configuration function.
```c
void efuse_default_cfg ( efuse_t *ctx );
```

- `efuse_enable_device` eFuse enable the device function.
```c
void efuse_enable_device ( efuse_t *ctx );
```

- `efuse_disable_device` eFuse disable the device function.
```c
void efuse_disable_device ( efuse_t *ctx );
```

- `efuse_disable_pwm` eFuse disable the device function.
```c
void efuse_disable_pwm ( efuse_t *ctx);
```

### Application Init

> Initialization of GPIO module and log UART.
> After driver initialization the app set default settings.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    efuse_cfg_t efuse_cfg;  /**< Click config object. */

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

    efuse_cfg_setup( &efuse_cfg );
    EFUSE_MAP_MIKROBUS( efuse_cfg, MIKROBUS_1 );
    if ( efuse_init( &efuse, &efuse_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    efuse_default_cfg ( &efuse );
    Delay_ms ( 100 );
    
    log_printf( &logger, " Disable PWM \r\n" );
    efuse_disable_pwm( &efuse );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that shows the use of an eFuse Click board&trade;.
> The Electronic Fuse is an electrical safety device that operates to 
> provide overcurrent protection of an electrical circuit.
> The intervention threshold is programmed by the Rs resistor.
> The device disconnects the load if the power overcomes the pre-set threshold, 
> for example, if Vset = 3.9 kOhm, Vin = 12 V, 
> the intervention threshold is set approximately to 875 mA.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "\t Active \r\n" );
    efuse_enable_device( &efuse );
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
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "\tInactive \r\n" );
    efuse_disable_device( &efuse );
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
}
```

### Note

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
