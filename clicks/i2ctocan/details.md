
---
# I2C to CAN click

I2C to CAN Click is a compact add-on board that contains I2C to CAN-physical transceiver, which extends a single-master I2C bus through harsh or noisy environments. This board features the LT3960, a robust high-speed transceiver that extends a single-master I2C bus up to 400kbps using the CAN-physical layer from Analog Devices. One LT3960 from SCL and SDA I2C lines creates equivalent differential buses (CAN) on two twisted pairs, while the second LT3960 recreates the I2C bus locally for any slave I2C devices on the other end of the twisted pairs. A built-in 3.3V LDO powers both the I2C and CAN lines from a single input supply from 4V to 60V. This Click board™ is suitable for industrial and automotive networking, remote sensor applications, and more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/i2ctocan_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/i2c-to-can-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the I2cToCan Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for I2cToCan Click driver.

#### Standard key functions :

- `i2ctocan_cfg_setup` Config Object Initialization function.
```c
void i2ctocan_cfg_setup ( i2ctocan_cfg_t *cfg );
```

- `i2ctocan_init` Initialization function.
```c
I2CTOCAN_RETVAL i2ctocan_init ( i2ctocan_t *ctx, i2ctocan_cfg_t *cfg );
```

- `i2ctocan_default_cfg` Click Default Configuration function.
```c
void i2ctocan_default_cfg ( i2ctocan_t *ctx );
```

#### Example key functions :

- `i2ctocan_set_slave_address` Set I2C Slave address function.
```c
I2CTOCAN_RETVAL i2ctocan_set_slave_address ( i2ctocan_t *ctx, uint8_t slave_addr );
```

- `i2ctocan_generic_write` I2C to CAN I2C writing function.
```c
I2CTOCAN_RETVAL i2ctocan_generic_write ( i2ctocan_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );
```

- `i2ctocan_generic_read` I2C to CAN I2C reading function.
```c
I2CTOCAN_RETVAL i2ctocan_generic_read ( i2ctocan_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );
```

## Example Description

> This library contains API for the I2C to CAN click driver.
> This demo application shows an example of an I2C CAN click 
> wired to the VAV Press click for reading 
> differential pressure and temperature measurement.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization and default settings, 
> the app set VAV Press click I2C slave address ( 0x5C ) 
> and enable device.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;            /**< Logger config object. */
    i2ctocan_cfg_t i2ctocan_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    i2ctocan_cfg_setup( &i2ctocan_cfg );
    I2CTOCAN_MAP_MIKROBUS( i2ctocan_cfg, MIKROBUS_1 );
    err_t init_flag = i2ctocan_init( &i2ctocan, &i2ctocan_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    i2ctocan_default_cfg ( &i2ctocan );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
    
    log_printf( &logger, "--------------------------------\r\n" );
    log_printf( &logger, "     Set I2C Slave Address      \r\n" );
    i2ctocan_set_slave_address ( &i2ctocan, I2CTOCAN_VAV_PRESS_DEV_ADDR );
    Delay_ms ( 100 );
    
    log_printf( &logger, "--------------------------------\r\n" );
    log_printf( &logger, "          Enable Device         \r\n" );
    log_printf( &logger, "--------------------------------\r\n" );
    i2ctocan_enable_device( &i2ctocan );
    Delay_ms ( 100 );
}

```

### Application Task

> This is an example that shows the use of an I2C to CAN click board™.
> Logs pressure difference [ Pa ] and temperature [ degree Celsius ] values 
> of the VAV Press click wired to the I2C to CAN click board™.  
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

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.I2cToCan

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
