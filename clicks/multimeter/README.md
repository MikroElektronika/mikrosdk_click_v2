
---
# Multimeter Click

> [Multimeter Click](https://www.mikroe.com/?pid_product=MIKROE-3116) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3116&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This example showcases how to configure, initialize and use the Multimeter Click. The
  Click measures resistance in Ohms, voltage in mVs, current in mAs and capacitance in nFs
  using a dual CMOS and quad CMOS op-amps, an ADC and other on board modules. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Multimeter

### Example Key Functions

- `multimeter_cfg_setup` Config Object Initialization function. 
```c
void multimeter_cfg_setup ( multimeter_cfg_t *cfg );
``` 
 
- `multimeter_init` Initialization function. 
```c
err_t multimeter_init ( multimeter_t *ctx, multimeter_cfg_t *cfg );
```

- `multimeter_default_cfg` Click Default Configuration function. 
```c
void multimeter_default_cfg ( multimeter_t *ctx );
```

- `multimeter_read_resistance` This function reads and returns resistance data. 
```c
float multimeter_read_resistance ( multimeter_t *ctx );
```
 
- `multimeter_read_voltage` This function reads and returns voltage data. 
```c
float multimeter_read_voltage ( multimeter_t *ctx );
```

- `multimeter_read_current` This function reads and returns current data. 
```c
float multimeter_read_current ( multimeter_t *ctx );
```

### Application Init

> This function initializes and configures the logger and Click modules. Additional 
  calibration of the measurement components is done in the default_cfg(...) function.

```c
void application_init ( )
{
    log_cfg_t log_cfg;
    multimeter_cfg_t cfg;

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

    multimeter_cfg_setup( &cfg );
    MULTIMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    multimeter_init( &multimeter, &cfg );
    multimeter_default_cfg( &multimeter );
}
```

### Application Task

> This function measures and displays resistance, voltage, current and capacitance data.
  It does so every second. 

```c
void application_task ( )
{
    float resistance;
    float voltage;
    float current;
    float capacitance;

    resistance = multimeter_read_resistance( &multimeter );
    log_printf( &logger, " * Resistance: %.3f Ohms * \r\n", resistance );

    voltage = multimeter_read_voltage( &multimeter );
    log_printf( &logger, " * Voltage: %.3f mV * \r\n", voltage );

    current = multimeter_read_current( &multimeter );
    log_printf( &logger, " * Current: %.3f mA * \r\n", current );

    capacitance = multimeter_read_capacitance( &multimeter );
    log_printf( &logger, " * Capacitance: %.3f nF * \r\n", capacitance );

    log_printf( &logger, "------------------------\r\n" );
    Delay_1sec( );
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
