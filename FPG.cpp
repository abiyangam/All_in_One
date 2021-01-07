/*
Archivo: Tablas.0.2
Autor: Andrés Bombela Iyanga Molongua 
Fecha: Malaga, 28/04/2020
Descripcion: App que lleva el registro de partidas entre 2 jugadores.
*/

// Definición de bibliotecas a utilizar
#include <iostream>
#include <string>
#include <fstream>
using namespace std ;

// Declaración de prototipos: tipos, constantes y subprogramas
const unsigned MAX = 2 ;
const unsigned numero_jugadores = 2 ;

enum Estado_Fichero {
  OK, ERROR_APERTURA_FICH, ERROR_FORMATO
} ;

struct Datos_Jugador {
  unsigned Pos ; //Posicion
  string N ; //Nombre
  unsigned Pts ; //Puntos
  unsigned PT ; //Partidos
  unsigned G ; //Partidos ganados
  unsigned E ; //Partidos empatados
  unsigned P ; //Partidos perdidos
  unsigned GF ; //Goles a favor
  unsigned GC ; //Goles en contra
  int DG ; //Diferencia de goles
} ;

typedef Datos_Jugador TVC[MAX] ;

void delimitador() ;
void logo_tabla (ofstream & fichero_salida) ;
void tipo_codigo (Estado_Fichero clase) ;
void logo_inicio () ;
void logo_seccion1 () ;
void limpiar_pantalla () ;
void credits () ;
void menu () ;
void leer_fichero ( ifstream & fichero, string & lineas ) ;
void mostrar_lineas ( string lineas ) ;
void procesamiento_fichero ( string & documento, Estado_Fichero & tipo  ) ;


