// Initialize the constants for LM35 temperature sensor and led pins
const int lm35Pin = A0;    
const int ledPin = 13;  

// store temperature, led state, and counters into a variable
float temp;
bool ledState = LOW;
int belowThresholdCount = 0;
int aboveThresholdCount = 0;

// Constants for temperature threshold, led intervals, and conversion factor
const float tempThreshold = 30.0;
const int belowThresholdInterval = 250;
const int aboveThresholdInterval = 500;
const float tempConversionFactor = 0.48876;

// setup function runs once at the start of execution
void setup() 
{
  pinMode(lm35Pin, INPUT);   // Set LM35 temperature sensor pin as input
  pinMode(ledPin, OUTPUT);   // Set led sensor pin as output
  
  // Initialize serial communication 
  Serial.begin(9600);
}

// execution of loop
void loop() 
{
  // Read the temperature from LM35 temperature sensor
  temp = readTemp();

  //print temperature values to Serial Monitor
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.println(" °C");

  // Check temperature conditions and control led accordingly
  if (temp < tempThreshold) 
  {
    manageBelowThresholdled();
  } 
  else 
  {
    manageAboveThresholdled();
  }
}

// use function to read temperature from LM35 sensor
float readTemp() 
{
  return analogRead(lm35Pin) * tempConversionFactor;  // Converting to Celsius
}

// Function to manage led when temperature falls below the threshold
void manageBelowThresholdled()
{
  // Increment below threshold count
  belowThresholdCount++;

  // Check if the interval has passed
  if (belowThresholdCount >= belowThresholdInterval / 2) 
  {
    // Reset the count value
    belowThresholdCount = 0;

    // Toggle the led state
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
}

// Function to manage led when temperature rises above the threshold
void manageAboveThresholdled() 
{
  // Increment the above threshold count
  aboveThresholdCount++;

  // Check if the interval has passed
  if (aboveThresholdCount >= aboveThresholdInterval / 2) 
  {
    // Reset the count
    aboveThresholdCount = 0;

    // Toggle the led state
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
}
