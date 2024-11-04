\mainpage Main Page

---
# H-Bridge 13 Click

> H-Bridge 13 Click is a compact add-on board with an H-bridge gate driver, also known as a full-bridge pre-driver. This board features the DRV8411A, a dual H-bridge motor driver with current regulations from Texas Instruments. It can drive one bipolar stepper motor, one or two brushed DC motors, solenoids, and other inductive loads.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hbridge13_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/h-bridge-13-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the H-Bridge 13 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for H-Bridge 13 Click driver.

#### Standard key functions :

- `hbridge13_cfg_setup` Config Object Initialization function.
```c
void hbridge13_cfg_setup ( hbridge13_cfg_t *cfg );
```

- `hbridge13_init` Initialization function.
```c
err_t hbridge13_init ( hbridge13_t *ctx, hbridge13_cfg_t *cfg );
```

- `hbridge13_default_cfg` Click Default Configuration function.
```c
err_t hbridge13_default_cfg ( hbridge13_t *ctx );
```

#### Example key functions :

- `hbridge13_write_reg` H-Bridge 13 write register function.
```c
err_t hbridge13_write_reg ( hbridge13_t *ctx, uint8_t reg, uint8_t data_out );
```

- `hbridge13_set_direction` H-Bridge 13 set direction function.
```c
err_t hbridge13_set_direction ( hbridge13_t *ctx, uint8_t dir_set, uint8_t speed );
```

- `hbridge13_get_an_voltage` H-Bridge 13 get xIPROPI voltage function.
```c
err_t hbridge13_get_an_voltage ( hbridge13_t *ctx, float *voltage, uint8_t an_sel );
```

## Example Description

> This example demonstrates the use of the H-Bridge 13 Click board by
  driving the motor connected to OUT A and OUT B, in both directions with braking and freewheeling.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge13_cfg_t hbridge13_cfg;  /**< Click config object. */

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
    hbridge13_cfg_setup( &hbridge13_cfg );
    HBRIDGE13_MAP_MIKROBUS( hbridge13_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hbridge13_init( &hbridge13, &hbridge13_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HBRIDGE13_ERROR == hbridge13_default_cfg ( &hbridge13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example is driving a motor in both directions with changes in speed and
  motor braking and freewheeling in between.

```c
void application_task ( void ) 
{
    for( uint8_t n_cnt = 0; n_cnt <= 100; n_cnt += 10 )
    {
        log_printf( &logger, " Motor in forward mode with speed of %d %% \r\n", ( uint16_t ) n_cnt );
        hbridge13_set_direction( &hbridge13, HBRIDGE13_DIR_FORWARD, n_cnt );
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " Motor brake is on \r\n" );
    hbridge13_set_brake( &hbridge13 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    for( uint8_t n_cnt = 0; n_cnt <= 100; n_cnt += 10 )
    {
        log_printf( &logger, " Motor in reverse with speed of %d %% \r\n", ( uint16_t ) n_cnt );
        hbridge13_set_direction( &hbridge13, HBRIDGE13_DIR_REVERSE, n_cnt );
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " Motor is coasting \r\n" );
    hbridge13_set_coast( &hbridge13 );
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
- Click.HBridge13

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
