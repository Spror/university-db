#!/usr/bin/env python3

import random
from faker import Faker

def generatePerson():
    fake = Faker()
    firstName = None
    pesel = None
    
    sex = randomSex()
    if sex == "male":
        #generate random first name
        firstName = fake.first_name_male()
        pesel = randomPesel(1)
    else:
        #generate random first name
        firstName = fake.first_name_female()
        pesel = randomPesel(0)
        
    #generate random last name
    lastName = fake.last_name()
    
    #generate random adress
    adress = fake.address()
    
    #generate random profession
    profession = randomProfession()
    
    
    
    if profession == "Employee":
        random_salry = random.uniform(2000.0, 12000.0)
        salary = f"{random_salry:.2f}"
        print(profession)
        print(firstName)
        print(lastName)
        print(sex)
        print(salary)
        print(profession)
        print(adress)
        
    else:
        random_index = random.randint(0, 999999)
        index = f"{random_index:06d}"
        print(profession)
        print(index)
        print(firstName)
        print(lastName)
        print(sex)
        print(pesel)
        print(adress)
        


def randomSex():
    sexes = ["male", "female"]
    return random.choice(sexes)

def randomProfession():
    professions = ["Student", "Employee"]
    return random.choice(professions)


def randomPesel(sex):
    # Generate the date part of PESEL (YYMMDD)
    year = random.randint(0, 99)
    month = random.randint(1, 12)
    day = random.randint(1, 28)  # 28 days for simplicity (real PESEL should account for varying days in a month)

    # Generate the personal part of PESEL (RRR)
    random_part = random.randint(0, 999)
    
    # Combine all parts to create PESEL
    pesel = f"{year:02d}{month:02d}{day:02d}{random_part:03d}{sex:01d}"
    
    # Calculate the control digit
    control_sum = (1 * int(pesel[0]) + 3 * int(pesel[1]) + 7 * int(pesel[2]) + 9 * int(pesel[3]) +
                   1 * int(pesel[4]) + 3 * int(pesel[5]) + 7 * int(pesel[6]) + 9 * int(pesel[7]) +
                   1 * int(pesel[8]) + 3 * int(pesel[9])) % 10
    control_digit = (10 - control_sum) % 10
    
    # Append the control digit to complete the PESEL
    pesel += str(control_digit)

    return pesel

if __name__ == "__main__":
    generatePerson()