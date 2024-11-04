
---
# DC Motor 23 Click

> DC Motor 23 Click is a compact add-on board with a brushed DC motor driver. 
> This board features the TB67H480FNG, a dual-channel, H-bridge, brushed DC motor driver from Toshiba Semiconductor. 
> Fabricated with the BiCD process (DMOSFET is used for output power transistor), 
> it covers a wide operating voltage range of 8.2V to 44V with a maximum output current capacity of 2A. 
> It also offers many helpful features that support a robust and reliable operation, 
> like the decay modes selection function, several protection features, and one anomaly detection indicator.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dcmotor23_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/dc-motor-23-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the DC Motor 23 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DC Motor 23 Click driver.

#### Standard key functions :

- `dcmotor23_cfg_setup` Config Object Initialization function.
```c
void dcmotor23_cfg_setup ( dcmotor23_cfg_t *cfg );
```

- `dcmotor23_init` Initialization function.
```c
err_t dcmotor23_init ( dcmotor23_t *ctx, dcmotor23_cfg_t *cfg );
```

- `dcmotor23_default_cfg` Click Default Configuration function.
```c
err_t dcmotor23_default_cfg ( dcmotor23_t *ctx );
```

#### Example key functions :

- `dcmotor23_set_clockwise` DC Motor 23 set clockwise function.
```c
err_t dcmotor23_set_clockwise ( dcmotor23_t *ctx, uint8_t sel_motor );
```

- `dcmotor23_set_counter_clockwise` DC Motor 23 set counter clockwise function.
```c
err_t dcmotor23_set_counter_clockwise ( dcmotor23_t *ctx, uint8_t sel_motor );
```

- `dcmotor23_set_decay` DC Motor 23 set decay function.
```c
err_t dcmotor23_set_decay ( dcmotor23_t *ctx, uint8_t sel_motor );
```

## Example Description

> This example demonstrates the use of DC Motor 23 Click board™. 
> by driving the motors in both direction every 3 seconds.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration 
> which sets the output torque to 100%.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor23_cfg_t dcmotor23_cfg;  /**< Click config object. */

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
    dcmotor23_cfg_setup( &dcmotor23_cfg );
    DCMOTOR23_MAP_MIKROBUS( dcmotor23_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == dcmotor23_init( &dcmotor23, &dcmotor23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( DCMOTOR23_ERROR == dcmotor23_default_cfg ( &dcmotor23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf ( &logger, "--------------------------\r\n" );
}

```

### Application Task

> This example demonstrates the use of the DC Motor 23  Click board™.
> Drives the motors in the clockwise direction,
> after that decay the motors with a 3 seconds delay
> then switches to the counter-clockwise direction, 
> and decay the motors with a 3 seconds delay.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{    
    if ( DCMOTOR23_OK == dcmotor23_set_clockwise( &dcmotor23, DCMOTOR23_SEL_OUT_A ) )
    {
        log_printf ( &logger, " OUTA: Clockwise\r\n" );
    }
    if ( DCMOTOR23_OK == dcmotor23_set_clockwise( &dcmotor23, DCMOTOR23_SEL_OUT_B ) )
    {
        log_printf ( &logger, " OUTB: Clockwise\r\n\n" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    if ( DCMOTOR23_OK == dcmotor23_set_decay( &dcmotor23, DCMOTOR23_SEL_OUT_A ) )
    {
        log_printf ( &logger, " OUTA: Decay\r\n" );
    }
    if ( DCMOTOR23_OK == dcmotor23_set_decay( &dcmotor23, DCMOTOR23_SEL_OUT_B ) )
    {
        log_printf ( &logger, " OUTB: Decay\r\n\n" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    if ( DCMOTOR23_OK == dcmotor23_set_counter_clockwise( &dcmotor23, DCMOTOR23_SEL_OUT_A ) )
    {
        log_printf ( &logger, " OUTA: Counter-Clockwise\r\n" );
    }
    if ( DCMOTOR23_OK == dcmotor23_set_counter_clockwise( &dcmotor23, DCMOTOR23_SEL_OUT_B ) )
    {
        log_printf ( &logger, " OUTB: Counter-Clockwise\r\n\n" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    if ( DCMOTOR23_OK == dcmotor23_set_decay( &dcmotor23, DCMOTOR23_SEL_OUT_A ) )
    {
        log_printf ( &logger, " OUTA: Decay\r\n" );
    }
    if ( DCMOTOR23_OK == dcmotor23_set_decay( &dcmotor23, DCMOTOR23_SEL_OUT_B ) )
    {
        log_printf ( &logger, " OUTB: Decay\r\n\n" );
    }
    log_printf ( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor23

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
