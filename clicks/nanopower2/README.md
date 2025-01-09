
---
# Nano Power 2 Click

> [Nano Power 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3036) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3036&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Petar Suknjaja
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example logs the comparators output value.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NanoPower2

### Example Key Functions

- `nanopower2_cfg_setup` Config Object Initialization function.
```c
void nanopower2_cfg_setup ( nanopower2_cfg_t *cfg ); 
```

- `nanopower2_init` Initialization function.
```c
err_t nanopower2_init ( nanopower2_t *ctx, nanopower2_cfg_t *cfg );
```

- `nanopower2_check_output` Function gets output voltage from comparator.
```c
uint8_t nanopower2_check_output ( nanopower2_t *ctx );
``` 

### Application Init

> Initializes GPIO driver.

```c
void application_init ( void )
{
	  log_cfg_t log_cfg;
    nanopower2_cfg_t cfg;

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
    nanopower2_cfg_setup( &cfg );
    NANOPOWER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    nanopower2_init( &nanopower2, &cfg );

    log_printf( &logger, "NANO POWER 2 is initialized\r\n" );
    out_check_prev = 2;
}
```

### Application Task

> Checks the comparator's output and logs output value on USBUART.

```c
void application_task ( void )
{
    out_check = nanopower2_check_output( &nanopower2 );
    if ( out_check != out_check_prev )
    {
        log_printf( &logger, "OUT is: %d\r\n", ( uint16_t ) out_check );

        out_check_prev = out_check;
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