// Cuerpo del programa
int main()
{

  TVC Jugadores ;
  unsigned rondas ;
  unsigned partido_ronda ;
  unsigned Resultado ;
  unsigned Goles_favor ;
  unsigned Goles_contra ;
  char saveornot ;
  Estado_Fichero clase ;


    menu() ;
    cout << "     >A donde quiere ir?: " ;
    int seleccion ;
    cin >> seleccion ;
    cout << endl ;


    if (seleccion == 1) {
      limpiar_pantalla() ;
      logo_seccion1 () ;

        for (unsigned i = 0; i < numero_jugadores; i++) {
          cout << "Introduzca el nombre del jugador numero " << i+1 << ": " ;
          cin >> Jugadores[i].N ;
        }

        cout << endl ;

        cout << "LOS JUGADORES SON: " << endl ;
        cout << "-----------------" << endl ;
        for (unsigned i = 0; i < numero_jugadores; i++) {
          cout << "  <*> "<< Jugadores[i].N << endl ;
          Jugadores[i].Pos = 0 ;
          Jugadores[i].Pts = 0 ;
          Jugadores[i].PT = 0 ;
          Jugadores[i].G = 0 ;
          Jugadores[i].E = 0 ;
          Jugadores[i].P = 0 ;
          Jugadores[i].GF = 0 ;
          Jugadores[i].GC = 0 ;
          Jugadores[i].DG = 0 ;
        }

        cout << endl ;

        cout << "Cuantas rondas van jugar?: " ;
        cin >> rondas ;
        cout << "Cuantos partidos por ronda?: " ;
        cin >> partido_ronda ;

        unsigned total_partidos = rondas * partido_ronda ;
        cout << "Jugaran un total de: " << total_partidos << " partidos." << endl ;

        delimitador() ;

        for (unsigned i = 0; i < rondas; i++) {
          cout << endl ;
          cout << "                              Ronda numero " << i+1 << ": " << endl ;
          for (unsigned j = 0; j < partido_ronda; j++) {
            Jugadores[0].PT = Jugadores[0].PT + 1 ;
            Jugadores[1].PT = Jugadores[1].PT + 1 ;

            cout << " (#)Partido numero " << j+1 << ": " << endl ;

            cout << "     (+)Goles a favor de " << Jugadores[0].N << ": " ;
            cin >> Goles_favor ;
            Jugadores[0].GF = Jugadores[0].GF + Goles_favor ;

            cout << "     (-)Goles en contra de " << Jugadores[0].N << ": " ;
            cin >> Goles_contra ;
            Jugadores[0].GC = Jugadores[0].GC + Goles_contra;

            Goles_favor = 0 ;
            Goles_contra = 0 ;
            cout << endl ;

            cout << "     (+)Goles a favor de " << Jugadores[1].N << ": " ;
            cin >> Goles_favor ;
            Jugadores[1].GF = Jugadores[1].GF + Goles_favor ;

            cout << "     (-)Goles en contra de " << Jugadores[1].N << ": " ;
            cin >> Goles_contra ;
            Jugadores[1].GC = Jugadores[1].GC + Goles_contra;

            Goles_favor = 0 ;
            Goles_contra = 0 ;
            cout << endl ;
            cout << endl ;

            if (Jugadores[0].GF == Jugadores[1].GC && Jugadores[1].GF == Jugadores[0].GC) {

              cout << "     > El Resultado de esta ronda ha sido: " << endl ;
              cout << "     L  1. Empate." << endl ;
              cout << "     L  2. Hay un ganador." << endl ;
              cout << "     L  R: " ;
              cin >> Resultado ;
              cout << endl ;

              if (Resultado == 1) {
                Resultado = 0 ;
                Jugadores[0].Pts += 1 ;
                Jugadores[1].Pts += 1 ;
                Jugadores[0].E += 1 ;
                Jugadores[1].E += 1 ;
              } else if (Resultado == 2) {
                Resultado = 0 ;
                cout << "     (?)Quien es el vencedor?: " << endl ;
                cout << "     L  1. " << Jugadores[0].N << endl ;
                cout << "     L  2. " << Jugadores[1].N << endl ;
                cout << "     L  R: " ;
                cin >> Resultado ;
                if (Resultado == 1) {
                  Jugadores[0].Pts += 3 ;
                  Jugadores[1].Pts += 0 ;
                  Jugadores[0].G += 1 ;
                  Jugadores[1].P += 1 ;
                } else if (Resultado == 2) {
                  Jugadores[1].Pts += 3 ;
                  Jugadores[0].Pts += 0 ;
                  Jugadores[1].G += 1 ;
                  Jugadores[0].P += 1 ;
                }
              }

            } else {
              cout << "Ha introducido mal los datos!!!" << endl ;
              cout << "Nada de lo que ha hecho vale!!!" << endl ;
              for (unsigned i = 0; i < numero_jugadores; i++) {
                cout << Jugadores[i].N << endl ;
                Jugadores[i].Pts = 0 ;
                Jugadores[i].PT = 0 ;
                Jugadores[i].G = 0 ;
                Jugadores[i].E = 0 ;
                Jugadores[i].P = 0 ;
                Jugadores[i].GF = 0 ;
                Jugadores[i].GC = 0 ;
                Jugadores[i].DG = 0 ;
              }
            }

            Resultado = 0 ;
          }
        }

        Jugadores[0].DG = Jugadores[0].GF - Jugadores[0].GC ;
        Jugadores[1].DG = Jugadores[1].GF - Jugadores[1].GC ;

        delimitador() ;

      //Designar ganador

        if (Jugadores[0].Pts > Jugadores[1].Pts) {
          cout << " " << Jugadores[0].N << " es el ganador por tener mas puntos." << endl ;
          Jugadores[0].Pos = 1 ;
          Jugadores[1].Pos = 2 ;
        } else if (Jugadores[1].Pts > Jugadores[0].Pts) {
          cout << " " << Jugadores[1].N << " es el ganador por tener mas puntos." << endl ;
          Jugadores[1].Pos = 1 ;
          Jugadores[0].Pos = 2 ;
        } else if (Jugadores[0].Pts == Jugadores[1].Pts) {
          if (Jugadores[0].DG > Jugadores[1].DG) {
            cout << " " << Jugadores[0].N << " es el ganador por tener una mayor direfencia de goles." << endl ;
            Jugadores[0].Pos = 1 ;
            Jugadores[1].Pos = 2 ;
          } else if (Jugadores[1].DG > Jugadores[0].DG) {
            cout << " " << Jugadores[1].N << " es el ganador por tener una mayor direfencia de goles." << endl ;
            Jugadores[1].Pos = 1 ;
            Jugadores[0].Pos = 2 ;
          } else if (Jugadores[0].DG == Jugadores[1].DG) {
            if (Jugadores[0].GF > Jugadores[1].GF) {
              cout << " " << Jugadores[0].N << " es el ganador por tener mas goles a favor." << endl ;
              Jugadores[0].Pos = 1 ;
              Jugadores[1].Pos = 2 ;
            } else if (Jugadores[1].GF > Jugadores[0].GF) {
              cout << " " << Jugadores[1].N << " es el ganador por tener mas goles a favor." << endl ;
              Jugadores[1].Pos = 1 ;
              Jugadores[0].Pos = 2 ;
            } else if (Jugadores[0].GF == Jugadores[1].GF) {
              cout << " " << "Empate tecnico." << endl ;
              Jugadores[0].Pos = 1 ;
              Jugadores[1].Pos = 1 ;
            }
          }
        }

        cout << endl ;
        cout << endl ;
        cout << endl ;

        cout << "  Desea salvaguardar los datos [S/N] ?: " ;
        cin >> saveornot ;
        cout << endl ;

        do {
          cout << endl ;
          if (saveornot == 'N') {
            cout << endl ;
            cout << "  OK. Gracias por hacer uso de la aplicacion. " << endl ;
            break ;
          } else if (saveornot == 'S') {
            cout << endl ;
              cout << "  Introduzca el fichero donde guardara los datos: " ;
              string documento ;
              cin >> documento ;
              cout << endl ;


              ofstream fichero_salida ;
              fichero_salida.open(documento.c_str(), ios::app) ;

                if (fichero_salida.fail()) {
                  clase = ERROR_APERTURA_FICH ;
                } else {
                    logo_tabla (fichero_salida) ;
            //Tabla
                  if (Jugadores[0].Pos == 1) {
                    fichero_salida << endl ;
                    fichero_salida << "================================================================================" << endl ;
                    fichero_salida << "||  Pos | Nom | Ptos | Parts | Vic | E | Drrts | G.favor | G.contra | Dif.gls ||" << endl ;
                    fichero_salida << "================================================================================" << endl ;
                    fichero_salida << "||                                                                            ||" << endl ;
                    fichero_salida << "||  " << Jugadores[0].Pos << "     " << Jugadores[0].N << "   " << Jugadores[0].Pts << "        " << Jugadores[0].PT << "     " << Jugadores[0].G << "    " << Jugadores[0].E << "     " << Jugadores[0].P << "        " << Jugadores[0].GF << "          " << Jugadores[0].GC << "         " << Jugadores[0].DG << "    ||" << endl ;
                    fichero_salida << "||                                                                            ||" << endl ;
                    fichero_salida << "--------------------------------------------------------------------------------" << endl ;
                    fichero_salida << "||                                                                            ||" << endl ;
                    fichero_salida << "||  " << Jugadores[1].Pos << "     " << Jugadores[1].N << "   " << Jugadores[1].Pts << "        " << Jugadores[1].PT << "     " << Jugadores[1].G << "    " << Jugadores[1].E << "     " << Jugadores[1].P << "        " << Jugadores[1].GF << "          " << Jugadores[1].GC << "         " << Jugadores[1].DG << "    ||" << endl ;
                    fichero_salida << "||                                                                            ||" << endl ;
                    fichero_salida << "================================================================================" << endl ;
                    fichero_salida << endl ;
                  } else if (Jugadores[1].Pos == 1) {
                  fichero_salida << endl ;
                  fichero_salida << "================================================================================" << endl ;
                  fichero_salida << "||  Pos | Nom | Ptos | Parts | Vic | E | Drrts | G.favor | G.contra | Dif.gls ||" << endl ;
                  fichero_salida << "================================================================================" << endl ;
                  fichero_salida << "||                                                                            ||" << endl ;
                  fichero_salida << "||  " << Jugadores[1].Pos << "     " << Jugadores[1].N << "   " << Jugadores[1].Pts << "        " << Jugadores[1].PT << "     " << Jugadores[1].G << "    " << Jugadores[1].E << "     " << Jugadores[1].P << "        " << Jugadores[1].GF << "          " << Jugadores[1].GC << "         " << Jugadores[1].DG << "    ||" << endl ;
                  fichero_salida << "||                                                                            ||" << endl ;
                  fichero_salida << "--------------------------------------------------------------------------------" << endl ;
                  fichero_salida << "||                                                                            ||" << endl ;
                  fichero_salida << "||  " << Jugadores[0].Pos << "     " << Jugadores[0].N << "   " << Jugadores[0].Pts << "        " << Jugadores[0].PT << "     " << Jugadores[0].G << "    " << Jugadores[0].E << "     " << Jugadores[0].P << "        " << Jugadores[0].GF << "          " << Jugadores[0].GC << "         " << Jugadores[0].DG << "    ||" << endl ;
                  fichero_salida << "||                                                                            ||" << endl ;
                  fichero_salida << "================================================================================" << endl ;
                  fichero_salida << endl ;
                } else if ((Jugadores[0].Pos == 1) && (Jugadores[1].Pos == 1)) {
                  fichero_salida << endl ;
                  fichero_salida << "================================================================================" << endl ;
                  fichero_salida << "||  Pos | Nom | Ptos | Parts | Vic | E | Drrts | G.favor | G.contra | Dif.gls ||" << endl ;
                  fichero_salida << "================================================================================" << endl ;
                  fichero_salida << "||                                                                            ||" << endl ;
                  fichero_salida << "||  " << Jugadores[1].Pos << "     " << Jugadores[1].N << "   " << Jugadores[1].Pts << "        " << Jugadores[1].PT << "     " << Jugadores[1].G << "    " << Jugadores[1].E << "     " << Jugadores[1].P << "        " << Jugadores[1].GF << "          " << Jugadores[1].GC << "         " << Jugadores[1].DG << "    ||" << endl ;
                  fichero_salida << "||                                                                            ||" << endl ;
                  fichero_salida << "--------------------------------------------------------------------------------" << endl ;
                  fichero_salida << "||                                                                            ||" << endl ;
                  fichero_salida << "||  " << Jugadores[0].Pos << "     " << Jugadores[0].N << "   " << Jugadores[0].Pts << "        " << Jugadores[0].PT << "     " << Jugadores[0].G << "    " << Jugadores[0].E << "     " << Jugadores[0].P << "        " << Jugadores[0].GF << "          " << Jugadores[0].GC << "         " << Jugadores[0].DG << "    ||" << endl ;
                  fichero_salida << "||                                                                            ||" << endl ;
                  fichero_salida << "================================================================================" << endl ;
                  fichero_salida << endl ;
                  }

                    cout << "  Datos guardados satisfactoriamente." << endl ;

                  if (!fichero_salida.fail() || fichero_salida.eof()) {
                    clase = OK ;
                  } else {
                    clase = ERROR_FORMATO ;
                  }
                }
              fichero_salida.close() ;


              cout << endl ;
              tipo_codigo(clase) ;
              cout << endl ;
              cout << "        OK. Gracias por hacer uso de la aplicacion. " << endl ;
              cout << endl ;
              break ;
            }

          cout << "  Por favor, haga una eleccion valida." << endl ;
          cout << "  S = Si o N = No." << endl ;
          cout << endl ;
          cout << "  R: " ;
          cin >> saveornot ;
        } while ((saveornot != 'S') || (saveornot != 'N')) ;

        cout << endl ;
        cout << endl ;

    } else if (seleccion == 2) {
      cout << endl ;
      cout << endl ;
      cout << "     >Que desea hacer?: " << endl ;
      cout << "     L  1. Cargar tablas." << endl ;
      cout << "     L  2. Salir." << endl ;
      cout << "     L  R: " ;
      int seleccion ;
      cin >> seleccion ;
      if (seleccion == 1) {
        cout << endl ;
        cout << "     >Introduzca el nombre del fichero a consultar: " ;
        string documento ;
        cin >> documento ;
        limpiar_pantalla() ;
        procesamiento_fichero(documento, clase) ;
        tipo_codigo(clase) ;
        cout << endl ;
        cout << "        OK. Gracias por hacer uso de la aplicacion. " << endl ;
        cout << endl ;
        exit(1) ;

      } else if (seleccion == 2) {
        exit(1);
      }

    } else if (seleccion == 3) {
        credits() ;
        cout << "     >Tecle 1 para salir: " << endl ;
        cout << "     L  1. Salir." << endl ;
        cout << "     L  R: " ;
        int seleccion ;
        cin >> seleccion ;
        if (seleccion == 1) {
          cout << endl ;
          cout << "        OK. Gracias por hacer uso de la aplicacion. " << endl ;
          cout << endl ;
          exit(1) ;
        }
      }


return 0 ;
}

