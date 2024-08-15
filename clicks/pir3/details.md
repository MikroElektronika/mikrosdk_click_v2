
---
# PIR 3 click

> PIR 3 Click is a compact add-on board designed for efficient and reliable motion detection in various applications. This board features the ZDP323B1 sensor from Zilog (Littelfuse), with high EMI immunity and precise motion detection capabilities. It includes a spectral filter window tuned to an 8-13um wavelength, dual sensing elements with a 0.6mm spacing, and a field of view of 148° on the X-axis and 136° on the Y-axis. The board also integrates the ZNCL10S PIR lens for maximum IR transmissivity and includes the Click Snap feature for flexible implementation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pir3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pir-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the PIR 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for PIR 3 Click driver.

#### Standard key functions :

- `pir3_cfg_setup` Config Object Initialization function.
```c
void pir3_cfg_setup ( pir3_cfg_t *cfg );
```

- `pir3_init` Initialization function.
```c
err_t pir3_init ( pir3_t *ctx, pir3_cfg_t *cfg );
```

- `pir3_default_cfg` Click Default Configuration function.
```c
err_t pir3_default_cfg ( pir3_t *ctx );
```

#### Example key functions :

- `pir3_set_detection_level` This function sets the detection threshold level in the ctx->config structure.
```c
void pir3_set_detection_level ( pir3_t *ctx, uint8_t detlvl );
```

- `pir3_write_config` This function writes a config structure to the sensor by using I2C serial interface.
```c
err_t pir3_write_config ( pir3_t *ctx );
```

- `pir3_read_peak_hold` This function reads a 12-bit signed peak hold data by using I2C serial interface.
```c
err_t pir3_read_peak_hold ( pir3_t *ctx, int16_t *peak_hold );
```

## Example Description

> This example demonstrates the use of PIR 3 click board by reading and displaying the peak hold tracking data.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pir3_cfg_t pir3_cfg;  /**< Click config object. */

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
    pir3_cfg_setup( &pir3_cfg );
    PIR3_MAP_MIKROBUS( pir3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pir3_init( &pir3, &pir3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PIR3_ERROR == pir3_default_cfg ( &pir3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the peak hold tracking data every 100ms and displays the results on the USB UART.

```c
void application_task ( void )
{
    int16_t peak_hold = 0;
    if ( PIR3_OK == pir3_read_peak_hold ( &pir3, &peak_hold ) )
    {
        log_printf( &logger, " PEAK HOLD: %d\r\n\n", peak_hold );
        Delay_ms ( 100 );
    }
}
```

## Note

> In order to establish communication with the sensor, some of the supported MCUs may require
the I2C lines to be pulled up additionally either with the external or internal weak pull-up resistor.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.PIR3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
