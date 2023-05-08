\mainpage Main Page
 
---
# 3D Hall 2 click

3D Hall 2 click is a very accurate magnetic field sensing Click board™, used to sense the magnetic field strength in three perpendicular axes. It relies on a TLV493D-A1B6, a low power 3D magnetic sensor from Infineon. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/3dhall2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/3d-hall-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the 3d Hall 2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 3d Hall 2 Click driver.

#### Standard key functions :

- `c3dhall2_cfg_setup` Config Object Initialization function.
```c
void c3dhall2_cfg_setup ( c10x10rgb_cfg_t *cfg );
```

- `c3dhall2_init` Initialization function.
```c
err_t c3dhall2_init ( c3dhall2_t *ctx, c3dhall2_cfg_t *cfg );
```

- `c3dhall2_default_cfg` Default configuration initialization function.
```c
err_t c3dhall2_default_cfg( c3dhall2_t *ctx );
```

#### Example key functions :

- `c3dhall2_read_data` This function reads data from register.
```c
err_t c3dhall2_read_data ( c3dhall2_t *ctx, uint8_t *data_buf, uint16_t len );
```

- `c3dhall2_get_axis_temp_data` This function gets temperature and axis data.
```c
err_t c3dhall2_get_axis_temp_data ( c3dhall2_t *ctx, float *axis_data, float *temp_data );
```

- `c3dhall2_configuration` This function configures the chip for measurement.
```c
err_t c3dhall2_configuration ( c3dhall2_t *ctx, uint8_t settings1, uint8_t settings2 );
```

## Examples Description

> This example reads X/Y/Z hall axis and temperature data and converts it to human readable format.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and configures the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c3dhall2_cfg_t cfg;

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
    c3dhall2_cfg_setup( &cfg );
    C3DHALL2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3dhall2_init( &c3dhall2, &cfg );
    c3dhall2_default_cfg( &c3dhall2 );
}
  
```

### Application Task

> Reads X/Y/Z hall axis and Temperature data. All data logs on the USBUART every 200ms.

```c

void application_task ( void )
{
    float xyz_axis[ 3 ] = { 0 };
    float temperature = 0;
    if ( C3DHALL2_OK == c3dhall2_get_axis_temp_data( &c3dhall2, &xyz_axis[ 0 ], &temperature ) )
    {
        log_printf( &logger, " Axis X: %.2f mT\r\n", xyz_axis[ 0 ] );
        log_printf( &logger, " Axis Y: %.2f mT\r\n", xyz_axis[ 1 ] );
        log_printf( &logger, " Axis Z: %.2f mT\r\n", xyz_axis[ 2 ] );
        log_printf( &logger, " Temperature: %.2f C\r\n\n", temperature );
        Delay_ms( 200 );
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.3dHall2

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
