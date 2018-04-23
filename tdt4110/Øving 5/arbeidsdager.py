weekday_list = ["mon","tue","wed","thu","fri","sat","sun"]

def is_leap_year(year):
    if year % 400 == 0:
        return True
    elif year % 100 == 0:
        return False
    elif year % 4 == 0:
        return True
    return False

def is_workday(weekday):
    if weekday%7 < 5:
        return True
    else:
        return False

def weekday_newyear(year):
    weekday = -1               #akkumuleringsvariabel
    for y in range(1900, year+1):
        if is_leap_year(y-1):
            weekday += 2
        else:
            weekday += 1
        print(y, ":", weekday_list[weekday%7])
    return weekday_list[weekday%7]

def workdays_in_year(year):
    weekday = 0
    for y in range(1900, year+1):
        workdays = 0  #akkumuleringsvariabel
        if is_leap_year(y):
            for d in range(366):
                if is_workday(weekday):
                    workdays += 1
                weekday += 1
        else:
            for d in range(365):
                if is_workday(weekday):
                    workdays += 1
                weekday += 1

        print(y, "har", workdays, "arbeidsdager")

#workdays_in_year(1919)
weekday_newyear(1919)
'''
for x in range(1900,1920):
    print(x, "begynner paa en", weekday_newyear(x), "og har", )
'''