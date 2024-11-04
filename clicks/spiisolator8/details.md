
---
# SPI Isolator 8 Click

> SPI Isolator 8 Click is a compact add-on board representing a digital isolator optimized for a serial peripheral interface. This board features the ISOW7743, a quad-channel digital isolator from Texas Instruments. This device has a maximum data rate of 100Mbps and transfers digital signals between circuits with different power domains featuring reinforced isolation for a withstand voltage rating of 5kVRMS for 60 seconds.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/spiisolator8_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/spi-isolator-8-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the SPI Isolator 8 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for SPI Isolator 8 Click driver.

#### Standard key functions :

- `spiisolator8_cfg_setup` Config Object Initialization function.
```c
void spiisolator8_cfg_setup ( spiisolator8_cfg_t *cfg );
```

- `spiisolator8_init` Initialization function.
```c
err_t spiisolator8_init ( spiisolator8_t *ctx, spiisolator8_cfg_t *cfg );
```

- `spiisolator8_default_cfg` Click Default Configuration function.
```c
void spiisolator8_default_cfg ( spiisolator8_t *ctx );
```

#### Example key functions :

- `spiisolator8_transfer` SPI Isolator 8 data transfer function.
```c
err_t spiisolator8_transfer ( spiisolator8_t *ctx, uint8_t *data_in, uint8_t *data_out, uint8_t len );
```

- `spiisolator8_enc_enable` SPI Isolator 8 enable side 1 function.
```c
void spiisolator8_enc_enable ( spiisolator8_t *ctx );
```

- `spiisolator8_enp_enable` SPI Isolator 8 enable side 2 function.
```c
void spiisolator8_enp_enable ( spiisolator8_t *ctx );
```

## Example Description

> This example demonstrates the use of SPI Isolator 8 Click board™ 
> by reading the manufacturer ID and device ID 
> of the connected Flash 11 Click board™.

**The demo application is composed of two sections :**

### Application Init

> The initialization of SPI module, log UART, and additional pins.
> After the driver init, the application enabled both isolated sides of the device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    spiisolator8_cfg_t spiisolator8_cfg;  /**< Click config object. */

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
    spiisolator8_cfg_setup( &spiisolator8_cfg );
    SPIISOLATOR8_MAP_MIKROBUS( spiisolator8_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == spiisolator8_init( &spiisolator8, &spiisolator8_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    spiisolator8_default_cfg ( &spiisolator8 );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " -----------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application reads and checks the manufacturer ID and 
> device ID of the connected Flash 11 Click board™. 
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    static uint8_t cmd_get_id[ 6 ] = { FLASH11_CMD_GET_ID };
    static uint8_t read_id[ 6 ] = { 0 };
    if ( SPIISOLATOR8_OK == spiisolator8_transfer( &spiisolator8, &cmd_get_id[ 0 ], &read_id[ 0 ], 6 ) )
    {
        if ( ( FLASH11_MANUFACTURER_ID == read_id[ 4 ] ) && ( FLASH11_DEVICE_ID == read_id[ 5 ] ) )
        {
            log_printf( &logger, " Manufacturer ID: 0x%.2X\r\n", ( uint16_t ) read_id[ 4 ] );
            log_printf( &logger, " Device ID: 0x%.2X    \r\n", ( uint16_t ) read_id[ 5 ] );
            log_printf( &logger, " -----------------------\r\n" );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SPIIsolator8

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
