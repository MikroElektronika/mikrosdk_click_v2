\mainpage Main Page

---
# Stepper 19 Click

> Stepper 19 Click is a compact add-on board for precise control over stepper motors. This board features the DRV8424, a stepper motor driver from Texas Instruments designed to drive both industrial and consumer stepper motors. The DRV8424 has dual N-channel power MOSFET H-bridge drivers, a microstepping indexer, and integrated current sensing, eliminating the need for external power sense resistors. Operating on a 5V to 30V external power supply, the DRV8424 can deliver up to 2.5A of full-scale output current, with an internal PWM current regulation scheme that includes smart tune, slow, and mixed decay options to optimize performance. Ideal for applications in multichannel system monitoring, robotics, precision positioning, and automated manufacturing processes, this Click board™ appears as a versatile solution for sophisticated stepper motor control.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepper19_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/stepper-19-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Stepper 19 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Stepper 19 Click driver.

#### Standard key functions :

- `stepper19_cfg_setup` Config Object Initialization function.
```c
void stepper19_cfg_setup ( stepper19_cfg_t *cfg );
```

- `stepper19_init` Initialization function.
```c
err_t stepper19_init ( stepper19_t *ctx, stepper19_cfg_t *cfg );
```

- `stepper19_default_cfg` Click Default Configuration function.
```c
err_t stepper19_default_cfg ( stepper19_t *ctx );
```

#### Example key functions :

- `stepper19_rotate_by_angle` This function rotates the shaft through a desired step speed and angle.
```c
err_t stepper19_rotate_by_angle ( stepper19_t *ctx, uint8_t step_speed, float angle, uint16_t res_360 );
```

- `stepper19_rotate_by_step` This function rotates the shaft through for the specific number of steps at the selected speed.
```c
err_t stepper19_rotate_by_step ( stepper19_t *ctx, uint8_t step_speed, uint16_t steps );
```

- `stepper19_set_direction` This function sets the desired direction of motor movement: clockwise or counterclockwise.
```c
err_t stepper19_set_direction ( stepper19_t *ctx, uint8_t dir );
```

## Example Description

> This example demonstrates the use of Stepper 19 Click board 
> by driving the motor in both directions for a desired rotation angle.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper19_cfg_t stepper19_cfg;  /**< Click config object. */

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
    stepper19_cfg_setup( &stepper19_cfg );
    STEPPER19_MAP_MIKROBUS( stepper19_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepper19_init( &stepper19, &stepper19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER19_ERROR == stepper19_default_cfg ( &stepper19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-----------------------------\r\n" );
}
```

### Application Task

> The application task represents an example that demonstrates 
> the use of the Stepper 19 Click board with which the user can sequentially move the motor. 
> The first part of the sequence executes the clockwise/counterclockwise motor movement 
> for an angle of 90 degrees with a step speed of 50%, 
> all the way to the last sequence of the same movement routine 
> of 360 degree angle with a step speed of 90%. 
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    log_printf( &logger, " Clockwise motion\r\n" );
    log_printf( &logger, " Angle of rotation :  90 degrees\r\n" );
    log_printf( &logger, " Step speed        :  50 %%\r\n" );
    stepper19_set_direction( &stepper19, STEPPER19_DIR_CLOCKWISE );
    if ( STEPPER19_OK == stepper19_rotate_by_angle( &stepper19, 50, 90, STEPPER19_STEP_RES_200 ) )
    {
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " Counterclockwise motion\r\n" );
    log_printf( &logger, " Angle of rotation :  180 deg\r\n" );
    log_printf( &logger, " Step speed        :  50 %%\r\n" );
    stepper19_set_direction( &stepper19, STEPPER19_DIR_COUNTERCLOCKWISE );
    if ( STEPPER19_OK == stepper19_rotate_by_angle( &stepper19, 50, 180, STEPPER19_STEP_RES_200 ) )
    {
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " Clockwise motion\r\n" );
    log_printf( &logger, " Angle of rotation : 270 deg\r\n" );
    log_printf( &logger, " Step speed        :  90 %% \r\n" );
    stepper19_set_direction( &stepper19, STEPPER19_DIR_CLOCKWISE );
    if ( STEPPER19_OK == stepper19_rotate_by_angle( &stepper19, 90, 270, STEPPER19_STEP_RES_200 ) )
    {
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " Counterclockwise motion\r\n" );
    log_printf( &logger, " Angle of rotation : 360 deg\r\n" );
    log_printf( &logger, " Step speed        : 90 %%\r\n" );
    stepper19_set_direction( &stepper19, STEPPER19_DIR_COUNTERCLOCKWISE );
    if ( STEPPER19_OK == stepper19_rotate_by_angle( &stepper19, 90, 360, STEPPER19_STEP_RES_200 ) )
    {
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " Clockwise motion\r\n" );
    log_printf( &logger, " Angle of rotation : 360 deg\r\n" );
    log_printf( &logger, " Step speed        : 90 %% \r\n" );
    stepper19_set_direction( &stepper19, STEPPER19_DIR_CLOCKWISE );
    if ( STEPPER19_OK == stepper19_rotate_by_angle( &stepper19, 90, 360, STEPPER19_STEP_RES_200 ) )
    {
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper19

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
