/*
 * I2C.c
 *
 *  Created on: Feb 7, 2018
 *      Author: Sergio
 */
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
#include "fsl_port.h"
#include "fsl_i2c.h"
#include "I2C.h"

volatile bool g_MasterCompletionFlag = false;
i2c_master_config_t masterConfig;
i2c_master_handle_t g_m_handle;
i2c_master_transfer_t masterXfer;
uint8_t buffer[6];
int16_t accelerometer[3];


static void i2c_release_bus_delay(void)
{
    uint32_t i = 0;
    for (i = 0; i < 100; i++)
    {
        __NOP();
    }
}

void i2c_ReleaseBus()
{
	uint8_t i = 0;
	gpio_pin_config_t pin_config;
	port_pin_config_t i2c_pin_config =
	{ 0 };

	/* Config pin mux as gpio */
	i2c_pin_config.pullSelect = kPORT_PullUp;
	i2c_pin_config.mux = kPORT_MuxAsGpio;

	pin_config.pinDirection = kGPIO_DigitalOutput;
	pin_config.outputLogic = 1U;
	CLOCK_EnableClock(kCLOCK_PortE);
	PORT_SetPinConfig(PORTE, 24, &i2c_pin_config);
	PORT_SetPinConfig(PORTE, 25, &i2c_pin_config);

	GPIO_PinInit(GPIOE, 24, &pin_config);
	GPIO_PinInit(GPIOE, 25, &pin_config);

	GPIO_WritePinOutput(GPIOE, 25, 0U);
	i2c_release_bus_delay();

	for (i = 0; i < 9; i++)
	{
		GPIO_WritePinOutput(GPIOE, 24, 0U);
		i2c_release_bus_delay();

		GPIO_WritePinOutput(GPIOE, 25, 1U);
		i2c_release_bus_delay();

		GPIO_WritePinOutput(GPIOE, 24, 1U);
		i2c_release_bus_delay();
		i2c_release_bus_delay();
	}

	GPIO_WritePinOutput(GPIOE, 24, 0U);
	i2c_release_bus_delay();

	GPIO_WritePinOutput(GPIOE, 25, 0U);
	i2c_release_bus_delay();

	GPIO_WritePinOutput(GPIOE, 24, 1U);
	i2c_release_bus_delay();

	GPIO_WritePinOutput(GPIOE, 25, 1U);
	i2c_release_bus_delay();
}

static void i2c_master_callback(I2C_Type *base, i2c_master_handle_t *handle,
        status_t status, void * userData)
{

	if (status == kStatus_Success)
	{
		g_MasterCompletionFlag = true;
	}
}

void i2cinit()
{
	/* Init board hardware. */
		BOARD_InitBootPins();
		BOARD_InitBootClocks();
		BOARD_InitBootPeripherals();
		/* Init FSL debug console. */
		i2c_ReleaseBus();
		BOARD_InitDebugConsole();

		CLOCK_EnableClock(kCLOCK_PortE);
		CLOCK_EnableClock(kCLOCK_I2c0);

		port_pin_config_t config_i2c =
		{ kPORT_PullDisable, kPORT_SlowSlewRate, kPORT_PassiveFilterDisable,
		        kPORT_OpenDrainDisable, kPORT_LowDriveStrength, kPORT_MuxAlt5,
		        kPORT_UnlockRegister, };

		PORT_SetPinConfig(PORTE, 24, &config_i2c);
		PORT_SetPinConfig(PORTE, 25, &config_i2c);

		I2C_MasterGetDefaultConfig(&masterConfig);
		masterConfig.baudRate_Bps = 100000;
		I2C_MasterInit(I2C0, &masterConfig, CLOCK_GetFreq(kCLOCK_BusClk));

		I2C_MasterTransferCreateHandle(I2C0, &g_m_handle, i2c_master_callback,
		NULL);

		uint8_t data_buffer = 0x01;

	#if 0
		masterXfer.slaveAddress = 0x1D;
		masterXfer.direction = kI2C_Write;
		masterXfer.subaddress = 0;
		masterXfer.subaddressSize = 0;
		masterXfer.data = &data_buffer;
		masterXfer.dataSize = 1;
		masterXfer.flags = kI2C_TransferNoStopFlag;

		I2C_MasterTransferNonBlocking(I2C0, &g_m_handle,
				&masterXfer);
		while (!g_MasterCompletionFlag)
		{}
		g_MasterCompletionFlag = false;

		uint8_t read_data;

		masterXfer.slaveAddress = 0x1D;
		masterXfer.direction = kI2C_Read;
		masterXfer.subaddress = 0;
		masterXfer.subaddressSize = 0;
		masterXfer.data = &read_data;
		masterXfer.dataSize = 1;
		masterXfer.flags = kI2C_TransferRepeatedStartFlag;

		I2C_MasterTransferNonBlocking(I2C0, &g_m_handle,
				&masterXfer);
		while (!g_MasterCompletionFlag)
		{}
		g_MasterCompletionFlag = false;
	#else

		masterXfer.slaveAddress = 0x1D;
		masterXfer.direction = kI2C_Write;
		masterXfer.subaddress = 0x2A;
		masterXfer.subaddressSize = 1;
		masterXfer.data = &data_buffer;
		masterXfer.dataSize = 1;
		masterXfer.flags = kI2C_TransferDefaultFlag;

		I2C_MasterTransferNonBlocking(I2C0, &g_m_handle, &masterXfer);
		while (!g_MasterCompletionFlag)	{}
		g_MasterCompletionFlag = false;

	#endif
}

uint16_t getA()
{
			masterXfer.slaveAddress = 0x1D;
			masterXfer.direction = kI2C_Read;
			masterXfer.subaddress = 0x01;
			masterXfer.subaddressSize = 1;
			masterXfer.data = buffer;
			masterXfer.dataSize = 6;
			masterXfer.flags = kI2C_TransferDefaultFlag;

			I2C_MasterTransferNonBlocking(I2C0, &g_m_handle, &masterXfer);

			i2c_ReleaseBus();
			while (!g_MasterCompletionFlag){}
			g_MasterCompletionFlag = false;

			accelerometer[0] = buffer[0] << 8 | buffer[1];
			accelerometer[1] = buffer[2] << 8 | buffer[3];
			accelerometer[2] = buffer[4] << 8 | buffer[5];

			return accelerometer[2];
}
