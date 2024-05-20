#include "MailSender.cpp"
#include <iostream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class TestableMailSender : public MailSender {
public:
	MOCK_METHOD(void, sendMail, (Schedule*), (override));
};