#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sqlite3 as lite

lineas_totales = 1
posicion_tabla = 0
correccion = 0
file = open("struct.bin", "wb")
file_index = open("struct.c", "w")


con = lite.connect('nuevadb.db')
with con:
    cur = con.cursor()
    cur.execute("SELECT * FROM parada")
    rows = cur.fetchall()
    for row in rows:
        posicion_tabla = posicion_tabla + 1
        c_parada = row[0]
        c_nombre = row[1][6:].title()
        c_lineas = row[4].upper()
        file.write(str(c_parada) + ('\0' * (4 - len(str(c_parada)))))
        file_index.write(str(c_parada)+',')
        file.write(c_nombre.encode('utf8') + ('\0' * (40 - len(c_nombre.encode('utf8')))))
        file.write(c_lineas.encode('utf8') + ('\0' * (11 - len(c_lineas.encode('utf8')))))
file_index.write("Total items: "+str(posicion_tabla))
file.close()
file_index.close()



print "Archivos generados"