// Definición de tipos, constantes y subprogramas
void delimitador() {
  cout << endl ;
  cout << endl ;
  cout << "[##############################################################################]" << endl ;
  cout << endl ;
  cout << endl ;
}

void logo_seccion1 () {
  cout << endl ;
  cout << endl ;
  cout << "   _     _     _     _     _     _     _     _     _  " << endl ;
  cout << " / /_  / /_  / /_  / /_  / /_  / /_  / /_  / /_  / /_ " << endl ;
  cout << "(_L _|=|_O |=|_O |=|_N |=|_E |=|_R |=|_E |=|_E |=|_K )" << endl ;
  cout << " /_/    /_/   /_/   /_/   /_/   /_/   /_/   /_/   /_/ " << endl ;
  cout << endl ;
  cout << endl ;
}

void tipo_codigo (Estado_Fichero clase) {
  switch (clase) {
    case OK:
    cout << "    Fichero ha sigo procesado correctamente." << endl ;
    break ;
    case ERROR_APERTURA_FICH:
    cout << "    Error en la apertura del fichero de entrada." << endl ;
    break ;
    case ERROR_FORMATO:
    cout << "    Error de formato en la escritura del fichero." << endl ;
    break ;
  }
}

void logo_tabla (ofstream & fichero_salida) {
  fichero_salida << endl ;
  fichero_salida << endl ;
  fichero_salida << endl ;
  fichero_salida << "  _     _     _     _     _     _     _     _     _   " << endl ;
  fichero_salida << " / /_  / /_  / /_  / /_  / /_  / /_  / /_  / /_  / /_ " << endl ;
  fichero_salida << "(_L _|=|_O |=|_O |=|_N |=|_E |=|_R |=|_E |=|_E |=|_K )" << endl ;
  fichero_salida << " /_/    /_/   /_/   /_/   /_/   /_/   /_/   /_/   /_/ " << endl ;
  fichero_salida << endl ;
}

