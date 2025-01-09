
---
# DAC 10 Click

> [DAC 10 Click](https://www.mikroe.com/?pid_product=MIKROE-4732) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4732&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of DAC 10 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DAC10

### Example Key Functions

- `dac10_cfg_setup` Config Object Initialization function.
```c
void dac10_cfg_setup ( dac10_cfg_t *cfg );
```

- `dac10_init` Initialization function.
```c
err_t dac10_init ( dac10_t *ctx, dac10_cfg_t *cfg );
```

- `dac10_check_device_id` This function checks the communication by reading and verifying the device ID.
```c
err_t dac10_check_device_id ( dac10_t *ctx );
```

- `dac10_enable_dac` This function enables the DAC output.
```c
err_t dac10_enable_dac ( dac10_t *ctx );
```

- `dac10_set_output_voltage` This function sets the output voltage depending on the vref value defined by the VCC SEL on-board jumper. VREF and Voltage values can be either in Volts or Milivolts.
```c
err_t dac10_set_output_voltage ( dac10_t *ctx, float vref, float voltage );
```

### Application Init

> Initializes the driver, checks the communication by reading and verifying the device ID, and enables the DAC output.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac10_cfg_t dac10_cfg;  /**< Click config object. */

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
    dac10_cfg_setup( &dac10_cfg );
    DAC10_MAP_MIKROBUS( dac10_cfg, MIKROBUS_1 );
    err_t init_flag = dac10_init( &dac10, &dac10_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    if ( DAC10_ERROR == dac10_check_device_id ( &dac10 ) ) 
    {
        log_error( &logger, " Check Device ID Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    dac10_enable_dac( &dac10 );
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the output voltage every 2 seconds and logs the voltage value on the USB UART.
> It will go through the entire voltage range taking into account the number of steps 
> which is defined below.

```c
void application_task ( void )
{
    float step = REFERENCE_VOLTAGE / NUMBER_OF_STEPS;
    float output_voltage = step;
    uint8_t cnt = 0;
    while ( cnt < NUMBER_OF_STEPS )
    {
        dac10_set_output_voltage ( &dac10, REFERENCE_VOLTAGE, output_voltage );
        log_printf( &logger, " DAC output voltage set to %.2f V\r\n", output_voltage );
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
