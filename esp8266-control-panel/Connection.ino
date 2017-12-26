
void Connection() {
  WiFi.begin(myssid, mypass);
  display.print("Podlaczanie do sieci");
  display.display();

  // Wait for successful connection
  int i = 0;

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    display.print(".");
    display.display();
    i++;
    if ( i > 20) {
      isConected = false;
      break;
    }
  }

  if (isConected == true) {

    display.clearDisplay();
    display.println("Polaczono do");
    display.println(myssid);
    display.display();
    delay(2000);
  }
  else {
    display.clearDisplay();
    display.println("NIE POLACZONO!");
    display.display();
    delay(2000);
  }

}



