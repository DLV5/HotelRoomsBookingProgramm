#include <vector>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

struct reservation
{
    int id;
    string name;
    vector<int> bookedRoomNumbers;
};

const unsigned int minNumberOfRooms = 40;
const unsigned int maxNumberOfRooms = 300;

const unsigned int singleRoomPrice = 100;
const unsigned int doubleRoomPrice = 150;

const filesystem::path folderPath = "C:\\temp";
const filesystem::path filePath = "C:\\temp\\bookingList.txt";

const string namesForRandomBooking[] = { "Josh", "Mike", "Stuart", "Ben", "Lisa", "Bella"};

void tryToCreateFolder(filesystem::path folderpath)
{
    if (!std::filesystem::exists(folderpath))
        filesystem::create_directory(folderpath);
}

unsigned short int generateNumberOfRooms() {
    srand(time(NULL));
    return rand() % (maxNumberOfRooms - minNumberOfRooms) + minNumberOfRooms;
}

int generateRoom() {
    return rand() % 2;
}

void greetTheUser(unsigned short int currentNumberOfRooms) {
    cout << "Welcome to hotel booking programm!" << endl;
    cout << "Price of a single room is " << singleRoomPrice << "e per night" << endl;
    cout << "Price of a double room is " << doubleRoomPrice << "e per night" << endl;
    cout << "First half of a rooms in out hotels are single rooms, second half are double rooms" << endl;
    cout << "Currently we have " << currentNumberOfRooms << " rooms" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Enter 1 to book a room" << endl;
    cout << "Enter 2 to check your reservation" << endl;
    cout << "Enter 0 to exit " << endl;
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

int getReservationNumber()
{
    return rand() % 90000 + 10000;
}

void generateRandomBookedRooms(vector<int>& rooms,
    unsigned short int numberOfRooms, ofstream &bookingFile) {
    int isRoomBooked;
    string reservatorName;

    srand(time(NULL));

    for (int i = 0; i < numberOfRooms; i++)
    {
        isRoomBooked = generateRoom();

        if (isRoomBooked == 1)
        {
            int randomNamesArraySize = sizeof(namesForRandomBooking) / sizeof(namesForRandomBooking[0]);
            reservatorName = namesForRandomBooking[rand() % randomNamesArraySize];
            bookingFile << isRoomBooked << " " << getReservationNumber() << " - " << reservatorName << "\n";
        }
        else
        {
            bookingFile << isRoomBooked << "\n";
        }
        rooms.push_back(isRoomBooked);
    }
}

vector<reservation> readInputFile(ifstream& bookingFile, vector<int>& rooms)
{
    int counter = 0;
    string booking;
    bool isBookingNameUnique = true;

    vector<reservation> userBookings;

    while (!bookingFile.eof())
    {
        getline(bookingFile, booking);
        counter++;

        if (booking[0] == '1')
        {
            isBookingNameUnique = true;
            reservation userBooking;

            for (reservation &uBooking : userBookings)
            {
                //10 - length of string before name in a file, ex. "0 12345 - Anny Lo" -> "0 12345 - " this is 10 symbols length
                if ((booking.substr(10) == uBooking.name) && (stoi(booking.substr(2, 10)) == uBooking.id))
                {
                    isBookingNameUnique = false;
                    
                    uBooking.bookedRoomNumbers.push_back(counter);
                }
            }

            if (isBookingNameUnique)
            {
                userBooking.id = stoi(booking.substr(2, 10));
                userBooking.name = booking.substr(10);
                userBooking.bookedRoomNumbers.clear();
                userBooking.bookedRoomNumbers.push_back(counter);

                userBookings.push_back(userBooking);
            }
            
            rooms.push_back(1);
        }
        else
        {
            rooms.push_back(0);
        }
    }

    return userBookings;
}

bool isRoomAwailable(unsigned short int roomNumber,
    vector<int> room) {
    return room[roomNumber - 1] == 0;
}

int getInputAsInt(string& userInput) {
    unsigned short int userInputNumber = 0;

    for (char letter : userInput) {
        userInputNumber = userInputNumber * 10 + (letter - '0');
    }
    return userInputNumber;
}

bool checkIsInputNumber(string& userInput, short int numberOfRooms) {
    unsigned short int length = 0;
    
    for (char symbol : userInput) {
        if (!isdigit(symbol))
            return false;

        length++;
    }

    if (getInputAsInt(userInput) > numberOfRooms)
        return false;

    return true;
}

bool checkIsInputNumber(string& userInput) {
    unsigned short int length = 0;

    for (char symbol : userInput) {
        if (!isdigit(symbol))
            return false;

        length++;
    }

    return true;
}

string getUserInput(unsigned short int numberOfRooms) {
    string userInput;

    cin >> userInput;

    if (!checkIsInputNumber(userInput, numberOfRooms))
    {
        do {
            cout << "Your input is wrong, please write another number: ";
            cin >> userInput;
        } while (!checkIsInputNumber(userInput, numberOfRooms));
    }

    return userInput;

}

string getUserInput() {
    string userInput;

    cin >> userInput;

    if (!checkIsInputNumber(userInput))
    {
        do {
            cout << "Your input is wrong, please write another number: ";
            cin >> userInput;
        } while (!checkIsInputNumber(userInput));
    }

    return userInput;
}

string getEntireStringAsUserInput() {
    string input;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    getline(cin, input); 

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

void bookTheRoom(vector<int>& currentUserBookedRooms,
    unsigned short int currentNumberOfRooms, vector<int>& rooms,
    float currentDiscount, int& totalBill, int roomToBook) {

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

void finishReservation(vector<reservation>& reservations, vector<int> currentUserBookedRooms) {

    cout << "For finishing reservation please write your name: " << endl;

    string reservationName;
    int reservaitonNumber;
    reservation userReservation;

    reservaitonNumber = getReservationNumber();
    reservationName = getEntireStringAsUserInput();

    userReservation.id = reservaitonNumber;
    userReservation.name = reservationName;
    userReservation.bookedRoomNumbers = currentUserBookedRooms;

    reservations.push_back(userReservation);

    cout << "Thank you for your reservation, " << reservationName << endl;
    cout << "Your reservation number is: " << reservaitonNumber << endl;

    ifstream bookingFileInput(filePath);

    std::vector<std::string> lines;
    std::string line;
    while (getline(bookingFileInput, line))
    {
        lines.push_back(line);
    }
    bookingFileInput.close();

    ofstream outputFile(filePath);

    int counter = 1;
    for (const string& modifiedLine : lines)
    {
        bool wasLineChanged = false;
        for (int room : userReservation.bookedRoomNumbers)
        {
            if (room == counter)
            {
                wasLineChanged = true;
                outputFile << "1 " << userReservation.id << " - " << userReservation.name << "\n";
            }
        }

        if(!wasLineChanged)
            outputFile << modifiedLine << "\n";

        counter++;
    }
}

void processReservation(unsigned short int currentNumberOfRooms, 
    vector<reservation>& reservations, vector<int> rooms) {

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

void showReservation(reservation reservationToShow)
{

    cout << "Reservation was found! " << endl;
    cout << "Name: " << reservationToShow.name << endl;
    cout << "Booked room(s): ";
    for (int room : reservationToShow.bookedRoomNumbers)
    {
        cout << room << " ";
    }
    cout << endl;
    cout << endl;
}

void checkReservation(vector<reservation> reservations) {

    bool wasReservationFound;
    bool isSearchByNumberEnabled;
    bool isSearchByNameEnabled;

    cout << "Enter 1 if you want to search reservation by number" << endl;
    cout << "Enter 2 if you want to search by name (case sentesive)" << endl;
    cout << "Enter 0 to exit from this section" << endl;

    string userInput = getUserInput();

    while (true) {

        isSearchByNumberEnabled = false;
        isSearchByNameEnabled = false;
        wasReservationFound = false;

        switch (getInputAsInt(userInput))
        {
            case 1:
                isSearchByNumberEnabled = true;
                break;
            case 2:
                isSearchByNameEnabled = true;
                break;
            default:
                isSearchByNumberEnabled = true;
                break;
        }

        if (isSearchByNumberEnabled)
        {
            cout << "Please enter reservation number " << endl;
            cout << "Enter 0 for exit: " << endl;
            userInput = getUserInput();
        }

        if (isSearchByNameEnabled)
        {
            cout << "Please enter reservation name: " << endl;
            cout << "Enter 0 for exit: " << endl;
            userInput = getEntireStringAsUserInput();
        }

        for (reservation userReservation : reservations)
        {
            if (isSearchByNumberEnabled)
            {
                if (userReservation.id == getInputAsInt(userInput))
                {
                    showReservation(userReservation);

                    wasReservationFound = true;
                }
            }

            if (isSearchByNameEnabled)
            {
                if (userReservation.name == userInput)
                {
                    showReservation(userReservation);

                    wasReservationFound = true;
                }
            }
        }

        if (!wasReservationFound)
        {
            if (getInputAsInt(userInput) == 0)
            {
                break;
            }

            cout << "Can't find reservation number or name, please enter another one" << endl;
        }
    }

    cout << "Press 1 to book a room or 2 to check your reservation, press 0 to exit " << endl;
}

int main()
{
    unsigned short int currentNumberOfRooms;

    tryToCreateFolder(folderPath);

    ifstream bookingListFileInput(filePath);

    //0 - free 1 - booked
    vector<int> rooms;

    vector<reservation> reservations;

    string userInput;

    currentNumberOfRooms = generateNumberOfRooms();
    
    if (!bookingListFileInput.is_open())
    {
        ofstream bookingListFileOutput(filePath);

        generateRandomBookedRooms(rooms, currentNumberOfRooms, bookingListFileOutput);  

        bookingListFileOutput.close();

        bookingListFileInput.open(filePath);
    }

    reservations = readInputFile(bookingListFileInput, rooms);

    bookingListFileInput.close();

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
                cout << "Enter 1 to book a room" << endl;
                cout << "Enter 2 to check your reservation" << endl;
                cout << "Enter 0 to exit " << endl;
        }
    }
}