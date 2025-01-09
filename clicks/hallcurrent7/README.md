
---
# Hall Current 7 Click

> [Hall Current 7 Click](https://www.mikroe.com/?pid_product=MIKROE-4420) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4420&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example shows the capabilities of the Hall Current 7 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent7

### Example Key Functions

- `hallcurrent7_cfg_setup` Config Object Initialization function.
```c
void hallcurrent7_cfg_setup ( hallcurrent7_cfg_t *cfg );
```

- `hallcurrent7_init` Initialization function.
```c
err_t hallcurrent7_init ( hallcurrent7_t *ctx, hallcurrent7_cfg_t *cfg );
```

- `hallcurrent7_read_voltage` Read voltage function.
```c
uint16_t hallcurrent7_read_voltage ( hallcurrent7_t *ctx, uint16_t v_ref );
```

- `hallcurrent7_calc_current` Calculate current function.
```c
int16_t hallcurrent7_calc_current ( hallcurrent7_t *ctx, uint16_t v_ref );
```

- `hallcurrent7_avg_current` Calculate Average current function.
```c
int16_t hallcurrent7_avg_current ( hallcurrent7_t *ctx, uint16_t v_ref );
```

### Application Init

> Initalizes I2C driver and makes an initial log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallcurrent7_cfg_t hallcurrent7_cfg;  /**< Click config object. */

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
    hallcurrent7_cfg_setup( &hallcurrent7_cfg );
    HALLCURRENT7_MAP_MIKROBUS( hallcurrent7_cfg, MIKROBUS_1 );
    err_t init_flag = hallcurrent7_init( &hallcurrent7, &hallcurrent7_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Measuring current passing through the on board Hall Effect Sensor and displaying data every two seconds.

```c
void application_task ( void ) 
{
    current = hallcurrent7_avg_current( &hallcurrent7, HALLCURRENT7_VREF_5000_mV );
    log_printf( &logger, "Current: %d mA\r\n", current );

    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> In order to get correct calculations user should change "v_ref" value to his own power supply voltage.

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
