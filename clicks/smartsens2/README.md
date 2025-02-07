
---
# Smart Sens 2 Click

> [Smart Sens 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5207) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5207&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example showcases the ability of the Smart Sens 2 Click board.
It has multiple examples that you can easily select with the
defines at the top of the main. There are 9 examples: Euler, Quaternion,
Vector (Accelerometer, Gyroscope, Magnetometer), and
Environmental (Temperature, Barometer, Humidity, Gas).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartSens2

### Example Key Functions

- `smartsens2_cfg_setup` Config Object Initialization function.
```c
void smartsens2_cfg_setup ( smartsens2_cfg_t *cfg );
```

- `smartsens2_init` Initialization function.
```c
err_t smartsens2_init ( smartsens2_t *ctx, smartsens2_cfg_t *cfg );
```

- `smartsens2_default_cfg` Click Default Configuration function.
```c
err_t smartsens2_default_cfg ( smartsens2_t *ctx );
```

- `smartsens2_register_fifo_parse_callback` Function to link a callback and relevant reference when the sensor event is available in the FIFO.
```c
err_t smartsens2_register_fifo_parse_callback ( smartsens2_t *ctx, uint8_t sensor_id, smartsens2_fifo_parse_callback_t callback, void *callback_ref );
```

- `smartsens2_set_virt_sensor_cfg` Function to set the sample rate and latency of the virtual sensor.
```c
err_t smartsens2_set_virt_sensor_cfg( smartsens2_t *ctx, uint8_t sensor_id, float sample_rate, uint32_t latency );
```

- `smartsens2_get_and_process_fifo` Function to get and process the FIFOs.
```c
err_t smartsens2_get_and_process_fifo ( smartsens2_t *ctx, uint8_t *work_buffer, uint32_t buffer_size );
```

### Application Init

