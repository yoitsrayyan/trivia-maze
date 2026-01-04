#include <iostream>
#include <string>
#include <cctype>
using namespace std;



void showMenu();
bool playRoom(string RoomQuestions[], char correctAnswers[], int &PlayerSouls, int &PlayerMark, char AnswersWhiteList[]);
void quizroTalk(int messageID);
void loadRoomData(int RoomNum, string RoomQuestions[], char correctAnswers[]);
void showCredit();



int main() {
    int PlayerOrder = 0, PlayerResponse = 0, PlayerSouls = 3, PlayerMark = 0, MaxMark = 20, PlayAgainOption = 0;
    string PlayerName;
    char AnswersWhiteList[8] = {'A', 'B', 'C', 'D', 'a', 'b', 'c', 'd'}; //the only answers the user can say during the game
    bool IsMenuOn = true, PlayerNamecheck = false, MasterGameLoop, LeaveCheck = false; //To keep the menu on before the user stars the game, also to check if the user entered his right name and the main loop
    
    string RoomQuestions[5];
    char correctAnswers[5];

    while (IsMenuOn == true) { //for the main menu
    PlayerOrder = 0;
    showMenu();
    cout << " >> ";
    cin >> PlayerOrder;

    if (cin.fail()) { //We use this code to make sure the game doesn't enter a loop Error
        cin.clear();
        cin.ignore(1000, '\n');
        cout << " Please enter a number not a character\n";
        } else {
            switch (PlayerOrder) {
                case(1): IsMenuOn = false; MasterGameLoop = true; break; //Starts the game
                case(2): showCredit(); cout << "PRESS ENTER TO RETURN TO THE MAIN MENU >>"; cin.ignore(); cin.get(); break; //this one shows the credit menu, Using cin.ignore and cin.get to make the menu stays till the user press enter!
                case(3): return 0; //leaves the game
                default: cout << "                                                        WRONG INPUT!                                                                 " << endl;
            }
        }

    }

    //ask the player of his name and make sure it's right
    do {
    quizroTalk(1);
    cin >> PlayerName;

    quizroTalk(2);
    cout << PlayerName << " (1-yes / 2-No) >>";
    cin >> PlayerResponse;

    if (cin.fail()) {  //the same as up, So the game doesn't enter that bad loop

        cin.clear();
        cin.ignore(1000, '\n');
        cout << " Please enter a number not a character\n";
        PlayerNamecheck = true;

        } else {

            switch (PlayerResponse) {
                case(1): cout << "[Quizro]: Okay, welcome " << PlayerName; quizroTalk(3);
                PlayerNamecheck = false; break;
                case(2): PlayerNamecheck = true; break;
                default:  cout << "                                                        WRONG INPUT!                                                                 " << endl; PlayerNamecheck = true; break;
            }
        }

    } while (PlayerNamecheck == true);

    cin.ignore();
    cin.get();

    do {
        PlayerSouls = 3;
        PlayerMark = 0;

        for (int room = 1; room <= 4; room++) {
            loadRoomData(room, RoomQuestions, correctAnswers);

            if (!playRoom(RoomQuestions, correctAnswers, PlayerSouls, PlayerMark, AnswersWhiteList)) {
                 break;
            }


            if (PlayerSouls > 0 && room < 4) {
                cout << "\nMoving to the next room " << PlayerName << "... Prepare yourself!" << endl;
            }
            
        }

        if (PlayerSouls > 0 && PlayerMark > 10) { //end game, win with mark bigger than 10 

         cout << "\nCONGRATULATIONS! " << PlayerName << " You conquered the maze and got my prize! Final Score: " << PlayerMark << "/20" << endl;

         } else if (PlayerSouls > 0 && PlayerMark <= 10) { //end game, win with a mark lower than 10

         cout << "\nCONGRATULATIONS! " << PlayerName << " You conquered the maze!...But your mark sucks so there is no prize for you. Final Score: " << PlayerMark << "/20" << endl;
             
         } else {
            cout << "\nGAME OVER! The maze claimed your soul. Score: " << PlayerMark << "/20" << endl;
         }
       
        do {
        quizroTalk(8);
        PlayAgainOption = 0;
        cin >> PlayAgainOption;

        if (cin.fail()) {  //the same as the other two, So the game doesn't enter that bad loop

        cin.clear();
        cin.ignore(1000, '\n');
        cout << " Please enter a number not a character\n";
        LeaveCheck = true;

     } else {

         switch (PlayAgainOption) {
                case(1): MasterGameLoop = true; LeaveCheck = false;  break;
                case(2): MasterGameLoop = false; LeaveCheck = false; showCredit();
                cout << "\nThanks for playing Trivia Maze " << PlayerName << "! See you next time. (ᵔᵕᵔ)" << endl; break;
                default: LeaveCheck = true; cout << "                                                        WRONG INPUT!                                                                 " << endl; break;
            } 

        }

     }while (LeaveCheck == true);

    } while (MasterGameLoop == true);

    return 0;
}


