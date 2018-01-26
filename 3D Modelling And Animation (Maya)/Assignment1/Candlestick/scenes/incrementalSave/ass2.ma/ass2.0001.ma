//Maya ASCII 2017ff05 scene
//Name: ass2.ma
//Last modified: Wed, Oct 11, 2017 11:40:49 PM
//Codeset: 1252
requires maya "2017ff05";
requires -nodeType "mentalrayFramebuffer" -nodeType "mentalrayOptions" -nodeType "mentalrayGlobals"
		 -nodeType "mentalrayItemsList" -dataType "byteArray" "Mayatomr" "2017.13  (3.14.5.1 - 268000.29819) ";
requires "stereoCamera" "10.0";
currentUnit -l centimeter -a degree -t film;
fileInfo "application" "maya";
fileInfo "product" "Maya 2017";
fileInfo "version" "2017";
fileInfo "cutIdentifier" "201706020738-1017329";
fileInfo "osv" "Microsoft Windows 8 Home Premium Edition, 64-bit  (Build 9200)\n";
fileInfo "license" "student";
createNode transform -s -n "persp";
	rename -uid "C368DF34-4E1A-03F6-61CE-68883AEBD7EE";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 18.48458649098912 12.883310175260792 4.8288225470474613 ;
	setAttr ".r" -type "double3" -32.738352729586232 75.799999999836729 -1.2965588745049421e-014 ;
createNode camera -s -n "perspShape" -p "persp";
	rename -uid "9129AE21-4C84-6F6B-0DF8-9FAD116793AE";
	setAttr -k off ".v" no;
	setAttr ".fl" 34.999999999999993;
	setAttr ".coi" 23.61198471280689;
	setAttr ".imn" -type "string" "persp";
	setAttr ".den" -type "string" "persp_depth";
	setAttr ".man" -type "string" "persp_mask";
	setAttr ".tp" -type "double3" 0 -3.2160442211504829 0.40729961400257508 ;
	setAttr ".hc" -type "string" "viewSet -p %camera";
	setAttr ".ai_translator" -type "string" "perspective";
createNode transform -s -n "top";
	rename -uid "682DA5F7-4B40-BFD5-5234-889ABDE7C480";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 1000.1 0 ;
	setAttr ".r" -type "double3" -89.999999999999986 0 0 ;
createNode camera -s -n "topShape" -p "top";
	rename -uid "BDD38557-4884-64D1-40EF-76969FFA22C6";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 1000.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "top";
	setAttr ".den" -type "string" "top_depth";
	setAttr ".man" -type "string" "top_mask";
	setAttr ".hc" -type "string" "viewSet -t %camera";
	setAttr ".o" yes;
	setAttr ".ai_translator" -type "string" "orthographic";
createNode transform -s -n "front";
	rename -uid "DD92F5EE-4229-11C0-3E61-BA931D0EE39A";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 0 1000.1 ;
createNode camera -s -n "frontShape" -p "front";
	rename -uid "B89DB6BB-4BAD-6EA4-B12D-2DB1A377185B";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 1000.1;
	setAttr ".ow" 24.980388658601804;
	setAttr ".imn" -type "string" "front";
	setAttr ".den" -type "string" "front_depth";
	setAttr ".man" -type "string" "front_mask";
	setAttr ".hc" -type "string" "viewSet -f %camera";
	setAttr ".o" yes;
	setAttr ".ai_translator" -type "string" "orthographic";
createNode transform -s -n "side";
	rename -uid "D68970AE-422B-C363-C37C-ECA22227DE66";
	setAttr ".t" -type "double3" 1000.1 2.0485099463374619 -0.50991544667904687 ;
	setAttr ".r" -type "double3" 0 89.999999999999986 0 ;
createNode camera -s -n "sideShape" -p "side";
	rename -uid "611250B5-4EA0-F9CD-B274-B986DBBB96BE";
	setAttr -k off ".v";
	setAttr ".rnd" no;
	setAttr ".coi" 1000.1;
	setAttr ".ow" 17.590854980794806;
	setAttr ".imn" -type "string" "side";
	setAttr ".den" -type "string" "side_depth";
	setAttr ".man" -type "string" "side_mask";
	setAttr ".hc" -type "string" "viewSet -s %camera";
	setAttr ".o" yes;
	setAttr ".ai_translator" -type "string" "orthographic";
createNode transform -n "imagePlane1";
	rename -uid "FC5CF451-4E35-36A1-0D5E-2BBA6283E802";
	setAttr ".t" -type "double3" -7.9339359721688352 2.1695967445348296 0 ;
	setAttr ".r" -type "double3" 0 89.999999999999986 0 ;
	setAttr ".s" -type "double3" 2.7474157690726067 2.7474157690726067 2.7474157690726067 ;
createNode imagePlane -n "imagePlaneShape1" -p "imagePlane1";
	rename -uid "DF269C5F-42FE-BFCD-A143-B291FB931CED";
	setAttr -k off ".v";
	setAttr ".fc" 50;
	setAttr ".imn" -type "string" "D:/Uni Stuff/3.3/236 3D Modelling and Animation/Assn/Assignment2/right.jpg";
	setAttr ".cov" -type "short2" 405 873 ;
	setAttr ".dlc" no;
	setAttr ".w" 4.05;
	setAttr ".h" 8.7299999999999986;
	setAttr ".cs" -type "string" "sRGB";
createNode transform -n "pCube1";
	rename -uid "37153E5A-4298-B1F8-8524-0190D8A3ED84";
	setAttr ".t" -type "double3" 0 0.27153307600172338 0.40729961400257508 ;
	setAttr ".s" -type "double3" 8.5089523870505985 17.437886225916277 7.7526010636644758 ;
createNode mesh -n "pCubeShape1" -p "pCube1";
	rename -uid "2273B9BE-4682-89B5-726D-6C88C664AA9B";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".pv" -type "double2" 0.5 1.5000001192092896 ;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr ".dr" 3;
	setAttr ".dsm" 2;
	setAttr ".ai_translator" -type "string" "polymesh";
createNode lightLinker -s -n "lightLinker1";
	rename -uid "BD66507E-47E9-7982-0896-A3851E4AC0A3";
	setAttr -s 2 ".lnk";
	setAttr -s 2 ".slnk";
createNode shapeEditorManager -n "shapeEditorManager";
	rename -uid "220E684D-4066-8A3F-029F-488C83F054C7";
createNode poseInterpolatorManager -n "poseInterpolatorManager";
	rename -uid "A9A0B87B-4B7F-9FAF-4336-DE974C48A5B2";
createNode displayLayerManager -n "layerManager";
	rename -uid "A33DBAC3-4D1B-75FE-B76E-FC95DE4AE001";
createNode displayLayer -n "defaultLayer";
	rename -uid "F382FFD7-4983-6E07-BEFC-15B2E9F1E99C";
createNode renderLayerManager -n "renderLayerManager";
	rename -uid "053920BF-49A9-3A04-1CDF-ADB3171D55AC";
createNode renderLayer -n "defaultRenderLayer";
	rename -uid "10AA85ED-4193-D495-24D4-D3A0FD3FD1E3";
	setAttr ".g" yes;
createNode mentalrayItemsList -s -n "mentalrayItemsList";
	rename -uid "8040C1B6-4106-3F28-A7F0-C99926B313F8";
createNode mentalrayGlobals -s -n "mentalrayGlobals";
	rename -uid "3847B764-477C-8A27-9AE1-FCAB8210BDA5";
createNode mentalrayOptions -s -n "miDefaultOptions";
	rename -uid "44E363D6-4438-3975-D012-929F83369AEB";
	setAttr ".miSamplesMax" 50;
createNode mentalrayFramebuffer -s -n "miDefaultFramebuffer";
	rename -uid "F83FD8C4-4C32-C50E-3707-3DB48BEB3A4B";
createNode polyCube -n "polyCube1";
	rename -uid "00808E4C-4374-D3CC-042B-CD89BDA64584";
	setAttr ".sw" 10;
	setAttr ".sh" 10;
	setAttr ".sd" 10;
	setAttr ".cuv" 1;
