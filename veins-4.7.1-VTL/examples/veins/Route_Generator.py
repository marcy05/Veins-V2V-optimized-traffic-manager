import time

author = "Marcello Sgarbi"

name1="CarA"
name2="CarB"
acc=2.6
dece=5
sigma=0.5
minG=2.0
#here in km/h -> it's converted in m/s in the string filling
maxSpeedA=50.0
maxSpeedB=90.0

idVar = 0
routeVar = 0

departingTime = 0.0

#######################################################################################
#                                FIRST SET TESTED
#######################################################################################

#Evehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
#Esignals =  [2, 4, 3, 4, 2, 4, 2, 4, 4, 4, 2, 3, 2, 2, 4, 4 ]

#Nvehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]
#Nsignals =  [2, 4, 3, 2, 3, 2, 4, 4, 2, 2, 2, 4, 4, 4, 2, 3, 2]

#Wvehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]
#Wsignals =  [4, 4, 2, 2, 4, 3, 2, 4, 3, 2, 2, 4, 4, 4, 2, 3, 2]

#Svehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
#Ssignals =  [4, 3, 3, 2, 2, 4, 2, 2, 2, 3, 4, 3, 2, 2, 4, 3 ]

#######################################################################################
#                               SECOND SET TESTED
#######################################################################################

#Evehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
#Esignals =  [4, 2, 4, 3, 4, 2, 2, 3, 4, 3, 4, 4, 2, 2, 2, 2]

#Nvehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]
#Nsignals =  [3, 2, 4, 2, 2, 2, 3, 3, 3, 4, 2, 2, 3, 4, 4, 4, 4]

#Wvehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]
#Wsignals =  [2, 3, 4, 3, 2, 3, 2, 2, 3, 2, 4, 2, 4, 4, 2, 2, 3]

#Svehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
#Ssignals =  [4, 4, 3, 2, 2, 2, 4, 3, 3, 4, 4, 3, 3, 3, 2, 2]

#######################################################################################
#                               THIRD SET TESTED
#######################################################################################

#Evehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
#Esignals =  [2, 4, 3, 2, 2, 2, 2, 3, 2, 4, 2, 3, 4, 2, 2, 4]

#Nvehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]
#Nsignals =  [3, 2, 4, 4, 2, 4, 2, 2, 4, 2, 2, 2, 3, 3, 4, 3, 3]

#Wvehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]
#Wsignals =  [3, 3, 2, 3, 3, 4, 2, 4, 4, 2, 2, 4, 2, 2, 2, 3, 3]

#Svehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
#Ssignals =  [4, 3, 3, 2, 4, 4, 2, 4, 2, 2, 2, 4, 3, 4, 2, 3]

#######################################################################################
#                               FOURTH SET TESTED
#######################################################################################

#Evehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
#Esignals =  [4, 4, 4, 2, 2, 2, 3, 3, 3, 2, 2, 2, 4, 4, 4, 4]

#Nvehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]
#Nsignals =  [2, 3, 4, 2, 4, 2, 2, 2, 2, 2, 4, 2, 2, 3, 4, 4, 2]

#Wvehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]
#Wsignals =  [3, 4, 3, 3, 4, 4, 4, 3, 4, 3, 2, 4, 2, 4, 3, 4, 4]

#Svehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
#Ssignals =  [2, 4, 3, 2, 3, 3, 2, 4, 2, 4, 3, 2, 3, 4, 2, 2]

#######################################################################################
#                               FIFTH SET TESTED
#######################################################################################

#Evehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
#Esignals =  [4, 3, 4, 4, 4, 2, 2, 2, 3, 2, 2, 4, 3, 2, 4, 3]

#Nvehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]
#Nsignals =  [2, 2, 3, 2, 3, 4, 4, 4, 2, 4, 4, 2, 2, 2, 4, 2, 3]

#Wvehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]
#Wsignals =  [3, 4, 4, 4, 3, 2, 3, 4, 4, 2, 4, 4, 2, 2, 3, 4, 2]

#Svehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
#Ssignals =  [2, 4, 4, 3, 4, 4, 4, 3, 2, 4, 4, 4, 3, 2, 2, 4]

#######################################################################################
#                               SIXTH SET TESTED
#######################################################################################

#Evehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
#Esignals =  [2, 2, 4, 2, 4, 3, 3, 4, 3, 2, 4, 4, 3, 3, 4, 4]

#Nvehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]
#Nsignals =  [2, 2, 3, 3, 4, 4, 2, 4, 2, 2, 2, 2, 4, 4, 4, 2, 3]

#Wvehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]
#Wsignals =  [2, 4, 4, 3, 4, 4, 3, 3, 4, 4, 3, 2, 4, 4, 4, 4, 4]

#Svehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
#Ssignals =  [4, 4, 4, 3, 4, 4, 3, 3, 4, 4, 4, 3, 4, 2, 2, 2]

#######################################################################################
#                               SEVENTH SET TESTED
#######################################################################################

#Evehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
#Esignals =  [4, 2, 4, 4, 2, 4, 2, 4, 2, 4, 2, 2, 4, 3, 4, 2]

#Nvehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]
#Nsignals =  [2, 2, 3, 2, 3, 4, 4, 4, 2, 4, 4, 2, 2, 2, 4, 2, 3]

#Wvehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]
#Wsignals =  [3, 4, 4, 4, 3, 2, 3, 4, 4, 2, 4, 4, 2, 2, 3, 4, 2]

#Svehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
#Ssignals =  [3, 4, 3, 4, 2, 4, 4, 3, 4, 3, 2, 2, 4, 2, 4, 4]

#######################################################################################
#                               EIGHTH SET TESTED
#######################################################################################

#Evehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
#Esignals =  [2, 2, 4, 4, 4, 4, 2, 3, 3, 3, 4, 2, 4, 3, 4, 2]

#Nvehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]
#Nsignals =  [3, 2, 2, 3, 2, 3, 3, 3, 3, 3, 2, 3, 2, 4, 4, 4, 2]

#Wvehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]
#Wsignals =  [4, 3, 3, 4, 2, 2, 4, 2, 2, 4, 4, 2, 2, 3, 3, 2, 3]

#Svehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
#Ssignals =  [2, 2, 4, 2, 3, 2, 4, 3, 4, 4, 4, 3, 4, 3, 3, 2]

#######################################################################################
#                               NINETH SET TESTED
#######################################################################################

Evehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
Esignals =  [2, 2, 3, 4, 2, 3, 3, 2, 3, 3, 2, 2, 4, 3, 2, 3]

Nvehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]
Nsignals =  [4, 4, 4, 3, 3, 2, 4, 3, 4, 4, 3, 2, 4, 2, 4, 2, 4]

Wvehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]
Wsignals =  [4, 2, 3, 3, 3, 2, 2, 2, 4, 2, 3, 2, 2, 4, 4, 4, 4]

Svehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
Ssignals =  [3, 4, 2, 3, 4, 4, 2, 3, 4, 2, 4, 4, 3, 3, 2, 2]

#######################################################################################
#                               TENTH SET TESTED
#######################################################################################

Evehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
Esignals =  [4, 2, 4, 3, 2, 3, 2, 3, 3, 3, 2, 4, 2, 3, 2, 4]

Nvehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]
Nsignals =  [4, 3, 3, 4, 4, 4, 2, 4, 2, 2, 3, 3, 3, 2, 4, 4, 4]

Wvehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]
Wsignals =  [4, 2, 4, 3, 3, 3, 4, 3, 2, 2, 4, 4, 3, 2, 2, 4, 3]

Svehicles = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
Ssignals =  [2, 2, 3, 2, 3, 3, 4, 2, 4, 3, 3, 2, 2, 3, 4, 2]



