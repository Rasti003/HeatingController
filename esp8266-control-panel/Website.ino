void websiteBigin(){
server.on("/", []() {

    String page = "<!DOCTYPE html>";
    String IPaddress = WiFi.localIP().toString();
    page +=  "<html>";
    page +=  "<head>";
    page +=    "<meta http-equiv='Content-Type' content='text/html; charset=UTF-8' />";
    page +=    "<meta name='viewport' content='width=1,initial-scale=1,user-scalable=1' />";
    page +=    "<title>Centrum dowodzenia</title>";
    page +=  "<link href='http://fonts.googleapis.com/css?family=Lato:100italic,100,300italic,300,400italic,400,700italic,700,900italic,900' rel='stylesheet' type='text/css'>";
    page +=  "<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css'>";
    page +=  "<link rel='stylesheet' href='http://legalnyplener.pl/przemektest/kominek/biblioteki/style.css'/>";
    page += "<script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js'></script>";
    page += "<script type='text/javascript' src='https://ajax.googleapis.com/ajax/libs/jquery/1.7.2/jquery.min.js'></script> " ;
    page += "<script src='http://legalnyplener.pl/przemektest/kominek/biblioteki/jquery.easypiechart.min.js'></script>";
    page += " <script>";
    page += "$(function() {";
    page +=  " $('.chart').easyPieChart({";
    page +=    " easing: 'easeOutBounce',";
    page +=    " onStep: function(from, to, percent) {";
    page +=      " $(this.el).find('.percent').text(Math.round(percent));";
    page +=    " }";
    page +=  " });" ;
    page +=  "});";
    page +=  "</script>";
    page +=  "</head>";
    page +=  "<body>";
    page += "<body>";
    page += "<div style='overflow: hidden'>";
    page +=  "<div class='row'>";
    page +=    "<div class='col-xs-12 navbar-inverse text-center'>";
    page +=        "<div class='navbar-header' >";
    page +=          "<a class='navbar-brand active' href='http://" + IPaddress + "'>Centrum dowodzenia</a>";
    page +=       " </div> " ;
    page +=    "</div>";
    page +=  "</div>";
    page +=    "<div class='okregi'>";
    page +=      "<div class='col-xs-4' style='text-align: center;' ><span class='chart' data-percent=";
    page += fireplaceTMP;
    page +=     ">Kominek<span class='percent'></span></div>";
    page +=      "<div class='col-xs-4' style='text-align: center;'><span class='chart ' data-percent=";
    page += pumpFireplace;
    page +=       ">Pompa<span class='percent'></span></div>";
    page +=      "<div class='col-xs-4' style='text-align: center;'><span class='chart ' data-percent=";
    page += hysteresis;
    page +=     ">Histereza<span class='percent'></span></div>";
    page +=    "</div>";
    page +=    "<div class='row'>";
    page +=     "<div class='col-xs-10 col-xs-offset-1 ' >";
    page +=       "<form action='http://" + IPaddress + "' method='POST'>";
    page +=        "<input type='number' name='pumpFireplace_input' placeholder='90' step='1' min='0' max='90'; class='form-control' style='width: 100%; font-size: 24px; text-align: center' id='usr'>";
    page +=        "<button class='btn btn-default'  style='width: 100%; font-size: 24px;'  >Zapisz  Temp. Kominek</button>";
    page +=      "</form>";
    page +=    "</div>";
    page +=     "<div class='col-xs-10 col-xs-offset-1 ' style=' padding-top:20px;'>";
    page +=      "<form action='http://" + IPaddress + "' method='POST'>";
    page +=        "<input type='number' name='hysteresis_input' placeholder='10' step='1' min='0' max='30' class='form-control' style='width: 100%; font-size: 24px; font-size: 24px; text-align: center' id='usr'>";
    page +=        "<button class='btn btn-default' style='width: 100%; font-size: 24px;' >Zapisz histereze</button>";
    page +=      "</form>";
    page +=     "</div>";
    page +=      " <div class='col-xs-10 col-xs-offset-1' style=' padding-top:20px;'>";
    page +=     "<a href='http://" + IPaddress + "' class='btn btn-info btn-lg' style='width: 100%; '><span class='glyphicon glyphicon-refresh'></span> Refresh </a>";
    page +=  "</body>";
    page +=  "</html>";
    ;

    server.send(200, "text/html", page);
  });

  server.begin();
}

void websiteInput(){
    if (server.args() > 0 ) { // Arguments were received
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      Argument_Name = server.argName(i);
      if (server.argName(i) == "hysteresis_input") {

        int tmp = server.arg(i).toInt();
        if (tmp != 0) {
          if (tmp != hysteresis) {
            hysteresis =  tmp;
            digitalWrite(ledPin, HIGH);
            delay(100);
          }
        }
        Clients_Response1 = server.arg(i);

      }
      if (server.argName(i) == "pumpFireplace_input") {
        
      int tmp = server.arg(i).toInt();
        if (tmp != 0) {
          if (tmp != pumpFireplace) {
            pumpFireplace =  tmp;
            digitalWrite(ledPin, HIGH);
            delay(100);
          }
        }
        Clients_Response1 = server.arg(i);
        }
      }
    }
  }


