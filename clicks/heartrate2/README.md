
---
# Heart Rate 2 Click

> [Heart Rate 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4037) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4037&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Heart rate 2 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HeartRate2

### Example Key Functions

- `heartrate2_cfg_setup` Config Object Initialization function. 
```c
void heartrate2_cfg_setup ( heartrate2_cfg_t *cfg );
``` 
 
- `heartrate2_init` Initialization function. 
```c
err_t heartrate2_init ( heartrate2_t *ctx, heartrate2_cfg_t *cfg );
```

- `heartrate2_default_cfg` Click Default Configuration function. 
```c
void heartrate2_default_cfg ( heartrate2_t *ctx );
```

- `heartrate2_set_en` This function settings en pin status. 
```c
void heartrate2_set_en ( heartrate2_t *ctx, uint8_t state );
```
 
- `heartrate2_soft_reset` This function restarts device. 
```c
void heartrate2_soft_reset ( heartrate2_t *ctx );
```

- `heartrate2_read_fifo` This function reads data buffer from the desired register. 
```c
void heartrate2_read_fifo ( heartrate2_t *ctx, heartrate2_fifo_data_t *fifo );
```

### Application Init

> Initilizes the driver, resets the device, checks the device ID and applies default settings.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    heartrate2_cfg_t cfg;
    uint8_t rd_stat;

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

    heartrate2_cfg_setup( &cfg );
    HEARTRATE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    heartrate2_init( &heartrate2, &cfg );
    
    log_printf( &logger, "Configuring the module...\r\n" );
    Delay_ms ( 1000 );
    
    heartrate2_set_en( &heartrate2, HEARTRATE2_PIN_HIGH );
    Delay_ms ( 100 );
    heartrate2_soft_reset ( &heartrate2 );
    
    rd_stat = heartrate2_generic_read( &heartrate2, HEARTRATE2_REG_PART_ID );

    if ( rd_stat != HEARTRATE2_DEV_ID )
    {
        log_error( &logger, "---- WRONG ID ----" );
        log_printf( &logger, "Please restart your system.\r\n" );
        for ( ; ; );
    }
    
    heartrate2_default_cfg( &heartrate2, HEARTRATE2_CONFIG_GREEN );
    log_printf( &logger, "The module has been configured!\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

> Reads the data from Green diode and displays the results on USB UART if the measured data
> is above defined threshold, otherwise, it displays a desired message on the terminal.

```c
void application_task ( void )
{
    heartrate2_fifo_data_t fifo_object;

    heartrate2_read_fifo( &heartrate2, &fifo_object );

    if ( fifo_object.tag == HEARTRATE2_FIFO_TAG_PPG1_LEDC1 )
    {
        counter++;
        if ( fifo_object.data_val > 1000 )
        {
            log_printf( &logger, "%lu;\r\n", fifo_object.data_val );
            counter = 1000;
        }
        else if ( counter > 1000 )
        {
            log_printf( &logger, "Please place your index finger on the sensor.\r\n" );
            counter = 0;
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
