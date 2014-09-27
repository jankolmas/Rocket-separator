Rocket-separator
=========

This code was developed by Jan Kolmas for the Yale Undergraduate Aerospace Association (http://yaleaerospace.com) in Spring 2014 for the Rocket-deployed UAV project. Using a ground module, one can remotely separate the rocket fairing, release the UAV and deploy a parachute.


The code runs on two platforms:

OMEGA-EBAY runs on an Arduino on board the rocket. Digital outputs of the Arduino are connected to pyrotechinc deployment charges. The Arduino is connected to a radio, listening to commands from a ground module.

DETONATOR runs on a ground module connected to a radio. By flipping switches on the module one can remotely detonate the charges on board the rocket. The ground module also displays status of the charges via LEDs


