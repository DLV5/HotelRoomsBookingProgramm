# HotelRoomsBookingProgramm

This is a console app designed for booking rooms in a hotel

## Features of a project

1. You can book any room in a virtual Hotel
2. You can specify amount of nights you're staying
3. Program automatically applies random discount from 0 to 20 percent
4. You can search specific booking by booking number
5. You can search all bookings with the same name
6. Programm keeps track of all booking through a .txt file, that is placed in c:\temp\bookingList.txt
7. If you running program for the first time it'll generate folder temp and file bookingList.txt as well as
   it'll fill the file with random reservations. Around 50% of the rooms will be reserved

## How to run

1.Download repository
2.Unpack it
3.Open Visual Studio solution and click "run"

## Code

I wasn't using lots of comments in this project, because in my opinion method names are telling more than enough
for the person who, would read it. I tried to make code as readable as I can, give a feedback how if you think I can improve readability even further

## Personal thoughts
This is my first c++ project with a relatively big size (around 550 lines). Main point of the project
was to practice programming using c++, because even with my past experience in programming using c# 
some stuff work different in c++, for example I wasn't aware that vector type variables always copy when
you are writing something like this 


```
vector a = {1, 2};
vector b = a;

a.push_back(3);
cout << b[2];
```

following code would bring an error, because b vector actually don't have a third variable inside, but it
would work in c# language. 

But in a conclusion I want to say that it was still a lot's of fun. Next time I will explore more of a headers
and classes in c++, because it gets messy when so much different stuff is happening in one single file

This project is written as a course task for my c++ course in Univesity of applied science
