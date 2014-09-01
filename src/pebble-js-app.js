/*
VALORES QUE BUSCO
http://www.auesa.es/paradas_qr/1.php?vari=A
{"GetPasoParadaResult":{"PasoParada":{"cabecera":"true","e1":{"minutos":"6","metros":"1054","tipo":"NORMAL"},"e2":{"minutos":"18","metros":"3401","tipo":"NORMAL"},"linea":"A","parada":"1","ruta":"POL.IND.CARRUS"}},"status":"1"}


{
"GetPasoParadaResult":
   {"PasoParada":
       {"cabecera":"true","e1":
          {"minutos":"6","metros":"1054","tipo":"NORMAL"},"e2":
          {"minutos":"18","metros":"3401","tipo":"NORMAL"},"linea":"A","parada":"1","ruta":"POL.IND.CARRUS"
        }
    },
  "status":"1"
  }


*/

var dict;
var t1 , t2;



function HTTPGET(url) {
	var req = new XMLHttpRequest();
  req.open("GET", url, false);
	req.send(null);
  if (req.status == "404") 
    {
    console.log("ME HA DADO ERROR 404");
    return 1;
  
    }
  else
    {
    console.log("LA URL EXISTE. NO HAY ERROR");
    return req.responseText;
    }
}

function BuscaParadas(parada,linea) {
  console.log("URL: http://www.auesa.es/paradas_qr/"+parada+".php?vari="+linea);

    var response = HTTPGET("http://www.auesa.es/paradas_qr/"+parada+".php?vari="+linea);
  
    // CODIGOS DE ERROR
    // 97 = Error 404. La web no existe. Posiblemente por que la parada seleccionada no existe.
    // 98 = Existe la línea y la parada pero no hay datos (posiblemente no circulen autobueses a esas horas.
    // 99 = No pasa esa linea por la parada seleccionada.
    if (response==1)
      {
        console.log("Como no existe la web mando codigo 97");
        t1 = "97";
        t2 = "97";
      }
    else
      {
       var json = JSON.parse(response);
       if (json.GetPasoParadaResult)
         console.log("Existe el item JSON");
       else
         console.log("No existe JSON");   
       //Convierte la respuesta de la web de Google en JSON, para parsearla
       if (json.status==1) 
       {
         if (json.GetPasoParadaResult)
         {
           t1 = json.GetPasoParadaResult.PasoParada.e1.minutos;
           t2 = json.GetPasoParadaResult.PasoParada.e2.minutos;
           console.log("Hay datos");
         }
         else
         {
           t1 = "98";
           t2 = "98";
           console.log("Existe la línea y la parada pero no hay datos (posiblemente no circulen autobueses a esas horas.");   
         } 
       }
       else
       {
         console.log("Esa linea no pasa por esa parada"); 
         t1 = "99";
         t2 = "99";
       } 
      }
	
	//Mando a la consola los datos que he obtenido
  console.log("Tiempo:" + t1 + ", " + t2);
	
	//Este es el diccionario con los datos que voy a mandar al reloj
  dict = {"KEY_T1" : t1, "KEY_T2": t2};

	//Mando los datos de dirección al reloj
	Pebble.sendAppMessage(dict);
}



Pebble.addEventListener("ready",
  function(e) {
	//Se activa el reloj por primera vez. Se piden los datos por primera vez
  console.log("Evento Ready");

  }
);



Pebble.addEventListener("appmessage",
  function(e) {
    //Se refresca la información
    console.log("Mensaje recibido:" + e.payload.KEY_T1 + " " + e.payload.KEY_T2);

  var parada=e.payload.KEY_T1;
  var linea=e.payload.KEY_T2;
  BuscaParadas(parada,linea);
  }
);