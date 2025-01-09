
---
# Charger 17 Click

> [Charger 17 Click](https://www.mikroe.com/?pid_product=MIKROE-4823) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4823&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Charger 17 Click board by enabling battery charging and displaying the charging status.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger17

### Example Key Functions

- `charger17_cfg_setup` Config Object Initialization function.
```c
void charger17_cfg_setup ( charger17_cfg_t *cfg );
```

- `charger17_init` Initialization function.
```c
err_t charger17_init ( charger17_t *ctx, charger17_cfg_t *cfg );
```

- `charger17_default_cfg` Click Default Configuration function.
```c
err_t charger17_default_cfg ( charger17_t *ctx );
```

- `charger17_enable_charging` This function enables charging by setting the CE pin to low logic state.
```c
void charger17_enable_charging ( charger17_t *ctx );
```

- `charger17_set_psel_2400mA` This function sets charging current to 2400mA by setting the PSEL pin to low logic state.
```c
void charger17_set_psel_2400mA ( charger17_t *ctx );
```

- `charger17_read_register` This function reads data from the selected register by using I2C serial interface.
```c
err_t charger17_read_register ( charger17_t *ctx, uint8_t reg, uint8_t *data_out );
```

### Application Init

> Initializes the driver and performs the Click default configuration which enables charging.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger17_cfg_t charger17_cfg;  /**< Click config object. */

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
    charger17_cfg_setup( &charger17_cfg );
    CHARGER17_MAP_MIKROBUS( charger17_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == charger17_init( &charger17, &charger17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CHARGER17_ERROR == charger17_default_cfg ( &charger17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and displays the battery charging status (IC_STATUS and STAT0 regs) on the USB UART approximately once per second.

```c
void application_task ( void )
{
    uint8_t ic_status, status_0;
    if ( CHARGER17_OK == charger17_read_register ( &charger17, CHARGER17_REG_IC_STATUS, &ic_status ) )
    {
        charger17_parse_ic_status ( ic_status );
    }
    if ( CHARGER17_OK == charger17_read_register ( &charger17, CHARGER17_REG_STAT0, &status_0 ) )
    {
        charger17_parse_status_0 ( status_0 );
    }
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