#######################################################################################
#       Uncomment this and epty the lists above if you want to fill the list
#           by console to generate the Cross_intersectio.rou fie
#######################################################################################
#East
#print("Insert East vehicles as 1,2,3,...\n\tDigit 999 to finish")
#Ewritev = input("\tDigit vehicle: ")
#while(Ewritev != "999"):
#    Evehicles.append(int(Ewritev))
#    Ewritev = input("\tDigit vehicle: ")
#    if(str(Ewritev) == "999"):
#        break
#
#print("\nInsert East signals as 1,2,3,...\n\tDigit 999 to finish")
#Ewrites = input("\tDigit East signal: ")
#Esignals.append(int(Ewrites))
#while(Ewrites != "999"):
#    Esignals.append(int(Ewrites))
#    Ewrites = input("\tDigit vehicle: ")
#    if(str(Ewrites) == "999"):
#        break
#
##Nord
#print("\n\nInsert Nord vehicles as 1,2,3,...\n\tDigit 999 to finish")
#Nwritev = input("\tDigit vehicle: ")
#while(Nwritev != "999"):
#    Nvehicles.append(int(Nwritev))
#    Nwritev = input("\tDigit vehicle: ")
#    if(str(Nwritev) == "999"):
#        break
#
#print("\nInsert Nord signals as 1,2,3,...\n\tDigit 999 to finish")
#Nwrites = input("\tDigit Nord signal: ")
#Nsignals.append(int(Nwrites))
#while(Nwrites != "999"):
#    Nsignals.append(int(Nwrites))
#    Nwrites = input("\tDigit vehicle: ")
#    if(str(Nwrites) == "999"):
#        break
#
##West
#print("\n\nInsert West vehicles as 1,2,3,...\n\tDigit 999 to finish")
#Wwritev = input("\tDigit vehicle: ")
#while(Wwritev != "999"):
#    Wvehicles.append(int(Wwritev))
#    Wwritev = input("\tDigit vehicle: ")
#    if(str(Wwritev) == "999"):
#        break
#
#print("\nInsert West signals as 1,2,3,...\n\tDigit 999 to finish")
#Wwrites = input("\tDigit West signal: ")
#Wsignals.append(int(Wwrites))
#while(Wwrites != "999"):
#    Wsignals.append(int(Wwrites))
#    Wwrites = input("\tDigit vehicle: ")
#    if(str(Wwrites) == "999"):
#        break
#
##South
#print("\n\nInsert South vehicles as 1,2,3,...\n\tDigit 999 to finish")
#Swritev = input("\tDigit vehicle: ")
#while(Swritev != "999"):
#    Svehicles.append(int(Swritev))
#    Swritev = input("\tDigit vehicle: ")
#    if(str(Swritev) == "999"):
#        break
#
#print("\nInsert South signals as 1,2,3,...\n\tDigit 999 to finish")
#Swrites = input("\tDigit South signal: ")
#Ssignals.append(int(Swrites))
#while(Swrites != "999"):
#    Ssignals.append(int(Swrites))
#    Swrites = input("\tDigit vehicle: ")
#    if(str(Swrites) == "999"):
#        break
#######################################################################################




VehicleDirection = [Evehicles, Nvehicles, Wvehicles, Svehicles]
VehicleSignals = [Esignals, Nsignals, Wsignals, Ssignals]

straight = [1, 2, 3, 4]
possible_route_R = [5, 7, 9, 11]
possible_route_L = [6, 8, 10, 12]

result = time.localtime()
time_string = time.strftime("%H_%S__%d_%m_%Y", result)
fileName = "Cross_intersection"
fileName += time_string
fileName += ".rou.xml"

file = open(fileName, "w")
file.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")
file.write("<!-- Generated by %s\ndate: %s -->\n" %(author, time_string))
file.write("<routes> \n")
file.write("    <!-- Vehicle parameters definitions http://sumo.dlr.de/wiki/Definition_of_Vehicles,_Vehicle_Types,_and_Routes --> \n")
inter1="    <vType id=\"%s\"  accel=\"%.1f\" decel=\"%.1f\" sigma=\"%.1f\" minGap=\"%.1f\" maxSpeed=\"%.1f\"/> \n" %(name1,acc,dece,sigma,minG,maxSpeedA/3.6)
inter2="    <vType id=\"%s\"  accel=\"%.1f\" decel=\"%.1f\" sigma=\"%.1f\" minGap=\"%.1f\" maxSpeed=\"%.1f\"/> \n" %(name2,acc,dece,sigma,minG,maxSpeedB/3.6)
file.write(inter1)
file.write(inter2)

file.write("   <!-- routes --> \n")
file.write("    <route id=\"route1\" edges=\"D5 D6\" /> <!-- W2E -->\n")
file.write("    <route id=\"route2\" edges=\"D7 D8\" /> <!-- E2W -->\n")
file.write("    <route id=\"route3\" edges=\"D1 D2\" /> <!-- S2N -->\n")
file.write("    <route id=\"route4\" edges=\"D3 D4\" /> <!-- N2S -->\n")
#introducing turning capability
file.write("    <route id=\"route5\" edges=\"D5 D4\" /> <!-- W2S -->\n")       #right turn
file.write("    <route id=\"route6\" edges=\"D5 D2\" /> <!-- W2N -->\n")    #left turn
file.write("    <route id=\"route7\" edges=\"D7 D2\" /> <!-- E2N -->\n")       #right turn
file.write("    <route id=\"route8\" edges=\"D7 D4\" /> <!-- E2S -->\n")    #left turn
file.write("    <route id=\"route9\" edges=\"D1 D6\" /> <!-- S2W -->\n")       #right turn
file.write("    <route id=\"route10\" edges=\"D1 D8\" /> <!-- S2E -->\n")   #left turn
file.write("    <route id=\"route11\" edges=\"D3 D8\" /> <!-- N2W -->\n")      #right turn
file.write("    <route id=\"route12\" edges=\"D3 D6\" /> <!-- N2E -->\n")   #left turn

