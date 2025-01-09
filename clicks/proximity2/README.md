
---
# Proximity 2 Click

> [Proximity 2 Click](https://www.mikroe.com/?pid_product=MIKROE-1818) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1818&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> 
> This is an example that shows the most important
> functions that Proximity 2 Click has.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity2

### Example Key Functions

- `proximity2_cfg_setup` Config Object Initialization function. 
```c
void proximity2_cfg_setup ( proximity2_cfg_t *cfg );
``` 
 
- `proximity2_init` Initialization function. 
```c
err_t proximity2_init ( proximity2_t *ctx, proximity2_cfg_t *cfg );
```

- `proximity2_default_cfg` Click Default Configuration function. 
```c
void proximity2_default_cfg ( proximity2_t *ctx );
```

- `proximity2_read_prox` Read PROX Data Register function. 
```c
uint8_t proximity2_read_prox ( proximity2_t *ctx );
```
 
- `proximity2_read_als` Read ALS Data Registers function. 
```c
uint16_t proximity2_read_als ( proximity2_t *ctx );
```

### Application Init

>
> Configuring Clicks and log objects.
> Setting the Click in the default configuration.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity2_cfg_t cfg;

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
    log_info( &logger, "Application Init" );
    
    //  Click initialization.

    proximity2_cfg_setup( &cfg );
    PROXIMITY2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity2_init( &proximity2, &cfg );
    
    proximity2_default_cfg ( &proximity2 );
    
    log_info( &logger, "Application Init" );
    Delay_ms ( 1000 );
}
```

### Application Task

>
> Shows the most important proximity and ambient value.
> 

```c
void application_task ( void )
{
    proxi_val =  proximity2_read_prox ( &proximity2 );
    ambient = proximity2_read_als ( &proximity2 );

    log_printf( &logger, " Distance : %d \r\n", (uint16_t)proxi_val );
    
    log_printf( &logger, " Light    : %d \r\n", ambient );

    log_printf( &logger, "------------------\r\n" );
    
    Delay_ms ( 300 );
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
