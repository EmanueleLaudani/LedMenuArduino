void setup() {
  pinMode(5, OUTPUT); //verde
  pinMode(9 , OUTPUT); //Giallo
  pinMode(10, OUTPUT); //Rosso
  pinMode(3, OUTPUT); //Bianco
  analogWrite(5, 0);
  analogWrite(9, 0);
  analogWrite(10, 0);
  analogWrite(3, 0);
  Serial.begin(9600);

}
//Gestisce quale dei due menu stampare (TRUE MENU - FALSE SOTTOMENU)
bool stampaMenu = true;
int valoreSoftLight = 15;
int valoreOn = 255;
//Stampa il menu
void show_menu(String stato[]) {
  Serial.println("##################");
  Serial.println("1.Green" + stato[0]);
  Serial.println("2.Giallo" + stato[1]);
  Serial.println("3.Rosso" + stato[2]);
  Serial.println("4.Bianco" + stato[3]);
  Serial.println("5.Exit");
  Serial.println("##################");
}
//Stampa il sottoMenu
void show_sottoMenu() {
  Serial.println("##################");
  Serial.println("1.On");
  Serial.println("2.Off");
  Serial.println("3.Soft Light");
  Serial.println("4.Go Back");
  Serial.println("##################");
}

//OUTPUT mi serve per capire quale luce è stata scelta
void gestione_Luci(int sottoMenu, int output, String stato []) {
  if (sottoMenu != 0) {
    switch (sottoMenu) {
      //Gestione Accensione
      case 1:
        if (output == 0) {
          analogWrite(5, valoreOn);
          stato[0]="(ON)";
        } else if (output == 1) {
          analogWrite(9, valoreOn);
          stato[1]="(ON)";
        } else if (output == 2) {
          analogWrite(10, valoreOn);
          stato[2]="(ON)";
        } else if (output == 3) {
          analogWrite(3, valoreOn);
          stato[3]="(ON)";
        }
        sottoMenu = 0;
        break;
        //Gestione  Spegnimento
      case 2:
        if (output == 0) {
          analogWrite(5, 0);
          stato[0]="(OFF)";
        } else if (output == 1) {
          analogWrite(9, 0);
          stato[1]="(OFF)";
        } else if (output == 2) {
          analogWrite(10, 0);
          stato[2]="(OFF)";
        } else if (output == 3) {
          analogWrite(3, 0);
          stato[3]="(OFF)";
        }
        sottoMenu = 0;
        break;
        //Gestione  Luce Soffusa
      case 3:
        if (output == 0) {
          analogWrite(5, valoreSoftLight);
          stato[0]="(SOFT LIGHT)";
        } else if (output == 1) {
          analogWrite(9, valoreSoftLight);
          stato[1]="(SOFT LIGHT)";
        } else if (output == 2) {
          analogWrite(10, valoreSoftLight);
          stato[2]="(SOFT LIGHT)";
        } else if (output == 3) {
          analogWrite(3, valoreSoftLight);
          stato[3]="(SOFT LIGHT)";
        }
        sottoMenu = 0;
        break;
      case 4:

        stampaMenu = true;

        break;
      default:
        Serial.print("Valore non valido");
    }
  }
}
String stato [] = {"(OFF)", "(OFF)", "(OFF)", "(OFF)"};
//Scelta del sotto menu
int sottoMenu = 0;
//Segna la luce scelta
int output = 0;
//Scelta del Menu
int menu = 0;
void loop() {

  if (stampaMenu) {
    output = 0;
    menu = 0;
    show_menu(stato);
    while (menu == 0) {
      menu = Serial.parseInt();
    }
    switch (menu) {
      case 1:
        output = 0;
        stampaMenu = false;
        break;
      case 2:
        output = 1;
        stampaMenu = false;
        break;
      case 3:
        output = 2;
        stampaMenu = false;
        break;
      case 4:
        output = 3;
        stampaMenu = false;
        break;
      case 5:
        Serial.println("Ciao");
        stampaMenu = false;
        break;
      default:
        Serial.println("Valore Non valido");

    }

  }
  if (!stampaMenu && menu != 5) {
    show_sottoMenu();
    while (sottoMenu == 0) {
      sottoMenu = Serial.parseInt();
    }
    gestione_Luci(sottoMenu, output, stato);
    sottoMenu = 0;
  }

}
