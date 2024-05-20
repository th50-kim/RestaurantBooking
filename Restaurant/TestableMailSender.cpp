#include "MailSender.cpp"
#include <iostream>

class TestableMailSender : public MailSender {
public:
	void sendMail(Schedule* schedule) override {
		std::cout << "Mail Sender.send() for test" << std::endl;
		countMethodIsCall++;
	}

	int getSendMethodIsCall() {
		return countMethodIsCall;
	}


private:
	int countMethodIsCall = 0;

};