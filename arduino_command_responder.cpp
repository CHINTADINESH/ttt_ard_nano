/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

// Macros are not working for me. 
int test = 1;


#if defined(ARDUINO) && !defined(ARDUINO_ARDUINO_NANO33BLE)
#define ARDUINO_EXCLUDE_CODE
#endif  // defined(ARDUINO) && !defined(ARDUINO_ARDUINO_NANO33BLE)

#ifndef ARDUINO_EXCLUDE_CODE

#include "command_responder.h"

#include "Arduino.h"

//extern char* square;
enum game_state{PLAYER1, PLAYER2, GAMEOVER};

extern char square[10];
extern char input_buf[10];
extern int input_ind;
extern int player_state;



int mark_board(int choice){
    char mark;

    mark = (player_state == PLAYER2) ? 'X' : 'O';

    if (choice == 1 && square[1] == '1')
      square[1] = mark;
                  
    else if (choice == 2 && square[2] == '2')
      square[2] = mark;
                  
    else if (choice == 3 && square[3] == '3')
      square[3] = mark;
                  
    else if (choice == 4 && square[4] == '4')
      square[4] = mark;
                  
    else if (choice == 5 && square[5] == '5')
      square[5] = mark;
                  
    else if (choice == 6 && square[6] == '6')
      square[6] = mark;
                  
    else if (choice == 7 && square[7] == '7')
      square[7] = mark;
                  
    else if (choice == 8 && square[8] == '8')
      square[8] = mark;
                  
    else if (choice == 9 && square[9] == '9')
      square[9] = mark;
                  
    else 
      return 1;
    
    return 0;

  /*
  Serial.print("Current Player: Player %d\n\n\n", player_state + 1);
  */
}

/*********************************************

FUNCTION TO RETURN GAME STATUS
1 FOR GAME IS OVER WITH RESULT
-1 FOR GAME IS IN PROGRESS
O GAME IS OVER AND NO RESULT
**********************************************/

int checkwin() {
  if (square[1] == square[2] && square[2] == square[3]){
    if(square[1] == 'O')
      return 1;
    else 
      return 2;
  }

  else if (square[4] == square[5] && square[5] == square[6]){
    if(square[1] == 'O')
      return 1;
    else 
      return 2;
  }


  else if (square[7] == square[8] && square[8] == square[9]){
    if(square[1] == 'O')
      return 1;
    else 
      return 2;
  }


  else if (square[1] == square[4] && square[4] == square[7]){
    if(square[1] == 'O')
      return 1;
    else 
      return 2;
  }


  else if (square[2] == square[5] && square[5] == square[8]){
    if(square[1] == 'O')
      return 1;
    else 
      return 2;
  }


  else if (square[3] == square[6] && square[6] == square[9]){
    if(square[1] == 'O')
      return 1;
    else 
      return 2;
  }


  else if (square[1] == square[5] && square[5] == square[9]){
    if(square[1] == 'O')
      return 1;
    else 
      return 2;
  }


  else if (square[3] == square[5] && square[5] == square[7]){
    if(square[1] == 'O')
      return 1;
    else 
      return 2;
  }


  else if (square[1] != '1' && square[2] != '2'
    && square[3] != '3' && square[4] != '4'
    && square[5] != '5' && square[6] != '6'
    && square[7] != '7' && square[8] != '8'
    && square[9] != '9')

    return 0;

  else
    return -1;
}


/*******************************************************************
FUNCTION TO DRAW BOARD OF TIC TAC TOE WITH PLAYERS MARK
********************************************************************/


