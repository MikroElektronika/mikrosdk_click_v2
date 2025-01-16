
---
# NINA-B222 Click

> [NINA-B222 Click](https://www.mikroe.com/?pid_product=MIKROE-6086) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2024.
- **Type**          : UART type

# Software Support

## Example Description

> This example desmonstrates the use of NINA-B222 Click board by processing
> the incoming data and displaying them on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NINAB222

### Example Key Functions

- `ninab222_cfg_setup` Config Object Initialization function.
```c
void ninab222_cfg_setup ( ninab222_cfg_t *cfg );
```

- `ninab222_init` Initialization function.
```c
err_t ninab222_init ( ninab222_t *ctx, ninab222_cfg_t *cfg );
```

- `ninab222_set_device_name` This function sets the local name used as device name for Bluetooth Classic.
```c
err_t ninab222_set_device_name ( ninab222_t *ctx, uint8_t *device_name );
```

- `ninab222_set_connectability` This function sets the GAP connectability mode by using the UART serial interface.
```c
err_t ninab222_set_connectability ( ninab222_t *ctx, uint8_t c_mode );
```

- `ninab222_set_enter_mode` This function requests the module to move to the new mode by using the UART serial interface.
```c
err_t ninab222_set_enter_mode ( ninab222_t *ctx, uint8_t enter_mode );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ninab222_cfg_t ninab222_cfg;  /**< Click config object. */

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
    ninab222_cfg_setup( &ninab222_cfg );
    NINAB222_MAP_MIKROBUS( ninab222_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ninab222_init( &ninab222, &ninab222_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    ninab222_hw_reset( &ninab222 );
    Delay_ms ( 1000 );
    
    log_info( &logger, " Configuring the module " );
    Delay_ms ( 1000 );
    
    ninab222_set_sry_pin( &ninab222, NINAB222_PIN_STATE_HIGH );
    Delay_ms ( 100 );

    do 
    {
        ninab222_set_echo( &ninab222, NINAB222_ECHO_ON );
        Delay_ms ( 100 );
    }
    while ( NINAB222_OK != ninab222_process( &ninab222 ) );
    Delay_ms ( 500 );

    do 
    {
        ninab222_get_info( &ninab222 );
        Delay_ms ( 100 );
    }
    while ( NINAB222_OK != ninab222_process( &ninab222 ) );
    Delay_ms ( 500 );
    
    do 
    {
        ninab222_set_device_name( &ninab222, DEVICE_NAME );
        Delay_ms ( 100 );
    }
    while ( NINAB222_OK != ninab222_process( &ninab222 ) );
    Delay_ms ( 500 );
    
    do 
    {
        ninab222_set_connectability( &ninab222, NINAB222_GAP_MODE_CONN );
        Delay_ms ( 100 );
    }
    while ( NINAB222_OK != ninab222_process( &ninab222 ) );
    Delay_ms ( 500 );
    
    do 
    {
        ninab222_set_discoverability( &ninab222, NINAB222_GAP_MODE_GEN_DISC );
        Delay_ms ( 100 );
    }
    while ( NINAB222_OK != ninab222_process( &ninab222 ) );
    Delay_ms ( 500 );
    
    do 
    {
        ninab222_set_enter_mode( &ninab222, NINAB222_MODE_DATA );
        Delay_ms ( 100 );
    }
    while ( NINAB222_OK != ninab222_process( &ninab222 ) );
    ninab222_clear_app_buf( );
    Delay_ms ( 500 );
    
    ninab222_set_sry_pin( &ninab222, NINAB222_PIN_STATE_LOW );
    log_info( &logger, " Configuration is complete " );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> Reads and processes all incoming data and displays them on the USB UART.

```c
void application_task ( void ) 
{
    if ( NINAB222_OK == ninab222_process( &ninab222 ) ) 
    {
        ninab222_log_app_buf( );
        ninab222_clear_app_buf( );
    }
}
```

### Note

> - Recommended Android application at the link:
>   https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal
> - Before using this Click, it must be paired with your devices.

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
