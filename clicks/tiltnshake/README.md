\mainpage Main Page
 
---
# TILT-n-SHAKE click

> TILT-n-SHAKE click carries Freescale’s MMA8491Q IC. It’s a multifunctional 3-axis digital accelerometer that can also be configured as a 45-degree Tilt sensor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/tiltnshake_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/tilt-n-shake-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the TiltNshake Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TiltNshake Click driver.

#### Standard key functions :

- `tiltnshake_cfg_setup` Config Object Initialization function.
```c
void tiltnshake_cfg_setup ( tiltnshake_cfg_t *cfg ); 
```

- `tiltnshake_init` Initialization function.
```c
err_t tiltnshake_init ( tiltnshake_t *ctx, tiltnshake_cfg_t *cfg );
```

#### Example key functions :

- `tiltnshake_read_status_and_axis` Function for read status and axis
```c
void tiltnshake_read_status_and_axis ( tiltnshake_t *ctx, uint8_t *status, float *out_x, float *out_y, float *out_z )
```

- `tiltnshake_enable` Function for enabling chip
```c
void tiltnshake_enable ( tiltnshake_t *ctx );
```

- `tiltnshake_disable` Function for disabling chip
```c
void tiltnshake_disable ( tiltnshake_t *ctx );
```

## Example Description

> This application is multifunctional 3-axis digital accelerometer that can also be configured as a 45-degree Tilt sensor.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    tiltnshake_cfg_t cfg;

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
    tiltnshake_cfg_setup( &cfg );
    TILTNSHAKE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tiltnshake_init( &tiltnshake, &cfg );
    
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Reads 3-axis accelerometer measurement and logs results on the USB UART.

```c
void application_task ( )
{
    uint8_t status = 0;
    float out_x = 0;
    float out_y = 0;
    float out_z = 0;

    tiltnshake_enable( &tiltnshake );
    tiltnshake_read_status_and_axis( &tiltnshake, &status, &out_x, &out_y, &out_z );
    tiltnshake_disable( &tiltnshake );

    if ( TILTNSHAKE_DATA_READY == status )
    {
        log_printf( &logger, " X: %.2f\r\n", out_x );
        log_printf( &logger, " Y: %.2f\r\n", out_y );
        log_printf( &logger, " Z: %.2f\r\n", out_z );
        log_printf( &logger, "----------\r\n");
        Delay_ms( 500 );
    }
    Delay_ms( 500 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TiltNshake

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
