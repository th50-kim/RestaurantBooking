#include "BookingScheduler.cpp"

class TestableBookingScheduler : public BookingScheduler {
public:
    TestableBookingScheduler() {}
    TestableBookingScheduler(int capacity) :BookingScheduler(capacity)
    {
    }

    virtual time_t getNow(void) override {
        return setSunDayOfWeek();
    }

private:
    time_t setSunDayOfWeek(void) {
        tm tmTime;
        tmTime.tm_wday = 0;
        return mktime(&tmTime);
    }
};