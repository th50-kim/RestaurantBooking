#include "../Restaurant/BookingScheduler.cpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "TestableSmsSender.cpp"
#include "TestableMailSender.cpp"
#include "TestableBookingScheduler.cpp"

class BookingItem : public testing::Test {
protected:
	void SetUp() override {
		NOT_ON_THE_HOUR = getTime(2021, 3, 26, 9, 5);
		ON_THE_HOUR= getTime(2021, 3, 26, 9, 0);

		bookingSchedule.setSmsSender(&sms);
		bookingSchedule.setMailSender(&mail);
	}

public:
	tm getTime(int year, int mon, int day, int hour, int minute) {
		tm result = { 0, minute, hour, day, mon - 1, year - 1900, 0, 0, -1 };
		mktime(&result);
		return result;
	}

	tm plusHour(tm base, int hour) {
		base.tm_hour += hour;
		mktime(&base);
		return base;
	}

	tm NOT_ON_THE_HOUR;
	tm ON_THE_HOUR;

	Customer CUSTOMER{ "Fake name", "010-1234-5678" };
	Customer CUSTOMER_WITH_MAIL{ "Fake name", "010-1234-5678", "aaa@bbb.com" };
	const int UNDER_CAPACITY = 1;
	const int CAPACITY_PER_HOUR = 3;

	BookingScheduler bookingSchedule{ CAPACITY_PER_HOUR };

	TestableSmsSender sms;
	TestableMailSender mail;

};
TEST_F(BookingItem, ������_���ÿ���_�����ϴ�_���ð�_�ƴѰ��_����Ұ�) {
	Schedule* schedule = new Schedule{ NOT_ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER };

	EXPECT_THROW({
		bookingSchedule.addSchedule(schedule);
		}, std::runtime_error);
}

TEST_F(BookingItem, ������_���ÿ���_�����ϴ�_������_���_���డ��) {
	Schedule* schedule = new Schedule{ ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER };
	bookingSchedule.addSchedule(schedule);

	EXPECT_EQ(true, bookingSchedule.hasSchedule(schedule));
}

TEST_F(BookingItem, �ð��뺰_�ο�������_�ִ�_����_�ð��뿡_Capacity_�ʰ���_���_���ܹ߻�) {
	Schedule* schedule = new Schedule{ ON_THE_HOUR, CAPACITY_PER_HOUR, CUSTOMER };
	bookingSchedule.addSchedule(schedule);

	try {
		Schedule* schedule = new Schedule{ ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER };
		bookingSchedule.addSchedule(schedule);
		FAIL();
	}
	catch (std::runtime_error e) {
		EXPECT_EQ(string{e.what()}, string{"Number of people is over restaurant capacity per hour"});
	}
}

TEST_F(BookingItem, �ð��뺰_�ο�������_�ִ�_����_�ð��밡_�ٸ���_Capacity_���־_������_�߰�_����) {
	Schedule* schedule = new Schedule{ ON_THE_HOUR, CAPACITY_PER_HOUR, CUSTOMER };
	bookingSchedule.addSchedule(schedule);


	tm differentHour = plusHour(ON_THE_HOUR, 1);
	Schedule* newSchedule = new Schedule{ differentHour, UNDER_CAPACITY, CUSTOMER };
	bookingSchedule.addSchedule(newSchedule);

	EXPECT_EQ(true, bookingSchedule.hasSchedule(schedule));
	EXPECT_EQ(true, bookingSchedule.hasSchedule(newSchedule));


}

TEST_F(BookingItem, ����Ϸ��_SMS��_������_�߼�) {
	Schedule* schedule = new Schedule{ ON_THE_HOUR, CAPACITY_PER_HOUR, CUSTOMER };
	bookingSchedule.addSchedule(schedule);

	EXPECT_EQ(true, sms.isSendMethodIsCall());

}

TEST_F(BookingItem, �̸�����_����_��쿡��_�̸���_�̹߼�) {
	Schedule* schedule = new Schedule{ ON_THE_HOUR, CAPACITY_PER_HOUR, CUSTOMER };
	bookingSchedule.addSchedule(schedule);

	EXPECT_EQ(0, mail.getSendMethodIsCall());

}

TEST_F(BookingItem, �̸�����_�ִ�_��쿡��_�̸���_�߼�) {
	Schedule* schedule = new Schedule{ ON_THE_HOUR, CAPACITY_PER_HOUR, CUSTOMER_WITH_MAIL };
	bookingSchedule.addSchedule(schedule);

	EXPECT_EQ(1, mail.getSendMethodIsCall());
}

TEST_F(BookingItem, ���糯¥��_�Ͽ�����_���_����Ұ�_����ó��) {

	TestableBookingScheduler testableBookingSchedule{ CAPACITY_PER_HOUR, 0 };

	try {
		Schedule* schedule = new Schedule{ ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER };
		testableBookingSchedule.addSchedule(schedule);
		FAIL();
	}
	catch (std::runtime_error e) {
		EXPECT_EQ(string{ e.what() }, string{ "Booking system is not available on sunday" });
	}

}

TEST_F(BookingItem, ���糯¥��_�Ͽ�����_�ƴѰ��_���డ��) {
	TestableBookingScheduler testableBookingSchedule{ CAPACITY_PER_HOUR, 1 };

	try {
		Schedule* schedule = new Schedule{ ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER };
		testableBookingSchedule.addSchedule(schedule);
	}
	catch (std::runtime_error e) {
		FAIL();
	}
}