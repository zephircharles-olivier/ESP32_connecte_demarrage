/*
 * File:   display.cpp
 * Author: e2267146
 *
 * Created on September 19, 2023, 3:58 PM
 */
#include <Arduino.h>
#include <display.h>
#include <board_mapping.h>
#include <HardwareSerial.h>

HardwareSerial mySerial(2);  // Utilisation de l'UART1 (l'ESP32 dispose de plusieurs UARTs)


void initialize_screen(void){
 
    // Initialiser la connexion série vers l'écran LCD (9600 baud est courant pour les écrans UART)
    mySerial.begin(9600, SERIAL_8N2, GPIO_UART_RX, GPIO_UART_TX);  // RX : GPIO 16, TX : GPIO 17
    VideEcran();
    SetContrast(41);
    SetBacklight(1);    
    // Effacer l'écran LCD
    mySerial.write(0xFE);       // Indicateur de commande
    mySerial.write(0x01);       // Commande pour effacer l'écran
    //delay(10);                  // Délai pour permettre l'effacement
}

void afficher_message_accueil(void) {
    
    // Afficher le texte en français sur la première ligne
    
    // Positionner le curseur au début de la deuxième ligne
    // Afficher un texte additionnel sur la deuxième ligne
    VideEcran();
    CurseurPosition(0x01);
    mySerial.write("Test ESP32 LCD"); // Afficher le texte sur l'écran LCD
    CurseurPosition(0x14);     
    mySerial.write("Bonjour Jojo!"); // Afficher le texte sur l'écran LCD
    delay(400);
}

void Ecran_Allume(void) {
    mySerial.write(0xFE); //Command incoming!
    mySerial.write(0x41); //Allume l'ecran
}

void Ecran_Eteint(void) {
    mySerial.write(0xFE); //Command incoming!
    mySerial.write(0x42); //ecran s'eteint
}

void SetContrast(int contrast){
    mySerial.write(0xFE); //Command incoming!
    mySerial.write(0x52);
    mySerial.write(contrast); //Set contrast between 1 and 50
}

void SetBacklight(int brightness){
    mySerial.write(0xFE); //Command incoming!
    mySerial.write(0x53);
    mySerial.write(brightness); // Default: 8. 1 = Backlight OFF & 8 = Backlight ON (100%)  
}

void CurseurPosition(int position) {
    mySerial.write(0xFE); //Command incoming!
    mySerial.write(0x45); //Set cursor
    mySerial.write(position); //Quelle position?
}

void MoveCursor(int cursor) {
    int i;
    for (i = 0; i < cursor; i++) {
        mySerial.write(0XFE); //Command incoming!
        mySerial.write(0x4A); //Move cursor 1 space right
    }
}

void EffaceLigne1(void) {
    CurseurPosition(0x13); //ligne 3
    DeleteChar(); //1
    DeleteChar(); //2
    DeleteChar(); //3
    DeleteChar(); //4
    DeleteChar(); //5
    DeleteChar(); //6
    DeleteChar(); //7
    DeleteChar(); //8
    DeleteChar(); //9
    DeleteChar(); //10
    DeleteChar(); //1
    DeleteChar(); //2
    DeleteChar(); //3
    DeleteChar(); //4
    DeleteChar(); //5
    DeleteChar(); //6
    DeleteChar(); //7
    DeleteChar(); //8
    DeleteChar(); //9
    DeleteChar(); //10
}

void EffaceLigne2(void) {
    CurseurPosition(0x53); //ligne 3
    DeleteChar(); //1
    DeleteChar(); //2
    DeleteChar(); //3
    DeleteChar(); //4
    DeleteChar(); //5
    DeleteChar(); //6
    DeleteChar(); //7
    DeleteChar(); //8
    DeleteChar(); //9
    DeleteChar(); //10
    DeleteChar(); //1
    DeleteChar(); //2
    DeleteChar(); //3
    DeleteChar(); //4
    DeleteChar(); //5
    DeleteChar(); //6
    DeleteChar(); //7
    DeleteChar(); //8
    DeleteChar(); //9
    DeleteChar(); //10
}

void EffaceLigne3(void) {
    CurseurPosition(0x27); //ligne 3
    DeleteChar(); //1
    DeleteChar(); //2
    DeleteChar(); //3
    DeleteChar(); //4
    DeleteChar(); //5
    DeleteChar(); //6
    DeleteChar(); //7
    DeleteChar(); //8
    DeleteChar(); //9
    DeleteChar(); //10
    DeleteChar(); //1
    DeleteChar(); //2
    DeleteChar(); //3
    DeleteChar(); //4
    DeleteChar(); //5
    DeleteChar(); //6
    DeleteChar(); //7
    DeleteChar(); //8
    DeleteChar(); //9
    DeleteChar(); //10
}

void EffaceLigne4(void) {
    CurseurPosition(0x67); //ligne 3
    DeleteChar(); //1
    DeleteChar(); //2
    DeleteChar(); //3
    DeleteChar(); //4
    DeleteChar(); //5
    DeleteChar(); //6
    DeleteChar(); //7
    DeleteChar(); //8
    DeleteChar(); //9
    DeleteChar(); //10
    DeleteChar(); //1
    DeleteChar(); //2
    DeleteChar(); //3
    DeleteChar(); //4
    DeleteChar(); //5
    DeleteChar(); //6
    DeleteChar(); //7
    DeleteChar(); //8
    DeleteChar(); //9
    DeleteChar(); //10
}

void VideEcran(void) {
    mySerial.write(0xFE); //Command incoming!
    mySerial.write(0x51); //Clear screen

}

void EcrireCaractere(const char* caractere) {
    while (*caractere) {        // Loop through each character in the string
        mySerial.write(*caractere);  // Write the current character
        caractere++;             // Move to the next character
    }    
}

void MoveCaracter_Right() {
    mySerial.write(0XFE); //Command incoming!
    mySerial.write(0x4A); //Move cursor 1 space right
}

void DeleteChar() {
    mySerial.write(0xFE); //Command incoming!
    mySerial.write(0x4E); //Delete 1 character to the left
}

