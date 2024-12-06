#include <vector>
#include <iostream>
#include <string>

struct reservation
{
    int id;
    std::string name;
    std::vector<int> bookedRoomNumbers;
};

const unsigned int minNumberOfRooms = 40;
const unsigned int maxNumberOfRooms = 300;

const unsigned int singleRoomPrice = 100;
const unsigned int doubleRoomPrice = 150;

void greetTheUser(unsigned short int currentNumberOfRooms) {
    using namespace std;
    cout << "Welcome to hotel booking programm!" << endl;
    cout << "Price of a single room is " << singleRoomPrice << "e per night" << endl;
    cout << "Price of a double room is " << doubleRoomPrice << "e per night" << endl;
    cout << "Currently we have " << currentNumberOfRooms << " rooms" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Press 1 to book a room or 2 to check your reservation, press 0 to exit " << endl;
}

unsigned short int generateNumberOfRooms() {
    srand(time(NULL));
    return rand() % (maxNumberOfRooms - minNumberOfRooms) + minNumberOfRooms;
}

unsigned short int getPricePerNight(unsigned short int currentNumberOfRooms,
    unsigned short int roomNumber) {
    if (roomNumber < currentNumberOfRooms / 2) {
        return 100;
    }
    else {
        return 150;
    }
}

int generateRoom() {
    return rand() % 2;
}

void generateRandomBookedRooms(std::vector<int>& rooms,
    unsigned short int numberOfRooms) {
    for (int i = 0; i < numberOfRooms; i++)
    {
        rooms.push_back(generateRoom());
    }
}

bool isRoomAwailable(unsigned short int roomNumber,
    std::vector<int> room) {
    return room[roomNumber] == 0;
}

int getInputAsInt(std::string& userInput) {
    unsigned short int userInputNumber = 0;

    for (char letter : userInput) {
        userInputNumber = userInputNumber * 10 + (letter - '0');
    }
    return userInputNumber;
}

bool checkIsInputNumber(std::string& userInput, short int numberOfRooms) {
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

bool checkIsInputNumber(std::string& userInput) {
    unsigned short int length = 0;

    for (char symbol : userInput) {
        if (!std::isdigit(symbol))
            return false;

        length++;
    }

    return true;
}

std::string getUserInput(unsigned short int numberOfRooms) {
    std::string userInput;

    std::cin >> userInput;

    if (!checkIsInputNumber(userInput, numberOfRooms))
    {
        do {
            std::cout << "Your input is wrong, please write another number: ";
            std::cin >> userInput;
        } while (!checkIsInputNumber(userInput, numberOfRooms));
    }

    return userInput;

}

std::string getUserInput() {
    std::string userInput;

    std::cin >> userInput;

    if (!checkIsInputNumber(userInput))
    {
        do {
            std::cout << "Your input is wrong, please write another number: ";
            std::cin >> userInput;
        } while (!checkIsInputNumber(userInput));
    }

    return userInput;
}

std::string getEntireStringAsUserInput(std::string input) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::getline(std::cin, input); 

    return input;
}

float getDiscount() {
    srand(time(NULL));
    unsigned short int randResult = rand() % 4;

    switch (randResult)
    {
        case 1:
            return 0;
        case 2:
            return 0.1;
        case 3:
            return 0.2;
        default:
            return 0;
            break;
    }
}

int getReservationNumber() {
    srand(time(NULL));
    return rand() % 90000 + 10000;
}

void bookTheRoom(std::vector<int>& currentUserBookedRooms,
    unsigned short int currentNumberOfRooms, std::vector<int>& rooms,
    float currentDiscount, int& totalBill, int roomToBook) {
    using namespace std;

    string userInput;
    int userInputAsNumber;

    cout << "Room is awailable!" << endl;
    cout << "For how many nights you want to book it? " << endl;
    userInput = getUserInput(currentNumberOfRooms);
    userInputAsNumber = getInputAsInt(userInput);

    currentUserBookedRooms.push_back(roomToBook);
    unsigned short int pricePerNight = getPricePerNight(currentNumberOfRooms, userInputAsNumber);

    rooms[userInputAsNumber] = 1;

    totalBill += userInputAsNumber * pricePerNight;

    cout << "Total amount of the bill is: " << totalBill << "e" << endl;
    cout << "Total discount is: " << currentDiscount << "e" << endl;
    cout << "Total price with a dicount: " << totalBill - totalBill * currentDiscount << "e" << endl;

    cout << "Write 0 to finish reservation or number of another room, that you want to book ";
}

