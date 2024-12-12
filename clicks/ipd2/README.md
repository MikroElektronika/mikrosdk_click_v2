\mainpage Main Page

---
# IPD 2 Click

> IPD 2 Click is a compact add-on board for efficient and reliable high-side switching in automotive applications. This board features the BV2HD070EFU-C, an automotive-grade two-channel high-side switch from ROHM Semiconductor with advanced protection and diagnostic functionalities. This 70mΩ on-resistance high-side switch supports an input voltage range from 6V to 28V and includes built-in protection mechanisms such as overcurrent detection, thermal shutdown, undervoltage lockout, and open load detection. Additionally, it offers configurable overcurrent limits and diagnostic output for real-time fault feedback, ensuring enhanced system reliability.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ipd2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ipd-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2024.
- **Type**          : GPIO type


# Software Support

We provide a library for the IPD 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for IPD 2 Click driver.

#### Standard key functions :

- `ipd2_cfg_setup` Config Object Initialization function.
```c
void ipd2_cfg_setup ( ipd2_cfg_t *cfg );
```

- `ipd2_init` Initialization function.
```c
err_t ipd2_init ( ipd2_t *ctx, ipd2_cfg_t *cfg );
```

#### Example key functions :

- `ipd2_enable_out1` This function enables OUT1 by setting the IN1 pin to high logic state.
```c
void ipd2_enable_out1 ( ipd2_t *ctx );
```

- `ipd2_disable_out1` This function disables OUT1 by setting the IN1 pin to low logic state.
```c
void ipd2_disable_out1 ( ipd2_t *ctx );
```

- `ipd2_get_st1_pin` This function returns the ST1 pin logic state.
```c
uint8_t ipd2_get_st1_pin ( ipd2_t *ctx );
```

## Example Description

> This example demonstrates the use of IPD 2 Click by toggling the output state.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ipd2_cfg_t ipd2_cfg;  /**< Click config object. */

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
    ipd2_cfg_setup( &ipd2_cfg );
    IPD2_MAP_MIKROBUS( ipd2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == ipd2_init( &ipd2, &ipd2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Toggles OUT1 and OUT2 state every 3 seconds and displays both outputs state and
status diagnostics pin state. If the status pin is HIGH it indicates that the fault
condition on this output has occurred and the output is disabled.

```c
void application_task ( void )
{
    ipd2_enable_out1 ( &ipd2 );
    ipd2_disable_out2 ( &ipd2 );
    Delay_ms ( 100 );
    log_printf( &logger, " OUT1: enabled\r\n" );
    log_printf( &logger, " OUT2: disabled\r\n" );
    log_printf( &logger, " ST1: %s\r\n", ( char * ) ( ipd2_get_st1_pin ( &ipd2 ) ? "high" : "low" ) );
    log_printf( &logger, " ST2: %s\r\n\n", ( char * ) ( ipd2_get_st2_pin ( &ipd2 ) ? "high" : "low" ) );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    ipd2_disable_out1 ( &ipd2 );
    ipd2_enable_out2 ( &ipd2 );
    Delay_ms ( 100 );
    log_printf( &logger, " OUT1: disabled\r\n" );
    log_printf( &logger, " OUT2: enabled\r\n" );
    log_printf( &logger, " ST1: %s\r\n", ( char * ) ( ipd2_get_st1_pin ( &ipd2 ) ? "high" : "low" ) );
    log_printf( &logger, " ST2: %s\r\n\n", ( char * ) ( ipd2_get_st2_pin ( &ipd2 ) ? "high" : "low" ) );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.IPD2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
