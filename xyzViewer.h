unsigned int stringHash(void *string)
{
	/* This is the djb2 string hash function */

	unsigned int result = 995381;
	unsigned char *p;

	p = (unsigned char *) string;

	while (*p != '\0') {
		result = (result << 2) + result + *p;
		++p;
	}

	return result;
}

void stringToColorHex(char *str, char *hex)
{
    int hash, i;
    hash = stringHash(str);
    sprintf(hex,"000000");
    sprintf(hex,"%x",hash % 16777215);
    strncpy(hex, hex, 6);
}

void xyzViewer(char xyzName[],char htmlName[]){
	//char filename[40],dataname[40];
	//scanf()
	FILE *f, *data;
    char buffer[30];
    char hexColor[6];
    int atoms,i;
    float maxXRange=0.,maxYRange=0.,maxZRange=0.,minXRange=0.,minYRange=0.,minZRange=0.,centreX,centreY,centreZ,maxRange;
	f = fopen(htmlName,"w+");
	char HTMLBefore[] = "<!DOCTYPE html>\n"
"<html>\n"
"<title>XYZ Viewer</title>\n"
"<body>\n"
"   <div id=\"myDiv\" style='width:95%;margin:auto'></div>\n"
"   <div align=center>\n"
"       <button onClick=\"Play()\" id=\"PlayBtn\">Play</button>	\n"
"       <input type=\"text\" id=\"Frame\" style=\"width:100px;margin-left:5px;text-align:center\" placeholder=\"Frame\" />\n"
"       <input type=\"text\" id=\"Speed\" style=\"width:100px;margin-left:5px;text-align:center\" placeholder=\"Duration\" />(larger is slower)<br />\n"
"       Particle Size:<input type=\"text\" id=\"Size\" style=\"width:45px;margin-left:5px;text-align:center\" value=3 /><br /><br />\n"
"   </div>\n\n";

char JScript[] = "<script src=\"https://cdn.plot.ly/plotly-1.1.0.min.js\"></script>";

char HTMLAfter[] = "var numberOfFrame = Data.length;\n"
"var Atom = Data[0].length;\n"
"var x=[];\n"
"var y=[];\n"
"var z=[];\n"
"var color=[];\n"
"var names=[];\n"
"var Size = document.getElementById(\'Size\');\n\n"
"for(var i=0;i<Atom;i++){\n"
"	x.push(Data[0][i].coord[0]);\n"
"	y.push(Data[0][i].coord[1]);\n"
"	z.push(Data[0][i].coord[2]);\n"
"	color.push(Data[0][i].color);\n"
"	names.push(Data[0][i].name);\n"
"}\n\n"
"Plotly.plot(\'myDiv\',[{\n"
"  x: x,\n"
"  y: y,\n"
"  z: z,\n"
"  text: names,\n"
"  mode: \'markers\',\n"
"  type: \'scatter3d\',\n"
"  marker: {\n"
"    color: color,\n"
"    size: Size.value,\n"
"	 line:{color: 'rgb(231, 99, 250)',\n"
"      width: 1}\n"
"   },\n"
"  }],{height:500,\n"
"   dragmode:\"orbit\","
"   scene:{\n"
"	aspectmode: \"manual\",\n"
"   aspectratio: {\n"
"     x: 1, y: 1, z: 1,\n"
"    },\n"
"   xaxis: {\n"
"    range: [minXRange*1.05, maxXRange*1.05],\n"
"  },\n"
"   yaxis: {\n"
"    range: [minYRange*1.05, maxYRange*1.05],\n"
"  },\n"
"   zaxis: {\n"
"   range: [minZRange*1.05, maxZRange*1.05],\n"
"  }},\n"
"  })\n\n"
"var PlayBtn = document.getElementById(\'PlayBtn\');\n"
"var Speed = document.getElementById(\'Speed\');\n"
"var Frame = document.getElementById(\'Frame\');\n\n"
"function Play(){\n"
"	if(PlayBtn.innerHTML!=\"Stop\"){\n"
"		if(Speed.value==\"\")\n"
"          { Speed.value=10; }\n"
"		if(Frame.value==\"\")\n"
"          { Frame.value=0; }\n"
"       if(PlayBtn.innerHTML==\"Replay\")"
"          { Frame.value=0; }\n"
"		Playing = setInterval(function(){\n"
"		    if(Frame.value>=numberOfFrame-1 && PlayBtn.innerHTML!=\'Play\'){\n"
"		        PlayBtn.innerHTML=\"Replay\";\n"
"               Frame.value=numberOfFrame-1;\n"
"		        window.clearInterval(Playing);\n"
"		        return;\n"
"		    }\n"
"		    Update();\n"
"		}, Speed.value);\n"
"		PlayBtn.innerHTML=\"Stop\";\n"
"	}\n"
"	else{\n"
"		PlayBtn.innerHTML=\"Play\";\n"
"		window.clearInterval(Playing);\n"
"	}\n"
"}\n\n"
"function Update(){\n"
"   var n = parseInt(Frame.value);\n"
"	x=[];\n"
"	y=[];\n"
"	z=[];\n"
"	color=[];\n"
"	names=[];\n"
"	for(var i=0;i<Atom;i++){\n"
"		x.push(Data[n][i].coord[0]);\n"
"		y.push(Data[n][i].coord[1]);\n"
"		z.push(Data[n][i].coord[2]);\n"
"		color.push(Data[n][i].color);\n"
"		names.push(Data[n][i].name);\n"
"	}\n"
"    Plotly.restyle(\'myDiv\', {\n"
"    x: [x],\n"
"    y: [y],\n"
"    z: [z],\n"
"    text: names,\n"
"    marker: {\n"
"       color: color,\n"
"       size: Size.value,\n"
"	    line:{color: 'rgb(231, 99, 250)',\n"
"           width: 1}\n"
"       },\n"
"    });\n"
"   Frame.value=n+1;\n"
"}\n"
"Frame.addEventListener('change', function (e) {\n"
"	if(Playing) window.clearInterval(Playing);\n"
"	PlayBtn.innerHTML=\"Play\";\n"
"   Update();\n"
"	Frame.value-=1;\n"
"});\n"
"Frame.addEventListener('keypress', function (e) {\n"
"    if (e.key === 'Enter') {\n"
"      Play();\n"
"    }\n"
"});\n"
"Speed.addEventListener('keypress', function (e) {\n"
"    if (e.key === 'Enter') {\n"
"      Play();\n"
"    }\n"
"});\n"
"Size.addEventListener('keypress', function (e) {\n"
"    if (e.key === 'Enter') {\n"
"      Update();\n"
"    }\n"
"});\n"
"document.onkeydown = function (e) {\n"
"    if (e.key === 'Escape') {\n"
"       event.preventDefault(); "
"	    if(Playing) window.clearInterval(Playing);\n"
"	    PlayBtn.innerHTML=\"Play\";\n"
"    }\n"
"};\n"
"</script>\n"
"</body>\n"
"</html>";
data = fopen(xyzName,"r");
 if (NULL == data)
    {
         perror("File Not Exist!");
    }
  
fprintf(f,"%s",HTMLBefore);
fprintf(f,"%s\n",JScript);
fprintf(f,"<script>var Data = [\n");
while (1)
    {
    	if(EOF==fscanf(data, "%s", buffer)) break;
        fprintf(f,"  [\n");
        atoms = atoi(buffer);
    	if(EOF==fscanf(data, "%*s%[^\n]", buffer)) break;
        for(i=1;i<=atoms;i++){
    	if(EOF==fscanf(data, "%s", buffer)) break;
        fprintf(f,"    {name: \"%s\", ", buffer);
        stringToColorHex(buffer,hexColor);
        fprintf(f,"color : \"#%s\", ", hexColor);
    	if(EOF==fscanf(data, "%s", buffer)) break;
        fprintf(f," coord : [ %s, ", buffer);
        if((atof(buffer))>maxXRange)maxXRange=(atof(buffer));        
        if((atof(buffer))<minXRange)minXRange=(atof(buffer));
    	if(EOF==fscanf(data, "%s", buffer)) break;
        fprintf(f,"%s, ", buffer);
        if((atof(buffer))>maxYRange)maxYRange=(atof(buffer));
        if((atof(buffer))<minYRange)minYRange=(atof(buffer));
    	if(EOF==fscanf(data, "%s", buffer)) break;
        fprintf(f,"%s ]}, \n", buffer);
        //if(i!=atoms)fprintf(f,", ");
        if((atof(buffer))>maxZRange)maxZRange=(atof(buffer));
        if((atof(buffer))<minZRange)minZRange=(atof(buffer));
        }
        fprintf(f,"  ],\n");
    }
maxRange = fmax(fmax(maxXRange-minXRange,maxYRange-minYRange),maxZRange-minZRange);
centreX = 0.5*(maxXRange+minXRange);
centreY = 0.5*(maxYRange+minYRange);
centreZ = 0.5*(maxZRange+minZRange);
maxXRange = 0.5*maxRange+centreX;
minXRange = -0.5*maxRange+centreX;
maxYRange = 0.5*maxRange+centreY;
minYRange = -0.5*maxRange+centreY;
maxZRange = 0.5*maxRange+centreZ;
minZRange = -0.5*maxRange+centreZ;
fprintf(f,"];\nvar maxXRange=%f, maxYRange=%f,\n    maxZRange=%f, minXRange=%f,\n    minYRange=%f, minZRange=%f;\n",maxXRange,maxYRange,maxZRange,minXRange,minYRange,minZRange);
fprintf(f,"%s",HTMLAfter);
} 