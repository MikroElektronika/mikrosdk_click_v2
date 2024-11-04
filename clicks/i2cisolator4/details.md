
---
# I2C Isolator 4 Click

> I2C Isolator 4 Click is a compact add-on board that offers completely isolated bidirectional communication. This board features the MAX14937, a two-channel, 5kVRMS I2C digital isolator from Analog Devices. The MAX14937 provides two bidirectional, open-drain channels for applications that require data to be transmitted in both directions on the same line. It supports data rates from DC up to 1.7MHz and can be used in isolated I2C busses with or without clock stretching.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/i2cisolator4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/i2c-isolator-4-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : May 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the I2cIsolator4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for I2cIsolator4 Click driver.

#### Standard key functions :

- `i2cisolator4_cfg_setup` Config Object Initialization function.
```c
void i2cisolator4_cfg_setup ( i2cisolator4_cfg_t *cfg );
```

- `i2cisolator4_init` Initialization function.
```c
err_t i2cisolator4_init ( i2cisolator4_t *ctx, i2cisolator4_cfg_t *cfg );
```

- `i2cisolator4_default_cfg` Click Default Configuration function.
```c
err_t i2cisolator4_default_cfg ( i2cisolator4_t *ctx );
```

#### Example key functions :

- `i2cisolator4_generic_write` I2C Isolator 4 I2C writing function.
```c
err_t i2cisolator4_generic_write ( i2cisolator4_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len )
```

- `i2cisolator4_generic_read` I2C Isolator 4 I2C reading function.
```c
err_t i2cisolator4_generic_read ( i2cisolator4_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );
```

- `i2cisolator4_set_slave_address` I2C Isolator 4 set I2C Slave address function.
```c
err_t i2cisolator4_set_slave_address ( i2cisolator4_t *ctx, uint8_t address );
```

## Example Description

> This library contains API for the I2C Isolator 4 Click driver.
> This demo application shows an example of an I2C Isolator 4 Click 
> wired to the VAV Press Click for reading 
> differential pressure and temperature measurement.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization and default settings, 
> the app set VAV Press Click I2C slave address ( 0x5C ) 
> and enable device.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;                    /**< Logger config object. */
    i2cisolator4_cfg_t i2cisolator4_cfg;  /**< Click config object. */

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

    i2cisolator4_cfg_setup( &i2cisolator4_cfg );
    I2CISOLATOR4_MAP_MIKROBUS( i2cisolator4_cfg, MIKROBUS_1 );
    err_t init_flag = i2cisolator4_init( &i2cisolator4, &i2cisolator4_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
    
    log_printf( &logger, "--------------------------------\r\n" );
    log_printf( &logger, "     Set I2C Slave Address      \r\n" );
    i2cisolator4_set_slave_address ( &i2cisolator4, I2CISOLATOR4_VAV_PRESS_DEV_ADDR );
    Delay_ms ( 100 );
}

```

### Application Task

> This is an example that shows the use of an I2C Isolator 4 Click board™.
> Logs pressure difference [ Pa ] and temperature [ degree Celsius ] values 
> of the VAV Press Click wired to the I2C Isolator 4 Click board™.  
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) {
    get_dif_press_and_temp( );
    log_printf( &logger, " Diff. Pressure    : %.4f Pa\r\n", diff_press );
    log_printf( &logger, " Temperature       : %.4f C\r\n", temperature );
    log_printf( &logger, "--------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

## Note

> Additional Function :

- `get_dif_press_and_temp` Get differential pressure [ Pa ] and temperature [ degree Celsius ] function. 
```c
void get_dif_press_and_temp ( void );
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.I2cIsolator4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
