# use pytransitions
from transitions import Machine

# create a class named Vision
class Vision(object):
    # define the states
    states = [
        "start",
        "obejct found",
        "look for object",
        "object not found",
        "track",
        "error",
        "stop",
    ]

    def __init__(self, camera):
        self.name = camera
        # initialize the state machine
        self.machine = Machine(model=self, states=Vision.states, initial="start")
        # add the transitions
        self.machine.add_transition(
            trigger="initialize", source="start", dest="look for object"
        )
        self.machine.add_transition(
            trigger="object_found",
            source="look for object",
            dest="obejct found",
            after="track",
        )
        self.machine.add_transition(
            trigger="object_not_found",
            source="look for object",
            dest="object not found",
        )
        self.machine.add_transition(
            trigger="no_object", source="object not found", dest="look for object"
        )
        self.machine.add_transition(
            trigger="something_went_wrong", source="*", dest="error", after="stop"
        )
        self.machine.add_transition(
            trigger="object_found", source="obejct found", dest="track"
        )
        self.machine.add_transition(trigger="turn_off", source="*", dest="stop")