file.write("\n")
file.write("    <!-- vehicle generation --> \n")



maxLenVectors = 0

for i in range(len(VehicleSignals)):
    if( (len(VehicleSignals[i])) > maxLenVectors ):
        maxLenVectors = len(VehicleSignals[i])


VehicleByCircle = []
for i in range(maxLenVectors):
    queue = []

    if i < len(VehicleSignals[0]):
        queue.append(VehicleSignals[0][i])
    else:
        queue.append(0)
    if i < len(VehicleSignals[1]):
        queue.append((VehicleSignals[1][i]))
    else:
        queue.append(0)
    if i < len(VehicleSignals[2]):
        queue.append((VehicleSignals[2][i]))
    else:
        queue.append(0)
    if i < len(VehicleSignals[3]):
        queue.append((VehicleSignals[3][i]))
    else:
        queue.append(0)
    VehicleByCircle.append(queue)



NVehicles = 0
NVehicleL = [0]
for i in range(len(VehicleByCircle)):
    for j in range(len(VehicleByCircle[i])):
        if VehicleByCircle[i][j] != 0 :
            NVehicles += 1
            NVehicleL.append(Nvehicles)

counter = 0
for i in range(len(VehicleByCircle)):
    if(VehicleByCircle[i][0] != 0):
        route = 0
        if VehicleByCircle[i][0] == 4:
            route = 2
        if VehicleByCircle[i][0] == 2:
            route = 7
        if VehicleByCircle[i][0] == 3:
            route = 8

        #to_write = "    <vehicle depart=\"%.1f\" id=\"%d\" route=\"route%d\" type=\"CarA\" />" %(float(i)/2, counter, route)
        to_write = "    <vehicle depart=\"%.1f\" id=\"%d\" route=\"route%d\" type=\"CarA\" />" %(departingTime, counter, route)
        file.write(to_write + "\n")
        counter += 1

    if(VehicleByCircle[i][1] != 0):
        route = 0
        if VehicleByCircle[i][1] == 4:
            route = 4
        if VehicleByCircle[i][1] == 2:
            route = 11
        if VehicleByCircle[i][1] == 3:
            route = 12

        #to_write = "    <vehicle depart=\"%.1f\" id=\"%d\" route=\"route%d\" type=\"CarA\" />" %(float(i)/2, counter, route)
        to_write = "    <vehicle depart=\"%.1f\" id=\"%d\" route=\"route%d\" type=\"CarA\" />" %(departingTime, counter, route)
        file.write(to_write + "\n")
        counter += 1

    if(VehicleByCircle[i][2] != 0):
        route = 0
        if VehicleByCircle[i][2] == 4:
            route = 1
        if VehicleByCircle[i][2] == 2:
            route = 5
        if VehicleByCircle[i][2] == 3:
            route = 6

        #to_write = "    <vehicle depart=\"%.1f\" id=\"%d\" route=\"route%d\" type=\"CarA\" />" %(float(i)/2, counter, route)
        to_write = "    <vehicle depart=\"%.1f\" id=\"%d\" route=\"route%d\" type=\"CarA\" />" %(departingTime, counter, route)
        file.write(to_write + "\n")
        counter += 1

    if(VehicleByCircle[i][3] != 0):
        route = 0
        if VehicleByCircle[i][3] == 4:
            route = 3
        if VehicleByCircle[i][3] == 2:
            route = 10
        if VehicleByCircle[i][3] == 3:
            route = 9

        #to_write = "    <vehicle depart=\"%.1f\" id=\"%d\" route=\"route%d\" type=\"CarA\" />" %(float(i)/2, counter, route)
        to_write = "    <vehicle depart=\"%.1f\" id=\"%d\" route=\"route%d\" type=\"CarA\" />" %(departingTime, counter, route)
        file.write(to_write + "\n")
        counter += 1
    file.write("\n")

file.write("\n")
file.write("</routes>")

file.close
print(fileName+" has been generated")
