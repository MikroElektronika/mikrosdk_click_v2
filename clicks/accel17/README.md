\mainpage Main Page


---
# Accel 17 click

> Accel 17 Click is a compact add-on board that contains an acceleration sensor. This board features the MXC62320MP, a low-power digital output dual-axis accelerometer fabricated on a standard, submicron CMOS process from MEMSIC.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel17_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/accel-17-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Sep 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Accel17 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Accel17 Click driver.

#### Standard key functions :

- `accel17_cfg_setup` Config Object Initialization function.
```c
void accel17_cfg_setup ( accel17_cfg_t *cfg );
```

- `accel17_init` Initialization function.
```c
err_t accel17_init ( accel17_t *ctx, accel17_cfg_t *cfg );
```

- `accel17_default_cfg` Click Default Configuration function.
```c
err_t accel17_default_cfg ( accel17_t *ctx );
```

#### Example key functions :

- `accel17_get_axes_data` Accel data reading.
```c
err_t accel17_get_axes_data ( accel17_t *ctx, accel17_axes_t *axes );
```

- `accel17_generic_read` Reading function.
```c
err_t accel17_generic_read ( accel17_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );
```

- `accel17_generic_write` Writing function.
```c
err_t accel17_generic_write ( accel17_t *ctx, uint8_t reg, uint8_t tx_data );
```

## Example Description

> This example showcases ability of the device to read
x, y axis orientation.

**The demo application is composed of two sections :**

### Application Init

> Initialization of communication modules(I2C, UART), and
configures device.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel17_cfg_t accel17_cfg;  /**< Click config object. */

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
    accel17_cfg_setup( &accel17_cfg );
    ACCEL17_MAP_MIKROBUS( accel17_cfg, MIKROBUS_1 );
    err_t init_flag = accel17_init( &accel17, &accel17_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    accel17_default_cfg ( &accel17 );
    Delay_ms ( 1000 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads axis data and calculates it and logs result every 300ms.

```c

void application_task ( void ) 
{
    accel17_axes_t axes;
    accel17_get_axes_data ( &accel17, &axes );
    log_printf( &logger, " > X[degree]: %.2f\r\n > Y[degree]: %.2f\r\n", axes.x, axes.y );
    log_printf( &logger, "*********************************\r\n" );
    Delay_ms ( 300 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel17

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
