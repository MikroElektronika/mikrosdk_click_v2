
---
# Charger 8 Click

> [Charger 8 Click](https://www.mikroe.com/?pid_product=MIKROE-3348) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3348&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Nov 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application is used for charging devices and battery diagnostics

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger8

### Example Key Functions

- `charger8_cfg_setup` Config Object Initialization function. 
```c
void charger8_cfg_setup ( charger8_cfg_t *cfg );
``` 
 
- `charger8_init` Initialization function. 
```c
err_t charger8_init ( charger8_t *ctx, charger8_cfg_t *cfg );
```

- `charger8_default_cfg` Click Default Configuration function. 
```c
void charger8_default_cfg ( charger8_t *ctx );
```

- `charger8_get_temperature` Functions for read Temperature of the chip. 
```c
float charger8_get_temperature( charger8_t *ctx );
```
 
- `charger8_get_capacity` Function for reads the current capacity of the battery. 
```c
uint16_t charger8_get_capacity( charger8_t *ctx );
```

- `charger8_get_status` Function for reads the Status register. 
```c
uint16_t charger8_get_status( charger8_t *ctx );
```

### Application Init

> Initialization driver init, enable moduele and default configuration,
> disable ALERT and USB suspand mode and sets max battery capacity

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    charger8_cfg_t cfg;

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

    charger8_cfg_setup( &cfg );
    CHARGER8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    charger8_init( &charger8, &cfg );

    charger8_enable( &charger8, CHARGER8_CHARGER_ENABLE );
    charger8_default_cfg( &charger8 );
    charger8_reset( &charger8 );
    charger8_set_alert( &charger8, CHARGER8_ALERT_DISABLE );
    charger8_set_usb_suspend( &charger8, CHARGER8_USB_SUSPAND_MODE_DISABLE );
    charger8_set_max_battery_capacity( 2000 );
    log_printf( &logger, " --- Charger - Start measurement --- \r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

> Reads battery diagnostics and this data logs to USBUART every 1500 ms.

```c
void application_task ( void )
{
    //  Task implementation.

    float temperature;
    float current;
    float voltage;
    uint8_t soc;
    uint16_t capacity;
    
    log_printf( &logger, " - Battery diagnostics - \r\n" );
    
    temperature = charger8_get_temperature( &charger8 );
    log_printf( &logger, " - Temperature : %f C\r\n", temperature );
    
    current = charger8_get_current( &charger8 );
    log_printf( &logger, " - Current : %f mA\r\n", current);
    
    voltage = charger8_get_voltage( &charger8 );
    log_printf( &logger, " - Voltage : %f mV\r\n", voltage);
    
    capacity = charger8_get_capacity( &charger8 );
    log_printf( &logger, " - Capacity : %d mAh\r\n", capacity );
    
    soc = charger8_get_soc( &charger8 );
    log_printf( &logger, " - SOC : %d %%\r\n", soc );
    
    log_printf( &logger, " -------------------------- \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 500 );
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
