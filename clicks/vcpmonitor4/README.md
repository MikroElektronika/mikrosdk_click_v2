\mainpage Main Page

---
# VCP Monitor 4 click

> VCP Monitor 4 Click is a compact add-on board that represents a high-precision power monitoring system. This board features the INA239, ultra-precise digital power monitor with a 16-bit delta-sigma ADC specifically designed for current-sensing applications from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/vcp_monitor_4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/vcp-monitor-4-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Jul 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the VCPMonitor4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for VCPMonitor4 Click driver.

#### Standard key functions :

- `vcpmonitor4_cfg_setup` Config Object Initialization function.
```c
void vcpmonitor4_cfg_setup ( vcpmonitor4_cfg_t *cfg );
```

- `vcpmonitor4_init` Initialization function.
```c
err_t vcpmonitor4_init ( vcpmonitor4_t *ctx, vcpmonitor4_cfg_t *cfg );
```

- `vcpmonitor4_default_cfg` Click Default Configuration function.
```c
err_t vcpmonitor4_default_cfg ( vcpmonitor4_t *ctx );
```

#### Example key functions :

- `vcpmonitor4_get_vbus` Get BUS voltage.
```c
err_t vcpmonitor4_get_vbus ( vcpmonitor4_t *ctx, float *vbus )
```

- `vcpmonitor4_get_current` Get Current.
```c
err_t vcpmonitor4_get_current ( vcpmonitor4_t *ctx, float *current )
```

- `vcpmonitor4_get_power` Get Shunt voltage.
```c
err_t vcpmonitor4_get_power ( vcpmonitor4_t *ctx, float *power )
```

## Example Description

> This example application showcases ability of Click board
to be configured for different readings and read temperature, 
voltage, current and power.

**The demo application is composed of two sections :**

### Application Init

> Initialization of communication modules (SPI, UART) and 
additional alert pin. Reads Manufacturer and Device ID,
Configurates device for reading all device measurements.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    vcpmonitor4_cfg_t vcpmonitor4_cfg;  /**< Click config object. */

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
    vcpmonitor4_cfg_setup( &vcpmonitor4_cfg );
    VCPMONITOR4_MAP_MIKROBUS( vcpmonitor4_cfg, MIKROBUS_1 );
    err_t init_flag  = vcpmonitor4_init( &vcpmonitor4, &vcpmonitor4_cfg );
    VCPMONITOR4_SET_DATA_SAMPLE_EDGE
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    uint32_t temp_data = 0;
    vcpmonitor4_generic_read( &vcpmonitor4, VCPMONITOR4_REG_MANUFACTURER_ID, &temp_data );
    log_printf( &logger, " > Manufacturer ID: \t0x%.4X\r\n", temp_data );
    
    vcpmonitor4_generic_read( &vcpmonitor4, VCPMONITOR4_REG_DEVICE_ID, &temp_data );
    log_printf( &logger, " > Device ID: \t\t0x%.4X\r\n", temp_data );
    
    vcpmonitor4_default_cfg ( &vcpmonitor4 );
    Delay_ms( 1000 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> In span of 500ms reads and calculates data for IC temperature,
Bus voltage in V, Shunt voltage in mV, and current and power for device.

```c

void application_task ( void )
{
    float read_data;
    vcpmonitor4_get_temperature( &vcpmonitor4, &read_data );
    log_printf( &logger, " > Temperature:\t%.2f \r\n", read_data );
    
    vcpmonitor4_get_vbus( &vcpmonitor4, &read_data );
    log_printf( &logger, " > Vbus[V]:\t%.2f \r\n", read_data );
    
    vcpmonitor4_get_vshunt( &vcpmonitor4, &read_data );
    log_printf( &logger, " > Vshunt[mV]:\t%.2f \r\n", read_data );
    
    vcpmonitor4_get_current( &vcpmonitor4, &read_data );
    log_printf( &logger, " > Current[A]:\t%.2f \r\n", read_data );
    
    vcpmonitor4_get_power( &vcpmonitor4, &read_data );
    log_printf( &logger, " > Power[W]:\t%.2f \r\n", read_data );
    log_printf( &logger, "*************************\r\n" );
    
    Delay_ms( 500 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.VCPMonitor4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
