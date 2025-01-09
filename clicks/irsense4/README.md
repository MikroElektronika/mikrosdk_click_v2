
---
# IR Sense 4 Click

> [IR Sense 4 Click](https://www.mikroe.com/?pid_product=MIKROE-5952) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5952&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jun 2023.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of theIR Sense 4 Click board&trade;, 
> by showing parameters for detection of the presence and motion as well as ambient temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IRSense4

### Example Key Functions

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
