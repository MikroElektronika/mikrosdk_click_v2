\mainpage Main Page

---
# CAN FD 7 Click

> CAN FD 7 Click is a compact add-on board that contains a CAN transceiver that supports both CAN and CAN FD protocols. This board features the TCAN1462, an automotive fault-protected CAN FD transceiver from Texas Instruments. It is a high-speed Controller Area Network (CAN) transceiver that meets the ISO 11898-2:2016 high-speed CAN specification and the CiA 601-4 signal improvement capability (SIC) specification.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/canfd7_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/can-fd-7-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2023.
- **Type**          : UART type


# Software Support

We provide a library for the CAN FD 7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for CAN FD 7 Click driver.

#### Standard key functions :

- `canfd7_cfg_setup` Config Object Initialization function.
```c
void canfd7_cfg_setup ( canfd7_cfg_t *cfg );
```

- `canfd7_init` Initialization function.
```c
err_t canfd7_init ( canfd7_t *ctx, canfd7_cfg_t *cfg );
```

- `canfd7_default_cfg` Click Default Configuration function.
```c
void canfd7_default_cfg ( canfd7_t *ctx );
```

#### Example key functions :

- `canfd7_generic_write` CAN FD 7 data writing function.
```c
err_t canfd7_generic_write ( canfd7_t *ctx, uint8_t *data_in, uint16_t len ) 
```

- `canfd7_generic_read` CAN FD 7 data reading function.
```c
err_t canfd7_generic_read ( canfd7_t *ctx, uint8_t *data_out, uint16_t len );
```

- `canfd7_set_stb_pin` CAN FD 7 set STB pin function.
```c
void canfd7_set_stb_pin ( canfd7_t *ctx, uint8_t pin_state );
```

## Example Description

> This example writes and reads and processes data from CAN FD 7 Click.
  The library also includes a function for selection of the output polarity.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    canfd7_cfg_t canfd7_cfg;  /**< Click config object. */

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
    canfd7_cfg_setup( &canfd7_cfg );
    CANFD7_MAP_MIKROBUS( canfd7_cfg, MIKROBUS_1 );
    if ( UART_ERROR == canfd7_init( &canfd7, &canfd7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    canfd7_default_cfg ( &canfd7 );
    
#ifdef DEMO_APP_TRANSMITTER
    log_info( &logger, "---- Transmitter mode ----" );
#else
    log_info( &logger, "---- Receiver mode ----" );
#endif 
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example contains Transmitter/Receiver task depending on uncommented code.
  Receiver logs each received byte to the UART for data logging,
  while the transmitter sends messages every 2 seconds.

```c
void application_task ( void ) 
{
#ifdef DEMO_APP_TRANSMITTER
    canfd7_generic_write( &canfd7, TX_MESSAGE, strlen( TX_MESSAGE ) );
    log_info( &logger, "---- Data sent ----" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    canfd7_process( &canfd7 );
#endif
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.CANFD7

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
