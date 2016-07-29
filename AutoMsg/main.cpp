#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>

using namespace std;


void type(char x){
    INPUT ip;
    int sizeX = 42;
    char chars[sizeX] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                         'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                         'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
                         'r', 's', 't', 'u', 'v', 'w', 'x',
                         'y', 'z', ' ', '/', '.', ':', '[', ']'};
    int keys[sizeX] = {0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,
                       0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
                       0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51,
                       0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
                       0x59, 0x5A, 0x20, 0x6F, 0xBE, 0xBA, 0xDB, 0xDD};
    int herecode;
    for(int i=0; i<= sizeX; i++){
        if(chars[i] == x){
            herecode = keys[i];
        }
    }
    if(herecode == 0xBA){
        ip.type = INPUT_KEYBOARD;
        ip.ki.wScan = 0;
        ip.ki.time = 0;
        ip.ki.dwExtraInfo = 0;

        ip.ki.wVk = VK_SHIFT;
        ip.ki.dwFlags = 0; // 0 for key press
        SendInput(1, &ip, sizeof(INPUT));

        ip.ki.wVk = herecode;
        ip.ki.dwFlags = 0; // 0 for key press
        SendInput(1, &ip, sizeof(INPUT));

        ip.ki.wVk = herecode;
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));

        ip.ki.wVk = VK_SHIFT;
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));
    }
    else{
        ip.type = INPUT_KEYBOARD;
        ip.ki.wScan = 0;
        ip.ki.time = 0;
        ip.ki.dwExtraInfo = 0;

        ip.ki.wVk = herecode;
        ip.ki.dwFlags = 0;
        SendInput(1, &ip, sizeof(INPUT));
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));
    }
}

std::string getCode(int linenumber){
    fstream file;
    file.open( "dictionary/dictionary.txt", ios::in);
    std::string out;
    for(int i=0; i<=linenumber; i++){
        getline (file,out);
    }
    return out;
}

void write(std::string msgtowrite){
    for(int i=0; i<=msgtowrite.size(); i++){
        Sleep(50);
        type(msgtowrite[i]);
    }
}
void pressReturn(){
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    ip.ki.wVk = 0x0D;
    ip.ki.dwFlags = 0;
    SendInput(1, &ip, sizeof(INPUT));
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
}

int main(){
    cout << "Enter Delay here in mins\nExample: 5 - message every 5 mins"<<endl;
    cout << "Delay: ";
    int x;
    cin >> x;
    system("cls");
    cout << "Switch to console, you have 5 secs";
    Sleep(5000);
    system("cls");
    cout << "Spamming every "<<x<<" mins"<<endl;
    bool y = true;
    while(y==true){
        if(GetAsyncKeyState(VK_F2)){
            y=false;
            cout << "done";
            return 1;
        }  else {
            int index=0;
            while(index<=10000){
                if(getCode(index) == "end" ){
                    index=0;
                } else {
                    Sleep(1000);
                    Sleep(x*1000*60-1000);
                    write(getCode(index));
                    pressReturn();
                    index++;
                }
            }
        }
    }
    return 0;
}

