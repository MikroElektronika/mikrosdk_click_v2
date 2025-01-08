
---
# LDC Click

> [LDC Click](https://www.mikroe.com/?pid_product=MIKROE-4784) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4784&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Jul 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example showcases abillity of the device to detect 
metal objects. It configures device for reading data from 
channel 0, checks if ID's are OK and reads data when interrupt 
is asserted and logs result.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LDC

### Example Key Functions

- `ldc_cfg_setup` Config Object Initialization function.
```c
void ldc_cfg_setup ( ldc_cfg_t *cfg );
```

- `ldc_init` Initialization function.
```c
err_t ldc_init ( ldc_t *ctx, ldc_cfg_t *cfg );
```

- `ldc_default_cfg` Click Default Configuration function.
```c
err_t ldc_default_cfg ( ldc_t *ctx );
```

- `ldc_get_interrupt` Get interrupt pin status.
```c
uint8_t ldc_get_interrupt ( ldc_t *ctx );
```

- `ldc_get_frequency` Get frequency value calculated for specific channel.
```c
err_t ldc_get_frequency ( ldc_t *ctx, uint8_t channel, uint16_t divider, float *frequency );
```

- `ldc_calculate_inductance` Calculate inductance relative to frequency.
```c
float ldc_calculate_inductance ( float frequency );
```

### Application Init

> Initialization of communication modules (I2C, UART) and 
additional pins. Then configures the device for reading data from 
channel 0, and checks if device ID's are correctly read, and
read the currently set divider.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ldc_cfg_t ldc_cfg;  /**< Click config object. */

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
    ldc_cfg_setup( &ldc_cfg );
    LDC_MAP_MIKROBUS( ldc_cfg, MIKROBUS_1 );
    err_t init_flag = ldc_init( &ldc, &ldc_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    if ( ldc_default_cfg ( &ldc ) < 0 )
    {
        log_error( &logger, " Default configuration. " );
        for ( ; ; );
    }
    
    uint16_t temp_data = 0;
    ldc_generic_read( &ldc, LDC_REG_MANUFACTURER_ID, &temp_data );
    log_printf( &logger, "> Manufacturer ID: 0x%.4X\r\n", temp_data );
    if ( LDC_MANUFACTURER_ID != temp_data )
    {
        log_error( &logger, " Manufacturer ID. " );
        for ( ; ; );
    }
    
    ldc_generic_read( &ldc, LDC_REG_DEVICE_ID, &temp_data );
    log_printf( &logger, "> Device ID 0x%.4X\r\n", temp_data );
    if ( LDC_DEVICE_ID != temp_data )
    {
        log_error( &logger, " Device ID. " );
        for ( ; ; );
    }
    
    ldc_generic_read( &ldc, LDC_REG_CLOCK_DIVIDERS_CH0, &temp_data );
    divider = temp_data & 0x3FF;
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Checks if interrupt pin is asserted, if so reads data from channel 0.
Calculates and returns the frequency of the sensor. If the frequency 
is greater than 0, then it calculates the inductance of the sensor. 
It will log error and error values if it occurred.

```c
void application_task ( void ) 
{
    if ( !ldc_get_interrupt( &ldc ) )
    {
        float frequency = 0.0;
        float inductance = 0.0;
        uint16_t status = 0;
        ldc_generic_read( &ldc, LDC_REG_STATUS, &status );
        if ( status & LDC_STATUS_DRDY )
        {
            err_t ret_val = ldc_get_frequency( &ldc, LDC_REG_DATA_CH0, divider, &frequency );
            if ( !ret_val )
            {
                log_printf( &logger, "> Freq[MHz]: %.3f\r\n", frequency );
                if ( frequency > 0 )
                {
                    inductance = ldc_calculate_inductance( frequency );
                }
                log_printf( &logger, "> L[uH]: %.3f\r\n", inductance );
                log_printf( &logger, "> ************************\r\n" );
                
                Delay_ms ( 500 );
            }
            else
            {
                log_error( &logger, " Reading data: %ld", ret_val );
            }
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