createNode polyTweak -n "polyTweak1";
	rename -uid "24B09029-4ED3-4C1A-8F08-E4858C2F37E8";
	setAttr ".uopa" yes;
	setAttr -s 321 ".tk";
	setAttr ".tk[0]" -type "float3" 0 0 0.054567806 ;
	setAttr ".tk[1]" -type "float3" 0 0 0.054567806 ;
	setAttr ".tk[2]" -type "float3" 0 0 0.054567806 ;
	setAttr ".tk[3]" -type "float3" 0 0 0.054567806 ;
	setAttr ".tk[4]" -type "float3" 0 0 0.054567806 ;
	setAttr ".tk[5]" -type "float3" 0 0 0.054567806 ;
	setAttr ".tk[6]" -type "float3" 0 0 0.054567806 ;
	setAttr ".tk[7]" -type "float3" 0 0 0.054567806 ;
	setAttr ".tk[8]" -type "float3" 0 0 0.054567806 ;
	setAttr ".tk[9]" -type "float3" 0 0 0.054567806 ;
	setAttr ".tk[10]" -type "float3" 0 -3.4414319e-005 0.07038115 ;
	setAttr ".tk[11]" -type "float3" 0 0 0.044444442 ;
	setAttr ".tk[12]" -type "float3" 0 0 0.044444442 ;
	setAttr ".tk[13]" -type "float3" 0 0 0.044444442 ;
	setAttr ".tk[14]" -type "float3" 0 0 0.044444442 ;
	setAttr ".tk[15]" -type "float3" 0 0 0.044444442 ;
	setAttr ".tk[16]" -type "float3" 0 0 0.044444442 ;
	setAttr ".tk[17]" -type "float3" 0 0 0.044444442 ;
	setAttr ".tk[18]" -type "float3" 0 0 0.044444442 ;
	setAttr ".tk[19]" -type "float3" 0 0 0.044444442 ;
	setAttr ".tk[20]" -type "float3" 0 0 0.044444442 ;
	setAttr ".tk[21]" -type "float3" 0 0 0.044444442 ;
	setAttr ".tk[22]" -type "float3" 0 0.092158042 0.044444442 ;
	setAttr ".tk[23]" -type "float3" 0 0.092158042 0.044444442 ;
	setAttr ".tk[24]" -type "float3" 0 0.092158042 0.044444442 ;
	setAttr ".tk[25]" -type "float3" 0 0.092158042 0.044444442 ;
	setAttr ".tk[26]" -type "float3" 0 0.092158042 0.044444442 ;
	setAttr ".tk[27]" -type "float3" 0 0.092158042 0.044444442 ;
	setAttr ".tk[28]" -type "float3" 0 0.092158042 0.044444442 ;
	setAttr ".tk[29]" -type "float3" 0 0.092158042 0.044444442 ;
	setAttr ".tk[30]" -type "float3" 0 0.092158042 0.044444442 ;
	setAttr ".tk[31]" -type "float3" 0 0.092158042 0.044444442 ;
	setAttr ".tk[32]" -type "float3" 0 0.092158042 0.044444442 ;
	setAttr ".tk[33]" -type "float3" 0 0.089732781 0.044444442 ;
	setAttr ".tk[34]" -type "float3" 0 0.089732781 0.044444442 ;
	setAttr ".tk[35]" -type "float3" 0 0.089732781 0.044444442 ;
	setAttr ".tk[36]" -type "float3" 0 0.089732781 0.044444442 ;
	setAttr ".tk[37]" -type "float3" 0 0.089732781 0.044444442 ;
	setAttr ".tk[38]" -type "float3" 0 0.089732781 0.044444442 ;
	setAttr ".tk[39]" -type "float3" 0 0.089732781 0.044444442 ;
	setAttr ".tk[40]" -type "float3" 0 0.089732781 0.044444442 ;
	setAttr ".tk[41]" -type "float3" 0 0.089732781 0.044444442 ;
	setAttr ".tk[42]" -type "float3" 0 0.089732781 0.044444442 ;
	setAttr ".tk[43]" -type "float3" 0 0.089732781 0.044444442 ;
	setAttr ".tk[44]" -type "float3" 0 -2.7939677e-009 0.03585976 ;
	setAttr ".tk[45]" -type "float3" 0 -2.7939677e-009 0.03585976 ;
	setAttr ".tk[46]" -type "float3" 0 -2.7939677e-009 0.03585976 ;
	setAttr ".tk[47]" -type "float3" 0 -2.7939677e-009 0.03585976 ;
	setAttr ".tk[48]" -type "float3" 0 -2.7939677e-009 0.03585976 ;
	setAttr ".tk[49]" -type "float3" 0 -2.7939677e-009 0.03585976 ;
	setAttr ".tk[50]" -type "float3" 0 -2.7939677e-009 0.03585976 ;
	setAttr ".tk[51]" -type "float3" 0 -2.7939677e-009 0.03585976 ;
	setAttr ".tk[52]" -type "float3" 0 -2.7939677e-009 0.03585976 ;
	setAttr ".tk[53]" -type "float3" 0 -2.7939677e-009 0.03585976 ;
	setAttr ".tk[54]" -type "float3" 0 -2.7939677e-009 0.03585976 ;
	setAttr ".tk[55]" -type "float3" 0 -0.048504192 0.019092552 ;
	setAttr ".tk[56]" -type "float3" 0 -0.048504192 0.019092552 ;
	setAttr ".tk[57]" -type "float3" 0 -0.048504192 0.019092552 ;
	setAttr ".tk[58]" -type "float3" 0 -0.048504192 0.019092552 ;
	setAttr ".tk[59]" -type "float3" 0 -0.048504192 0.019092552 ;
	setAttr ".tk[60]" -type "float3" 0 -0.048504192 0.019092552 ;
	setAttr ".tk[61]" -type "float3" 0 -0.048504192 0.019092552 ;
	setAttr ".tk[62]" -type "float3" 0 -0.048504192 0.019092552 ;
	setAttr ".tk[63]" -type "float3" 0 -0.048504192 0.019092552 ;
	setAttr ".tk[64]" -type "float3" 0 -0.048504192 0.019092552 ;
	setAttr ".tk[65]" -type "float3" 0 -0.048504192 0.019092552 ;
	setAttr ".tk[275]" -type "float3" 0 -0.048504192 0.019092554 ;
	setAttr ".tk[276]" -type "float3" 0 -0.048504192 0.019092554 ;
	setAttr ".tk[277]" -type "float3" 0 -0.048504192 0.019092554 ;
	setAttr ".tk[278]" -type "float3" 0 -0.048504192 0.019092554 ;
	setAttr ".tk[279]" -type "float3" 0 -0.048504192 0.019092554 ;
	setAttr ".tk[280]" -type "float3" 0 -0.048504192 0.019092554 ;
	setAttr ".tk[281]" -type "float3" 0 -0.048504192 0.019092554 ;
	setAttr ".tk[282]" -type "float3" 0 -0.048504192 0.019092554 ;
	setAttr ".tk[283]" -type "float3" 0 -0.048504192 0.019092554 ;
	setAttr ".tk[284]" -type "float3" 0 -0.048504192 0.019092554 ;
	setAttr ".tk[285]" -type "float3" 0 -0.048504192 0.019092554 ;
	setAttr ".tk[286]" -type "float3" 0 -2.7939677e-009 -0.0085846838 ;
	setAttr ".tk[287]" -type "float3" 0 -2.7939677e-009 -0.0085846838 ;
	setAttr ".tk[288]" -type "float3" 0 -2.7939677e-009 -0.0085846838 ;
	setAttr ".tk[289]" -type "float3" 0 -2.7939677e-009 -0.0085846838 ;
	setAttr ".tk[290]" -type "float3" 0 -2.7939677e-009 -0.0085846838 ;
	setAttr ".tk[291]" -type "float3" 0 -2.7939677e-009 -0.0085846838 ;
	setAttr ".tk[292]" -type "float3" 0 -2.7939677e-009 -0.0085846838 ;
	setAttr ".tk[293]" -type "float3" 0 -2.7939677e-009 -0.0085846838 ;
	setAttr ".tk[294]" -type "float3" 0 -2.7939677e-009 -0.0085846838 ;
	setAttr ".tk[295]" -type "float3" 0 -2.7939677e-009 -0.0085846838 ;
	setAttr ".tk[296]" -type "float3" 0 -2.7939677e-009 -0.0085846838 ;
	setAttr ".tk[297]" -type "float3" 0 0.089732781 -0.044444442 ;
	setAttr ".tk[298]" -type "float3" 0 0.089732781 -0.044444442 ;
	setAttr ".tk[299]" -type "float3" 0 0.089732781 -0.044444442 ;
	setAttr ".tk[300]" -type "float3" 0 0.089732781 -0.044444442 ;
	setAttr ".tk[301]" -type "float3" 0 0.089732781 -0.044444442 ;
	setAttr ".tk[302]" -type "float3" 0 0.089732781 -0.044444442 ;
	setAttr ".tk[303]" -type "float3" 0 0.089732781 -0.044444442 ;
	setAttr ".tk[304]" -type "float3" 0 0.089732781 -0.044444442 ;
	setAttr ".tk[305]" -type "float3" 0 0.089732781 -0.044444442 ;
	setAttr ".tk[306]" -type "float3" 0 0.089732781 -0.044444442 ;
	setAttr ".tk[307]" -type "float3" 0 0.089732781 -0.044444442 ;
	setAttr ".tk[308]" -type "float3" 0 0.092158042 -0.044444442 ;
	setAttr ".tk[309]" -type "float3" 0 0.092158042 -0.044444442 ;
	setAttr ".tk[310]" -type "float3" 0 0.092158042 -0.044444442 ;
	setAttr ".tk[311]" -type "float3" 0 0.092158042 -0.044444442 ;
	setAttr ".tk[312]" -type "float3" 0 0.092158042 -0.044444442 ;
	setAttr ".tk[313]" -type "float3" 0 0.092158042 -0.044444442 ;
	setAttr ".tk[314]" -type "float3" 0 0.092158042 -0.044444442 ;
	setAttr ".tk[315]" -type "float3" 0 0.092158042 -0.044444442 ;
	setAttr ".tk[316]" -type "float3" 0 0.092158042 -0.044444442 ;
	setAttr ".tk[317]" -type "float3" 0 0.092158042 -0.044444442 ;
	setAttr ".tk[318]" -type "float3" 0 0.092158042 -0.044444442 ;
	setAttr ".tk[319]" -type "float3" 0 0 -0.044444442 ;
	setAttr ".tk[320]" -type "float3" 0 0 -0.044444442 ;
	setAttr ".tk[321]" -type "float3" 0 0 -0.044444442 ;
	setAttr ".tk[322]" -type "float3" 0 0 -0.044444442 ;
	setAttr ".tk[323]" -type "float3" 0 0 -0.044444442 ;
	setAttr ".tk[324]" -type "float3" 0 0 -0.044444442 ;
	setAttr ".tk[325]" -type "float3" 0 0 -0.044444442 ;
	setAttr ".tk[326]" -type "float3" 0 0 -0.044444442 ;
	setAttr ".tk[327]" -type "float3" 0 0 -0.044444442 ;
	setAttr ".tk[328]" -type "float3" 0 0 -0.044444442 ;
	setAttr ".tk[329]" -type "float3" 0 0 -0.044444442 ;
	setAttr ".tk[330]" -type "float3" 0 0 -0.022925382 ;
	setAttr ".tk[331]" -type "float3" 0 0 -0.022925382 ;
	setAttr ".tk[332]" -type "float3" 0 0 -0.022925382 ;
	setAttr ".tk[333]" -type "float3" 0 0 -0.022925382 ;
	setAttr ".tk[334]" -type "float3" 0 0 -0.022925382 ;
	setAttr ".tk[335]" -type "float3" 0 0 -0.022925382 ;
	setAttr ".tk[336]" -type "float3" 0 0 -0.022925382 ;
	setAttr ".tk[337]" -type "float3" 0 0 -0.022925382 ;
	setAttr ".tk[338]" -type "float3" 0 0 -0.022925382 ;
	setAttr ".tk[339]" -type "float3" 0 0 -0.022925382 ;
	setAttr ".tk[340]" -type "float3" 0 -3.4414319e-005 -0.038739074 ;
	setAttr ".tk[341]" -type "float3" 0 0 -0.018480934 ;
	setAttr ".tk[342]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[343]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[344]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[345]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[346]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[347]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[348]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[349]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[350]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[351]" -type "float3" 0 -3.4414319e-005 -0.031231496 ;
	setAttr ".tk[352]" -type "float3" 0 0 -0.014036489 ;
	setAttr ".tk[353]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[354]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[355]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[356]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[357]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[358]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[359]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[360]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[361]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[362]" -type "float3" 0 -3.4414319e-005 -0.023719624 ;
	setAttr ".tk[363]" -type "float3" 0 0 -0.0095920442 ;
	setAttr ".tk[364]" -type "float3" 0 -0.028100001 -0.028100001 ;
	setAttr ".tk[365]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[366]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[367]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[368]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[369]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[370]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[371]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[372]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[373]" -type "float3" 0 -3.4414319e-005 -0.01620825 ;
	setAttr ".tk[374]" -type "float3" 0 0 -0.0051476024 ;
	setAttr ".tk[375]" -type "float3" 0 -0.0281354 0 ;
	setAttr ".tk[376]" -type "float3" 0 -0.0281354 0 ;
	setAttr ".tk[377]" -type "float3" 0 -0.0281354 0 ;
	setAttr ".tk[378]" -type "float3" 0 -0.0281354 0 ;
	setAttr ".tk[379]" -type "float3" 0 -0.0281354 0 ;
	setAttr ".tk[380]" -type "float3" 0 -0.0281354 0 ;
	setAttr ".tk[381]" -type "float3" 0 -0.0281354 0 ;
	setAttr ".tk[382]" -type "float3" 0 -0.0281354 0 ;
	setAttr ".tk[383]" -type "float3" 0 -0.0281354 0 ;
	setAttr ".tk[384]" -type "float3" 0 -3.4414319e-005 -0.0086988043 ;
	setAttr ".tk[385]" -type "float3" 0 0 -0.00070315792 ;
	setAttr ".tk[386]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[387]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[388]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[389]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[390]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[391]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[392]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[393]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[394]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[395]" -type "float3" 0 -3.4414319e-005 -0.0011881341 ;
	setAttr ".tk[396]" -type "float3" 0 0 0.003741286 ;
	setAttr ".tk[397]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[398]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[399]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[400]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[401]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[402]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[403]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[404]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[405]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[406]" -type "float3" 0 -3.4414319e-005 0.0063224672 ;
	setAttr ".tk[407]" -type "float3" 0 7.4505806e-009 0.0081857303 ;
	setAttr ".tk[408]" -type "float3" 0 -0.028135395 0 ;
	setAttr ".tk[409]" -type "float3" 0 -0.028135395 0 ;
	setAttr ".tk[410]" -type "float3" 0 -0.028135395 0 ;
	setAttr ".tk[411]" -type "float3" 0 -0.028135395 0 ;
	setAttr ".tk[412]" -type "float3" 0 -0.028135395 0 ;
	setAttr ".tk[413]" -type "float3" 0 -0.028135395 0 ;
	setAttr ".tk[414]" -type "float3" 0 -0.028135395 0 ;
	setAttr ".tk[415]" -type "float3" 0 -0.028135395 0 ;
	setAttr ".tk[416]" -type "float3" 0 -0.028135395 0 ;
	setAttr ".tk[417]" -type "float3" 0 -3.4406869e-005 0.013833079 ;
	setAttr ".tk[418]" -type "float3" 0 -0.022273859 0.012630173 ;
	setAttr ".tk[419]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[420]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[421]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[422]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[423]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[424]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[425]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[426]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[427]" -type "float3" 0 -0.028100001 0 ;
	setAttr ".tk[428]" -type "float3" 0 -3.4418288e-005 0.021344017 ;
	setAttr ".tk[429]" -type "float3" 0 -0.028135411 0.017074618 ;
	setAttr ".tk[430]" -type "float3" 0 -0.028135415 0 ;
	setAttr ".tk[431]" -type "float3" 0 -0.028135415 0 ;
	setAttr ".tk[432]" -type "float3" 0 -0.028135415 0 ;
	setAttr ".tk[433]" -type "float3" 0 -0.028135415 0 ;
	setAttr ".tk[434]" -type "float3" 0 -0.028135415 0 ;
	setAttr ".tk[435]" -type "float3" 0 -0.028135415 0 ;
	setAttr ".tk[436]" -type "float3" 0 -0.028135415 0 ;
	setAttr ".tk[437]" -type "float3" 0 -0.028135415 0 ;
	setAttr ".tk[438]" -type "float3" 0 -0.028135415 0 ;
	setAttr ".tk[439]" -type "float3" 0 0.0023790211 0.028855516 ;
	setAttr ".tk[440]" -type "float3" 0 0 -0.035555549 ;
	setAttr ".tk[441]" -type "float3" 0 0 -0.026666667 ;
	setAttr ".tk[442]" -type "float3" 0 0 -0.017777778 ;
	setAttr ".tk[443]" -type "float3" 0 0 -0.008888891 ;
	setAttr ".tk[444]" -type "float3" 0 0 -1.3245476e-009 ;
	setAttr ".tk[445]" -type "float3" 0 0 0.0088888872 ;
	setAttr ".tk[446]" -type "float3" 0 0 0.017777774 ;
	setAttr ".tk[447]" -type "float3" 0 0 0.026666664 ;
	setAttr ".tk[448]" -type "float3" 0 0 0.035555549 ;
	setAttr ".tk[449]" -type "float3" 0 0.092158042 -0.035555549 ;
	setAttr ".tk[450]" -type "float3" 0 0.092158042 -0.026666667 ;
	setAttr ".tk[451]" -type "float3" 0 0.092158042 -0.017777778 ;
	setAttr ".tk[452]" -type "float3" 0 0.092158042 -0.008888891 ;
	setAttr ".tk[453]" -type "float3" 0 0.092158042 -1.3245476e-009 ;
	setAttr ".tk[454]" -type "float3" 0 0.092158042 0.0088888872 ;
	setAttr ".tk[455]" -type "float3" 0 0.092158042 0.017777774 ;
	setAttr ".tk[456]" -type "float3" 0 0.092158042 0.026666664 ;
	setAttr ".tk[457]" -type "float3" 0 0.092158042 0.035555549 ;
	setAttr ".tk[458]" -type "float3" 0 0.089732781 -0.035555553 ;
	setAttr ".tk[459]" -type "float3" 0 0.089732781 -0.026666665 ;
	setAttr ".tk[460]" -type "float3" 0 0.089732781 -0.017777778 ;
	setAttr ".tk[461]" -type "float3" 0 0.089732781 -0.00888889 ;
	setAttr ".tk[462]" -type "float3" 0 0.089732781 -1.3245476e-009 ;
	setAttr ".tk[463]" -type "float3" 0 0.089732781 0.0088888872 ;
	setAttr ".tk[464]" -type "float3" 0 0.089732781 0.017777776 ;
	setAttr ".tk[465]" -type "float3" 0 0.089732781 0.026666664 ;
	setAttr ".tk[466]" -type "float3" 0 0.089732781 0.035555553 ;
	setAttr ".tk[467]" -type "float3" 0 -2.7939677e-009 -0.0041402364 ;
	setAttr ".tk[468]" -type "float3" 0 -2.7939677e-009 0.00030420022 ;
	setAttr ".tk[469]" -type "float3" 0 -2.7939677e-009 0.0047486485 ;
	setAttr ".tk[470]" -type "float3" 0 -2.7939677e-009 0.0091930926 ;
	setAttr ".tk[471]" -type "float3" 0 -2.7939677e-009 0.013637539 ;
	setAttr ".tk[472]" -type "float3" 0 -2.7939677e-009 0.018081987 ;
	setAttr ".tk[473]" -type "float3" 0 -2.7939677e-009 0.022526432 ;
	setAttr ".tk[474]" -type "float3" 0 -2.7939677e-009 0.026970865 ;
	setAttr ".tk[475]" -type "float3" 0 -2.7939677e-009 0.031415313 ;
	setAttr ".tk[476]" -type "float3" 0 -0.048504192 0.019092556 ;
	setAttr ".tk[477]" -type "float3" 0 -0.048504192 0.019092556 ;
	setAttr ".tk[478]" -type "float3" 0 -0.048504192 0.019092552 ;
	setAttr ".tk[479]" -type "float3" 0 -0.048504192 0.019092554 ;
	setAttr ".tk[480]" -type "float3" 0 -0.048504192 0.019092558 ;
	setAttr ".tk[481]" -type "float3" 0 -0.048504192 0.019092552 ;
	setAttr ".tk[482]" -type "float3" 0 -0.048504192 0.019092556 ;
	setAttr ".tk[483]" -type "float3" 0 -0.048504192 0.019092556 ;
	setAttr ".tk[484]" -type "float3" 0 -0.048504192 0.019092556 ;
	setAttr ".tk[521]" -type "float3" 0 0 -0.035555549 ;
	setAttr ".tk[522]" -type "float3" 0 0 -0.026666667 ;
	setAttr ".tk[523]" -type "float3" 0 0 -0.017777778 ;
	setAttr ".tk[524]" -type "float3" 0 0 -0.008888891 ;
	setAttr ".tk[525]" -type "float3" 0 0 -1.3245476e-009 ;
	setAttr ".tk[526]" -type "float3" 0 0 0.0088888872 ;
	setAttr ".tk[527]" -type "float3" 0 7.4505806e-009 0.017777774 ;
	setAttr ".tk[528]" -type "float3" 0 0 0.026666664 ;
	setAttr ".tk[529]" -type "float3" 0 0 0.035555549 ;
	setAttr ".tk[530]" -type "float3" 0 0.092158042 -0.035555549 ;
	setAttr ".tk[531]" -type "float3" 0 0.092158042 -0.026666667 ;
	setAttr ".tk[532]" -type "float3" 0 0.092158042 -0.017777778 ;
	setAttr ".tk[533]" -type "float3" 0 0.092158042 -0.008888891 ;
	setAttr ".tk[534]" -type "float3" 0 0.092158042 -1.3245476e-009 ;
	setAttr ".tk[535]" -type "float3" 0 0.092158042 0.0088888872 ;
	setAttr ".tk[536]" -type "float3" 0 0.092158042 0.017777774 ;
	setAttr ".tk[537]" -type "float3" 0 0.092158042 0.026666664 ;
	setAttr ".tk[538]" -type "float3" 0 0.092158042 0.035555549 ;
	setAttr ".tk[539]" -type "float3" 0 0.089732781 -0.035555553 ;
	setAttr ".tk[540]" -type "float3" 0 0.089732781 -0.026666665 ;
	setAttr ".tk[541]" -type "float3" 0 0.089732781 -0.017777778 ;
	setAttr ".tk[542]" -type "float3" 0 0.089732781 -0.00888889 ;
	setAttr ".tk[543]" -type "float3" 0 0.089732781 -1.3245476e-009 ;
	setAttr ".tk[544]" -type "float3" 0 0.089732781 0.0088888872 ;
	setAttr ".tk[545]" -type "float3" 0 0.089732781 0.017777776 ;
	setAttr ".tk[546]" -type "float3" 0 0.089732781 0.026666664 ;
	setAttr ".tk[547]" -type "float3" 0 0.089732781 0.035555553 ;
	setAttr ".tk[548]" -type "float3" 0 -2.7939677e-009 -0.0041402364 ;
	setAttr ".tk[549]" -type "float3" 0 -2.7939677e-009 0.00030420022 ;
	setAttr ".tk[550]" -type "float3" 0 -2.7939677e-009 0.0047486485 ;
	setAttr ".tk[551]" -type "float3" 0 -2.7939677e-009 0.0091930926 ;
	setAttr ".tk[552]" -type "float3" 0 -2.7939677e-009 0.013637539 ;
	setAttr ".tk[553]" -type "float3" 0 -2.7939677e-009 0.018081987 ;
	setAttr ".tk[554]" -type "float3" 0 -2.7939677e-009 0.022526432 ;
	setAttr ".tk[555]" -type "float3" 0 -2.7939677e-009 0.026970865 ;
	setAttr ".tk[556]" -type "float3" 0 -2.7939677e-009 0.031415313 ;
	setAttr ".tk[557]" -type "float3" 0 -0.048504192 0.019092556 ;
	setAttr ".tk[558]" -type "float3" 0 -0.048504192 0.019092556 ;
	setAttr ".tk[559]" -type "float3" 0 -0.048504192 0.019092552 ;
	setAttr ".tk[560]" -type "float3" 0 -0.048504192 0.019092554 ;
	setAttr ".tk[561]" -type "float3" 0 -0.048504192 0.019092558 ;
	setAttr ".tk[562]" -type "float3" 0 -0.048504192 0.019092552 ;
	setAttr ".tk[563]" -type "float3" 0 -0.048504192 0.019092556 ;
	setAttr ".tk[564]" -type "float3" 0 -0.048504192 0.019092556 ;
	setAttr ".tk[565]" -type "float3" 0 -0.048504192 0.019092556 ;
