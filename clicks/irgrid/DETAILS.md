 
---
# IR Grid click

IR Grid click is a thermal imaging sensor. It has an array of 64 very sensitive factory calibrated IR elements (pixels), arranged in 4 rows of 16 pixels, each measuring an object temperature up to 300˚C within its local Field of View (FOV). The MLX90621ESF-BAD IR sensor used on this Click board™ has only four pins, and it is mounted inside of the industry standard TO39 package. It is equipped with 2Kbit of EEPROM for storing the compensation and calibration parameters.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/irgrid_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/ir-grid-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : maj 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the IrGrid Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for IrGrid Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void irgrid_cfg_setup ( irgrid_cfg_t *cfg ); 
 
- Initialization function.
> IRGRID_RETVAL irgrid_init ( irgrid_t *ctx, irgrid_cfg_t *cfg );


#### Example key functions :

- Measures temperature and places it inside internal buffers. This function is 
- needed to be called prior to `irgrid_get_ir_raw` or `irgrid_get_temperature`.
> uint8_t irgrid_measure ( irgrid_t *ctx, irgrid_data_t *data_str );
 
- Populates provided buffer with calculated temperatures. Buffer must have at least 64 members.
> void irgrid_get_temperature ( irgrid_data_t *data_str, float *buffer );

- Read function using EEPROM slave adress.
> void irgrid_read_eeprom ( irgrid_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

## Examples Description

> IR Grid click is a thermal imaging sensor. It has an array of 64 very sensitive factory 
> calibrated IR elements (pixels), arranged in 4 rows of 16 pixels, each measuring an 
> object temperature up to 300˚C. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init and IR Grid module

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irgrid_cfg_t irgrid_cfg;  /**< Click config object. */

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
    irgrid_cfg_setup( &irgrid_cfg );
    IRGRID_MAP_MIKROBUS( irgrid_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == irgrid_init( &irgrid, &irgrid_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    irgrid_device_init( &irgrid, &irgrid_data, 16 );
    
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Reads the temperature of all pixels and creates a pixel temperature matrix that logs 
> on usbuart every half of second

```c

void application_task ( void )
{    
    if ( 1 != irgrid_measure( &irgrid, &irgrid_data ) )
    {
        irgrid_get_temperature( &irgrid_data, &ir_tmp[ 0 ] );
    }

    for ( rc = 0; rc < 4; rc++ )
    {
        for ( cc = 0; cc < 16; cc++ )
        {
            i = ( cc * 4 ) + rc;
            log_printf( &logger, "%.3f    ", ir_tmp[ i ] );
        }
        log_printf( &logger, "\r\n" );
        Delay_ms( 100 );
    }
    
    log_printf( &logger, "\r\n" );
    log_printf( &logger, "\r\n" );
    log_printf( &logger, "\r\n" );
    Delay_ms( 500 );
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.IrGrid

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
