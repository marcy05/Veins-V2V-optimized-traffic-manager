import subprocess


configFile = "C:\\veins-4.7.1acc_id\\examples\\veins\\for net_xml\\Cross_intersection.netccfg"
argument = "netconvert --configuration-file=%s" %(configFile)
subprocess.Popen(argument ,shell=True)
