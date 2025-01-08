
---
# 6DOF IMU 11 Click

> [6DOF IMU 11 Click](https://www.mikroe.com/?pid_product=MIKROE-3869) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3869&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> Designed to strike a balance between current consumption and noise performance with excellent bias stability over temperature

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.6DofImu11

### Example Key Functions

- `c6dofimu11_cfg_setup` Config Object Initialization function. 
```c
void c6dofimu11_cfg_setup ( c6dofimu11_cfg_t *cfg );
``` 
 
- `c6dofimu11_init` Initialization function. 
```c
err_t c6dofimu11_init ( c6dofimu11_t *ctx, c6dofimu11_cfg_t *cfg );
```

- `c6dofimu11_default_cfg` Click Default Configuration function. 
```c
void c6dofimu11_default_cfg ( c6dofimu11_t *ctx );
```

- `c6dofimu11_config_accel` Configuration Accel function. 
```c
void c6dofimu11_config_accel (  c6dofimu11_t *ctx, uint8_t data_rate, uint8_t data_range, uint8_t data_resolution  );
```

- `c6dofimu11_config_mag` Configuration Magnetometer function. 
```c
void c6dofimu11_config_mag (  c6dofimu11_t *ctx, uint8_t data_rate, uint8_t data_resolution  );
```

- `c6dofimu11_get_axis` Get axis data function. 
```c
int16_t c6dofimu11_get_axis (  c6dofimu11_t *ctx, uint8_t reg_add_lsb  );
```

- `c6dofimu11_get_accel_data` Read Accel X-axis, Y-axis and Z-axis function. 
```c
void c6dofimu11_get_accel_data (  c6dofimu11_t *ctx, int16_t *accel_x, int16_t *accel_y, int16_t *accel_z  );
```

- `c6dofimu11_get_mag_data` Read Magnetometer X-axis, Y-axis and Z-axis function. 
```c
void c6dofimu11_get_mag_data (  c6dofimu11_t *ctx, int16_t *mag_x, int16_t *mag_y, int16_t *mag_z  );
```

- `c6dofimu11_read_accel` Get Accel range X, Y and Z value ( g ) function. 
```c
void c6dofimu11_read_accel (   c6dofimu11_t *ctx, c6dofimu11_accel_t *accel_data  );
```

- `c6dofimu11_read_mag` Get Magnetometer magnetic field strength X, Y and Z value ( nT ) function. 
```c
void c6dofimu11_read_mag (  c6dofimu11_t *ctx, c6dofimu11_mag_t *mag_data  );
```

### Application Init

> Initialization driver enables - I2C, check device ID,
  sets default configuration, also write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu11_cfg_t cfg;

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

    c6dofimu11_cfg_setup( &cfg );
    C6DOFIMU11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu11_init( &c6dofimu11, &cfg );

    if ( c6dofimu11_check_id( &c6dofimu11 ) == C6DOFIMU11_CHECK_ID_SUCCESS )
    {
        log_printf( &logger, "         SUCCESS          \r\n" );
        log_printf( &logger, "--------------------------\r\n" );
    }
    else
    {
        log_printf( &logger, "          ERROR           \r\n" );
        log_printf( &logger, "     Reset the device     \r\n" );
        log_printf( &logger, "--------------------------\r\n" );
        for ( ; ; );
    }

    c6dofimu11_default_cfg(  &c6dofimu11 );

    log_printf( &logger, "    Set default config    \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example which demonstrates the use of 6DOF IMU 11 Click board.
> Measured and display Accel and Magnetometer magnetic field strength values for X-axis, Y-axis and Z-axis.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on USB uart changes for every 2 sec. 

```c
void application_task ( void )
{
c6dofimu11_mag_t mag_data;
   c6dofimu11_accel_t accel_data;
   
   c6dofimu11_read_accel ( &c6dofimu11, &accel_data );
    Delay_ms ( 10 );
    c6dofimu11_read_mag ( &c6dofimu11, &mag_data );
    Delay_ms ( 10 );

    log_printf( &logger, " Accel X : %d %c g\r\n", accel_data.x  );
    c6dofimu11_uart_sign_print (  );

    log_printf( &logger, " Accel Y : %d %c g\r\n", accel_data.y  );
    c6dofimu11_uart_sign_print (  ); 

    
    log_printf( &logger, " Accel Z : %d %c g\r\n", accel_data.z  );
    c6dofimu11_uart_sign_print (  );

    log_printf( &logger, " Mag X : %d %c uT\r\n", mag_data.x  );
    c6dofimu11_uart_sign_print (  );

    log_printf( &logger, " Mag Y : %d %c uT\r\n", mag_data.y  );
    c6dofimu11_uart_sign_print (  );

    log_printf( &logger, " Mag Z : %d %c uT\r\n", mag_data.z  );
    c6dofimu11_uart_sign_print (  );
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