//The main menu:
void showMenu() {
    cout << "===========================================================================================================\n" << endl;
    cout << "    mmmmmmmm               ##                  ##               mmm  mmm                               " << endl;
    cout << "    \"\"\"##\"\"\"               \"\"                  \"\"               ###  ###                               " << endl;
    cout << "       ##      ##m####   ####     ##m  m##   ####      m#####m  ########   m#####m  ########   m####m  " << endl;
    cout << "       ##      ##\"         ##      ##  ##      ##      \" mmm##  ## ## ##   \" mmm##      m#\"   ##mmmm## " << endl;
    cout << "       ##      ##          ##      \"#mm#\"      ##     m##\"\"\"##  ## \"\" ##  m##\"\"\"##    m#\"     ##\"\"\"\"\"\" " << endl;
    cout << "       ##      ##       mmm##mmm    ####    mmm##mmm  ##mmm###  ##    ##  ##mmm###  m##mmmmm  \"##mmmm# " << endl;
    cout << "       \"\"      \"\"       \"\"\"\"\"\"\"\"     \"\"     \"\"\"\"\"\"\"\"   \"\"\"\" \"\"  \"\"    \"\"   \"\"\"\" \"\"  \"\"\"\"\"\"\"\"    \"\"\"\"\"  " << endl;
    cout << "\n===========================================================================================================" << endl;
    cout << "                                     ###############################                                                       " << endl;
    cout << "                                     #   welcome to trivia maze!   #                                                       " << endl;
    cout << "                                     # Type '1' to start the game! #                                                       " << endl;
    cout << "                                     #   Type '2' to show credit   #                                                       " << endl;
    cout << "                                     #  Type '3' to Exit the game  #                                                       " << endl;
    cout << "                                     ###############################                                                       " << endl;
}


//The rooms system
bool playRoom(string RoomQuestions[], char correctAnswers[], int &PlayerSouls, int &PlayerMark, char AnswersWhiteList[]) {
    int AnswersCorrectInRoom = 0;

    for (int i = 0; i<5; i++) {
        char PlayerAnswer;
        bool IsValidAnswer = false; //To check if the input is on the white list

        cout << "\n----------------------------------------" << endl;
        cout << RoomQuestions[i] << endl;

        do { 
            cout << "ENTER YOUR ANSWER >> ";
            cin >> PlayerAnswer;
            
            for (int j = 0; j < 8; j++) { //The answer system that make sure the user Entered a valid one (A a B b C c D d)
                if (PlayerAnswer == AnswersWhiteList[j]) {
                    IsValidAnswer = true;
                    break;
                }
                
            }
                if (IsValidAnswer == false) {
                    quizroTalk(4);
                    IsValidAnswer = false;
                }
                
        } while (!IsValidAnswer);

        PlayerAnswer = toupper(PlayerAnswer); //We use this to turn smalls to Caps (Forgive the player XD)

        if (PlayerAnswer == correctAnswers[i]) {
            quizroTalk(5); //Right one
            PlayerMark++;
            AnswersCorrectInRoom++;
        } else {
            quizroTalk(6); //Wrong one
            PlayerSouls--;
            cout << "Remaining Souls: " << PlayerSouls << endl;
        }
        if (PlayerSouls <= 0) return false;
    }

    if (AnswersCorrectInRoom == 5) {
        quizroTalk(7);
        PlayerSouls++;
        cout << "Current Souls: " << PlayerSouls << endl;
    }
    return true;
}


