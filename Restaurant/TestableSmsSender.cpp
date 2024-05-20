#include "SmsSender.cpp"
#include <iostream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class TestableSmsSender : public SmsSender {
public:
	MOCK_METHOD(void, send, (Schedule*), (override));

private:
};