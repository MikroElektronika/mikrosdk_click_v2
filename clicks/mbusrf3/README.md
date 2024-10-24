\mainpage Main Page

---
# M-BUS RF 3 click

> M-BUS RF 3 Click is a compact add-on board designed for utility metering and various telemetry applications. This board features the Metis-II (2607021183000), an 868MHz radio module from Würth Elektronik. It integrates an MSP430 microcontroller and a CC1125 RF chip-set to ensure efficient data transmission. Key features include a frequency range of 868.3MHz to 869.525MHz, support for the Wireless M-BUS EN13757-4:2013 and Open Metering System (OMS) standards, and communication capabilities up to 1000 meters in line-of-sight conditions. The board also offers energy-saving functionalities such as Wake-On-Radio, an output power of +14dBm output, and AES-128 encryption for secure communication.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mbusrf3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/m-bus-rf-3-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jan 2024.
- **Type**          : UART type


# Software Support

We provide a library for the M-BUS RF 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for M-BUS RF 3 Click driver.

#### Standard key functions :

- `mbusrf3_cfg_setup` Config Object Initialization function.
```c
void mbusrf3_cfg_setup ( mbusrf3_cfg_t *cfg );
```

- `mbusrf3_init` Initialization function.
```c
err_t mbusrf3_init ( mbusrf3_t *ctx, mbusrf3_cfg_t *cfg );
```

- `mbusrf3_default_cfg` Click Default Configuration function.
```c
err_t mbusrf3_default_cfg ( mbusrf3_t *ctx );
```

#### Example key functions :

- `mbusrf3_set_rst_pin` This function is used to set reset pin state.
```c
void mbusrf3_set_rst_pin ( mbusrf3_t *ctx, uint8_t pin_state );
```

- `mbusrf3_send_command` This function is used to send a desired command.
```c
err_t mbusrf3_send_command ( mbusrf3_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );
```

- `mbusrf3_send_data` This function is used to data in transmitter mode.
```c
err_t mbusrf3_send_data ( mbusrf3_t *ctx, uint8_t *data_in, uint8_t len );
```

## Example Description

> This example demonstrates the use of M-BUS RF 3 click board by processing
  the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click configuration depending on selected DEMO_EXAMPLE macro.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mbusrf3_cfg_t mbusrf3_cfg;  /**< Click config object. */

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
    mbusrf3_cfg_setup( &mbusrf3_cfg );
    MBUSRF3_MAP_MIKROBUS( mbusrf3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == mbusrf3_init( &mbusrf3, &mbusrf3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    mbusrf3_process( );
    mbusrf3_clear_app_buf( );
    Delay_ms ( 500 );
   
    mbusrf3_configure_for_example( );
    
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
    mbusrf3_example( );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.MBUSRF3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