createNode deleteComponent -n "deleteComponent1";
	rename -uid "5C7EFAF7-4AD6-FB76-56F2-D8A5D3A25235";
	setAttr ".dc" -type "componentList" 4 "vtx[55:65]" "vtx[275:285]" "vtx[476:484]" "vtx[557:565]";
createNode polyTweak -n "polyTweak2";
	rename -uid "BC476B38-43CA-C072-DFF0-64BC136EA062";
	setAttr ".uopa" yes;
	setAttr -s 200 ".tk";
	setAttr ".tk[55]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[56]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[57]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[58]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[59]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[60]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[61]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[62]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[63]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[64]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[65]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[66]" -type "float3" 0 -0.13702436 0.019092456 ;
	setAttr ".tk[67]" -type "float3" 0 -0.13702436 0.019092456 ;
	setAttr ".tk[68]" -type "float3" 0 -0.13702436 0.019092456 ;
	setAttr ".tk[69]" -type "float3" 0 -0.13702436 0.019092456 ;
	setAttr ".tk[70]" -type "float3" 0 -0.13702436 0.019092456 ;
	setAttr ".tk[71]" -type "float3" 0 -0.13702436 0.019092456 ;
	setAttr ".tk[72]" -type "float3" 0 -0.13702436 0.019092456 ;
	setAttr ".tk[73]" -type "float3" 0 -0.13702436 0.019092456 ;
	setAttr ".tk[74]" -type "float3" 0 -0.13702436 0.019092456 ;
	setAttr ".tk[75]" -type "float3" 0 -0.13702436 0.019092456 ;
	setAttr ".tk[76]" -type "float3" 0 -0.13702436 0.019092456 ;
	setAttr ".tk[77]" -type "float3" 0 -0.17825328 0.0054549989 ;
	setAttr ".tk[78]" -type "float3" 0 -0.17825328 0.0054549989 ;
	setAttr ".tk[79]" -type "float3" 0 -0.17825328 0.0054549989 ;
	setAttr ".tk[80]" -type "float3" 0 -0.17825328 0.0054549989 ;
	setAttr ".tk[81]" -type "float3" 0 -0.17825328 0.0054549989 ;
	setAttr ".tk[82]" -type "float3" 0 -0.17825328 0.0054549989 ;
	setAttr ".tk[83]" -type "float3" 0 -0.17825328 0.0054549989 ;
	setAttr ".tk[84]" -type "float3" 0 -0.17825328 0.0054549989 ;
	setAttr ".tk[85]" -type "float3" 0 -0.17825328 0.0054549989 ;
	setAttr ".tk[86]" -type "float3" 0 -0.17825328 0.0054549989 ;
	setAttr ".tk[87]" -type "float3" 0 -0.17825328 0.0054549989 ;
	setAttr ".tk[88]" -type "float3" 0 -0.25113812 -0.0058100042 ;
	setAttr ".tk[89]" -type "float3" 0 -0.25113812 -0.0058100042 ;
	setAttr ".tk[90]" -type "float3" 0 -0.25113812 -0.0058100042 ;
	setAttr ".tk[91]" -type "float3" 0 -0.25113812 -0.0058100042 ;
	setAttr ".tk[92]" -type "float3" 0 -0.25113812 -0.0058100042 ;
	setAttr ".tk[93]" -type "float3" 0 -0.25113812 -0.0058100042 ;
	setAttr ".tk[94]" -type "float3" 0 -0.25113812 -0.0058100042 ;
	setAttr ".tk[95]" -type "float3" 0 -0.25113812 -0.0058100042 ;
	setAttr ".tk[96]" -type "float3" 0 -0.25113812 -0.0058100042 ;
	setAttr ".tk[97]" -type "float3" 0 -0.25113812 -0.0058100042 ;
	setAttr ".tk[98]" -type "float3" 0 -0.25113812 -0.0058100042 ;
	setAttr ".tk[99]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[100]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[101]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[102]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[103]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[104]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[105]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[106]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[107]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[108]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[109]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[231]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[232]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[233]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[234]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[235]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[236]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[237]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[238]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[239]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[240]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[241]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[242]" -type "float3" 0 -0.25113812 0.33249724 ;
	setAttr ".tk[243]" -type "float3" 0 -0.25113812 0.33249724 ;
	setAttr ".tk[244]" -type "float3" 0 -0.25113812 0.33249724 ;
	setAttr ".tk[245]" -type "float3" 0 -0.25113812 0.33249724 ;
	setAttr ".tk[246]" -type "float3" 0 -0.25113812 0.33249724 ;
	setAttr ".tk[247]" -type "float3" 0 -0.25113812 0.33249724 ;
	setAttr ".tk[248]" -type "float3" 0 -0.25113812 0.33249724 ;
	setAttr ".tk[249]" -type "float3" 0 -0.25113812 0.33249724 ;
	setAttr ".tk[250]" -type "float3" 0 -0.25113812 0.33249724 ;
	setAttr ".tk[251]" -type "float3" 0 -0.25113812 0.33249724 ;
	setAttr ".tk[252]" -type "float3" 0 -0.25113812 0.33249724 ;
	setAttr ".tk[253]" -type "float3" 0 -0.17825325 0.10910031 ;
	setAttr ".tk[254]" -type "float3" 0 -0.17825325 0.10910031 ;
	setAttr ".tk[255]" -type "float3" 0 -0.17825325 0.10910031 ;
	setAttr ".tk[256]" -type "float3" 0 -0.17825325 0.10910031 ;
	setAttr ".tk[257]" -type "float3" 0 -0.17825325 0.10910031 ;
	setAttr ".tk[258]" -type "float3" 0 -0.17825325 0.10910031 ;
	setAttr ".tk[259]" -type "float3" 0 -0.17825325 0.10910031 ;
	setAttr ".tk[260]" -type "float3" 0 -0.17825325 0.10910031 ;
	setAttr ".tk[261]" -type "float3" 0 -0.17825325 0.10910031 ;
	setAttr ".tk[262]" -type "float3" 0 -0.17825325 0.10910031 ;
	setAttr ".tk[263]" -type "float3" 0 -0.17825325 0.10910031 ;
	setAttr ".tk[264]" -type "float3" 0 -0.13823706 0.029620994 ;
	setAttr ".tk[265]" -type "float3" 0 -0.13823706 0.029620994 ;
	setAttr ".tk[266]" -type "float3" 0 -0.13823706 0.029620994 ;
	setAttr ".tk[267]" -type "float3" 0 -0.13823706 0.029620994 ;
	setAttr ".tk[268]" -type "float3" 0 -0.13823706 0.029620994 ;
	setAttr ".tk[269]" -type "float3" 0 -0.13823706 0.029620994 ;
	setAttr ".tk[270]" -type "float3" 0 -0.13823706 0.029620994 ;
	setAttr ".tk[271]" -type "float3" 0 -0.13823706 0.029620994 ;
	setAttr ".tk[272]" -type "float3" 0 -0.13823706 0.029620994 ;
	setAttr ".tk[273]" -type "float3" 0 -0.13823706 0.029620994 ;
	setAttr ".tk[274]" -type "float3" 0 -0.13823706 0.029620994 ;
	setAttr ".tk[275]" -type "float3" 0 -0.012125857 -0.010910038 ;
	setAttr ".tk[276]" -type "float3" 0 -0.012125857 -0.010910038 ;
	setAttr ".tk[277]" -type "float3" 0 -0.012125857 -0.010910038 ;
	setAttr ".tk[278]" -type "float3" 0 -0.012125857 -0.010910038 ;
	setAttr ".tk[279]" -type "float3" 0 -0.012125857 -0.010910038 ;
	setAttr ".tk[280]" -type "float3" 0 -0.012125857 -0.010910038 ;
	setAttr ".tk[281]" -type "float3" 0 -0.012125857 -0.010910038 ;
	setAttr ".tk[282]" -type "float3" 0 -0.012125857 -0.010910038 ;
	setAttr ".tk[283]" -type "float3" 0 -0.012125857 -0.010910038 ;
	setAttr ".tk[284]" -type "float3" 0 -0.012125857 -0.010910038 ;
	setAttr ".tk[285]" -type "float3" 0 -0.012125857 -0.010910038 ;
	setAttr ".tk[476]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[477]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[478]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[479]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[480]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[481]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[482]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[483]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[484]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[485]" -type "float3" 0 -0.13702436 0.03000249 ;
	setAttr ".tk[486]" -type "float3" 0 -0.13702436 0.03000249 ;
	setAttr ".tk[487]" -type "float3" 0 -0.13702436 0.03000249 ;
	setAttr ".tk[488]" -type "float3" 0 -0.13702436 0.03000249 ;
	setAttr ".tk[489]" -type "float3" 0 -0.13702436 0.03000249 ;
	setAttr ".tk[490]" -type "float3" 0 -0.13702436 0.03000249 ;
	setAttr ".tk[491]" -type "float3" 0 -0.13702436 0.03000249 ;
	setAttr ".tk[492]" -type "float3" 0 -0.13702436 0.03000249 ;
	setAttr ".tk[493]" -type "float3" 0 -0.13702436 0.03000249 ;
	setAttr ".tk[494]" -type "float3" 0 -0.17825328 0.10910031 ;
	setAttr ".tk[495]" -type "float3" 0 -0.17825328 0.0054549999 ;
	setAttr ".tk[496]" -type "float3" 0 -0.17825328 0.0054549999 ;
	setAttr ".tk[497]" -type "float3" 0 -0.17825328 0.0054549999 ;
	setAttr ".tk[498]" -type "float3" 0 -0.17825328 0.0054549999 ;
	setAttr ".tk[499]" -type "float3" 0 -0.17825328 0.0054549999 ;
	setAttr ".tk[500]" -type "float3" 0 -0.17825328 0.0054549999 ;
	setAttr ".tk[501]" -type "float3" 0 -0.17825328 0.0054549999 ;
	setAttr ".tk[502]" -type "float3" 0 -0.17825328 0.0054549999 ;
	setAttr ".tk[503]" -type "float3" 0 -0.25113812 0.23249826 ;
	setAttr ".tk[504]" -type "float3" 0 -0.25113812 0.13249928 ;
	setAttr ".tk[505]" -type "float3" 0 -0.25113812 0.032500282 ;
	setAttr ".tk[506]" -type "float3" 0 -0.25113812 -0.00024424307 ;
	setAttr ".tk[507]" -type "float3" 0 -0.25113812 -0.00024424307 ;
	setAttr ".tk[508]" -type "float3" 0 -0.25113812 -0.00024424307 ;
	setAttr ".tk[509]" -type "float3" 0 -0.25113812 -0.00024424307 ;
	setAttr ".tk[510]" -type "float3" 0 -0.25113812 -0.00024424307 ;
	setAttr ".tk[511]" -type "float3" 0 -0.25113812 -0.00024424307 ;
	setAttr ".tk[512]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[513]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[514]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[515]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[516]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[517]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[518]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[519]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[520]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[557]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[558]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[559]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[560]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[561]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[562]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[563]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[564]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[565]" -type "float3" 0 -0.012125857 0.0027275081 ;
	setAttr ".tk[566]" -type "float3" 0 -0.13702436 0.03000249 ;
	setAttr ".tk[567]" -type "float3" 0 -0.13702436 0.03000249 ;
	setAttr ".tk[568]" -type "float3" 0 -0.13702436 0.03000249 ;
	setAttr ".tk[569]" -type "float3" 0 -0.13702436 0.03000249 ;
	setAttr ".tk[570]" -type "float3" 0 -0.13702436 0.03000249 ;
	setAttr ".tk[571]" -type "float3" 0 -0.13702436 0.03000249 ;
	setAttr ".tk[572]" -type "float3" 0 -0.13702436 0.03000249 ;
	setAttr ".tk[573]" -type "float3" 0 -0.13702436 0.03000249 ;
	setAttr ".tk[574]" -type "float3" 0 -0.13702436 0.03000249 ;
	setAttr ".tk[575]" -type "float3" 0 -0.17825328 0.10910031 ;
	setAttr ".tk[576]" -type "float3" 0 -0.17825328 0.0054549999 ;
	setAttr ".tk[577]" -type "float3" 0 -0.17825328 0.0054549999 ;
	setAttr ".tk[578]" -type "float3" 0 -0.17825328 0.0054549999 ;
	setAttr ".tk[579]" -type "float3" 0 -0.17825328 0.0054549999 ;
	setAttr ".tk[580]" -type "float3" 0 -0.17825328 0.0054549999 ;
	setAttr ".tk[581]" -type "float3" 0 -0.17825328 0.0054549999 ;
	setAttr ".tk[582]" -type "float3" 0 -0.17825328 0.0054549999 ;
	setAttr ".tk[583]" -type "float3" 0 -0.17825328 0.0054549999 ;
	setAttr ".tk[584]" -type "float3" 0 -0.25113812 0.23249826 ;
	setAttr ".tk[585]" -type "float3" 0 -0.25113812 0.13249928 ;
	setAttr ".tk[586]" -type "float3" 0 -0.25113812 0.032500282 ;
	setAttr ".tk[587]" -type "float3" 0 -0.25113812 -0.00024424307 ;
	setAttr ".tk[588]" -type "float3" 0 -0.25113812 -0.00024424307 ;
	setAttr ".tk[589]" -type "float3" 0 -0.25113812 -0.00024424307 ;
	setAttr ".tk[590]" -type "float3" 0 -0.25113812 -0.00024424307 ;
	setAttr ".tk[591]" -type "float3" 0 -0.25113812 -0.00024424307 ;
	setAttr ".tk[592]" -type "float3" 0 -0.25113812 -0.00024424307 ;
	setAttr ".tk[593]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[594]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[595]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[596]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[597]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[598]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[599]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[600]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
	setAttr ".tk[601]" -type "float3" 0 -6.4074993e-007 1.2926757e-006 ;
