
---
# Smart Sens click

> Smart Sens Click is a compact add-on board that contains an intelligent sensor hub with an integrated IMU sensor. This board utilizes the BHI260 and BMM150, an environmental sensor and magnetometer from Bosch Sensortech. The BHI260 includes a programmable and powerful 32-bit MCU, a 6-axis IMU, and a robust software framework. In addition to its internal functions, it also performs signal data processing from the BMM150 that performs measurements of the magnetic field in three perpendicular axes.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/smartsens_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/smart-sens-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Oct 2021.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Smart Sens Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Smart Sens Click driver.

#### Standard key functions :

- `smartsens_cfg_setup` Config Object Initialization function.
```c
void smartsens_cfg_setup ( smartsens_cfg_t *cfg );
```

- `smartsens_init` Initialization function.
```c
err_t smartsens_init ( smartsens_t *ctx, smartsens_cfg_t *cfg );
```

- `smartsens_default_cfg` Click Default Configuration function.
```c
err_t smartsens_default_cfg ( smartsens_t *ctx );
```

#### Example key functions :

- `smartsens_cmd_write` Send command.
```c
err_t smartsens_cmd_write ( smartsens_t *ctx, uint16_t cmd, uint8_t *cmd_buf, uint16_t cmd_len );
```

- `smartsens_get_parameter` Get command parameters resposne.
```c
err_t smartsens_get_parameter ( smartsens_t *ctx, uint16_t parameter, 
                                uint8_t *parameter_buf, uint16_t *parameter_len );
```

- `smartsens_power_on_device` Power on device boot/upload firmware to device.
```c
err_t smartsens_power_on_device( smartsens_t *ctx );
```

## Example Description

> This example showcases the ability of the Smart Sens click board.
It has multiple examples that you can easily select with the 
defines at top of the main. There are 5 examples Euler, Quaternion,
and Vector examples for Accelerometer, Gyroscope, and Magnetometer.

**The demo application is composed of two sections :**

### Application Init

