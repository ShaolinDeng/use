#!/usr/bin/ksh
#
# SCRIPT: co-process
# AUTHOR: shaolin.deng
# DATE:   11.24.2010
# REV:    1.1.A (Valid are A, B, D, T and P)
#               (For Alpha, Beta, Dev, Test and Production)
#
# PLATFORM:  Linux
#
# PURPOSE: co-process example
#
# REV LIST:
#        DATE: DATE_of_REVISION
#        BY:	  AUTHOR_of_MODIFICATION   
#        MODIFICATION: Describe what was modified, new features, etc-
#
#
# set -n   # Uncomment to check your syntax, without execution.
#          # NOTE: Do not forget to put the comment back in or
#          #       the shell script will not execute!
# set -x   # Uncomment to debug this shell script (Korn shell only)
#          
##########################################################
########### DEFINE FILES AND VARIABLES HERE ##############
##########################################################



##########################################################
############### DEFINE FUNCTIONS HERE ####################
##########################################################
function trap_exit
{
    #tell the co-process to break out of the loop
    BREAK_OUT='Y'
    print -p $BREAK_OUT #use print -p to talk to the co-process
}

function proc_watch
{
    #this function is started as a co-process

    while :  #loop forever
       do
	read $BREAK_OUT 
	if [[ $BREAK_OUT='Y']]
        then
	    return 0
     	 fi
	done
}

##########################################################
################ BEGINNING OF MAIN #######################
##########################################################
trap 'trap_exit;exit 2' 1 2 3 15
TOTAL_SECONDS=300
BREAK_OUT='N'
proc_watch |&
PW_PID=&1
until((TOTAL_SECONDS==0))
do
    ((TOTAL_SECONDS=TOTAL_SECONDS-1))
    sleep 1
done

BREAK_OUT='Y'
print -p $BREAK_OUT
kill $PW_PID
exit 0


# End of script
