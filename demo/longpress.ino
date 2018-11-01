int LED1 = 13;
int button = 0;

boolean LED1State = false;
boolean LED2State = false;

long buttonTimer = 0;
long longPressTime = 1250;

boolean buttonActive = false;
boolean longPressActive = false;

void setup() {

	pinMode(LED1, OUTPUT);
	pinMode(button, INPUT);

}

void loop() {

	if (digitalRead(button) == LOW) {

		if (buttonActive == false) {

			buttonActive = true;
			buttonTimer = millis();

		}

		if ((millis() - buttonTimer > longPressTime) && (longPressActive == false)) {

			longPressActive = true;
			LED1State = !LED1State;
			digitalWrite(LED1, LED1State);

		}

	} else {

		if (buttonActive == true) {

			if (longPressActive == true) {

				longPressActive = false;

			} else {

				// LED2State = !LED2State;
				// digitalWrite(LED2, LED2State);

			}

			buttonActive = false;

		}

	}

}