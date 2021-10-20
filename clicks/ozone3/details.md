
---
# Ozone 3 click

Ozone 3 Click is a compact add-on board suitable for ozone concentration detection and monitoring. This board features the 110-407, a high-performance ultra-thin electrochemical gas sensor from SPEC Sensors supported by the LMP91000, a high-precision integrated analog front-end IC (AFE) ideal for this sensing application. It provides the reference voltage required by the sensor and offers a choice between the analog output from the AFE IC buffered with the low noise Op-Amp and digital output from the 12-bit SAR A/D converter.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ozone3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ozone-3-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Ozone3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Ozone3 Click driver.

#### Standard key functions :

- `ozone3_cfg_setup` Config Object Initialization function.
```c
void ozone3_cfg_setup ( ozone3_cfg_t *cfg );
```

- `ozone3_init` Initialization function.
```c
OZONE3_RETVAL ozone3_init ( ozone3_t *ctx, ozone3_cfg_t *cfg );
```

- `ozone3_default_cfg` Click Default Configuration function.
```c
void ozone3_default_cfg ( ozone3_t *ctx );
```

#### Example key functions :

- `ozone3_read_adc` Ozone 3 read ADC function.
```c
uint16_t ozone3_read_adc ( ozone3_t *ctx );
```

- `ozone3_get_o3_ppm` Ozone 3 get O3 ppm function.
```c
float ozone3_get_o3_ppm ( ozone3_t *ctx );
```

## Example Description

> This library contains API for the Ozone 3 click driver.
> This demo application shows an example of the O3 ppm data measurement.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization the app set default settings.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;        /**< Logger config object. */
    ozone3_cfg_t ozone3_cfg;  /**< Click config object. */

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

    ozone3_cfg_setup( &ozone3_cfg );
    OZONE3_MAP_MIKROBUS( ozone3_cfg, MIKROBUS_1 );
    err_t init_flag = ozone3_init( &ozone3, &ozone3_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    ozone3_default_cfg ( &ozone3 );
    log_info( &logger, " Application Task " );
    Delay_ms( 300 );
}

```

### Application Task

> This is an example that shows the use of a Ozone 3 click board™.
> Get and logs O3 ( Trioxygen ) data as ppm value.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) {
    float o3_ppm = ozone3_get_o3_ppm( &ozone3 );
    log_printf( &logger, "\tOzone : %.2f ppm \r\n", o3_ppm );
    Delay_ms( 500 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Ozone3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
