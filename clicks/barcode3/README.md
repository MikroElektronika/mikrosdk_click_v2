\mainpage Main Page

---
# Barcode 3 Click

> Barcode 3 Click is a compact add-on board for efficient barcode scanning applications. This board features the LV30, an advanced area image engine from Rakinda. The LV30 features a laser aiming system and LED illumination, ensuring quick and accurate barcode decoding on various media, including paper and magnetic cards. This module also includes a red LED for low-light conditions, a laser aimer for precise positioning, an onboard buzzer for audible feedback, buttons for scanning and resetting, and an LED indicator for successful reads.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/barcode3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/barcode-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2024.
- **Type**          : UART type


# Software Support

We provide a library for the Barcode 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Barcode 3 Click driver.

#### Standard key functions :

- `barcode3_cfg_setup` Config Object Initialization function.
```c
void barcode3_cfg_setup ( barcode3_cfg_t *cfg );
```

- `barcode3_init` Initialization function.
```c
err_t barcode3_init ( barcode3_t *ctx, barcode3_cfg_t *cfg );
```

#### Example key functions :

- `barcode3_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t barcode3_generic_read ( barcode3_t *ctx, uint8_t *data_out, uint16_t len );
```

- `barcode3_start_scanning` This function starts the barcode scanning by setting the TRG pin to low logic state.
```c
void barcode3_start_scanning ( barcode3_t *ctx );
```

- `barcode3_stop_scanning` This function stops the barcode scanning by setting the TRG pin to high logic state.
```c
void barcode3_stop_scanning ( barcode3_t *ctx );
```

## Example Description

> This example demonstrates the use of the Barcode 3 Click board by scanning and displaying the content of a barcode or QR Code.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, stops scanning and resets the barcode device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barcode3_cfg_t barcode3_cfg;  /**< Click config object. */

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
    barcode3_cfg_setup( &barcode3_cfg );
    BARCODE3_MAP_MIKROBUS( barcode3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == barcode3_init( &barcode3, &barcode3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    barcode3_stop_scanning ( &barcode3 );
    barcode3_reset_device ( &barcode3 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Triggers scanning and waits up to 3 seconds for the barcode to be detected.
If a barcode or QR Code is detected, it displays its content on the USB UART.

```c
void application_task ( void )
{
    uint16_t timeout = 0;
    log_printf( &logger, "\r\n------- SCAN START ------\r\n" );
    barcode3_start_scanning ( &barcode3 );
    while ( ++timeout < 3000 )
    {
        if ( BARCODE3_OK == barcode3_process( &barcode3 ) )
        {
            barcode3_log_app_buf( );
            barcode3_clear_app_buf( );
            Delay_10ms ( );
            while ( BARCODE3_OK == barcode3_process( &barcode3 ) )
            {
                barcode3_log_app_buf( );
                barcode3_clear_app_buf( );
                Delay_10ms ( );
            }
            break;
        }
        Delay_1ms ( );
    }
    log_printf( &logger, "------- SCAN STOP -------\r\n" );
    barcode3_stop_scanning ( &barcode3 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Barcode3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
