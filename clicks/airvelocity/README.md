\mainpage Main Page

---
# Air Velocity click

> Air Velocity Click is a compact add-on board that measures direct airspeed. This board features the FS3000-1005, a surface-mount type air velocity module utilizing a MEMS thermopile-based sensor from Renesas. This I2C-configurable air velocity module features a digital output with a 12-bit resolution with a wide operational range of 0-7.2meter/second (0-16.2mph). The sensor comprises a “solid” thermal isolation technology and silicon-carbide coating to protect it from abrasive wear and water condensation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/airvelocity_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/air-velocity-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Air Velocity Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Air Velocity Click driver.

#### Standard key functions :

- `airvelocity_cfg_setup` Config Object Initialization function.
```c
void airvelocity_cfg_setup ( airvelocity_cfg_t *cfg );
```

- `airvelocity_init` Initialization function.
```c
err_t airvelocity_init ( airvelocity_t *ctx, airvelocity_cfg_t *cfg );
```

#### Example key functions :

- `airvelocity_read_output` This function reads the raw output counts by using I2C serial interface.
```c
err_t airvelocity_read_output ( airvelocity_t *ctx, uint16_t *out_counts );
```

- `airvelocity_convert_counts_to_mps` This function converts raw output counts to velocity in m/sec (0-7.23).
```c
float airvelocity_convert_counts_to_mps ( uint16_t out_counts );
```

## Example Description

> This example demonstrates the use of Air Velocity click board by reading and displaying the output counts and air velocity in m/sec.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    airvelocity_cfg_t airvelocity_cfg;  /**< Click config object. */

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
    airvelocity_cfg_setup( &airvelocity_cfg );
    AIRVELOCITY_MAP_MIKROBUS( airvelocity_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == airvelocity_init( &airvelocity, &airvelocity_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the output counts and converts it to air velocity in m/sec. Both values will be displayed on the USB UART approximately every 250ms.

```c
void application_task ( void )
{
    uint16_t out_counts;
    if ( AIRVELOCITY_OK == airvelocity_read_output ( &airvelocity, &out_counts ) )
    {
        log_printf ( &logger, " Out counts: %u\r\n", out_counts );
        log_printf ( &logger, " Air velocity: %.2f m/s\r\n\n", airvelocity_convert_counts_to_mps ( out_counts ) );
        Delay_ms ( 250 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.AirVelocity

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