createNode polySplit -n "polySplit1";
	rename -uid "A70DCD64-48DC-F517-7A4D-C6B1B5EEBF81";
	setAttr -s 41 ".e[0:40]"  0.558083 0.558083 0.558083 0.558083 0.558083
		 0.558083 0.558083 0.558083 0.558083 0.558083 0.558083 0.558083 0.558083 0.558083
		 0.558083 0.558083 0.558083 0.558083 0.558083 0.558083 0.441917 0.441917 0.441917
		 0.441917 0.441917 0.441917 0.441917 0.441917 0.441917 0.441917 0.441917 0.558083
		 0.558083 0.558083 0.558083 0.558083 0.558083 0.558083 0.558083 0.558083 0.558083;
	setAttr -s 41 ".d[0:40]"  -2147483160 -2147483159 -2147483158 -2147483157 -2147483156 -2147483155 
		-2147483154 -2147483153 -2147483152 -2147483151 -2147483150 -2147482638 -2147482639 -2147482640 -2147482641 -2147482642 -2147482643 -2147482644 
		-2147482645 -2147482646 -2147483007 -2147483008 -2147483009 -2147483010 -2147483011 -2147483012 -2147483013 -2147483014 -2147483015 -2147483016 
		-2147483017 -2147482466 -2147482465 -2147482464 -2147482463 -2147482462 -2147482461 -2147482460 -2147482459 -2147482458 -2147483160;
	setAttr ".sma" 180;
	setAttr ".m2015" yes;
