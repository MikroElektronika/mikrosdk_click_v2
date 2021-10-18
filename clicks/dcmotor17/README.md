\mainpage Main Page

---
# DC Motor 17 click

DC Motor 17 Click is a compact add-on board that contains a brushed DC motor driver. This board features the TC78H660FTG,
a dual H Bridge driver for one or two brushed motors that incorporate a DMOS
with low on-resistance in output transistors from Toshiba Semiconductor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dcmotor17_click.png" height=300px width=auto>
</p>

[click Product page](https://www.mikroe.com/dc-motor-17-click?adtoken=48b980cc0840208867ff3317ac2fc531db4a1dd7&ad=mikromanage&id_employee=33)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the DcMotor17 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

```
This library contains API for DcMotor17 Click driver.
```

#### Standard key functions :

> Config Object Initialization function.
```
void dcmotor17_cfg_setup ( dcmotor17_cfg_t *cfg );
```

> Initialization function.
```
err_t dcmotor17_init ( dcmotor17_t *ctx, dcmotor17_cfg_t *cfg );
```

> Click Default Configuration function.
```
void dcmotor17_default_cfg ( dcmotor17_t *ctx );
```

#### Example key functions :

> DC Motor 17 stop motor function.
```
dcmotor17_retval_t dcmotor17_stop ( dcmotor17_t *ctx, uint8_t sel_out );
```

> DC Motor 17 forward function.
```
dcmotor17_retval_t dcmotor17_forward ( dcmotor17_t *ctx, uint8_t sel_out );
```

> DC Motor 17 reverse function.
```
dcmotor17_retval_t dcmotor17_reverse ( dcmotor17_t *ctx, uint8_t sel_out );
```

## Examples Description

> The library covers all the necessary functions to control DC Motor 17 Click board.
> Library performs a standard GPIO interface communication.
> DC Motor 17 Click board is a dual H Bridge driver IC for one or two DC brushed
> motors which incorporates DMOS with low on-resistance in output transistors.

**The demo application is composed of two sections :**

### Application Init

> Initializes GPIO driver, set default configuration and start to write log.

```
void application_init ( void ) {
    log_cfg_t log_cfg;              /**< Logger config object. */
    dcmotor17_cfg_t dcmotor17_cfg;  /**< Click config object. */

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
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "      DC Motor 17 click     \r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    dcmotor17_cfg_setup( &dcmotor17_cfg );
    DCMOTOR17_MAP_MIKROBUS( dcmotor17_cfg, MIKROBUS_1 );
    if ( dcmotor17_init( &dcmotor17, &dcmotor17_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    dcmotor17_default_cfg ( &dcmotor17 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This is an example that demonstrates the use of the DC Motor 17 click board.
> This example demonstrates the use of DC Motor 17 click,
> we first control motion A by driving it forward motion for 5 seconds,
> than applying short brakes it for 2 second, then driving it in reverse for 5 seconds
> and stop the motor for 2 seconds.
> In the second part of the example, we control motion B by the same principle.
> Results are being sent to the Usart Terminal where you can track their changes.

```
void application_task ( void ) {
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "          Motor A           \r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "  Start the motor forward.  \r\n" );
    dcmotor17_forward( &dcmotor17, DCMOTOR17_SEL_OUT_A );
    Delay_ms( 5000 );

    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "       Stop the motor.      \r\n" );
    dcmotor17_stop( &dcmotor17, DCMOTOR17_SEL_OUT_A );
    Delay_ms( 2000 );

    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "  Start the motor reverse.  \r\n" );
    dcmotor17_reverse( &dcmotor17, DCMOTOR17_SEL_OUT_A );
    Delay_ms( 5000 );

    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "       Stop the motor.      \r\n" );
    dcmotor17_stop( &dcmotor17, DCMOTOR17_SEL_OUT_A );
    Delay_ms( 2000 );

    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "          Motor B           \r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "  Start the motor forward.  \r\n" );
    dcmotor17_forward( &dcmotor17, DCMOTOR17_SEL_OUT_B );
    Delay_ms( 5000 );

    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "       Stop the motor.      \r\n" );
    dcmotor17_stop( &dcmotor17, DCMOTOR17_SEL_OUT_B );
    Delay_ms( 2000 );

    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "  Start the motor reverse.  \r\n" );
    dcmotor17_reverse( &dcmotor17, DCMOTOR17_SEL_OUT_B );
    Delay_ms( 5000 );

    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "       Stop the motor.      \r\n" );
    dcmotor17_stop( &dcmotor17, DCMOTOR17_SEL_OUT_B );
    Delay_ms( 2000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DcMotor17

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
