\mainpage Main Page

---
# IR Grid 3 click

IR Grid 3 click is a thermal imaging sensor. It has an array of 768 very sensitive, factory calibrated IR elements (pixels), arranged in 32 rows of 24 pixels, each measuring an object temperature up to 300˚C within its local Field of View (FOV). The MLX90640ESF-BAA IR sensor used on this Click board™ has only four pins, and it is mounted inside of the industry standard TO39 package. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/irgrid3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ir-grid-3-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the IRGrid3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for IRGrid3 Click driver.

#### Standard key functions :

- `irgrid3_cfg_setup` Config Object Initialization function.
```c
void irgrid3_cfg_setup ( irgrid3_cfg_t *cfg );
```

- `irgrid3_init` Initialization function.
```c
err_t irgrid3_init ( irgrid3_t *ctx, irgrid3_cfg_t *cfg );
```

- `irgrid3_default_cfg` Click Default Configuration function.
```c
void irgrid3_default_cfg ( irgrid3_t *ctx );
```

#### Example key functions :

- `irgrid3_generic_write` This function reads a desired number of data bytes starting from the selected register by using I2C serial interface.
```c
void irgrid3_generic_write ( irgrid3_t *ctx, uint16_t reg, uint8_t *data_buf, uint16_t len );
```

- `irgrid3_get_frame_data` This function is used for getting frame data.
```c
uint16_t irgrid3_get_frame_data ( irgrid3_t *ctx, uint16_t *frame_data );
```

- `irgrid3_get_pixel_temperature` This function is used for getting pixels temperature.
```c
void irgrid3_get_pixel_temperature ( irgrid3_t *ctx, float *temp_ambient, float *pixel_temp );
```

## Example Description

> The demo application displays a reading of ambient temperature and a 32x24 pixel object temperature matrix.

**The demo application is composed of two sections :**

### Application Init

> Configures the click and log objects and sets the click default configuration.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    irgrid3_cfg_t irgrid3_cfg;  /**< Click config object. */

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

    // Click initialization.
    irgrid3_cfg_setup( &irgrid3_cfg );
    IRGRID3_MAP_MIKROBUS( irgrid3_cfg, MIKROBUS_1 );
    err_t init_flag = irgrid3_init( &irgrid3, &irgrid3_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    irgrid3_default_cfg ( &irgrid3 );
    Delay_ms( 1000 );
    log_info( &logger, "---- Start measurement ----" );
}

```

### Application Task

> Reads the temperature of all pixels every 500ms and displays it on USB UART in a form of a 32x24 matrix.

```c

void application_task ( void ) {
    float px_matrix[ 768 ];
    float temp_ambient;

    irgrid3_get_pixel_temperature( &irgrid3, &temp_ambient, px_matrix );

    log_printf( &logger, "\r\n>> Pixel temperature matrix 32x24 <<\r\n" );
    for ( uint16_t cnt = 1 ; cnt < 769 ; cnt++) {
        log_printf( &logger, "%.2f", px_matrix[ cnt - 1 ] );
        if ( ( ( cnt % 32 ) == 0 ) ) {
            log_printf( &logger, "\r\n" );
        } else {
            log_printf( &logger, " | " );
        }
    }
    log_printf( &logger, "\r\n** Ambient (sensor) temperature is %.2f Celsius\r\n", temp_ambient );
    Delay_ms( 500 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.IRGrid3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
