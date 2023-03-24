\mainpage Main Page

---
# Proximity 18 click

> Proximity 18 Click is a compact add-on board that contains a close-range proximity sensing solution. This board features the VCNL3036X01, a high-resolution digital proximity sensor from Vishay Semiconductors. Besides the proximity sensor, the VCNL3036X01 also integrates a mux and a driver for three external LEDs, which are located near the chip on the board, photodiodes, amplifiers, and analog to digital converting circuits into a single chip by CMOS process. It allows absolute distance measurement, whatever the target color and reflectance, providing an accurate range of up to 50cm.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/proximity18_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/proximity-18-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Proximity 18 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Proximity 18 Click driver.

#### Standard key functions :

- `proximity18_cfg_setup` Config Object Initialization function.
```c
void proximity18_cfg_setup ( proximity18_cfg_t *cfg );
```

- `proximity18_init` Initialization function.
```c
err_t proximity18_init ( proximity18_t *ctx, proximity18_cfg_t *cfg );
```

- `proximity18_default_cfg` Click Default Configuration function.
```c
err_t proximity18_default_cfg ( proximity18_t *ctx );
```

#### Example key functions :

- `proximity18_start_measurement` This function starts the measurement by setting the one time trigger bit in the PS_CONF3_MS register.
```c
err_t proximity18_start_measurement ( proximity18_t *ctx );
```

- `proximity18_wait_for_data_ready` This function waits for the MPX data ready interrupt flag.
```c
err_t proximity18_wait_for_data_ready ( proximity18_t *ctx );
```

- `proximity18_read_proximity` This function reads the proximity data from all 3 sensors.
```c
err_t proximity18_read_proximity ( proximity18_t *ctx, uint16_t *ps1_data, uint16_t *ps2_data, uint16_t *ps3_data );
```

## Example Description

> This example demonstrates the use of Proximity 18 click board by reading and displaying the proximity data on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger, and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity18_cfg_t proximity18_cfg;  /**< Click config object. */

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
    proximity18_cfg_setup( &proximity18_cfg );
    PROXIMITY18_MAP_MIKROBUS( proximity18_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proximity18_init( &proximity18, &proximity18_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY18_ERROR == proximity18_default_cfg ( &proximity18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the proximity data from 3 sensors in a multiplex mode and displays it on the USB UART
approximately once per second. The higher the proximity value, the closer the detected object is.

```c
void application_task ( void )
{
    uint16_t ps1_data, ps2_data, ps3_data;
    if ( PROXIMITY18_ERROR == proximity18_start_measurement ( &proximity18 ) )
    {
        log_error ( &logger, " Start measurement." );
        Delay_ms ( 5000 );
    }
    if ( PROXIMITY18_ERROR == proximity18_wait_for_data_ready ( &proximity18 ) )
    {
        log_error ( &logger, " Wait for data ready." );
        Delay_ms ( 5000 );
    }
    if ( PROXIMITY18_ERROR == proximity18_read_proximity ( &proximity18, &ps1_data, &ps2_data, &ps3_data ) )
    {
        log_error ( &logger, " Read proximity." );
        Delay_ms ( 5000 );
    }
    else
    {
        log_printf ( &logger, " PS1 data: %u\r\n", ps1_data );
        log_printf ( &logger, " PS2 data: %u\r\n", ps2_data );
        log_printf ( &logger, " PS3 data: %u\r\n\n", ps3_data );
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity18

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
