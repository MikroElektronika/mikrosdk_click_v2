
---
# Accel 10 Click

> [Accel 10 Click](https://www.mikroe.com/?pid_product=MIKROE-4112) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4112&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2020.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Accel 10 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel10

### Example Key Functions

- `accel10_cfg_setup` Config Object Initialization function. 
```c
void accel10_cfg_setup ( accel10_cfg_t *cfg );
``` 
 
- `accel10_init` Initialization function. 
```c
err_t accel10_init ( accel10_t *ctx, accel10_cfg_t *cfg );
```

- `accel10_default_cfg` Click Default Configuration function. 
```c
void accel10_default_cfg ( accel10_t *ctx );
```

- `accel10_check_data_ready` Check data ready function. 
```c
uint8_t accel10_check_data_ready ( accel10_t *ctx );
```
 
- `accel10_get_data` Read Accel data function. 
```c
void accel10_get_data ( accel10_t *ctx, accel10_data_t *p_accel_data );
```

- `accel10_read_temperature` Read temperature function. 
```c
int8_t accel10_read_temperature ( accel10_t *ctx );
```

### Application Init

> Initializes the driver and checks the communication by reading the device ID.
> After that, performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    accel10_cfg_t cfg;

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

    accel10_cfg_setup( &cfg );
    ACCEL10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel10_init( &accel10, &cfg );
    Delay_ms ( 500 );
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "    Accel 10 Click\r\n" );
    log_printf( &logger, "---------------------\r\n" );
    
    // Checking communication
    if ( accel10_check_id( &accel10 ) == ACCEL10_SUCCESS )
    {
        log_printf( &logger, "  Communication  OK\r\n" );
        log_printf( &logger, "---------------------\r\n" );
        Delay_ms ( 100 );
    }
    else
    {
        log_printf( &logger, "  Communication ERROR\r\n" );
        log_printf( &logger, "  Reset the device\r\n" );
        log_printf( &logger, "---------------------\r\n" );
        for ( ; ; );
    }
    
    accel10_default_cfg ( &accel10 );
    log_printf( &logger, "  Default config.\r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> Reads the accel values for X, Y, and Z axis and also reads the temperature in Celsius
> and displays the results on the USB UART each second.

```c
void application_task ( void )
{
    if ( accel10_check_data_ready( &accel10 ) == ACCEL10_STATUS_DATA_READY )
    {
        accel10_get_data ( &accel10, &accel_data );
        Delay_ms ( 10 );
        
        log_printf( &logger, "  Accel X :  %d\r\n", accel_data.x );
        log_printf( &logger, "  Accel Y :  %d\r\n", accel_data.y );
        log_printf( &logger, "  Accel Z :  %d\r\n", accel_data.z );
    
        temperature = accel10_read_temperature( &accel10 );
        Delay_ms ( 10 );

        log_printf( &logger, " Temperature :  %d C\r\n", ( int16_t ) temperature );
        log_printf( &logger, "---------------------\r\n" );
        Delay_ms ( 1000 );
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
