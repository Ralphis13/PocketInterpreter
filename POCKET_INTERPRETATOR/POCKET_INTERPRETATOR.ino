 #include <SPI.h>
#include <SD.h>
#include <StackArray.h>

File myFile;
StackArray<bool> conditionStack;
bool shouldExecute = true;
int nestingLevel = 0;

bool boolvarebals[5];
byte bytevarebals[5];
int intvarebals[5];
char charvarebals[5];
long longvarebals[5];
String strvarebals[]={"", "", "", "", ""};

void setup() {
  Serial.begin(9600);
  if (!SD.begin(5)) {
    Serial.println("Initialization failed!");
    while (1);
  }
}

void loop() {
  myFile = SD.open("program.txt");

  while (myFile.available()) {
    
    String readstr = myFile.readStringUntil('\n');
    
    if (readstr.startsWith("IF")) {
      funkci(readstr);
    }
    
    if (shouldExecute) {
      comanda(readstr);
    }
    
    if (readstr.length() == 1) {
      if (!conditionStack.isEmpty()) {
        conditionStack.pop();
      }
      Serial.println("conditionStack ");
      Serial.print(conditionStack.peek());
      if (!conditionStack.isEmpty()) {
        shouldExecute = conditionStack.peek();
      } else {
        shouldExecute = true;
      }
    }
  }

  myFile.close();
}