//Quizro lines:
void quizroTalk(int messageID) {
    //For Quizro lines we made a switch case code to bring the right line at the right moment, Smart isn't it B-)?
    switch(messageID) {
        case(1): cout << "[Quizro]: Greetings, traveler! I am Quizro, the guardian of this maze. Before we begin, what is your name? "; break;
        case(2): cout << "[Quizro]: Is this the right name, "; break;
        case(3): cout << " To escape this maze and get my prize, you must pass through 4 rooms. Answer wisely, for your souls are limited! \n Press Enter when you're ready!" << endl; break;
        case (4): cout << "\n[Quizro]: WRONG INPUT! Please stick to A, B, C, or D!\n"; break;
        case (5): cout << "\n[Quizro]: Spot on! Your wisdom is impressive!"; break;
        case (6): cout << "\n[Quizro]: Alas! That is incorrect. You have lost a soul... Be careful!"; break;
        case (7): cout << "\n[Quizro]: Incredible! A perfect run in this room! As a reward, Quizro grants you an extra soul."; break;
        case (8): cout << "\n[Quizro]: Great effort! Want to try the maze again or are you too scared? \n(1- Yes / 2- No) >> "; break;
    }
}


//Questions and Answers Place:
void loadRoomData(int RoomNum, string RoomQuestions[], char correctAnswers[]) {
    //The rooms data (questions and answers) in order using switch and arrays (We used arrays for better tidiness)
    switch (RoomNum) {
        case(1): //room no.1
                RoomQuestions[0] = "1. When did Jordan gain independence?\nA) 1921 B) 1946 C) 1952 D) 1967";
                correctAnswers[0] = 'B';

                RoomQuestions[1] = "2. Which King is known as the \"Builder of Modern Jordan\"?\nA) King Abdullah I B) King Talal bin Abdullah C) King Abdullah II D) King Hussein bin Talal";
                correctAnswers[1] = 'D';
                
                RoomQuestions[2] = "3. In which year was the Arab Legion \"Arabized\" and Glubb Pasha dismissed?\nA) 1953 B) 1956 C) 1967 D) 1948";
                correctAnswers[2] = 'B';
                
                RoomQuestions[3] = "4. What was the ancient name given to \"Amman\" by the Greeks and Romans?\nA) Gerasa B) Gadara C) Philadelphia D) Petra";
                correctAnswers[3] = 'C';
                
                RoomQuestions[4] = "5. What is the name of the 1924 battle where Jordanians repelled an attack near Amman?\nA) Battle of Karameh B) Battle of Umm al-Amad C) Battle of Dhiban D) Battle of Maysalun";
                correctAnswers[4] = 'B';
                break;
        

        case(2): //room no.2
                RoomQuestions[0] = "1. What is the largest mammal on Earth (living in the oceans)?\nA) Great White Shark B) Blue Whale C)Sperm Whale  D) Orca (Killer Whale)";
                correctAnswers[0] = 'B';

                RoomQuestions[1] = "2. Which of these birds is famous for being flightless but a skilled swimmer?\nA) Penguin B) Ostrich C) Falcon D) Kiwi";
                correctAnswers[1] = 'A';
                
                RoomQuestions[2] = "3. Which animal has 3 hearts and blue blood?\nA) Octopus B) Jellyfish C) Seahorse D) Starfish";
                correctAnswers[2] = 'A';

                RoomQuestions[3] = "4. How many legs does a spider have\nA) 6 legs B) 8 legs C) 10 legs D) 12 legs";
                correctAnswers[3] = 'B';

                RoomQuestions[4] = "5. Which of the following senses is the strongest in dogs compared to humans?\nA) Sight B) Taste C) Smell D) Hearing";
                correctAnswers[4] = 'C';
                break;


        case(3): //room no.3
                RoomQuestions[0] = "1. How many players from each team are on the field in a football (soccer) match?\nA) 10 players B) 11 players C) 9 players D) 12 players";
                correctAnswers[0] = 'B';

                RoomQuestions[1] = "2. What is the official duration of a standard football match?\nA) 60 minutes B) 120 minutes C) 90 minutes D) 45 minutes";
                correctAnswers[1] = 'C';
                
                RoomQuestions[2] = "3. In which sport is a \"shuttlecock\" (feather) used?\nA) Handball B) Volleyball C) Golf D) Badminton";
                correctAnswers[2] = 'D';

                RoomQuestions[3] = "4. How many players from each team are on the court in a basketball game?\nA) 7 players B) 11 players C) 5 players D) 6 players";
                correctAnswers[3] = 'C';

                RoomQuestions[4] = "5. Where were the Ancient Olympic Games held?\nA) Greece B) Rome C) Egypt D) China";
                correctAnswers[4] = 'A';
                break;


        case(4): //room no.4
                RoomQuestions[0] = "1. Which vitamin do we primarily get from sun exposure?\nA) Vitamin D B) Vitamin A C) Vitamin C D) Vitamin B12";
                correctAnswers[0] = 'A';

                RoomQuestions[1] = "2. Which organ in the body is responsible for filtering blood from toxins?\nA) Kidneys B) Liver C) Heart D) Lungs";
                correctAnswers[1] = 'A';
                
                RoomQuestions[2] = "3. What is the normal human body temperature?\nA) 37°C B) 42°C C) 50°C D) 35°C";
                correctAnswers[2] = 'A';

                RoomQuestions[3] = "4. What is the largest organ in the human body?\nA) Liver B) Skin C) Lungs D) Intestines";
                correctAnswers[3] = 'B';

                RoomQuestions[4] = "5. How many bones does an adult human have?\nA) 500 bones B) 206 bones C) 300 bones D) 100 bones";
                correctAnswers[4] = 'B';
                break;

        
    }
    
}