void board(tflite::ErrorReporter* error_reporter) {
  //system("cls");
  TF_LITE_REPORT_ERROR(error_reporter, "Tic Tac Toe");
  //delay(1);
  Serial.print("Player 1 (O)  -  Player 2 (X)\n\n\n");
  //delay(1);

  //TF_LITE_REPORT_ERROR(error_reporter, "%s %s %s\n%s %s %s\n%s %s %s", 
  //                                      square[1], square[2], square[3],
  //                                      square[4], square[5], square[6],
  //                                      square[7], square[8], square[9]
  //                                      );

  Serial.println("     |     |     ");
  //delay(1);

  Serial.print("  ");
  //delay(1);

  Serial.print(square[1]);
  //delay(1);

  Serial.print("  |  ");
  //delay(1);
  
  Serial.print(square[2]);
  //delay(1);

  Serial.print("  |  ");
  //delay(1);

  Serial.print(square[3]);
  //delay(1);

  Serial.println("\n_____|_____|_____");
  //delay(1);

  Serial.println("     |     |     ");
  //delay(1);
  
  Serial.print("  ");
  //delay(1);

  Serial.print(square[4]);
  //delay(1);
  Serial.print("  |  ");
  //delay(1);
  Serial.print(square[5]);
  //delay(1);
  Serial.print("  |  ");
  //delay(1);
  Serial.println(square[6]);

  
  //delay(1);
  Serial.println("_____|_____|_____");
  //delay(1);
  Serial.println("     |     |     ");

  //delay(1);
  Serial.print("  ");
  //delay(1);
  Serial.print(square[7]);
  //delay(1);
  Serial.print("  |  ");
  //delay(1);
  Serial.print(square[8]);
  //delay(1);
  Serial.print("  |  ");
  //delay(1);
  Serial.println(square[9]);
 
  //delay(1);
  Serial.println("     |     | ");
}

int get_choice(){
  int choice = 0;

  for(int i = 0; i < 4; i++){
    choice <<= 1;
    if(input_buf[i] == '1')
        choice += 1;
  }

  return choice;
}

int validate_input(){
  int choice = 0;

  for(int i = 0; i < 6; i++){
    if(input_buf[i] == '1')
        choice ^= 1;
  }
  return choice;
}

void set_input_buf(int testcase){
  for(int i = 0; i < input_ind; i++){
    input_buf[5-i] = (testcase & 1) ? '1' : '0';
    testcase >>= 1;
  }
  return;
}
  


