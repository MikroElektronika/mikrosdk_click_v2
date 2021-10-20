
---
# Shake2Wake click

Shake2Wake click carries an ADXL362 ultralow power, 3-axis MEMS accelerometer and ADP195 load switch. The distinguishing feature of this IC is that it incorporates several activity detection modes.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/shake2wake_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/shake-2-wake-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Shake2Wake Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Shake2Wake Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void shake2wake_cfg_setup ( shake2wake_cfg_t *cfg ); 
 
- Initialization function.
> SHAKE2WAKE_RETVAL shake2wake_init ( shake2wake_t *ctx, shake2wake_cfg_t *cfg );

- Click Default Configuration function.
> void shake2wake_default_cfg ( shake2wake_t *ctx );


#### Example key functions :

- This function is used to read 8-bit acceleration data per axis.
> void shake2wake_get_lo_res_raw_data ( shake2wake_t *ctx, int8_t *x_val, int8_t *y_val, int8_t *z_val );
 
- This function is used to read the 3-axis raw data from the accelerometer.
> void shake2wake_get_raw_data ( shake2wake_t *ctx, int16_t *x_val, int16_t *y_val, int16_t *z_val )

- This function is used to enable FIFO and mode selection.
> void shake2wake_set_fifo_mode ( shake2wake_t *ctx, uint8_t mode );

## Examples Description

> This app shows the capabilities of the Shake2Wake click by
> reading values of an accelerometer.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes device and applies default settings.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    shake2wake_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    shake2wake_cfg_setup( &cfg );
    SHAKE2WAKE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    shake2wake_init( &shake2wake, &cfg );

    Delay_ms( 100 );
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "    Shake2Wake  Click     \r\n" );
    log_printf( &logger, "--------------------------\r\n" );

    shake2wake_default_cfg( &shake2wake );
}
  
```

### Application Task

> This is an example that shows the capabilities of the Shake2Wake click by
> reading values of an accelerometer and logging them on USART terminal and, in case of an interrupt, it
> raises voltage on the connector.

```c

void application_task ( void )
{
    uint8_t temp_val;
    float temperature;
    int16_t x_val;
    int16_t y_val;
    int16_t z_val;

    shake2wake_get_raw_data( &shake2wake, &x_val, &y_val, &z_val );
    temperature = shake2wake_read_temperature( &shake2wake );

    log_printf( &logger, "X axis: %d\r\n", x_val );
    log_printf( &logger, "Y axis: %d\r\n", y_val );
    log_printf( &logger, "Z axis: %d\r\n", z_val );
    log_printf( &logger, "Temperature: %f \r\n", temperature );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Shake2Wake

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
