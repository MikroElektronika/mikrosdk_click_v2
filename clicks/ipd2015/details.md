
---
# IPD 2015 click

> IPD Click is a compact add-on board for controlling inductive and resistive loads in industrial automation and other demanding applications. This board features the TPD2015FN, an 8-channel high-side switch with MOSFET outputs from Toshiba Semiconductor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ipd2015_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ipd-click-tpd2015)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Nov 2023.
- **Type**          : GPIO type


# Software Support

We provide a library for the IPD 2015 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for IPD 2015 Click driver.

#### Standard key functions :

- `ipd2015_cfg_setup` Config Object Initialization function.
```c
void ipd2015_cfg_setup ( ipd2015_cfg_t *cfg );
```

- `ipd2015_init` Initialization function.
```c
err_t ipd2015_init ( ipd2015_t *ctx, ipd2015_cfg_t *cfg );
```

#### Example key functions :

- `ipd2015_all_pins_set` IPD 2015 pin setting function.
```c
void ipd2015_all_pins_set ( ipd2015_t *ctx );
```

- `ipd2015_set_out_level` IPD 2015 set output level function.
```c
err_t ipd2015_set_out_level ( ipd2015_t *ctx, uint8_t out_sel, uint8_t state );
```

- `ipd2015_get_out_state` IPD 2015 get output level function.
```c
uint8_t ipd2015_get_out_state ( ipd2015_t *ctx );
```

## Example Description

> This example demonstrates the use of IPD 2015 click board by toggling the output state.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ipd2015_cfg_t ipd2015_cfg;  /**< Click config object. */

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
    ipd2015_cfg_setup( &ipd2015_cfg );
    IPD2015_MAP_MIKROBUS( ipd2015_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == ipd2015_init( &ipd2015, &ipd2015_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Switches on all output pins state for 2 seconds, then switches them off, and turns them on one by one.

```c
void application_task ( void ) 
{
    log_printf( &logger, " Turning OUT 1 to OUT 4 HIGH \r\n" );
    ipd2015_all_pins_set( &ipd2015 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Turning OUT 1 to OUT 4 LOW \r\n" );
    ipd2015_all_pins_clear( &ipd2015 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Turning OUT 1 to OUT 4 one by one \r\n" );
    uint8_t out_sel = IPD2015_OUT1_PIN_MASK;
    do
    {
        ipd2015_set_out_level( &ipd2015, out_sel, IPD2015_PIN_STATE_HIGH );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        ipd2015_set_out_level( &ipd2015, out_sel, IPD2015_PIN_STATE_LOW );
        out_sel <<=  1;
    }
    while ( out_sel <= IPD2015_OUT4_PIN_MASK );
    
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.IPD2015

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
