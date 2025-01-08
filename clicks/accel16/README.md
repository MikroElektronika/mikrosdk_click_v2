
---
# Accel 16 Click

> [Accel 16 Click](https://www.mikroe.com/?pid_product=MIKROE-4876) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4876&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Sep 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This showcases ability of the Click board to 
read x, y, and z axes data in different resolution,
read IC temperature and also have additional functionality
to read ADC data. Device also has ability to store data 
in internal fifo buffer.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel16

### Example Key Functions

- `accel16_cfg_setup` Config Object Initialization function.
```c
void accel16_cfg_setup ( accel16_cfg_t *cfg );
```

- `accel16_init` Initialization function.
```c
err_t accel16_init ( accel16_t *ctx, accel16_cfg_t *cfg );
```

- `accel16_default_cfg` Click Default Configuration function.
```c
err_t accel16_default_cfg ( accel16_t *ctx );
```

- `accel16_get_axes` Get axes data.
```c
err_t accel16_get_axes ( accel16_t *ctx, accel16_axes_t *axes );
```

- `accel16_filter_configuration` Filter configuration.
```c
err_t accel16_filter_configuration ( accel16_t *ctx, accel16_gain_t gain, accel16_output_rate_t odr );
```

- `accel16_get_temperature` Get temperature data.
```c
err_t accel16_get_temperature ( accel16_t *ctx, float *temperature );
```

### Application Init

> Initialization of communication modules(SPI, UART) and 
additional interrupt pins. Reads device ID's and revision.
Then configures device to work in FIFO mode or to read data
from the registers, sets 2g resolution, 12.5Hz output data rate,
sets interrupt 1 active low, powers on device, and calibrates temperature.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel16_cfg_t accel16_cfg;  /**< Click config object. */

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
    accel16_cfg_setup( &accel16_cfg );
    ACCEL16_MAP_MIKROBUS( accel16_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == accel16_init( &accel16, &accel16_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    accel16.application_type = ACCEL16_APPLICATION_REG;
    
    uint8_t temp_buf[ 4 ] = { 0 };
    
    accel16_multiple_reg_read( &accel16, ACCEL16_REG_DEVID_AD, temp_buf, 4 );
    log_printf( &logger, " > ID0: 0x%.2X\r\n > ID1: 0x%.2X\r\n > ID2: 0x%.2X\r\n > REV: 0x%.2X\r\n", 
                ( uint16_t ) temp_buf[ 0 ], ( uint16_t ) temp_buf[ 1 ], 
                ( uint16_t ) temp_buf[ 2 ], ( uint16_t ) temp_buf[ 3 ] );
    
    
    if ( ACCEL16_ERROR == accel16_default_cfg ( &accel16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Depending of the application mode selects example. 
 - If fifo example is selected waits for the interrupt 
     to indicate that data is ready  in fifo buffer and 
     reads number of fifo entries. Data that should be 
     read are X, Y, Z axes and temperature.
 - If register example is selected also waits for interrupt
     to indicate that data is ready to read. Then reads X, Y, Z
     axes, temperature, and ADC data.

```c
void application_task ( void )
{   
    if ( ACCEL16_APPLICATION_FIFO == accel16.application_type )
    {
        accel16_read_fifo_data( );
    }
    else if ( ACCEL16_APPLICATION_REG == accel16.application_type )
    {
        accel16_read_reg_data( );
    }

    log_printf( &logger, "********************************************************\r\n" );
    Delay_ms ( 300 );
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
