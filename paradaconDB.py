import sqlite3 as lite

lineas_totales = 2
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
        cadena = row[1][6:].title()
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
