
---
# Touchpad 5 Click

> [Touchpad 5 Click](https://www.mikroe.com/?pid_product=MIKROE-5199) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5199&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Popovic
- **Date**          : Apr 2022.
- **Type**          : I2C type

# Software Support

## Example Description

>  This example demonstrates the use of Touchpad 5 Click board by utilizing the touchpad XY 
   and snap functionalities.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TouchPad5

### Example Key Functions

- `touchpad5_cfg_setup` Config Object Initialization function.
```c
void touchpad5_cfg_setup ( touchpad5_cfg_t *cfg );
```

- `touchpad5_init` Initialization function.
```c
err_t touchpad5_init ( touchpad5_t *ctx, touchpad5_cfg_t *cfg );
```

- `touchpad5_default_cfg` Click Default Configuration function.
```c
err_t touchpad5_default_cfg ( touchpad5_t *ctx );
```

- `touchpad5_get_touch` This function get touch XY data.
```c
err_t touchpad5_get_touch( touchpad5_t *ctx, touchpad5_touch_t *touch_data );
```

- `touchpad5_get_status` This function get status proximity, touch or snap data.
```c
err_t touchpad5_get_status( touchpad5_t *ctx, uint8_t sel_status, uint16_t *rx_data, uint8_t num_of_samples );
```

- `touchpad5_wait_ready` This function waits for the communication window to be available.
```c
void touchpad5_wait_ready( touchpad5_t *ctx );
```

### Application Init

>  Initializes the driver and USB UART logging and displays the device version information 
   such as product number, project number, major/minor release number, hardware ID, hardware
   revision and bootloader status.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    touchpad5_cfg_t touchpad5_cfg;      /**< Click config object. */

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
    touchpad5_cfg_setup( &touchpad5_cfg );
    TOUCHPAD5_MAP_MIKROBUS( touchpad5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == touchpad5_init( &touchpad5, &touchpad5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    Delay_100ms();
    
    if ( TOUCHPAD5_ERROR == touchpad5_default_cfg ( &touchpad5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    Delay_1sec( );
    
    if ( TOUCHPAD5_ERROR == touchpad5_check_version( &touchpad5, &ver_info ) )
    {
        log_error( &logger, " Cannot read version.\r\n " );
        for ( ; ; );
    }
    
    Delay_100ms();
    
    if ( TOUCHPAD5_ERROR == touchpad5_check_bl_status( &touchpad5, &bl_status ) )
    {
        log_error( &logger, " Cannot read bootloader status.\r\n " );
        for ( ; ; );
    }
    
    Delay_100ms();
    
    if ( ver_info.product_num != TOUCHPAD5_IQS550_PRODUCT_NUMBER ) 
    {
        log_error( &logger, " Incorrect product number.\r\n " );
        for ( ; ; );
    }
    
    log_printf( &logger, "----------------------------------------------------------------\r\n" );
    log_printf( &logger, " Product number %u \r\n",    ( uint32_t ) ver_info.product_num );
    log_printf( &logger, " Project number %u \r\n",    ( uint32_t ) ver_info.project_num );
    log_printf( &logger, " Version %.1f \r\n", ver_info.version );
    log_printf( &logger, " Hardware ID %x \r\n",       ( uint32_t ) ver_info.hw_id );
    log_printf( &logger, " Hardware revision %x \r\n", ( uint32_t ) ver_info.hw_revision );
    log_printf( &logger, " Bootloader status %x \r\n", ( uint16_t ) bl_status );
    log_printf( &logger, "----------------------------------------------------------------\r\n" );
    Delay_1sec( );
    log_printf( &logger, "----------------------------------------------------------------\r\n" );
    log_printf( &logger, " Waiting for a new touch or snap (click)\r\n" );
    log_printf( &logger, "----------------------------------------------------------------\r\n" );
    Delay_1sec( );
    log_info( &logger, " Application Task " );
}
```

### Application Task

>  Task busy waits for the touchpad controller ready bit using polling operation. When the
   communication window is available, the snap functionality is being checked, as well as 
   XY touchpad data. Based on the user's touch sensibility and duration, one of the two 
   features is being determined and logged over UART terminal. Snap (click) corresponds to
   the shorter and lighter 'click' gesture, while the touch is detected as longer and 
   stronger 'swipe' gesture.

```c
void application_task ( void ) 
{
    // Get touchpad XY data
    touchpad5_get_touch( &touchpad5, &touch_data );
    
    // Detecting the snap (click) criteria
    if ( touchpad5_detect_snap( &touchpad5, snap_buffer, SNAP_BUFFER_SIZE, &snap_reference) && touch_data.touch_strength > 0 )
    {
        log_printf( &logger, "----------------------------------------------------------------\r\n" );
        log_printf( &logger, "\r\n* Snap (click) event occured with strength: %u *\r\n", 
                                                                        ( uint16_t ) touch_data.touch_strength ); 
        log_printf( &logger, "----------------------------------------------------------------\r\n" );
        Delay_1sec( );
    }
    // Detecting the touch criteria
    else if ( touch_data.x_pos > 0 && touch_data.y_pos > 0 && touch_data.touch_strength > TOUCH_STRENGTH_THRESHOLD )
    {
        
        log_printf( &logger, "----------------------------------------------------------------\r\n" );
        log_printf( &logger, " \r\nTouch with Tag ID %u detected\r\n",  ( uint16_t ) touch_data.id_tag );
        log_printf( &logger, "Coordinate X = %u \r\n",                               touch_data.x_pos );
        log_printf( &logger, "Coordinate Y = %u \r\n",                               touch_data.y_pos );
        log_printf( &logger, "Touch strength = %u  \r\n",               ( uint16_t ) touch_data.touch_strength );
        log_printf( &logger, "----------------------------------------------------------------\r\n\r\n" );
        Delay_ms ( 100 );
    }
    
    // Monitoring to determine whether the reset occurred on the device after the last ack reset     
    if ( touch_data.xy_info & TOUCHPAD5_SHOW_RESET )
    {
        log_printf( &logger, "----------------------------------------------------------------\r\n" );
        log_error( &logger, "\r\n Unexpected reset occured. \r\n" ); 
        log_printf( &logger, "----------------------------------------------------------------\r\n\r\n" );
    }
}
```

### Note

> This example relies on the IQS5xx-A000 firmware of the touch-pad controller.

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



