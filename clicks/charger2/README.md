
---
# Charger 2 Click

> [Charger 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3049) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3049&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This app charges the battery.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger2

### Example Key Functions

- `charger2_cfg_setup` Config Object Initialization function. 
```c
void charger2_cfg_setup ( charger2_cfg_t *cfg );
``` 
 
- `charger2_init` Initialization function. 
```c
err_t charger2_init ( charger2_t *ctx, charger2_cfg_t *cfg );
```

- `charger2_default_cfg` Click Default Configuration function. 
```c
void charger2_default_cfg ( charger2_t *ctx );
```

- `charger2_write_reg` This function writes one byte data to the register. 
```c
uint8_t charger2_write_reg ( charger2_t *ctx, uint8_t register_address, uint8_t transfer_data );
```
 
- `charger2_read_data` This function reads the desired data from data registers and converts this data to the appropriate unit. 
```c
uint8_t charger2_read_data ( charger2_t *ctx, uint8_t data_mode, uint32_t *data_out );
```

- `charger2_check_conv_cycle` This function checks is conversion cycle for battery current, or for battery voltage and temperature, finished, and if is not, waits until one of this conversions be finished. 
```c
uint8_t charger2_check_conv_cycle ( charger2_t *ctx, uint8_t conv_mode );
```

### Application Init

> Initializes device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    charger2_cfg_t cfg;

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

    charger2_cfg_setup( &cfg );
    CHARGER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    charger2_init( &charger2, &cfg );

    Delay_ms ( 500 );
    
    charger2_reset( &charger2, CHARGER2_RESET_COUNTER_MODE );
    Delay_ms ( 1000 );
    charger2_write_reg( &charger2, CHARGER2_REG_MODE, CHARGER2_AUTO_DETECT | CHARGER2_14_BITS_RESOLUTION | CHARGER2_OPERATING_MODE );
    log_printf( &logger, "Charger 2 is initialized \r\n" );
    log_printf( &logger, "------------------------------ \r\n" );
    Delay_ms ( 300 );
}
```

### Application Task

> Reads the all necessary information for the battery charging status and logs this results on UART.
> Repeats operation every second.
> The LED diodes are used to indicate the Vcc presence when this voltage is in operating range, and to show the charging status.

```c
void application_task ( void )
{
    charger2_read_data( &charger2, CHARGER2_GAS_GAUGE_CHARGE_DATA, &battery_data );
    results_logger( &charger2 );
    charger2_read_data( &charger2, CHARGER2_CONV_NUMBER, &battery_data );
    results_logger( &charger2 );
    charger2_read_data( &charger2, CHARGER2_SHUNT_VOLTAGE, &battery_data );
    results_logger( &charger2 );
    charger2_read_data( &charger2, CHARGER2_BATTERY_VOLTAGE, &battery_data );
    results_logger( &charger2 );
    charger2_read_data( &charger2, CHARGER2_TEMPERATURE, &battery_data );
    results_logger( &charger2 );
    charger2_read_data( &charger2, CHARGER2_BATTERY_CURRENT, &battery_data );
    results_logger( &charger2 );
    
    log_printf( &logger, "------------------------------ \r\n" );
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
