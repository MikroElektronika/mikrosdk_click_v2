
---
# DC Motor 19 Click

> DC Motor 19 Click is a compact add-on board that contains a brushed DC motor driver. This board features the TC78H653FTG, a dual H-bridge driver for one or two DC brushed motors or one stepping motor, which incorporates DMOS with low ON resistance in output transistors from Toshiba Semiconductor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dcmotor19_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/dc-motor-19-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2021.
- **Type**          : GPIO type


# Software Support

We provide a library for the DCMotor19 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DCMotor19 Click driver.

#### Standard key functions :

- `dcmotor19_cfg_setup` Config Object Initialization function.
```c
void dcmotor19_cfg_setup ( dcmotor19_cfg_t *cfg );
```

- `dcmotor19_init` Initialization function.
```c
err_t dcmotor19_init ( dcmotor19_t *ctx, dcmotor19_cfg_t *cfg );
```

#### Example key functions :

- `dcmotor19_drive_motor` This function drives the motor for a certian time specified by time_ms at the desired speed. The motor channel and mode must be previously selected using the dcmotor19_set_channel_mode function.
```c
err_t dcmotor19_drive_motor ( dcmotor19_t *ctx, uint8_t speed, uint32_t time_ms );
```

- `dcmotor19_set_channel_mode` This function sets the active channel and mode which will be used by the dcmotor19_drive_motor function.
```c
err_t dcmotor19_set_channel_mode ( dcmotor19_t *ctx, uint8_t channel, uint8_t mode );
```

- `dcmotor19_disable_standby_mode` This function disables the standby mode.
```c
void dcmotor19_disable_standby_mode ( dcmotor19_t *ctx );
```

## Example Description

> This example demonstrates the use of DC Motor 19 Click board by driving the motors in both direction in the span of 14 seconds.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and enables the Click by disabling the standby mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    dcmotor19_cfg_t dcmotor19_cfg;  /**< Click config object. */

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
    dcmotor19_cfg_setup( &dcmotor19_cfg );
    DCMOTOR19_MAP_MIKROBUS( dcmotor19_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == dcmotor19_init( &dcmotor19, &dcmotor19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    dcmotor19_disable_standby_mode ( &dcmotor19 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Drives the motors in the forward direction for 5 seconds, then pulls brake for 2 seconds, 
and after that drives them in the reverse direction for 5 seconds, and finally, 
stops driving for 2 seconds which basically disconnects the motors.
Each step will be logged on the USB UART where you can track the program flow.

```c

void application_task ( void )
{
    log_printf ( &logger, " Driving motors forward...\r\n" );
    dcmotor19_set_channel_mode ( &dcmotor19, DCMOTOR19_CHANNEL_1 | DCMOTOR19_CHANNEL_2, DCMOTOR19_MODE_FORWARD );
    dcmotor19_drive_motor ( &dcmotor19, DCMOTOR19_SPEED_DEFAULT, 5000 );
    log_printf ( &logger, " Pull brake!\r\n" );
    dcmotor19_set_channel_mode ( &dcmotor19, DCMOTOR19_CHANNEL_1 | DCMOTOR19_CHANNEL_2, DCMOTOR19_MODE_SHORT_BRAKE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf ( &logger, " Driving motors in reverse...\r\n" );
    dcmotor19_set_channel_mode ( &dcmotor19, DCMOTOR19_CHANNEL_1 | DCMOTOR19_CHANNEL_2, DCMOTOR19_MODE_REVERSE );
    dcmotor19_drive_motor ( &dcmotor19, DCMOTOR19_SPEED_DEFAULT, 5000 );
    log_printf ( &logger, " Stop driving!\r\n\n" );
    dcmotor19_set_channel_mode ( &dcmotor19, DCMOTOR19_CHANNEL_1 | DCMOTOR19_CHANNEL_2, DCMOTOR19_MODE_STOP );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor19

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