//The credit menu:
void showCredit() {
    cout << "***************************************************************************" << endl;
    cout << "         _______   _       _       __  __               " << endl;
    cout << "        |__   __| (_)     (_)     |  \\/  |              " << endl;
    cout << "           | |_ __ ___   ___  __ _| \\  / | __ _ _______ " << endl;
    cout << "           | | '__| \\ \\ / / |/ _` | |\\/| |/ _` |_  / _ \\" << endl;
    cout << "           | | |  | |\\ V /| | (_| | |  | | (_| |/ /  __/" << endl;
    cout << "           |_|_|  |_| \\_/ |_|\\__,_|_|  |_|\\__,_/___\\___|" << endl;
    cout << "\n       Made by:\n                Rayyan Mohammad Farouq Saleh         (202510096)                          " << endl;
    cout << "                Mohammad Mahmoud Yaseen Shhabat      (202510239)                          " << endl;
    cout << "                Hisham Mahmoud Muhammad Al-Nassour   (202510419)                          " << endl;
    cout << "                Mohammad Tariq Mohammed Abu-Naim     (202510201)                          " << endl;
    cout << "\n**************************************************************************" << endl;
}

/* made by :

  Rayyan Mohammad Farouq Saleh         (202510096)
  Mohammad Mahmoud Yaseen Shhabat      (202510239)            
  Hisham Mahmoud Muhammad Al-Nassour   (202510419)    
  Mohammad Tariq Mohammed Abu-Naim     (202510201)    

*/