
---
# Power Monitor 2 click

> Power Monitoring 2 Click is a compact add-on board for precise power monitoring of connected load devices. This board features two INA219 12-bit I2C-output digital power monitors from Texas Instruments. This Click board™ monitors current and voltage on two separate power rails - 3.3V and 5V - of an onboard mikroBUS™ socket, providing real-time digital readings of the power consumption of added Click boards™. It supports high-speed I2C communication with configurable I2C addresses and operates at 3.3V and 5V logic levels, which makes it ideal for applications in power management, system diagnostics, and energy optimization in embedded systems.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/powermonitor2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/power-monitor-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the Power Monitor 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Power Monitor 2 Click driver.

#### Standard key functions :

- `powermonitor2_cfg_setup` Config Object Initialization function.
```c
void powermonitor2_cfg_setup ( powermonitor2_cfg_t *cfg );
```

- `powermonitor2_init` Initialization function.
```c
err_t powermonitor2_init ( powermonitor2_t *ctx, powermonitor2_cfg_t *cfg );
```

- `powermonitor2_default_cfg` Click Default Configuration function.
```c
err_t powermonitor2_default_cfg ( powermonitor2_t *ctx );
```

#### Example key functions :

- `powermonitor2_set_address` This function sets the device slave address.
```c
err_t powermonitor2_set_address ( powermonitor2_t *ctx, uint8_t slave_address );
```

- `powermonitor2_read_data` This function reads the shunt voltage, bus voltage, current, and power data measurements.
```c
err_t powermonitor2_read_data ( powermonitor2_t *ctx, powermonitor2_data_t *data_out );
```

- `powermonitor2_read_data_avg` This function reads the shunt voltage, bus voltage, current, and power data measurements averaged from num_conv samples.
```c
err_t powermonitor2_read_data_avg ( powermonitor2_t *ctx, uint16_t num_conv, powermonitor2_data_t *data_out );
```

## Example Description

> This example demonstrates the use of Power Monitor 2 click by reading and displaying the power consumption at 3V3 and 5V of the connected click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    powermonitor2_cfg_t powermonitor2_cfg;  /**< Click config object. */

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
    powermonitor2_cfg_setup( &powermonitor2_cfg );
    POWERMONITOR2_MAP_MIKROBUS( powermonitor2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == powermonitor2_init( &powermonitor2, &powermonitor2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( POWERMONITOR2_ERROR == powermonitor2_default_cfg ( &powermonitor2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the voltage, current, and power measurements from U2 and U3 sensors averaged from 20 samples and displays the results on the USB UART.

```c
void application_task ( void )
{
    powermonitor2_data_t pm_3v3, pm_5v;

    powermonitor2_set_address ( &powermonitor2, powermonitor2.address_3v3 );
    if ( POWERMONITOR2_OK == powermonitor2_read_data_avg ( &powermonitor2, POWERMONITOR2_DEFAULT_NUM_CONV, &pm_3v3 ) )
    {
        log_printf( &logger, " --- 3V3 Power Monitor ---\r\n" );
        log_printf( &logger, " Voltage: %.3f V\r\n", pm_3v3.bus_v );
        log_printf( &logger, " Current: %.3f A\r\n", pm_3v3.current );
        log_printf( &logger, " Power: %.2f W\r\n", pm_3v3.power );
        log_printf( &logger, " -------------------------\r\n" );
    }
    
    powermonitor2_set_address ( &powermonitor2, powermonitor2.address_5v );
    if ( POWERMONITOR2_OK == powermonitor2_read_data_avg ( &powermonitor2, POWERMONITOR2_DEFAULT_NUM_CONV, &pm_5v ) )
    {
        log_printf( &logger, " ---- 5V Power Monitor ---\r\n" );
        log_printf( &logger, " Voltage: %.3f V\r\n", pm_5v.bus_v );
        log_printf( &logger, " Current: %.3f A\r\n", pm_5v.current );
        log_printf( &logger, " Power: %.2f W\r\n", pm_5v.power );
        log_printf( &logger, " -------------------------\r\n" );
    }

    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.PowerMonitor2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