void finishReservation(std::vector<reservation>& reservations, std::vector<int> currentUserBookedRooms) {
    using namespace std;

    cout << "For finishing reservation please write your name: " << endl;

    string reservationName;
    int reservaitonNumber;
    reservation userReservation;

    reservaitonNumber = getReservationNumber();
    reservationName = getEntireStringAsUserInput(reservationName);

    userReservation.id = reservaitonNumber;
    userReservation.name = reservationName;
    userReservation.bookedRoomNumbers = currentUserBookedRooms;

    reservations.push_back(userReservation);

    cout << "Thank you for your reservation, " << reservationName << endl;
    cout << "Your reservation number is: " << reservaitonNumber << endl;
}

void processReservation(unsigned short int currentNumberOfRooms, 
    std::vector<reservation>& reservations, std::vector<int> rooms) {
    using namespace std;

    string userInput;
    int totalBill = 0;
    float currentDiscount;

    vector<int> currentUserBookedRooms;

    currentDiscount = getDiscount();

    cout << "Write a number of a room you want to book: " << endl;

    while (true) {

        userInput = getUserInput(currentNumberOfRooms);
        int userInputAsNumber = getInputAsInt(userInput);

        if (userInputAsNumber == 0) {
            finishReservation(
                reservations, 
                currentUserBookedRooms 
            );
            break;
        }

        if ((isRoomAwailable(userInputAsNumber, rooms))) {
            bookTheRoom(
                currentUserBookedRooms,
                currentNumberOfRooms,
                rooms,
                currentDiscount,
                totalBill,
                userInputAsNumber
            );
        }
        else {
            cout << "Unfortunately room is unawailable, please choose another number " << endl;
            cout << "Write another number of a room you want to book: ";
        }
    }

    cout << "Press 1 to book a room or 2 to check your reservation, press 0 to exit " << endl;
}

void checkReservation(std::vector<reservation> reservations) {
    using namespace std;

    bool wasReservationRound = false;

    cout << "Please enter your reservation number: ";

    while (true) {
        string userInput = getUserInput();
        int userInputAsNumber = getInputAsInt(userInput);

        for (reservation userReservation : reservations)
        {
            if (userReservation.id = getInputAsInt(userInput))
            {
                cout << "Reservation was found! " << endl;
                cout << "Name: " << userReservation.name << endl;
                cout << "Booked room(s): ";
                for (int room : userReservation.bookedRoomNumbers)
                {
                    cout << room << " ";
                }
                cout << endl;

                wasReservationRound = true;
            }
        }

        if (!wasReservationRound)
        {
            cout << "Can't find reservation number, please enter another number " << endl;

            if (userInputAsNumber == 0)
            {
                break;
            }
        }
    }

    cout << "Press 1 to book a room or 2 to check your reservation, press 0 to exit " << endl;
}

int main()
{
    using namespace std;

    unsigned short int currentNumberOfRooms;

    //0 - free 1 - booked
    vector<int> rooms;

    vector<int> reservationNumbers;
    vector<string> reservationNames;
    vector<vector<int>> bookedRooms;

    vector<reservation> reservations;

    string userInput;

    currentNumberOfRooms = generateNumberOfRooms();

    generateRandomBookedRooms(rooms, currentNumberOfRooms);

    greetTheUser(currentNumberOfRooms);

    while (true) {

        userInput = getUserInput();

        //Exit from programm
        if (userInput == "0")
            break;

        switch (getInputAsInt(userInput)) {
            
            //This part is responsible for booking rooms
            case 1:
                processReservation(
                    currentNumberOfRooms,
                    reservations,
                    rooms);
                break;

            //This part is responsible for cheking reservations
            case 2:
                checkReservation(
                    reservations
                );
                break;

            //Tell all awailable inputs to user
            default:
                cout << "Please enter 1, 2 or 0" << endl;
        }
    }
}