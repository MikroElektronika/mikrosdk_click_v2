
---
# Charger 3 Click

> [Charger 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4449) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4449&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Nikolic
- **Date**          : nov 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the utilization of Charger 3 Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger3

### Example Key Functions

- `charger3_cfg_setup` Config Object Initialization function.
```c
void charger3_cfg_setup ( charger3_cfg_t *cfg );
```

- `charger3_init` Initialization function.
```c
err_t charger3_init ( charger3_t *ctx, charger3_cfg_t *cfg );
```

- `charger3_default_cfg` Click Default Configuration function.
```c
void charger3_default_cfg ( charger3_t *ctx );
```

- `charger3_enable_write` Charger 3 enable write function.
```c
void charger3_enable_write ( charger3_t *ctx );
```

- `charger3_set_current` Charger 3 set current function.
```c
uint8_t charger3_set_current ( charger3_t *ctx, float curr_value );
```

- `charger3_calc_digipot_res` Charger 3 calculate digipot resistance function.
```c
float charger3_calc_digipot_res ( charger3_t *ctx );
```

### Application Init

> The application init sets up the UART LOG and I2C communication
drivers. The default configuration disables write protection
and sets the operation mode to charging.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger3_cfg_t charger3_cfg;  /**< Click config object. */

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

    charger3_cfg_setup( &charger3_cfg );
    CHARGER3_MAP_MIKROBUS( charger3_cfg, MIKROBUS_1 );
    err_t init_flag = charger3_init( &charger3, &charger3_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    Delay_ms ( 100 );
    charger3_default_cfg ( &charger3 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ------------------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> Task consists of two operations. First, the desired battery
charging current is set by the user. Since setting the current
doesn't implicitly reveals the resistance, the value
of AD5175 digipot is directly read from the RDAC register,
calculated and displayed on the uart log.

```c
void application_task ( void ) 
{
    float result;
    
    charger3_set_current( &charger3, 0.4 );
    Delay_ms ( 1000 );
    result = charger3_calc_digipot_res( &charger3 );
    log_printf( &logger, " Digipot res value: %.2f ohm\r\n", result );
    log_printf( &logger, " ------------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

While the resistance of the AD5175 can be directly set and read,
the total resistance value on the PROG pin should be accounted for
( this means an additional 1kohm in series ) setting of the
battery charging current.

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
