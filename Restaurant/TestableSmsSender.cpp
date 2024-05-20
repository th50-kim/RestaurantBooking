#include "SmsSender.cpp"
#include <iostream>

class TestableSmsSender : public SmsSender {
public:
	void send(Schedule* schedule) override{
		std::cout << "SMS Sender.send() for test" << std::endl;
		sendMethodIsCall = true;
	}

	bool isSendMethodIsCall() {
		return sendMethodIsCall;
	}
	

private:
	bool sendMethodIsCall;
};