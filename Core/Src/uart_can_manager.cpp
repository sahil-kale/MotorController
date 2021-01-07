#include "uart_can_manager.hpp"
#include "usart.h"
#include "can.h"
#include <bits/stdc++.h>

/*******UART DECLERATIONS*******/
extern UART_HandleTypeDef huart2;
const int MAX_CHARS = 1000;
const int UART_TX_TIMEOUT = 10;
const int UART_RX_TIMEOUT = 1000;

/*******CAN DECLERATIONS*******/
extern CAN_HandleTypeDef hcan2;
static CAN_TxHeaderTypeDef txCanMsg;
static CAN_RxHeaderTypeDef rxCanMsg;
const uint16_t DEVICE_ID = 0x254;
const uint16_t TARGET_ID = 0x200;
uint32_t TxMailbox;
uint8_t rxData;

UART_CAN_Manager::UART_CAN_Manager()
{
	CANConfig();
}

UART_CAN_Manager* UART_CAN_Manager::s_instance = nullptr;

UART_CAN_Manager* UART_CAN_Manager::GetInstance()
{
	if(!s_instance)
	{
		s_instance = new UART_CAN_Manager();
	}

	return s_instance;
}

void UART_CAN_Manager::sendUART(std::string input)
{
	if(input.length() <= MAX_CHARS)
	{
		char stringToWrite[MAX_CHARS+1] = {'\0'}; //initalize with EOF char
		strcpy(stringToWrite, input.c_str());
		HAL_UART_Transmit(&huart2, (uint8_t*)stringToWrite, input.length(), UART_TX_TIMEOUT);
		char newline[3] = "\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)newline, 3, UART_TX_TIMEOUT);
	}
}

std::string UART_CAN_Manager::readUARTBuffer() //can only read 8 bits
{
	char in[8];
	HAL_UART_Receive(&huart2, (uint8_t*)in, 8, UART_RX_TIMEOUT);
	std::string returnString(in);
	return returnString;
}

void UART_CAN_Manager::CANConfig()
{
	const int NO_OF_BYTES_PER_CAN_MSG = 1;
	txCanMsg.DLC=NO_OF_BYTES_PER_CAN_MSG;
	txCanMsg.IDE=CAN_ID_STD;
	txCanMsg.StdId=DEVICE_ID;
	txCanMsg.RTR=CAN_RTR_DATA; //Set the RTR for request frame remote transmission request

	CAN_FilterTypeDef filterConfig;
	/***DO NOT TOUCH!! DEFAULT INITALIZATIONS!!***/
	filterConfig.FilterActivation = ENABLE;
	filterConfig.FilterFIFOAssignment = 0;
	filterConfig.FilterIdHigh = TARGET_ID << 5;
	filterConfig.FilterIdLow = 0x0000;
	filterConfig.FilterMaskIdHigh = 0;
	filterConfig.FilterMaskIdLow = 0;
	filterConfig.FilterScale = CAN_FILTERSCALE_32BIT;

	HAL_CAN_ConfigFilter(&hcan2, &filterConfig);
	HAL_CAN_Start(&hcan2);

	HAL_CAN_ActivateNotification(&hcan2, CAN_RX_FIFO0);
}

void UART_CAN_Manager::AddCanTxMessage(uint8_t msg)
{
	HAL_CAN_AddTxMessage(&hcan2, &txCanMsg, &msg, &TxMailbox);
}

uint8_t UART_CAN_Manager::GetMostRecentCANMessage()
{
	return rxData;
}

void CAN2_RX0_IRQHandler()
{
	HAL_CAN_IRQHandler(&hcan2); //no clue what this line does, it is srequired by CAN though?
	HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &rxCanMsg, &rxData);
}



