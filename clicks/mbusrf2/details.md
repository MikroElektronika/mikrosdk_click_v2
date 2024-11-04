
---
# M-BUS RF 2  Click

> M-BUS RF 2 Click is a compact add-on board designed for utility metering and various telemetry applications. This board features the Metis-I (2605041183000), an 868MHz radio module from Würth Elektronik. It integrates an MSP430 microcontroller and a CC1101 RF chip-set to ensure efficient data transmission. Key features include a frequency range of 868.3MHz to 869.525MHz, support for the Wireless M-BUS EN13757-4:2013 and Open Metering System (OMS) standards, and communication capabilities up to 700 meters in clear conditions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mbusrf2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/m-bus-rf-2-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Nov 2023.
- **Type**          : UART type


# Software Support

We provide a library for the M-BUS RF 2  Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for M-BUS RF 2  Click driver.

#### Standard key functions :

- `mbusrf2_cfg_setup` Config Object Initialization function.
```c
void mbusrf2_cfg_setup ( mbusrf2_cfg_t *cfg );
```

- `mbusrf2_init` Initialization function.
```c
err_t mbusrf2_init ( mbusrf2_t *ctx, mbusrf2_cfg_t *cfg );
```

#### Example key functions :

- `mbusrf2_set_rst_pin` This function is used to set reset pin state.
```c
void mbusrf2_set_rst_pin ( mbusrf2_t *ctx, uint8_t pin_state );
```

- `mbusrf2_send_command` This function is used to send a desired command.
```c
err_t mbusrf2_send_command ( mbusrf2_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );
```

- `mbusrf2_send_data` This function is used to data in transmitter mode.
```c
err_t mbusrf2_send_data ( mbusrf2_t *ctx, uint8_t *data_in, uint8_t len );
```

## Example Description

> This example demonstrates the use of M-BUS RF 2 Click board by processing
  the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click configuration depending on selected DEMO_EXAMPLE macro.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mbusrf2_cfg_t mbusrf2_cfg;  /**< Click config object. */

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
    mbusrf2_cfg_setup( &mbusrf2_cfg );
    MBUSRF2_MAP_MIKROBUS( mbusrf2_cfg, MIKROBUS_1 );
    if ( UART_ERROR == mbusrf2_init( &mbusrf2, &mbusrf2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    mbusrf2_process( );
    mbusrf2_clear_app_buf( );
    Delay_ms ( 500 );
   
    mbusrf2_configure_for_example( );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example contains two examples depending on selected DEMO_EXAMPLE macro:
> EXAMPLE_TRANSMIT - Device is sending MESSAGE data to be read by receiver.
> EXAMPLE_RECEIVER - Device is reading transmitted message, and display it on USB UART terminal.

```c
void application_task ( void ) 
{
    mbusrf2_example( );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.MBUSRF2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
