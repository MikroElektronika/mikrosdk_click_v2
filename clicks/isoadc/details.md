
---
# ISO ADC click

> The ISO ADC Click is add-on board current-shunt measurement device with isolated delta-sigma modulator. This Click board™ is based on AMC1204BDWR provide a single-chip solution for measuring the small signal of a shunt resistor across an isolated barrier from Texas Instruments. ISO ADC Click contains shunt resistor, these types of resistors are typically used to sense currents in motor control inverters, green energy generation systems, and other industrial applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/isoadc_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/iso-adc-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : SPI type


# Software Support

We provide a library for the ISO ADC Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ISO ADC Click driver.

#### Standard key functions :

- `isoadc_cfg_setup` Config Object Initialization function.
```c
void isoadc_cfg_setup ( isoadc_cfg_t *cfg );
```

- `isoadc_init` Initialization function.
```c
err_t isoadc_init ( isoadc_t *ctx, isoadc_cfg_t *cfg );
```

#### Example key functions :

- `isoadc_read_voltage` This function reads a raw ADC in ISOADC_ADC_NUM_AVERAGES number of samples and converts it to a shunt voltage in millivolts.
```c
err_t isoadc_read_voltage ( isoadc_t *ctx, float *voltage );
```

- `isoadc_get_current` This function converts a shunt voltage input to a load current in milliampers.
```c
float isoadc_get_current ( float voltage );
```

- `isoadc_get_power` This function converts a shunt voltage input to electrical power in watts.
```c
float isoadc_get_power ( isoadc_t *ctx, float voltage );
```

## Example Description

> This example demonstrates the use of ISO ADC click board by reading the shunt voltage, current, and power.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and sets the external voltage reference.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    isoadc_cfg_t isoadc_cfg;  /**< Click config object. */

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
    isoadc_cfg_setup( &isoadc_cfg );
    ISOADC_MAP_MIKROBUS( isoadc_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == isoadc_init( &isoadc, &isoadc_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    isoadc_set_vext ( &isoadc, ISOADC_VEXT_5V );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads a 10 samples of a shunt voltage measurement, then averages and calculates the current and power from it. All data is displayed on the USB UART.

```c
void application_task ( void )
{
    float voltage = 0;
    float avg_voltage = 0;
    uint16_t avg_cnt = 0; 

    log_printf( &logger, " --- MEASUREMENT IN PROGRESS ---\r\n" );
    log_info( &logger, "Keep the load and power supply stable during the measurement process\r\n" );

    while ( avg_cnt < ISOADC_VOLTAGE_NUM_AVERAGES )
    {
        if ( ISOADC_OK == isoadc_read_voltage ( &isoadc, &voltage ) )
        {
            avg_voltage += voltage;
            avg_cnt++;
        }
    }
    voltage = avg_voltage / ISOADC_VOLTAGE_NUM_AVERAGES;
    log_printf( &logger, " Shunt Voltage: %.1f mV\r\n", voltage );
    log_printf( &logger, " Current: %.3f mA\r\n", isoadc_get_current ( voltage ) );
    log_printf( &logger, " Power: %.3f W\r\n", isoadc_get_power ( &isoadc, voltage ) );
    log_printf( &logger, "-------------------------\r\n\n" );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ISOADC

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
