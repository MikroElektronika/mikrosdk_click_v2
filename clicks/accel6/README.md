
---
# Accel 6 Click

> [Accel 6 Click](https://www.mikroe.com/?pid_product=MIKROE-3075) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3075&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This application allows acceleration measurement in three perpendicular axes.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel6

### Example Key Functions

- `accel6_cfg_setup` Config Object Initialization function. 
```c
void accel6_cfg_setup ( accel6_cfg_t *cfg );
``` 
 
- `accel6_init` Initialization function. 
```c
err_t accel6_init ( accel6_t *ctx, accel6_cfg_t *cfg );
```

- `accel6_default_cfg` Click Default Configuration function. 
```c
void accel6_default_cfg ( accel6_t *ctx, uint8_t range_data, uint8_t bw_data, uint8_t lpw_data );
```

- `accel6_data_offset` Functions for set offset. 
```c
void accel6_data_offset( accel6_t *ctx, uint8_t set_offset, float *offset_data );
```
 
- `accel6_get_orient` Functions for read orient. 
```c
void accel6_get_orient( accel6_t *ctx, uint8_t *z_orient, uint8_t *xy_orient );
```

- `accel6_get_axis` Functions for read axis data. 
```c
float accel6_get_axis( accel6_t *ctx, uint8_t axis );
```

### Application Init

> Initializes Driver init and settings accelerometer data range, 
> bandwidth, mode and sleep timer which are necessary for the init chip.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    accel6_cfg_t cfg;

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

    accel6_cfg_setup( &cfg );
    ACCEL6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel6_init( &accel6, &cfg );

    accel6_soft_reset( &accel6 );
    Delay_1sec();
    log_info( &logger, "---- Device reset done ----" );
    
    accel6_default_cfg( &accel6, ACCEL6_PMU_RANGE_4g, 
                                          ACCEL6_PMU_BW_125Hz, 
                                          ACCEL6_PMU_LPW_NORMAL_MODE | 
                                          ACCEL6_PMU_LPW_SLEEP_10ms );
    
    log_info( &logger, "---- Device configuration done ----" );
    
    Delay_1sec();
}
```

### Application Task

> Reads the accel X / Y / Z axis data in mg, 
> Temperature data in C, detects the orientation of the X,Y and Z axis
> and checking on which axis the tap is detected.
> All data logs on usb uart for every 500 ms.

```c
void application_task ( )
{
    uint8_t tap_detect;
    uint8_t orient;
    uint8_t z_orient;
    uint8_t xy_orient;
    float f_axis = 0.0;
    float temp = 0.0;
    
    f_axis = accel6_get_axis ( &accel6, ACCEL6_AXIS_X );
    log_printf( &logger, " X axis: %f mg \r\n ", f_axis );


    f_axis = accel6_get_axis ( &accel6, ACCEL6_AXIS_Y );
    log_printf( &logger, " Y axis: %f mg \r\n ", f_axis );

    f_axis = accel6_get_axis ( &accel6, ACCEL6_AXIS_Z );
    log_printf( &logger, " Z axis: %f mg \r\n ", f_axis );

    temp = accel6_get_temperature( &accel6 );
    log_printf( &logger, " Temperature: %.2f C \r\n ", temp );

    accel6_get_orient( &accel6, &z_orient, &xy_orient );
    
    switch ( z_orient )
    {
        case 1:
        {
            log_printf( &logger, " Z orient : UPWARD looking \r\n " );
            break;
        }
        case 2:
        {
            log_printf( &logger, " Z orient : DOWNWARD looking \r\n " );
            break;
        }
        default:
        {
            break;
        }
    }

    switch ( xy_orient )
    {
        case 1:
        {
            log_printf( &logger, " XY orient : UPSIDE DOWN \r\n " );
            break;
        }
        case 2:
        {
            log_printf( &logger, " XY orient : LANDSCAPE LEFT \r\n " );
            break;
        }
        case 3:
        {
            log_printf( &logger, " XY orient : LANDSCAPE RIGHT \r\n " );
            break;
        }
        case 4:
        {
            log_printf( &logger, " XY orient : UPRIGHT \r\n " );
            break;
        }
        default:
        {
            break;
        }
    }
	
	tap_detect = accel6_get_tap_status( &accel6 );
    switch ( tap_detect )
    {
        case 1:
        {
            log_printf( &logger, " Tap status : X negative \r\n " );
            break;
        }
        case 2:
        {
            log_printf( &logger, " Tap status : Y negative \r\n " );
            break;
        }
        case 3:
        {
            log_printf( &logger, " Tap status : Z negative \r\n " );
            break;
        }
        case 4:
        {
            log_printf( &logger, " Tap status : X positive \r\n " );
            break;
        }
        case 5:
        {
            log_printf( &logger, " Tap status : Y positive \r\n " );
            break;
        }
        case 6:
        {
            log_printf( &logger, " Tap status : Z positive \r\n " );
            break;
        }
        default:
        {
            break;
        }
    }
	
    log_printf( &logger, "   \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
