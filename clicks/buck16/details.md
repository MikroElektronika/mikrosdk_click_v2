
---
# Buck 16 click

> Buck 16 Click is a compact add-on board that contains a DC-DC power converter that steps down the voltage from its input to its output. This board features the TPS62912, a high-efficiency, low noise, and low ripple current-mode synchronous buck converter from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buck16_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/buck-16-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Sep 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the Buck16 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Buck16 Click driver.

#### Standard key functions :

- `buck16_cfg_setup` Config Object Initialization function.
```c
void buck16_cfg_setup ( buck16_cfg_t *cfg );
```

- `buck16_init` Initialization function.
```c
err_t buck16_init ( buck16_t *ctx, buck16_cfg_t *cfg );
```

#### Example key functions :

- `buck16_enable_output` Enable/Disable voltage output.
```c
void buck16_enable_output ( buck16_t *ctx, uint8_t enable );
```

- `buck16_set_potentiometer` Set potentiometer resistivity.
```c
err_t buck16_set_potentiometer ( buck16_t *ctx, uint16_t rwb );
```

- `buck16_set_output` Set output voltage.
```c
err_t buck16_set_output ( buck16_t *ctx, uint16_t vout );
```

## Example Description

> This example showcases ability of the device to
control voltage output of device. Output voltage 
can range from 800 to 5500 depending of VIN. By default
it will go from 800 to 3300 VIN==VCC.

**The demo application is composed of two sections :**

### Application Init

> Initialization of communication modules (SPI, UART) 
and additional pin for enabling output and sets it to
high.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    buck16_cfg_t buck16_cfg;    /**< Click config object. */

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
    log_printf( &logger, "\r> Application Init <\r\n" );

    // Click initialization.
    buck16_cfg_setup( &buck16_cfg );
    BUCK16_MAP_MIKROBUS( buck16_cfg, MIKROBUS_1 );
    err_t init_flag  = buck16_init( &buck16, &buck16_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    buck16_enable_output( &buck16, 1 );
    log_printf( &logger, "> Application Task <\r\n" );
}

```

### Application Task

> Sets voltage output first to 900mV then to 2500 mV.
Then disables and enables output by toggling pin.
In the end sets output value to 1500mV.

```c

void application_task ( void )
{
    log_printf( &logger, " > Setting output to 0.9V\r\n" );
    buck16_set_output( &buck16, 900 );
    Delay_ms( 5000 );
    log_printf( &logger, " > Setting output to 2.5V\r\n" );
    buck16_set_output( &buck16, 2500 );
    Delay_ms( 5000 );
    log_printf( &logger, " > Disable output\r\n" );
    buck16_enable_output( &buck16, 0 );
    Delay_ms( 3000 );
    log_printf( &logger, " > Enable output\r\n" );
    buck16_enable_output( &buck16, 1 );
    Delay_ms( 3000 );
    log_printf( &logger, " > Setting output to 1.5V\r\n" );
    buck16_set_output( &buck16, 1500 );
    Delay_ms( 5000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck16

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
