#include <vector>
#include <iostream>
#include <string>

void greetTheUser(unsigned short int singleRoomPrice, unsigned short int doubleRoomPrice,
    unsigned short int currentNumberOfRooms) {
    using namespace std;
    cout << "Welcome to hotel booking programm!" << endl;
    cout << "Price of a single room is " << singleRoomPrice << "e per night" << endl;
    cout << "Price of a double room is " << doubleRoomPrice << "e per night" << endl;
    cout << "Currently we have " << currentNumberOfRooms << " rooms" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Press 1 to book a room or 2 to check your reservation, press 0 to exit ";
}

unsigned short int generateNumberOfRooms(unsigned short int minNumberOfRooms,
    unsigned short int maxNumberOfRooms) {
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

}std::string getUserInput() {
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
            break;
    }
}

int getReservationNumber() {
    srand(time(NULL));
    return rand() % 90000 + 10000;
}

int main()
{
    using namespace std;

    const unsigned int minNumberOfRooms = 40;
    const unsigned int maxNumberOfRooms = 300;

    const unsigned int singleRoomPrice = 100;
    const unsigned int doubleRoomPrice = 150;

    unsigned short int currentNumberOfRooms;
    float currentDiscount;

    //0 - free 1 - booked
    unsigned short int rooms[maxNumberOfRooms];

    vector<int> reservationNumbers;
    vector<string> reservationNames;
    vector<vector<int>> bookedRooms;

    unsigned int totalBill = 0;

    string userInput;

    currentNumberOfRooms = generateNumberOfRooms(minNumberOfRooms, maxNumberOfRooms);
    currentDiscount = getDiscount();

    generateRandomBookedRooms(rooms, currentNumberOfRooms);

    greetTheUser(singleRoomPrice, doubleRoomPrice, currentNumberOfRooms);

    while (true) {

        userInput = getUserInput();

        //This part is responsible for booking rooms
        if (userInput == "1") {
            cout << "Write a number of a room you want to book: ";

            vector<int> currentUserBookedRooms;

            while (true) {

                userInput = getUserInput(currentNumberOfRooms);

                if (getInputAsInt(userInput) == 0) {
                    cout << "For finishing reservation please write your name: " << endl;

                    string input;
                    int reservaitonNumber;

                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    getline(cin, input);

                    reservaitonNumber = getReservationNumber();

                    reservationNames.push_back(input);
                    reservationNumbers.push_back(reservaitonNumber);

                    cout << "Thank you for your reservation, " << input << endl;
                    cout << "Your reservation number is: " << reservaitonNumber << endl;

                    bookedRooms.push_back(currentUserBookedRooms);
                    break;
                }

                if ((isRoomAwailable(getInputAsInt(userInput), rooms))) {
                    currentUserBookedRooms.push_back(getInputAsInt(userInput));
                    unsigned short int pricePerNight = getPricePerNight(currentNumberOfRooms, getInputAsInt(userInput));

                    cout << "Room is awailable!" << endl;
                    cout << "For how many nights you want to book it? " << endl;
                    userInput = getUserInput(currentNumberOfRooms);

                    rooms[getInputAsInt(userInput)] = 1;

                    totalBill += getInputAsInt(userInput) * pricePerNight;

                    cout << "Total amount of the bill is: " << totalBill << "e" << endl;
                    cout << "Total discount is: " << currentDiscount << "e" << endl;
                    cout << "Total price with a dicount: " << totalBill - totalBill * currentDiscount << "e" << endl;

                    cout << "Write 0 to finish reservation or number of another room, that you want to book ";
                }
                else {
                    cout << "Unfortunately room is unawailable, please choose another number " << endl;
                    cout << "Write another number of a room you want to book: ";
                }
            }

            cout << "Press 1 to book a room or 2 to check your reservation, press 0 to exit " << endl;
        }
        //This part is responsible for cheking reservations
        else if (userInput == "2") {
            cout << "Please enter your reservation number: ";

            while (true) {
                userInput = getUserInput();

                auto num = find(reservationNumbers.begin(), reservationNumbers.end(), getInputAsInt(userInput));
                int index = distance(reservationNumbers.begin(), num);

                if (num != reservationNumbers.end()) {
                    cout << "Reservation was found! " << endl;
                    cout << "Name: " << reservationNames[index] << endl;
                    cout << "Booked rooms: ";
                    for (int room : bookedRooms[index]) {
                        cout << room << " ";
                    }
                    cout << endl;
                }
                else {
                    cout << "Can't find reservation number, please enter another number " << endl;
                }
            }

            cout << "Press 1 to book a room or 2 to check your reservation, press 0 to exit " << endl;
        }
        else if (userInput == "0") {
            break;
        }
        else {
            cout << "Please enter 1, 2 or 0" << endl;
        }
    }
}