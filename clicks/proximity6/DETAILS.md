
---
# Proximity 6 Click

> Proximity 6 Click is a versatile proximity detection device on a Click board™.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/proximity6_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/proximity-6-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Proximity6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Proximity6 Click driver.

#### Standard key functions :

- `proximity6_cfg_setup` Config Object Initialization function.
```c
void proximity6_cfg_setup ( proximity6_cfg_t *cfg ); 
```

- `proximity6_init` Initialization function.
```c
err_t proximity6_init ( proximity6_t *ctx, proximity6_cfg_t *cfg );
```

- `proximity6_default_cfg` Click Default Configuration function.
```c
err_t proximity6_default_cfg ( proximity6_t *ctx );
```

#### Example key functions :

- `proximity6_read_data` Function reads proximity data when one or more data register is updated.
```c
err_t proximity6_read_data( proximity6_t *ctx, proximity6_data_t *axis_out );
```

- `proximity6_generic_write` This function writes data to the desired register.
```c
err_t proximity6_generic_write ( proximity6_t *ctx, uint8_t reg, uint16_t *data_buf, uint8_t len );
```

- `proximity6_generic_read` This function reads data from the desired register.
```c
err_t proximity6_generic_read ( proximity6_t *ctx, uint8_t reg, uint16_t *data_out, uint8_t len );
```

## Examples Description
 
> This application demonstrates the use of Proximity 6 Click board by reading and displaying the raw data measurements from 4 photodiode channels.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity6_cfg_t proximity6_cfg;  /**< Click config object. */

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
    proximity6_cfg_setup( &proximity6_cfg );
    PROXIMITY6_MAP_MIKROBUS( proximity6_cfg, MIKROBUS_1 );
    if ( PROXIMITY6_ERROR == proximity6_init( &proximity6, &proximity6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY6_ERROR == proximity6_default_cfg ( &proximity6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Reads the raw data measurements from 4 photodiode channels and displays the results on the USB UART every 200ms approximately.

```c

void application_task ( void )
{
    proximity6_data_t axis_data;
    if ( PROXIMITY6_OK == proximity6_read_data( &proximity6, &axis_data ) )
    {
        log_printf( &logger, " X1: %u\r\n", axis_data.val_x1 );
        log_printf( &logger, " X2: %u\r\n", axis_data.val_x2 );
        log_printf( &logger, " Y1: %u\r\n", axis_data.val_y1 );
        log_printf( &logger, " Y2: %u\r\n\n", axis_data.val_y2 );
        Delay_ms ( 200 );
    }
} 

```
 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity6

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
