
---
# I2C Isolator 5 click

> I2C Isolator 5 Click is a compact add-on board that offers completely isolated bidirectional communication. This board features ISO1644, a hot-swappable bidirectional I2C isolator with enhanced EMC and GPIOs from Texas Instruments. The ISO1644 provides two bidirectional channels, supporting a completely isolated I2C interface that eliminates the need for splitting I2C signals into separate transmit and receive signals for use with standalone optocouplers.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/i2cisolator5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/i2c-isolator-5-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Apr 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the I2C Isolator 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for I2C Isolator 5 Click driver.

#### Standard key functions :

- `i2cisolator5_cfg_setup` Config Object Initialization function.
```c
void i2cisolator5_cfg_setup ( i2cisolator5_cfg_t *cfg );
```

- `i2cisolator5_init` Initialization function.
```c
err_t i2cisolator5_init ( i2cisolator5_t *ctx, i2cisolator5_cfg_t *cfg );
```

#### Example key functions :

- `i2cisolator5_set_slave_address` I2C Isolator 5 set I2C Slave address function.
```c
err_t i2cisolator5_set_slave_address ( i2cisolator5_t *ctx, uint8_t address );
```

- `i2cisolator5_set_outa_state` I2C Isolator 5 set output A state function.
```c
void i2cisolator5_set_outa_state ( i2cisolator5_t *ctx, uint8_t outa_state );
```

- `i2cisolator5_get_ina_state` I2C Isolator 5 get input A state function.
```c
uint8_t i2cisolator5_get_ina_state ( i2cisolator5_t *ctx );
```

## Example Description

> This library contains API for the I2C Isolator 5 click driver.
  This demo application shows an example of an I2C Isolator 5 click 
  wired to the VAV Press click for reading 
  differential pressure and temperature measurement.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
  After driver initialization and default settings, 
  the app set VAV Press click I2C slave address ( 0x5C ) 
  and enable device.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    i2cisolator5_cfg_t i2cisolator5_cfg;  /**< Click config object. */

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
    i2cisolator5_cfg_setup( &i2cisolator5_cfg );
    I2CISOLATOR5_MAP_MIKROBUS( i2cisolator5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == i2cisolator5_init( &i2cisolator5, &i2cisolator5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Set VAV Press Click I2C Slave Address \r\n" );
    i2cisolator5_set_slave_address ( &i2cisolator5, I2CISOLATOR5_VAV_PRESS_DEV_ADDR );
    Delay_ms( 100 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This is an example that shows the use of an I2C Isolator 5 click board™.
  Logs pressure difference [ Pa ] and temperature [ degree Celsius ] values 
  of the VAV Press click written to the I2C Isolator 5 click board™.  
  Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    if ( I2CISOLATOR5_OK == i2cisolator5_get_press_and_temp( ) )
    {
        log_printf( &logger, " Diff. Pressure : %.4f Pa \r\n", diff_press );
        log_printf( &logger, " Temperature : %.2f C \r\n", temperature );
        log_printf( &logger, "--------------------------------\r\n" );
    }
    
    Delay_ms( 2000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.I2CIsolator5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
