
---
# Oximeter 3 Click

> [Oximeter 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4267) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4267&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Oximeter 3 Click board. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Oximeter3

### Example Key Functions

- `oximeter3_cfg_setup` Config Object Initialization function. 
```c
void oximeter3_cfg_setup ( oximeter3_cfg_t *cfg );
``` 
 
- `oximeter3_init` Initialization function. 
```c
err_t oximeter3_init ( oximeter3_t *ctx, oximeter3_cfg_t *cfg );
```

- `oximeter3_generic_read` Generic read function. 
```c
uint8_t oximeter3_generic_read ( oximeter3_t *ctx, uint8_t reg );
```
 
- `oximeter3_get_int_status` Gets state of the int pin. 
```c
uint8_t oximeter3_get_int_status ( oximeter3_t *ctx );
```

- `oximeter3_read_value` Generic function for reading als and proximity values. 
```c
uint16_t oximeter3_read_value ( oximeter3_t *ctx, uint8_t type_macro );
```

### Application Init

> Initializes the driver, checks the device ID then configures the device for the selected mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    oximeter3_cfg_t cfg;

    uint8_t dev_status;

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

    oximeter3_cfg_setup( &cfg );
    OXIMETER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    oximeter3_init( &oximeter3, &cfg );

    dev_status = oximeter3_generic_read( &oximeter3, OXIMETER3_REG_PRODUCT_ID );
    
    if ( dev_status != OXIMETER3_ID_VAL )
    {
        log_printf( &logger, " *****  ERROR!  ***** \r\n" );
        for ( ; ; );
    }

    dev_mode = OXIMETER3_HEART_RATE;
    
    oximeter3_generic_write( &oximeter3, OXIMETER3_REG_COMMAND,
                                         OXIMETER3_CMD_MEASUREMENT_DISABLE );
    
    oximeter3_generic_write( &oximeter3, OXIMETER3_REG_INTERRUPT_CTRL,
                                         OXIMETER3_INT_STATUS_PROX );
    
    if ( OXIMETER3_HEART_RATE == dev_mode )
    {
        oximeter3_generic_write( &oximeter3, OXIMETER3_REG_LED_CURRENT, 
                                             OXIMETER3_LED_CURR_MID );
        oximeter3_generic_write( &oximeter3, OXIMETER3_REG_PROX_MODULATOR_TIMING,
                                             OXIMETER3_PROX_TIMING_FREQ_390p625_KHZ );
    }
    else
    {
        oximeter3_generic_write( &oximeter3, OXIMETER3_REG_LED_CURRENT, 
                                             OXIMETER3_LED_CURR_MIN );
        oximeter3_generic_write( &oximeter3, OXIMETER3_REG_PROX_MODULATOR_TIMING,
                                             OXIMETER3_PROX_TIMING_FREQ_3p125_MHZ );
    }
    
    oximeter3_generic_write( &oximeter3, OXIMETER3_REG_PROX_RATE,
                                         OXIMETER3_PROX_RATE_250_MPS );

    oximeter3_generic_write( &oximeter3, OXIMETER3_REG_COMMAND,
                                         OXIMETER3_CMD_MEASUREMENT_ENABLE |
                                         OXIMETER3_CMD_PROX_PERIODIC_MEASUREMENT_ENABLE |
                                         OXIMETER3_CMD_ALS_PERIODIC_MEASUREMENT_ENABLE );

    log_printf( &logger, " ***** APP TASK ***** \r\n" );
}
```

### Application Task

> Depending on the selected mode it reads heart rate data (OXIMETER3_HEART_RATE mode) or
> values of proximity and ambient light sensor (OXIMETER3_PROX or OXIMETER3_ALS modes).
> All data is being logged on USB UART where you can track their changes.

```c
void application_task ( void )
{
    if ( OXIMETER3_HEART_RATE == dev_mode )
    {
        if( !oximeter3_get_int_status( &oximeter3 ) )
        {
            rd_val = oximeter3_read_value( &oximeter3, OXIMETER3_PROX );
            oximeter3_generic_write( &oximeter3, OXIMETER3_REG_INTERRUPT_STATUS, 
                                                 OXIMETER3_INT_STATUS_PROX );
            
            counter++;
            if ( rd_val > 10000 )
            {
                log_printf( &logger, "%u\r\n", rd_val );
                counter = 2500;
            }
            else if ( counter > 2500 )
            {
                log_printf( &logger, "Please place your index finger on the sensor.\r\n" );
                counter = 0;
            }
        }
    }
    else if ( OXIMETER3_PROX == dev_mode || OXIMETER3_ALS == dev_mode )
    {
        if( !oximeter3_get_int_status( &oximeter3 ) )
        {
            rd_val = oximeter3_read_value( &oximeter3, OXIMETER3_PROX );
            oximeter3_generic_write( &oximeter3, OXIMETER3_REG_INTERRUPT_STATUS, 
                                                 OXIMETER3_INT_STATUS_PROX );
            
            log_printf( &logger, " * Proximity: %u \r\n", rd_val );
        
            rd_val = oximeter3_read_value( &oximeter3, OXIMETER3_ALS );
            log_printf( &logger, " * ALS: %u \r\n", rd_val );
            
            log_printf( &logger, "******************** \r\n" );
            
            Delay_ms ( 500 );
        }
    }
}
```

### Note

> In the case of heart rate, please use a Serial Plot application for data plotting.

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
