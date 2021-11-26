\mainpage Main Page

---
# DC Motor 21 click

> DC Motor 21 Click is a compact add-on board that contains a brushed DC motor driver. This board features the A3910, a DC motor driver designed for low voltage power applications from Allegro Microsystems. It is controlled via several GPIO pins and has a wide operating voltage range with an output current capacity of 500mA. In addition to the possibility to be used in the full-bridge configuration to drive a single bidirectional DC motor, it can also be used as a dual half-bridge to drive dual DC motors.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dcmotor21_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dc-motor-21-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2021.
- **Type**          : GPIO type


# Software Support

We provide a library for the DCMotor21 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DCMotor21 Click driver.

#### Standard key functions :

- `dcmotor21_cfg_setup` Config Object Initialization function.
```c
void dcmotor21_cfg_setup ( dcmotor21_cfg_t *cfg );
```

- `dcmotor21_init` Initialization function.
```c
err_t dcmotor21_init ( dcmotor21_t *ctx, dcmotor21_cfg_t *cfg );
```

- `dcmotor21_default_cfg` Click Default Configuration function.
```c
void dcmotor21_default_cfg ( dcmotor21_t *ctx );
```

#### Example key functions :

- `dcmotor21_set_out_1` This function sets the state of output 1.
```c
void dcmotor21_set_out_1 ( dcmotor21_t *ctx, uint8_t state );
```

- `dcmotor21_set_out_2` This function sets the state of output 2.
```c
void dcmotor21_set_out_2 ( dcmotor21_t *ctx, uint8_t state );
```

## Example Description

> This example demonstrates the use of DC Motor 21 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor21_cfg_t dcmotor21_cfg;  /**< Click config object. */

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
    dcmotor21_cfg_setup( &dcmotor21_cfg );
    DCMOTOR21_MAP_MIKROBUS( dcmotor21_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == dcmotor21_init( &dcmotor21, &dcmotor21_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    dcmotor21_default_cfg ( &dcmotor21 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> In the span of six seconds, it drives the motor in one direction, then switches the direction, 
> and after that disconnects the motor. Each step will be logged on the USB UART where you can track the program flow.

```c

void application_task ( void )
{
    dcmotor21_set_out_1 ( &dcmotor21, DCMOTOR21_OUT_LOW );
    dcmotor21_set_out_2 ( &dcmotor21, DCMOTOR21_OUT_HIGH );
    log_printf( &logger, " \r\n Driving the motor...\r\n" );
    Delay_ms( 2000 );
    dcmotor21_set_out_1 ( &dcmotor21, DCMOTOR21_OUT_HIGH );
    dcmotor21_set_out_2 ( &dcmotor21, DCMOTOR21_OUT_LOW );
    log_printf( &logger, " Switch direction.\r\n" );
    Delay_ms( 2000 );
    dcmotor21_set_out_1 ( &dcmotor21, DCMOTOR21_OUT_HIGH_Z );
    dcmotor21_set_out_2 ( &dcmotor21, DCMOTOR21_OUT_HIGH_Z );
    log_printf( &logger, " The motor is disconnected.\r\n" );
    Delay_ms( 2000 );
}

```

## Note

> For this example, a DC motor should be connected to OUT1 and OUT2 lines.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor21

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
