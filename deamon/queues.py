from queue import Queue

class commandQueue:
    def __init__(self):
        self.queue = Queue()

    def push(self, command):
        self.queue.put(command)

    def pop(self):
        if self.queue.empty():
            return None
        return self.queue.get()

    def empty(self):
        return self.queue.empty()

class commandDict():
    def __init__(self):
        self.PendingCmd = {}
        self.idCount = 0

    def getCurId(self):
        return self.idCount

    def addCMD(self, command):
        self.PendingCmd[self.idCount] = command
        idCount += 1

    def popCMD(self, CMDID):
        poppedCMD = self.PendingCmd.pop(CMDID, False)
        return poppedCMD

firstStageQueue = commandQueue()
secondStageQueue = commandQueue()
