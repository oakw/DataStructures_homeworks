// Martins_Prokuratovs_221RDB473
#include <iostream>
#include <string>
#include <map>

using namespace std;


enum months {
    Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec,
};


class Date {
    int day;
    months month;
    int year;

    Date(int day, months month, int year)
        : day(day), month(month), year(year) {};

        static bool is_leap_year(int year);

    public:
        static Date parse_date(string dateString);
        string strftime();
        
        /**
         * So many exception classes may seem like an overkill for a simple 'everyday code'
         * Used just to showcase the technical possibility
         */
        class InvalidDateStringError: public runtime_error {
            public:
                InvalidDateStringError(string message) throw() : runtime_error(message) {}
        };
        
        private:
            class InvalidFormatError : public InvalidDateStringError {
                public:
                    InvalidFormatError(string message): InvalidDateStringError(message) {}
            };

            class InvalidDayError : public InvalidDateStringError {
                public:
                    InvalidDayError(string message) throw() : InvalidDateStringError(message) {}
            };

            class InvalidMonthError: public InvalidDateStringError {
                public:
                    InvalidMonthError(string message) throw() : InvalidDateStringError(message) {}
            };

            class InvalidYearError: public InvalidDateStringError {
                public:
                    InvalidYearError(string message) throw() : InvalidDateStringError(message) {}
            };
};


map<months, string> monthNames = {
    {Dec, "December"},  {Jan, "January"},   {Feb, "February"},
    {Mar, "March"},     {Apr, "April"},     {May, "May"},
    {Jun, "June"},      {Jul, "July"},      {Aug, "August"},
    {Sep, "September"}, {Oct, "October"},   {Nov, "November"},
};


// Based on rules described https://lv.wikipedia.org/wiki/Garais_gads
bool Date::is_leap_year(int year) {
    if (year % 4000 == 0)
        return false;
    else if (year % 400 == 0)
        return true;
    else if (year % 100 == 0)
        return false;
    else if (year % 4 == 0)
        return true;
    else
        return false;
}


// Idea of static function implementation borrowed from https://www.learncpp.com/cpp-tutorial/static-member-functions/
Date Date::parse_date(string dateString) {
    if (dateString[2] != '-' || dateString[5] != '-')
        throw InvalidFormatError("Expected date in format DD-MM-YYYY");


    int day = stoi(dateString.substr(0, 2));
    // https://stackoverflow.com/a/11452972
    months month = static_cast<months>(stoi(dateString.substr(3, 5)) - 1);
    int year = stoi(dateString.substr(6, 10));
    
    if (year < 0)
        throw InvalidYearError("Only Anno Domini");

    if (month < 0 || month >= 12)
        throw InvalidMonthError("Month must be between 1 and 12");

    if (day <= 0)
        throw InvalidDayError("Day must be larger than 0");


    // Apr, June, Sept and Nov has max 30 days
    if (month == months::Apr || month == months::Jun || month == months::Sep || month == months::Nov) {
        if (day > 30)
            throw InvalidDayError("The specified month has at most 30 days");
        

    // February has max 29 days on leap year, 28 on others
    } else if (month == months::Feb) {
        if (! Date::is_leap_year(year) && day > 28)
            throw InvalidDayError("The specified month has at most 28 days");

        else if (day > 29)
            throw InvalidDayError("The specified month (in leap year) has at most 29 days");


    // In rest cases, max 31 days
    } else if (day > 31) {
        throw InvalidDayError("The specified month has at most 31 days");
    }

    return Date(day, month, year);
}


string Date::strftime() {
    string dateString = "";

    dateString += monthNames[this->month] + ", "; 

    dateString += to_string(this->day);
    if (this->day == 1 || this->day == 21 || this->day == 31)
        dateString += "st";
    else if (this->day == 2 || this->day == 22)
        dateString += "nd";
    else if (this->day == 3 || this->day == 23)
        dateString += "rd";
    else
        dateString += "th";

    dateString += ", " + to_string(this->year);
    
    return dateString;
}


int main() {
    char dateString[10];
    printf("Input your birth date: ");
    scanf("%s", dateString);

    try {
        Date date = Date::parse_date(dateString);
        printf("%s\n", date.strftime().c_str());

    } catch (Date::InvalidDateStringError ex) {
        printf("Error: %s\n", ex.what());
    }

    return 0;
}