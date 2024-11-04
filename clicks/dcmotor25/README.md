\mainpage Main Page

---
# DC Motor 25 Click

> DC Motor 25 Click is a compact add-on board with a brushed DC motor driver. 
> This board features the A3908, a low-voltage bidirectional DC motor driver from Allegro Microsystems. 
> The A3908 is rated for an operating voltage range compatible with mikroBUS™ power rails and 
> output currents up to 500mA. The unique output full-bridge incorporates source-side linear operation 
> to allow a constant voltage across the motor coil. Logic input pins are provided 
> to control the motor direction of rotation, brake, and standby modes. 
> It also has complete protection capabilities supporting robust and reliable operation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dcmotor25_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/dc-motor-25-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the DC Motor 25 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DC Motor 25 Click driver.

#### Standard key functions :

- `dcmotor25_cfg_setup` Config Object Initialization function.
```c
void dcmotor25_cfg_setup ( dcmotor25_cfg_t *cfg );
```

- `dcmotor25_init` Initialization function.
```c
err_t dcmotor25_init ( dcmotor25_t *ctx, dcmotor25_cfg_t *cfg );
```

- `dcmotor25_default_cfg` Click Default Configuration function.
```c
err_t dcmotor25_default_cfg ( dcmotor25_t *ctx );
```

#### Example key functions :

- `dcmotor25_forward` DC Motor 25 set forward mode function.
```c
void dcmotor25_forward ( dcmotor25_t *ctx );
```

- `dcmotor25_reverse` DC Motor 25 set reverse mode function.
```c
void dcmotor25_reverse ( dcmotor25_t *ctx );
```

- `dcmotor25_brake` DC Motor 25 set brake mode function.
```c
void dcmotor25_brake ( dcmotor25_t *ctx );
```

## Example Description

> This example demonstrates the use of DC Motor 25 Click board™ 
> by driving the DC motor in both directions every 3 seconds.

**The demo application is composed of two sections :**

### Application Init

> Initializes the I2C drivernd and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor25_cfg_t dcmotor25_cfg;  /**< Click config object. */

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
    dcmotor25_cfg_setup( &dcmotor25_cfg );
    DCMOTOR25_MAP_MIKROBUS( dcmotor25_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == dcmotor25_init( &dcmotor25, &dcmotor25_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR25_ERROR == dcmotor25_default_cfg ( &dcmotor25 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the DC Motor 25 Click board™.
> Drives the motors in the forward and reverse direction 
> with a 3 seconds delay with engine braking between direction changes.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    log_printf ( &logger, " Forward\r\n" );
    dcmotor25_forward( &dcmotor25 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Brake\r\n" );
    dcmotor25_brake( &dcmotor25 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Reverse\r\n" );
    dcmotor25_reverse( &dcmotor25 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Brake\r\n" );
    dcmotor25_brake( &dcmotor25 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor25

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