void comanda(String readstr) {
  Serial.println("Processing command: " + readstr); 
  if (readstr.substring(0, 5) == "PRINT") {    //println
    if (readstr.substring(readstr.indexOf("[")).startsWith("[VR16_")) {   //println for int
      Serial.println(intvarebals[readstr.substring(readstr.indexOf("[VR16_")+6, readstr.indexOf("]")).toInt()-1]);
    }else if (readstr.substring(readstr.indexOf("[")).startsWith("[VR08_")) {   //println for byte
      Serial.println(bytevarebals[readstr.substring(readstr.indexOf("[VR08_")+6, readstr.indexOf("]")).toInt()-1]);
    }else if (readstr.substring(readstr.indexOf("[")).startsWith("[BOOL_")) {   //println for bool
      Serial.println(boolvarebals[readstr.substring(readstr.indexOf("[BOOL_")+6, readstr.indexOf("]")).toInt()-1]);
    }else if (readstr.substring(readstr.indexOf("[")).startsWith("[VR32_")) {   //println for long
      Serial.println(longvarebals[readstr.substring(readstr.indexOf("[VR32_")+6, readstr.indexOf("]")).toInt()-1]);
    }else if (readstr.substring(readstr.indexOf("[")).startsWith("[CHAR_")) {   //println for char
      Serial.println(charvarebals[readstr.substring(readstr.indexOf("[CHAR_")+6, readstr.indexOf("]")).toInt()-1]);
    }else if (readstr.substring(readstr.indexOf("[")).startsWith("[TEXT_")) {   //println for String
      Serial.println(strvarebals[readstr.substring(readstr.indexOf("[TEXT_")+6, readstr.indexOf("]")).toInt()-1]);
    }else{Serial.println(readstr.substring(readstr.indexOf("[")+1, readstr.indexOf("]")));}
  }else if (readstr.substring(0, 8) == "PRINTSTR") {    //команда print
    if (readstr.substring(readstr.indexOf("[")).startsWith("[VR16_")) {   //println for int
      Serial.print(intvarebals[readstr.substring(readstr.indexOf("[VR16_")+6, readstr.indexOf("]")).toInt()-1]);
    }else if (readstr.substring(readstr.indexOf("[")).startsWith("[VR08_")) {   //println for byte
      Serial.print(bytevarebals[readstr.substring(readstr.indexOf("[VR08_")+6, readstr.indexOf("]")).toInt()-1]);
    }else if (readstr.substring(readstr.indexOf("[")).startsWith("[BOOL_")) {   //println for bool
      Serial.print(boolvarebals[readstr.substring(readstr.indexOf("[BOOL_")+6, readstr.indexOf("]")).toInt()-1]);
    }else if (readstr.substring(readstr.indexOf("[")).startsWith("[VR32_")) {   //println for long
      Serial.print(longvarebals[readstr.substring(readstr.indexOf("[VR32_")+6, readstr.indexOf("]")).toInt()-1]);
    }else if (readstr.substring(readstr.indexOf("[")).startsWith("[CHAR_")) {   //println for char
      Serial.print(charvarebals[readstr.substring(readstr.indexOf("[CHAR_")+6, readstr.indexOf("]")).toInt()-1]);
    }else if (readstr.substring(readstr.indexOf("[")).startsWith("[TEXT_")) {   //println for String
      Serial.print(strvarebals[readstr.substring(readstr.indexOf("[TEXT_")+6, readstr.indexOf("]")).toInt()-1]);
    }else{Serial.print(readstr.substring(readstr.indexOf("[")+1, readstr.indexOf("]")));}
  }

  if (readstr.startsWith("TONE")) {    //tone
    int vare1=readstr.substring(readstr.indexOf("[")+1, readstr.indexOf(",")).toInt();
    int vare2=readstr.substring(readstr.indexOf(",")+1, readstr.lastIndexOf(",")).toInt();
    int vare3=readstr.substring(readstr.lastIndexOf(",")+1, readstr.indexOf("]")).toInt();
//    tone(vare1, vare2, vare3);
  }
  
  if (readstr.startsWith("VR16_")) {    // equalizing a variable of type int
      int numvar1;
    if (readstr.indexOf("=")!=-1) {
      if (readstr.substring(readstr.indexOf("=")).startsWith("=VR16_")){   
        numvar1=intvarebals[readstr.substring(readstr.indexOf("=VR16_")+6, readstr.indexOf("+")).toInt()-1];
      }else if (readstr.substring(readstr.indexOf("=")).startsWith("=")){  
        numvar1=readstr.substring(readstr.indexOf("=")+1, readstr.indexOf("+")).toInt();
      }
    }
    if (readstr.indexOf("+")!=-1) {
      if (readstr.substring(readstr.indexOf("+")).startsWith("+VR16_")){   
        numvar1=numvar1+intvarebals[readstr.substring(readstr.indexOf("+VR16_")+6).toInt()-1];
      }else if (readstr.substring(readstr.indexOf("+")).startsWith("+")){  
        numvar1=numvar1+readstr.substring(readstr.indexOf("+")+1).toInt();
      }
    }
    intvarebals[readstr.substring(readstr.indexOf("VR16_")+5, readstr.indexOf("=")).toInt()-1]=numvar1;  
  }

  if (readstr.startsWith("VR08_")) {    // equating a variable of type byte
      int numvar2;
    if (readstr.indexOf("=")!=-1) {
      if (readstr.substring(readstr.indexOf("=")).startsWith("=VR08_")){   
        numvar2=bytevarebals[readstr.substring(readstr.indexOf("=VR08_")+6, readstr.indexOf("+")).toInt()-1];
      }else if (readstr.substring(readstr.indexOf("=")).startsWith("=")){  
        numvar2=readstr.substring(readstr.indexOf("=")+1, readstr.indexOf("+")).toInt();
      }
    }
    if (readstr.indexOf("+")!=-1) {
      if (readstr.substring(readstr.indexOf("+")).startsWith("+VR08_")){   
        numvar2=numvar2+bytevarebals[readstr.substring(readstr.indexOf("+VR08_")+6).toInt()-1];
      }else if (readstr.substring(readstr.indexOf("+")).startsWith("+")){  
        numvar2=numvar2+readstr.substring(readstr.indexOf("+")+1).toInt();
      }
    }
    bytevarebals[readstr.substring(readstr.indexOf("VR08_")+5, readstr.indexOf("=")).toInt()-1]=numvar2;  
  }

  if (readstr.startsWith("BOOL_")) {    // equating a variable of type bool
      int numvar3;
    if (readstr.indexOf("=")!=-1) {
      if (readstr.substring(readstr.indexOf("=")).startsWith("=BOOL_")){   
        numvar3=boolvarebals[readstr.substring(readstr.indexOf("=BOOL_")+6, readstr.indexOf("+")).toInt()-1];
      }else if (readstr.substring(readstr.indexOf("=")).startsWith("=")){  
        numvar3=readstr.substring(readstr.indexOf("=")+1, readstr.indexOf("+")).toInt();
      }
    }
    if (readstr.indexOf("+")!=-1) {
      if (readstr.substring(readstr.indexOf("+")).startsWith("+BOOL_")){   
        numvar3=numvar3+boolvarebals[readstr.substring(readstr.indexOf("+BOOL_")+6).toInt()-1];
      }else if (readstr.substring(readstr.indexOf("+")).startsWith("+")){  
        numvar3=numvar3+readstr.substring(readstr.indexOf("+")+1).toInt();
      }
    }
    boolvarebals[readstr.substring(readstr.indexOf("BOOL_")+5, readstr.indexOf("=")).toInt()-1]=numvar3;  
  }

  if (readstr.startsWith("CHAR_")) {    // equating a variable of type char
      int numvar4;
    if (readstr.indexOf("=")!=-1) {
      if (readstr.substring(readstr.indexOf("=")).startsWith("=CHAR_")){   
        numvar4=charvarebals[readstr.substring(readstr.indexOf("=CHAR_")+6, readstr.indexOf("+")).toInt()-1];
      }else if (readstr.substring(readstr.indexOf("=")).startsWith("=")){  
        numvar4=readstr.substring(readstr.indexOf("=")+1, readstr.indexOf("+")).charAt(0);
      }
    }
    if (readstr.indexOf("+")!=-1) {
      if (readstr.substring(readstr.indexOf("+")).startsWith("+CHAR_")){   
        numvar4=numvar4+charvarebals[readstr.substring(readstr.indexOf("+CHAR_")+6).toInt()-1];
      }else if (readstr.substring(readstr.indexOf("+")).startsWith("+")){  
        numvar4=numvar4+readstr.substring(readstr.indexOf("+")+1).charAt(0);
      }
    }
    charvarebals[readstr.substring(readstr.indexOf("CHAR_")+5, readstr.indexOf("=")).toInt()-1]=numvar4;  
  }

  if (readstr.startsWith("VR32_")) {    // equating a variable of type long
      long numvar5;
    if (readstr.indexOf("=")!=-1) {
      if (readstr.substring(readstr.indexOf("=")).startsWith("=VR32_")){   
        numvar5=longvarebals[readstr.substring(readstr.indexOf("=VR32_")+6, readstr.indexOf("+")).toInt()-1];
      }else if (readstr.substring(readstr.indexOf("=")).startsWith("=")){  
        numvar5=atol(readstr.substring(readstr.indexOf("=")+1, readstr.indexOf("+")).c_str());
      }
    }
    if (readstr.indexOf("+")!=-1) {
      if (readstr.substring(readstr.indexOf("+")).startsWith("+VR32_")){   
        numvar5=numvar5+longvarebals[readstr.substring(readstr.indexOf("+VR32_")+6).toInt()-1];
      }else if (readstr.substring(readstr.indexOf("+")).startsWith("+")){
        numvar5=numvar5+atol(readstr.substring(readstr.indexOf("+")+1).c_str());
      }
    }
    longvarebals[readstr.substring(readstr.indexOf("VR32_")+5, readstr.indexOf("=")).toInt()-1]=numvar5;  
  }

  if (readstr.startsWith("TEXT_")) {    // equalizing a variable of type String
      String numvar6;
    if (readstr.indexOf("=")!=-1) {
      if (readstr.substring(readstr.indexOf("=")).startsWith("=TEXT_")){   
        numvar6=strvarebals[readstr.substring(readstr.indexOf("=TEXT_")+6, readstr.indexOf("+")).toInt()-1];
      }else if (readstr.substring(readstr.indexOf("=")).startsWith("=")){  
        numvar6=readstr.substring(readstr.indexOf("=")+1, readstr.indexOf("+"));
      }
    }
    if (readstr.indexOf("+")!=-1) {
      if (readstr.substring(readstr.indexOf("+")).startsWith("+TEXT_")){   
        numvar6=numvar6+strvarebals[readstr.substring(readstr.indexOf("+TEXT_")+6).toInt()-1];
      }else if (readstr.substring(readstr.indexOf("+")).startsWith("+")){  
        numvar6=numvar6+readstr.substring(readstr.indexOf("+")+1);
      }
    }
    strvarebals[readstr.substring(readstr.indexOf("TEXT_")+5, readstr.indexOf("=")).toInt()-1]=numvar6;  
  }  
  if (readstr.startsWith("DELAY")) {
    delay(readstr.substring(6).toInt());
  }
  
  if (readstr.startsWith("IF")) {
    funkci(readstr);
  }
    Serial.print("shouldExecute: ");
  Serial.println(shouldExecute);
}

