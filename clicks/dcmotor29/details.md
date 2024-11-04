
---
# DC Motor 29 Click

> DC Motor 29 Click is a compact add-on board that contains a high-performance DC motor driver. This board features the DRV8245P, an automotive H-Bridge driver with integrated current sense and diagnostic from Texas Instruments. It can be configured as a single full-bridge driver or independent half-bridge driver. The driver offers excellent power handling and thermal capability due to a BiCMOS high power process technology mode, in which it is designed.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dcmotor29_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/dc-motor-29-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the DC Motor 29 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DC Motor 29 Click driver.

#### Standard key functions :

- `dcmotor29_cfg_setup` Config Object Initialization function.
```c
void dcmotor29_cfg_setup ( dcmotor29_cfg_t *cfg );
```

- `dcmotor29_init` Initialization function.
```c
err_t dcmotor29_init ( dcmotor29_t *ctx, dcmotor29_cfg_t *cfg );
```

- `dcmotor29_default_cfg` Click Default Configuration function.
```c
err_t dcmotor29_default_cfg ( dcmotor29_t *ctx );
```

#### Example key functions :

- `dcmotor29_register_write` DC Motor 29 data register writing function.
```c
err_t dcmotor29_register_write ( dcmotor29_t *ctx, uint8_t reg, uint8_t data_in );
```

- `dcmotor29_port_expander_read` DC Motor 29 port ecpander read register function.
```c
err_t dcmotor29_port_expander_read ( dcmotor29_t *ctx, uint8_t reg, uint8_t *data_out );
```

- `dcmotor29_drive_motor` DC Motor 29 drive motor function.
```c
err_t dcmotor29_drive_motor ( dcmotor29_t *ctx, uint8_t state );
```

## Example Description

> This example demonstrates the use of the DC Motor 29 Click board by driving the 
  motor in both directions with braking and coasting in between.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor29_cfg_t dcmotor29_cfg;  /**< Click config object. */

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
    dcmotor29_cfg_setup( &dcmotor29_cfg );
    DCMOTOR29_MAP_MIKROBUS( dcmotor29_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == dcmotor29_init( &dcmotor29, &dcmotor29_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR29_ERROR == dcmotor29_default_cfg ( &dcmotor29 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
       
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Drives the motor in both directions with coasting and braking in between, every sate is lasting 5 seconds.

```c
void application_task ( void )
{
    dcmotor29_drive_motor( &dcmotor29, DCMOTOR29_DRIVE_MOTOR_CW );
    log_printf( &logger, " Driving motor Clockwise \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    dcmotor29_drive_motor( &dcmotor29, DCMOTOR29_DRIVE_MOTOR_BRAKE );
    log_printf( &logger, " Brake is on \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    dcmotor29_drive_motor( &dcmotor29, DCMOTOR29_DRIVE_MOTOR_CCW );
    log_printf( &logger, " Driving motor counter-clockwise \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    dcmotor29_drive_motor( &dcmotor29, DCMOTOR29_DRIVE_MOTOR_COASTING );
    log_printf( &logger, " Driving motor Coasting \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor29

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
