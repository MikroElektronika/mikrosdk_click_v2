
---
# Pedometer 3 Click

> [Pedometer 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3259) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3259&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> The demo application displays measuring 2 accelerometers (normal accel and high pass accel),
> counting steps and displaying tilt positions.
> The sensor includes additional feature and setups that you can look up in the library.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pedometer3

### Example Key Functions

- `pedometer3_cfg_setup` Config Object Initialization function.
```c
void pedometer3_cfg_setup ( pedometer3_cfg_t *cfg ); 
```

- `pedometer3_init` Initialization function.
```c
err_t pedometer3_init ( pedometer3_t *ctx, pedometer3_cfg_t *cfg );
```

- `pedometer3_default_cfg` Click Default Configuration function.
```c
void pedometer3_default_cfg ( pedometer3_t *ctx );
```

- `pedometer3_get_hp_accel_axis` High Pass Accel axis data
```c
void pedometer3_get_hp_accel_axis ( pedometer3_t *ctx, pedometer3_axis_t *axis );
```

- `pedometer3_get_accel_axis` Accel axis data
```c
void pedometer3_get_accel_axis ( pedometer3_t *ctx, pedometer3_axis_t *axis );
```

- `pedometer3_get_step_counter` Pedometer step counter
```c
uint16_t pedometer3_get_step_counter ( pedometer3_t *ctx );
```

### Application Init

> Configuring Clicks and log objects.
> Settings the Click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    pedometer3_cfg_t cfg;
    uint8_t tmp;

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
    pedometer3_cfg_setup( &cfg );
    PEDOMETER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pedometer3_init( &pedometer3, &cfg );

    // Default Click configurations
    pedometer3_default_cfg( &pedometer3 );

    tmp = PEDOMETER3_CNTL1_MODE_LOW_POWER | PEDOMETER3_CNTL1_MODE_LOW_POWER |
          PEDOMETER3_CNTL1_RES_MODE_LOWER_NOISE | PEDOMETER3_CNTL1_DATA_READY_DISABLE |
          PEDOMETER3_CNTL1_G_RANGE_2g | PEDOMETER3_CNTL1_TAP_ENABLE |
          PEDOMETER3_CNTL1_PEDOMETER_ENABLE | PEDOMETER3_CNTL1_TILT_ENABLE;

    pedometer3_generic_write( &pedometer3, PEDOMETER3_REG_CONTROL_1, &tmp, 1 );
}
```

### Application Task

> Reads Accel and High Pass Accel X/Y/Z axis and detect Tilt Position.
> All data logs on the USBUART every 400 ms.

```c
void application_task ( void )
{
    static uint16_t ped_step = 0;
    pedometer3_axis_t accel_axis;
    pedometer3_axis_t highpass_axis;
    pedometer3_tilt_position_t tilt;

    pedometer3_get_accel_axis( &pedometer3, &accel_axis );
    pedometer3_get_hp_accel_axis( &pedometer3, &highpass_axis );
    ped_step += pedometer3_get_step_counter( &pedometer3 );

    log_printf( &logger, "___________ Pedometer 3 Click _____________\r\n");

    log_printf( &logger, "--  Accel : [ X ]: %d / [ Y ]: %d / [ Z ]: %d \r\n", 
                accel_axis.x, accel_axis.y, accel_axis.z );
    log_printf( &logger, "--  HP Accel : [ X ]: %d / [ Y ]: %d / [ Z ]: %d \r\n", 
                highpass_axis.x, highpass_axis.y, highpass_axis.z );

    log_printf( &logger, "--  Step counter : [ STEP ]: %d \r\n", ped_step );

    pedometer3_get_tilt_position( &pedometer3, &tilt);

    switch ( tilt.current_pos )
    {
        case PEDOMETER3_TILT_POSITION_LEFT:
        {
            log_printf( &logger, "--  Current Tilt Position: [ LEFT ] \r\n" );
            break;
        }
        case PEDOMETER3_TILT_POSITION_RIGHT:
        {
            log_printf( &logger, "--  Current Tilt Position: [ RIGHT ] \r\n" );
            break;
        }
        case PEDOMETER3_TILT_POSITION_DOWN:
        {
            log_printf( &logger, "--  Current Tilt Position: [ DOWN ] \r\n" );
            break;
        }
        case PEDOMETER3_TILT_POSITION_UP:
        {
            log_printf( &logger, "--  Current Tilt Position: [ UP ] \r\n" );
            break;
        }
        case PEDOMETER3_TILT_POSITION_FACE_DOWN:
        {
            log_printf( &logger, "--  Current Tilt Position: [ FACE DOWN ] \r\n" );
            break;
        }
        case PEDOMETER3_TILT_POSITION_FACE_UP:
        {
            log_printf( &logger, "--  Current Tilt Position: [ FACE UP ] \r\n" );
            break;
        }
    }

    Delay_ms ( 400 );
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
