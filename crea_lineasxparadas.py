#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sqlite3 as lite
from suds.client import Client

lineas_totales = 2
posicion_tabla = 0
correccion = 0
file = open("lineas_db.c", "w")
file.write("#include \"lineas_db.h\"\n\n")

file.write("char *array_lineasxparada[] = {\n")
file.write("\"Sin datos\",\n")

con = lite.connect('datos.db')
with con:
    cur = con.cursor()
    cur.execute("SELECT * FROM parada")
    rows = cur.fetchall()
    for row in rows:
        posicion_tabla = posicion_tabla + 1
        cadena = row[4].upper()
        cadena2 = row[0]
        if (posicion_tabla+correccion != cadena2):
            file.write("\"Sin datos\",\n")
            correccion = correccion+1
            lineas_totales = lineas_totales + 1
        file.write("\"" + cadena.encode('utf8')+"\""+","+"\n")
        lineas_totales = lineas_totales+1

file.write("\"Sin datos\"\n};\n\nint total_paradas = "+ str(lineas_totales) + ";")
file = open("lineas_db.h", "w")
file.write("char *array_lineasxparada["+str(lineas_totales)+"];\nint total_paradas;")


print "Archivos generados"
