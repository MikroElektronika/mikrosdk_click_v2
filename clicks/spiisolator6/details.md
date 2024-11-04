
---
# SPI Isolator 6 Click

> SPI Isolator 6 Click is a compact add-on board representing a digital isolator optimized for a serial peripheral interface. This board features the MAX22345, a fast, low-power 4-channel digital galvanic isolator from Analog Devices. This device comes with a maximum data rate of 200Mbps and transfers digital signals between circuits with different power domains featuring reinforced isolation for a withstand voltage rating of 3.75kVRMS for 60 seconds.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/spiisolator6_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/spi-isolator-6-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the SPI Isolator 6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for SPI Isolator 6 Click driver.

#### Standard key functions :

- `spiisolator6_cfg_setup` Config Object Initialization function.
```c
void spiisolator6_cfg_setup ( spiisolator6_cfg_t *cfg );
```

- `spiisolator6_init` Initialization function.
```c
err_t spiisolator6_init ( spiisolator6_t *ctx, spiisolator6_cfg_t *cfg );
```

#### Example key functions :

- `spiisolator6_generic_write` This function writes a desired number of data bytes by using SPI serial interface.
```c
err_t spiisolator6_generic_write ( spiisolator6_t *ctx, uint8_t *data_in, uint8_t in_len );
```

- `spiisolator6_generic_read` This function writes and then reads a desired number of data bytes by using SPI serial interface.
```c
err_t spiisolator6_generic_read ( spiisolator6_t *ctx, uint8_t *data_in, uint8_t in_len, uint8_t *data_out, uint8_t out_len );
```

## Example Description

> This example demonstrates the use of SPI Isolator 6 Click board by reading the device ID of the connected Accel 22 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    spiisolator6_cfg_t spiisolator6_cfg;  /**< Click config object. */

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
    spiisolator6_cfg_setup( &spiisolator6_cfg );
    SPIISOLATOR6_MAP_MIKROBUS( spiisolator6_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == spiisolator6_init( &spiisolator6, &spiisolator6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and checks the device ID of the connected Accel 22 Click board, and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    spiisolator6_get_accel22_device_id ( &spiisolator6 );
    Delay_ms ( 1000 );
}
```

## Note

> Make sure to provide VCC power supply on VCC-EXT pin.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SPIIsolator6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