void funkci(String readstr) {
  int operatorPos;
   
  if (readstr.substring(readstr.indexOf("="), readstr.indexOf("=") + 1).startsWith("=")) {
    operatorPos = 5;
  }
  
  String leftValue = readstr.substring(3, readstr.indexOf("="));
  String rightValue = readstr.substring(readstr.indexOf("=") + 1, readstr.indexOf(":"));
   Serial.println("Processing condition: " + readstr); // tracking current condition
  
  Serial.println("Left Value: " + leftValue); // Print leftValue to the console
  Serial.println("Right Value: " + rightValue); // Print rightValue to the console
  
  if (operatorPos == 5) {
    bool currentCondition = false;
    if (leftValue.startsWith("BOOL_")){    //read the value of the boolean type that we wrote in the file
      leftValue=boolvarebals[leftValue.substring(leftValue.indexOf("BOOL_")+5).toInt()-1];
    }
    if (rightValue.startsWith("BOOL_")){
      rightValue=boolvarebals[rightValue.substring(rightValue.indexOf("BOOL_")+5).toInt()-1];
    }
    if (leftValue.startsWith("VR08_")){    //read the value of the byte type that we wrote in the file
      leftValue=bytevarebals[leftValue.substring(leftValue.indexOf("VR08_")+5).toInt()-1];
    }
    if (rightValue.startsWith("VR08_")){
      rightValue=bytevarebals[rightValue.substring(rightValue.indexOf("VR08_")+5).toInt()-1];
    }
    if (leftValue.startsWith("VR16_")){    //read the value of the int type we wrote in the file
      leftValue=intvarebals[leftValue.substring(leftValue.indexOf("VR16_")+5).toInt()-1];
    }
    if (rightValue.startsWith("VR16_")){
      rightValue=intvarebals[rightValue.substring(rightValue.indexOf("VR16_")+5).toInt()-1];
    }
    if (leftValue.startsWith("VR32_")){    //read the value of the peer type long that we wrote in the file
      leftValue=longvarebals[leftValue.substring(leftValue.indexOf("VR32_")+5).toInt()-1];
    }
    if (rightValue.startsWith("VR32_")){
      rightValue=longvarebals[rightValue.substring(rightValue.indexOf("VR32_")+5).toInt()-1];
    }
    if (leftValue.startsWith("CHAR_")){    //read the value of the char type that we wrote in the file
      leftValue=charvarebals[leftValue.substring(leftValue.indexOf("CHAR_")+5).toInt()-1];
    }
    if (rightValue.startsWith("CHAR_")){
      rightValue=charvarebals[rightValue.substring(rightValue.indexOf("CHAR_")+5).toInt()-1];
    }
    if (leftValue.startsWith("TEXT_")){    //read the value of the string type that we wrote in the file
      leftValue=strvarebals[leftValue.substring(leftValue.indexOf("TEXT_")+5).toInt()-1];
    }
    if (rightValue.startsWith("TEXT_")){
      rightValue=strvarebals[rightValue.substring(rightValue.indexOf("TEXT_")+5).toInt()-1];
    }    
    // Check if the leftValue represents a range of values
    if (leftValue.startsWith("[")) {
      // Check if the leftValue represents a range with enumerated values
      if (leftValue.indexOf("|") != -1) {
        // Extract the enumerated values from the range
        String valuesStr = leftValue.substring(1, leftValue.indexOf("]"));
        int pipeIndex = -1; // Track the index of the "|" delimiter
        int prevPipeIndex = 0; // Track the index of the previous "|" delimiter
        int numValues = 0; // Count the number of enumerated values
        
        while ((pipeIndex = valuesStr.indexOf("|", prevPipeIndex)) != -1) {
          numValues++;
          prevPipeIndex = pipeIndex + 1;
        }
        numValues++; // Increment the count for the last value
        
        String* values = new String[numValues]; // Create an array to store the enumerated values
        
        prevPipeIndex = 0; // Reset the index of the previous "|" delimiter
        int valueIndex = 0; // Track the index of the current value
        
        while ((pipeIndex = valuesStr.indexOf("|", prevPipeIndex)) != -1) {
          values[valueIndex] = valuesStr.substring(prevPipeIndex, pipeIndex);
          valueIndex++;
          prevPipeIndex = pipeIndex + 1;
        }
        values[valueIndex] = valuesStr.substring(prevPipeIndex); // Store the last value
        
        // Check if the rightValue matches any of the enumerated values
        for (int i = 0; i < numValues; i++) {
          if (rightValue.toInt() == values[i].toInt()) {
            currentCondition = true;
            break;
          }
        }
        
        delete[] values; // Free the dynamically allocated array
      }
      // Check if the leftValue represents a numeric range
      else {
        // Extract the lower and upper bounds from the range
        int rangeStart = leftValue.substring(1, leftValue.indexOf(" ")).toInt();
        int rangeEnd = leftValue.substring(leftValue.indexOf(" ") + 1, leftValue.indexOf("]")).toInt();
        
        // Check if the rightValue is within the range
        if (rightValue.toInt() >= rangeStart && rightValue.toInt() <= rangeEnd) {
          currentCondition = true;
        }
      }
    }
    
    // Check if the rightValue represents a range of values
    else if (rightValue.startsWith("[")) {
      // Check if the rightValue represents a range with enumerated values
      if (rightValue.indexOf("|") != -1) {
        // Extract the enumerated values from the range
        String valuesStr = rightValue.substring(1, rightValue.indexOf("]"));
        int pipeIndex = -1; // Track the index of the "|" delimiter
        int prevPipeIndex = 0; // Track the index of the previous "|" delimiter
        int numValues = 0; // Count the number of enumerated values
        
        while ((pipeIndex = valuesStr.indexOf("|", prevPipeIndex)) != -1) {
          numValues++;
          prevPipeIndex = pipeIndex + 1;
        }
        numValues++; // Increment the count for the last value
        
        String* values = new String[numValues]; // Create an array to store the enumerated values
        
        prevPipeIndex = 0; // Reset the index of the previous "|" delimiter
        int valueIndex = 0; // Track the index of the current value
        
        while ((pipeIndex = valuesStr.indexOf("|", prevPipeIndex)) != -1) {
          values[valueIndex] = valuesStr.substring(prevPipeIndex, pipeIndex);
          valueIndex++;
          prevPipeIndex = pipeIndex + 1;
        }
        values[valueIndex] = valuesStr.substring(prevPipeIndex); // Store the last value
        
        // Check if the leftValue matches any of the enumerated values
        for (int i = 0; i < numValues; i++) {
          if (leftValue.toInt() == values[i].toInt()) {
            currentCondition = true;
            break;
          }
        }
        
        delete[] values; // Free the dynamically allocated array
      }
      // Check if the rightValue represents a numeric range
      else {
        // Extract the lower and upper bounds from the range
        int rangeStart = rightValue.substring(1, rightValue.indexOf(" ")).toInt();
        int rangeEnd = rightValue.substring(rightValue.indexOf(" ") + 1, rightValue.indexOf("]")).toInt();
        
        // Check if the leftValue is within the range
        if (leftValue.toInt() >= rangeStart && leftValue.toInt() <= rangeEnd) {
          currentCondition = true;
        }
      }
    }
    // Check if both leftValue and rightValue are single values
    else {
      // Compare leftValue and rightValue for equality
      currentCondition = (leftValue == rightValue);
       Serial.print("currentCondition: ");
  Serial.println(currentCondition);
    }
    
    conditionStack.push(currentCondition);
    
    if (nestingLevel < 5) {
      nestingLevel++;
    }
    
      if (conditionStack.peek()) {
        shouldExecute = true;
      } else {
        shouldExecute = false;
      }

  }
  Serial.print("shouldExecute: ");
  Serial.println(shouldExecute);
  Serial.print("conditionStack: ");
  Serial.println(conditionStack.peek());
}




/*
IF 0=1:
PRINT[111]

IF 2=[1|2|3|4]:
PRINT[222]

IF 4=3:
IF [3 7]=4:
PRINT[444]

PRINT[333]

IF [1|2|3|4]=3:
IF 5=[3 7]:
PRINT[555]

PRINT[777]

PRINT[888]

DELAY[200]
*/