createNode polySplit -n "polySplit2";
	rename -uid "D8CD9E09-4555-7889-25F3-F7B48071E399";
	setAttr -s 41 ".e[0:40]"  0.53585303 0.53585303 0.53585303 0.53585303
		 0.53585303 0.53585303 0.53585303 0.53585303 0.53585303 0.53585303 0.53585303 0.53585303
		 0.53585303 0.53585303 0.53585303 0.53585303 0.53585303 0.53585303 0.53585303 0.53585303
		 0.464147 0.464147 0.464147 0.464147 0.464147 0.464147 0.464147 0.464147 0.464147
		 0.464147 0.464147 0.53585303 0.53585303 0.53585303 0.53585303 0.53585303 0.53585303
		 0.53585303 0.53585303 0.53585303 0.53585303;
	setAttr -s 41 ".d[0:40]"  -2147483160 -2147483159 -2147483158 -2147483157 -2147483156 -2147483155 
		-2147483154 -2147483153 -2147483152 -2147483151 -2147483150 -2147482638 -2147482639 -2147482640 -2147482641 -2147482642 -2147482643 -2147482644 
		-2147482645 -2147482646 -2147482428 -2147482427 -2147482426 -2147482425 -2147482424 -2147482423 -2147482422 -2147482421 -2147482420 -2147482419 
		-2147482418 -2147482466 -2147482465 -2147482464 -2147482463 -2147482462 -2147482461 -2147482460 -2147482459 -2147482458 -2147483160;
	setAttr ".sma" 180;
	setAttr ".m2015" yes;
