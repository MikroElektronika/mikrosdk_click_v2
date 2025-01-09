
---
# Heart Rate Click

> [Heart Rate Click](https://www.mikroe.com/?pid_product=MIKROE-2000) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2000&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This Click features an advanced oximeter and heart rate monitoring sensor, 
> which relies on two integrated LEDs. It is enough to place an index finger on a top 
> of the sensor to get both of the heart rate and blood oxygen saturation via the I2C interface. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HeartRate

### Example Key Functions

- `heartrate_cfg_setup` Config Object Initialization function. 
```c
void heartrate_cfg_setup ( heartrate_cfg_t *cfg );
``` 
 
- `heartrate_init` Initialization function. 
```c
err_t heartrate_init ( heartrate_t *ctx, heartrate_cfg_t *cfg );
```

- `heartrate_default_cfg` Click Default Configuration function. 
```c
void heartrate_default_cfg ( heartrate_t *ctx );
```

- `heartrate_data_ready` Using this function we can check if the data is ready for reading. 
```c
uint8_t heartrate_data_ready ( heartrate_t *ctx );
```
 
- `heartrate_read_ir_red` Using this function we can read IR and RED values. 
```c
uint8_t heartrate_read_ir_red ( heartrate_t *ctx, uint16_t *ir_buff, uint16_t *red_buff );
```

- `heartrate_generic_read` This function reads data from the desired register. 
```c
void heartrate_generic_read ( heartrate_t *ctx, uint8_t reg, uint16_t len, uint8_t *data_buf );
```

### Application Init

> Initializes heartrate driver and set the Click board default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    heartrate_cfg_t cfg;

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

    heartrate_cfg_setup( &cfg );
    HEARTRATE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    heartrate_init( &heartrate, &cfg );

    heartrate_default_cfg( &heartrate );
    Delay_ms ( 100 );
}
```

### Application Task

> Reading values from both Ir and Red diode and displaying their average values on the USB UART.

```c
void application_task ( void )
{
    if ( heartrate_data_ready( &heartrate ) )      
    {
        sample_num = heartrate_read_ir_red( &heartrate, ir_buff, red_buff );             
        if ( sample_num > 0 )
        {
            ir_average = 0;
            red_average = 0;
            for ( uint8_t cnt = 0; cnt < sample_num; cnt++ )
            {              
                ir_average += ir_buff[ cnt ];
                red_average += red_buff[ cnt ];
            }                 
            ir_average  /= sample_num;
            red_average /= sample_num;
            counter++;
            if( red_average > 100 && ir_average > 100 )                
            {       
                log_printf( &logger, "%lu;%lu;\r\n", red_average, ir_average );
                counter = 500;
            }
            else
            {
                if ( counter > 500 ) 
                {
                    log_printf( &logger, "Please place your index finger on the sensor.\r\n" );
                    counter = 0;
                }
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
