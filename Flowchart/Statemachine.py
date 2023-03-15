#use pytransitions
from transitions import Machine
#create a class named Vision
class Vision(object):
    #define the states
    states = ['start','obejct found', 'object not found', 'track','error','stop']
    def __init__(self,camera):
        self.name=camera
        #initialize the state machine
        self.machine = Machine(model=self, states=Vision.states, initial='start')



