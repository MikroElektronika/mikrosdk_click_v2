\mainpage Main Page

---
# DAC 19 Click

> DAC 19 Click is a compact add-on board designed for high-performance voltage-output applications. This board features the DAC53701-Q1, a 10-bit automotive-grade DAC from Texas Instruments, offering smart functionality through force-sense output, GPI function trigger, PWM output, and integrated nonvolatile memory (NVM). The board supports an internal or power supply reference, provides a full-scale output range, and communicates efficiently with microcontrollers using an I2C interface with up to 1MHz clock speed.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dac19_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/dac-19-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the DAC 19 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DAC 19 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example demonstrates the use of DAC 19 Click board by changing the output voltage level.

**The demo application is composed of two sections :**

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

## Note

> Measure the voltage at VCC_SEL jumper and adjust the reference voltage value below for better accuracy.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DAC19

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