> Initialization of communication modules(SPI/I2C, UART) and additional 
pins(int_pin, rst). Then after going through reset sequence and checking
device and product IDs, interrupt mask, and host control is set to 0, so
every interrupt enabled. IF boot status is OK boot sequence is initiated,
depending on the defines from the library header it will use RAM or Flash type
of the boot. If RAM is selected firmware image first needs to be uploaded to RAM
and then it will be booted. If Flash example is selected it will try to boot
firmware first if it fails it will then write firmware image to flash and then
try to boot it again. When firmware boot is finished Kernel version and Feature
registers will be read to check if the firmware is loaded. Then all the callback function
will be registered(meta event callback and whatever type of example parser you set),
and driver will update its the list of virtual sensors present, and finally will configure
virtual sensor that will be used in the selected example.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartsens_cfg_t smartsens_cfg;  /**< Click config object. */

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
    smartsens_cfg_setup( &smartsens_cfg );
    SMARTSENS_MAP_MIKROBUS( smartsens_cfg, MIKROBUS_1 );
    err_t init_flag  = smartsens_init( &smartsens, &smartsens_cfg );
    SMARTSENS_SET_DATA_SAMPLE_EDGE
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    /* It can take a few seconds to configure and boot device*/
    log_info( &logger, " Configuring device..." );
    if ( SMARTSENS_ERROR == smartsens_default_cfg ( &smartsens ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Setting callbacks..." );
    /*Set callbacks*/
    if ( smartsens_register_fifo_parse_callback( &smartsens, SMARTSENS_SYS_ID_META_EVENT,
                                                 parse_meta_event, (void*)&accuracy ) )
    {
        log_error( &logger, " FIFO sys meta event." );
        for( ; ; );
    }
    if ( smartsens_register_fifo_parse_callback( &smartsens, SMARTSENS_SYS_ID_META_EVENT_WU,
                                                 parse_meta_event, ( void* )&accuracy ) )
    {
        log_error( &logger, " FIFO sys meta event wu." );
        for( ; ; );
    }
#if EULAR
    if ( smartsens_register_fifo_parse_callback( &smartsens, SMARTSENS_SENSOR_ID_ORI_WU, 
                                                 parse_euler, ( void* )&accuracy ) )
#elif QUATERNION
    if ( smartsens_register_fifo_parse_callback( &smartsens, SMARTSENS_SENSOR_ID_RV_WU, 
                                                 parse_quaternion, NULL ) )
#elif VECTOR
    
        
    #if ACCELEROMETER
        parse_table.sensor[SMARTSENS_SENSOR_ID_ACC].scaling_factor = 1.0f / 4096.0f;
        if ( smartsens_register_fifo_parse_callback( &smartsens, SMARTSENS_SENSOR_ID_ACC, 
                                                    parse_3axis_s16, &parse_table ) )
    #elif GYROSCOPE
        parse_table.sensor[SMARTSENS_SENSOR_ID_GYRO].scaling_factor = 1.0f;
        if ( smartsens_register_fifo_parse_callback( &smartsens, SMARTSENS_SENSOR_ID_GYRO, 
                                                    parse_3axis_s16, &parse_table ) )
    #elif MAGNOMETER
        parse_table.sensor[SMARTSENS_SENSOR_ID_MAG].scaling_factor = 1.0f;
        if ( smartsens_register_fifo_parse_callback( &smartsens, SMARTSENS_SENSOR_ID_MAG, 
                                                    parse_3axis_s16, &parse_table ) )
    #else
        #error NO_VECTOR_EXAMPLE_DEFINED
    #endif
#else
    #error NO_EXAMPLE_DEFINED
#endif
    {
        log_error( &logger, " FIFO sensor id." );
        for( ; ; );
    }
    /*Go through fifo process*/
    if ( smartsens_get_and_process_fifo( &smartsens, work_buffer, WORK_BUFFER_SIZE ) )
    {
        log_error( &logger, " FIFO get and process." );
        for( ; ; );
    }
    /*Update virtual sensor list in context object*/
    if ( smartsens_update_virtual_sensor_list( &smartsens ) )
    {
        log_error( &logger, " Update virtual sensor list." );
        for( ; ; );
    }
    /*Set virtual sensor configuration*/
    float sample_rate = 100.0; /* Read out data measured at 100Hz */
    uint32_t report_latency_ms = 0; /* Report immediately */
#if EULAR
    if ( smartsens_set_virt_sensor_cfg( &smartsens, SMARTSENS_SENSOR_ID_ORI_WU, 
                                        sample_rate, report_latency_ms ) )
#elif QUATERNION
    if ( smartsens_set_virt_sensor_cfg( &smartsens, SMARTSENS_SENSOR_ID_RV_WU, 
                                    sample_rate, report_latency_ms ) )
#elif VECTOR
    #if ACCELEROMETER
        if ( smartsens_set_virt_sensor_cfg( &smartsens, SMARTSENS_SENSOR_ID_ACC, 
                                    sample_rate, report_latency_ms ) )
    #elif GYROSCOPE
        if ( smartsens_set_virt_sensor_cfg( &smartsens, SMARTSENS_SENSOR_ID_GYRO, 
                                    sample_rate, report_latency_ms ) )
    #elif MAGNOMETER
        if ( smartsens_set_virt_sensor_cfg( &smartsens, SMARTSENS_SENSOR_ID_MAG, 
                                    sample_rate, report_latency_ms ) )
    #else
        #error NO_VECTOR_EXAMPLE_DEFINED
    #endif
#else
    #error NO_EXAMPLE_DEFINED
#endif
    {
        log_error( &logger, " Set virtual sensor configuration." );
        for( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Wait for an interrupt to occur. When occurred read wake-up, non-weak-up, and status FIFO.
Parse received that and run the callback parsers to show received data.

```c
void application_task ( void )
{
    /*Check interrupt and get and process fifo buffer*/
    if ( smartsens_get_interrupt( &smartsens ) )
    {
        /* Data from the FIFO is read and the relevant callbacks if registered are called */
        if ( smartsens_get_and_process_fifo( &smartsens, work_buffer, WORK_BUFFER_SIZE ) )
        {
            log_error( &logger, " Get and process fifo." );
            for( ; ; );
        }
    }
}
```

## Note

> You need to select one of the examples to use this application. You can choose one of 3 
type of parsers: Eular, Quaternion, Vector. If Vector example is selected you need to 
choose one of the 3 sensors to show x,y,z values: Accelerometer, Gyroscope, or Magnetometer.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartSens

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
