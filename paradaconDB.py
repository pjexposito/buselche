import sqlite3 as lite
from suds.client import Client

url = 'http://www.isae-auesa.com:82/services/dinamica.asmx?wsdl'
client = Client(url)
linea = 'K'
parada = '177'
lineas_totales = 2
file = open("busdb.c", "w")
file.write("#include \"busdb.h\"\n\n")

file.write("char *array_nombre_parada[] = {\n")
file.write("\"Sin datos\",\n")

con = lite.connect('datos.db')
with con:
    
    cur = con.cursor()
    # Se seleccionan dos tablas (calendar y shifts), se unen y se ordenan por fecha
    cur.execute("SELECT * FROM parada")
    rows = cur.fetchall()
    for row in rows:
        cadena = row[1][6:].title()
        file.write("\""+ cadena.encode('utf8')+"\""+","+"\n")
        lineas_totales = lineas_totales+1
        #print parada, " ", row[0]
        if parada == str(row[0]):
            nombre = row[1][6:].title()
            # Como el valor incluye el numero de parada, yo se lo quito
            # El title del final hace que la direccion, que es todo mayusculas, se convierta en minusculas salvo la
            # primera letra de cada palabra
        
print nombre
file.write("\"Sin datos\"\n};\n")
file = open("busdb.h", "w")
file.write("char *array_nombre_parada["+str(lineas_totales)+"];")



tiempo1 = client.service.GetPasoParada(linea,parada,0).GetPasoParadaResult.PasoParada[0].e1.minutos
tiempo2 = client.service.GetPasoParada(linea,parada,0).GetPasoParadaResult.PasoParada[0].e2.minutos
print "Faltan", tiempo1, "y", tiempo2, "minutos para que pase la linea", linea, "por la parada", parada, "(" + nombre + ")"