// Toggles the built-in LED every inference, and lights a colored LED depending
// on which word was detected.
void RespondToCommand(tflite::ErrorReporter* error_reporter,
                      int32_t current_time, const char* found_command,
                      uint8_t score, bool is_new_command) {

 //TF_LITE_REPORT_ERROR(error_reporter, "Entered Respond");             
  static bool is_initialized = false;
  if (!is_initialized) {
    pinMode(LED_BUILTIN, OUTPUT);
    // Pins for the built-in RGB LEDs on the Arduino Nano 33 BLE Sense
    pinMode(LEDR, OUTPUT);
    pinMode(LEDG, OUTPUT);
    pinMode(LEDB, OUTPUT);
    // Ensure the LED is off by default.
    // Note: The RGB LEDs on the Arduino Nano 33 BLE
    // Sense are on when the pin is LOW, off when HIGH.
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, HIGH);
    is_initialized = true;
  }
  static int32_t last_command_time = 0;
  static int count = 0;
  static int certainty = 220;


  


  if (is_new_command) {
    TF_LITE_REPORT_ERROR(error_reporter, "Heard %s (%d) @%dms", found_command,
                         score, current_time);
    // If we hear a command, light up the appropriate LED
    if (found_command[0] == 'y') {
      last_command_time = current_time;
      digitalWrite(LEDG, LOW);  // Green for yes
    }

    if (found_command[0] == 'n') {
      last_command_time = current_time;
      digitalWrite(LEDR, LOW);  // Red for no
    }

    if (found_command[0] == 'u') {
      last_command_time = current_time;
      digitalWrite(LEDB, LOW);  // Blue for unknown
    }

if(test) {

      ///*Testing
      static int inp_counter = -1;
      inp_counter++;
      int testcases[10] = {
            0b000110,   //player 1 takes 1
            0b000110,   //player 2 try to take the same position => expected retake
            0b000101,   //player 2 decides to reinput
            0b000100,   //some communication error
            0b001010,   // player 2 takes 2
            0b010010,   // player 1 takes 4
            0b011110,   // player 2 takes 7
            0b010111,   // player 1 takes 5
            0b100111,   // player 2 takes 9
            0b011011,   // player 1 takes 6 => player 1 wins
      };
      
      input_ind = 6;
      set_input_buf(testcases[inp_counter]);   
      Serial.print("Test case = ");
      Serial.println(testcases[inp_counter]);  
}

      //*/

   
    if( test
      ||
      (
          (found_command[0] == 'y')
        || (found_command[0] == 'n')
        || (found_command[0] == 'u')
       )
    ) {

      

      //TF_LITE_REPORT_ERROR(error_reporter, "Inside");   
if(!test) {               
      input_buf[input_ind++] = (found_command[0] == 'y') ? '1': '0';
}
      

  
      // print the board status and the game mode
      //TF_LITE_REPORT_ERROR(error_reporter, "Printing board %c", square[0]);
      board(error_reporter);


      Serial.print("\n\nInput buffer: ");
      for(int i = 0; i < input_ind; i++){
        //Serial.print(i);
        //Serial.print(" ");
        Serial.print(input_buf[i]);
        //Serial.print(" ");
      }

      Serial.print("\n\n");
  
      if(input_ind == 6) {
        if(validate_input()){
          Serial.println("\n\nERROR: Invalid input combination. Please try again!\n\n");
          input_ind = 0;
        }
        else if(input_buf[4] == '0'){
          Serial.println("\n\nRe-enter the input!\n\n");
          input_ind = 0;
        }
        else {
  
          int choice = get_choice();
          Serial.print("Choice = ");
          Serial.println(choice);
          if(mark_board(choice)){
            Serial.println("\n\nERROR: Invalid move. Please try again!\n\n");
            input_ind = 0;
          }
          else {
            int board_status = checkwin();
      
            if((board_status == 1)
              || (board_status == 2)) {
      
              player_state = GAMEOVER;
      
              Serial.print("\n\n\n~~~~~~~~~~~~~~~~ GAME OVER! ~~~~~~~~~~~~~~~~~\n" );
              Serial.print("~~~~~~~~~ WINNER = PLAYER ");
              Serial.print(board_status);
              Serial.print(" ~~~~~~~~~~~~~~~~~\n\n\n" );
      
            }
            else if (board_status == 0) {
              player_state = GAMEOVER;
      
              Serial.print("\n\n\n~~~~~~~~~~~~~~~~ GAME OVER! ~~~~~~~~~~~~~~~~~\n" );
              Serial.print("~~~~~~~~~~~~~~~~ BOARD FULL! ~~~~~~~~~~~~~~~~~\n\n\n");
            }
            else {
              //Serial.print("~~~~~~~~~~~~~~~~ GAME ON ~~~~~~~~~~~~~~~~~\n\n\n");
              //board(error_reporter);
              if (player_state != GAMEOVER){
                player_state = (player_state) ? PLAYER1 : PLAYER2;
              }
            }
          }
        }
      }
    }
  }    //end of custom code
    

  // If last_command_time is non-zero but was >3 seconds ago, zero it
  // and switch off the LED.
  if (last_command_time != 0) {
    //if (last_command_time < (current_time - 3000)) {
  if (last_command_time < (current_time - 1000)) {
      last_command_time = 0;
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(LEDR, HIGH);
      digitalWrite(LEDG, HIGH);
      digitalWrite(LEDB, HIGH);
    }
    // If it is non-zero but <1 seconds ago, do nothing.
  }

  // Otherwise, toggle the LED every time an inference is performed.
  ++count;
  if (count & 1) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}

#endif  // ARDUINO_EXCLUDE_CODE
