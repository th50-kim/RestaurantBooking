#include "BookingScheduler.cpp"

class TestableBookingScheduler : public BookingScheduler {
public:
    TestableBookingScheduler() {}
    TestableBookingScheduler(int capacity, int wday) :BookingScheduler(capacity), wday(wday)
    {
    }

    time_t getNow(void) override {
        return (wday==0) ? setSunDayOfWeek(): setMonDayOfWeek();
    }

private:
    time_t setSunDayOfWeek(void) {
        tm tmTime = { 0, 0, 17, 19, 5 - 1, 2024 - 1900, 0, 0, -1 };
        tmTime.tm_wday = wday;
        return mktime(&tmTime);
    }

    time_t setMonDayOfWeek(void) {
        tm tmTime = { 0, 0, 17, 20, 5 - 1, 2024 - 1900, 0, 0, -1 };
        tmTime.tm_wday = wday;
        return mktime(&tmTime);
    }
    int wday = 0;
};