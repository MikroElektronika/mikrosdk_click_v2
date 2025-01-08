
---
# MAGNETO Click

> [MAGNETO Click](https://www.mikroe.com/?pid_product=MIKROE-1886) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1886&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> 
> Example presents precise angle measurements down to 0.05º in 14-bit resolution.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneto

### Example Key Functions

- `magneto_cfg_setup` Config Object Initialization function. 
```c
void magneto_cfg_setup ( magneto_cfg_t *cfg );
``` 
 
- `magneto_init` Initialization function. 
```c
err_t magneto_init ( magneto_t *ctx, magneto_cfg_t *cfg );
```

- `magneto_default_cfg` Click Default Configuration function. 
```c
void magneto_default_cfg ( magneto_t *ctx );
```

- `magneto_get_state` This function read and returns the value of the state register. 
```c
uint16_t magneto_get_state ( magneto_t *ctx );
```
 
- `magneto_calculate_angle` This function read the 16-bit data from register then calculate and convert to float angle value from 0deg to 360deg. 
```c
float magneto_calculate_angle ( magneto_t *ctx );
```

### Application Init

>
> Application Init performs Logger and Click initialization.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    magneto_cfg_t cfg;

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
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "     Application  Init\r\n" );
    Delay_ms ( 100 );

    //  Click initialization.

    magneto_cfg_setup( &cfg );
    MAGNETO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    magneto_init( &magneto, &cfg );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " ----- MAGNETO Click ---- \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    
    if ( magneto_get_state( &magneto ) != 1 )
    {
        log_printf( &logger, " -- Initialization done --\r\n" );
    }
    else
    {
        log_printf( &logger, " -------- ERROR ! --------\r\n" );
    }

    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

>
> Magneto Click communicates with register via SPI by write and read from register and calculate float angle value. 
> Results are being sent to the UART Terminal where you can track their changes. 
> All data logs on USB UART for aproximetly every 2 sec.
> 

```c
void application_task ( void )
{
    angle_value = magneto_calculate_angle( &magneto );
    log_printf( &logger, "  [ANGLE] : %0.3f \r\n", angle_value );

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
