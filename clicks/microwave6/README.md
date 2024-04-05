\mainpage Main Page

---
# Microwave 6 click

> Microwave 6 Click is a compact add-on board that utilizes the Doppler Shift Phenomenon to sense motion. 
> This board features the PD-V8-S, a high-frequency microwave sensor from Ningbo Pdlux Electronic Technology. 
> The transmitter on this transceiver works on a 5.8GHz frequency over the patch antenna, 
> with a 2-3kHz pulse repetition frequency. The strength of the sensor’s output, in other words, 
> the detection range, depends on the Signal-to-Noise ratio. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/microwave6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/microwave-6-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : May 2023.
- **Type**          : ADC/I2C type


# Software Support

We provide a library for the Microwave 6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Microwave 6 Click driver.

#### Standard key functions :

- `microwave6_cfg_setup` Config Object Initialization function.
```c
void microwave6_cfg_setup ( microwave6_cfg_t *cfg );
```

- `microwave6_init` Initialization function.
```c
err_t microwave6_init ( microwave6_t *ctx, microwave6_cfg_t *cfg );
```

#### Example key functions :

- `microwave6_read_raw_adc` Microwave 6 read raw ADC value function.
```c
err_t microwave6_read_raw_adc ( microwave6_t *ctx, uint16_t *raw_adc );
```

- `microwave6_read_voltage` Microwave 6 read voltage level function.
```c
err_t microwave6_read_voltage ( microwave6_t *ctx, float *voltage );
```

- `microwave6_set_vref` Microwave 6 set vref function.
```c
err_t microwave6_set_vref ( microwave6_t *ctx, float vref );
```

## Example Description

> This example demonstrates the use of the Microwave 6 Click board™ 
> by reading and displaying the results of AD conversion and motion detection.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C or ADC module and log UART.
> After driver initialization, the app calculates the reference ADC value.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    microwave6_cfg_t microwave6_cfg;  /**< Click config object. */

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
    microwave6_cfg_setup( &microwave6_cfg );
    MICROWAVE6_MAP_MIKROBUS( microwave6_cfg, MIKROBUS_1 );
    err_t init_flag = microwave6_init( &microwave6, &microwave6_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Calibrating the sensor...\r\n" );
    log_printf( &logger, " There must be no movement near the sensor!\r\n" );
    log_printf( &logger, "----------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    if ( MICROWAVE6_OK == microwave6_read_voltage( &microwave6, &reference ) )
    {
        log_printf( &logger, " The sensor has been calibrated!\r\n" );
        log_printf( &logger, "  Detector AN Voltage : %.3f[V]\r\n", reference );
        log_printf( &logger, "----------------------------------\r\n" );
        Delay_ms ( 100 );
    }
    else
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    
    log_printf( &logger, "The motion detector unit is ready.\r\n" );
    log_printf( &logger, "----------------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application reads the ADC results, takes an ADC sample, 
> compares the difference between the taken samples and the ADC reference value, 
> and reports the movement if the difference is higher/lower than the selected threshold value.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    if ( MICROWAVE6_OK == microwave6_read_voltage( &microwave6, &voltage ) )
    {
        if ( ( ( voltage + MICROWAVE6_THRESHOLD ) < reference ) || 
             ( ( voltage - MICROWAVE6_THRESHOLD ) > reference ) )
        {
            if ( MICROWAVE6_FLAG_SET == flag )
            {
                log_printf( &logger, " Motion detected!\r\n" );
                log_printf( &logger, " Detector AN Voltage : %.3f[V]\r\n", voltage );
                log_printf( &logger, "----------------------------------\r\n" );
                flag = MICROWAVE6_FLAG_CLEAR;
                Delay_ms ( 100 );
            }
        }
        else
        {
            flag = MICROWAVE6_FLAG_SET;
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Microwave6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
