\mainpage Main Page

---
# GainAMP click

> GainAMP click carries the LTC6912 dual channel, low noise, digitally programmable gain amplifier (PGA).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gainamp_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gainamp-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the GainAMP Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for GainAMP Click driver.

#### Standard key functions :

- `gainamp_cfg_setup` Config Object Initialization function.
```c
void gainamp_cfg_setup ( gainamp_cfg_t *cfg );
```

- `gainamp_init` Initialization function.
```c
err_t gainamp_init ( gainamp_t *ctx, gainamp_cfg_t *cfg );
```

- `gainamp_default_cfg` Click Default Configuration function.
```c
err_t gainamp_default_cfg ( gainamp_t *ctx );
```

#### Example key functions :

- `gainamp_read_an_pin_value` GainAMP read AN pin value function.
```c
err_t gainamp_read_an_pin_value ( gainamp_t *ctx, uint16_t *data_out );
```

- `gainamp_read_an_pin_voltage` GainAMP read AN pin voltage level function.
```c
err_t gainamp_read_an_pin_voltage ( gainamp_t *ctx, float *data_out );
```

- `gainamp_set_gain` Function for sets gain of the GainAMP Click.
```c
void gainamp_set_gain ( gainamp_t *ctx, uint8_t gain );
```

## Example Description

> This is an example that demonstrates the use of the GainAMP Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes SPI module and set CS pin and RST pin as OUTPUT, initialization driver init and resets chip.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gainamp_cfg_t gainamp_cfg;  /**< Click config object. */

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

    gainamp_cfg_setup( &gainamp_cfg );
    GAINAMP_MAP_MIKROBUS( gainamp_cfg, MIKROBUS_1 );
    err_t init_flag  = gainamp_init( &gainamp, &gainamp_cfg );
    if ( ( SPI_MASTER_ERROR == init_flag ) || ( ADC_ERROR == init_flag ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    gainamp_reset( &gainamp );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Sets the gain for both channels, channel A and channel B.

```c

void application_task ( void )
{
    gainamp_set_gain( &gainamp, GAINAMP_CHANNEL_A_x1 | GAINAMP_CHANNEL_B_x5 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    gainamp_set_gain( &gainamp, GAINAMP_CHANNEL_A_x10 | GAINAMP_CHANNEL_B_x100 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.GainAMP

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
