
---
# Hall Current 2 Click

> [Hall Current 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2987) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2987&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application very accurately measures current using Hall effect.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent2

### Example Key Functions

- `hallcurrent2_cfg_setup` Config Object Initialization function. 
```c
void hallcurrent2_cfg_setup ( hallcurrent2_cfg_t *cfg );
``` 
 
- `hallcurrent2_init` Initialization function. 
```c
err_t hallcurrent2_init ( hallcurrent2_t *ctx, hallcurrent2_cfg_t *cfg );
```

- `hallcurrent2_default_cfg` Click Default Configuration function. 
```c
void hallcurrent2_default_cfg ( hallcurrent2_t *ctx );
```

- `hallcurrent2_generic_read` This function reads data from the desired register. 
```c
void hallcurrent2_generic_read ( hallcurrent2_t *ctx );
```
 
- `hallcurrent2_reset` This function changes reset chip states to reset the chip. 
```c
void hallcurrent2_reset ( hallcurrent2_t *ctx );
```

- `hallcurrent2_get_current` Reads current's value in mV. 
```c
int16_t hallcurrent2_get_current ( hallcurrent2_t *ctx );
```

### Application Init

> Initializes Driver init and reset chip

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    hallcurrent2_cfg_t cfg;

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

    hallcurrent2_cfg_setup( &cfg );
    HALLCURRENT2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hallcurrent2_init( &hallcurrent2, &cfg );

    hallcurrent2_reset( &hallcurrent2 );
}
```

### Application Task

> Reads current and logs on usbuart every 1 second.

```c
void application_task ( void )
{
    int16_t current_data;

    current_data = hallcurrent2_get_current( &hallcurrent2 );
    log_printf( &logger, "--- Current : %d mA\r\n", current_data );
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
