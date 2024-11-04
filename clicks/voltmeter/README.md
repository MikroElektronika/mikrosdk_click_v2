\mainpage Main Page
 
---
# Voltmeter Click

> Voltmeter Click is a mikroBUS™ add-on board for measuring voltage in an external electric circuit.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/voltmeter_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/voltmeter-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Voltmeter Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Voltmeter Click driver.

#### Standard key functions :

- `voltmeter_cfg_setup` Config Object Initialization function.
```c
void voltmeter_cfg_setup ( voltmeter_cfg_t *cfg ); 
```

- `voltmeter_init` Initialization function.
```c
err_t voltmeter_init ( voltmeter_t *ctx, voltmeter_cfg_t *cfg );
```

#### Example key functions :

- `voltmeter_read_raw_data` This function reads raw ADC value.
```c
int16_t voltmeter_read_raw_data ( voltmeter_t *ctx );
```

- `voltmeter_calculate_voltage` This function converts the raw ADC value to proportional voltage level.
```c
float voltmeter_calculate_voltage ( voltmeter_t *ctx, int16_t raw_adc, uint8_t iso_gnd );
```

## Example Description

> This application reads the voltage measurement and displays the results on the USB UART.

**The demo application is composed of two sections :**

### Application Init 

> Initialization the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    voltmeter_cfg_t cfg;

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

    //  Click initialization.
    voltmeter_cfg_setup( &cfg );
    VOLTMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    voltmeter_init( &voltmeter, &cfg );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Reads the raw ADC measurement once per second and converts it to the proportional voltage level.
All data are being displayed on the USB UART where you can track their changes.

```c

void application_task ( void )
{
    int16_t adc_value = 0;
    float voltage = 0;

    adc_value = voltmeter_read_raw_data( &voltmeter );
    log_printf( &logger, " ADC Value: %d\r\n", adc_value );

    voltage = voltmeter_calculate_voltage( &voltmeter, adc_value, VOLTMETER_GND_ISO );
    log_printf( &logger, " Voltage  : %.3f V\r\n", voltage );
    log_printf( &logger, "------------------------\r\n");
    Delay_ms ( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Voltmeter

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
