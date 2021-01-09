#ifndef UART_CAN_MANAGER_HPP
#define UART_CAN_MANAGER_HPP
#include <string>

class UART_CAN_Manager
{
	public:
		UART_CAN_Manager(const UART_CAN_Manager*) = delete;
		static UART_CAN_Manager* GetInstance();

		void sendUART(std::string input);
		void sendCAN(std::string input);
		std::string readUARTBuffer();

	private:
		UART_CAN_Manager();
		static UART_CAN_Manager* s_instance;
		void CANConfig();
		void AddCanTxMessage(uint8_t msg);
		uint8_t GetMostRecentCANMessage();
};


#endif
