
---
# DC Motor 15 Click

DC Motor 15 Click is a compact add-on board that contains a motor driver with current sense and regulation. This board features the DRV8874, an integrated motor driver with N-channel H-bridge, charge pump, current sensing, and adjustment from Texas Instruments. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dcmotor15_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/dc-motor-15-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2021.
- **Type**          : ADC type


# Software Support

We provide a library for the DCMotor15 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DCMotor15 Click driver.

#### Standard key functions :

- `dcmotor15_cfg_setup` Config Object Initialization function.
```c
void dcmotor15_cfg_setup ( dcmotor15_cfg_t *cfg );
```

- `dcmotor15_init` Initialization function.
```c
DCMOTOR15_RETVAL dcmotor15_init ( dcmotor15_t *ctx, dcmotor15_cfg_t *cfg );
```

- `dcmotor15_default_cfg` Click Default Configuration function.
```c
void dcmotor15_default_cfg ( dcmotor15_t *ctx );
```

#### Example key functions :

- `dcmotor15_forward` This function drives the motor forward.
```c
void dcmotor15_forward ( dcmotor15_t *ctx );
```

- `dcmotor15_reverse` This function drives the motor in reverse.
```c
void dcmotor15_reverse ( dcmotor15_t *ctx );
```

- `dcmotor15_get_current` This function reads the motor current consumption by performing analog to digital read of IPR pin.
```c
float dcmotor15_get_current ( dcmotor15_t *ctx, uint16_t num_of_conv );
```

## Example Description

> This example demonstrates the use of DC Motor 15 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    dcmotor15_cfg_t dcmotor15_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    dcmotor15_cfg_setup( &dcmotor15_cfg );
    DCMOTOR15_MAP_MIKROBUS( dcmotor15_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == dcmotor15_init( &dcmotor15, &dcmotor15_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    dcmotor15_default_cfg ( &dcmotor15 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Drives the motor in the forward direction for 5 seconds, then pulls brake for 2 seconds, 
> and after that drives it in the reverse direction for 5 seconds, and finally, 
> disconnects the motor for 2 seconds. It will also calculates and displays the motor current consumption.
> Each step will be logged on the USB UART where you can track the program flow.

```c

void application_task ( void )
{
    log_printf( &logger, " The motor turns forward! \r\n" );
    dcmotor15_forward( &dcmotor15 );
    display_current ( &dcmotor15, RUN_PERIOD );
    log_printf( &logger, " Pull brake! \r\n" );
    dcmotor15_brake( &dcmotor15 );
    display_current ( &dcmotor15, IDLE_PERIOD );
    log_printf( &logger, " The motor turns in reverse! \r\n" );
    dcmotor15_reverse( &dcmotor15 );
    display_current ( &dcmotor15, RUN_PERIOD );
    log_printf( &logger, " The motor is disconnected (High-Z)!  \r\n" );
    dcmotor15_stop( &dcmotor15 );
    display_current ( &dcmotor15, IDLE_PERIOD );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor15

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
