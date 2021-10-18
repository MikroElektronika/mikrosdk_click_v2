\mainpage Main Page

---
# GNSS RTK click

> GNSS RTK Click is a compact add-on board made for positioning and wireless communication purposes. This board features the ZED-F9P, a multi-band GNSS module with integrated multi-band Real Time Kinematics (RTK) technology offering centimeter-level accuracy from U-blox.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gnssrtk_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gnss-rtk-click)

---


#### Click library

- **Author**        : Stefan Nikolic
- **Date**          : nov 2020.
- **Type**          : UART type


# Software Support

We provide a library for the GNSSRTK Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

```
This library contains API for GNSSRTK Click driver.
```

#### Standard key functions :

- Config Object Initialization function.
```
void gnssrtk_cfg_setup ( gnssrtk_cfg_t *cfg );
```

- Initialization function.
```
GNSSRTK_RETVAL gnssrtk_init ( gnssrtk_t *ctx, gnssrtk_cfg_t *cfg );
```

- Click Default Configuration function.
```
void gnssrtk_default_cfg ( gnssrtk_t *ctx );
```

#### Example key functions :

- Generic parser function.
```
gnssrtk_error_t gnssrtk_generic_parser ( char *rsp,  uint8_t command, uint8_t element, char *parser_buf );
```

- Generic read function.
```
err_t gnssrtk_generic_read ( gnssrtk_t *ctx, char *data_buf, uint16_t max_len );
```

- Module cold start function.
```
void gnssrtk_module_cold_start ( gnssrtk_t *ctx );
```

## Examples Description

This example reads and processes data from GNSS RTK click.

**The demo application is composed of two sections :**

### Application Init

Initializes driver and starts the module.

```
void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnssrtk_cfg_t gnssrtk_cfg;  /**< Click config object. */

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

    gnssrtk_cfg_setup( &gnssrtk_cfg );
    GNSSRTK_MAP_MIKROBUS( gnssrtk_cfg, MIKROBUS_1 );
    Delay_ms( 100 );
    err_t init_flag  = gnssrtk_init( &gnssrtk, &gnssrtk_cfg );
    if ( init_flag == UART_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    gnssrtk_default_cfg ( &gnssrtk );
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}
```

### Application Task

Reads the received data and parses it.

```
void application_task ( void ) {
    gnssrtk_process();
    parser_application( current_parser_buf );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSSRTK

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
