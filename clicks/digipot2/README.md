\mainpage Main Page

---
# DIGI POT 2 click

DIGI POT 2 click is a mikroBUS™ add-on board with a single channel digital potentiometer TPL0501 with 256 wiper positions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/digipot_2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/digipot-2-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the DigiPot2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DigiPot2 Click driver.

#### Standard key functions :

- `digipot2_cfg_setup` Config Object Initialization function.
```c
void digipot2_cfg_setup ( digipot2_cfg_t *cfg );
```

- `digipot2_init` Initialization function.
```c
err_t digipot2_init ( digipot2_t *ctx, digipot2_cfg_t *cfg );
```

#### Example key functions :

- `digipot2_set_wiper_positions` The function sets 8-bit wiper positions data.
```c
void digipot2_set_wiper_positions ( digipot2_t *ctx, uint8_t wiper_pos );
```

- `digipot2_convert_output` The function convert 10-bit ADC value to volatage reference.
```c
float digipot2_convert_output ( uint16_t adc_val, float v_ref );
```

## Example Description

> The demo application changes the resistance using DIGI POT 2 Click.

**The demo application is composed of two sections :**

### Application Init

> Initializes SPI and LOG modules.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot2_cfg_t digipot2_cfg;  /**< Click config object. */

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

    digipot2_cfg_setup( &digipot2_cfg );
    DIGIPOT2_MAP_MIKROBUS( digipot2_cfg, MIKROBUS_1 );
    err_t init_flag  = digipot2_init( &digipot2, &digipot2_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_printf( &logger, "----------------\r\n" );
    log_printf( &logger, " DIGI POT 2 Click\r\n" );
    log_printf( &logger, "----------------\r\n" );
}

```

### Application Task

> This is an example which demonstrates the use of DIGI POT 2 Click board. Increments the wiper position by 10 positions every 5 seconds.

```c

void application_task ( void ) {
    for ( uint16_t n_cnt = 127; n_cnt < 255; n_cnt += 10 ) {
        wiper_pos = ( uint8_t ) n_cnt;
        digipot2_set_wiper_positions( &digipot2, wiper_pos );
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
- Click.DigiPot2

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
