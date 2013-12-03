// Morse code from 0 (ASCII 48) through Z (ASCII 90)
//                            0     1     2     3     4     5     6.... 7     8     9     :;<=>?@A  B    C    D   E F    G   H    I  J    K   L    M  N  O   P    Q    R   S   T U   V    W   X    Y    Z
const char MorseAlphabet[] = "-----|.----|..---|...--|....-|.....|-....|--...|---..|----.||||||||.-|-...|-.-.|-..|.|..-.|--.|....|..|.---|-.-|.-..|--|-.|---|.--.|--.-|.-.|...|-|..-|...-|.--|-..-|-.--|--..";
const unsigned int baseUnitInMs = 100;
const unsigned int dotUnits = 1;
const unsigned int dashUnits = 3;
const unsigned int intraCharacterGap = 1;
const unsigned int interCharacterGap = 3;
const unsigned int interWordGap = 7;
const unsigned int countOfChars = 42;
int idxCharInMorse[countOfChars];
int ledPin =13;

void setup()
{
  pinMode(ledPin, OUTPUT);     
  Serial.begin(9600);
  idxCharInMorse[0] = 0;
  Serial.print("Found character '");Serial.print(char(48));Serial.print("' at position ");Serial.println(0);
  int currentIdx = 1;
  for(int iMorseAlphabet = 0;iMorseAlphabet < sizeof(MorseAlphabet)-1;iMorseAlphabet++)
  {
    if(MorseAlphabet[iMorseAlphabet] == '|')
    {
      Serial.print("Found character '");Serial.print(char(currentIdx+48));Serial.print("' at position ");Serial.println(iMorseAlphabet+1);
      idxCharInMorse[currentIdx] = iMorseAlphabet + 1;
      currentIdx++;
    }
  }
  
}

void loop()
{
  char message[] = "ROB PURSER";
  Serial.print("sending: ");Serial.print(message);Serial.print(". length:");Serial.println(sizeof(message)-1);
  for(int iMessage = 0;iMessage < sizeof(message)-1;iMessage++)
  {
    if(message[iMessage] == ' ')
    {
      delay(baseUnitInMs * interWordGap);
      continue; 
    }
    Serial.print("Letter: ");Serial.println(char(message[iMessage]));
    int currentPos = idxCharInMorse[message[iMessage] - 48];
    Serial.print("Index into Morse: ");Serial.println(currentPos);
    while(MorseAlphabet[currentPos] != '|')
    {
      digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
      switch(MorseAlphabet[currentPos])
      {
        case '.':
          Serial.print(".");
          delay(baseUnitInMs * dotUnits);               // 1 units
          break;
        case '-':
          Serial.print("-");
          delay(baseUnitInMs * dashUnits);               // 3 units
        break;
      }
      currentPos++;
      digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
      delay(baseUnitInMs * intraCharacterGap);               // 1 units
    }
    Serial.println();
    delay(baseUnitInMs * interCharacterGap);               // 3 units
  }
  
//  for(unsigned iMorseMessage = 0;iMorseMessage < sizeof(morseMessage);iMorseMessage++)
//  {
//    Serial.print("Loop ");Serial.println(iMorseMessage);
//    digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
//    switch(morseMessage[iMorseMessage])
//    {
//      case '.':
//        Serial.println(".");
//        delay(baseUnitInMs * dotUnits);               // 1 units
//        break;
//      case '-':
//        Serial.println("-");
//        delay(baseUnitInMs * dashUnits);               // 3 units
//      break;
//    }
//    digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
//    delay(baseUnitInMs * intraCharacterGap);               // 1 units
//  }
}

