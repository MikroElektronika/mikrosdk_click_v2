
---
# POWER BANK Click

> [PowerBank Click](https://www.mikroe.com/?pid_product=MIKROE-4082) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4082&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> 
> This is an example which demonstrates the usage of Power Bank Click board.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PowerBank

### Example Key Functions

- `powerbank_cfg_setup` Config Object Initialization function. 
```c
void powerbank_cfg_setup ( powerbank_cfg_t *cfg );
``` 
 
- `powerbank_init` Initialization function. 
```c
err_t powerbank_init ( powerbank_t *ctx, powerbank_cfg_t *cfg );
```

- `powerbank_read_data` Read data function. 
```c
uint16_t powerbank_read_data ( powerbank_t *ctx );
```
 
- `powerbank_read_voltage` Read voltage function. 
```c
uint16_t powerbank_read_voltage ( powerbank_t *ctx, uint16_t v_ref );
```

### Application Init

> Initalizes I2C driver and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    powerbank_cfg_t cfg;

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

    powerbank_cfg_setup( &cfg );
    POWERBANK_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    powerbank_init( &powerbank, &cfg );

    Delay_ms ( 100 );
    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, "     PowerBank Click    \r\n" );
    log_printf( &logger, "------------------------\r\n" );
}
```

### Application Task

> This example shows the capabilities of the PowerBank Click by measuring voltage of the connected battery. In order to get correct calculations user should change "v_ref" value to his own power supply voltage.

```c
void application_task ( void )
{
    uint16_t voltage;
    uint16_t v_ref = 5075;

    voltage = powerbank_read_voltage( &powerbank, v_ref );
    log_printf( &logger, "Battery voltage: %d mV\r\n", voltage );
    
    log_printf( &logger, "------------------------\r\n" );
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