createNode polySplit -n "polySplit3";
	rename -uid "8EB5AC26-4956-4133-496C-A399F95FBCD7";
	setAttr -s 41 ".e[0:40]"  0.45034301 0.45034301 0.45034301 0.45034301
		 0.45034301 0.45034301 0.45034301 0.45034301 0.45034301 0.45034301 0.45034301 0.54965699
		 0.54965699 0.54965699 0.54965699 0.54965699 0.54965699 0.54965699 0.54965699 0.54965699
		 0.54965699 0.54965699 0.54965699 0.54965699 0.54965699 0.54965699 0.54965699 0.54965699
		 0.54965699 0.54965699 0.54965699 0.54965699 0.54965699 0.54965699 0.54965699 0.54965699
		 0.54965699 0.54965699 0.54965699 0.54965699 0.45034301;
	setAttr -s 41 ".d[0:40]"  -2147483017 -2147483016 -2147483015 -2147483014 -2147483013 -2147483012 
		-2147483011 -2147483010 -2147483009 -2147483008 -2147483007 -2147482429 -2147482430 -2147482431 -2147482432 -2147482433 -2147482434 -2147482435 
		-2147482436 -2147482437 -2147482438 -2147482439 -2147482440 -2147482441 -2147482442 -2147482443 -2147482444 -2147482445 -2147482446 -2147482447 
		-2147482448 -2147482409 -2147482410 -2147482411 -2147482412 -2147482413 -2147482414 -2147482415 -2147482416 -2147482417 -2147483017;
	setAttr ".sma" 180;
	setAttr ".m2015" yes;
createNode polySplit -n "polySplit4";
	rename -uid "EC43DCDF-47B9-C25A-A99F-64BF4841FB52";
	setAttr -s 41 ".e[0:40]"  0.577663 0.422337 0.422337 0.422337 0.422337
		 0.422337 0.422337 0.422337 0.422337 0.422337 0.422337 0.422337 0.422337 0.422337
		 0.422337 0.422337 0.422337 0.422337 0.422337 0.422337 0.422337 0.422337 0.422337
		 0.422337 0.422337 0.422337 0.422337 0.422337 0.422337 0.422337 0.577663 0.577663
		 0.577663 0.577663 0.577663 0.577663 0.577663 0.577663 0.577663 0.577663 0.577663;
	setAttr -s 41 ".d[0:40]"  -2147482428 -2147482349 -2147482350 -2147482351 -2147482352 -2147482353 
		-2147482354 -2147482355 -2147482356 -2147482357 -2147482358 -2147482359 -2147482360 -2147482361 -2147482362 -2147482363 -2147482364 -2147482365 
		-2147482366 -2147482367 -2147482368 -2147482329 -2147482330 -2147482331 -2147482332 -2147482333 -2147482334 -2147482335 -2147482336 -2147482337 
		-2147482418 -2147482419 -2147482420 -2147482421 -2147482422 -2147482423 -2147482424 -2147482425 -2147482426 -2147482427 -2147482428;
	setAttr ".sma" 180;
	setAttr ".m2015" yes;
createNode polySplit -n "polySplit5";
	rename -uid "DB19E9AF-49A8-679E-6EB0-A5AC58180673";
	setAttr -s 41 ".e[0:40]"  0.494376 0.494376 0.494376 0.494376 0.494376
		 0.494376 0.494376 0.494376 0.494376 0.494376 0.494376 0.494376 0.494376 0.494376
		 0.494376 0.494376 0.494376 0.494376 0.494376 0.494376 0.505624 0.505624 0.505624
		 0.505624 0.505624 0.505624 0.505624 0.505624 0.505624 0.505624 0.505624 0.494376
		 0.494376 0.494376 0.494376 0.494376 0.494376 0.494376 0.494376 0.494376 0.494376;
	setAttr -s 41 ".d[0:40]"  -2147483160 -2147483159 -2147483158 -2147483157 -2147483156 -2147483155 
		-2147483154 -2147483153 -2147483152 -2147483151 -2147483150 -2147482638 -2147482639 -2147482640 -2147482641 -2147482642 -2147482643 -2147482644 
		-2147482645 -2147482646 -2147482348 -2147482347 -2147482346 -2147482345 -2147482344 -2147482343 -2147482342 -2147482341 -2147482340 -2147482339 
		-2147482338 -2147482466 -2147482465 -2147482464 -2147482463 -2147482462 -2147482461 -2147482460 -2147482459 -2147482458 -2147483160;
	setAttr ".sma" 180;
	setAttr ".m2015" yes;
