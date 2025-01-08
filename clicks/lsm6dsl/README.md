
---
# LSM6DSL Click

> [LSM6DSL Click](https://www.mikroe.com/?pid_product=MIKROE-2731) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2731&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This app measures linear and angular velocity with six degrees of freedom.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Lsm6Dsl

### Example Key Functions

- `lsm6dsl_cfg_setup` Config Object Initialization function. 
```c
void lsm6dsl_cfg_setup ( lsm6dsl_cfg_t *cfg );
``` 
 
- `lsm6dsl_init` Initialization function. 
```c
err_t lsm6dsl_init ( lsm6dsl_t *ctx, lsm6dsl_cfg_t *cfg );
```

- `lsm6dsl_default_cfg` Click Default Configuration function. 
```c
void lsm6dsl_default_cfg ( lsm6dsl_t *ctx );
```

- `lsm6dsl_set_accel_config` This function set accel configuration to the target LSM6DSL_CTRL1_XL register of LSM6DSL sensor. 
```c
void lsm6dsl_set_accel_config ( lsm6dsl_t *ctx, uint8_t odr_sel, uint8_t full_scale );
```
 
- `lsm6dsl_set_gyro_config` This function set gyro configuration to the target LSM6DSL_CTRL1_XL register of LSM6DSL sensor. 
```c
void lsm6dsl_set_gyro_config ( lsm6dsl_t *ctx, uint8_t odr_sel, uint8_t full_scale );
```

- `lsm6dsl_get_axis` This function get axis value from the two target 8-bit register address of LSM6DSL sensor. 
```c
uint16_t lsm6dsl_get_axis ( lsm6dsl_t *ctx, uint8_t reg_address_low );
```

### Application Init

> Initialization driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    lsm6dsl_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    lsm6dsl_cfg_setup( &cfg );
    LSM6DSL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lsm6dsl_init( &lsm6dsl, &cfg );

    lsm6dsl_default_cfg( &lsm6dsl );

    log_printf( &logger, "---------------------------------------\r\n" );
    log_printf( &logger, "|            LSM6DSL Click            |\r\n" );
    log_printf( &logger, "---------------------------------------\r\n" );
    log_printf( &logger, "|     Accel       |       Gyro        |\r\n" );
    log_printf( &logger, "---------------------------------------\r\n" );

    Delay_ms ( 100 );
}
```

### Application Task

> This is a example which demonstrates the use of LSM6DSL Click board.
> LSM6DSL Click communicates with register via SPI by write to register and read from register,
> measured acceleration and gyroscope coordinates values ( X,Y,Z )
> Result are being sent to the uart where you can track their changes.
> All data logs on usb uart for aproximetly every 3 sec.

```c
void application_task ( void )
{

    lsm6dsl_get_accel( &lsm6dsl, &accel, LSM6DSL_FULLSCALE_XL_2 );
    
    Delay_ms ( 10 );
    
    lsm6dsl_get_gyro( &lsm6dsl, &gyro, LSM6DSL_FULLSCALE_G_245 );
    
    Delay_ms ( 10 );

    log_printf( &logger, " Accel X : %f |  Gyro X : %f |\r\n", accel.accel_x, gyro.gyro_x );

    log_printf( &logger, " Accel Y : %f |  Gyro Y : %f |\r\n", accel.accel_y, gyro.gyro_y );

    log_printf( &logger, " Accel Z : %f |  Gyro Z : %f |\r\n", accel.accel_z, gyro.gyro_z );

    log_printf( &logger, "---------------------------------------\r\n" );

    Delay_ms ( 1000 );
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
