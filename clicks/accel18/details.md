
---
# Accel 18 click

> Accel 18 Click is a compact add-on board that contains an acceleration sensor. This board features the MC3419, a digital output 3-axis accelerometer with a feature set optimized for consumer product motion sensing from MEMSIC. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel_18_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/accel-18-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Aug 2021.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Accel18 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Accel18 Click driver.

#### Standard key functions :

- `accel18_cfg_setup` Config Object Initialization function.
```c
void accel18_cfg_setup ( accel18_cfg_t *cfg );
```

- `accel18_init` Initialization function.
```c
err_t accel18_init ( accel18_t *ctx, accel18_cfg_t *cfg );
```

- `accel18_default_cfg` Click Default Configuration function.
```c
err_t accel18_default_cfg ( accel18_t *ctx );
```

#### Example key functions :

- `accel18_read_axes` Accel data reading.
```c
err_t accel18_read_axes ( accel18_t *ctx, accel18_axes_t *axes_data );
```

- `accel18_set_range` Set range configuration.
```c
err_t accel18_set_range ( accel18_t *ctx, uint8_t range_macro );
```

- `accel18_get_interrupt_1` Get interrupt 1 pin state.
```c
uint8_t accel18_get_interrupt_1 ( accel18_t *ctx );
```

## Example Description

> This example application showcases ability of the device
to read axes values on detected interrupt, and check detected
motion.

**The demo application is composed of two sections :**

### Application Init

> Initialization of comunication modules(SPI/I2C, UART) and additional
two interrupt pins. Then configures device and sets 8g range and 25 
data rate, with interrupt enabled.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel18_cfg_t accel18_cfg;  /**< Click config object. */

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
    accel18_cfg_setup( &accel18_cfg );
    ACCEL18_MAP_MIKROBUS( accel18_cfg, MIKROBUS_1 );
    err_t init_flag  = accel18_init( &accel18, &accel18_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    if ( accel18_default_cfg ( &accel18 ) )
    {
        log_error( &logger, " Default configuration. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Whenever interrupt is detected checks interrupt status for motion
detection, and then reads x, y, and z axes, calculates value and
logs result.

```c

void application_task ( void )
{
    if ( !accel18_get_interrupt_1( &accel18 ) )
    {
        //Interrupt detected check
        uint8_t int_flag = 0;
        uint8_t interrupt_state = 0;
        accel18_byte_read( &accel18, ACCEL18_REG_INTERRUPT_STATUS, &interrupt_state );
        if ( interrupt_state & ACCEL18_INT_TILT_EN )
        {
            int_flag++;
            log_printf( &logger, ">Tilt<\t" );
        }
        if ( interrupt_state & ACCEL18_INT_FLIP_EN )
        {
            int_flag++;
            log_printf( &logger, ">Flip<\t" );
        }
        if ( interrupt_state & ACCEL18_INT_SHAKE_EN )
        {
            int_flag++;
            log_printf( &logger, ">Shake<\t" );
        }
        if ( int_flag )
        {
            log_printf( &logger, "\r\n" );
        }

        //Axis read
        accel18_axes_t axes_data;
        accel18_read_axes( &accel18, &axes_data );
        log_printf( &logger, " > X[g]: %.2f\r\n", axes_data.x );
        log_printf( &logger, " > Y[g]: %.2f\r\n", axes_data.y );
        log_printf( &logger, " > Z[g]: %.2f\r\n", axes_data.z );
        log_printf( &logger, "**************************\r\n" );
        Delay_ms( 300 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel18

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
