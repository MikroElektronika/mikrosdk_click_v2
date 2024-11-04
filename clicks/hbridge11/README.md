\mainpage Main Page

---
# H-Bridge 11 Click

> H-Bridge 11 Click is a compact add-on board that allows a voltage to be applied across a load in either direction. This board features the MAX22200, an octal serial-controlled solenoid and motor driver from Analog Devices. The MAX22200 is SPI-configurable and rated for an operating voltage range from 4.5V to 36V. Each channel features a low impedance push-pull output stage with sink-and-source driving capability up to 1A RMS driving current. Its internal half-bridges can be configured as low-side or high-side drivers, supports two control methods (voltage and current drive regulation), and features a full set of protections and diagnostic functions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hbridge11_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/h-bridge-11-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the H-Bridge 11 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for H-Bridge 11 Click driver.

#### Standard key functions :

- `hbridge11_cfg_setup` Config Object Initialization function.
```c
void hbridge11_cfg_setup ( hbridge11_cfg_t *cfg );
```

- `hbridge11_init` Initialization function.
```c
err_t hbridge11_init ( hbridge11_t *ctx, hbridge11_cfg_t *cfg );
```

- `hbridge11_default_cfg` Click Default Configuration function.
```c
err_t hbridge11_default_cfg ( hbridge11_t *ctx );
```

#### Example key functions :

- `hbridge11_get_fault_pin` This function returns the fault pin logic state.
```c
uint8_t hbridge11_get_fault_pin ( hbridge11_t *ctx );
```

- `hbridge11_read_flags` This function reads and clears the fault flags from the status register.
```c
err_t hbridge11_read_flags ( hbridge11_t *ctx, uint8_t *fault_flags );
```

- `hbridge11_set_motor_state` This function sets the operating state for the selected motor from the half-bridge pairs 0-1, 2-3, 4-5, or 6-7.
```c
err_t hbridge11_set_motor_state ( hbridge11_t *ctx, uint8_t motor, uint8_t state );
```

## Example Description

> This example demonstrates the use of the H-Bridge 11 Click board by driving the DC motors connected between OUT0-OUT1 and OUT2-OUT3 in both directions. 

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge11_cfg_t hbridge11_cfg;  /**< Click config object. */

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
    hbridge11_cfg_setup( &hbridge11_cfg );
    HBRIDGE11_MAP_MIKROBUS( hbridge11_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == hbridge11_init( &hbridge11, &hbridge11_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HBRIDGE11_ERROR == hbridge11_default_cfg ( &hbridge11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Drives the motors connected between OUT0-OUT1 and OUT2-OUT3 in both directions in the span of 12 seconds, and logs data on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    hbridge11_set_motor_state ( &hbridge11, HBRIDGE11_MOTOR_SEL_0, HBRIDGE11_MOTOR_STATE_FORWARD );
    hbridge11_set_motor_state ( &hbridge11, HBRIDGE11_MOTOR_SEL_1, HBRIDGE11_MOTOR_STATE_FORWARD );
    log_printf( &logger, "\r\n MOTOR 0: FORWARD\r\n" );
    log_printf( &logger, " MOTOR 1: FORWARD\r\n" );
    hbridge11_check_fault ( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    hbridge11_set_motor_state ( &hbridge11, HBRIDGE11_MOTOR_SEL_0, HBRIDGE11_MOTOR_STATE_BRAKE );
    hbridge11_set_motor_state ( &hbridge11, HBRIDGE11_MOTOR_SEL_1, HBRIDGE11_MOTOR_STATE_BRAKE );
    log_printf( &logger, "\r\n MOTOR 0: BRAKE\r\n" );
    log_printf( &logger, " MOTOR 1: BRAKE\r\n" );
    hbridge11_check_fault ( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    hbridge11_set_motor_state ( &hbridge11, HBRIDGE11_MOTOR_SEL_0, HBRIDGE11_MOTOR_STATE_REVERSE );
    hbridge11_set_motor_state ( &hbridge11, HBRIDGE11_MOTOR_SEL_1, HBRIDGE11_MOTOR_STATE_REVERSE );
    log_printf( &logger, "\r\n MOTOR 0: REVERSE\r\n" );
    log_printf( &logger, " MOTOR 1: REVERSE\r\n" );
    hbridge11_check_fault ( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    hbridge11_set_motor_state ( &hbridge11, HBRIDGE11_MOTOR_SEL_0, HBRIDGE11_MOTOR_STATE_HI_Z );
    hbridge11_set_motor_state ( &hbridge11, HBRIDGE11_MOTOR_SEL_1, HBRIDGE11_MOTOR_STATE_HI_Z );
    log_printf( &logger, "\r\n MOTOR 0: DISCONNECTED\r\n" );
    log_printf( &logger, " MOTOR 1: DISCONNECTED\r\n" );
    hbridge11_check_fault ( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge11

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
