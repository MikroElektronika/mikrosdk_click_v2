\mainpage Main Page

---
# Speed Radar click

> Speed Radar Click is a compact add-on board that comes with a radar motion detector. This board features the K-LD2, a radar transceiver from RFbeam. It is a 24GHz radar with a detection distance for humans of up to 15m and cars of up to 30m. Its digital structure makes it easy to use in an MCU-based application or as a standalone device where movement detection or even a speed measurement is required.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/speedradar_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/speed-radar-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2023.
- **Type**          : UART type


# Software Support

We provide a library for the Speed Radar Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Speed Radar Click driver.

#### Standard key functions :

- `speedradar_cfg_setup` Config Object Initialization function.
```c
void speedradar_cfg_setup ( speedradar_cfg_t *cfg );
```

- `speedradar_init` Initialization function.
```c
err_t speedradar_init ( speedradar_t *ctx, speedradar_cfg_t *cfg );
```

- `speedradar_default_cfg` Click Default Configuration function.
```c
err_t speedradar_default_cfg ( speedradar_t *ctx );
```

#### Example key functions :

- `speedradar_send_command` Speed Radar send command function.
```c
err_t speedradar_send_command ( speedradar_t *ctx, uint8_t *cmd )
```

- `speedradar_get_direction` Speed Radar get direction function.
```c
uint8_t speedradar_get_direction ( speedradar_t *ctx )
```

- `speedradar_get_detection` Speed Radar get detection function.
```c
uint8_t speedradar_get_detection ( speedradar_t *ctx );
```

## Example Description

> This example demonstrates the use of Speed Radar click board by processing
> the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    speedradar_cfg_t speedradar_cfg;  /**< Click config object. */

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
    speedradar_cfg_setup( &speedradar_cfg );
    SPEEDRADAR_MAP_MIKROBUS( speedradar_cfg, MIKROBUS_1 );
    if ( UART_ERROR == speedradar_init( &speedradar, &speedradar_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SPEEDRADAR_ERROR == speedradar_default_cfg ( &speedradar ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    speedradar_process( &speedradar );
    speedradar_clear_app_buf( );
    Delay_ms( 100 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ---------------------- \r\n" );
    Delay_ms( 100 );
}
```

### Application Task

> The demo application sends a command that returns and displays the speed [km/h] 
> and magnitude [dB] of the dominant movement for the forward and backward planes of the spectrum,
> measured frontal to the sensor.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    speedradar_send_command( &speedradar, SPEEDRADAR_CMD_GET_DETECTION_STR );
    Delay_ms( 50 );
    speedradar_process( &speedradar );
    if ( app_buf_len >= PROCESS_C00_RSP_LEN  )
    {
        speedradar_adv_det_display( );
        speedradar_clear_app_buf( );
        Delay_ms( 100 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SpeedRadar

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