void logo_inicio () {
  cout << endl ;
  cout << endl ;
  cout << "####################################################" << endl ;
  cout << "#                                                  #" << endl ;
  cout << "#     __                                      __   #" << endl ;
  cout << "#    / /___  ____  ____  ___  ________  ___  / /__ #" << endl ;
  cout << "#   / / __ )/ __ )/ __ )/ _ )/ ___/ _ )/ _ )/ //_/ #" << endl ;
  cout << "#  / / /_/ / /_/ / / / /  __/ /  /  __/  __/ ,<    #" << endl ;
  cout << "# /_/(____/(____/_/ /_/(___/_/  (___/(___/__/|_|   #" << endl ;
  cout << "#                                                  #" << endl ;
  cout << "#                                                  #" << endl ;
  cout << "####################################################" << endl ;
  cout << endl ;
  cout << endl ;
}

void limpiar_pantalla () {
  for (int i = 0; i < 100; i++) {
    cout << endl ;
  }
}

void credits () {
  limpiar_pantalla () ;
  cout << "              Aplicacion creada por el equipo de Loonereek.                       " << endl ;
  cout << endl ;
  cout << "    Esperemos haya disfrutado de la version 0.2 de nuestra aplicacion.            " << endl ;
  cout << endl ;
  cout << "Toda propuesta destinada a mejorar la experiencia del usuario es bienvenida. Si   " << endl ;
  cout << "tiene alguna sugerencia no dude en ponerse en contacto con el equipo.             " << endl ;
  cout << endl ;
  cout << "                           DESIGNER: Makayla Dafne                                "<< endl ;
  cout << "                           PROGRAMMER1: Kayden Milles                             "<< endl ;
  cout << "                           PROGRAMMER2: Andres Bombela                            "<< endl ;
  cout << endl ;
  cout << "                      Last release date: April, 28th 2020                         "<< endl ;
  cout << endl ;
  cout << endl ;
}

