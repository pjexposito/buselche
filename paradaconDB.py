#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sqlite3 as lite
from suds.client import Client

parada = raw_input ("¿Qué parada buscas? ")
linea = raw_input ("Ahora, introduce la línea: ")
linea = linea.upper()

url = 'http://www.isae-auesa.com:82/services/dinamica.asmx?wsdl'
client = Client(url)
lineas_totales = 2
posicion_tabla = 0
correccion = 0
file = open("busdb.c", "w")
file.write("#include \"busdb.h\"\n\n")

file.write("char *array_nombre_parada[] = {\n")
file.write("\"Sin datos\",\n")

con = lite.connect('datos.db')
with con:
    
    cur = con.cursor()
    cur.execute("SELECT * FROM parada")
    rows = cur.fetchall()
    for row in rows:
        posicion_tabla = posicion_tabla + 1
        cadena = row[1][6:].title()
        cadena2 = row[0]
        if (posicion_tabla+correccion != cadena2):
            file.write("\"Sin datos\",\n")
            correccion = correccion+1
            lineas_totales = lineas_totales + 1
        file.write("\""+ cadena.encode('utf8')+"\""+","+"\n")
        lineas_totales = lineas_totales+1
        if parada == str(row[0]):
            nombre = row[1][6:].title()
            # Como el valor incluye el numero de parada, yo se lo quito
            # El title del final hace que la direccion, que es todo mayusculas, se convierta en minusculas salvo la
            # primera letra de cada palabra
        
file.write("\"Sin datos\"\n};\n\nint total_paradas = "+ str(lineas_totales) + ";")
file = open("busdb.h", "w")
file.write("char *array_nombre_parada["+str(lineas_totales)+"];\nint total_paradas;")


if client.service.GetPasoParada(linea,parada,0).GetPasoParadaResult:
    tiempo1 = client.service.GetPasoParada(linea,parada,0).GetPasoParadaResult.PasoParada[0].e1.minutos
    tiempo2 = client.service.GetPasoParada(linea,parada,0).GetPasoParadaResult.PasoParada[0].e2.minutos
    print 'Faltan %s y %s minutos para que pase la linea %s por la parada %s (%s)' % (tiempo1, tiempo2, linea, parada, nombre)

else:
    print "Esa línea no existe"
