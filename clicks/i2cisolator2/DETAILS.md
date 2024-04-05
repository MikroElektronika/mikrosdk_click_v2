
---
# I2C Isolator 2 click

> I2C Isolator 2 click provides I2C lines and power isolation for slave devices. It carries the ADM3260 dual I2C isolator with an integrated DC-to-DC converter. I2C Isolator 2 click is designed to run on either 3.3V or 5V power supply.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/i2cisolator2_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/i2c-isolator-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the I2CIsolator2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for I2CIsolator2 Click driver.

#### Standard key functions :

- `i2cisolator2_cfg_setup` Config Object Initialization function.
```c
void i2cisolator2_cfg_setup ( i2cisolator2_cfg_t *cfg ); 
```

- `i2cisolator2_init` Initialization function.
```c
err_t i2cisolator2_init ( i2cisolator2_t *ctx, i2cisolator2_cfg_t *cfg );
```

- `i2cisolator2_enable_power` This function sets PDIS pin state.
```c
void i2cisolator2_enable_power ( i2cisolator2_t *ctx, uint8_t state );
```

#### Example key functions :

- `i2cisolator2_write` This function writes a desired data to I2C bus.
```c
err_t i2cisolator2_write ( i2cisolator2_t *ctx, uint8_t *data_in, uint16_t len );
```

- `i2cisolator2_read` This function reads a desired number of data bytes from I2C bus.
```c
err_t i2cisolator2_read ( i2cisolator2_t *ctx, uint8_t *data_out, uint16_t len );
```

- `i2cisolator2_set_slave_address` This function sets the slave address.
```c
err_t i2cisolator2_set_slave_address ( i2cisolator2_t *ctx, uint8_t slave_addr );
```

## Examples Description

> This example showcases how to initialize, configure and use the I2C Isolator 2 click module.
> The click provides I2C lines and power isolation for slave devices. In order for this 
> example to work, you need the EEPROM 3 click.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and enables the power output.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    i2cisolator2_cfg_t cfg;

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
    i2cisolator2_cfg_setup( &cfg );
    I2CISOLATOR2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cisolator2_init( &i2cisolator2, &cfg );
    
    i2cisolator2_enable_power( &i2cisolator2, I2CISOLATOR2_POWER_ENABLE );
    Delay_ms ( 100 );

    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Writes the desired message to EEPROM 3 click board and reads it back every 2 seconds.
> All data is being displayed on the USB UART where you can track the program flow.

```c

void application_task ( void )
{
    uint8_t read_buf[ 100 ] = { 0 };
    if ( I2CISOLATOR2_OK == eeprom3_write_page ( EEPROM3_MEMORY_ADDRESS, EEPROM3_DEMO_TEXT, 
                                                 strlen( EEPROM3_DEMO_TEXT ) ) )
    {
        log_printf( &logger, " Demo text message is written to EEPROM 3 click!\r\n" );
    }
    Delay_ms ( 1000 );
    
    if ( I2CISOLATOR2_OK == eeprom3_read_page ( EEPROM3_MEMORY_ADDRESS, read_buf, 
                                                strlen( EEPROM3_DEMO_TEXT ) ) )
    {
        read_buf[ strlen( EEPROM3_DEMO_TEXT ) ] = 0;
        log_printf( &logger, " Read data: \"%s\"\r\n\n", read_buf );
    }
    Delay_ms ( 1000 );
}  

``` 

## Note

> Make sure to provide the VCC power supply on VCC pin and EEPROM 3 click.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.I2CIsolator2

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
