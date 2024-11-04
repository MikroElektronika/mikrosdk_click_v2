\mainpage Main Page

---
# Qi RX Click

> Qi RX Click is a compact add-on board made for the purpose of wireless power transfer. This board features the PIC16F15313, a general-purpose 8-bit MCU that makes a flexible, low-cost alternative to the wireless charging solutions based on ASICs from Microchip.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/qi_rx_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/qi-rx-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Oct 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the QiRX Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for QiRX Click driver.

#### Standard key functions :

- `qirx_cfg_setup` Config Object Initialization function.
```c
void qirx_cfg_setup ( qirx_cfg_t *cfg );
```

- `qirx_init` Initialization function.
```c
err_t qirx_init ( qirx_t *ctx, qirx_cfg_t *cfg );
```


#### Example key functions :

- `qirx_read_data` Read data function.
```c
uint16_t qirx_read_data ( qirx_t *ctx );
```

- `qirx_read_voltage` Read voltage function.
```c
uint16_t qirx_read_voltage ( qirx_t *ctx, uint16_t v_ref );
```

## Example Description

> This is an example that demonstrates the use of the Qi RX Click board.

**The demo application is composed of two sections :**

### Application Init

> Initalizes I2C driver and makes an initial log.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    qirx_cfg_t qirx_cfg;  /**< Click config object. */

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
    qirx_cfg_setup( &qirx_cfg );
    QIRX_MAP_MIKROBUS( qirx_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == qirx_init( &qirx, &qirx_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_printf( &logger, "----------------------- \r\n" );
    log_printf( &logger, "      Qi RX Click       \r\n" );
    log_printf( &logger, "----------------------- \r\n" );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "----------------------- \r\n" );
}

```

### Application Task

> This example shows the capabilities of the Qi RX Click by measuring voltage of the connected
> battery. In order to get correct calculations user should change "v_ref" value 
> to his own power supply voltage.

```c

void application_task ( void ) 
{
    voltage = qirx_read_voltage( &qirx, v_ref );
    log_printf( &logger, " Battery voltage: %d mV \r\n", voltage );
    log_printf( &logger, "----------------------- \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.QiRX

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
