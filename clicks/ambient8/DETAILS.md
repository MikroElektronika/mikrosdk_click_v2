

---
# Ambient 8 Click

Ambient 8 Click is equipped with the ambient light sensor (ALS) IC, providing
measurements of the ambient light intensity in a digital format.
It utilizes the LTR-329ALS-01, an ALS with the I2C interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ambient8_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ambient-8-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Ambient8 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ambient8 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ambient8_cfg_setup ( ambient8_cfg_t *cfg ); 
 
- Initialization function.
> AMBIENT8_RETVAL ambient8_init ( ambient8_t *ctx, ambient8_cfg_t *cfg );

- Click Default Configuration function.
> void ambient8_default_cfg ( ambient8_t *ctx );


#### Example key functions :

- This function sets constants ( gain and integration time ) for lux level calculation.
> void ambient8_set_constants ( ambient8_t* ctx );
 
- This function checks for new data by polling ALS status register.
> AMBIENT8_RETVAL ambient8_get_als_data ( ambient8_t* ctx, uint16_t* als_data_ch1,uint16_t* als_data_ch0 );

- This function reads and data and performs lux level calculation
> AMBIENT8_RETVAL ambient8_get_lux_level ( ambient8_t* ctx, float* lux_level, float window_factor, float IR_factor );

## Examples Description

> This example collects data from the sensor, calculates the light intensity and then logs it. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes device and I2C driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient8_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ambient8_cfg_setup( &cfg );
    AMBIENT8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient8_init( &ambient8, &cfg );

    window_factor = 1.0;
    IR_factor = 0.0;
}
  
```

### Application Task

> Performs Lux calculation based on window and IR factor and log results.

```c

void application_task ( void )
{
    status_flag = ambient8_get_lux_level( &ambient8, &lux_level, window_factor, IR_factor );

    if ( status_flag == 0 )
    {
        log_printf( &logger, "Lux level : %.2f lx\r\n", lux_level );
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient8

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
