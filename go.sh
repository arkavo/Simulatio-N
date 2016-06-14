#!/bin/bash
octave -q --persist getting.m # It calls the octave and remain as interactive
echo " Now we continue "     # Here the script continue when you exit from octave
sleep 5                      # Do some stuffs
exit   
