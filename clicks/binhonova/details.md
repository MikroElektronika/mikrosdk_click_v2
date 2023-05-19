
---
# Binho Nova click

> Binho Nova Click is an adapter Click board™ that can be used as a multi-protocol adapter. This board features two female 1.27mm 2x5 connectors suitable for connecting the Binho Nova Multi-Protocol USB Host Adapter depending on the desired interface. This Click board™ is designed for ultimate flexibility and provides the ability to use this adapter with different communication protocols, such as I2C, SPI, or UART. It features five signal pins, which can be used as Digital Input/Output, PWM Output, Digital Interrupt, or Analog Input/Output. Along with these connectors, it also features two power jumpers that can be used to supply the host from the Binho Nova.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/binhonova_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/binho-nova-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : May 2023.
- **Type**          : UART type


# Software Support

We provide a library for the Binho Nova Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Binho Nova Click driver.

#### Standard key functions :

- `binhonova_cfg_setup` Config Object Initialization function.
```c
void binhonova_cfg_setup ( binhonova_cfg_t *cfg );
```

- `binhonova_init` Initialization function.
```c
err_t binhonova_init ( binhonova_t *ctx, binhonova_cfg_t *cfg );
```

#### Example key functions :

- `binhonova_generic_write` This function writes a desired number of data bytes by using UART serial interface.
```c
err_t binhonova_generic_write ( binhonova_t *ctx, uint8_t *data_in, uint16_t len );
```

- `binhonova_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t binhonova_generic_read ( binhonova_t *ctx, uint8_t *data_out, uint16_t len );
```

## Example Description

> This example demonstrates the use of Binho Nova click board by processing the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    binhonova_cfg_t binhonova_cfg;  /**< Click config object. */

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
    binhonova_cfg_setup( &binhonova_cfg );
    BINHONOVA_MAP_MIKROBUS( binhonova_cfg, MIKROBUS_1 );
    if ( UART_ERROR == binhonova_init( &binhonova, &binhonova_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 1000 );
    
    uart_set_blocking( &logger.uart, false );
}

```

### Application Task

> All data received from the USB UART will be forwarded to mikroBUS UART, and vice versa.

```c
void application_task ( void )
{
    app_buf_len = uart_read( &logger.uart, app_buf, PROCESS_BUFFER_SIZE );
    if ( app_buf_len > 0 ) 
    {
        uart_write ( &binhonova.uart, app_buf, app_buf_len );
        memset( app_buf, 0, app_buf_len );
        app_buf_len = 0;
    }
    app_buf_len = uart_read( &binhonova.uart, app_buf, PROCESS_BUFFER_SIZE );
    if ( app_buf_len > 0 ) 
    {
        uart_write ( &logger.uart, app_buf, app_buf_len );
        memset( app_buf, 0, app_buf_len );
        app_buf_len = 0;
    }
}
```

## Note

> The example code is performed via UART communication and consists of a few simple steps:
> 1. Place "Binho Nova Click" into the mikroBUS socket 1.
> 2. Insert the "Binho USB Host Adapter" connector into the "Binho Nova Click" I2C/UART slot.
> 3. Start the "Mission Control Software" application.
> 4. Connect "Binho USB Host Adapter".
> 5. Activate UART Bridge with a baud rate of 115200bps.
> 6. All data sent via the "Mission Control Software" application will be displayed on the USB UART logger, and vice versa.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.BinhoNova

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