createNode script -n "uiConfigurationScriptNode";
	rename -uid "D76E946B-4676-934B-B6AA-E296FFAF20C5";
	setAttr ".b" -type "string" (
		"// Maya Mel UI Configuration File.\n//\n//  This script is machine generated.  Edit at your own risk.\n//\n//\n\nglobal string $gMainPane;\nif (`paneLayout -exists $gMainPane`) {\n\n\tglobal int $gUseScenePanelConfig;\n\tint    $useSceneConfig = $gUseScenePanelConfig;\n\tint    $menusOkayInPanels = `optionVar -q allowMenusInPanels`;\tint    $nVisPanes = `paneLayout -q -nvp $gMainPane`;\n\tint    $nPanes = 0;\n\tstring $editorName;\n\tstring $panelName;\n\tstring $itemFilterName;\n\tstring $panelConfig;\n\n\t//\n\t//  get current state of the UI\n\t//\n\tsceneUIReplacement -update $gMainPane;\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Top View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"side\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n"
		+ "            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n"
		+ "            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n"
		+ "            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 688\n            -height 710\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Side View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"side\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n"
		+ "            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n"
		+ "            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 777\n            -height 333\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Front View\")) `;\n"
		+ "\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"front\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n"
		+ "            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n"
		+ "            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 778\n            -height 333\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n"
		+ "        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Persp View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"persp\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n"
		+ "            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n"
		+ "            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n"
		+ "            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 689\n            -height 710\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"outlinerPanel\" (localizedPanelLabel(\"ToggledOutliner\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\toutlinerPanel -edit -l (localizedPanelLabel(\"ToggledOutliner\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        outlinerEditor -e \n            -showShapes 0\n            -showAssignedMaterials 0\n            -showTimeEditor 1\n            -showReferenceNodes 0\n            -showReferenceMembers 0\n            -showAttributes 0\n            -showConnected 0\n            -showAnimCurvesOnly 0\n"
		+ "            -showMuteInfo 0\n            -organizeByLayer 1\n            -showAnimLayerWeight 1\n            -autoExpandLayers 1\n            -autoExpand 0\n            -showDagOnly 1\n            -showAssets 1\n            -showContainedOnly 1\n            -showPublishedAsConnected 0\n            -showContainerContents 1\n            -ignoreDagHierarchy 0\n            -expandConnections 0\n            -showUpstreamCurves 1\n            -showUnitlessCurves 1\n            -showCompounds 1\n            -showLeafs 1\n            -showNumericAttrsOnly 0\n            -highlightActive 1\n            -autoSelectNewObjects 0\n            -doNotSelectNewObjects 0\n            -dropIsParent 1\n            -transmitFilters 0\n            -setFilter \"0\" \n            -showSetMembers 1\n            -allowMultiSelection 1\n            -alwaysToggleSelect 0\n            -directSelect 0\n            -isSet 0\n            -isSetMember 0\n            -displayMode \"DAG\" \n            -expandObjects 0\n            -setsIgnoreFilters 1\n            -containersIgnoreFilters 0\n"
		+ "            -editAttrName 0\n            -showAttrValues 0\n            -highlightSecondary 0\n            -showUVAttrsOnly 0\n            -showTextureNodesOnly 0\n            -attrAlphaOrder \"default\" \n            -animLayerFilterOptions \"allAffecting\" \n            -sortOrder \"none\" \n            -longNames 0\n            -niceNames 1\n            -showNamespace 1\n            -showPinIcons 0\n            -mapMotionTrails 0\n            -ignoreHiddenAttribute 0\n            -ignoreOutlinerColor 0\n            -renderFilterVisible 0\n            -renderFilterIndex 0\n            -selectionOrder \"chronological\" \n            -expandAttribute 0\n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"outlinerPanel\" (localizedPanelLabel(\"Outliner\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\toutlinerPanel -edit -l (localizedPanelLabel(\"Outliner\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        outlinerEditor -e \n"
		+ "            -showShapes 0\n            -showAssignedMaterials 0\n            -showTimeEditor 1\n            -showReferenceNodes 0\n            -showReferenceMembers 0\n            -showAttributes 0\n            -showConnected 0\n            -showAnimCurvesOnly 0\n            -showMuteInfo 0\n            -organizeByLayer 1\n            -showAnimLayerWeight 1\n            -autoExpandLayers 1\n            -autoExpand 0\n            -showDagOnly 1\n            -showAssets 1\n            -showContainedOnly 1\n            -showPublishedAsConnected 0\n            -showContainerContents 1\n            -ignoreDagHierarchy 0\n            -expandConnections 0\n            -showUpstreamCurves 1\n            -showUnitlessCurves 1\n            -showCompounds 1\n            -showLeafs 1\n            -showNumericAttrsOnly 0\n            -highlightActive 1\n            -autoSelectNewObjects 0\n            -doNotSelectNewObjects 0\n            -dropIsParent 1\n            -transmitFilters 0\n            -setFilter \"defaultSetFilter\" \n            -showSetMembers 1\n"
		+ "            -allowMultiSelection 1\n            -alwaysToggleSelect 0\n            -directSelect 0\n            -displayMode \"DAG\" \n            -expandObjects 0\n            -setsIgnoreFilters 1\n            -containersIgnoreFilters 0\n            -editAttrName 0\n            -showAttrValues 0\n            -highlightSecondary 0\n            -showUVAttrsOnly 0\n            -showTextureNodesOnly 0\n            -attrAlphaOrder \"default\" \n            -animLayerFilterOptions \"allAffecting\" \n            -sortOrder \"none\" \n            -longNames 0\n            -niceNames 1\n            -showNamespace 1\n            -showPinIcons 0\n            -mapMotionTrails 0\n            -ignoreHiddenAttribute 0\n            -ignoreOutlinerColor 0\n            -renderFilterVisible 0\n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"graphEditor\" (localizedPanelLabel(\"Graph Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n"
		+ "\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Graph Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showAssignedMaterials 0\n                -showTimeEditor 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 1\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 1\n                -showCompounds 0\n                -showLeafs 1\n"
		+ "                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 1\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 1\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 1\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n"
		+ "                -ignoreOutlinerColor 0\n                -renderFilterVisible 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"GraphEd\");\n            animCurveEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 1\n                -displayInfinities 0\n                -displayValues 0\n                -autoFit 1\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -showResults \"off\" \n                -showBufferCurves \"off\" \n                -smoothness \"fine\" \n                -resultSamples 1\n                -resultScreenSamples 0\n                -resultUpdate \"delayed\" \n                -showUpstreamCurves 1\n                -showCurveNames 0\n                -showActiveCurveNames 0\n                -stackedCurves 0\n                -stackedCurvesMin -1\n                -stackedCurvesMax 1\n                -stackedCurvesSpace 0.2\n                -displayNormalized 0\n                -preSelectionHighlight 0\n"
		+ "                -constrainDrag 0\n                -classicMode 1\n                -valueLinesToggle 1\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dopeSheetPanel\" (localizedPanelLabel(\"Dope Sheet\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dope Sheet\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showAssignedMaterials 0\n                -showTimeEditor 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 0\n"
		+ "                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 0\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 1\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n"
		+ "                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 0\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                -ignoreOutlinerColor 0\n                -renderFilterVisible 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"DopeSheetEd\");\n            dopeSheetEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -displayValues 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -outliner \"dopeSheetPanel1OutlineEd\" \n                -showSummary 1\n                -showScene 0\n                -hierarchyBelow 0\n                -showTicks 1\n"
		+ "                -selectionWindow 0 0 0 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"timeEditorPanel\" (localizedPanelLabel(\"Time Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Time Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"clipEditorPanel\" (localizedPanelLabel(\"Trax Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n"
		+ "                -displayValues 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -initialized 0\n                -manageSequencer 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"sequenceEditorPanel\" (localizedPanelLabel(\"Camera Sequencer\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Camera Sequencer\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = sequenceEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -displayValues 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -initialized 0\n                -manageSequencer 1 \n"
		+ "                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperGraphPanel\" (localizedPanelLabel(\"Hypergraph Hierarchy\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypergraph Hierarchy\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n                -orientation \"horiz\" \n                -mergeConnections 0\n                -zoom 1\n                -animateTransition 0\n                -showRelationships 1\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n                -showConnectionFromSelected 0\n                -showConnectionToSelected 0\n                -showConstraintLabels 0\n                -showUnderworld 0\n                -showInvisible 0\n"
		+ "                -transitionFrames 1\n                -opaqueContainers 0\n                -freeform 0\n                -imagePosition 0 0 \n                -imageScale 1\n                -imageEnabled 0\n                -graphType \"DAG\" \n                -heatMapDisplay 0\n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n                -range 0 0 \n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperShadePanel\" (localizedPanelLabel(\"Hypershade\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypershade\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"visorPanel\" (localizedPanelLabel(\"Visor\")) `;\n"
		+ "\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Visor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"nodeEditorPanel\" (localizedPanelLabel(\"Node Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Node Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"NodeEditorEd\");\n            nodeEditor -e \n                -allAttributes 0\n                -allNodes 0\n                -autoSizeNodes 1\n                -consistentNameSize 1\n                -createNodeCommand \"nodeEdCreateNodeCommand\" \n                -defaultPinnedState 0\n                -additiveGraphingMode 0\n                -settingsChangedCallback \"nodeEdSyncControls\" \n                -traversalDepthLimit -1\n                -keyPressCommand \"nodeEdKeyPressCommand\" \n                -nodeTitleMode \"name\" \n"
		+ "                -gridSnap 0\n                -gridVisibility 1\n                -popupMenuScript \"nodeEdBuildPanelMenus\" \n                -showNamespace 1\n                -showShapes 1\n                -showSGShapes 0\n                -showTransforms 1\n                -useAssets 1\n                -syncedSelection 1\n                -extendToShapes 1\n                -activeTab -1\n                -editorMode \"default\" \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"createNodePanel\" (localizedPanelLabel(\"Create Node\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Create Node\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"polyTexturePlacementPanel\" (localizedPanelLabel(\"UV Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n"
		+ "\t\tscriptedPanel -edit -l (localizedPanelLabel(\"UV Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"renderWindowPanel\" (localizedPanelLabel(\"Render View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"shapePanel\" (localizedPanelLabel(\"Shape Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tshapePanel -edit -l (localizedPanelLabel(\"Shape Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"posePanel\" (localizedPanelLabel(\"Pose Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tposePanel -edit -l (localizedPanelLabel(\"Pose Editor\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynRelEdPanel\" (localizedPanelLabel(\"Dynamic Relationships\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"relationshipPanel\" (localizedPanelLabel(\"Relationship Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"referenceEditorPanel\" (localizedPanelLabel(\"Reference Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"componentEditorPanel\" (localizedPanelLabel(\"Component Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Component Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynPaintScriptedPanelType\" (localizedPanelLabel(\"Paint Effects\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"scriptEditorPanel\" (localizedPanelLabel(\"Script Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"profilerPanel\" (localizedPanelLabel(\"Profiler Tool\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Profiler Tool\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"contentBrowserPanel\" (localizedPanelLabel(\"Content Browser\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Content Browser\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"Stereo\" (localizedPanelLabel(\"Stereo\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Stereo\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "string $editorName = ($panelName+\"Editor\");\n            stereoCameraView -e \n                -camera \"persp\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -holdOuts 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 32768\n                -fogging 0\n                -fogSource \"fragment\" \n"
		+ "                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -depthOfFieldPreview 1\n                -maxConstantTransparency 1\n                -objectFilterShowInHUD 1\n                -isFiltered 0\n                -colorResolution 4 4 \n                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n"
		+ "                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -imagePlane 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                -captureSequenceNumber -1\n                -width 0\n"
		+ "                -height 0\n                -sceneRenderFilter 0\n                -displayMode \"centerEye\" \n                -viewColor 0 0 0 1 \n                -useCustomBackground 1\n                $editorName;\n            stereoCameraView -e -viewSelected 0 $editorName;\n            stereoCameraView -e \n                -pluginObjects \"gpuCacheDisplayFilter\" 1 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\tif ($useSceneConfig) {\n        string $configName = `getPanel -cwl (localizedPanelLabel(\"Current Layout\"))`;\n        if (\"\" != $configName) {\n\t\t\tpanelConfiguration -edit -label (localizedPanelLabel(\"Current Layout\")) \n\t\t\t\t-userCreated false\n\t\t\t\t-defaultImage \"\"\n\t\t\t\t-image \"\"\n\t\t\t\t-sc false\n\t\t\t\t-configString \"global string $gMainPane; paneLayout -e -cn \\\"vertical2\\\" -ps 1 50 100 -ps 2 50 100 $gMainPane;\"\n\t\t\t\t-removeAllPanels\n\t\t\t\t-ap false\n\t\t\t\t\t(localizedPanelLabel(\"Persp View\")) \n\t\t\t\t\t\"modelPanel\"\n"
		+ "\t\t\t\t\t\"$panelName = `modelPanel -unParent -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels `;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -holdOuts 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 0\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 32768\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -depthOfFieldPreview 1\\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 1\\n    -shadows 0\\n    -captureSequenceNumber -1\\n    -width 689\\n    -height 710\\n    -sceneRenderFilter 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName;\\nmodelEditor -e \\n    -pluginObjects \\\"gpuCacheDisplayFilter\\\" 1 \\n    $editorName\"\n"
		+ "\t\t\t\t\t\"modelPanel -edit -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels  $panelName;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -holdOuts 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 0\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 32768\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -depthOfFieldPreview 1\\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 1\\n    -shadows 0\\n    -captureSequenceNumber -1\\n    -width 689\\n    -height 710\\n    -sceneRenderFilter 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName;\\nmodelEditor -e \\n    -pluginObjects \\\"gpuCacheDisplayFilter\\\" 1 \\n    $editorName\"\n"
		+ "\t\t\t\t-ap false\n\t\t\t\t\t(localizedPanelLabel(\"Top View\")) \n\t\t\t\t\t\"modelPanel\"\n"
		+ "\t\t\t\t\t\"$panelName = `modelPanel -unParent -l (localizedPanelLabel(\\\"Top View\\\")) -mbv $menusOkayInPanels `;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -camera \\\"side\\\" \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -holdOuts 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 0\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 32768\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -depthOfFieldPreview 1\\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 1\\n    -shadows 0\\n    -captureSequenceNumber -1\\n    -width 688\\n    -height 710\\n    -sceneRenderFilter 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName;\\nmodelEditor -e \\n    -pluginObjects \\\"gpuCacheDisplayFilter\\\" 1 \\n    $editorName\"\n"
		+ "\t\t\t\t\t\"modelPanel -edit -l (localizedPanelLabel(\\\"Top View\\\")) -mbv $menusOkayInPanels  $panelName;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -camera \\\"side\\\" \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -holdOuts 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 0\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 32768\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -depthOfFieldPreview 1\\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 1\\n    -shadows 0\\n    -captureSequenceNumber -1\\n    -width 688\\n    -height 710\\n    -sceneRenderFilter 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName;\\nmodelEditor -e \\n    -pluginObjects \\\"gpuCacheDisplayFilter\\\" 1 \\n    $editorName\"\n"
		+ "\t\t\t\t$configName;\n\n            setNamedPanelLayout (localizedPanelLabel(\"Current Layout\"));\n        }\n\n        panelHistory -e -clear mainPanelHistory;\n        sceneUIReplacement -clear;\n\t}\n\n\ngrid -spacing 5 -size 12 -divisions 5 -displayAxes yes -displayGridLines yes -displayDivisionLines yes -displayPerspectiveLabels no -displayOrthographicLabels no -displayAxesBold yes -perspectiveLabelPosition axis -orthographicLabelPosition edge;\nviewManip -drawCompass 0 -compassAngle 0 -frontParameters \"\" -homeParameters \"\" -selectionLockParameters \"\";\n}\n");
	setAttr ".st" 3;
createNode script -n "sceneConfigurationScriptNode";
	rename -uid "A1B103CF-4FE0-4540-852F-02B807177F6D";
	setAttr ".b" -type "string" "playbackOptions -min 1 -max 120 -ast 1 -aet 200 ";
	setAttr ".st" 6;
select -ne :time1;
	setAttr ".o" 1;
	setAttr ".unw" 1;
select -ne :hardwareRenderingGlobals;
	setAttr ".otfna" -type "stringArray" 22 "NURBS Curves" "NURBS Surfaces" "Polygons" "Subdiv Surface" "Particles" "Particle Instance" "Fluids" "Strokes" "Image Planes" "UI" "Lights" "Cameras" "Locators" "Joints" "IK Handles" "Deformers" "Motion Trails" "Components" "Hair Systems" "Follicles" "Misc. UI" "Ornaments"  ;
	setAttr ".otfva" -type "Int32Array" 22 0 1 1 1 1 1
		 1 1 1 0 0 0 0 0 0 0 0 0
		 0 0 0 0 ;
	setAttr ".fprt" yes;
select -ne :renderPartition;
	setAttr -s 2 ".st";
select -ne :renderGlobalsList1;
select -ne :defaultShaderList1;
	setAttr -s 4 ".s";
select -ne :postProcessList1;
	setAttr -s 2 ".p";
select -ne :defaultRenderingList1;
select -ne :initialShadingGroup;
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	setAttr ".ro" yes;
select -ne :defaultRenderGlobals;
	setAttr ".ren" -type "string" "arnold";
select -ne :defaultResolution;
	setAttr ".pa" 1;
select -ne :hardwareRenderGlobals;
	setAttr ".ctrs" 256;
	setAttr ".btrs" 512;
select -ne :ikSystem;
	setAttr -s 4 ".sol";
connectAttr ":defaultColorMgtGlobals.cme" "imagePlaneShape1.cme";
connectAttr ":defaultColorMgtGlobals.cfe" "imagePlaneShape1.cmcf";
connectAttr ":defaultColorMgtGlobals.cfp" "imagePlaneShape1.cmcp";
connectAttr ":defaultColorMgtGlobals.wsn" "imagePlaneShape1.ws";
connectAttr ":sideShape.msg" "imagePlaneShape1.ltc";
connectAttr "polySplit5.out" "pCubeShape1.i";
relationship "link" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
connectAttr "layerManager.dli[0]" "defaultLayer.id";
connectAttr "renderLayerManager.rlmi[0]" "defaultRenderLayer.rlid";
connectAttr ":mentalrayGlobals.msg" ":mentalrayItemsList.glb";
connectAttr ":miDefaultOptions.msg" ":mentalrayItemsList.opt" -na;
connectAttr ":miDefaultFramebuffer.msg" ":mentalrayItemsList.fb" -na;
connectAttr ":miDefaultOptions.msg" ":mentalrayGlobals.opt";
connectAttr ":miDefaultFramebuffer.msg" ":mentalrayGlobals.fb";
connectAttr "polyCube1.out" "polyTweak1.ip";
connectAttr "polyTweak1.out" "deleteComponent1.ig";
connectAttr "deleteComponent1.og" "polyTweak2.ip";
connectAttr "polyTweak2.out" "polySplit1.ip";
connectAttr "polySplit1.out" "polySplit2.ip";
connectAttr "polySplit2.out" "polySplit3.ip";
connectAttr "polySplit3.out" "polySplit4.ip";
connectAttr "polySplit4.out" "polySplit5.ip";
connectAttr "defaultRenderLayer.msg" ":defaultRenderingList1.r" -na;
connectAttr "pCubeShape1.iog" ":initialShadingGroup.dsm" -na;
// End of ass2.ma
