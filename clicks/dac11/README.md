
---
# DAC 11 Click

> [DAC 11 Click](https://www.mikroe.com/?pid_product=MIKROE-4767) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4767&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of DAC 11 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DAC11

### Example Key Functions

- `dac11_cfg_setup` Config Object Initialization function.
```c
void dac11_cfg_setup ( dac11_cfg_t *cfg );
```

- `dac11_init` Initialization function.
```c
err_t dac11_init ( dac11_t *ctx, dac11_cfg_t *cfg );
```

- `dac11_default_cfg` Click Default Configuration function.
```c
err_t dac11_default_cfg ( dac11_t *ctx );
```

- `dac11_write_control_reg` This function writes data to a single control register by using SPI serial interface.
```c
err_t dac11_write_control_reg( dac11_t *ctx, uint8_t cmd, uint16_t data_in );
```

- `dac11_set_all_ch_voltage` This function sets the output voltage of all channels depending on the vref value defined by the VCC SEL on-board jumper. The VREF and Voltage values can be either in Volts or Milivolts.
```c
err_t dac11_set_all_ch_voltage( dac11_t *ctx, float vref, float voltage );
```

- `dac11_set_specific_ch_voltage` This function sets the output voltage of the specific channels depending on the vref value defined by the VCC SEL on-board jumper. The VREF and Voltage values can be either in Volts or Milivolts.
```c
err_t dac11_set_specific_ch_voltage( dac11_t *ctx, uint8_t channel, float vref, float voltage );
```

### Application Init

> Initializes the driver and executes the Click default configuration which sets the WRM mode and disables all outputs.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    dac11_cfg_t dac11_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    dac11_cfg_setup( &dac11_cfg );
    DAC11_MAP_MIKROBUS( dac11_cfg, MIKROBUS_1 );
    err_t init_flag  = dac11_init( &dac11, &dac11_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    dac11_default_cfg ( &dac11 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the output voltage of all channels every 2 seconds and logs the voltage value on the USB UART. 
It will go through the entire voltage range taking into account the number of steps which is defined below.

```c
void application_task ( void )
{
    float step = REFERENCE_VOLTAGE / NUMBER_OF_STEPS;
    float output_voltage = step;
    uint8_t cnt = 0;
    while ( cnt < NUMBER_OF_STEPS )
    {
        dac11_set_all_ch_voltage ( &dac11, REFERENCE_VOLTAGE, output_voltage );
        log_printf( &logger, " All channels output voltage set to %.2f V\r\n", output_voltage );
        
        output_voltage += step;
        cnt++;
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
