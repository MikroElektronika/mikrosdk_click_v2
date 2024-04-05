\mainpage Main Page

---
# SPI Isolator 3 click

SPI Isolator 3 Click is a compact add-on board that contains a digital isolator optimized for a serial peripheral interface. This board features the MAX14483, a 6-channel 3.75kVRMS digital galvanic isolator with a very low propagation delay on the SDI, SDO, and SCLK channels from Maxim Integrated. Besides a second enable control input, which allows MAX14483 to isolate multiple SPI devices, and an auxiliary channel available for passing timing or control signals from the master side to the slave side, the MAX14483 also possesses power monitors provided for both power domains to signal if the opposite side of the isolator is ready for operation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/spi_isolator_3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/spi-isolator-3-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the SpiIsolator3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for SpiIsolator3 Click driver.

#### Standard key functions :

- `spiisolator3_cfg_setup` Config Object Initialization function.
```c
void spiisolator3_cfg_setup ( spiisolator3_cfg_t *cfg );
```

- `spiisolator3_init` Initialization function.
```c
SPIISOLATOR3_RETVAL spiisolator3_init ( spiisolator3_t *ctx, spiisolator3_cfg_t *cfg );
```

- `spiisolator3_default_cfg` Click Default Configuration function.
```c
void spiisolator3_default_cfg ( spiisolator3_t *ctx );
```

#### Example key functions :

- `spiisolator3_generic_write` SPI Isolator 3 data writing function.
```c
SPIISOLATOR3_RETVAL spiisolator3_generic_write ( spiisolator3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );
```

- `spiisolator3_generic_read` SPI Isolator 3 data reading function.
```c
SPIISOLATOR3_RETVAL spiisolator3_generic_read ( spiisolator3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );
```

- `spiisolator3_get_fault` SPI Isolator 3 get fault state function.
```c
uint8_t spiisolator3_get_fault ( spiisolator3_t *ctx );
```

## Example Description

> This library contains API for the SPI Isolator 3 click driver.
> This demo application shows an example of an SPI Isolator 3 click wired 
> to the nvSRAM 4 click for reading Device ID.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, the app sets the default configuration.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;                    /**< Logger config object. */
    spiisolator3_cfg_t spiisolator3_cfg;  /**< Click config object. */

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

    spiisolator3_cfg_setup( &spiisolator3_cfg );
    SPIISOLATOR3_MAP_MIKROBUS( spiisolator3_cfg, MIKROBUS_1 );
    err_t init_flag  = spiisolator3_init( &spiisolator3, &spiisolator3_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    spiisolator3_default_cfg ( &spiisolator3 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

```

### Application Task

> This is an example that shows the use of an SPI Isolator 3 click board™.
> Logs Device ID of the nvSRAM 4 click wired to the SPI Isolator 3 board™.  
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) {
    get_device_id( );
    log_printf( &logger, " Device ID : 0x%.8LX\r\n", device_id ); 
    Delay_ms ( 1000 );
}

```

## Additional Function

- `get_device_id` Get Device ID function.
```c
void get_device_id ( void );
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SpiIsolator3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all Mikroelektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
