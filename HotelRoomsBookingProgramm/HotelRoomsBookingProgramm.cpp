
#include <iostream>
#include <string>

int generateRoom() {
    return rand() % 2;
}

void generateRandomBookedRooms(unsigned short int rooms[],
    unsigned short int numberOfRooms) {
    for (int i = 0; i < numberOfRooms; i++)
    {
        rooms[i] = generateRoom();
    }
}

bool isRoomAwailable(unsigned short int roomNumber,
    unsigned short int room[]) {
    return room[roomNumber] == 0;
}

int getInputAsInt(std::string& userInput) {
    unsigned short int userInputNumber = 0;

    for (char letter : userInput) {
        userInputNumber = userInputNumber * 10 + (letter - '0');
    }
    return userInputNumber;
}

bool checkIsInputValid(std::string& userInput, short int numberOfRooms) {
    unsigned short int length = 0;
    
    for (char symbol : userInput) {
        if (!std::isdigit(symbol))
            return false;

        length++;
    }

    if (getInputAsInt(userInput) > numberOfRooms)
        return false;

    return true;
}

std::string getUserInput(unsigned short int numberOfRooms) {
    std::string userInput;

    std::cin >> userInput;

    if (!checkIsInputValid(userInput, numberOfRooms))
    {
        do {
            std::cout << "Your input is wrong, please write another number: ";
            std::cin >> userInput;
        } while (!checkIsInputValid(userInput, numberOfRooms));
    }

    return userInput;
}


int main()
{
    using namespace std;

    const unsigned int numberOfRooms = 10;

    //0 - free 1 - booked
    unsigned short int rooms[numberOfRooms];

    unsigned int totalBill = 0;

    string userInput;

    generateRandomBookedRooms(rooms, numberOfRooms);

    cout << "Welcome to hotel booking programm!" << endl;
    cout << "Price of a room is 100e per night" << endl;
    cout << "Currently we have " << numberOfRooms << " rooms" << endl;

    cout << "Write a number of a room you want to book: ";

    while (true) {

        userInput = getUserInput(numberOfRooms);

        if (getInputAsInt(userInput) == 0)
            break;

        if((isRoomAwailable(getInputAsInt(userInput), rooms))) {
            cout << "Room is awailable!" << endl;
            cout << "For how many nights you want to book it? " << endl;
            userInput = getUserInput(numberOfRooms);

            rooms[getInputAsInt(userInput)] = 1;

            totalBill += getInputAsInt(userInput) * 100;

            cout << "Total amount of the bill is: " << totalBill << "e" << endl;

            cout << "Write 0 to exit or number of another room, that you want to book ";
        }
        else {
            cout << "Unfortunately room is unawailable, please choose another number " << endl;
            cout << "Write another number of a room you want to book: ";
        }
    }
}

