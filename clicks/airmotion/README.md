
---
# Air Motion Click

> [Air Motion Click](https://www.mikroe.com/?pid_product=MIKROE-5524) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5524&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2022.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Air Motion Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AirMotion

### Example Key Functions

- `airmotion_cfg_setup` Config Object Initialization function.
```c
void airmotion_cfg_setup ( airmotion_cfg_t *cfg );
```

- `airmotion_init` Initialization function.
```c
err_t airmotion_init ( airmotion_t *ctx, airmotion_cfg_t *cfg );
```

- `airmotion_default_cfg` Click Default Configuration function.
```c
err_t airmotion_default_cfg ( airmotion_t *ctx );
```

- `airmotion_set_reg_bank` Air Motion set register bank function.
```c
err_t airmotion_set_reg_bank( airmotion_t *ctx, uint8_t bank );
```

- `airmotion_sw_reset` Air Motion software reset function.
```c
err_t airmotion_sw_reset( airmotion_t *ctx );
```

- `airmotion_get_data_from_register` Air Motion read data function.
```c
err_t airmotion_get_data_from_register ( airmotion_t *ctx, float *temperature_data, airmotion_data_t *accel_data, airmotion_data_t *gyro_data, uint32_t *tmst_data );
```

### Application Init

> Initializes the driver after that resets the device and performs default configuration and reads the device id.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    airmotion_cfg_t airmotion_cfg;  /**< Click config object. */

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
    airmotion_cfg_setup( &airmotion_cfg );
    AIRMOTION_MAP_MIKROBUS( airmotion_cfg, MIKROBUS_1 );
    err_t init_flag = airmotion_init( &airmotion, &airmotion_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AIRMOTION_OK != airmotion_default_cfg ( &airmotion ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
   
    log_info( &logger, " Application Task " );
    
    uint8_t id = 0;
    airmotion_reg_read( &airmotion, AIRMOTION_BANK0_SEL, AIRMOTION_WHO_AM_I, &id, 1);
    log_printf( &logger, " WHO AM I = 0X%.2X\r\n", (uint16_t)id );
    
#if defined TAP_DETECTION_MODE
    log_printf( &logger, " Tap Detection Mode \r\n" );
    airmotion_set_basic_tap_detection( &airmotion );
#endif
    
}
```

### Application Task

> When the device is in Tap Detection Mode, Air Motion Click board will read and display the direction, axis, and number of taps that it detected. If Tap Detection mode is disabled, the device will read accel, gyro, and temperature data.

```c
void application_task ( void )
{
    if ( airmotion_get_int1_state( &airmotion) )
    {       
#if defined TAP_DETECTION_MODE
        uint8_t tap_num;
        uint8_t tap_axis;
        uint8_t tap_dir;
        
        airmotion_get_tap_detection( &airmotion, &tap_num, &tap_axis, &tap_dir );
        if (  AIRMOTION_TAP_SINGLE == tap_num )
        {
            log_printf( &logger, " SINGLE TAP" );
        }
        else
        {
            log_printf( &logger, " DOUBLE TAP" );
        }
        
        if (  AIRMOTION_TAP_DIR_POSITIVE == tap_dir )
        {
            log_printf( &logger, " IN POSITIVE" );
        }
        else
        {
            log_printf( &logger, " IN NEGATIVE" );
        }
        
        if (  AIRMOTION_TAP_AXIS_X == tap_axis )
        {
            log_printf( &logger, " X AXIS DIRECTION \r\n" );
        }
        else if ( AIRMOTION_TAP_AXIS_Y == tap_axis )
        {
            log_printf( &logger, " Y AXIS DIRECTION  \r\n" );
        }
        else
        {
            log_printf( &logger, " Z AXIS DIRECTION  \r\n" );
        }
#else
        airmotion_data_t accel_data;
        airmotion_data_t gyro_data;
        float temp_data;
        uint32_t tmst_data;
        
        airmotion_get_data_from_register( &airmotion, &temp_data, &accel_data, &gyro_data, &tmst_data );
        log_printf( &logger, " TEMP: %.2f \r\n", temp_data );
        log_printf( &logger, " GYRO: x:%d y:%d z:%d \r\n", gyro_data.data_x,gyro_data.data_y,gyro_data.data_z );
        log_printf( &logger, " ACCEL: x:%d y:%d z:%d \r\n", accel_data.data_x,accel_data.data_y,accel_data.data_z );
        log_printf( &logger, "========================== \r\n" );
        Delay_ms ( 1000 );
#endif
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
