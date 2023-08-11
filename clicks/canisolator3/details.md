
---
# CAN Isolator 3 click

> CAN Isolator 3 Click is a compact add-on board that provides isolated CAN communication. This board features the MAX14882, an isolated CAN transceiver with an integrated transformer driver from Analog Devices. It is galvanically isolated between the device's CAN-protocol controller side (TDX, RDX) and the physical wires of the CAN network (CANH, CANL) cable-side/bus-side of the transceiver.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/canisolator3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/can-isolator-3-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2023.
- **Type**          : UART type


# Software Support

We provide a library for the CAN Isolator 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for CAN Isolator 3 Click driver.

#### Standard key functions :

- `canisolator3_cfg_setup` Config Object Initialization function.
```c
void canisolator3_cfg_setup ( canisolator3_cfg_t *cfg );
```

- `canisolator3_init` Initialization function.
```c
err_t canisolator3_init ( canisolator3_t *ctx, canisolator3_cfg_t *cfg );
```

- `canisolator3_default_cfg` Click Default Configuration function.
```c
err_t canisolator3_default_cfg ( canisolator3_t *ctx );
```

#### Example key functions :

- `canisolator3_generic_write` CAN Isolator 3 data writing function.
```c
err_t canisolator3_generic_write ( canisolator3_t *ctx, uint8_t *data_in, uint16_t len );
```

- `canisolator3_generic_read` CAN Isolator 3 data reading function.
```c
err_t canisolator3_generic_read ( canisolator3_t *ctx, uint8_t *data_out, uint16_t len );
```

- `canisolator3_set_pol_pin` CAN Isolator 3 set polarity function.
```c
void canisolator3_set_pol_pin ( canisolator3_t *ctx, uint8_t pin_state );
```

## Example Description

> This example writes and reads and processes data from CAN Isolator 3 Click.
  The library also includes a function for selection of the output polarity.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    canisolator3_cfg_t canisolator3_cfg;  /**< Click config object. */

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
    canisolator3_cfg_setup( &canisolator3_cfg );
    CANISOLATOR3_MAP_MIKROBUS( canisolator3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == canisolator3_init( &canisolator3, &canisolator3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    canisolator3_default_cfg ( &canisolator3 );
    
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
    canisolator3_generic_write( &canisolator3, TX_MESSAGE, strlen( TX_MESSAGE ) );
    log_info( &logger, "---- Data sent ----" );
    Delay_ms( 2000 );
#else
    canisolator3_process( &canisolator3 );
#endif
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.CANIsolator3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
