
---
# DIGI POT Click

DIGIPOT Click is an accessory board in mikroBUS form factor. It features a single-channel digital potentiometer MCP4161 with 8-bit resolution (256 wiper steps) and industry-standard SPI serial interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/digipot_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/digipot-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the DigiPot Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DigiPot Click driver.

#### Standard key functions :

- `digipot_cfg_setup` Config Object Initialization function.
```c
void digipot_cfg_setup ( digipot_cfg_t *cfg );
```

- `digipot_init` Initialization function.
```c
err_t digipot_init ( digipot_t *ctx, digipot_cfg_t *cfg );
```

#### Example key functions :

- `digipot_set_wiper_positions` The function sets 8-bit wiper positions data.
```c
void digipot_set_wiper_positions ( digipot_t *ctx, uint8_t wiper_pos );
```

- `digipot_convert_output` The function convert 10-bit ADC value to volatage reference.
```c
float digipot_convert_output ( uint16_t adc_val, float v_ref );
```

## Example Description

> The demo application changes the resistance using DIGIPOT Click.

**The demo application is composed of two sections :**

### Application Init

> Initializes SPI and LOG modules.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot_cfg_t digipot_cfg;  /**< Click config object. */

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

    digipot_cfg_setup( &digipot_cfg );
    DIGIPOT_MAP_MIKROBUS( digipot_cfg, MIKROBUS_1 );
    err_t init_flag  = digipot_init( &digipot, &digipot_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_printf( &logger, "----------------\r\n" );
    log_printf( &logger, " DIGI POT Click\r\n" );
    log_printf( &logger, "----------------\r\n" );
}

```

### Application Task

> This is an example which demonstrates the use of DIGI POT Click board. Increments the wiper position by 10 positions every 5 seconds.

```c

void application_task ( void ) {
    for ( uint16_t n_cnt = 127; n_cnt < 255; n_cnt += 10 ) {
        wiper_pos = ( uint8_t ) n_cnt;
        digipot_set_wiper_positions( &digipot, wiper_pos );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DigiPot

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
