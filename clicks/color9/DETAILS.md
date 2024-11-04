# Color 9 Click

Color 9 Click is a very accurate color sensing Click board� which features the
APDS-9250, IR and ambient light sensor, from Broadcom. It contains a specially 
designed matrix of photosensitive elements, which can sense red, green,
blue and IR component.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/color9_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/color-9-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Color9 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Color9 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void color9_cfg_setup ( color9_cfg_t *cfg ); 
 
- Initialization function.
> COLOR9_RETVAL color9_init ( color9_t *ctx, color9_cfg_t *cfg );

#### Example key functions :

- This function gets Green measurement reading.
> uint32_t color9_get_green ( color9_t* ctx );
 
- This function gets Blue measurement reading.
> uint32_t color9_get_blue ( color9_t* ctx );

- This function gets Red measurement reading.
> uint32_t color9_get_red ( color9_t* ctx );

## Examples Description
 
> This example reads data from the sensor, and then logs IR, green, blue and red 
> measurements.


**The demo application is composed of two sections :**

### Application Init 

> Initialize the driver and test if the sensor is
> present. If the ID read from the sensor is correct
> execute the initialization procedure.


```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    color9_cfg_t cfg;

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

    color9_cfg_setup( &cfg );
    COLOR9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    color9_init( &color9, &cfg );

    ID = color9_read( &color9, COLOR9_PART_ID );

    if ( ID == 0xB2 )
    {
        log_printf( &logger, "Register ID 0x%x\r\n", ID );
        color9_meas_rate( &color9, COLOR9_LS_MEAS_BITWIDTH_13, COLOR9_LS_MEAS_RATE_1000ms );
        color9_reg_ctrl( &color9, COLOR9_MAIN_CTRL_CS_MODE | COLOR9_MAIN_CTRL_LS_EN );
    }
    else
    {
        log_printf( &logger, "Error\r\n" );
        while ( 1 );
    }
}
  
```

### Application Task

> Wait for the color data to be available then read the data
> and send it to the serial port.


```c

void application_task ( void )
{
    conv_complete = color9_get_status_reg( &color9 );

    if ( conv_complete & 0x08 )
    {
        conv_complete = 0;
        measurement_data = color9_get_Ir( &color9 );
        log_printf( &logger, "Ir: %d\r\n", measurement_data );

        
        measurement_data = color9_get_green( &color9 );
        log_printf(&logger, "Green: %d\r\n", measurement_data);

        measurement_data = color9_get_blue( &color9 );
        log_printf(&logger, "Blue: %d\r\n", measurement_data);

        measurement_data = color9_get_red( &color9 );
        log_printf(&logger, "Red: %d\r\n", measurement_data);

    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Color9

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