#include "busdb.h"

int total_paradas = 322;  
  
char *array_nombre_parada[] = {
"Sin datos",
"Centre - Doctor Caro",
"Vicente Blasco Ibañez, 22",
"Vicente Blasco Ibañez, 80",
"Inem Carrus",
"P. Moreno Sastre, 62",
"P. Moreno Sastre, 80",
"P. Moreno Sastre, 102",
"Sant Crispi",
"Almansa (Según Horario)",
"Pol. Ind. Carrus 1 (Según Horario)",
"Pol. Ind. Carrus 2 (Según Horario)",
"Pol. Ind. Carrus 3 (Según Horario)",
"Pol. Ind. Carrus 4 (Según Horario)",
"Pol. Ind. Carrus 5 (Según Horario)",
"Tanatori Carrus",
"Jardi D Asp",
"M. Campello Ruiz",
"El Toscar (Según Horario)",
"Jose Diez Mora (Según Horario)",
"Plaça Madrid",
"Leon Sanchez Saez",
"Reina Victoria, 141",
"Reina Victoria, 95",
"Reina Victoria - Jorge Juan",
"Ies La Assumpcio - Teulada",
"Hospital General",
"Ies Pere Ibarra - L Avet",
"Prolog. M. Soler Olmos",
"La Torreta - Curtidores",
"Mariano Soler Olmos",
"Pere Joan Perpinya, 26",
"Pere Joan Perpinya, 42",
"Pere Joan Perpinya, 80",
"C. P. L Alcudia",
"Antonio. P. Quiles, 87",
"Jardi 9 D Octubre",
"Antonio. P. Quiles, 9",
"Juan D. Martinez, 14",
"Juan D. Martinez, 56",
"Jardi Andalusia",
"Victoria Kent, 37",
"Avinguda Novelda, 79",
"Avinguda Novelda, 59",
"Jardi Francesc Canto",
"Avinguda Novelda, 17",
"Sant Fermi - C. Arenal",
"C. P. M. De L Assumpcio",
"Plaça Crevillent",
"Concepcio Arenal",
"Pere Joan Perpinya, 45",
"P. J. Perpinya - F. G. Lorca",
"Eduardo Fdez. Garcia",
"Ies La Torreta",
"Portalada",
"Hospital General - Teulada",
"Cristobal Sanz",
"Diagonal - Avg. Llibertat",
"Pol. Industrial Ida",
"Pol. Industrial Vuelta",
"Pl. Barcelona",
"Plaça 1Er De Maig",
"G. N. Caracena",
"Melchor Botella, 7",
"Centre Salut Carrus",
"Poliesportiu Carrus",
"Jose Romero Lopez, 115",
"Jose Romero Lopez, 67",
"Mario Pastor Sempere",
"Plaça Barcelona",
"Sant Fermi - Jorge Juan",
"Jorge Juan - Reina Victoria",
"Hospital Gral. - Ies Pere Ibarra",
"Magraner",
"Politecnic",
"Avinguda Alacant, 26",
"Jaime P. Javaloyes",
"Dr. Marañon",
"Plaça Altabix",
"Residencia 3A Edad",
"Renfe - Conservatori",
"Renfe - Parc Transit",
"Jardi F. F. Ordoñez",
"Clara Campoamor",
"Casablanca",
"Tomas Y Valiente, 2",
"Tomas Y Valiente, 40",
"Tomas Y Valiente, 88",
"Renfe - Carrus",
"Avinguda Llibertad, 11",
"Renfe - Parc Municipal",
"Estacio Autobusos",
"Avg. Universitat - Ies Misteri D Elx",
"Bisbe Winibal, 41",
"Bisbe Winibal, 25",
"Bisbe Winibal, 1",
"Pio Baroja, 57",
"Cp. San Fernando",
"Avinguda Santa Pola",
"Els Palmerars",
"Ies C. Sempere",
"Cine Altamira",
"Plaça De Baix",
"Plaça Constitucio",
"Plaça Dels Pontos",
"Raval",
"Morera",
"Sant Antoni - Esglesia",
"Sant Antoni",
"Eucaliptus",
"Comissaria",
"Daoiz",
"Cp. Ferrandez Cruz",
"Santa Maria",
"Sollana",
"Centre - Avg. C. Valenciana",
"Mestre Albeniz",
"Llar Del Pensionista",
"Pio Baroja, 28",
"Sixto Marco",
"Vicent Andres Estelles",
"Centre Salut Altabix",
"Parc Municipal",
"Espronceda",
"Avinguda Llauradors",
"Cp. Lluis Vives",
"Avinguda Corts Valencianes, 5",
"Museu Del Palmerar",
"Pere Joan Perpinya, 114",
"Ies Tirant Lo Blanc",
"Avinguda Llibertat, 137",
"Antonio Machado",
"Capitan Antonio Mena",
"Poeta M. Hernandez, 23",
"Jose Maria Peman",
"Jesuitines",
"Avg. Joan Carles I",
"Avinguda Alacant, 74",
"Oriola",
"Ies Victoria Kent-Hisenda",
"Mallorca",
"Ciutat Esportiva 1",
"Avg. Universitat - Poliesp. Altabix",
"Sucre",
"Correus Altabix",
"Avinguda Alacant, 59",
"Avinguda Alacant, 39",
"Plaça Benidorm",
"Plaça Jaume I",
"Cami Dels Magros, 14",
"Cami Dels Magros, 48",
"Diagonal",
"Cami Cementeri",
"Cementeri Nou 1",
"Cementeri Nou 2",
"Cementeri Nou 3",
"Cementeri Nou 4",
"Plaça L Algeps",
"Avg. Corts Valencianes, 31",
"C. P. El Palmerar",
"Fco. Perez Campillo, 12",
"Centre Comercial L Aljub",
"L Aljub - Bigastro",
"Bigastro 1",
"San Fulgencio Ida",
"Cami Crevillent,185",
"Cami Crevillent, 200",
"Venta Tio Jose",
"Palazon Ida",
"Farmacia",
"San Fulgencio Vuelta",
"Bigastro 3 Vuelta",
"L Aljub - Redovan",
"Casita De Reposo (Según Horario)",
"Avg. Llibertat - Correus",
"Cases De Ferrandez",
"La Galia",
"Vicente Clavel Florentino",
"Avinguda Travalon",
"Elche Palmeral Aventuras",
"Colege La Galia",
"Bar La Galia",
"Cami La Galia 1",
"Cami La Galia 2",
"Cami La Galia - El Pi",
"Cami La Galia 4",
"Cami La Galia 5",
"Carrer Pego 1",
"Carrer Pego 2",
"Carrer Pego, 90",
"Carrer Pego, 96",
"Mazarron",
"Fco. Perez Campillo, 11",
"Avg. De L Elx C. F. ",
"Bigastro 2 Vuelta",
"C.Social Sant Antoni (Según Horario)",
"Urb. Penya Les Aguiles, 1",
"Urb. Penya Les Aguiles, 2",
"Urb. Penya Les Aguiles, 3",
"Palazon Vuelta",
"E. Hernandez Selva, 32",
"Avinguda Novelda, 115",
"Jose Maria Castaño",
"E. Hernandez Selva, 64",
"Avinguda Llibertad, 138",
"Victoria Kent, 24",
"Caritas",
"Cauce",
"Club De Campo",
"Passeig De Ronda 1",
"Passeig De Ronda 2",
"Gasolinera",
"Alcoraia",
"Bassa Del Peix",
"La Ceramica 2",
"Cami Del Panta",
"Centre Salut Toscar",
"Cementeri Nou 5",
"C. O. Altabix",
"Marchena",
"Alcalde J. Hernandez Rizo, 48",
"Alcalde J. Hernandez Rizo, 43",
"Alcalde J. Hernandez Rizo, 1",
"J. Joaquin Landerer",
"Jaime Gomez Orts",
"Hort De Montenegro",
"Universitat - Estacio Autobusos",
"Ies Victoria Kent 2",
"Centre Social Nou Altabix",
"Josefina Manresa",
"Poliesportiu Altabix",
"Caratula",
"Barxell",
"Federico Garcia Lorca",
"Centre Salut El Pla",
"Poliesportiu El Pla",
"Torres Quevedo",
"Pisos Blaus",
"Pl. Crevillent - Antonio Machado",
"Centre Salut D. Sapena",
"Doctor Sapena",
"Tanatori L Aljub",
"Cp. Maria Benlliure",
"Pere Joan Perpinya, 63",
"Conrado Del Campo, 91",
"Conrado Del Campo, 47",
"Conrado Del Campo, 21",
"C. Social Sector 5E",
"Avg. L Altet 1",
"Avg. L Altet 2",
"Avg. L Altet 3",
"M.Martinez Valero (Según Horario)",
"Travalon",
"Jose L.Navarro Campello",
"Policia Local",
"Jose A.Cañete Juarez",
"Ciutat Esportiva 2",
"Ciutat De La Justicia",
"Victoria Kent, 9",
"Clara Campoamor, 19",
"Blas Valero, 109",
"Blas Valero, 55",
"Cami Del Magros 1",
"Cami Del Magros 2",
"Cami Vell D Asp 1",
"Cami Vell D Asp 2",
"Cami Vell D Asp 3",
"Cami Vell D Asp 4",
"Cami Vell D Asp 5",
"Cami Servici 1",
"Cami Servici 2",
"I.T.V.",
"Cami Servici Autovia 1",
"Cami Servici Autovia 2",
"Cami Dels Magros 3",
"Portes Encarnades",
"Pintor Juan De Juanes",
"Antonio De Ulloa",
"L Escorxador",
"Cami Del Bolo 1",
"Cami Del Bolo 2",
"Cami Del Bolo 3",
"Centro Dep.Municipal Forus Elche",
"Hospital Del Vinalopo",
"Presidente Adolfo Suarez, 7",
"Avinguda Jubalcoi",
"Universitat - Rectorat",
"Cami De Benavente 1",
"Cami De Benavente 2",
"Cami Vell De Castella",
"Ronda Nord, 1",
"Ronda Nord, 2",
"Ronda Nord, 3",
"Avinguda Unesco",
"Avg. Llibertad, 115",
"Avg. Llibertad, 69",
"Melchor Botella, 8",
"Cementeri Vell",
"Hipercor",
"Carretera De Matola (Según Horario)",
"Poeta M. Hernandez, 71",
"Avg. Llibertat - Reina Victoria",
"Avg. Llibertat - Cristobal Sanz",
"Avg. Universitat - Bisbe Winibal",
"Avg. Universitat - V. A. Estelles",
"Avg. Universitat - Sucre",
"C. Esportiva - Confrides",
"C. Esportiva - Pavello E. Lag",
"Barxell - Centre Comercial",
"Avg. Universitat - Plaça Castella",
"Universitat - Escola O. Idiomes",
"Avinguda Llibertat, 12",
"Avinguda Llibertat, 34",
"L Algeps - Avg. Llibertat",
"Bigastro 2 Ida",
"Bigastro 3 Ida",
"Tren: Oficina De Turismo",
"Tren: Parque Municipal",
"Tren: Calahorra",
"Tren: Museo Del Palmeral",
"Tren: Huerto Ripoll",
"Sin datos"
};
