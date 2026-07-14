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