void menu () {
  limpiar_pantalla () ;
  logo_inicio () ;
  cout << "               1.   CHALLENGE DIRECTO 'VS'         " << endl ;
  cout << "               2.   ESTADISTICAS                   " << endl ;
  cout << "               3.   CREDITOS                       " << endl ;
  cout << endl ;
  cout << "Coming soon: Liguilla(Todos vs Todos), Estudios probabilisticos, etc..." << endl ;
  cout << endl ;
  cout << endl ;
  cout << endl ;
}

void procesamiento_fichero ( string & documento, Estado_Fichero & clase ) {
  ifstream fichero ;
  fichero.open(documento.c_str(), ios::in) ;

    if (fichero.fail()) {
      clase = ERROR_APERTURA_FICH ;
    } else {
      string linea ;
      while (!fichero.fail()) {
        leer_fichero(fichero, linea) ;
        mostrar_lineas(linea) ;
      }
      if (!fichero.fail() || fichero.eof()) {
        clase = OK ;
      } else {
        clase = ERROR_FORMATO ;
      }
    }

  fichero.close() ;
}

void mostrar_lineas ( string lineas ) {
  cout << lineas << endl ;
}

void leer_fichero ( ifstream & fichero, string & lineas ) {
  getline(fichero, lineas) ;
}
