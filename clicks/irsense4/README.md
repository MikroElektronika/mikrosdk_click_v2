\mainpage Main Page

---
# IR Sense 4 click

> IR Sense 4 Click is a compact add-on board that can be used in short-range IR sensing applications. This board features the STHS34PF80, a low-power high-sensitivity infrared (IR) sensor from STMicroelectronics. It is a sensor for presence and motion detection and can reach up to 4m without a lens for object measuring. The sensor can detect stationary objects and distinguish them from moving objects.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/irsense4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ir-sense-4-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jun 2023.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the IR Sense 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for IR Sense 4 Click driver.

#### Standard key functions :

- `irsense4_cfg_setup` Config Object Initialization function.
```c
void irsense4_cfg_setup ( irsense4_cfg_t *cfg );
```

- `irsense4_init` Initialization function.
```c
err_t irsense4_init ( irsense4_t *ctx, irsense4_cfg_t *cfg );
```

- `irsense4_default_cfg` Click Default Configuration function.
```c
err_t irsense4_default_cfg ( irsense4_t *ctx );
```

#### Example key functions :

- `irsense4_get_presence_data` IR Sense 4 get the presence detection data function.
```c
err_t irsense4_get_presence_data ( irsense4_t *ctx, int16_t *presence );
```

- `irsense4_get_motion_data` IR Sense 4 get the motion detection data function.
```c
err_t irsense4_get_motion_data ( irsense4_t *ctx, int16_t *motion );
```

- `irsense4_get_amb_temperature` IR Sense 4 get the ambient temperature function.
```c
err_t irsense4_get_amb_temperature ( irsense4_t *ctx, float *temperature );
```

## Example Description

> This example demonstrates the use of theIR Sense 4 Click board™, 
> by showing parameters for detection of the presence and motion as well as ambient temperature.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C or SPI module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irsense4_cfg_t irsense4_cfg;  /**< Click config object. */

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
    irsense4_cfg_setup( &irsense4_cfg );
    IRSENSE4_MAP_MIKROBUS( irsense4_cfg, MIKROBUS_1 );
    err_t init_flag = irsense4_init( &irsense4, &irsense4_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( IRSENSE4_ERROR == irsense4_default_cfg ( &irsense4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ------------------------\r\n" );
}
```

### Application Task

> The application checks for the human presence and motion detection 
> and display output data, using embedded algorithms, and ambient temperature in degrees Celsius.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{ 
    static float temperature = 0.0;
    static int16_t detection_data = 0;
    static uint8_t status = 0;
    while ( IRSENSE4_OK != irsense4_wait_new_data_ready( &irsense4 ) );
    if ( IRSENSE4_OK == irsense4_get_status( &irsense4, &status ) )
    {
        if ( status & IRSENSE4_STATUS_DETECT_FLAG )
        {
            if ( ( IRSENSE4_OK == irsense4_get_presence_data( &irsense4, &detection_data ) ) && 
                 ( status & IRSENSE4_STATUS_PRES_FLAG ) )
            {
                log_printf( &logger, " Presence: %d \r\n", detection_data );
            }
    
            if ( ( IRSENSE4_OK == irsense4_get_motion_data( &irsense4, &detection_data ) ) && 
                 ( status & IRSENSE4_STATUS_MOT_FLAG ) )
            {
                log_printf( &logger, " Motion: %d \r\n", detection_data );
            }
            
            if ( IRSENSE4_OK == irsense4_get_amb_temperature( &irsense4, &temperature ) )
            {
                log_printf( &logger, " Temperature: %.2f C\r\n", temperature );
            }
            log_printf( &logger, " ------------------------\r\n" );
            Delay_ms ( 100 );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.IRSense4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
