// Morse code from 0 (ASCII 48) through Z (ASCII 90)
//                            0     1     2     3     4     5     6.... 7     8     9     :;<=>?@A  B    C    D   E F    G   H    I  J    K   L    M  N  O   P    Q    R   S   T U   V    W   X    Y    Z
const char MorseAlphabet[] = "-----|.----|..---|...--|....-|.....|-....|--...|---..|----.||||||||.-|-...|-.-.|-..|.|..-.|--.|....|..|.---|-.-|.-..|--|-.|---|.--.|--.-|.-.|...|-|..-|...-|.--|-..-|-.--|--..";
const unsigned int baseUnitInMs = 200;
const unsigned int dotUnits = 1;
const unsigned int dashUnits = 3;
const unsigned int intraCharacterGap = 1;
const unsigned int interCharacterGap = 3;
const unsigned int interWordGap = 7;
const unsigned int countOfChars = 42;
int idxCharInMorse[42];
int ledPin = 13;

void setup()
{
  pinMode(ledPin, OUTPUT);     
  idxCharInMorse[0] = 0;
  int iMorseAlphabet = 0;
  int currentIdx = 1;
  while(iMorseAlphabet < sizeof(MorseAlphabet))
  {
    if(MorseAlphabet[iMorseAlphabet] == '|')
    {
      idxCharInMorse[currentIdx] = iMorseAlphabet + 1;
      currentIdx++;
    }
    iMorseAlphabet++;
  }
  
}

void loop()
{
  char message[] = "SOS";
  for(unsigned iMessage = 0;iMessage < sizeof(message);iMessage++)
  {
    char currentCharInMessage = message[iMessage];
    int idxCurrentMorseSymbol = idxCharInMorse[currentCharInMessage - 48];
    while(idxCharInMorse[idxCurrentMorseSymbol] != '|')
    {
      digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
      switch(idxCharInMorse[idxCurrentMorseSymbol])
      {
        case '.':
          delay(baseUnitInMs * dotUnits);               // 1 units
          break;
        case '-':
          delay(baseUnitInMs * dashUnits);               // 3 units
        break;
      }
      digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
      delay(baseUnitInMs * intraCharacterGap);               // 1 units
      idxCurrentMorseSymbol++;
    }
    delay(baseUnitInMs * interCharacterGap);               // 1 units
  }
}

