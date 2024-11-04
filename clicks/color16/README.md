\mainpage Main Page

---
# Color 16 Click

> Color 16 Click is a compact add-on board providing an accurate color-sensing solution. This board features ams AG’s AS7343, a 14-channel multi-purpose spectral sensor offering spectral response through a compatible I2C interface. It has a built-in aperture that controls the light entering the sensor array to increase accuracy, alongside precise optical filters integrated into standard CMOS silicon via deposited interference filter technology. The spectral response is defined by individual channels covering approximately 380nm to 1000nm with 11 channels centered in the visible spectrum, one near-infrared, and a clear channel.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/color16_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/color-16-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Color 16 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Color 16 Click driver.

#### Standard key functions :

- `color16_cfg_setup` Config Object Initialization function.
```c
void color16_cfg_setup ( color16_cfg_t *cfg );
```

- `color16_init` Initialization function.
```c
err_t color16_init ( color16_t *ctx, color16_cfg_t *cfg );
```

- `color16_default_cfg` Click Default Configuration function.
```c
err_t color16_default_cfg ( color16_t *ctx );
```

#### Example key functions :

- `color16_read_data` This function checks if the spectral measurement data is ready and then reads data from all channels along with the STATUS and ASTATUS bytes.
```c
err_t color16_read_data ( color16_t *ctx, color16_data_t *data_out );
```

- `color16_set_wait_time_ms` This function sets the wait time in milliseconds by setting the WTIME register.
```c
err_t color16_set_wait_time_ms ( color16_t *ctx, float wait_time_ms );
```

- `color16_set_integration_time_ms` This function sets the integration time in milliseconds by setting the ATIME and ASTEP registers.
```c
err_t color16_set_integration_time_ms ( color16_t *ctx, float int_time_ms );
```

## Example Description

> This example demonstrates the use of Color 16 Click by reading and displaying the values from all 14 channels.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color16_cfg_t color16_cfg;  /**< Click config object. */

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
    color16_cfg_setup( &color16_cfg );
    COLOR16_MAP_MIKROBUS( color16_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == color16_init( &color16, &color16_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COLOR16_ERROR == color16_default_cfg ( &color16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for the spectral measurement complete flag and then reads data from all 14 channels
in 3 cycles, and displays the results on the USB UART every 300ms approximately.

```c
void application_task ( void )
{
    color16_data_t color_data;
    if ( COLOR16_OK == color16_read_data ( &color16, &color_data ) )
    {
        log_printf ( &logger, " STATUS:          0x%.2X\r\n", ( uint16_t ) color_data.status );
        log_printf ( &logger, " ASTATUS:         0x%.2X\r\n", ( uint16_t ) color_data.astatus );
        log_printf ( &logger, " ------- Cycle 1 -------\r\n" );
        log_printf ( &logger, " Channel FZ:      %u\r\n", color_data.ch_fz );
        log_printf ( &logger, " Channel FY:      %u\r\n", color_data.ch_fy );
        log_printf ( &logger, " Channel FXL:     %u\r\n", color_data.ch_fxl );
        log_printf ( &logger, " Channel NIR:     %u\r\n", color_data.ch_nir );
        log_printf ( &logger, " Channel 2xVIS_1: %u\r\n", color_data.ch_2x_vis_1 );
        log_printf ( &logger, " Channel FD_1:    %u\r\n", color_data.ch_fd_1 );
        log_printf ( &logger, " ------- Cycle 2 -------\r\n" );
        log_printf ( &logger, " Channel F2:      %u\r\n", color_data.ch_f2 );
        log_printf ( &logger, " Channel F3:      %u\r\n", color_data.ch_f3 );
        log_printf ( &logger, " Channel F4:      %u\r\n", color_data.ch_f4 );
        log_printf ( &logger, " Channel F6:      %u\r\n", color_data.ch_f6 );
        log_printf ( &logger, " Channel 2xVIS_2: %u\r\n", color_data.ch_2x_vis_2 );
        log_printf ( &logger, " Channel FD_2:    %u\r\n", color_data.ch_fd_2 );
        log_printf ( &logger, " ------- Cycle 3 -------\r\n" );
        log_printf ( &logger, " Channel F1:      %u\r\n", color_data.ch_f1 );
        log_printf ( &logger, " Channel F5:      %u\r\n", color_data.ch_f5 );
        log_printf ( &logger, " Channel F7:      %u\r\n", color_data.ch_f7 );
        log_printf ( &logger, " Channel F8:      %u\r\n", color_data.ch_f8 );
        log_printf ( &logger, " Channel 2xVIS_3: %u\r\n", color_data.ch_2x_vis_3 );
        log_printf ( &logger, " Channel FD_3:    %u\r\n", color_data.ch_fd_3 );
        log_printf ( &logger, " -----------------------\r\n\n" );
        Delay_ms ( 300 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Color16

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