> Initialization of communication modules (SPI/I2C) and additional
pins(int_pin, rst). After that going through reset sequence and checking
device and product IDs, interrupt mask, and host control is set to 0, so
every interrupt enabled. If boot status is OK boot sequence is initiated,
depending on the defines from the library header it will use RAM or Flash type
of the boot. If RAM is selected firmware image first needs to be uploaded to RAM
and then it will be booted. If Flash example is selected it will try to boot
firmware first if it fails it will then write firmware image to flash and then
try to boot it again. When firmware boot is finished Kernel version and Feature
registers will be read to check if the firmware is loaded. Then all the callback function
will be registered(meta event callback and whatever type of example parser you set),
and driver will update the list of virtual sensors present, and finally will configure
virtual sensor that will be used in the selected example.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartsens2_cfg_t smartsens2_cfg;  /**< Click config object. */

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
    smartsens2_cfg_setup( &smartsens2_cfg );
    SMARTSENS2_MAP_MIKROBUS( smartsens2_cfg, MIKROBUS_1 );
    err_t init_flag = smartsens2_init( &smartsens2, &smartsens2_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    /* It can take a few seconds to configure and boot device */
    log_info( &logger, " Configuring device..." );
    if ( SMARTSENS2_ERROR == smartsens2_default_cfg ( &smartsens2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Setting callbacks..." );
    /* Set callbacks */
    if ( smartsens2_register_fifo_parse_callback( &smartsens2, SMARTSENS2_SYS_ID_META_EVENT,
                                                  parse_meta_event, &accuracy ) )
    {
        log_error( &logger, " FIFO sys meta event." );
        for ( ; ; );
    }
    if ( smartsens2_register_fifo_parse_callback( &smartsens2, SMARTSENS2_SYS_ID_META_EVENT_WU,
                                                  parse_meta_event, &accuracy ) )
    {
        log_error( &logger, " FIFO sys meta event wu." );
        for ( ; ; );
    }
    uint8_t sensor_id;
    smartsens2_fifo_parse_callback_t callback;
    void *callback_ref;
#if EULER
    sensor_id = SMARTSENS2_SENSOR_ID_ORI;
    callback = parse_euler;
    callback_ref = &accuracy;
#elif QUATERNION
    sensor_id = SMARTSENS2_SENSOR_ID_RV;
    callback = parse_quaternion;
    callback_ref = NULL;
#elif VECTOR
    #if ACCELEROMETER
        parse_table.sensor[ SMARTSENS2_SENSOR_ID_ACC ].scaling_factor = 1.0f / 4096.0f;
        sensor_id = SMARTSENS2_SENSOR_ID_ACC;
    #elif GYROSCOPE
        parse_table.sensor[ SMARTSENS2_SENSOR_ID_GYRO ].scaling_factor = 1.0f;
        sensor_id = SMARTSENS2_SENSOR_ID_GYRO;
    #elif MAGNETOMETER
        parse_table.sensor[ SMARTSENS2_SENSOR_ID_MAG ].scaling_factor = 1.0f;
        sensor_id = SMARTSENS2_SENSOR_ID_MAG;
    #else
        #error NO_VECTOR_EXAMPLE_DEFINED
    #endif
    callback = parse_vector_s16;
    callback_ref = &parse_table;
#elif ENVIRONMENTAL
    #if TEMPERATURE
        sensor_id = SMARTSENS2_SENSOR_ID_TEMP;
        callback = parse_temperature;
    #elif BAROMETER
        sensor_id = SMARTSENS2_SENSOR_ID_BARO;
        callback = parse_barometer;
    #elif HUMIDITY
        sensor_id = SMARTSENS2_SENSOR_ID_HUM;
        callback = parse_humidity;
    #elif GAS
        sensor_id = SMARTSENS2_SENSOR_ID_GAS;
        callback = parse_gas;
    #else
        #error NO_ENVIRONMENTAL_EXAMPLE_DEFINED
    #endif
    callback_ref = NULL;
#else
    #error NO_EXAMPLE_DEFINED
#endif
    if ( smartsens2_register_fifo_parse_callback( &smartsens2, sensor_id, callback, callback_ref ) )
    {
        log_error( &logger, " FIFO sensor id." );
        for ( ; ; );
    }
    /* Go through fifo process */
    if ( smartsens2_get_and_process_fifo( &smartsens2, work_buffer, WORK_BUFFER_SIZE ) )
    {
        log_error( &logger, " FIFO get and process." );
        for ( ; ; );
    }
    /* Update virtual sensor list in context object */
    if ( smartsens2_update_virtual_sensor_list( &smartsens2 ) )
    {
        log_error( &logger, " Update virtual sensor list." );
        for ( ; ; );
    }
    /* Set virtual sensor configuration */
    float sample_rate = 10.0; /* Read out data at 10Hz */
    uint32_t report_latency_ms = 0; /* Report immediately */
    if ( smartsens2_set_virt_sensor_cfg( &smartsens2, sensor_id, sample_rate, report_latency_ms ) )
    {
        log_error( &logger, " Set virtual sensor configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Wait for an interrupt to occur, then read wake-up, non-weak-up, and status FIFO.
Parse received data and run the callback parsers to show data on the USB UART.

```c
void application_task ( void )
{
    /* Check interrupt and get and process fifo buffer */
    if ( smartsens2_get_interrupt( &smartsens2 ) )
    {
        /* Data from the FIFO is read and the relevant callbacks if registered are called */
        if ( smartsens2_get_and_process_fifo( &smartsens2, work_buffer, WORK_BUFFER_SIZE ) )
        {
            log_error( &logger, " Get and process fifo." );
            for ( ; ; );
        }
    }
}
```

### Note

> Select one of the examples with macros at the top of the main file. Euler example is selected by default.
You can choose one of 4 type of parsers: Euler, Quaternion, Vector, Environmental. If Vector example is selected
you choose one of the 3 sensors to show X, Y, and Z values: Accelerometer, Gyroscope, or Magnetometer.
If Environmental example is selected you choose one of the 4 sensors: Temperature, Barometer, Humidity, or Gas.

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
