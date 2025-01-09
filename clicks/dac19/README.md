
---
# DAC 19 Click

> [DAC 19 Click](https://www.mikroe.com/?pid_product=MIKROE-6406) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6406&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of DAC 19 Click board by changing the output voltage level.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DAC19

### Example Key Functions

- `dac19_cfg_setup` Config Object Initialization function.
```c
void dac19_cfg_setup ( dac19_cfg_t *cfg );
```

- `dac19_init` Initialization function.
```c
err_t dac19_init ( dac19_t *ctx, dac19_cfg_t *cfg );
```

- `dac19_default_cfg` Click Default Configuration function.
```c
err_t dac19_default_cfg ( dac19_t *ctx );
```

- `dac19_set_voltage` This function sets the output voltage depending on the vref value defined by the VCC SEL on-board jumper. VREF and Voltage values can be either in Volts or Milivolts.
```c
err_t dac19_set_voltage ( dac19_t *ctx, uint16_t vref_mv, uint16_t voltage_mv );
```

- `dac19_set_value` This function sets the DAC DATA register to a desired value.
```c
err_t dac19_set_value ( dac19_t *ctx, uint16_t data_in );
```

- `dac19_set_voltage_int_vref` This function sets the output voltage with the internal reference enabled. 
```c
err_t dac19_set_voltage_int_vref ( dac19_t *ctx, uint16_t voltage_mv );
```

### Application Init

> Initializes the driver, checks the communication by reading and verifying the device ID, and enables the DAC output.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac19_cfg_t dac19_cfg;  /**< Click config object. */

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
    dac19_cfg_setup( &dac19_cfg );
    DAC19_MAP_MIKROBUS( dac19_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == dac19_init( &dac19, &dac19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DAC19_ERROR == dac19_default_cfg ( &dac19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the output voltage every 2 seconds and logs the voltage value on the USB UART.
It will go through the entire voltage range for the step number defined below.

```c
void application_task ( void )
{
    uint16_t step = REFERENCE_VOLTAGE_MV / NUMBER_OF_STEPS;
    uint16_t output_voltage = step;
    for ( uint8_t cnt = 0; cnt < NUMBER_OF_STEPS; cnt++ )
    {
        if ( DAC19_OK == dac19_set_voltage ( &dac19, REFERENCE_VOLTAGE_MV, output_voltage ) )
        {
            log_printf( &logger, " VOUT: %u mV\r\n", output_voltage );
        }
        output_voltage += step;
        Delay_ms ( 1000 ); 
        Delay_ms ( 1000 );
    }
}
```

### Note

> Measure the voltage at VCC_SEL jumper and adjust the reference voltage value below for better accuracy.

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
