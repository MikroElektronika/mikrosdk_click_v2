
---
# DC Motor 20 Click

> DC Motor 20 Click is a compact add-on board that contains a brushed DC motor driver. This board features the TC78H651AFNG, a dual H-bridge driver for one or two DC brushed motors, which incorporates DMOS with low ON resistance in output transistors from Toshiba Semiconductor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dcmotor20_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/dc-motor-20-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2021.
- **Type**          : GPIO type


# Software Support

We provide a library for the DCMotor20 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DCMotor20 Click driver.

#### Standard key functions :

- `dcmotor20_cfg_setup` Config Object Initialization function.
```c
void dcmotor20_cfg_setup ( dcmotor20_cfg_t *cfg );
```

- `dcmotor20_init` Initialization function.
```c
err_t dcmotor20_init ( dcmotor20_t *ctx, dcmotor20_cfg_t *cfg );
```

#### Example key functions :

- `dcmotor20_drive_motor` This function drives the motor for a certian time specified by time_ms at the desired speed. 
```c
err_t dcmotor20_drive_motor ( dcmotor20_t *ctx, uint8_t speed, uint32_t time_ms );
```

- `dcmotor20_set_channel_mode` This function sets the active channel and mode which will be used by the dcmotor20_drive_motor function.
```c
err_t dcmotor20_set_channel_mode ( dcmotor20_t *ctx, uint8_t channel, uint8_t mode );
```

- `dcmotor20_set_standby_mode` This function sets the chip to the standby mode which affects both channels.
```c
void dcmotor20_set_standby_mode ( dcmotor20_t *ctx );
```

## Example Description

> This example demonstrates the use of DC Motor 20 Click board by driving the motors in both direction in the span of 14 seconds.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and sets the Click board to standby mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    dcmotor20_cfg_t dcmotor20_cfg;  /**< Click config object. */

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
    dcmotor20_cfg_setup( &dcmotor20_cfg );
    DCMOTOR20_MAP_MIKROBUS( dcmotor20_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == dcmotor20_init( &dcmotor20, &dcmotor20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    dcmotor20_set_standby_mode ( &dcmotor20 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Drives the motors in the forward direction for 5 seconds, and then switches the direction, with a brake time of 2 seconds between switching the direction.
Each step will be logged on the USB UART where you can track the program flow.

```c

void application_task ( void )
{
    log_printf ( &logger, " Driving motors forward...\r\n" );
    dcmotor20_set_channel_mode ( &dcmotor20, DCMOTOR20_CHANNEL_1 | DCMOTOR20_CHANNEL_2, DCMOTOR20_MODE_FORWARD );
    dcmotor20_drive_motor ( &dcmotor20, DCMOTOR20_SPEED_DEFAULT, 5000 );
    log_printf ( &logger, " Pull brake!\r\n" );
    dcmotor20_set_standby_mode ( &dcmotor20 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf ( &logger, " Driving motors in reverse...\r\n" );
    dcmotor20_set_channel_mode ( &dcmotor20, DCMOTOR20_CHANNEL_1 | DCMOTOR20_CHANNEL_2, DCMOTOR20_MODE_REVERSE );
    dcmotor20_drive_motor ( &dcmotor20, DCMOTOR20_SPEED_DEFAULT, 5000 );
    log_printf ( &logger, " Pull brake!\r\n\n" );
    dcmotor20_set_standby_mode ( &dcmotor20 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor20

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
