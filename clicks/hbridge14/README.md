
---
# H-Bridge 14 Click

> [H-Bridge 14 Click](https://www.mikroe.com/?pid_product=MIKROE-5916) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5916&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2023.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of the H-Bridge 14 board by driving the 
  motor in both directions with braking and coasting in between.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge14

### Example Key Functions

- `hbridge14_cfg_setup` Config Object Initialization function.
```c
void hbridge14_cfg_setup ( hbridge14_cfg_t *cfg );
```

- `hbridge14_init` Initialization function.
```c
err_t hbridge14_init ( hbridge14_t *ctx, hbridge14_cfg_t *cfg );
```

- `hbridge14_default_cfg` Click Default Configuration function.
```c
err_t hbridge14_default_cfg ( hbridge14_t *ctx );
```

- `hbridge14_set_pins` H-Bridge 14 set pins function.
```c
err_t hbridge14_set_pins ( hbridge14_t *ctx, uint8_t set_mask, uint8_t clr_mask );
```

- `hbridge14_sleep_state` H-Bridge 14 control sleep function.
```c
err_t hbridge14_sleep_state ( hbridge14_t *ctx, uint8_t sleep_state );
```

- `hbridge14_drive_motor` H-Bridge 14 drive motor function.
```c
err_t hbridge14_drive_motor ( hbridge14_t *ctx, uint8_t state );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge14_cfg_t hbridge14_cfg;  /**< Click config object. */

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
    hbridge14_cfg_setup( &hbridge14_cfg );
    HBRIDGE14_MAP_MIKROBUS( hbridge14_cfg, MIKROBUS_1 );
    err_t init_flag = hbridge14_init( &hbridge14, &hbridge14_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HBRIDGE14_ERROR == hbridge14_default_cfg ( &hbridge14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Drives the motor in both directions with coasting and braking in between, every sate is lasting 5 seconds.

```c
void application_task ( void )
{
    uint8_t fault_status = 0;

    hbridge14_drive_motor( &hbridge14, HBRIDGE14_DRIVE_MOTOR_CW );
    log_printf( &logger, " Driving motor Clockwise \r\n" );
    hbridge14_register_read( &hbridge14, HBRIDGE14_REG_FAULT_STATUS, &fault_status );
    log_printf( &logger, " Fault status : 0x%.2X \r\n", ( uint16_t ) fault_status );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    hbridge14_drive_motor( &hbridge14, HBRIDGE14_DRIVE_MOTOR_BRAKE );
    log_printf( &logger, " Brake is on \r\n" );
    hbridge14_register_read( &hbridge14, HBRIDGE14_REG_FAULT_STATUS, &fault_status );
    log_printf( &logger, " Fault status : 0x%.2X \r\n", ( uint16_t ) fault_status );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    hbridge14_drive_motor( &hbridge14, HBRIDGE14_DRIVE_MOTOR_CCW );
    log_printf( &logger, " Driving motor counter-clockwise \r\n" );
    hbridge14_register_read( &hbridge14, HBRIDGE14_REG_FAULT_STATUS, &fault_status );
    log_printf( &logger, " Fault status : 0x%.2X \r\n", ( uint16_t ) fault_status );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    hbridge14_drive_motor( &hbridge14, HBRIDGE14_DRIVE_MOTOR_COASTING );
    log_printf( &logger, " Driving motor Coasting \r\n" );
    hbridge14_register_read( &hbridge14, HBRIDGE14_REG_FAULT_STATUS, &fault_status );
    log_printf( &logger, " Fault status : 0x%.2X \r\n", ( uint16_t ) fault_status );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
