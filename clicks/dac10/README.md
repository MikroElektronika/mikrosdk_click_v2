\mainpage Main Page

---
# DAC 10 click

DAC 10 Click is a compact add-on board that contains a fully-featured, highly accurate digital-to-analog converter. This board features the DAC53401, a 10-bit voltage-output smart digital-to-analog converter from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dac_10_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dac-10-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the DAC10 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DAC10 Click driver.

#### Standard key functions :

- `dac10_cfg_setup` Config Object Initialization function.
```c
void dac10_cfg_setup ( dac10_cfg_t *cfg );
```

- `dac10_init` Initialization function.
```c
err_t dac10_init ( dac10_t *ctx, dac10_cfg_t *cfg );
```

#### Example key functions :

- `dac10_check_device_id` This function checks the communication by reading and verifying the device ID.
```c
err_t dac10_check_device_id ( dac10_t *ctx );
```

- `dac10_enable_dac` This function enables the DAC output.
```c
err_t dac10_enable_dac ( dac10_t *ctx );
```

- `dac10_set_output_voltage` This function sets the output voltage depending on the vref value defined by 
the VCC SEL on-board jumper. VREF and Voltage values can be either in Volts or Milivolts.
```c
err_t dac10_set_output_voltage ( dac10_t *ctx, float vref, float voltage );
```

## Example Description

> This example demonstrates the use of DAC 10 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, checks the communication by reading and verifying the device ID, and enables the DAC output.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac10_cfg_t dac10_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    Delay_ms( 100 );
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
    Delay_ms( 100 );
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
        Delay_ms( 2000 );
    }
}

```

## Note

> Measure the voltage at VCC_SEL jumper and adjust the reference voltage value below for better accuracy.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DAC10

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
