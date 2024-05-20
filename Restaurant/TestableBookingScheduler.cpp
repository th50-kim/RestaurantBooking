#include "BookingScheduler.cpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class TestableBookingScheduler : public BookingScheduler {
public:
    TestableBookingScheduler() {}
    TestableBookingScheduler(int capacity) :BookingScheduler(capacity)
    {
    }

    MOCK_METHOD(time_t, getNow, (), (override));
};