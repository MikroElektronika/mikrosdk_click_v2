\mainpage Main Page

---
# Silent Step 2 click

> Silent Step 2 Click is a compact add-on board that allows extremely smooth and silent operation of the connected motor. This board features the TMC2130, a high-performance two-phase stepper motor driver from Analog Devices. The driver uses an external motor power supply of 4.75 up to 43V to power a 2-phase stepper motor up to 2A coil current (2.5A peak).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/silentstep2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/silent-step-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2023.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Silent Step 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Silent Step 2 Click driver.

#### Standard key functions :

- `silentstep2_cfg_setup` Config Object Initialization function.
```c
void silentstep2_cfg_setup ( silentstep2_cfg_t *cfg );
```

- `silentstep2_init` Initialization function.
```c
err_t silentstep2_init ( silentstep2_t *ctx, silentstep2_cfg_t *cfg );
```

- `silentstep2_default_cfg` Click Default Configuration function.
```c
err_t silentstep2_default_cfg ( silentstep2_t *ctx );
```

#### Example key functions :

- `silentstep2_rotate_by_angle` Silent Step 2 rotates the shaft through a desired angle function.
```c
err_t silentstep2_rotate_by_angle ( silentstep2_t *ctx, uint8_t step_speed, float angle, uint16_t res_360 );
```

- `silentstep2_set_direction` Silent Step 2 sets the clockwise or counterclockwise direction movement function.
```c
void silentstep2_set_direction ( silentstep2_t *ctx, uint8_t dir );
```

## Example Description

> This example demonstrates the use of Silent Step 2 Click board™ 
> by driving the motor in both directions for a desired rotation angle.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C and SPI module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    silentstep2_cfg_t silentstep2_cfg;  /**< Click config object. */

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
    silentstep2_cfg_setup( &silentstep2_cfg );
    SILENTSTEP2_MAP_MIKROBUS( silentstep2_cfg, MIKROBUS_1 );
    err_t init_flag = silentstep2_init( &silentstep2, &silentstep2_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SILENTSTEP2_ERROR == silentstep2_default_cfg ( &silentstep2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms( 100 );
}
```

### Application Task

> The application task represents an example that demonstrates 
> the use of the Silent Step 2 Click board™ with which the user can sequentially move the motor. 
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
    silentstep2_set_direction( &silentstep2, SILENTSTEP2_DIRECTION_CLOCKWISE );
    if ( SILENTSTEP2_OK == silentstep2_rotate_by_angle( &silentstep2, 50, 90, SILENTSTEP2_STEP_RES_200 ) )
    {
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms( 2000 );
    }
    
    log_printf( &logger, " Counterclockwise motion\r\n" );
    log_printf( &logger, " Angle of rotation :  180 deg\r\n" );
    log_printf( &logger, " Step speed        :  50 %%\r\n" );
    silentstep2_set_direction( &silentstep2, SILENTSTEP2_DIRECTION_COUNTERCLOCKWISE );
    if ( SILENTSTEP2_OK == silentstep2_rotate_by_angle( &silentstep2, 50, 180, SILENTSTEP2_STEP_RES_200 ) )
    {
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms( 2000 );
    }
    
    log_printf( &logger, " Clockwise motion\r\n" );
    log_printf( &logger, " Angle of rotation : 270 deg\r\n" );
    log_printf( &logger, " Step speed        :  50 %% \r\n" );
    silentstep2_set_direction( &silentstep2, SILENTSTEP2_DIRECTION_CLOCKWISE );
    if ( SILENTSTEP2_OK == silentstep2_rotate_by_angle( &silentstep2, 50, 270, SILENTSTEP2_STEP_RES_200 ) )
    {
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms( 2000 );
    }
    
    log_printf( &logger, " Counterclockwise motion\r\n" );
    log_printf( &logger, " Angle of rotation : 360 deg\r\n" );
    log_printf( &logger, " Step speed        : 90 %%\r\n" );
    silentstep2_set_direction( &silentstep2, SILENTSTEP2_DIRECTION_COUNTERCLOCKWISE );
    if ( SILENTSTEP2_OK == silentstep2_rotate_by_angle( &silentstep2, 90, 360, SILENTSTEP2_STEP_RES_200 ) )
    {
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms( 2000 );
    }
    
    log_printf( &logger, " Clockwise motion\r\n" );
    log_printf( &logger, " Angle of rotation : 360 deg\r\n" );
    log_printf( &logger, " Step speed        : 90 %% \r\n" );
    silentstep2_set_direction( &silentstep2, SILENTSTEP2_DIRECTION_CLOCKWISE );
    if ( SILENTSTEP2_OK == silentstep2_rotate_by_angle( &silentstep2, 90, 360, SILENTSTEP2_STEP_RES_200 ) )
    {
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms( 2000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SilentStep2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
